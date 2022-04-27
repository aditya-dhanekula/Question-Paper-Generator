#include "QuestionBankManager.h"
#include "QPGQuestion.h"
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
//#include <iomanip>
using namespace std;
int QuestionBankManager::manage() {
    int nSelectedOption = -1;
    while (nSelectedOption != 0 && nSelectedOption != 9) {
        cout << string(100, '\n');
        cout << "   ********  MANAGE QUESTION BANK  **********";
        cout << "\n\n         ****************  MENU  **********";
        cout << "\n           1   Load From File";
        cout << "\n           2   Save To File";
        cout << "\n           3   Add Question";
        cout << "\n           4   List Questions";
        cout << "\n           5   Sort Questions";
        cout << "\n           6   Search Questions";
        cout << "\n           9   Return To Previous Menu";
        cout << "\n           0   Exit \n";
        cout << "\n Select the option:";
        cin >> nSelectedOption;
        switch (nSelectedOption) {
        case 0:
            break;
        case 1:
            loadFromFile();
            break;
        case 2:
            saveToFile();
            break;
        case 3:
            addQuestion();
            break;
        case 4:
            listQuestions();
            break;
        case 5:
            sortQuestions();
            break;
        case 6:
            nSelectedOption = searchQuestion();
            break;
        case 9:
            break;
        default:
            cout << "\n\nInvalid entry, enter again!!\n\n";
            break;
        }
    }
    return nSelectedOption;
}

QPGList<QPGQuestion>* QuestionBankManager::getQuestionBank() {
    return &qBank;
}

int QuestionBankManager::loadFromFile() { 

    string filename = "", line ="";
    cout << "Enter the file Name to Load file :";
    cin >> filename;
    ifstream inputFile{ filename };

    if (!inputFile.is_open()) {
        cerr << "Couldn't read file: " << filename << "\n";
        return 1;
    }
    //Skip Column Names Row;
    if (inputFile)
        getline(inputFile, line);
    try {
        qBank.removeAll();
        while (inputFile) {
            getline(inputFile, line);
            if (line.compare("") != 0 ) {
                QPGQuestion* question = new QPGQuestion(line);//creating question object
                qBank.add(question);
                addChapterIfNew(question->getchapterName());
            }
        }
        inputFile.close();
    }
    catch (exception ex) {
        cout << "error while reading the file:" << ex.what() << endl;
    }
    qBank.sort();
    resetQuestionNumbers();
    listQuestions();
    return 1; 
}

int QuestionBankManager::saveToFile() { 
    QPGQuestion* question;
    if (qBank.isEmpty()) {
        cout << "No Questions added to the Question Bank" << endl;
    }
    else {
        string fileName = "";
        cout << "Enter the file name to Save Question Bank:";
        cin >> fileName;
        fileName += ".csv";
        ofstream wfile;
        wfile.open(fileName);
        if (!wfile.is_open()) {
            cout << "Failed to open the file to write" << endl;
            return 1;
        }
        else {
            wfile << QPGQuestion::saveHeader() << endl;
            question = qBank.getFirst();
            while (question != NULL) {
                wfile << question->toStringForSave() << endl;
                question = qBank.getNext();
            }
        }
        wfile.close();
        cout << "Question Bank Saved to file. Press any Key to continue :";
        cin.sync(); cin.ignore(); cin.get();  
    }
    return 1; 
}

