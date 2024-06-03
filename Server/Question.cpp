#include "Question.h"


Question::Question(string question, std::vector<string> possibleAnswers, int idCorrectAnswer)
{
    this->m_question = question;
    this->m_possibleAnswers = possibleAnswers;
    this->_indexCorrect = idCorrectAnswer;
}

string Question::getQuestion()
{
    return this->m_question;
}

std::vector<string> Question::getPossibleAnswers()
{
    return this->m_possibleAnswers;
}

int Question::getCorrectAnswerId()
{
    return _indexCorrect;
}
