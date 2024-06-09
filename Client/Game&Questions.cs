using JsonSerialzierHelper;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using static JsonDeserialzierHelper.JsonDeserializerHelper;

namespace clientGuiTrivia
{
    public partial class GameQuestions : Form
    {
        private string username;
        private ClientHandler clientHandler;
        private bool isAdmin;
        private int timePerQuestion;

        private CancellationTokenSource cts = new CancellationTokenSource();
        private static readonly object lockSocket = new object();
        private Task task = null;
        private Task task2 = null;
        public GameQuestions(string user, ClientHandler clientHandler, int maxQuestion,bool isAdmin,int time)
        {
            this.timePerQuestion = time;
            this.isAdmin = isAdmin;
            this.username = user;
            this.clientHandler = clientHandler;

            InitializeComponent();
            this.timeToQuestionLabel.Text = time.ToString();
            this.NumberOfRightQuestions.Text = "0";
            this.NumberOfQuestionLeft.Text = maxQuestion.ToString();


            // Ensure the FormClosing event is attached
            this.FormClosing += Game_FormClosing;

            // Start the task
            this.task = Task.Run(() => updateTimer(cts.Token));
            this.task2 = Task.Run(() => updateQuestions(cts.Token));
            //send get question request
            //getQuestion();
        }

        //problem - the thread keeps on sending msgs!
        private void getQuestion()
        {
            //should be wait until timer for question ended to get everyone on the same question each time?

            string msg = Serializer.serialize((char)JsonSerialzierHelper.SerializeMessageCode.GET_GET_QUESTION_CODE);
            //Console.WriteLine(msg[0]);
            char ch = msg[0];
            clientHandler.sendMsg(msg);
            string msgRecived = clientHandler.receiveMsg();
            Question question = Deserializer.desirializeGetQuestionResponse(msgRecived);
            if (question.status == -1)//if server sends error
            {
                // getQuestion();

                //go to result page
                GameResultPage gameResult = new GameResultPage(username,clientHandler,isAdmin);
                gameResult.Show();
                this.Close();
                //loggedUserPage loggedUser = new loggedUserPage(this.username, this.clientHandler);
                //loggedUser.Show();
                //this.Close();

            }
            else if (question.status == 1)
            {
                //no more quesitions left - get into another page or something - or wait until all players will finish?
            }
            else if(question.status == -3)
            {
                return;//wait for question to come..
            }
            else if (question.status == 0)
            {
                if(questionLabel.Text != question.question)
                {
                    this.NumberOfQuestionLeft.Text = (int.Parse(NumberOfQuestionLeft.Text)-1).ToString();
                    timeToQuestionLabel.Text = this.timePerQuestion.ToString();
                }
                
                //display the question
                this.questionLabel.Text = question.question;
                this.answer1.Text = question.answers[0];
                this.answer2.Text = question.answers[1];
                this.answer3.Text = question.answers[2];
                this.answer4.Text = question.answers[3];
            }
        }
        private void sendAnswerToSrever(int indexAnswer)
        {
            SendAnswerMessageFields answer = new SendAnswerMessageFields();
            answer.answerIndex = indexAnswer;
            string msg = Serializer.serialize(answer);
            clientHandler.sendMsg(msg);
            string msgRecived = clientHandler.receiveMsg();
            SubmitAnswerResponse submitAnswer = new SubmitAnswerResponse();

            try
            {
                submitAnswer = Deserializer.desirializeSubmitAnswerResponse(msgRecived);
            }
            catch (Exception e)
            {
                //if invalid code msg
                //do not accept the sending?
                return;
            }
            if (submitAnswer.hasUserAnswerRight)
            {
                this.NumberOfRightQuestions.Text = (int.Parse(this.NumberOfRightQuestions.Text) + 1).ToString();
            }
            //this.NumberOfQuestionLeft.Text = (int.Parse(this.NumberOfQuestionLeft.Text) - 1).ToString();

            //getQuestion();//at the end get a new questoin
        }
        private void answer1_Click(object sender, EventArgs e)
        {
            sendAnswerToSrever(0);
        }

        private void answer2_Click(object sender, EventArgs e)
        {
            sendAnswerToSrever(1);
        }

        private void answer3_Click(object sender, EventArgs e)
        {
            sendAnswerToSrever(2);
        }

        private void answer4_Click(object sender, EventArgs e)
        {
            sendAnswerToSrever(3);
        }

        private void timeToQuestionLabel_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
        private void updateQuestions(CancellationToken token)
        {
            try
            {
                while(!token.IsCancellationRequested)
                {
                    while (!(this.IsHandleCreated)) // runs untill ready to refresh
                    {
                        continue;
                    }
                    Thread.Sleep(100);
                    Invoke((MethodInvoker)delegate { getQuestion(); });

                }
               
            }
            catch (TaskCanceledException)
            {
                Console.WriteLine("Task was canceled.");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Unexpected error: {ex.Message}");
            }
        }
        private async Task updateTimer(CancellationToken token)
        {
            try
            {
                while (!token.IsCancellationRequested)
                {
                    Console.WriteLine("Task running...");

                    while (!(this.IsHandleCreated)) // runs untill ready to refresh
                    {
                        continue;
                    }

                    //update next second
                    await Task.Delay(1000, token); // wait 1000 milisecondes = 1 second 
                    Console.WriteLine("updating");
                    Invoke((MethodInvoker)delegate
                    {
                        this.timeToQuestionLabel.Text = (int.Parse(timeToQuestionLabel.Text) - 1).ToString();
                        if (int.Parse(timeToQuestionLabel.Text) == 0)
                        {
                            timeToQuestionLabel.Text = this.timePerQuestion.ToString();
                            //sendAnswerToSrever(-1);//this will be in server
                            //getQuestion();//server auto send a fake answer request so we will get another question
                        }

                    });
                    



                }
            }
            catch (TaskCanceledException)
            {
                Console.WriteLine("Task was canceled.");
            }
            catch (Exception ex)
            {
                Console.WriteLine($"Unexpected error: {ex.Message}");
            }
        }

        private async void Game_FormClosing(object sender, FormClosingEventArgs e)
        {
            cts.Cancel();
            if (task != null)
            {
                try
                {
                    await task; // Await the task instead of blocking
                }
                catch (TaskCanceledException)
                {
                    Console.WriteLine("Task was canceled.");
                }
                catch (Exception ex)
                {
                    Console.WriteLine($"Unexpected error: {ex.Message}");
                }
            }
        }
    }
}