//List the chapters available and allow user to select the chapter 
//or allow adding a new Chapter Name
string QuestionBankManager::getChapterFromUser() 
{
    string chapterName ="";
    if (!chapters.isEmpty()) {
        int nselectedOption = -1;
        QPGChapter* chapter = chapters.getFirst();
        cout << endl << "Chapter No\t\t\t Chapter Name" << endl;
        while (chapter != NULL) {
            cout << chapter->getChapterId() << "\t\t\t\t" << chapter->getChapterName() << endl;
            chapter = chapters.getNext();
        }
        cout << "0\t\t\t To Enter Chapter Name" << endl;
        cout << endl << "Enter the Chapter No: ";
        while (nselectedOption < 0) {
            cin >> nselectedOption;
            if (nselectedOption > 0) {
                chapterName = getChapterName(nselectedOption);
                if (chapterName.empty()) {
                    cout << endl << "Invalid input!! Enter the Chapter No from above List:";
                    nselectedOption = -1;
                }
                else {
                    return chapterName;
                }
            }
        }
    }
    cout << endl << "Enter Chapter Name :";
    getline(cin >> ws, chapterName);
    addChapterIfNew(chapterName);
    return chapterName;
}
// Start of Questions Management 
int QuestionBankManager::addQuestion() {
    string pQuestionDesc;
    string pKey;
    string pChapter;
    int pMarks;
    int pQLevel;
    cout << "\n Enter Question Description: ";
    getline(cin >> ws, pQuestionDesc);
    cout << "\n Enter Key: ";
    getline(cin >> ws, pKey);
    pChapter = getChapterFromUser();
    cout << "\n Enter Marks: ";
    cin >> pMarks;
    cout << "\n Enter diffculty Level: ";
    cin >> pQLevel;
    QPGQuestion *question = new QPGQuestion(pChapter,pQuestionDesc, pKey, pMarks, pQLevel);
    qBank.add(question);
    addChapterIfNew(pChapter);
    qBank.sort();
    resetQuestionNumbers();
    return 1; 
}

int QuestionBankManager::listQuestions(){
    QPGQuestion* question;
    if (qBank.isEmpty()) {
        cout << "No Questions added to the Question Bank \n";
    }
    else{
        question = qBank.getFirst();
        QPGQuestion::printHeader();
        while (question != NULL) {
            question->toString();
            question = qBank.getNext();
        }
        cout << "\n\nEnter any key to continue: ";
        cin.sync(); cin.ignore(); cin.get();  
    }  
    return 1;
}

int QuestionBankManager::sortQuestions() {
    int nSelectedOption = -1;
    while (nSelectedOption != 0 && nSelectedOption != 9) {
        cout << string(100, '\n');
        cout << "\n        **********   SORT OPTIONS  **********";
        cout << "\n\n         **********   MENU  **********";
        cout << "\n           1   Chapter - Question - Marks - Difficulty Level";
        cout << "\n           2   Question - Chapter - Marks - Difficulty Level";
        cout << "\n           3   Marks - Chapter - Difficulty Level - Question";
        cout << "\n           4   Chapter - Marks - Difficulty Level - Question";
        cout << "\n           5   Difficulty Level - Marks - Chapter - Question";
        cout << "\n           9   Return To Previous Menu";
        cout << "\n           0   Exit" << endl;
        cout << "\n Select the option:";
        cin >> nSelectedOption;
        switch (nSelectedOption) {
        case 0:
            break;
        case 1:
            QPGQuestion::SortType = QuestionSortType::ChapterQuestionMarksDifficulty;
            break;
        case 2:
            QPGQuestion::SortType = QuestionSortType::QuestionChapterMarksDifficulty;
            break;
        case 3:
            QPGQuestion::SortType = QuestionSortType::MarksChapterDifficultyQuestion;
            break;
        case 4:
            QPGQuestion::SortType = QuestionSortType::ChapterMarksDifficultyQuestion;
            break;
        case 5:
            QPGQuestion::SortType = QuestionSortType::DifficultyMarksChapterQuestion;
            break;
        case 9:
            break;
        default:
            cout << "Invalid entry, enter any Key to continue!!";
            cin.sync(); cin.ignore(); cin.get();
            break;
        }
        if (nSelectedOption > 0 && nSelectedOption <= 6) {
            nSelectedOption = 9;
            qBank.sort();
            resetQuestionNumbers();
            cout << endl << "Questions are Sorted in the given order." << endl;
            cout << "Enter any Key to continue!!";
            cin.sync(); cin.ignore(); cin.get();
        }
    }
    return nSelectedOption;
}

