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
    public partial class GameResultPage : Form
    {
        private string username;
        private ClientHandler clientHandler;
        public GameResultPage(string username,ClientHandler clientHandler)
        {
            this.username = username;
            this.clientHandler = clientHandler;
            InitializeComponent();
            //need to send in thread requests to server to get game result
            
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }
    }
}
