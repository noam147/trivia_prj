using JsonSerialzierHelper;
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
    public partial class UserWaitingRoom : Form
    {
        private string username;
        private ClientHandler clientHandler;
        private int numPlayers;
        private int maxQuestions;
        private int timePerQuestion;
        private CancellationTokenSource cts = new CancellationTokenSource();
        private static readonly object lockSocket = new object();
        private Task task = null;

        public UserWaitingRoom(string user,string roomName, ClientHandler clientHandler)
        {
            this.username = user;
            int numQuestions = 0;
            float timePerQuestion = 0;//get this from server
            InitializeComponent();
            this.roomNameLabel.Text = "you are connected to room: " + roomName;
            this.UsersListLabel.Text = "current users are: ";
            this.roomSettingsLabel.Text = "number of questions: " + numQuestions + ", time per question: "+timePerQuestion;
            this.clientHandler = clientHandler;
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

                    //this is for user:
                    if (Deserializer.desirializeLeaveRoomResponse(msgReceived))
                    {
                        this.Invoke((MethodInvoker)delegate { leaveAction(); });
                        return;
                        //if the admin exited go to menu again
                    }
                    if (Deserializer.desirializeStartGameResponse(msgReceived))
                    {
                        this.Invoke((MethodInvoker)delegate
                        {
                            GameQuestions game = new GameQuestions(username, this.clientHandler, this.maxQuestions,false,timePerQuestion);
                            //if the admin start game
                            game.Show();
                            this.Close();
                            return;
                        });                   
                    }
                    var roomData = Deserializer.desirializeGetRoomStateResponse(msgReceived);
                    if (roomData.status == -2)
                    {
                        continue;
                    }
                    
                    this.Invoke((MethodInvoker)delegate
                    {
                        this.timePerQuestion = roomData.answerTimeOut;
                        this.roomSettingsLabel.Text = "number of questions: " + roomData.AnswerCount.ToString() + ", time per question: " + roomData.answerTimeOut.ToString();
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
       
        private void button1_Click(object sender, EventArgs e)
        {
            leaveAction();
        }
        private void leaveAction()
        {
            char codeMsg = (char)JsonSerialzierHelper.SerializeMessageCode.GET_LEAVE_ROOM_CODE;
            string msgToSend = "{}";
            Serializer.addLength(ref msgToSend);
            msgToSend = codeMsg + msgToSend;
            string msgReceived = "";

            lock (lockSocket)
            {
                clientHandler.sendMsg(msgToSend);
                msgReceived = clientHandler.receiveMsg();
            }


            loggedUserPage frm = new loggedUserPage(this.username, clientHandler);
            frm.Show();
            this.Close();

        }

        private async void UserWaitingRoom_FormClosing(object sender, FormClosingEventArgs e)
        {
            cts.Cancel();
            if (this.task != null)
            {
                try
                {
                    await this.task; // Await the task asynchronously
                }
                catch (TaskCanceledException)
                {
                    Console.WriteLine("Task was canceled.");
                }
                catch (Exception ex)
                {
                    // Handle any other exceptions that might occur
                    Console.WriteLine("An error occurred: " + ex.Message);
                }
            }
        }

        private void UserWaitingRoom_Load(object sender, EventArgs e)
        {

        }
    }
}