int QuestionBankManager::searchQuestion() {
    QPGQuestion* question;
    int nSelectedOption = -1;
    if (qBank.isEmpty()) {
        cout << "No Questions added to the Question Bank \n";
        cout << "\n Enter any key to continue: ";
        cin.sync(); cin.ignore(); cin.get();  
    }
    else {
        string strsearchString = "";
        int nFoundCount = 0;
        while (strsearchString.empty()) {
            //Show message and accept String to search in question description into the above variable
            cout << "\n Enter the Keyword to search in the Question Bank: ";
            getline(cin >> ws,strsearchString);
        }
        //Search the questions with above text in question bank and if found, print them
        question = qBank.getFirst();
        while (question != NULL) {
            if (question->getquestionDescription().find(strsearchString) != string::npos) {
                if (nFoundCount == 0) {
                    QPGQuestion::printHeader();
                }
                question->toString();
                nFoundCount++;
            }
            question = qBank.getNext();
        }
        if (nFoundCount == 0) {
            //if No questions found with given Keyword, show proper message, accept input after reading and then return
            cout << "No questions found with the given Keyword\n ";
            cout << "\n Enter any key to continue: ";
            cin.sync(); cin.ignore(); cin.get();  
        }
        else {
            int qId = 0;
            //show message to enter question no to edit or delete and accept the question no into a variable
            cout << "\n 0 to go back to previous menu" << endl << endl;
            cout << "Enter Question Id : ";
            cin >> qId;
            if (qId > 0) {
                //Search for the question with the Question Id and when found current will remain at the selected question
                question = qBank.getFirst();
                while (question != NULL && question->getquestionId() != qId) {
                    question = qBank.getNext();
                }
                //When given Question is not found, show message and return
                if (question == NULL) {
                    cout << "Given Question No not found!!!\n";
                    cout << "\n Enter any key to continue: ";
                    cin.sync(); cin.ignore(); cin.get();  
                }
                else {
                    cout << endl<< "Question Management Menu \n";
                    cout << "1         Edit\n";
                    cout << "2         Delete\n";
                    cout << "9         Back to Previous Menu\n";
                    cout << "0         Exit\n\n";
                    while (nSelectedOption != 0 && nSelectedOption != 1 && nSelectedOption != 2 && nSelectedOption != 9) {
                        cout << "\n Select the option: ";
                        cin >> nSelectedOption;
                        switch (nSelectedOption)
                        {
                        case 0:
                            break;
                        case 1:
                            return editQuestion();
                            break;
                        case 2:
                            deleteQuestion();
                            nSelectedOption = 9;
                            break;
                        case 9:
                            break;
                        default:
                            cout << "Entered option is invalid \n\n";
                            break;
                        }
                    }
                    
                }
            }

        }
    }
    return nSelectedOption;

}

int QuestionBankManager::editQuestion() { 
        //what field u want to edit
        int nSelectedOption = -1;
        QPGQuestion* question = qBank.getCurrent();
        while (nSelectedOption != 0 && nSelectedOption != 9) {
            cout << endl << string(100, '\n');
            cout << "   ********  EDIT QUESTION   **********" << endl;
            QPGQuestion::printHeader();
            question->toString();
            cout << "\n\n         ****************  MENU  **********";
            cout << "\n           1   Edit Question Description";
            cout << "\n           2   Edit Key";
            cout << "\n           3   Edit Chapter";
            cout << "\n           4   Edit Marks";
            cout << "\n           5   Edit Diffculty Level";
            cout << "\n           9   Return to Previous Menu";
            cout << "\n           0   Exit \n";
            cout << "\n Select the option:";
            cin >> nSelectedOption;
            switch (nSelectedOption) {
            case 0:
                break;
            case 1:
                changeQuestionDesc();
                break;
            case 2:
                changeKey();
                break;
            case 3:
                changeChapterName(); 
                break;
            case 4:
                changeMarks();
                break;
            case 5:
                changeDiffLevel();
                break;
            case 9:
                qBank.sort();
                resetQuestionNumbers();
                break;
            default:
                cout << "\n\nInvalid entry, enter again!!\n\n";
                break;
            }
        }
        return nSelectedOption;
    }

int QuestionBankManager::deleteQuestion() {
    string chapterName = qBank.getCurrent()->getchapterName();
    qBank.remove();
    removeChapterIfNoQuestionsAssociated(chapterName);
    qBank.sort();
    resetQuestionNumbers();
    return 1;
}

void QuestionBankManager::resetQuestionNumbers() {
    int ctr = 1;
    for (QPGQuestion* question = qBank.getFirst(); question != NULL; question = qBank.getNext()) {
        question->setquestionId(ctr++);
    }
}

void QuestionBankManager::changeQuestionDesc() {
    //change quesn desc
    cout << "Question Description is: " << qBank.getCurrent()->getquestionDescription() << endl;
    string newQuesnDesc;
    cout << "Enter new Question Description: ";
    getline(cin >> ws, newQuesnDesc);
    qBank.getCurrent()->setquestionDescription(newQuesnDesc);
    cout << "Entered Question Description is saved:" << endl;
    cout << "Enter any key to continue: ";
    cin.sync(); cin.ignore(); cin.get();  
}

