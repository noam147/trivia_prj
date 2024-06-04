using JsonSerialzierHelper;
using System;
using System.Collections.Generic;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using static JsonDeserialzierHelper.JsonDeserializerHelper;

namespace clientGuiTrivia
{
    public partial class JoinRoomPage : Form
    {
        private string username;
        private string roomToJoin = "";
        private ClientHandler clientHandler;
        private CancellationTokenSource cts = new CancellationTokenSource();
        private static readonly object lockSocket = new object();
        private Task task = null;

        public JoinRoomPage(string user, ClientHandler clientHandler)
        {
            this.username = user;
            this.clientHandler = clientHandler;

            InitializeComponent();
            this.joinButton.Enabled = false; //in the start the button is disabled 
                                             //send request to server to check available rooms

            // Ensure the FormClosing event is attached
            this.FormClosing += JoinRoomPage_FormClosing;

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

                    /*char codeMsg = (char)JsonSerialzierHelper.SerializeMessageCode.GET_ROOM_CODE;
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
*/
                    while (!(this.IsHandleCreated))
                    {
                        continue;  
                    }
                    this.Invoke((MethodInvoker)(() => refreshAction()));

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

        private void button2_Click(object sender, EventArgs e)
        {
            loggedUserPage frm = new loggedUserPage(this.username, clientHandler);
            frm.Show();
            this.Close();
        }

        private void joinButton_Click(object sender, EventArgs e)
        {
            joinRoomMessageFields joinRoom = new joinRoomMessageFields();
            joinRoom.roomName = this.roomToJoin;
            string msgToSend = Serializer.serialize(joinRoom);
            clientHandler.sendMsg(msgToSend);
            string msgReceived = clientHandler.receiveMsg();
            if (Deserializer.desirializeJoinRoomResponse(msgReceived))
            {
                UserWaitingRoom frm = new UserWaitingRoom(this.username, roomToJoin, clientHandler);
                frm.Show();
                this.Close();
            }
            else
            {
                //display error label
            }
        }

        private void refreshAction()
        {
            getRoomsMessageFields getRooms = new getRoomsMessageFields();
            string msg = Serializer.serialize(getRooms);
            clientHandler.sendMsg(msg);
            string msgReceived = clientHandler.receiveMsg();
            List<string> roomNames = Deserializer.desirializeGetRoomsResponse(msgReceived);
            if (roomNames == null)
            {
                return;
            }

            this.RoomsList.Text = "RoomsList:\n";
            this.RoomsList.Visible = true;
            string selectedItem = RoomsList.SelectedItem?.ToString();

            RoomsList.Items.Clear();
            foreach (var room in roomNames)
            {
                this.RoomsList.Items.Add(room);
            }

            if (selectedItem != null && roomNames.Contains(selectedItem))
            {
                RoomsList.SelectedItem = selectedItem;
                this.roomToJoin = selectedItem;
            }

            if (selectedItem == null)
            {
                this.joinButton.Enabled = false;
            }
        }

        private void RoomsList_SelectedIndexChanged(object sender, EventArgs e)
        {
            string selectedItem = RoomsList.SelectedItem?.ToString();
            if (selectedItem != null)
            {
                RoomsList.SelectedItem = selectedItem;
                joinButton.Enabled = true;
                this.roomToJoin = selectedItem;
            }
        }

        private void refreshButton_Click(object sender, EventArgs e)
        {
            refreshAction();
        }

        private async void JoinRoomPage_FormClosing(object sender, FormClosingEventArgs e)
        {
            cts.Cancel();

            try
            {
                Console.WriteLine("check1");
                if (task != null)
                {
                    await task; // Wait for the task to complete
                }
                Console.WriteLine("check2");
            }
            catch (TaskCanceledException)
            {
                Console.WriteLine("TaskCanceledException caught during form closing.");
            }
            catch (Exception ex)
            {
                Console.WriteLine("Unexpected error during form closing: " + ex.Message);
            }
        }
    }
}
