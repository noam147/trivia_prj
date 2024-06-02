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
    public partial class signUpPage : Form
    {
        private ClientHandler clientHandler;
        public signUpPage(ClientHandler clientHandler)
        {
            InitializeComponent();
            this.clientHandler = clientHandler;
        }

        private void backButton_Click(object sender, EventArgs e)
        {
            MainScreen frm = new  MainScreen(clientHandler);
            //Form1 frm = new Form1();
            frm.Show();
            this.Close();
            //frm.ShowDialog();
        }

        private void signUpSenderButton_Click(object sender, EventArgs e)
        {
            //send request to server 
            string senderName = sender.ToString();
            //string msg = Serlazer
            signupMessageFields signupMessageFields = new signupMessageFields();
            signupMessageFields.username = this.textBox1.Text;
            signupMessageFields.password = this.textBox2.Text;
            signupMessageFields.email = this.textBox3.Text;
            string msg = Serializer.serialize(signupMessageFields);
            clientHandler.sendMsg(msg);
            string msgFromServer = clientHandler.receiveMsg();
            if(Deserializer.desirializeSignupResponse(msgFromServer))
            {
                MainScreen mainScreen = new MainScreen(clientHandler);
                this.Close();
                mainScreen.Show();
            }
            this.warningLabel.Text = "user name already exsist or other problem occured.\ntry put another username";//for example
        }
    }
}
