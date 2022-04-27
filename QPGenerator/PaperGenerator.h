#pragma once
#include "QPGList.h"
#include "QPGPatternSpecification.h"
#include "QPGQuestion.h"
class PaperGenerator
{
private:
	QPGList<QPGPatternSpecification>* qPattern;
	QPGList<QPGQuestion> questionPaper;//this is the list of final quesns that we will display in paper
	int generatedPaperTotalMarks;
	string instituteName;
	string logourl;
	string examSubject;
	string examName;
	string examDuration;


	void generateQuestionPaper();
	void saveQuestionPaper(bool withKey);

public:
	PaperGenerator();
	int manage(QPGList<QPGPatternSpecification>* pattern);
};

