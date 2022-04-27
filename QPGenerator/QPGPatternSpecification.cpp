#include "QPGPatternSpecification.h"
#include<iomanip>

SpecificationSortType QPGPatternSpecification::SortType = SpecificationSortType::MarksChapterDifficulty;
int QPGPatternSpecification::counter=0;
void QPGPatternSpecification::resetQuestionNo() {
    counter = 0;
}

void QPGPatternSpecification::setSpecificationId(int Id) {
    specificationId = Id;
}

int QPGPatternSpecification::getspecificationId() {
    return specificationId;
}

int QPGPatternSpecification::getmarks() {
    return marks;
}

string QPGPatternSpecification::getchapterName() {
    return chapterName;
}

int QPGPatternSpecification::getdifficultyLevel() {
    return difficultyLevel;
}

int QPGPatternSpecification::getquestionsInQBank() {
    return questionsInQBank;
}

void QPGPatternSpecification::setnoOfQuestions(int n) {
    noOfQuestions = n;
}
int QPGPatternSpecification::getnoOfQuestions() {
    return noOfQuestions;
}

bool QPGPatternSpecification::operator <(const QPGPatternSpecification& Spec) {
    switch (SortType) {
    case SpecificationSortType::ChapterDifficultyMarks:
        return (_stricmp(chapterName.c_str(), Spec.chapterName.c_str()) < 0 
            || (_stricmp(chapterName.c_str(), Spec.chapterName.c_str()) == 0 && difficultyLevel < Spec.difficultyLevel)
            || (_stricmp(chapterName.c_str(), Spec.chapterName.c_str()) == 0 && difficultyLevel == Spec.difficultyLevel && marks < Spec.marks));
        break;
    case SpecificationSortType::ChapterMarksDifficulty:
        return(_stricmp(chapterName.c_str(), Spec.chapterName.c_str()) < 0
            || (_stricmp(chapterName.c_str(), Spec.chapterName.c_str()) == 0 && marks < Spec.marks)
            || (_stricmp(chapterName.c_str(), Spec.chapterName.c_str()) == 0 && marks == Spec.marks&& difficultyLevel < Spec.difficultyLevel));
        break;
    case SpecificationSortType::DifficultyChapterMarks:
        return (difficultyLevel < Spec.difficultyLevel 
            || (difficultyLevel == Spec.difficultyLevel && _stricmp(chapterName.c_str(), Spec.chapterName.c_str()) < 0)
            || (difficultyLevel == Spec.difficultyLevel && _stricmp(chapterName.c_str(), Spec.chapterName.c_str()) == 0 && marks < Spec.marks));
        break;
    case SpecificationSortType::DifficultyMarksChapter:
        return (difficultyLevel < Spec.difficultyLevel 
            || (difficultyLevel == Spec.difficultyLevel && marks < Spec.marks )
            || (difficultyLevel == Spec.difficultyLevel && marks == Spec.marks && _stricmp(chapterName.c_str(), Spec.chapterName.c_str()) < 0));
        break;
    case SpecificationSortType::MarksChapterDifficulty:
        return ((marks < Spec.marks) 
            || (marks == Spec.marks && _stricmp(chapterName.c_str(), Spec.chapterName.c_str()) < 0)
            || (marks == Spec.marks && _stricmp(chapterName.c_str(), Spec.chapterName.c_str()) == 0 && difficultyLevel < Spec.difficultyLevel));
        break;
    case SpecificationSortType::MarksDifficultyChapter:
        return ((marks < Spec.marks) 
            || (marks == Spec.marks && difficultyLevel < Spec.difficultyLevel)
            || (marks == Spec.marks && difficultyLevel == Spec.difficultyLevel && _stricmp(chapterName.c_str(), Spec.chapterName.c_str()) < 0));
        break;
    default:
        cout << "Error: Unknown Specification Sort Type" << endl;
        break;
    }
    return false;
}

bool QPGPatternSpecification::operator >=(const QPGPatternSpecification& Spec) {
    return !(*this < Spec);
}

void QPGPatternSpecification::addQuestion(QPGQuestion* question) {
    questions.add(question);
    questionsInQBank++;
}

QPGList<QPGQuestion>* QPGPatternSpecification::getquestions() {
    return &questions;
}

QPGPatternSpecification::QPGPatternSpecification(QPGPatternSpecification* spec) {
    marks = spec->marks;
    chapterName = spec->chapterName;
    difficultyLevel = spec->difficultyLevel;
    questionsInQBank = spec->questionsInQBank;
    noOfQuestions = spec->noOfQuestions;
}

QPGPatternSpecification::QPGPatternSpecification(QPGQuestion* question) {
    specificationId = ++counter;
    marks = question->getmarks();
    chapterName = question->getchapterName();
    difficultyLevel = question->getdifficultyLevel();
    questions.add(question);
    questionsInQBank = 1;
    noOfQuestions = 0;
}

