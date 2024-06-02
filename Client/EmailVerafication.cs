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
            if(textBox1.Text.Length == 6)
            {
                //send to server the code
                textBox1.Text = "";
                //if msg from server is good:
                this.button2.Visible = true;
            }

        }

        private void button1_Click(object sender, EventArgs e)
        {
            signUpPage signUp = new signUpPage(clientHandler);
            this.Close();
            signUp.Show();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            MainScreen mainScreen = new MainScreen(clientHandler);
            this.Close();
            mainScreen.Show();
        }
    }
}
