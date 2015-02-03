//
//  main.cpp
//  Euler Problem 1
//
//  Created by Joel Atyas on 1/25/15.
//  Copyright (c) 2015 Joel Atyas. All rights reserved.
//

#include <iostream>
#include <string.h>
#include <exception>

using namespace std;

#define FINESSE

/*
   Function to read and validate user input
   (help from http://stackoverflow.com/questions/4023895/how-to-read-string-entered-by-user-in-c/4023921#4023921)
 */
#define OK       0      // input is valid
#define NO_INPUT 1      // user did not enter anything
#define TOO_LONG 2      // too much information entered
#define DEFAULT_INPUT 3 // user pressed return with nothing preceding
static int getUserInputLine(char *prmpt, char *buff, size_t sz) {
	int ch, extra;

	// Get line with buffer overrun protection.
	if (prmpt != NULL) {
		printf("%s", prmpt);
		fflush(stdout);
	}
	if (fgets(buff, sz, stdin) == NULL)
		return NO_INPUT;

	// If it was too long, there'll be no newline. In that case, we flush
	// to end of line so that excess doesn't affect the next call.
	if (buff[strlen(buff) - 1] != '\n') {
		extra = 0;
		while (((ch = getchar()) != '\n') && (ch != EOF))
			extra = 1;
		return (extra == 1) ? TOO_LONG : OK;
	}
    
    if (buff[0] == '\n') {
        return DEFAULT_INPUT;
    }

	// Otherwise remove newline and give string back to caller.
	buff[strlen(buff) - 1] = '\0';
	return OK;
}

int solveByBruteForce(int input);

int solveByCleverness(int input);

int main(int argc, const char *argv[]) {
	
    int userInput = 0;
	char inputBuffer[7];
	int inputResult = 0;

	int sumMult = 0;

    printf("Please enter an integer value of less than 1,000,000. Enter return to accept a default of 1000: ");
	try {
		while ((inputResult = getUserInputLine(NULL, inputBuffer, sizeof(inputBuffer))) != OK) {
			switch (inputResult) {
				case NO_INPUT:
					printf("\nPlease enter an integer value:  \n");
					break;
				case TOO_LONG:
                    printf("\nPlease enter an integer value less 1,000,000:  \n");
					break;
                case DEFAULT_INPUT:
                    printf("\nDefault value of 1000 accepted.  \n");
                    break;
				default:
					break;
			}
            if (inputResult == DEFAULT_INPUT) {
                break;
            }
		}
        
        if (inputResult == DEFAULT_INPUT) {
            userInput = 1000;
        }
        else
            userInput = atoi(inputBuffer);
	}
	catch (exception &)
	{
		printf("\nSomething went wrong!  Please start over.");
		return -1;
	}
    
#ifndef FINESSE
    sumMult = solveByBruteForce(userInput);
#else
    sumMult = solveByCleverness(userInput);
#endif
    
    printf("\n");
    printf("The sum of all the numbers less than %d with a factor of three or five is %d.\n", userInput, sumMult);

	return 0;
}


int solveByBruteForce(int input)
{
    int sumMultiples = 0;
    
    for (int index = 1; index < input; index++) {
        
        if ((index%3 == 0) || (index%5 == 0)) {
            sumMultiples += index;
        }
    }
    
    return sumMultiples;
}

int solveByCleverness(int input)
{
    input -= 1;
    
    int threeN = input/3;
    int fiveN = input/5;
    int fifteenN = input/15;
    
    return (3*threeN*(threeN + 1))/2 + (5*fiveN*(fiveN + 1))/2 - (15*fifteenN*(fifteenN + 1))/2;
}
