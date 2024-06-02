using JsonSerialzierHelper;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static JsonDeserialzierHelper.JsonDeserializerHelper;

namespace clientGuiTrivia
{
    public partial class Game_Questions : Form
    {
        private string username;
        private ClientHandler clientHandler;
        public Game_Questions(string user, ClientHandler clientHandler,int maxQuestion)
        {
            this.username = user;
            this.clientHandler = clientHandler;

            InitializeComponent();
            this.NumberOfRightQuestions.Text = "0";
            this.NumberOfQuestionLeft.Text = maxQuestion.ToString();
            //send get question request
        }
        private void getQuestion()
        {
            //should be wait until timer for question ended to get everyone on the same question each time?
           
            string msg = Serializer.serialize((char)JsonSerialzierHelper.SerializeMessageCode.GET_GET_QUESTION_CODE);
            clientHandler.sendMsg(msg);
            string msgRecived = clientHandler.receiveMsg();
            Question question =  Deserializer.desirializeGetQuestionResponse(msgRecived);
            if(question.status == -1)
            {
                //error accured - server return error
            }
            else if(question.status == 0)
            {
                //no more quesitions left - get into another page or something - or wait until all players will finish?
            }
            else if(question.status == 1)
            {
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
            catch(Exception e) 
            {
                //if invalid code msg
                //do not accept the sending?
                return;
            }
            if(submitAnswer.hasUserAnswerRight) 
            {
                this.NumberOfRightQuestions.Text = (int.Parse(this.NumberOfRightQuestions.Text) + 1).ToString();        
            }
            this.NumberOfQuestionLeft.Text = (int.Parse(this.NumberOfQuestionLeft.Text)-1).ToString();

            getQuestion();//at the end get a new questoin
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
    }
}
