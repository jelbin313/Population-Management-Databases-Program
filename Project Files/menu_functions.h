//menu_functions.h
//Julianne Elbin
//functions used only by main menu
//

//function to run the database menu given a filePath for a database
void database_menu(char * filePath, char * name);

//function to check document to see if a line matches a string
//returns 1 if match found and 0 if not
int checkForMatch(FILE *fp, char *string);

//function to create database file path given file name
char * createFilePath(char *name);

//function to print current databases
void displayDatabases(FILE *fp);

//function to print databases in databases file, then have user select one
int selectDatabase(FILE *fp);