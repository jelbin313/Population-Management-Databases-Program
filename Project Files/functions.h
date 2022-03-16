//functions.h
//Julianne Elbin
//functions used throughout the whole project
//

//function to read in a string from standard io until new line char is reached
char * readLine();

//function to read in a string from a file until new line char is reached
char * readFileLine(FILE *fp);

//function to find the end posistion of a file, then rewind to the start
int findEnd(FILE *fp);

//this function will check if a file is empty
//will return 1 if file is empty and 0 if not
int fileEmpty(FILE *fp);

//function to read a line from a file, given an int specifying which line it is
char * getFileLine(FILE *fp, int database);

//function to delete a line from a file, given an int specifying which line it is
void deleteFileLine(char *filePath, int lineNum);
