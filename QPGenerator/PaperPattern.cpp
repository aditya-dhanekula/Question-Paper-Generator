#include "PaperPattern.h"
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;
PaperPattern::PaperPattern() {
    qBank = NULL;

}

int PaperPattern::manage(QPGList<QPGQuestion>* QuestionBank) {
    //Question Bank empty check
    if (QuestionBank == NULL) {
        cout << endl << "Question Bank is empty. First create Question Bank";
        cout << endl << "Enter any Key to proceed";
        cin.sync(); cin.ignore(); cin.get();  
        return 9;
    }

   
    qBank = QuestionBank;
    setPaperPattern();

    int nSelectedOption = -1;
    while (nSelectedOption != 0 && nSelectedOption != 9) {
        cout << string(100, '\n');
        cout << "\n   ********  MANAGE PAPER PATTERN **********";
        cout << "\n\n         **********   MENU  **********";
        cout << "\n           1   Set Specification";
        cout << "\n           2   Sort Specifications";
        cout << "\n           3   List Pattern";
        cout << "\n           4   Save Specifications";
        cout << "\n           5   Save Paper Pattern";
        cout << "\n           6   Reset Paper Pattern";
        cout << "\n           9   Return To Previous Menu";
        cout << "\n           0   Exit \n";
        cout << "\n Select the option:";
        cin >> nSelectedOption;
        switch (nSelectedOption) {
        case 0:
            break;
        case 1:
            setSpecification();
            break;
        case 2:
            sortSpecifications();
            break;
        case 3:
            listPattern();
            break;
        case 4:
            saveSpecifications(false);
            break;
        case 5:
            saveSpecifications(true);
            break;
        case 6:
            setPaperPattern();
            break;
        case 9:
            break;
        default:
            cout << "Invalid entry, enter any Key to continue!!";
            cin.sync(); cin.ignore(); cin.get();  
            break;
        }
    }
    return nSelectedOption;
}

QPGPatternSpecification* PaperPattern::moveToSpecification(int SpecificationId) {
    QPGPatternSpecification* specification = qPattern.getFirst();
    while (specification != NULL && specification->getspecificationId() != SpecificationId) {
        specification = qPattern.getNext();
    }
    return specification;
}

void PaperPattern::addSpecification(QPGQuestion* question) {
    QPGPatternSpecification* specification = new QPGPatternSpecification(question);
    qPattern.add(specification);
}

void PaperPattern::setSpecification(){
    int nSelectedOption = -1;
    int totalMarksSet = 0;
    while (nSelectedOption < 0) {
        totalMarksSet = 0;
        QPGPatternSpecification* specification = qPattern.getFirst();
        /*cout << endl << endl << endl << QPGPatternSpecification::header() << endl;*/
        cout << endl << endl << endl;
        QPGPatternSpecification::printHeader();
        while (specification != NULL) {
            totalMarksSet += (specification->getmarks() * specification->getnoOfQuestions());
            /*cout << specification->toString() << endl;*/
            specification->toString();
            specification = qPattern.getNext();
        }
        cout << "Total Marks set: " << totalMarksSet << endl;
        cout << "0 \t Return to Previous Menu" << endl;
        cout << endl << "Enter the Specification Number to set or Zero to return to Previous Menu: ";
        cin >> nSelectedOption;
        if (nSelectedOption > 0) {
            if (moveToSpecification(nSelectedOption) == NULL) {
                cout << endl << "Entered option is invalid!!" << endl;
                cout << "Enter any key to continue :";
                cin.sync(); cin.ignore(); cin.get();  
            }
            else {
                int NoOfQuestion = -1;
                while (NoOfQuestion < 0) {
                    cout << "Enter Number of questions to set for this specification. Maximum " << qPattern.getCurrent()->getquestionsInQBank() << ": ";
                    cin >> NoOfQuestion;
                    if (NoOfQuestion > qPattern.getCurrent()->getquestionsInQBank()) {
                        cout << endl << "Invalid input!!!Enter any Key to continue :" << endl;
                        cin.sync(); cin.ignore(); cin.get();
                        NoOfQuestion = -1;
                    }
                    else {
                        qPattern.getCurrent()->setnoOfQuestions(NoOfQuestion);
                        cout << "Specification is saved!!" << endl;
                        nSelectedOption = -1;
                    }
                }
            }
        }
    }
}

