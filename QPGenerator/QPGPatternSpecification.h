#pragma once
#include <string>
#include "QPGList.h"
#include "QPGQuestion.h"
enum class SpecificationSortType {
    MarksChapterDifficulty,
    MarksDifficultyChapter,
    ChapterMarksDifficulty,
    ChapterDifficultyMarks,
    DifficultyChapterMarks,
    DifficultyMarksChapter
};
class QPGPatternSpecification {
private:
    static int counter;
    int specificationId;
    int marks;
    string chapterName;
    int difficultyLevel;
    int questionsInQBank;//total num of quesn avlbl with this spec
    int noOfQuestions;//what user enters -- no of ques he wants

    QPGList<QPGQuestion> questions;//list of address of objects of quesns availbl in bank for this particular spec

public:
    static SpecificationSortType SortType;
    static string saveHeader();
    static void printHeader();
    void setSpecificationId(int Id);
    int getspecificationId();
    int getmarks();

    string getchapterName();
    int getdifficultyLevel();
    int getquestionsInQBank();
    void setnoOfQuestions(int n);
    int getnoOfQuestions();

    bool operator <(const QPGPatternSpecification& Spec);
    bool operator >=(const QPGPatternSpecification& Spec);

    QPGList<QPGQuestion>* getquestions();
    void addQuestion(QPGQuestion* question);
    QPGPatternSpecification(QPGQuestion* question);
    QPGPatternSpecification(QPGPatternSpecification* spec);
    static void resetQuestionNo();
    string toStringForSave();
    void toString();
};