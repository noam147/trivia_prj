using JsonSerialzierHelper;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace clientGuiTrivia
{
    public partial class CreateRoomPage : Form
    {
        private string username;
        private ClientHandler clientHandler;
        public CreateRoomPage(string username, ClientHandler clientHandler)
        {
            this.username = username;
            InitializeComponent();
            this.KeyPreview = true; // Set KeyPreview to true in the constructor
            this.KeyPress += textBox3_KeyPress; // add listner for enter press
            this.clientHandler = clientHandler;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            loggedUserPage frm = new loggedUserPage(this.username,clientHandler );
            this.Close();
            frm.Show();
        }
        private void textBox3_KeyPress(object sender, KeyPressEventArgs e)
        {

            if (e.KeyChar == (char)Keys.Enter)
            {
                button1_Click(sender, e);
;                // Enter key was pressed while the text box has focus
                // Add your code here
            }
        }
        private void button1_Click(object sender, EventArgs e)
        {
            string roomName = this._roomName.Text;
            int numPlayers = 0;
            int numQuestions = 0;
            int time = 0;
            try
            {
                numPlayers = int.Parse(this._numberOfPlayers.Text);
                numQuestions =int.Parse(this._numberOfQuestions.Text);
                time = int.Parse(this._TimeForQuestion.Text);
            }
            catch
            {
                this.warningLabel.Text = "error inputs are invalid!";
                return;
            }
            //UserWaitingRoom frm = new UserWaitingRoom(this.username,roomName);
            //this.Close();
            //frm.Show();

            CreateRoomMessageFields createRoomMessageFields = new CreateRoomMessageFields();
            createRoomMessageFields.maxUsers = numPlayers;
            createRoomMessageFields.questionTimeout = time;
            createRoomMessageFields.roomName = roomName;
            createRoomMessageFields.questionCount = numQuestions;
            string msgToSend = Serializer.serialize(createRoomMessageFields);
            clientHandler.sendMsg(msgToSend);
            string msgRecived = clientHandler.receiveMsg();
            if(Deserializer.desirializeCreateRoomResponse(msgRecived))
            {
                AdminWaitingRoom frm = new AdminWaitingRoom(this.username, numPlayers, numQuestions, time, roomName, clientHandler);
                this.Hide();
                frm.Show();
                this.Close();

            }
            else
            {
                warningLabel.Text = "error - try change room name or try again";
            }

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label8_Click(object sender, EventArgs e)
        {

        }

        private void CreateRoomPage_Load(object sender, EventArgs e)
        {

        }

        private void _numberOfPlayers_TextChanged(object sender, EventArgs e)
        {
            warningLabel.Text = "";
        }

        private void __TextChanged(object sender, EventArgs e)
        {
        }

        private void _roomName_TextChanged(object sender, EventArgs e)
        {
            warningLabel.Text = "";
        }
        
        private void _numberOfQuestions_TextChanged(object sender, EventArgs e)
        {
            warningLabel.Text = "";
        }

        private void _TimeForQuestion_TextChanged(object sender, EventArgs e)
        {
            warningLabel.Text = "";
        }
    }
}
