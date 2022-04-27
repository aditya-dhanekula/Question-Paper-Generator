#pragma once
#ifndef QUESTIONBANKManager
#define QUESTIONBANKManager

#include <string>
#include <iostream>
#include "QPGList.h"
#include "QPGQuestion.h"
#include "QPGChapter.h"
using namespace std;

class QuestionBankManager
{
private:
	 QPGList<QPGQuestion> qBank;
	 QPGList<QPGChapter> chapters;
	 int loadFromFile();
	 int saveToFile();
	 int addQuestion();
	 int listQuestions();
	 int sortQuestions();
	 int searchQuestion();
	 int editQuestion();
	 int deleteQuestion();
	 void resetQuestionNumbers();
	 string getChapterFromUser();
	 void changeChapterName();
     void changeQuestionDesc();
	 void changeKey();
	 void changeMarks();
     void changeDiffLevel();

	 int getChapterNo(string ChapterName);
	 string getChapterName(int chapterId);
	 bool addChapterIfNew(string chapterName);
	 bool removeChapterIfNoQuestionsAssociated(string chapterName);

public:
	int manage();
	 QPGList<QPGQuestion>* getQuestionBank();
};
#endif
