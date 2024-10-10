/* This program implements a recreation of the Ubuntu cal command.
 * Frija Reinert
 * freinert@gustavus.edu
 *
 * ooh look a snail!
 *	       \   /
 * 	 @@@@@  \-/
 * 	@@@@@@@ . .|
 *     @@@@@@@@ ___/
 *     @@@@@@@@ KK
 *~~~~~~@@@@@@KKK
 *```````````````
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

#define NUM_MONTHS 12
#define NUM_DAYS 7
#define MONTH_SPACE 20 // the amount of space a month takes up in terminal

const char *months[120] = {"January","February","March","April","May",
	"June","July","August","September","October","November","December"};
const char *week[70] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa", "Su"};
int monthDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

int getMonth();
int getYear();
void printMonth(int m, int y);
void printYear(int y);
int convertMonth(char *m);
int isValidYear(int y, char *sYear);
int firstDayYear(int y);
int firstDayMonth(int m, int y);
int isLeapYear(int y);

int main(int argc, char *argv[]) {
	// no args
	if(argc == 1) {
		printMonth(getMonth(), getYear());
	}
	// just year provided
	else if (argc == 2) {
		int year = atoi(argv[1]);
	       	if(isValidYear(year,argv[1]) == 0) {
			printYear(year);
		}
		else {
			printf("Please enter a year between 1-9999\n");
		}
	}
	// user provided month and used -m
	else if ((strcmp(argv[1], "-m") == 0) && argc >= 3) {
		int month = convertMonth(argv[2]);
		if (month == -1) {
			printf("Invalid month: %s\n",argv[2]);
			return 1;
		}
		// just month
		if (argc == 3) {
			printMonth(month, getYear());
		}
		// month and year
		else if (argc == 4) {
			int year = atoi(argv[3]);
			if (isValidYear(year,argv[3]) == 0) {
				printMonth(month, year);
			}
			else {
				printf("Please enter a year in range 1-9999\n");
			}
		}
	}
	// month provided without -m
	else if (argc == 3) {
		int month = convertMonth(argv[1]);
		int year = atoi(argv[2]);
		if (isValidYear(year,argv[2]) != 0) {
			printf("Please enter a year between 1-9999\n");
		}
		else if (month == -1) {
			printf("Invalid month: %s\n",argv[1]);
		}
		else {
			printMonth(month, year);
		}
	}
	else {
		printf("Usage: cal.c [-m month] [year]\n");
		return 1;
	}
	return 0;
}

/*
 * Determines if m is a valid month
 * @param: char *month, the month in string form
 * @return: int, 0-11 if m is valid
 * @return: int, -1 if m is invalid
 */
int convertMonth(char *month) {
	// check if m is a num
	int digit = 0;
	for (int i = 0; i < strlen(month); i++) {
		if (isdigit(month[i]) == 0){
			digit = 1;
		}
	}
	// if month was provided numerically, check that it is valid
	if (digit == 0) {
		int intMonth = (atoi(month))-1; // subtract 1 for indexing
		// if valid, save month name in m
		if (intMonth <= 11 && intMonth >= 0) {
			return intMonth;
		}
		else {
			return -1;
		}
	}	
	// if month was not provided numerically:
	else {
		int length = strlen(month);
		if (length < 3) {
			return -1;
		}
		char monthCopy[3];
		// fix and save first 3 letters of month 
		for (int i = 0; i < 3; i++) {
			if (i==0) {
				monthCopy[i] = toupper(month[i]);
			}
			else {
				monthCopy[i] = tolower(month[i]);
			}
		}
		// search for first 3 chars of m in months
		for (int i = 0; i < NUM_MONTHS; i++) {
			if (strncmp(monthCopy, months[i], 3) == 0) {
				return i;
			}
		}
	}
	return -1;
}

/*
 * Checks if year is valid (int 1-9999)
 * @param: int year, the year
 * @param: char *sYear, the year in string format
 * @return: int, 0 if valid 
 * @return: int, -1 if invalid
*/
int isValidYear(int year, char *sYear) {
	// check that year is a whole number 
	double dYear;
	sscanf(sYear, "%lf", &dYear);
	if (dYear == year && year >= 1 && year <= 9999) {	
		return 0;
	}
	return 1;
}

/*
 * Prints the inputed month of the inputed year
 * @param: int month
 * @param: int year
 */
void printMonth(int month, int year) {
	int yearSpace = 4;
	// if year is 1-2 digits, halve the spaces required
	if (year < 100) {
		yearSpace = 2;
	}
	int spaces = (MONTH_SPACE - (yearSpace+1) - strlen(months[month])) / 2;
	
	// print month name, centered
	for (int i = 0; i < spaces; i++) {
		printf(" ");
	}
	printf("%s %d\n",months[month],year);
	
	if (month == 1 && isLeapYear(year) == 0) {
		monthDays[month] = 29;
	}

	// print days of week
	for (int i = 0; i < NUM_DAYS; i++) {
		printf("%s ",week[i]);
	}
	printf("\n");

	// now for the #s
	int dow = firstDayMonth(month,year);
	int counter = 1;
	for (int i = 0; i < dow; i++) {
		printf("   ");
		counter++;
	}
	for (int i = 1; i <= monthDays[month]; i++) {
		if (i < 10) {
			printf(" %d ",i);
		}
		else {
			printf("%d ",i);
		}
		if (counter % 7 == 0) {
			printf("\n");
		}
		counter++;
	}
	printf("\n");
	// if counter has only printed 5 lines of days, print another
	// to ensure the same # of lines is always printed
	if (counter <= (7 * 5)) {
		printf("\n"); 
	}
	
}

