#include <sstream>  
#include "QPGQuestion.h"
#include <iostream>
#include<iomanip>
int QPGQuestion::counter;
//by default sort type
//again not writing static
QuestionSortType QPGQuestion::SortType = QuestionSortType::ChapterQuestionMarksDifficulty;

    //Setter
    void QPGQuestion::setquestionId(int QuestionId) {
        questionId = QuestionId;
    }
    // Getter
    int QPGQuestion::getquestionId() {
        return questionId;
    }

    // Setter
    void QPGQuestion::setchapterName(string s) {
        chapterName = s;
    }
    // Getter
    string QPGQuestion::getchapterName() {
        return chapterName;
    }

    // Setter
    void QPGQuestion::setquestionDescription(string s) {
        questionDescription = s;
    }
    // Getter
    string QPGQuestion::getquestionDescription() {
        return questionDescription;
    }

    // Setter
    void QPGQuestion::setkey(string s) {
        key = s;
    }
    // Getter
    string QPGQuestion::getkey() {
        return key;
    }

    // Setter
    void QPGQuestion::setmarks(int s) {
        marks = s;
    }
    // Getter
    int QPGQuestion::getmarks() {
        return marks;
    }

    // Setter
    void QPGQuestion::setdifficultyLevel(int s) {
        difficultyLevel = s;
    }
    // Getter
    int QPGQuestion::getdifficultyLevel() {
        return difficultyLevel;
    }

    QPGQuestion::QPGQuestion(string cName, string questionDesc, string solution, int mrks, int difficulty) {
        questionId = ++counter;
        chapterName = cName;
        questionDescription = questionDesc;
        key = solution;
        marks = mrks;
        difficultyLevel = difficulty;
    }

    QPGQuestion::QPGQuestion(string record) {
            string temp;
            stringstream ss(record);
            questionId = ++counter;//each quesn gets a new number
            //getline reads string including spaces. comma is the splitter.
            getline(ss, chapterName, ',');
            getline(ss, questionDescription, ',');
            getline(ss, key, ',');
            getline(ss, temp, ',');
            marks = stoi(temp);//string to integer conversion stoi
            getline(ss, temp, ',');
            difficultyLevel = stoi(temp);
    }

    QPGQuestion::QPGQuestion(QPGQuestion* question) {
        chapterName = question->chapterName;
        questionDescription = question->questionDescription;
        key = question->key;
        marks = question->marks;
        difficultyLevel = question->difficultyLevel;
    }

    bool QPGQuestion::operator <(const QPGQuestion& question) {
        switch (SortType) {
        case QuestionSortType::ChapterMarksDifficultyQuestion:
            return (_stricmp(chapterName.c_str(), question.chapterName.c_str()) < 0
                || (_stricmp(chapterName.c_str(), question.chapterName.c_str()) == 0 && marks < question.marks)
                || (_stricmp(chapterName.c_str(), question.chapterName.c_str()) == 0 && marks == question.marks && difficultyLevel < question.difficultyLevel)
                || (_stricmp(chapterName.c_str(), question.chapterName.c_str()) == 0 && marks == question.marks
                    && difficultyLevel == question.difficultyLevel && _stricmp(questionDescription.c_str(), question.questionDescription.c_str()) < 0));
            break;
        case QuestionSortType::ChapterQuestionMarksDifficulty:
            return (_stricmp(chapterName.c_str(), question.chapterName.c_str()) < 0
                || (_stricmp(chapterName.c_str(), question.chapterName.c_str()) == 0
                    && _stricmp(questionDescription.c_str(), question.questionDescription.c_str()) < 0)
                || (_stricmp(chapterName.c_str(), question.chapterName.c_str()) == 0
                    && _stricmp(questionDescription.c_str(), question.questionDescription.c_str()) == 0 && marks < question.marks)
                || (_stricmp(chapterName.c_str(), question.chapterName.c_str()) == 0
                    && _stricmp(questionDescription.c_str(), question.questionDescription.c_str()) == 0 && marks == question.marks
                    && difficultyLevel < question.difficultyLevel));
            break;
        case QuestionSortType::DifficultyMarksChapterQuestion:
            return(difficultyLevel < question.difficultyLevel || (difficultyLevel == question.difficultyLevel && marks < question.marks)
                || (difficultyLevel == question.difficultyLevel && marks == question.marks
                    && _stricmp(chapterName.c_str(), question.chapterName.c_str()) < 0)
                || (difficultyLevel == question.difficultyLevel && marks == question.marks
                    && _stricmp(chapterName.c_str(), question.chapterName.c_str()) == 0
                    && _stricmp(questionDescription.c_str(), question.questionDescription.c_str()) < 0));
            break;
        case QuestionSortType::MarksChapterDifficultyQuestion:
            return (marks < question.marks || (marks == question.marks && _stricmp(chapterName.c_str(), question.chapterName.c_str()) < 0)
                || (marks == question.marks && _stricmp(chapterName.c_str(), question.chapterName.c_str()) == 0 && difficultyLevel < question.difficultyLevel)
                || (marks == question.marks && _stricmp(chapterName.c_str(), question.chapterName.c_str()) == 0
                    && difficultyLevel == question.difficultyLevel && _stricmp(questionDescription.c_str(), question.questionDescription.c_str()) < 0));
            break;
        case QuestionSortType::QuestionChapterMarksDifficulty:
            return (_stricmp(questionDescription.c_str(), question.questionDescription.c_str()) < 0
                || (_stricmp(questionDescription.c_str(), question.questionDescription.c_str()) == 0 
                    && _stricmp(chapterName.c_str(), question.chapterName.c_str()) < 0)
                || (_stricmp(questionDescription.c_str(), question.questionDescription.c_str()) == 0
                    && _stricmp(chapterName.c_str(), question.chapterName.c_str()) == 0
                    && marks < question.marks)
                || (_stricmp(questionDescription.c_str(), question.questionDescription.c_str()) == 0
                    && _stricmp(chapterName.c_str(), question.chapterName.c_str()) == 0
                    && marks == question.marks
                    && difficultyLevel < question.difficultyLevel));
            break;
        default:
            cout << "Error: Unknown Sort Type" << endl;
            break;
        }
        return false;
    }
    
    bool QPGQuestion::operator >=(const QPGQuestion& Spec) {
        return !(*this < Spec);
    }

    string QPGQuestion::saveHeader() {
        return string("Chapter, Question Description, Key, Marks, Diffculty Level");
    }

    void QPGQuestion::printHeader() {
        switch (SortType) {
        case QuestionSortType::ChapterMarksDifficultyQuestion:
            cout << setfill(' ') << left << setw(15) << "Question Id" <<
                setfill(' ') << left << setw(30) << "Chapter" <<
                setfill(' ') << left << setw(10) << "Marks" <<
                setfill(' ') << left << setw(20) << "Diffculty Level" <<
                setfill(' ') << left << setw(80) << "Question Description" <<
                setfill(' ') << left << setw(50) << "Key" << endl;
            break;
        case QuestionSortType::ChapterQuestionMarksDifficulty:
            /*sortedHeader = "Question Id, Chapter, Question Description, Key, Marks, Diffculty Level";*/
            cout << setfill(' ') << left << setw(15) << "Question Id" <<
                setfill(' ') << left << setw(30) << "Chapter" <<
                setfill(' ') << left << setw(80) << "Question Description" <<
                setfill(' ') << left << setw(50) << "Key" <<
                setfill(' ') << left << setw(10) << "Marks" <<
                setfill(' ') << left << setw(20) << "Diffculty Level" << endl;
                
                 
            break;
        case QuestionSortType::DifficultyMarksChapterQuestion:
            /*sortedHeader = "Question Id, Diffculty Level, Marks, Chapter, Question Description, Key";*/
            cout << setfill(' ') << left << setw(15) << "Question Id" <<
                setfill(' ') << left << setw(20) << "Diffculty Level" <<
                setfill(' ') << left << setw(10) << "Marks" <<
                setfill(' ') << left << setw(30) << "Chapter" <<
                setfill(' ') << left << setw(80) << "Question Description" <<
                setfill(' ') << left << setw(50) << "Key" << endl;
            break;
        case QuestionSortType::MarksChapterDifficultyQuestion:
            /*sortedHeader = "Question Id, Marks, Chapter, Diffculty Level, Question Description, Key";*/
            cout << setfill(' ') << left << setw(15) << "Question Id" <<
                setfill(' ') << left << setw(10) << "Marks" <<
                setfill(' ') << left << setw(30) << "Chapter" <<
                
                setfill(' ') << left << setw(20) << "Diffculty Level" <<
                setfill(' ') << left << setw(80) << "Question Description" <<
                setfill(' ') << left << setw(50) << "Key" << endl;
            break;
        case QuestionSortType::QuestionChapterMarksDifficulty:
            /*sortedHeader = "Question Id, Question Description, Key, Chapter, Marks, Diffculty Level";*/
            cout << setfill(' ') << left << setw(15) << "Question Id" <<
                setfill(' ') << left << setw(80) << "Question Description" <<
                setfill(' ') << left << setw(50) << "Key" <<
                setfill(' ') << left << setw(30) << "Chapter" <<
                setfill(' ') << left << setw(10) << "Marks" <<
                setfill(' ') << left << setw(20) << "Diffculty Level" << endl;
                 
            break;
        }
        return;
    }

    void QPGQuestion::toString() {
        switch (SortType) {
        case QuestionSortType::ChapterMarksDifficultyQuestion:
            //record = to_string(questionId) + ", " + chapterName + ", " + to_string(marks) + ", " + to_string(difficultyLevel) + ", " + questionDescription + "," + key;

            cout << setfill(' ') << left << setw(15) << to_string(questionId) <<
                setfill(' ') << left << setw(30) << chapterName <<
                setfill(' ') << left << setw(10) << to_string(marks) <<
                setfill(' ') << left << setw(20) << to_string(difficultyLevel) <<
                setfill(' ') << left << setw(80) << questionDescription <<
                setfill(' ') << left << setw(50) << key << endl;
            break;
        case QuestionSortType::ChapterQuestionMarksDifficulty:
            /*sortedHeader = "Question Id, Chapter, Question Description, Key, Marks, Diffculty Level";*/
            cout << setfill(' ') << left << setw(15) << to_string(questionId) <<
                setfill(' ') << left << setw(30) << chapterName <<
                setfill(' ') << left << setw(80) << questionDescription <<
                setfill(' ') << left << setw(50) << key <<
                setfill(' ') << left << setw(10) << to_string(marks) <<
                setfill(' ') << left << setw(20) << to_string(difficultyLevel) << endl;


            break;
        case QuestionSortType::DifficultyMarksChapterQuestion:
            /*sortedHeader = "Question Id, Diffculty Level, Marks, Chapter, Question Description, Key";*/
            cout << setfill(' ') << left << setw(15) << to_string(questionId) <<
                setfill(' ') << left << setw(20) << to_string(difficultyLevel) <<
                setfill(' ') << left << setw(10) << to_string(marks) <<
                setfill(' ') << left << setw(30) << chapterName <<
                setfill(' ') << left << setw(80) << questionDescription <<
                setfill(' ') << left << setw(50) << key  << endl;
            break;
        case QuestionSortType::MarksChapterDifficultyQuestion:
            /*sortedHeader = "Question Id, Marks, Chapter, Diffculty Level, Question Description, Key";*/
            cout << setfill(' ') << left << setw(15) << to_string(questionId) <<
                setfill(' ') << left << setw(10) << to_string(marks) <<
                setfill(' ') << left << setw(30) << chapterName <<

                setfill(' ') << left << setw(20) << to_string(difficultyLevel) <<
                setfill(' ') << left << setw(80) << questionDescription <<
                setfill(' ') << left << setw(50) << key << endl;
            break;
        case QuestionSortType::QuestionChapterMarksDifficulty:
            /*sortedHeader = "Question Id, Question Description, Key, Chapter, Marks, Diffculty Level";*/
            cout << setfill(' ') << left << setw(15) << to_string(questionId) <<
                setfill(' ') << left << setw(80) << questionDescription <<
                setfill(' ') << left << setw(50) << key <<
                setfill(' ') << left << setw(30) << chapterName <<
                setfill(' ') << left << setw(10) << to_string(marks) <<
                setfill(' ') << left << setw(20) << to_string(difficultyLevel) << endl;

            break;
        }
        return;
    }
    //to save to file
    string QPGQuestion::toStringForSave() {
        string record = string(chapterName + "," + questionDescription + "," + key + "," + to_string(marks) + "," + to_string(difficultyLevel) );
        return record;
    }