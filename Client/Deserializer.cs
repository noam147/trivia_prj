using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using JsonDeserialzierHelper;
using Newtonsoft.Json;
//using static ConsoleApp1Check.Program;
using static JsonDeserialzierHelper.JsonDeserializerHelper;

namespace clientGuiTrivia
{
    static class Deserializer
    {
        public static RoomState desirializeGetRoomStateResponse(string GetRoomStatusResponse)
        {
            RoomState roomState = new RoomState();
            roomState.status = -2; ;
            if (GetRoomStatusResponse[0] != (char)DeserializeMessageCode.GET_ROOM_STATE_CODE)
            {
                return roomState;
            }
            GetRoomStatusResponse = GetRoomStatusResponse.Substring(5);
            roomState = JsonConvert.DeserializeObject<RoomState>(GetRoomStatusResponse);
            return roomState;
        }
        public static bool desirializeServerAnswerToAdminStartGameRequest(string msgFromServer)//get msg from server to leave room - admin disconnected
        {
            if (msgFromServer[0] != (char)DeserializeMessageCode.GET_ADMIN_START_GAME_CODE)
            {
                return false;
            }
            return true;
        }
        public static bool desirializeServerAnswerToAdminLeaveGameRequest(string msgFromServer)//get msg from server to leave room - admin disconnected
        {
            if (msgFromServer[0] != (char)DeserializeMessageCode.GET_SERVER_ANSWER_TO_ADMIN_LEAVE_GAME_REQUEST_SUCSEES)
            {
                return false;
            }
            return true;
        }
        public static bool desirializeLeaveRoomResponse(string LeaveRoomResponse)//get msg from server to leave room - admin disconnected
        {
            if (LeaveRoomResponse[0] != (char)DeserializeMessageCode.GET_LEAVE_ROOM_CODE)//in to check the codes
            {
                return false;
            }
            return true;
        }
        public static bool desirializeStartGameResponse(string LeaveRoomResponse)//get msg from server - admin started game
        {
            if (LeaveRoomResponse[0] != (char)DeserializeMessageCode.GET_ADMIN_START_GAME_CODE)
            {
                return false;
            }
            return true;
        }
        public static bool desirializeAddQuestionResponse(string AddQuestionResponse)
        {
            if (AddQuestionResponse[0] != (char)DeserializeMessageCode.GET_ADD_QUESTION_CODE)
            {
                return false;
            }
            return true;
        }
        public static bool desirializeLoginResponse(string loginResponse)
        {
            if (loginResponse[0] != (char)DeserializeMessageCode.LOGIN_CODE)
            {  
                return false;
            }
            return true;
        }

        public static bool desirializeSignupResponse(string signupResponse)
        {
            if (signupResponse[0] != (char)DeserializeMessageCode.SIGNUP_CODE)
            {
                return false;
            }
            return true;
        }

        public static bool desirializeLogoutResponse(string logoutResponse)
        {
            if (logoutResponse[0] != (char)DeserializeMessageCode.LOGOUT_CODE)
            {
                return false;
            }
            return true;
        }

        public static bool desirializeJoinRoomResponse(string joinRoomResponse)
        {
            if (joinRoomResponse[0] != (char)DeserializeMessageCode.JOIN_ROOM_CODE)
            {
                return false;
            }
            return true;
        }

        public static bool desirializeCreateRoomResponse(string createRoomResponse)
        {
            if (createRoomResponse[0] != (char)DeserializeMessageCode.CREATE_ROOM_CODE_SUCCSESS)
            {
                return false;
            }
            return true;
        }

        public static Question desirializeGetQuestionResponse(string msg)
        {
            if (msg[0] != (char)DeserializeMessageCode.GET_QUESTION_CODE)
            {
                Question error = new Question();
                error.question = "";
                error.status = -1;
                return error;
            }
            msg = msg.Substring(5);
            Question question = JsonConvert.DeserializeObject<Question>(msg);
            return question;
        }
        public static SubmitAnswerResponse desirializeSubmitAnswerResponse(string msg)
        {
            if (msg[0] != (char)DeserializeMessageCode.SUBMIT_ANSWER_CODE)
            {
                throw new Exception("invalid code msg");  
            }
            msg = msg.Substring(5);
            SubmitAnswerResponse answerResponse = JsonConvert.DeserializeObject<SubmitAnswerResponse>(msg);
            return answerResponse;
        }

        //if the return value is null, it means the message returned was either error or invalid
        public static List<string> desirializeGetRoomsResponse(string getRoomsResponse)
        {
            if (getRoomsResponse[0] != (char)DeserializeMessageCode.GET_ROOM_CODE)
            {
                return null;
            }

            getRoomsResponse = getRoomsResponse.Substring(5);
            RoomData roomList = JsonConvert.DeserializeObject<RoomData>(getRoomsResponse);
            return roomList.Rooms;
        }

        //if the return value is null, it means the message returned was either error or invalid
        public static List<string> desirializeGetPlayersResponse(string getPlayersResponse)
        {
            if (getPlayersResponse[0] != (char)DeserializeMessageCode.GET_PLAYER_IN_ROOM_CODE)
            {
                System.Console.WriteLine("resualt: " + getPlayersResponse[0]);

                return null;
            }

            getPlayersResponse = getPlayersResponse.Substring(5);
            PersonData PlayersList = JsonConvert.DeserializeObject<PersonData>(getPlayersResponse);
            return PlayersList.Users;
        }

        //if the return value is null, it means the message returned was either error or invalid
        public static List<string> desirializeGetStatsResponse(string getStatsResponse)
        {
            if (getStatsResponse[0] != (char)DeserializeMessageCode.GET_PERSONAL_STAT_CODE)
            {
                return null;
            }

            getStatsResponse = getStatsResponse.Substring(5);
            StatData statsList = JsonConvert.DeserializeObject<StatData>(getStatsResponse);
            return statsList.UserStatistics;

        }

        //if the return value is null, it means the message returned was either error or invalid
        public static List<Dictionary<string, string>> desirializeGetHighscoreResponse(string getHighscoreResponse)
        {
            if (getHighscoreResponse[0] != (char)DeserializeMessageCode.GET_HIGH_SCORE_CODE)
            {
                return null;
            }

            getHighscoreResponse = getHighscoreResponse.Substring(5);
            //HighscoreData highscore = JsonConvert.DeserializeObject<HighscoreData>(getHighscoreResponse);
            HighscoreData highscore = JsonConvert.DeserializeObject<HighscoreData>(getHighscoreResponse);
            return highscore.HighScores;
            
        }
    }
}
