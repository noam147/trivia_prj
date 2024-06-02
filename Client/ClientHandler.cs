using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
//using static ConsoleApp1Check.Program;

namespace clientGuiTrivia
{
    public struct JsonForamt//should we put all possible commands in json?
    {
        public string status;
        public string message;//the error msg if needed
    }
    public class ClientHandler
    {
        private TcpClient _tcpClient;
        private string ipAddress = "127.0.0.1";
        private int port = 55555;
        private NetworkStream _clientStream;

        public ClientHandler() 
        {
        }
        public void closeConnection()
        {
            this._clientStream.Close();
        }
        public bool connectServer()
        {
            _tcpClient = new TcpClient();
            // IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Any, port); when the server is on subnet
            IPEndPoint serverEndPoint = new IPEndPoint(IPAddress.Parse(ipAddress), port);
            try
            {
                _tcpClient.Connect(serverEndPoint);
            }
            catch (Exception ex)
            {
                return false;
            }
            _clientStream = _tcpClient.GetStream();
            return true;
        }
        public void sendMsg(string msg)
        {
            byte[] buffer = new ASCIIEncoding().GetBytes(msg);
            //sending msg
            _clientStream.Write(buffer, 0, buffer.Length);
            _clientStream.Flush();
        }
        public string receiveMsg()
        {
            byte[] buffer = new byte[4096];
            int bytesRead = _clientStream.Read(buffer, 0, 4096);
            return Encoding.ASCII.GetString(buffer);
        }
        public void handleClient()
        {
            string msgToSend = "";
            string msgToRecive = "";
            while(msgToSend != "exit")
            {
                //get the msg form the gui somehow? msg now treat as the json
                sendMsg(msgToSend);

                msgToRecive = receiveMsg();
                JsonForamt jsonForamt = JsonConvert.DeserializeObject<JsonForamt>(msgToRecive);
                if (jsonForamt.status == "1") 
                {
                    //set next gui screen to next level
                }
                else if(jsonForamt.status != "")
                {

                }
                else if(jsonForamt.message != "")
                {
                    //display the error msg to the gui
                }

            }
        }
    }
}
