//Deborah Kirchner
//CS201 
//dkkbd@mail.umkc.edu
//Program 3

#include <iostream>
#include <string>
#include <algorithm>
#include <iomanip>
#include <ios>
using namespace std;

int GetYear();
//Takes no parameters. Prompts user for year, then checks that the year is within the acceptable range. 
//When an acceptable year is entered, it returns the year.

int GetStartDayNumber();
//Takes no parameters. Prompts user for the day that January 1 of the year starts on, checks to see whether it is
//a valid day of the week. When an acceptable day is entered, it returns a number corresponding to the day.

int DaysPerMonth(int MonthNumber, int Year);
//Takes parameters year and number of the current month. Returns the number of days in the current month, taking 
//into account leap years.

void PrintOneMonth(int MonthNumber, int MonthDays, int Year, int StartDayNumber);
//Takes parameters year, days in the month, number of the current month, and a number corresponding to the starting
//day of the month. Prints a calendar for the month.

int main() {
	//gets the year and the start day of the year from the user
	int year = GetYear();
	int startDayNum = GetStartDayNumber();

	//for each month of the year, a calendar is printed
	for (int i = 1; i <= 12; i++) {
		int monthDays = DaysPerMonth(i, year);
		PrintOneMonth(i, monthDays, year, startDayNum);
		//figures out the starting day of the next month
		startDayNum += monthDays - 28;
		if (startDayNum >= 7) {
			startDayNum -= 7;
		}
		cout << endl;
	}
	system("pause");
	return 0;
}

int GetYear() {
	int year;
	cout << "Enter year (must be in range 1000 <= Year <= 9999) : " << endl;
	cin >> year;
	//prompts user again if the year that they entered is invalid
	while ((year < 1000) || (year > 9999)) {
		cout << "Invalid year, try again (must be in range 1000 <= Year <= 9999) : " << endl;
		cin >> year;
	}
	return year;
}

int GetStartDayNumber() {
	bool validInput = false;
	string startDay;
	int startDayNum;
	//array containing the valid days of the week in lowercase
	string weekDays[7] = { "sunday", "monday", "tuesday", "wednesday", "thursday", "friday", "saturday" };

	//asks for the first day of the week for the year until user gives valid input
	while (validInput == false) {
		cout << "What day of the week does Jan 1 fall on this year? " << endl;
		cin >> startDay;
		//transforms string to lowercase: code found at 
		//https://www.geeksforgeeks.org/conversion-whole-string-uppercase-lowercase-using-stl-c/
		std::transform(startDay.begin(), startDay.end(), startDay.begin(), ::tolower);
		//searches array of valid days of the week for a match for the user's input
		//breaks out of the loop as soon as a match is found, and assigns the start day to the index of the match in the array
		for (int i = 0; i < 7; i++) {
			if (weekDays[i] == startDay) {
				startDayNum = i;
				validInput = true;
				break;
			}
		}
		//if the user's input is not found in the array, an error message is given and the loop continues
		if (validInput == false) {
			cout << "Invalid input, please try again" << endl;
		}
	}
	return startDayNum;
}

int DaysPerMonth(int MonthNumber, int Year) {
	int daysInMonth;

	//switch statement to determine the days in each month (1 is January, 12 is December)
	switch (MonthNumber) {
		//Jan, Mar, May, July, Aug, Oct, and Dec all have 31 days
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			daysInMonth = 31;
			break;
		//Apr, June, Sept, and Nov all have 30 days
		case 4:
		case 6:
		case 9:
		case 11:
			daysInMonth = 30;
			break;
		//if the current year is not divisible by 4, Feb has 28 days
		//if the current year is divisible by 4 but not 100, Feb has 29 days
		//if the current year is divisible by 100 but not 400, Feb has 28 days
		//if the current year is divisible by 400, Feb has 29 days
		case 2:
			if (Year % 4 == 0) {
				if (Year % 100 == 0) {
					if (Year % 400 == 0) {
						daysInMonth = 29;
					}
					else {
						daysInMonth = 28;
					}
				}
				else {
					daysInMonth = 29;
				}
			}
			else {
				daysInMonth = 28;
			}
			break;
	}
	return daysInMonth;
}

void PrintOneMonth(int MonthNumber, int MonthDays, int Year, int StartDayNumber) {
	//array of the months of the year
	string months[12] = { "JANUARY", "FEBRUARY", "MARCH", "APRIL", "MAY", "JUNE", 
		"JULY", "AUGUST", "SEPTEMBER", "OCTOBER", "NOVEMBER", "DECEMBER" };
	//Prints the current month and year name, centered at the top of the calendar
	cout << setw(35) << right << months[MonthNumber - 1] << " " << Year << endl;
	//array of the days of the week
	string weekDays[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
	//prints each day of the week in the line directly after the month and year
	for (int i = 0; i < 7; i++) {
		cout << setw(10) << left << weekDays[i];
	}
	cout << endl;

	//calculates the number of rows needed for the month's calendar
	int rows;
	if ((StartDayNumber + MonthDays) % 7 == 0) {
		rows = (StartDayNumber + MonthDays) / 7;
	}
	else {
		rows = ((StartDayNumber + MonthDays) / 7) + 1;
	}

	int currNumber = 1;
	//prints any necessary blank days before the numbers start
	for (int i = 0; i < StartDayNumber; i++) {
		cout << setw(10) << left << "";
	}

	//prints the remaining days on the first row of the calendar
	for (int j = StartDayNumber; j < 7; j++) {
		cout << setw(10) << left << currNumber;
		currNumber += 1;
	}
	cout << endl;

	//prints the remaining rows of the calendar, printing days only if they are not larger than the number of
	//days in that month
	for (int k = 1; k < rows; k++) {
		for (int m = 0; m < 7; m++) {
			if (currNumber <= MonthDays) {
				cout << setw(10) << left << currNumber;
				currNumber += 1;
			}
		}
		cout << endl;
	}

}