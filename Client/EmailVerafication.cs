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
    public partial class EmailVerafication : Form
    {
        private ClientHandler clientHandler;
        public EmailVerafication(ClientHandler c)
        {
            InitializeComponent();
            clientHandler = c;
            this.button2.Visible = false;
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            this.errorLabel.Text = "";
            int code = 0;
            if(textBox1.Text.Length == 6)
            {
                //send to server the code    
                try
                {
                    code = int.Parse(textBox1.Text);
                    textBox1.Text = "";
                }
               catch 
                {
                    this.errorLabel.Text = "incorrect";
                    textBox1.Text = "";
                    return;
                }
                emailVerMessageFields email = new emailVerMessageFields();
                email.emailCode = code;
                clientHandler.sendMsg(Serializer.serialize(email));
                string msgRecived = clientHandler.receiveMsg();
                if(Deserializer.desirializeEmailVerafictionRequest(msgRecived))
                {
                    this.errorLabel.Text = "";
                    //if msg from server is good:
                    this.button2.Visible = true;
                    this.errorLabel.Text = "user signuped successfully";
                }
                else
                {
                    this.errorLabel.Text = "incorrect";
                }
               


            }

        }

        private void button1_Click(object sender, EventArgs e)
        {
            signUpPage signUp = new signUpPage(clientHandler);
            signUp.Show();
            this.Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            MainScreen mainScreen = new MainScreen(clientHandler);
            mainScreen.Show();
            this.Close();
        }

        private void EmailVerafication_Load(object sender, EventArgs e)
        {

        }
    }
}
