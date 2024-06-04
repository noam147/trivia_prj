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
    public partial class UserStatusPage : Form
    {
        private string username;
        private ClientHandler clientHandler;
        public UserStatusPage(string user, ClientHandler clientHandler)
        {
            this.username = user;
            InitializeComponent();
            this.clientHandler = clientHandler;

        
            getStatsMessageFields getStatsMessageFields = new getStatsMessageFields();
            getStatsMessageFields.username = this.username;
            string msgToSend = Serializer.serialize(getStatsMessageFields);
            clientHandler.sendMsg(msgToSend);
            string msg = clientHandler.receiveMsg();
            
            List<string> userDetalis = Deserializer.desirializeGetStatsResponse(msg);
            this.GamesLabel.Text += userDetalis[2];
            this.RightAnswerLabel.Text += userDetalis[1];
            this.WrongAnswersLabel.Text += ((int.Parse(userDetalis[4]) - int.Parse(userDetalis[1]))).ToString();//total- right
            this.AvgTimeLabel.Text += userDetalis[0];//time
            //0 -time 1 coorect answer 2 numgames 3 player score 4 total answers
            this.TotalScoreLabel.Text += userDetalis[3];

        }

        private void button1_Click(object sender, EventArgs e)
        {
            loggedUserPage frm = new loggedUserPage(this.username,clientHandler);
            frm.Show();
            this.Close();
        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void UserStatusPage_Load(object sender, EventArgs e)
        {

        }
    }
}
