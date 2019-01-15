//Asks the user for the principal, the interest rate, and the desired monthly payment and then displays an amortization table
#include <iostream>
#include <iomanip>
using namespace std;

//function main begins program execution

int main() {

//declare and intialize variables

float p = 0;
float ir = 0;
float mp = 0;
int month = 0;
int years = 0;
// Start inputs

cout << "Enter the principal amount: "; 
cin >> p;

	if (p < 0){
		cout << "Invalid principal amount." << endl;
		cout << "Please enter a positive value for principal: "; 
		cin >> p;
	}

cout << "Enter the interest rate (in decimal form): ";
cin >> ir;

	if (ir > 1 || ir < 0) {
		cout << "Invalid interest rate." << endl;
		cout << "Please enter a postive decimal value for interest rate: ";
		cin >> ir;
	}
	
cout << "Enter the desired monthly payment: ";
cin >> mp;

	if (mp < 0) {
		cout << "Invalid monthly payment." << endl;
		cout << "Please enter a positive value for monthly payment: ";
		cin >> mp;
	}

// Calculation Equations

float balance = p;
float paymenttotal = 0;

// Start of amortization table
cout << " ";
cout << left << setw(11) << "Month" << setw(13) << "Payment" << setw(13) << "Interest" << setw(20) << "Balance" << endl;
	while (balance > 0) {
	float interest =((ir*balance)/12);
		if (balance >= mp) {
			balance = (balance + interest - mp);
		}
		else {
		mp = balance + interest;
		balance = 0;
		}
		if (interest >= mp) {
		cout << "It will be impossible to pay off this loan." << endl;
		return 0;
		}
		cout << left << setw(12) << (month =(month+1)) << "$" << setw(12) << fixed << setprecision(2) << mp << "$" << setw(12) << interest << "$" << setw(12) << balance << endl;
		paymenttotal = paymenttotal + mp;
		}
	
		years = month/12;
		month = month - (years*12);
		cout << "You paid a total of $" << paymenttotal << " over " << years << " years and " << month << " months." << endl;
return 0;
}

