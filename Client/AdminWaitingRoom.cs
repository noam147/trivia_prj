using System;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace clientGuiTrivia
{
    public partial class AdminWaitingRoom : Form
    {
        private string username;
        private ClientHandler clientHandler;
        private CancellationTokenSource cts = new CancellationTokenSource();
        private static readonly object lockSocket = new object();
        private Task task = null;

        public AdminWaitingRoom(string user, int maxPlayers, int numQuestions, float timePerQuestion, string roomName, ClientHandler clientHandler)
        {
            username = user;
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

                    var roomData = Deserializer.desirializeGetRoomStateResponse(msgReceived);

                    this.Invoke((MethodInvoker)delegate
                    {
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
                    });

                    await Task.Delay(1000, token);
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
            }
            else
            {
                // display error msg
            }

            var frm = new loggedUserPage(username, clientHandler);
            frm.Show();
            this.Close();
        }

        private void AdminWaitingRoom_FormClosing(object sender, FormClosingEventArgs e)
        {
            cts.Cancel();
            try
            {
                this.task?.Wait();
            }
            catch (AggregateException ex)
            {
                if (ex.InnerException is TaskCanceledException)
                {
                    Console.WriteLine("Task was canceled.");
                }
                else
                {
                    throw;
                }
            }
        }

        private void AdminWaitingRoom_Load(object sender, EventArgs e) { }

        private void UsersList_SelectedIndexChanged(object sender, EventArgs e) { }
    }
}
