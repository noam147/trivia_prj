using System;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Collections.Generic;
namespace JsonDeserialzierHelper
{
    static class JsonDeserializerHelper
    {
        public enum DeserializeMessageCode
        {
            ERROR_CODE = 49,
            LOGIN_CODE,
            SIGNUP_CODE,
            LOGOUT_CODE,
            JOIN_ROOM_CODE,
            GET_ROOM_CODE,
            GET_PLAYER_IN_ROOM_CODE,
            CREATE_ROOM_CODE_SUCCSESS,
            GET_HIGH_SCORE_CODE,
            GET_PERSONAL_STAT_CODE,
            GET_ADD_QUESTION_CODE,
            CLOSE_ROOM_CODE,//60
            GET_ADMIN_START_GAME_CODE,
            GET_ROOM_STATE_CODE,
            GET_LEAVE_ROOM_CODE,
            GET_GAME_RESULT_CODE,
            SUBMIT_ANSWER_CODE,//65
            GET_QUESTION_CODE,
            LEAVE_ROOM_CODE,
            GET_SERVER_ANSWER_TO_ADMIN_START_GAME_REQUEST_SUCSEES,
            GET_SERVER_ANSWER_TO_ADMIN_LEAVE_GAME_REQUEST_SUCSEES,
            EMAIL_SUCCSEES_CODE,

            //
            //
            //GET_ROOM_STATE_CODE,
            // LEAVE_ROOM_CODE,
            //,
            //,
            //,
            //LEAVE_GAME_CODE
        }
        public struct regularMsgData
        {
            public int status;
        }
        public struct RoomData {//change to see admin and players in room 
             public List<string> Rooms { get; set; }
        }
        public struct PersonData
        {
            public List<string> Users { get; set; }
        }
        public struct userDetails
        {
            public string username { get; set; }
            public string score { get; set; }
        }
        public struct HighscoreData
        {
            public List<Dictionary<string, string>> HighScores { get; set; }
            //public List<string> HighScores { get; set; }
        }
        public struct StatData
        {
            public List<string> UserStatistics { get; set; }
        }
        public struct RoomState
        {
            public int status { get; set; }
            public bool hasGameBegun { get; set; }
            public List<string> players { get; set; }
            public int AnswerCount { get; set; }
            public int answerTimeOut { get; set; }
        }
        public struct Question
        {
            public int status { get; set; }
            public string question { get; set; }
            public List<string> answers { get; set; }
        }
        public struct SubmitAnswerResponse
        {
            public bool hasUserAnswerRight { get; set; }
        }
        public struct playerResult
        {
            public string username {  get; set; }
            public int correctAnswerCount { get; set; }
            public int wrongAnswerCount { get; set;}
            public float averageAnswerTime { get; set; }
            public int sumPoints { get; set; }
        }
        public struct gameResult
        {
            public List<playerResult> results { get; set; }
        }

    }
}
