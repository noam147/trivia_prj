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
            char msgCode = msg[0];
            msg = msg.Substring(1);

            AesEncryption.Encrypt(ref msg);
            addLength(ref msg);
            msg = msgCode + msg;
            byte[] buffer = Encoding.UTF8.GetBytes(msg);

            _clientStream.Write(buffer, 0, buffer.Length);
            _clientStream.Flush();
        }

        public static void addLength(ref string msg)
        {
            int length = msg.Length;

            string str = "0000";
            char[] charArray = str.ToCharArray();
            charArray[3] = (char)(length % 127);

            charArray[3] = (char)(length % 127);
            length /= 127;
            charArray[2] = (char)(length % 127);
            length /= 127;
            charArray[1] = (char)(length % 127);
            length /= 127;
            charArray[0] = (char)(length % 127);
            str = new string(charArray);
            msg = str + msg;
        }

        public string receiveMsg()
        {
            byte[] code = new byte[1];
            int bytesRead = _clientStream.Read(code, 0, 1);
            byte[] lengthBuffer = new byte[4];
            bytesRead = _clientStream.Read(lengthBuffer, 0, 4);
            if (BitConverter.IsLittleEndian)
                Array.Reverse(lengthBuffer);
            int length = BitConverter.ToInt32(lengthBuffer, 0);
            byte[] buffer = new byte[length];
            bytesRead = _clientStream.Read(buffer, 0, length);
            _clientStream.Flush();
            string strBuffer = Encoding.UTF8.GetString(buffer);
            string msg = AesEncryption.Decrypt(strBuffer);
            msg = Encoding.UTF8.GetString(code) + length.ToString().PadLeft(4, '0') + msg;
            return msg;
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
