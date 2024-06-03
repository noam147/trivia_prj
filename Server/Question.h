#pragma once
#include <string>
#include <vector>
using std::string;
class Question
{
public:
	Question(string question, std::vector<string> possibleAnswers,int indexCorrectAnswer);//
	string getQuestion();
	std::vector<string> getPossibleAnswers();
	int getCorrectAnswerId();
private:
	string m_question;
	std::vector<string> m_possibleAnswers;
	int _indexCorrect;
};