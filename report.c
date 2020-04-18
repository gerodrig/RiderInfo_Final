/* DIGITAL SIGNATURE(S):
   ====================

   List the student author(s) of this code below:

   Fullname                    Seneca Email Address
   --------------------------- ----------------------------
   1) Gerardo Arturo Rodriguez  garodriguez-cardenas@myseneca.ca
   */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "file_helper.h"
#include "report.h"

//-------------------------------------------------------------------------------------
//FoolProof and helper Functions
//-------------------------------------------------------------------------------------

void clearStdInput(void)
{
	while (getchar() != '\n'); // empty execution code block on purpose
	return; 
}

int getInt(void)
{
	int value;
	char newline;

	scanf("%d%c", &value, &newline);

	while (newline != '\n')
	{
		clearStdInput();
		printf("*** INVALID INTEGER *** <Please enter an integer>: ");
		scanf("%d%c", &value, &newline);
	}

	return value;
}

int getIntInRange(int min, int max)
{
	int inRange = 0;

	do
	{

		inRange = getInt();

		if (inRange < min || inRange > max)
		{
			printf("*** INVALID SELECTION*** <Enter a number between %d and %d>: ", min, max);
		}

	} while (inRange < min || inRange > max);

	return inRange;
}

char categorySelection(void)
{
	char oneChar;
	char newline;
	char category;

	printf("\nWhich category (S, M, L): ");
	scanf(" %c%c", &oneChar, &newline);

	while ((oneChar != 's' && oneChar != 'S' && oneChar != 'm' && oneChar != 'M' && oneChar != 'l' && oneChar != 'L') || (newline != '\n'))
	{
		clearStdInput();
		printf("*** INVALID ENTRY *** <Only (S)hort (M)edium or (L)ong are acceptable>: ");
		scanf("%c%c", &oneChar, &newline);
	}

	if ((oneChar == 's') || (oneChar == 'S'))
	{
		return category = 'S';
	}
	else if ((oneChar == 'm') || (oneChar == 'M'))
	{
		return category = 'M';
	}
	else if ((oneChar == 'l') || (oneChar == 'L'))
	{
		return category = 'L';
	}
	else
	{
		return category = 0;
	}
}

//-------------------------------------------------------------------------------------
//Menu Functions
//-------------------------------------------------------------------------------------

int getMenuSelection(void)
{
	int selection;

	/*printf("******************** Seneca Cycling Race Results ********************\n");*/
	printf("What would you like to do?\n");
	printf("0 - Exit\n");
	printf("1 - Print top 3 riders in a category\n");
	printf("2 - Print all riders in a category\n");
	printf("3 - Print last 3 riders in a category\n");
	printf("4 - Print winners in all categories\n");
	printf(": ");

	return selection = getIntInRange(0, 4);

}

void startReportManager(struct RiderInfo info[], int arrSize)
{
	/*struct RiderInfo info;*/
	int keepRunning = 1, option;
	const char filename[] = "data.txt"; //filename data.txt will be loaded
	char category;

	// Calling this function to load the riders data and return the count of entries in file. reportSize will hold the number of lines.
	int reportSize = loadRiderData(filename, info, arrSize); 
	// Function to sort the riders in ascending order and run the sort according to the number of entries read from the filename.
	sortRiders(info, reportSize);

	printf("******************** Seneca Cycling Race Results ********************\n");

	do
	{

		switch (option = getMenuSelection())
		{
		// 0 to exit the application 
		case 0:
			printf("\nKeep on Riding!\n");
			keepRunning = 0;
			break;
		// 1 to run the report to show top 3 Riders in selected category
		case 1:
			category = categorySelection();
			displayReportHeader(option);
			displayTopRiders(info, category, reportSize);
			break;
		// 2 to run the report to display all riders in selected category
		case 2:
			category = categorySelection();
			displayReportHeader(option);
			displayAllRiders(info, category, reportSize);
			break;
		// 3 to run the report to show top Last Riders in selected category
		case 3:
			category = categorySelection();
			displayReportHeader(option);
			displayLastRiders(info, category, reportSize);
			break;
		// 4 to run the report to show winner rider in each category
		case 4:
			displayReportHeader(option);
			displayWinnerRiders(info, reportSize);
			break;
		}

	} while (keepRunning == 1);
}

//-------------------------------------------------------------------------------------
// File I/O Functions
//-------------------------------------------------------------------------------------

int loadRiderData(const char* filename, struct RiderInfo info[], int arrSize) {
	/*struct RiderInfo info[MAXRIDERS] = { 0 };*/
	/*const char filename[] = "data.txt";*/
	int i = 0;

	FILE* fp = fopen(filename, "r"); //read mode is selected

	if (fp != NULL)
	{
		for (i = 0; !readFileRecord(fp, &info[i]) && i < arrSize; i++);

		fclose(fp);   //safely close file connection and flush the contents from input buffer
		fp = NULL;    //set fp to a safe empty state
	}
	else
	{
		printf("ERROR: Unable to open file for reading.\n");
	}

	return i;
}

