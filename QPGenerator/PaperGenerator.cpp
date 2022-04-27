#include "PaperGenerator.h"
#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <Windows.h>
using namespace std;
PaperGenerator::PaperGenerator() {
    qPattern = NULL;
    generatedPaperTotalMarks = 0;
}

int PaperGenerator::manage(QPGList<QPGPatternSpecification>* pattern) {
    //Question Bank empty check
    if (pattern == NULL) {
        cout << endl << "Question Bank is empty. First create Question Bank";
        cout << endl << "Enter any Key to proceed";
        cin.sync(); cin.ignore(); cin.get();
        return 9;
    }
    qPattern = pattern;
    int nTotalMarksSet = 0;
    QPGPatternSpecification* specification = qPattern->getFirst();
    while (specification != NULL) {
        nTotalMarksSet += (specification->getmarks() * specification->getnoOfQuestions());
        specification = qPattern->getNext();
    }

    if (nTotalMarksSet == 0) {
        cout << endl << "Paper Pattern is not set!! Set the Paper Pattern to generate the Paper" << endl;
        cout << "Enter any Key to continue: ";
        cin.sync(); cin.ignore(); cin.get();
        return 9;
    }
    int nSelectedOption = -1;
    while (nSelectedOption != 0 && nSelectedOption != 9) {
        cout << string(100, '\n');
        cout << "        ********  MANAGE GENERATE QUESTION PAPER **********";
        cout << "\n\n         **********   MENU  **********";
        cout << "\n           1   Generate Question Paper";
        cout << "\n           2   Save Question Paper with Key";
        cout << "\n           3   Save Question Paper without Key";
        cout << "\n           9   Return To Previous Menu";
        cout << "\n           0   Exit \n";
        cout << "\n    Pattern set for Total Marks: " << nTotalMarksSet << endl;
        cout << "\n Select the option:";
        cin >> nSelectedOption;
        switch (nSelectedOption) {
        case 0:
            break;
        case 1:
            generateQuestionPaper();
            break;
        case 2:
            saveQuestionPaper(true);
            break;
        case 3:
            saveQuestionPaper(false);
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

void PaperGenerator::generateQuestionPaper() {
    /*if (!questionPaper.isEmpty()) {
        cout << "Current Question paper will be lost to generate New paper." << endl;
        cout << "Enter 1 to proceed. Entering any other Number will skip new generation";
        int response = 0;
        cin >> response;
        if (response != 1) {
            return;
        }
    }*/

    //Accept extra inputs to be shown in Header, Paper Name, Subject etc and save them in class level provate variables
    cout << endl << "Enter Institution Name: ";
    getline(cin >> ws, instituteName);
    cout << endl << "Enter Institution Logo URL: ";
    getline(cin >> ws, logourl);
    cout << endl << "Enter Examination Name: ";
    getline(cin >> ws, examName);
    cout << endl << "Enter subject: ";
    getline(cin >> ws, examSubject);
    cout << endl << "Enter Examination Duration in words: ";
    getline(cin >> ws, examDuration);
    //clear previously generated Quesiotn if any
    questionPaper.removeAll();
    //reset Randomizer to generate different random numbers
    srand((unsigned)time(NULL));
    //navigate through the pattern for all specifications 
    QPGPatternSpecification* specification = qPattern->getFirst();
    while (specification != NULL) {
        //If questions set for paper in the current specification
        if (specification->getnoOfQuestions() > 0) {
            //create an boolean array with size of Questions of the specification to mark random selected ones
            int nQuestionsInBank = specification->getquestionsInQBank();
            bool* nOptedNumbers = new bool[nQuestionsInBank];
            //initialize with false
            for (int ctr = 0; ctr < nQuestionsInBank; ctr++) {
                nOptedNumbers[ctr] = false;
            }

            int nSelectedCount = 0;
            int nQuestionesOpted = specification->getnoOfQuestions();
            //selecting the random questions from the specification questions
            while (nSelectedCount < nQuestionesOpted) {
                int randomNumber = rand() % nQuestionsInBank;
                if (nOptedNumbers[randomNumber] == false) {
                    nOptedNumbers[randomNumber] = true;
                    nSelectedCount++;
                }
            }
            //adding selected questions to Question Paper object
            QPGQuestion* question = specification->getquestions()->getFirst();
            for (int ctr = 0; ctr < nQuestionsInBank && question != NULL; ctr++, question = specification->getquestions()->getNext()) {
                if (nOptedNumbers[ctr] == true) {
                    questionPaper.add(question);
                }
            }

            delete[] nOptedNumbers;
        }
        specification = qPattern->getNext();
    }
    QuestionSortType currentSort = QPGQuestion::SortType;
    
        QPGQuestion::SortType = QuestionSortType::MarksChapterDifficultyQuestion;
        questionPaper.sort();
        QPGQuestion::SortType = currentSort;
        int ctr = 1;
        generatedPaperTotalMarks = 0;
        for (QPGQuestion* question = questionPaper.getFirst(); question != NULL; question = questionPaper.getNext()) {
            question->setquestionId(ctr++);
            generatedPaperTotalMarks += question->getmarks();
        }
    
    cout << "Paper Generated Successfully. Enter any Key to Continue: ";
    cin.sync(); cin.get();
}

void PaperGenerator::saveQuestionPaper(bool withKey) {
    QPGQuestion* question;
    if (questionPaper.isEmpty()) {
        cout << "Question Paper Not created" << endl;
    }
    else {
        string fileName = "";
        cout << "Enter the file name to Save Question Paper:";
        cin >> fileName;
        fileName += ".html";
        ofstream wfile;
        wfile.open(fileName);
        if (!wfile.is_open()) {
            cout << "Failed to open the file to write" << endl;
            return;
        }
        else {
            wfile << "<!DOCTYPE html>\n <html lang = \"en\"> \n <head> \n <meta charset = \"UTF-8\"> \n <meta http - equiv = \"X-UA-Compatible\" content = \"IE=edge\">";
            wfile << "\n <meta name = \"viewport\" content = \"width=device-width, initial-scale=1.0\"> \n <title>Exam Paper</title>" << endl;
            wfile<<"<link rel='stylesheet' href='https://cdn.jsdelivr.net/npm/bootstrap@4.1.3/dist/css/bootstrap.min.css' integrity='sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO' crossorigin='anonymous'>"<<endl;
            wfile << "<style>" << endl;
            wfile<<"*{margin : 0; padding:0; }"<<endl<<"body{max-width:100%;margin:5%;}"<<endl<<".center{display:block;margin-left:auto;margin-right:auto;}" << endl;
            wfile << "img{ transform: scale(0.5); vertical-align:bottom; } "<< endl;
            wfile << "hr{position: relative;top: 20px; border: none;height: 12px;background: black;margin - bottom: 50px;}" << endl;
            wfile << "table{font-size: 1.0 em;}</style>" << endl;
     
            wfile << "</head>";
            wfile << "<body> <img src = \'" << logourl << "' class = 'center'>" << endl;
            wfile << "<h1 style = \"text-align:center;\">" << instituteName << "</h1>" << endl;
            wfile << "<h2 style = \"text-align:center;text-decoration: underline;\"> "<<examSubject <<"</h2> \n <br><br>\n " << endl;
            wfile << "<h2 style = \"text-align:center;text-decoration: underline;\">" << examName << "</h2 > <br><br> <div style = \"clear: both;\"> <h2 style = \"float: left;\">Exam Duration: " << examDuration;
            wfile << "<h2 style = \"float: right;\">Max Marks = " << generatedPaperTotalMarks << "</h2></div> <br><br> <hr/>" << endl;
            wfile << "<table class='table table-borderless'>" << endl;
            wfile << "<thead><tr><th style='width:6%;' scope='col'></th><th style='width:84%;' scope='col'></th><th scope='col' style='width:10%;'></th>" << endl;
            wfile << "</tr> </thead ><tbody>" << endl;
            
            int ctr = 1;
            question = questionPaper.getFirst();
            while (question != NULL) {
                    wfile << "<tr><td scope='row'>Q " << ctr++ << "</td>" << endl;
                    wfile << "<td style='text-align:left;overflow-wrap:break-word;'>" << question->getquestionDescription() << "</td>" << endl;
                    wfile << "<td >(" << to_string(question->getmarks()) << " Marks) </td>" << endl;
                    if (withKey) {
                        wfile << "</tr><td></td><td style='text-align:left;overflow-wrap:break-word;'><b>Key: </b>" << question->getkey() << "</td>" << endl;
                    }
                    wfile << "</tr>" << endl;
                    question = questionPaper.getNext();
            }
            wfile << "</tbody></table> </body></html>" << endl;
                
        }
        wfile.close();
        ShellExecuteA(NULL, "open", fileName.c_str(), NULL, NULL, SW_SHOWNORMAL);
        cout << "Question Paper Saved to file. Press any Key to continue :";
        cin.sync(); cin.ignore(); cin.get();
    }

}