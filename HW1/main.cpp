/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Title: HW1
// 
// Author: Samuel Garbarino
// 
// Description: Simple program that gives you a table of statistics in csv form based off of the loan amount, interest
// per year, and payment per month.
// 
// 09/11/2024: Created the program
// 
// Input: loan amount, interestper year, and payment per month
// 
// Output: CSV file
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <fstream>

using namespace std;

void inputter(double &inputVal, string name) {
    while (inputVal < 0) {
        cout << "\nPlease enter " << name << " amount here: ";
        cin >> inputVal;

        if(cin.fail()) {
            cout << "\nSubmission was not a valid number, please try again.";
            inputVal = -1;
            cin.clear(); // Resets cin.fail, keeping an endless loop from happening
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clears cin to prevent the same thing
        }
    }
}

int main() {

    // Var Init
    double loanAmount = -1, interestPerYear = -1, payment = -1, interestPaid, debtPaid, fullPay, remainingDebt, interestPerMonth, totalPayment = 0;
    int debtIncrease = 0, month = 0;

    // Grabbing Neccesary User Input
    inputter(loanAmount, "loan");
    inputter(interestPerYear, "interest");
    inputter(payment, "monthly pay");

    interestPerMonth = ((interestPerYear/100)/12);

    // Opening File and Creating Headers
    ofstream amortizationTable("amortization.csv");
    amortizationTable << "Month,Debt,Interest Paid,Debt Paid,Full Pay,Remaining Debt\n";
    amortizationTable << setprecision(2) << fixed;


    // Creating Object for CSV File
    while ((loanAmount > 0) && (debtIncrease != 5)) {
        month++;
        interestPaid = loanAmount * interestPerMonth;
        debtPaid = payment - interestPaid;
        if (interestPaid > loanAmount) {
            interestPaid = loanAmount;
        }
        remainingDebt = loanAmount - debtPaid;
        fullPay = debtPaid + interestPaid;

        if (remainingDebt < 0) {
            remainingDebt = 0;
        }

        amortizationTable << month << ',';
        amortizationTable << loanAmount << ',';
        amortizationTable << interestPaid << ',';
        amortizationTable << debtPaid << ',';
        amortizationTable << fullPay << ',';
        amortizationTable << remainingDebt << ',';
        amortizationTable << "\n";

        if (loanAmount < remainingDebt) {
            debtIncrease = debtIncrease + 1;
        }

        loanAmount = remainingDebt;
        totalPayment = totalPayment + fullPay;
    }
    amortizationTable.close();

    cout << "\nYour total Payment is: " << fullPay;
    cout << "\nSee CSV file for more statistics.";


    cout << "\n\n\nEnd of Program\n";
    return 0;
}