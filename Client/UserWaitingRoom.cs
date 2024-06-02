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
        public UserWaitingRoom(string user,string roomName, ClientHandler clientHandler)
        {
            int numQuestions = 0;
            int numPlayers = 0;
            float timePerQuestion = 0;//get this from server
            InitializeComponent();
            this.roomNameLabel.Text = "you are connected to room: " + roomName;
            this.UsersListLabel.Text = "current users are: ";
            this.roomSettingsLabel.Text = "number of questions: " + numQuestions + ", time per question: "+timePerQuestion;
            this.clientHandler = clientHandler;
        }
        public void GetRoomStateFromServer()//thread func
        {
            char length = '\0';
            char codeMsg = (char)JsonSerialzierHelper.SerializeMessageCode.GET_ROOM_STATE_CODE;
            string msgTosend =  "";//send get room code
            msgTosend += codeMsg;
            msgTosend += length + length + length + length;
            this.clientHandler.sendMsg(msgTosend);
            string msgRecived = clientHandler.receiveMsg();
            RoomState roomState = Deserializer.desirializeGetRoomStateResponse(msgRecived);
           
            this.roomSettingsLabel.Text = "number of questions: " + roomState.AnswerCount + ", time per question: " + roomState.answerTimeOut;
            if (roomState.hasGameBegun)
            {
                //get into game page
            }
            if(roomState.status == -1)//if admin left
            {
                roomNameLabel.Text = "admin closed Room - you need to exit";
                UsersListLabel.Text = "";
            }
            if (roomState.status == -2)//if error accuared - server sent invalid msg
            {
                //break;
            }
            if (roomState.players.Count > numPlayers)
            {
                this.UsersListLabel.Text = "current users are: ";
                for (int i = 0; i < roomState.players.Count; i++)
                {
                    this.UsersListLabel.Text += roomState.players[i] + ", ";
                }
                this.UsersListLabel.Text.Substring(0,UsersListLabel.Text.Length - 2);//crop the last , 
                numPlayers = roomState.players.Count;
            }
           
        }
        private void button1_Click(object sender, EventArgs e)
        {
            char length = '\0';//when leaving - sending to server
            char codeMsg = (char)JsonSerialzierHelper.SerializeMessageCode.GET_LEAVE_ROOM_CODE;
            string msgTosend = "";
            msgTosend += codeMsg;
            msgTosend += length + length + length + length;
            this.clientHandler.sendMsg(msgTosend);
            clientHandler.receiveMsg();
            loggedUserPage frm = new loggedUserPage(this.username,clientHandler);
            frm.Show();
            this.Close();
        }

        private void UserWaitingRoom_Load(object sender, EventArgs e)
        {

        }
    }
}
