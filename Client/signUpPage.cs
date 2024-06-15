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

        private async void signUpSenderButton_Click(object sender, EventArgs e)
        {
            // Update the label text immediately
            this.warningLabel.Text = "checking info...";

            // Perform the time-consuming operations asynchronously
            bool isSignUpSuccessful = await Task.Run(() =>
            {
                string senderName = sender.ToString();
                signupMessageFields signupMessageFields = new signupMessageFields
                {
                    username = this.textBox1.Text,
                    password = this.textBox2.Text,
                    email = this.textBox3.Text
                };
                string msg = Serializer.serialize(signupMessageFields);
                clientHandler.sendMsg(msg);
                string msgFromServer = clientHandler.receiveMsg();
                return Deserializer.desirializeSignupResponse(msgFromServer);
            });

            // Handle the result on the UI thread
            if (isSignUpSuccessful)
            {
                EmailVerafication email = new EmailVerafication(clientHandler);
                email.Show();
                this.Close();
            }
            else
            {
                this.warningLabel.Text = "User name already exists or another problem occurred.\nPlease try another username.";
            }
        }

    }
}