void QuestionBankManager::changeKey() {
    //edit key
    cout << "Current Answer Key is: " << qBank.getCurrent()->getkey() << endl;
    string newKey;
    cout << "Enter new Answer Key :";
    getline(cin >> ws, newKey);
    qBank.getCurrent()->setkey(newKey);
    cout << "Entered Answer Key is saved:" << endl;
    cout << "Enter any key to continue: ";
    cin.sync(); cin.ignore(); cin.get();  
}

void QuestionBankManager::changeChapterName() {
    //change chapter name
    string chapterName = qBank.getCurrent()->getchapterName();
    cout << "Chapter name is: " << chapterName << endl;
    string newChapterName = getChapterFromUser();
    qBank.getCurrent()->setchapterName(newChapterName);
    removeChapterIfNoQuestionsAssociated(chapterName);
    cout << "Chapter Name saved." << endl;
    cout << "Enter any key to continue: ";
    cin.sync(); cin.ignore(); cin.get();  
}

void QuestionBankManager::changeMarks() {
    //edit marks
    cout << "Current Marks are: " << qBank.getCurrent()->getmarks() << endl;
    int newMarks;
    cout << "Enter new marks :";
    cin >> newMarks;
    qBank.getCurrent()->setmarks(newMarks);
    cout << "Entered marks are saved:" << endl;
    cout << "Enter any key to continue: ";
    cin.sync(); cin.ignore(); cin.get();  
}

void QuestionBankManager::changeDiffLevel() {
    //edit diff Level
    cout << "Current Difficulty level is: " << qBank.getCurrent()->getdifficultyLevel() << endl;
    int newDiffLevel;
    cout << "Enter new Difficulty level :";
    cin >> newDiffLevel;
    qBank.getCurrent()->setdifficultyLevel(newDiffLevel);
    cout << "Difficulty level is saved" << endl;
    cout << "Enter any key to continue: ";
    cin.sync(); cin.ignore(); cin.get();  
}
// End of Questions Management 

//Start Chapters Management

int QuestionBankManager::getChapterNo(string chapterName) {
    QPGChapter* chapter = chapters.getFirst();
    while (chapter != NULL) {
        //compare the given Chapter with chapter collection items Case insensitive and if found return
        if (chapter->getChapterName().compare(chapterName) == 0) {
            return chapter->getChapterId();
        }
        chapter = chapters.getNext();
    }
    return 0;
}

string QuestionBankManager::getChapterName(int chapterId){
    QPGChapter* chapter = chapters.getFirst();
    while (chapter != NULL) {
        //compare the given Chapter Id with chapter collection items Case insensitive and if found return Chapter Name
        if (chapter->getChapterId() == chapterId) {
            return chapter->getChapterName();
        }
        chapter = chapters.getNext();
    }
    //If Chaper Id not found in the  Chapters collection return emptty string 
    return "";
}

bool QuestionBankManager::addChapterIfNew(string chapterName){
//Search for the given Chapter Name in the Chapters collection. If now found then add new one
    QPGChapter* chapter = chapters.getFirst();
    while (chapter != NULL) {
        //compare the given Chapter with chapter collection items Case insensitive and if found return
        if (chapter->getChapterName().compare(chapterName) == 0) {
            return false;
        }
        chapter = chapters.getNext();
    }
    chapters.add(new QPGChapter(chapterName));
    return true;
}

bool QuestionBankManager::removeChapterIfNoQuestionsAssociated(string chapterName){
    //Search in the question bank for the given chapter name 
    QPGQuestion* question = qBank.getFirst();
    while (question != NULL) {
        //If question found with the given chaptername then return
        if (question->getchapterName().compare(chapterName) == 0) {
            return false;
        }
        question = qBank.getNext();
    }

    //remove the given chapter from the Chapter collection
    QPGChapter* chapter = chapters.getFirst();
    while (chapter != NULL) {
        //compare the given Chapter with chapter collection items Case insensitive and if found return
        if (chapter->getChapterName().compare(chapterName) == 0) {
            chapters.remove();
            return true;
        }
        chapter = chapters.getNext();
    }
    return false;
}
//End of Chapters Management




