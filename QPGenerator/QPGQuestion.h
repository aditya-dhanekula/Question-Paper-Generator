#pragma once
#include <string>
using namespace std;
enum class QuestionSortType {
    MarksChapterDifficultyQuestion,
    ChapterMarksDifficultyQuestion,
    ChapterQuestionMarksDifficulty,
    QuestionChapterMarksDifficulty,
    DifficultyMarksChapterQuestion
};

class QPGQuestion
{
private:
    static int counter;//incremental for each obj and assign ques id
    int questionId;
    string chapterName;
    string questionDescription;
    string key;
    int marks;
    int difficultyLevel;
 public:
    static void printHeader();
    static string saveHeader();//format to save in .csv file
    static QuestionSortType SortType;
    
    QPGQuestion(string cName, string questionDesc, string solution, int mrks, int difficulty);
    QPGQuestion(string record);//splitting line from csv file
    QPGQuestion(QPGQuestion* question);

    bool operator <(const QPGQuestion& Spec);
    bool operator >=(const QPGQuestion& Spec);

    void setquestionId(int QuestionId);
    int getquestionId();
    void setchapterName(string s);
    string getchapterName();
    void setquestionDescription(string s);
    string getquestionDescription();
    void setkey(string s);
    string getkey();
    void setdifficultyLevel(int s);
    int getdifficultyLevel();
    void setmarks(int s);
    int getmarks();
    void toString();
    string toStringForSave();
 };