string QPGPatternSpecification::saveHeader() {
    string strHeader = "";
    switch (SortType) {
    case SpecificationSortType::ChapterDifficultyMarks:
        strHeader = "Spec No, Chapter Name, Difficulty Level, Marks, Questions In Bank, Questions Set";
        break;
    case SpecificationSortType::ChapterMarksDifficulty:
        strHeader = "Spec No, Chapter Name, Marks, Difficulty Level, Questions In Bank, Questions Set";
        break;
    case SpecificationSortType::DifficultyChapterMarks:
        strHeader = "Spec No, Difficulty Level, Chapter Name, Marks, Questions In Bank, Questions Set";
        break;
    case SpecificationSortType::DifficultyMarksChapter:
        strHeader = "Spec No, Difficulty Level, Marks, Chapter Name, Questions In Bank, Questions Set";
        break;
    case SpecificationSortType::MarksChapterDifficulty:
        strHeader = "Spec No, Marks, Chapter Name, Difficulty Level, Questions In Bank, Questions Set";
        break;
    case SpecificationSortType::MarksDifficultyChapter:
        strHeader = "Spec No, Marks, Difficulty Level, Chapter Name, Questions In Bank, Questions Set";
        break;
    }
    return strHeader;
};

void QPGPatternSpecification::printHeader() {
    switch (SortType) {
    case SpecificationSortType::ChapterDifficultyMarks:
        /*strHeader = "Spec No, Chapter Name, Difficulty Level, Marks, Questions In Bank, Questions Set";*/
        cout << setfill(' ') << left << setw(15) << "Spec No" <<
            setfill(' ') << left << setw(30) << "Chapter" <<
            setfill(' ') << left << setw(25) << "Diffculty Level" <<
            setfill(' ') << left << setw(20) << "Marks" <<
            setfill(' ') << left << setw(22) << "Questions In Bank" <<
            setfill(' ') << left << setw(20) << "Questions Set" << endl;
        break;
    case SpecificationSortType::ChapterMarksDifficulty:
       /* strHeader = "Spec No, Chapter Name, Marks, Difficulty Level, Questions In Bank, Questions Set";*/
        cout << setfill(' ') << left << setw(15) << "Spec No" <<
            setfill(' ') << left << setw(30) << "Chapter" <<
            setfill(' ') << left << setw(20) << "Marks" <<
            setfill(' ') << left << setw(25) << "Diffculty Level" <<
            
            setfill(' ') << left << setw(22) << "Questions In Bank" <<
            setfill(' ') << left << setw(20) << "Questions Set" << endl;
        break;
    case SpecificationSortType::DifficultyChapterMarks:
        /*strHeader = "Spec No, Difficulty Level, Chapter Name, Marks, Questions In Bank, Questions Set";*/
        cout << setfill(' ') << left << setw(15) << "Spec No" <<
            
            setfill(' ') << left << setw(25) << "Diffculty Level" <<
            setfill(' ') << left << setw(30) << "Chapter" <<
            setfill(' ') << left << setw(20) << "Marks" <<
            setfill(' ') << left << setw(22) << "Questions In Bank" <<
            setfill(' ') << left << setw(20) << "Questions Set" << endl;
        break;
    case SpecificationSortType::DifficultyMarksChapter:
        /*strHeader = "Spec No, Difficulty Level, Marks, Chapter Name, Questions In Bank, Questions Set";*/
        cout << setfill(' ') << left << setw(15) << "Spec No" <<
            setfill(' ') << left << setw(25) << "Diffculty Level" <<
           
            
            setfill(' ') << left << setw(20) << "Marks" <<
            setfill(' ') << left << setw(30) << "Chapter" <<
            setfill(' ') << left << setw(22) << "Questions In Bank" <<
            setfill(' ') << left << setw(20) << "Questions Set" << endl;
        break;
    case SpecificationSortType::MarksChapterDifficulty:
        /*strHeader = "Spec No, Marks, Chapter Name, Difficulty Level, Questions In Bank, Questions Set";*/
        cout << setfill(' ') << left << setw(15) << "Spec No" <<
            setfill(' ') << left << setw(20) << "Marks" <<
            
            setfill(' ') << left << setw(30) << "Chapter" <<
            setfill(' ') << left << setw(25) << "Diffculty Level" <<
            setfill(' ') << left << setw(22) << "Questions In Bank" <<
            setfill(' ') << left << setw(20) << "Questions Set" << endl;
        break;
    case SpecificationSortType::MarksDifficultyChapter:
        /*strHeader = "Spec No, Marks, Difficulty Level, Chapter Name, Questions In Bank, Questions Set";*/
        cout << setfill(' ') << left << setw(15) << "Spec No" <<
            setfill(' ') << left << setw(20) << "Marks" <<
            setfill(' ') << left << setw(25) << "Diffculty Level" <<
            setfill(' ') << left << setw(30) << "Chapter" <<
            setfill(' ') << left << setw(22) << "Questions In Bank" <<
            setfill(' ') << left << setw(20) << "Questions Set" << endl;
        break;
    }
    return;
}

