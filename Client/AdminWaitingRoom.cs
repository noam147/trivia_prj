using System;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using static JsonDeserialzierHelper.JsonDeserializerHelper;

namespace clientGuiTrivia
{
    public partial class AdminWaitingRoom : Form
    {
        private int maxQuestions;
        private string username;
        private ClientHandler clientHandler;
        private CancellationTokenSource cts = new CancellationTokenSource();
        private static readonly object lockSocket = new object();
        private Task task = null;
        private int timePerQuestion;
        public AdminWaitingRoom(string user, int maxPlayers, int numQuestions, int timePerQuestion, string roomName, ClientHandler clientHandler)
        {
            this.timePerQuestion = timePerQuestion;
            username = user;
            this.maxQuestions = numQuestions;
            InitializeComponent();
            this.label7.Text = "max players: " + maxPlayers + ", number of questions: " + numQuestions + ", time for each question: " + timePerQuestion;
            this.label6.Text = "you are connected to room: " + roomName;
            this.clientHandler = clientHandler;

            // Ensure the FormClosing event is attached
            this.FormClosing += AdminWaitingRoom_FormClosing;

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

            char codeMsg = (char)JsonSerialzierHelper.SerializeMessageCode.GET_ROOM_STATE_CODE;
            string msgToSend = "{}";
            Serializer.addLength(ref msgToSend);
            msgToSend = codeMsg + msgToSend;
            string msgReceived = "";

            lock (lockSocket)
            {
                clientHandler.sendMsg(msgToSend);
                msgReceived = clientHandler.receiveMsg();
            }

            //this is for user:
            if (Deserializer.desirializeLeaveRoomResponse(msgReceived))
            {
                //if the admin exited go to menu again
            }
            if (Deserializer.desirializeStartGameResponse(msgReceived))
            {
                GameQuestions game = new GameQuestions(username, this.clientHandler, this.maxQuestions,true,this.timePerQuestion);
                //if the admin start game
                game.Show();
                this.Close();
            }
            var roomData = Deserializer.desirializeGetRoomStateResponse(msgReceived);
            if (roomData.status == -2)
            {
                return;
            }

            string selectedItem = UsersList.SelectedItem?.ToString();

            UsersList.Items.Clear();
            foreach (var user in roomData.players)
            {
                this.UsersList.Items.Add(user);
            }

            if (selectedItem != null && roomData.players.Contains(selectedItem))
            {
                UsersList.SelectedItem = selectedItem;
            }

            this.UsersList.Refresh();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            char codeMsg = (char)JsonSerialzierHelper.SerializeMessageCode.GET_ADMIN_CLOSE_ROOM_REQUEST;
            string msgToSend = "{}";
            Serializer.addLength(ref msgToSend);
            msgToSend = codeMsg + msgToSend;
            string msgReceived = "";

            lock (lockSocket)
            {
                clientHandler.sendMsg(msgToSend);
                msgReceived = clientHandler.receiveMsg();
            }

            if (Deserializer.desirializeServerAnswerToAdminStartGameRequest(msgReceived))
            {
                var frm = new loggedUserPage(username, clientHandler);
                frm.Show();
                this.Close();
            }
            else
            {
                var frm2 = new loggedUserPage(username, clientHandler);
                frm2.Show();
                this.Close();
            }
        }

        private void startGmaeButton_Click(object sender, EventArgs e)
        {
            char codeMsg = (char)JsonSerialzierHelper.SerializeMessageCode.GET_ADMIN_START_GAME_REQUEST;
            string msgToSend = "{}";
            Serializer.addLength(ref msgToSend);
            msgToSend = codeMsg + msgToSend;
            string msgReceived = "";

            lock (lockSocket)
            {
                clientHandler.sendMsg(msgToSend);
                msgReceived = clientHandler.receiveMsg();
            }

            if (Deserializer.desirializeServerAnswerToAdminStartGameRequest(msgReceived))
            {
                // get into game
                var frm2 = new GameQuestions(username, clientHandler,this.maxQuestions,true,this.timePerQuestion);//admin page
                frm2.Show();
                this.Close();
                return;
            }
            else
            {
                // display error msg
            }

            var frm = new loggedUserPage(username, clientHandler);
            frm.Show();
            this.Close();
        }

        private async void AdminWaitingRoom_FormClosing(object sender, FormClosingEventArgs e)
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

        private void AdminWaitingRoom_Load(object sender, EventArgs e) { }

        private void UsersList_SelectedIndexChanged(object sender, EventArgs e) { }
    }
}
