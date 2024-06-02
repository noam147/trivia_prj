//using ConsoleApp1Check;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
namespace clientGuiTrivia
{
    public partial class LoadingScreenPage : Form
    {
        public LoadingScreenPage(ref ClientHandler clientHandler)
        {
            InitializeComponent();
            ClientHandler local = clientHandler;
            
        }
    }

}