void sortRiders(struct RiderInfo info[], int arrSize) {
	
	struct RiderInfo temp;
	int i, j, m;

	for (i = 0; i < arrSize; i++) {  //FOR loop to sort all members for low to highest. N/As will be sorted first
		m = i;
		for (j = i + 1; j < arrSize; j++)
			if ((info[j].finishTime - info[j].startTime) < (info[m].finishTime - info[m].startTime))
			{
				m = j;
			}
		if (m != i)
		{
			temp = info[i];
			info[i] = info[m];
			info[m] = temp;
		}
	}

	for (i = 0; i < arrSize; i++) { //FOR LOOP to Sort all N/As to end
		m = i;
		for (j = i + 1; j < arrSize; j++)
			if (info[j].withdrawn < info[m].withdrawn)
			{
				m = j;
			}

		if (m != i)
		{
			temp = info[i];
			info[i] = info[m];
			info[m] = temp;
		}
	}
}

void timeOutputFormat(double time) {
	int hour, minute;
	time += .005; // adding .005 to time to resolve when either rounded or truncated

	hour = (int)time;
	minute = (int)(time * 60) % 60;
	//minute %= 60;


	printf(" %d:%02d", hour, minute);
}

void displayReportHeader(int option) {

	char* headerTitles[] = { "Rider", "Age", "Group", "Category", "Time", "Withdrew" }; // char array to hold the name of the header titles. Struct would be better to hold this values.

	putchar('\n');
	if (option == 1 || option == 3)
	{
		printf("%-25s%-4s%-6s%s\n", headerTitles[0], headerTitles[1], headerTitles[2], headerTitles[4]);
		printf("---------------------------------------\n");
	}
	else if (option == 2)
	{
		printf("%-25s%-4s%-6s%-5s%s\n", headerTitles[0], headerTitles[1], headerTitles[2], headerTitles[4], headerTitles[5]);
		printf("------------------------------------------------\n");
	}
	else if (option == 4)
	{
		printf("%-25s%-4s%-6s%-9s%s\n", headerTitles[0], headerTitles[1], headerTitles[2], headerTitles[3], headerTitles[4]);
		printf("------------------------------------------------\n");
	}



}

void displayTopRiders(const struct RiderInfo info[], char selection, int arrSize) {
	int i;
	int count = 0;

	// FOR loop to print the top riders according to selection. For loop will break after 3 riders are displayed.
	for (i = 0; i < arrSize; i++)
	{
		if (info[i].raceLength == selection && count < 3 && info[i].withdrawn != 1) {

			printf("%-25s  ", info[i].name);

			if (info[i].age >= 16 && info[i].age <= 20)
			{
				char group[] = "Junior";
				printf(" %-6s", group);
			}
			else if (info[i].age >= 21 && info[i].age <= 34)
			{
				char group[] = "Adult";
				printf(" %-6s", group);
			}
			else if (info[i].age >= 35)
			{
				char group[] = "Senior";
				printf(" %-6s", group);
			}
				timeOutputFormat(info[i].finishTime - info[i].startTime);
				putchar('\n');
				count++;
		}
		if (count == 3)
		{
			break;
		}
	}
	//IF no rider was displayed. Not Awarded will be displayed
	if (count == 0)
	{
		printf("Not Awarded\n");
	}
	putchar('\n');
}

void displayLastRiders(const struct RiderInfo info[], char selection, int arrSize) {
	int i;
	int count = 0;	//this variable will be used as a flag to stop any loop when the count gets to 3 and avoid checking all the struct. This to make code process efficient.
	int lastTopIndex[3] = { 0 };  //This variable will hold the top 3 lowest values, this to avoid sorting the structure again and be able to display the last riders in ascending order.

	//Struct Array is already sorted with ascending values. this FOR loop will save the rider index in lastTopIndex[3] array for the last riders in selected category
	for (i = arrSize - 1; i >= 0; i--)
	{
		//Following condition will trigger only for the selected category and discarding riders with withdrawn status.
		if (info[i].raceLength == selection && count < 3 && info[i].withdrawn != 1) {
			lastTopIndex[count] = i;
			count++;
		}
		if (count == 3)
		{
			break;
		}
	}
	// IF no rider is found for selected category "No Awarded will be displayed and function will end
	if (count == 0) 
	{
		printf("Not Awarded\n");
	}
	else
	{	// lastTopIndex[i] is holding the last rider values from more to less. [0] is holding the slowest values. hence, FOR loop is in descending order to show from lowest time to highest
		for (i = (sizeof(lastTopIndex) / sizeof(lastTopIndex[0])) - 1; i >= 0; i--) 
		{
			printf("%-25s  ", info[lastTopIndex[i]].name);

			//Following logic will print the category based on the age of the rider
			if (info[lastTopIndex[i]].age >= 16 && info[lastTopIndex[i]].age <= 20)
			{
				char group[] = "Junior";
				printf(" %-6s", group);
			}
			else if (info[lastTopIndex[i]].age >= 21 && info[lastTopIndex[i]].age <= 34)
			{
				char group[] = "Adult";
				printf(" %-6s", group);
			}
			else if (info[lastTopIndex[i]].age >= 35)
			{
				char group[] = "Senior";
				printf(" %-6s", group);
			}
			timeOutputFormat(info[lastTopIndex[i]].finishTime - info[lastTopIndex[i]].startTime);
			putchar('\n');
			count++;
		}
	}
	putchar('\n');
}

