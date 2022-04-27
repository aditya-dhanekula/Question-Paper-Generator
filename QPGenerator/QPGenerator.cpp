// QPGenerator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "QuestionBankManager.h"
#include "PaperPattern.h"
#include "PaperGenerator.h"
#include <Windows.h>
using namespace std;
int main()
{
    QuestionBankManager qBankManager;
    PaperPattern pPattern;
    PaperGenerator pGenerator;
    cout << string(100, '\n');
    cout << "********************************************************\n";
    cout << "****   WELCOME TO THE QUESTION PAPER GENERATOR  ********\n";
    cout << "********************************************************\n";
    int nSelectedOption = -1;
    while (nSelectedOption != 0) {
        if (nSelectedOption != -1) {
            cout << string(100, '\n');
        }
        cout << "\n         ********  MAIN MENU **********";
        cout << "\n           1   Manage Question Bank";
        cout << "\n           2   Manage Paper Pattern";
        cout << "\n           3   Generate Question Paper";
        cout << "\n           0   Exit \n";
        cout << "\n Select the option:";
        cin >> nSelectedOption;
        switch (nSelectedOption) {
        case 0:
            break;
        case 1:
             nSelectedOption = qBankManager.manage();
            break;
        case 2:
            nSelectedOption = pPattern.manage(qBankManager.getQuestionBank());
            break;
        case 3:
            nSelectedOption = pGenerator.manage(pPattern.getSpecifications());
            break;
        default:
            cout << "Invalid input!! Enter any Key to continue" << endl;
            cin.sync(); cin.ignore(); cin.get();  
            break;

        }
    }
    cout << "      THANK YOU";
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