string QPGPatternSpecification::toStringForSave() {
    string orderedString = "";
    switch (SortType) {
    case SpecificationSortType::ChapterDifficultyMarks:
        orderedString = chapterName + ", " + to_string(difficultyLevel) + ", " + to_string(marks);
        break;
    case SpecificationSortType::ChapterMarksDifficulty:
        orderedString = chapterName + ", " + to_string(marks) + ", " + to_string(difficultyLevel);
        break;
    case SpecificationSortType::DifficultyChapterMarks:
        orderedString = to_string(difficultyLevel) + ", " + chapterName + ", " + to_string(marks);
        break;
    case SpecificationSortType::DifficultyMarksChapter:
        orderedString = to_string(difficultyLevel) + ", " + to_string(marks)+ ", " + chapterName;
        break;
    case SpecificationSortType::MarksChapterDifficulty:
        orderedString = to_string(marks) + ", " + chapterName + ", " + to_string(difficultyLevel);
        break;
    case SpecificationSortType::MarksDifficultyChapter:
        orderedString = to_string(marks) + ", " + to_string(difficultyLevel) + ", " + chapterName;
        break;
    }
    string record = string(to_string(specificationId) + ", " + orderedString + ", " + to_string(questionsInQBank) + ", " + to_string(noOfQuestions));
    return record;
}

void QPGPatternSpecification::toString() {
    switch (SortType) {
    case SpecificationSortType::ChapterDifficultyMarks:
        /*orderedString = chapterName + ", " + to_string(difficultyLevel) + ", " + to_string(marks);*/
        cout << setfill(' ') << left << setw(15) << to_string(specificationId) << 
            setfill(' ') << left << setw(30) << chapterName<<
            setfill(' ') << left << setw(25) << to_string(difficultyLevel) <<
            setfill(' ') << left << setw(20) << to_string(marks) << setfill(' ') << left << setw(22) << to_string(questionsInQBank) <<
            setfill(' ') << left << setw(20) << to_string(noOfQuestions) << endl;

            
 
        break;
    case SpecificationSortType::ChapterMarksDifficulty:
        /*orderedString = chapterName + ", " + to_string(marks) + ", " + to_string(difficultyLevel);*/
        cout << setfill(' ') << left << setw(15) << to_string(specificationId) << 
            setfill(' ') << left << setw(30) << chapterName <<
            
            setfill(' ') << left << setw(20) << to_string(marks) <<
            setfill(' ') << left << setw(25) << to_string(difficultyLevel) << setfill(' ') << left << setw(22) << to_string(questionsInQBank) <<
            setfill(' ') << left << setw(10) << to_string(noOfQuestions) << endl;
        break;
    case SpecificationSortType::DifficultyChapterMarks:
        /*orderedString = to_string(difficultyLevel) + ", " + chapterName + ", " + to_string(marks);*/
        cout << setfill(' ') << left << setw(15) << to_string(specificationId) <<
            setfill(' ') << left << setw(25) << to_string(difficultyLevel) <<
            setfill(' ') << left << setw(30) << chapterName <<
            
            setfill(' ') << left << setw(20) << to_string(marks) << setfill(' ') << left << setw(22) << to_string(questionsInQBank) <<
            setfill(' ') << left << setw(10) << to_string(noOfQuestions) << endl;
        break;
    case SpecificationSortType::DifficultyMarksChapter:
        /*orderedString = to_string(difficultyLevel) + ", " + to_string(marks) + ", " + chapterName;*/
        cout << setfill(' ') << left << setw(15) << to_string(specificationId) <<
            setfill(' ') << left << setw(25) << to_string(difficultyLevel) <<
            setfill(' ') << left << setw(20) << to_string(marks) <<
            setfill(' ') << left << setw(30) << chapterName << setfill(' ') << left << setw(22) << to_string(questionsInQBank) <<
            setfill(' ') << left << setw(10) << to_string(noOfQuestions) << endl;
            
             
        break;
    case SpecificationSortType::MarksChapterDifficulty:
        /*orderedString = to_string(marks) + ", " + chapterName + ", " + to_string(difficultyLevel);*/
        cout << setfill(' ') << left << setw(15) << to_string(specificationId) <<
            setfill(' ') << left << setw(20) << to_string(marks) <<
            setfill(' ') << left << setw(30) << chapterName <<
            setfill(' ') << left << setw(25) << to_string(difficultyLevel) << setfill(' ') << left << setw(22) << to_string(questionsInQBank) <<
            setfill(' ') << left << setw(10) << to_string(noOfQuestions) << endl;
             
        break;
    case SpecificationSortType::MarksDifficultyChapter:
        /*orderedString = to_string(marks) + ", " + to_string(difficultyLevel) + ", " + chapterName;*/
        cout << setfill(' ') << left << setw(15) << to_string(specificationId) <<
            setfill(' ') << left << setw(20) << to_string(marks) <<
            setfill(' ') << left << setw(25) << to_string(difficultyLevel) <<
            setfill(' ') << left << setw(30) << chapterName <<
            setfill(' ') << left << setw(10) << to_string(questionsInQBank) <<
            setfill(' ') << left << setw(10) << to_string(noOfQuestions) << endl;
            
             
        break;
    }
    /*string record = string(to_string(specificationId) + ", " + orderedString + ", " + to_string(questionsInQBank) + ", " + to_string(noOfQuestions));*/
    return;
}
