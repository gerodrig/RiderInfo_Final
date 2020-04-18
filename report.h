/* DIGITAL SIGNATURE(S):
   ====================

   List the student author(s) of this code below:

   Fullname                    Seneca Email Address
   --------------------------- ----------------------------
   1) Gerardo Arturo Rodriguez  garodriguez-cardenas@myseneca.ca
   */
/********************************************************/
/* All Prototypes for report c will be declared in this */
/* header.                                              */
/********************************************************/


// Function to clear input buffer.
void clearStdInput(void);

// Function to return a char used for category selection. foolproof check is included.
char categorySelection(void);

// Function to foolproof check that an int is entered.
int getInt(void);

// Function gets a valid range to ensure menu selection is foolproof and an int will be returned.
int getIntInRange(int min, int max);

// Function return int to use it as the menu selection.
int getMenuSelection(void);

// Display Rider Report Header.
void displayReportHeader(int option);

// Core function that Manages other functions and run in main:
void startReportManager(struct RiderInfo info[], int arrSize);

// Function reads the contents of a file and stores the record into a Rider info array. Funtion will return the count of the number of registers in the file.
int loadRiderData(const char* filename, struct RiderInfo info[], int arrSize);

// After reading the data file Function to Sort in ascending order all riders. withdrawn riders will be sorted at the end of the array.
void sortRiders(struct RiderInfo info[], int arrSize);

// Display the time passed in the format requested in the report.
void timeOutputFormat(double time);

// Display the Top 3 riders according to the selection that is passed.
void displayTopRiders(const struct RiderInfo info[], char selection, int arrSize);

// Display the Last 3 riders in ascending order according to the selection that is passed.
void displayLastRiders(const struct RiderInfo info[], char selection, int arrSize);

// Display all riders in ascending order according to the selection that is passed.
void displayAllRiders(const struct RiderInfo info[], char selection, int arrSize);

// Display all riders in ascending order according to the selection that is passed.
void displayWinnerRiders(const struct RiderInfo info[], int arrSize);
