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
    public partial class GameFinishScreen : Form
    {
        private ClientHandler clientHandler;
        private string username;
        public GameFinishScreen(string username, ClientHandler clientHandler)
        {
            this.clientHandler = clientHandler;
            InitializeComponent();
            char codeMsg = (char)JsonSerialzierHelper.SerializeMessageCode.GET_GAME_RESULT_CODE;
            string msgToSend = "{}";
            Serializer.addLength(ref msgToSend);
            msgToSend = codeMsg + msgToSend;
            clientHandler.sendMsg(msgToSend);
            string msgReceive = clientHandler.receiveMsg();
            var playerStats = Deserializer.desirializeGetGameResultsResponse(msgToSend);
            MessageBox.Show(playerStats.ToString());
        }
        
    }
}
