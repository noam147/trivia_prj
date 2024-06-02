/*
 this file contains the definitions of the messages structure 
 and the message codes for the serialized messages
(the ones sent from the client to the server)
 */


using System.Collections.Generic;

namespace JsonSerialzierHelper
{
    public enum SerializeMessageCode
    {
        LOGIN_CODE = 1,
        SIGNUP_CODE,
        LOGOUT_CODE,
        LOGIN_FAILED,
        SIGNUP_FAILED,
        JOIN_ROOM_CODE,
        GET_ROOM_CODE,
        GET_PLAYER_IN_ROOM_CODE,
        GET_CREATE_ROOM_CODE,
        GET_HIGH_SCORE_CODE,
        GET_PERSONAL_STAT_CODE,
        GET_ADD_QUESTION_CODE,
        GET_ADMIN_CLOSE_ROOM_REQUEST,
        GET_ADMIN_START_GAME_REQUEST,
        GET_ROOM_STATE_CODE,
        GET_LEAVE_ROOM_CODE,
        GET_GET_QUESTION_CODE,
        SUBMIT_ANSWER_CODE,

        //CLOSE_ROOM_CODE,
        //START_GAME_CODE,
        //GET_ROOM_STATE_CODE,
        // LEAVE_ROOM_CODE,
        //GET_GAME_RESULT_CODE,
        //,
        //GET_QUESTION_CODE,
        //LEAVE_GAME_CODE
    }

    // login related structs
    public struct loginMessageFields {
        public string username;
        public string password;
    }

    public struct signupMessageFields
    {
        public string username;
        public string password;
        public string email;
    }

    // menue related structs
    public struct getPlayersInRoomMessageFields
    {
        public int roomId;
    }

    public struct getRoomsMessageFields
    {
        // no data needed
    }

    public struct joinRoomMessageFields
    {
        public string roomName;
    }

    public struct CreateRoomMessageFields
    {
        public  string roomName;
        public int maxUsers;
        public int questionCount;
        public int questionTimeout;
    }
    public struct SendAnswerMessageFields
    {
        public int answerIndex;
        public float answerTime;
    }
    public struct getStatsMessageFields
    {
        // no data needed
        public string username;
    }

    public struct getHighScoreMessageFields
    {
        public string username;
    }

    public struct logoutMessageFields
    {
        // no data needed
    }
    public struct addNewQuestionsMessageFields
    {
        public string question;
        public string rightAnswer;
        public List<string> wrongAnswers;
    }

}
