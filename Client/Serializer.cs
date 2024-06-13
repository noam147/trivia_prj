using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using JsonSerialzierHelper;
using Newtonsoft.Json;
//using static ConsoleApp1Check.Program;

namespace clientGuiTrivia
{
    public static class Serializer
    {
        // login related serializations
        public static string serialize(loginMessageFields lmf) {
            string msg = JsonConvert.SerializeObject(lmf, Formatting.Indented);
            addLength(ref msg);
            msg = ((char)SerializeMessageCode.LOGIN_CODE) + msg;
            Console.WriteLine("login message: " + msg);
            return msg;
        }
        public static string serialize(banPlayerMessageFields lmf)
        {
            string msg = JsonConvert.SerializeObject(lmf, Formatting.Indented);
            addLength(ref msg);
            msg = ((char)SerializeMessageCode.GET_BAN_PLAYER_CODE) + msg;
            Console.WriteLine("ban player message: " + msg);
            return msg;
        }
        public static string serialize(signupMessageFields smf)
        {
            string msg = JsonConvert.SerializeObject(smf, Formatting.Indented);
            addLength(ref msg);
            msg = ((char)SerializeMessageCode.SIGNUP_CODE) + msg;
            Console.WriteLine("signup message: " + msg);
            return msg;
        }
        public static string serialize(kickPlayerMessageFields kmf)
        {
            string msg = JsonConvert.SerializeObject(kmf, Formatting.Indented);
            addLength(ref msg);
            msg = ((char)SerializeMessageCode.GET_KICK_PLAYER_CODE) + msg;
            Console.WriteLine("kick player message: " + msg);
            return msg;
        }
        public static string serialize(logoutMessageFields lmf)
        {
            string msg = JsonConvert.SerializeObject(lmf, Formatting.Indented);
            addLength(ref msg);
            msg = ((char)SerializeMessageCode.LOGOUT_CODE) + msg;
            Console.WriteLine("logout message: " + msg);
            return msg;
        }

        public static string serialize(getPlayersInRoomMessageFields gpmf)
        {
            string msg = JsonConvert.SerializeObject(gpmf, Formatting.Indented);
            addLength(ref msg);
            msg = (SerializeMessageCode.GET_PLAYER_IN_ROOM_CODE) + msg;
            Console.WriteLine("getPlayers message: " + msg);
            return msg;
        }

        public static string serialize(getRoomsMessageFields grmf)
        {
            string msg = JsonConvert.SerializeObject(grmf, Formatting.Indented);
            addLength(ref msg);
            msg = ((char)SerializeMessageCode.GET_ROOM_CODE) + msg;
            Console.WriteLine("getRoom message: " + msg);
            return msg;
        }

        public static string serialize(joinRoomMessageFields jrmf)
        {
            string msg = JsonConvert.SerializeObject(jrmf, Formatting.Indented);
            addLength(ref msg);
            msg = ((char)SerializeMessageCode.JOIN_ROOM_CODE) + msg;
            Console.WriteLine("joinRoom message: " + msg);
            return msg;
        }

        public static string serialize(CreateRoomMessageFields crmf)
        {
            string msg = JsonConvert.SerializeObject(crmf, Formatting.Indented);
            addLength(ref msg);
            msg = ((char)SerializeMessageCode.GET_CREATE_ROOM_CODE) + msg;
            Console.WriteLine("CreateRoom message: " + msg);
            return msg;
        }

        public static string serialize(getHighScoreMessageFields ghsmf)
        {
            string msg = JsonConvert.SerializeObject(ghsmf, Formatting.Indented);
            addLength(ref msg);
            msg = ((char)SerializeMessageCode.GET_HIGH_SCORE_CODE) + msg;
            Console.WriteLine("GetHighScore Message: " + msg);
            return msg;
        }
        public static string serialize(getStatsMessageFields gsmf)
        {
            string msg = JsonConvert.SerializeObject(gsmf, Formatting.Indented);
            addLength(ref msg);
            msg = ((char)SerializeMessageCode.GET_PERSONAL_STAT_CODE) + msg;
            Console.WriteLine("GetStats Message: " + msg);
            return msg;
        }

        public static string serialize(addNewQuestionsMessageFields gsmf)
        {
            string msg = JsonConvert.SerializeObject(gsmf, Formatting.Indented);
            addLength(ref msg);
            msg = ((char)SerializeMessageCode.GET_ADD_QUESTION_CODE) + msg;
            Console.WriteLine("addNewQuestionsMessageFields Message: " + msg);
            return msg;
        }
        public static string serialize(SendAnswerMessageFields gsmf)
        {
            string msg = JsonConvert.SerializeObject(gsmf, Formatting.Indented);
            addLength(ref msg);
            msg = ((char)SerializeMessageCode.SUBMIT_ANSWER_CODE) + msg;
            Console.WriteLine("SendAnswerMessageFields Message: " + msg);
            return msg;
        }
        public static string serialize(char ch)//when we just need a code msg
        {
            string msg = "{}";
            addLength(ref msg);
            msg = ch + msg;
            //Console.WriteLine("Message: " + msg);
            return msg;
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
            /*byte[] lengthBytes = BitConverter.GetBytes(length);
            char[] lengthChars = new char[sizeof(int)];
            for (int i = 0; i < sizeof(int); i++)
            {
                lengthChars[i] = (char)lengthBytes[i];
            }*/
            //Array.Reverse(lengthChars);
            msg = str + msg;
        }
        }
}
