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

namespace clientGuiTrivia
{
    public partial class AddNewQuestions : Form
    {
        private string username;
        private ClientHandler clientHandler;
        public AddNewQuestions(string user, ClientHandler clientHandler)
        {
            InitializeComponent();
            this.username = user;
            this.clientHandler = clientHandler;
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            loggedUserPage frm = new loggedUserPage(this.username, clientHandler);
            frm.Show();
            this.Close();
        }

        private void sendButton(object sender, EventArgs e)
        {
            if(this.textBox1.Text == "" || this.textBox2.Text == ""||this.textBox3.Text == "" || this.textBox4.Text == "")
            {
                this.label3.Text = "invalid input";
                return;
            }
            addNewQuestionsMessageFields addNewQuestions = new addNewQuestionsMessageFields();
            addNewQuestions.wrongAnswers = new List<string>(); ;
            addNewQuestions.question = this.richTextBox1.Text; ;
            addNewQuestions.rightAnswer = this.textBox4.Text;
            addNewQuestions.wrongAnswers.Add(this.textBox1.Text);
            addNewQuestions.wrongAnswers.Add(this.textBox2.Text);
            addNewQuestions.wrongAnswers.Add(this.textBox3.Text);
            string msgToSend = Serializer.serialize(addNewQuestions);
            clientHandler.sendMsg(msgToSend);
            string msg = clientHandler.receiveMsg();
            this.textBox1.Text = "";
            this.textBox2.Text = "";
            this.textBox3.Text = "";
            this.richTextBox1.Text = "";
            this.textBox4.Text = "";
            bool msgFromServer = Deserializer.desirializeAddQuestionResponse(msg);
            if(msgFromServer) 
            {
                label3.Text = "Question received successfully";
                
                
            }
            else
            {
                label3.Text = "Error during receiving question";
            }

        }
        private void AddNewQuestions_FormClosing(object sender, FormClosingEventArgs e)
        {

        }
    }
}