/*
 * Prints the inputed year in 3x4 format
 * @param: int year
 */
void printYear(int year) {
	int spaces;
	int mCounter = 0;
	int firstDay = firstDayYear(year);

	if (isLeapYear(year) == 0) {
		monthDays[1] = 29;
	}
	
	int yearSpace = 4;
	// if year is 1-2 digits, halve the space required
	if (year < 100) {
		yearSpace = 2;
	}

	// print centered year (3 month's space - digits of year)
	// extra +1 to match cal
	spaces = ((MONTH_SPACE*3) - (yearSpace-1)) / 2;
	for (int i = 0; i < spaces; i++) {
		printf(" ");
	}
	printf("%d",year);
	for (int i = 0; i < spaces; i++) {
		printf(" ");
	}
	printf("\n");

	// print 4 sets of 3 months 
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			spaces = (MONTH_SPACE - strlen(months[mCounter])) / 2;
			// print 1 month:
			for (int k = 0; k < spaces; k++) { // leading spaces
				printf(" ");
			}
			if (strlen(months[mCounter]) % 2 == 1) {
				spaces++; // counteracts odd # of chars
			}
			printf("%s",months[mCounter]); // month name
			for (int k = 0; k < spaces+2; k++) {
				printf(" "); // trailing spaces
			}
			mCounter++;
		} // end j loop
		printf("\n");

		// print days of week for month
		for (int j = i; j < (i+3); j++) {
			for (int k = 0; k < NUM_DAYS; k++) {
				printf("%s ",week[k]);
			}
			printf(" ");
		}
		printf("\n");

		// now for the days, starting with Jan 1
		int dow[3]; // day of week
		int dom[] = {1,1,1}; // day of month
		for (int j = 0; j < 6; j++) { // 6 rows of numbers
			for (int k = 0; k < 3; k++) { // 3 columns of months
				if (j == 0) {
					// set days of week
					int mCounter2 = k + (i * 3);
					dow[k] = firstDay;
					if (mCounter2 != 0) {
						for (int l = 0; l < mCounter2; 
						    l++) {
							dow[k] += monthDays[l];
						}	
						if (isLeapYear(year) == 0 && 
						    mCounter2 != 1) {
							dow[k]++;
						}
					}
					dow[k] %= 7;
					// print leading spaces
					spaces = dow[k];
					for (int l = 0; l < spaces; l++) {
						printf("   ");
					}
				}
				// print day nums
				while (dow[k] != 7 && 
				       dom[k] <= monthDays[k + (i*3)]) {
					if (dom[k] < 10) {
						printf(" %d ",dom[k]);
					}
					else {
						printf("%d ",dom[k]);
					}
					dow[k]++;
					dom[k]++;
				}
				// reset day of week
				if (dow[k] == 7) {
					dow[k] = 0;
				}
				else {
					// reached end of month
					for (int l = 0; l < (7-dow[k]); l++) {
						printf("   ");
					}
					dow[k] = 0;
				} 
				// cushion between month cols
				printf(" "); 
			} // end k loop
			printf("\n");
		} // end j loop
		  // cushion between month rows
		printf("\n"); 
	} // end i loop
	printf("\n");
	
}

/*
 * Calculates the day of the week of Jan 1st. for the specified year
 * @param: int year
 * @return: int dow, the day of the week
 */
int firstDayYear(int year) {
	int dow = 6; // day of week--cal 1/1/1 is on a Saturday
	for (int i = 1; i < year; i++) {
		if (i < 1752) {
			if (i % 4 == 0) { // leap year
				dow += 366;
			}
			else {
				dow += 365;
			}
		}
		else if (i == 1752) {
			dow = 1; // day of week--cal 1/1/1753 is on a Monday
		}
		else {
			if ((i%4 == 0 && i%100 != 0) || i%400 == 0) {
				dow += 366;
			}
			else {
				dow += 365;
			}
		}
	}
	return dow % 7;
}

/*
 * Calculates the day of the week for the 1st day of the specified month
 * @param: int month
 * @param: int year
 * @return: int dow, the day of the week
 */
int firstDayMonth(int month, int year) {
	int dow = firstDayYear(year);
	for (int i = 0; i < month; i++) { // start at 0 for indexing
		if (i == 1) { 
			if (isLeapYear(year) == 0) {
				dow++;
			}
		}
		dow += monthDays[i];
	}
	return dow % 7;
}

/*
 * Determines if inputed year is a leap year
 * @param: int year
 * @return: int 0 if true, 1 if false
 */
int isLeapYear(int y) {
	if (y < 1753) {
		if (y % 4 == 0) {
			return 0;
		}
	}
	else {
		if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) {
			return 0;
		}
	}
	return 1;
}

/*
 * Calculates and returns the current month
 * using the time library
 * @return: int, the current month
 */
int getMonth() {
	// get current month
	struct tm *timePtr;
        time_t timenow;
	// retrieve current time and store it in timenow
        time(&timenow);
	// convert to local timezone
        timePtr = localtime(&timenow);
	return (timePtr -> tm_mon);
}

/*
 * Calculates and returns the current year
 * using the time library
 * @return: int, the current year
 */
int getYear() {
	// get current year
	struct tm *timePtr;
        time_t timenow;
	// retrieve current time and store it in timenow
        time(&timenow);
	// convert to local timezone
        timePtr = localtime(&timenow);
	// tm_year counts num years since 1900
	return (timePtr -> tm_year + 1900);
}