void displayAllRiders(const struct RiderInfo info[], char selection, int arrSize) {
	int i;
	int count = 0;

	// FOR loop to print the All riders according to selection. 
	for (i = 0; i < arrSize; i++)
	{
		if (info[i].raceLength == selection) {

			printf("%-25s  ", info[i].name);

			if (info[i].age >= 16 && info[i].age <= 20)
			{
				char group[] = "Junior";
				printf(" %-6s", group);
			}
			else if (info[i].age >= 21 && info[i].age <= 34)
			{
				char group[] = "Adult";
				printf(" %-6s", group);
			}
			else if (info[i].age >= 35)
			{
				char group[] = "Senior";
				printf(" %-6s", group);
			}

			if (info[i].withdrawn)
			{
				char yes[] = "Yes";
				printf("  N/A %8s", yes);
			}
			else
			{
				char no[] = "No";
				timeOutputFormat(info[i].finishTime - info[i].startTime);
				printf(" %8s", no);
			}
			putchar('\n');
			count++;
		}

	}
	//IF no rider was displayed message will be displayed.
	if (count == 0)
	{
		printf("No riders were registered under %c category.", selection);
	}
	putchar('\n');
}

void displayWinnerRiders(const struct RiderInfo info[], int arrSize) {

	int i;

	//For loop to display the top rider in S category. After first rider is found loop will break. If no entries found No Awarded will be displayed.
	for (i = 0; i < arrSize; i++)
	{
		char cat[] = "50 km";

		if (info[i].raceLength == 'S')
		{
			printf("%-25s  ", info[i].name);

			if (info[i].age >= 16 && info[i].age <= 20)
			{
				char group[] = "Junior";
				printf(" %-6s", group);
			}
			else if (info[i].age >= 21 && info[i].age <= 34)
			{
				char group[] = "Adult";
				printf(" %-6s", group);
			}
			else if (info[i].age >= 35)
			{
				char group[] = "Senior";
				printf(" %-6s", group);
			}
			printf(" %8s", cat);
			timeOutputFormat(info[i].finishTime - info[i].startTime);
			putchar('\n');
			break;
		}
		if (i == arrSize -1)
		{
			printf("Not Awarded %31s\n", cat);
		}
	}

	//FOR loop to display the top rider in M category. After first rider is found loop will break. If no entries found No Awarded will be displayed.
	for (i = 0; i < arrSize; i++)
	{
		char cat[] = "75 km";

		if (info[i].raceLength == 'M')
		{
			printf("%-25s  ", info[i].name);

			if (info[i].age >= 16 && info[i].age <= 20)
			{
				char group[] = "Junior";
				printf(" %-6s", group);
			}
			else if (info[i].age >= 21 && info[i].age <= 34)
			{
				char group[] = "Adult";
				printf(" %-6s", group);
			}
			else if (info[i].age >= 35)
			{
				char group[] = "Senior";
				printf(" %-6s", group);
			}
			printf(" %8s", cat);
			timeOutputFormat(info[i].finishTime - info[i].startTime);
			putchar('\n');
			break;
		}
		if (i == arrSize -1)
		{
			printf("Not Awarded %31s\n", cat);
		}
	}
	//FOR loop to display the top rider in L category.After first rider is found loop will break.If no entries found No Awarded will be displayed.
	for (i = 0; i < arrSize; i++)
	{
		char cat[] = "100 km";

		if (info[i].raceLength == 'L')
		{
			printf("%-25s  ", info[i].name);

			if (info[i].age >= 16 && info[i].age <= 20)
			{
				char group[] = "Junior";
				printf(" %-6s", group);
			}
			else if (info[i].age >= 21 && info[i].age <= 34)
			{
				char group[] = "Adult";
				printf(" %-6s", group);
			}
			else if (info[i].age >= 35)
			{
				char group[] = "Senior";
				printf(" %-6s", group);
			}
			printf(" %8s", cat);
			timeOutputFormat(info[i].finishTime - info[i].startTime);
			putchar('\n');
			break;
		}
		if (i == arrSize - 1)
		{
			printf("Not Awarded %31s\n", cat);
		}
	}
	putchar('\n');
}
