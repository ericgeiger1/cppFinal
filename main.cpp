// Name: Eric Geiger
// Course: COSC - 1436 - 21004
// Date: 3/9/2026
/* Purpose: This program is a personal expense and budget 
   calculator that allows users to enter their expenses, display
   a summary of those expenses, and save the summary to a text file.
   The program uses an array to store the expenses and includes functions
   for each of the main features: entering expenses, displaying the summary,
   and saving the summary to a file. The user interacts with 
   the program through a simple menu system.
 */

// https://github.com/ericgeiger1/cppFinal

// I planned, then wrote. And then planned more with Github Copilot, then wrote more. I tested the code as I went along,
// asking copilot for help as needed with possible improvements, and modified it as needed.

#include <iostream>
#include <fstream>
#include <limits>
#include <iomanip>
using namespace std;
// Added consts to make the code more readable and maintainable. 
// I also added input validation to ensure that the user enters valid choices and expense counts
const int MAX_EXPENSES = 20;
const int ENTER_EXPENSES = 1;
const int DISPLAY_SUMMARY = 2;
const int SAVE_SUMMARY = 3;
const int QUIT = 4;
// Function prototypes for the functions used in the program.
void showMenu();
int enterExpenses(double expenses[], int maxSize);
void displaySummary(const double expenses[], int count);
void saveSummary(const double expenses[], int count);

// The program allows the user to enter expenses, display a summary of the expenses, and save the summary to a text file.
int main() {
// Declare an array to store expenses and a variable to keep track of the number of expenses entered.
    double expenses[MAX_EXPENSES];
    int expenseCount = 0;
    int choice;

    do {
        showMenu();
        cin >> choice;

        while (choice < ENTER_EXPENSES || choice > QUIT) {
            cout << "Please enter a valid choice." << endl;
            cin >> choice;
        }

        if (choice == ENTER_EXPENSES) {
            expenseCount = enterExpenses(expenses, MAX_EXPENSES);
        }
        else if (choice == DISPLAY_SUMMARY) {
            displaySummary(expenses, expenseCount);
        }
        else if (choice == SAVE_SUMMARY) {
            saveSummary(expenses, expenseCount);
        }

    } while (choice != QUIT);

    return 0;
}
// The show menu function displays the main menu options to the user.
void showMenu() {
    cout << "Personal Expense & Budget Calculator" << endl;
    cout << "---------------------------------------" << endl;
    cout << "1. Enter Expenses" << endl;
    cout << "2. Display Summary" << endl;
    cout << "3. Save Summary" << endl;
    cout << "4. Quit" << endl;
    cout << "Enter your choice: ";
}
// The enter expenses function prompts the user to enter the number of expenses they want to input, 
//and then allows them to enter each expense. It returns the count of expenses entered.
int enterExpenses(double expenses[], int maxSize) {
    int count;

    cout << "How many expenses would you like to enter? (1-20) ";
    cin >> count;

    while (count < 1 || count > maxSize) {
        cout << "Please enter a number between 1 and " << maxSize << ": ";
        cin >> count;
    }

    for (int index = 0; index < count; index++) {
        cout << "Enter expense " << (index + 1) << ": ";
        cin >> expenses[index];
    }

    return count;
}

// The display summary includes the total expenses, average expense, highest expense, and lowest expense.
void displaySummary(const double expenses[], int count) {
    if (count == 0) {
        cout << "No expenses have been entered yet." << endl << endl;
        return;
    }

    double total = 0.0;  //initialize total to 0.0.
    double highest = expenses[0]; //initialize highest to the first expense in the array.
    double lowest = expenses[0]; //initialize lowest to the first expense in the array.

    for (int index = 0; index < count; index++) { //loop through the expenses and calculate the total, highest, and lowest expenses.
        total += expenses[index];

        if (expenses[index] > highest) { //if the current expense is greater than the current highest, update highest to the current expense.
            highest = expenses[index];
        }

        if (expenses[index] < lowest) { //if the current expense is less than the current lowest, update lowest to the current expense.
            lowest = expenses[index];
        }
    }

    double average = total / count;
// Display the summary with two decimal places using fixed and setprecision manipulators from the iomanip library.
    cout << fixed << setprecision(2);
    cout << endl;
    cout << "Expense Summary" << endl;
    cout << "-----------------" << endl;
    cout << "Total expenses: $" << total << endl;
    cout << "Average expense: $" << average << endl;
    cout << "Highest expense: $" << highest << endl;
    cout << "Lowest expense: $" << lowest << endl;
}
// The save summary function saves the same summary information to a text file named "expenses.txt". 
//It uses ofstream to write to the file and includes error handling to ensure the file is opened successfully.
void saveSummary(const double expenses[], int count) {
    if (count == 0) {
        cout << "No expenses have been entered yet." << endl << endl;
        ;
        return;
    }

    double total = 0.0;
    double highest = expenses[0];
    double lowest = expenses[0];
// Loop through the expenses to calculate the total, highest, and lowest expenses.
    for (int index = 0; index < count; index++) {
        total += expenses[index];

        if (expenses[index] > highest) { //if the current expense is greater than the current highest, update highest to the current expense.
            highest = expenses[index];
        }

        if (expenses[index] < lowest) { //if the current expense is less than the current lowest, update lowest to the current expense.
            lowest = expenses[index];
        }
    }

    double average = total / count;

    ofstream outputFile("expenses.txt");
// Check if the file was opened successfully before writing to it.
    if (!outputFile) {
        cout << "Unable to open expenses.txt for writing." << endl;
        return;
    }
// Write the summary to the file with two decimal places using fixed and setprecision manipulators from the iomanip library.
    outputFile << fixed << setprecision(2);
    outputFile << "Expense Summary" << endl;
    outputFile << "Total expenses: $" << total << endl;
    outputFile << "Average expense: $" << average << endl;
    outputFile << "Highest expense: $" << highest << endl;
    outputFile << "Lowest expense: $" << lowest << endl;
// Close the file after writing to it.
    outputFile.close();
    cout << "Summary saved to expenses.txt" << endl;
}
