using JsonSerialzierHelper;
using System;
using System.Threading.Tasks;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace clientGuiTrivia
{
    public partial class MainScreen : Form
    {
        Timer timer = new Timer();
        private string _username = "";
        ClientHandler clientHandler;
        public MainScreen(ClientHandler clientHandler)
        {
            InitializeComponent();
            this.clientHandler = clientHandler;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.label3.Text = "";
            _username = this.textBox1.Text;
            string password = this.textBox2.Text;

           loginMessageFields loginMessageFields = new loginMessageFields();
            loginMessageFields.username = _username;
            loginMessageFields.password = password;


            string msg = Serializer.serialize(loginMessageFields);
            clientHandler.sendMsg(msg);
            string msgFromServer = clientHandler.receiveMsg();
            if (Deserializer.desirializeLoginResponse(msgFromServer))
            {
                this.Invoke((MethodInvoker)delegate {
                    loggedUserPage logPage = new loggedUserPage(_username, clientHandler);
                    logPage.FormClosed += (formClosedSender, formClosedEventArgs) => {
                        // This code will execute when the loggedUserPage form is closed
                        //this.Hide();
                        //this.Close(); // Close the current form after the loggedUserPage form is closed
                    };
                    
                    this.Hide();
                    logPage.ShowDialog();
                    this.Close();
                    
                });
               
                
               

            }
            Task.Delay(50).Wait();
            this.label3.Text = "invalid details, try again.";
            //send to server login request
            //get server response
            //if server respone == status 1:
            //loggedUserPage frm = new loggedUserPage(this._username, clientHandler);
            //this.Hide();
            //frm.ShowDialog();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //go to sign up page
            //send msg to server
            //wariningLabel.Text = "passwword or user name are incorrect"; //for exasmple
            signUpPage frm = new signUpPage(clientHandler);

            //frm.Show();
            this.Hide();
            frm.ShowDialog();
            this.Close();

        }
   
        private void textBox1_textChanged(object sender, EventArgs e)
        {
            this.label3.Text = "";
        }
        private void textBox2_textChanged(object sender, EventArgs e)
        {
            this.label3.Text = "";
        }

        private void button7_Click(object sender, EventArgs e)
        {
            this.Hide();
            this.Close();
        }

    }
}
