using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using static JsonDeserialzierHelper.JsonDeserializerHelper;

namespace clientGuiTrivia
{
    public partial class GameResultPage : Form
    {
        private string username;
        private bool isAdmin;
        private ClientHandler clientHandler;
        private CancellationTokenSource cts = new CancellationTokenSource();
        private static readonly object lockSocket = new object();
        private Task task = null;
        public GameResultPage(string username,ClientHandler clientHandler,bool isAdmin)
        {
            this.isAdmin = isAdmin;
            this.username = username;
            this.clientHandler = clientHandler;
            InitializeComponent();
            this.menuButton.Visible = false;
            this.playAgainButton.Visible = false;
            //need to send in thread requests to server to get game result
            // Ensure the FormClosing event is attached
            this.FormClosing += GameResult_FormClosing;

            // Start the task
            this.task = Task.Run(() => RefreshUsers(cts.Token));

        }


        private async Task RefreshUsers(CancellationToken token)
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
                    this.Invoke((MethodInvoker)(() => refreshAction())); // refreshing form

                    await Task.Delay(1000, token); // wait 1000 milisecondes = 1 second 
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

        private void refreshAction()
        {
            Console.WriteLine("Task running...");

            char codeMsg = (char)JsonSerialzierHelper.SerializeMessageCode.GET_GAME_RESULT_CODE;
            string msgToSend = "{}";
            Serializer.addLength(ref msgToSend);
            msgToSend = codeMsg + msgToSend;
            string msgReceived = "";

            lock (lockSocket)
            {
                clientHandler.sendMsg(msgToSend);
                msgReceived = clientHandler.receiveMsg();
            }

            if (!Deserializer.desirializeAreAllPLayersFinishGameRequest(msgReceived))
            {
                return;
            }
            this.menuButton.Visible = true;
            this.playAgainButton.Visible = true;
            gameResult playerResults = Deserializer.desirializeGameResultResponse(msgReceived);

            //gets score
            for (int i = 0; i < playerResults.results.Count; i++)
            {
                var user = playerResults.results[i];
                user.sumPoints = user.correctAnswerCount * 20 - user.wrongAnswerCount * 10;
                if (user.sumPoints < 0)
                    user.sumPoints = 0;
                playerResults.results[i] = user;
            }

            this.label2.Text = "";
            playerResults.results.Sort((x, y) => x.sumPoints.CompareTo(y.sumPoints));//sort points
            playersLabel.Text = "Results:\n";
            foreach (var user in playerResults.results)
            {
                playersLabel.Text += "user: " + user.username + "scored: " + user.sumPoints + " correct: " + user.correctAnswerCount + " wrong: " + user.wrongAnswerCount + " avgTime: " + user.averageAnswerTime + "\n";
            }
            //stop task here
            cts.Cancel();

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }
        private async void GameResult_FormClosing(object sender, FormClosingEventArgs e)
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


        private void menuButton_Click(object sender, EventArgs e)
        {
            loggedUserPage l = new loggedUserPage(username,clientHandler);
            l.Show();
            this.Close();
        }

        private void playAgainButton_Click(object sender, EventArgs e)
        {
            if(isAdmin) //if get time to save the room setting from before
            {
                CreateRoomPage createRoom = new CreateRoomPage(username, clientHandler);
                createRoom.Show();
                this.Close();
            }
            else//if get time to get into waiting page and not roomPage 
            {
                JoinRoomPage roomPage = new JoinRoomPage(username, clientHandler);
                roomPage.Show();
                this.Close();
            }
        }
    }
}
