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
    public partial class loggedUserPage : Form
    {
        private string username;
        private ClientHandler clientHandler;
        public loggedUserPage(string user, ClientHandler clientHandler)
        {
            InitializeComponent();
            this.username = user;
            this.clientHandler = clientHandler;
            this.label1.Text += user;
            ScaleFont(label1);
        }

        private void button2_Click(object sender, EventArgs e)
        {
      
            logoutMessageFields logoutMessageFields = new logoutMessageFields();
            clientHandler.sendMsg(Serializer.serialize(logoutMessageFields));
            clientHandler.receiveMsg();

            this.Invoke((MethodInvoker)delegate {
                MainScreen frm = new MainScreen(clientHandler);
                frm.FormClosed += (formClosedSender, formClosedEventArgs) => {
                    // This code will execute when the loggedUserPage form is closed
                    this.Hide(); // Close the current form after the loggedUserPage form is closed
                    this.Close();
                };
                this.Hide();
                this.Close();
                frm.ShowDialog();
            });

        }

        private void button6_Click(object sender, EventArgs e)
        {
            bestScorePage frm = new bestScorePage(this.username,clientHandler);
            frm.Show();
          
            this.Close();
            
            
        }

        private void button4_Click(object sender, EventArgs e)
        {
            CreateRoomPage frm = new CreateRoomPage(this.username, clientHandler);
            frm.Show();
            
            this.Close();
        }

        private void button5_Click(object sender, EventArgs e)
        {
            UserStatusPage frm = new UserStatusPage(this.username, clientHandler);
            frm.Show();
            
            this.Close();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            JoinRoomPage frm = new JoinRoomPage(this.username, clientHandler);
            frm.Show();
            this.Close();
        }


        private void ScaleFont(Label lab)
        {
            SizeF extent = TextRenderer.MeasureText(lab.Text, lab.Font);

            float hRatio = lab.Height / extent.Height;
            float wRatio = lab.Width / extent.Width;
            float ratio = (hRatio < wRatio) ? hRatio : wRatio;

            float newSize = lab.Font.Size * ratio;

            lab.Font = new Font(lab.Font.FontFamily, newSize, lab.Font.Style);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            AddNewQuestions addNewQuestions = new AddNewQuestions(this.username,this.clientHandler);
            this.Close();
            addNewQuestions.Show();

        }

        private void loggedUserPage_FormClosing(object sender, FormClosingEventArgs e)
        {
            //this.clientHandler.closeConnection();
        }
    }
}