void PaperPattern::listPattern() {
    int nTotalMarks = 0;
    
    cout << string(100, '\n');
    QPGPatternSpecification::printHeader();
    for (QPGPatternSpecification* specification = qPattern.getFirst(); specification != NULL; specification = qPattern.getNext()) {
        if (specification->getnoOfQuestions() > 0) {
            nTotalMarks += (specification->getmarks() * specification->getnoOfQuestions());
            specification->toString();
        }
    }
    cout << endl << endl << "Paper set for Total Marks " << nTotalMarks << endl;
    cout << "Enter any Key to continue";
    cin.sync(); cin.ignore(); cin.get();  
}
//setQuestionsOnly == true --> set only for this spec
void PaperPattern::saveSpecifications(bool setQuestionsOnly) {
    QPGPatternSpecification* specification;
    if (qBank->isEmpty()) {
        cout << "No Questions added to the Question Bank" << endl;
    }
    else {
        string fileName = "";
        cout << "Enter the file name:";
        cin >> fileName;
        fileName += ".csv";
        ofstream wfile;
        wfile.open(fileName);
        if (!wfile.is_open()) {
            cout << "Failed to open the file to write" << endl;
            return;
        }
        else {
            wfile << QPGPatternSpecification::saveHeader() << endl;
            specification = qPattern.getFirst();
            for (QPGPatternSpecification* specification = qPattern.getFirst(); specification != NULL; specification = qPattern.getNext()) {
                if (!setQuestionsOnly || specification->getnoOfQuestions() > 0) {
                    wfile << specification->toStringForSave() << endl;
                }
            }
        }
        wfile.close();
        cout << "Saved to file. Press any Key to continue :";
        cin.sync(); cin.ignore(); cin.get();
    }
}

//Read all questions from Question Bank and save grouping them by (Chapter, difficulty Level and Marks) with Question as sub item
void PaperPattern::setPaperPattern(){
    //Clear previous paper pattern if any
    qPattern.removeAll();
    //To Start Specification Number from 1 again;
    QPGPatternSpecification::resetQuestionNo();//make counter = 0
    //Navigate to all questions in Question bank
    QPGQuestion* question = qBank->getFirst();
    while (question != NULL) {
        //NAvigate all specicifations in the collection
        QPGPatternSpecification* specification = qPattern.getFirst();
        //for each quesn, we should check all specifications
        while (specification != NULL) {
            //If specification found with the same Chapter, Difficulty Level and Marks of Question, then add question to specification inner question collection
            if (specification->getchapterName().compare(question->getchapterName()) == 0
                && specification->getdifficultyLevel() == question->getdifficultyLevel()
                && specification->getmarks() == question->getmarks()) {

                specification->addQuestion(question);

                break;
            }
            specification = qPattern.getNext();//go to next specification if this spec doesnot match
        }
        //when matching specification not found then create new specification
        if (specification == NULL) {
            specification = new QPGPatternSpecification(question);
            qPattern.add(specification);
        }
        question = qBank->getNext();
    }

    qPattern.sort();
    resetSpecificationNos();
}

int PaperPattern::sortSpecifications() {
    int nSelectedOption = -1;
    while (nSelectedOption != 0 && nSelectedOption != 9) {
        cout << string(100, '\n');
        cout << "\n        **********   SORT OPTIONS  **********";
        cout << "\n\n         **********   MENU  **********";
        cout << "\n           1\t Marks - Chapter - Difficulty Level";
        cout << "\n           2\t Marks - Difficulty Level - Chapter";
        cout << "\n           3\t Chapter - Marks - Difficulty Level";
        cout << "\n           4\t Chapter - Difficulty Level - Marks";
        cout << "\n           5\t Difficulty Level - Chapter - Marks";
        cout << "\n           6\t Difficulty Level - Marks - Chapter";
        cout << "\n           9\t Return To Previous Menu";
        cout << "\n           0\t Exit" << endl;
        cout << "\n Select the option:";
        cin >> nSelectedOption;
        switch (nSelectedOption) {
        case 0:
            break;
        case 1:
            QPGPatternSpecification::SortType= SpecificationSortType::MarksChapterDifficulty;
            break;
        case 2:
            QPGPatternSpecification::SortType = SpecificationSortType::MarksDifficultyChapter;
            break;
        case 3:
            QPGPatternSpecification::SortType = SpecificationSortType::ChapterMarksDifficulty;
            break;
        case 4:
            QPGPatternSpecification::SortType = SpecificationSortType::ChapterDifficultyMarks;
            break;
        case 5:
            QPGPatternSpecification::SortType = SpecificationSortType::DifficultyChapterMarks;
            break;
        case 6:
            QPGPatternSpecification::SortType = SpecificationSortType::DifficultyMarksChapter;
            break;
        case 9:
            break;
        default:
            cout << "Invalid entry, Enter any Key to continue!!";
            cin.sync(); cin.ignore(); cin.get();
            break;
        }
        if (nSelectedOption > 0 && nSelectedOption <= 6) {
            nSelectedOption = 9;
            qPattern.sort();
            resetSpecificationNos();
            cout << endl << "Specification are sorted in the given order." << endl;
            cout << "Enter any Key to continue!!";
            cin.sync(); cin.ignore(); cin.get();
        }
    }
    return nSelectedOption;
}

void PaperPattern::resetSpecificationNos() {
    int ctr = 1;
    for (QPGPatternSpecification* spec = qPattern.getFirst(); spec != NULL; spec = qPattern.getNext()) {
        spec->setSpecificationId(ctr++);
    }
}

QPGList<QPGPatternSpecification>* PaperPattern::getSpecifications() {
    return &qPattern;
}



