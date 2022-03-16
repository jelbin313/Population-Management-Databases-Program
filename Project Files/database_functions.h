//database_functions.h

//structure to store data points in
struct dataPoint {
   int population;
   int month;
   int day;
   int year;   
};

//function to ask user to input a new data point and print that point to a line in a file
void inputDataPoint(FILE *fp);

//function to get a line from a database, store in dataPoint struct, and then print data
//void printDataPoint(FILE *fp);

//function to print every line of a database as a data point
void printDatabase(FILE *fp, char *name);

//function to edit a data point from a database file
void editFileLine(char *filePath, int lineNum);

//function to create file path for a file outside of the project folder
char * createExportFilePath(char *name);

//function to get a line from a database, store in dataPoint struct, and then print data to a file
void printDataPointFile(FILE *fp, FILE *new);

//function to print every data point to a txt file
void exportFile(FILE *fp, char *name);