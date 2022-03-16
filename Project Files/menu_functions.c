//menu_functions.c
// Julianne Elbin
//functions used only by main menu
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "functions.h"
#include "menu_functions.h"



//function to check document to see if a line matches a string
//returns 1 if match found and 0 if not
int checkForMatch(FILE *fp, char *string) {
   //first make sure we're at the start of the file
   rewind(fp);
   
   //variables
   char * line = NULL;
   int end = findEnd(fp);
   
   //get every line in the docuemnt
   while(ftell(fp) != end) {
      //get line
      line = readFileLine(fp);
      
      //compare line to string
      if(strcmp(line, string) == 0) {
         //if match is found, make sure to free line and return 1
         free(line);
         return 1;
      }
      //if match not found, make sure to free line
      free(line);
   }
   //if match not found, return 0
   return 0;
}



//function to create file path given database name
char * createFilePath(char *name) {
   //variable to hold file path
   char *filePath = calloc(95, sizeof(char));
   
   //concatenate and store in filePath
   strcat(filePath, "Databases/");
   strcat(filePath, name);
   strcat(filePath, ".txt");
   
   //return
   return filePath;
}


//function to print current databases
void displayDatabases(FILE *fp) {
   //first make sure we're at the start of the file
   rewind(fp);
   
   //display databases
   printf("\nCurrent Databases: \n");
   
   //number for database display
   int i = 1;
   
   //get end of file position and store it
   int end = findEnd(fp);
   
   //char pointer to store line so we can free it
   char * line;
   line = NULL;
   
   //go through file and get each line
   while(ftell(fp) != end) {
      line = readFileLine(fp);
      printf("%d. %s\n", i, line);
      free(line);
      i++;
   }
}



//function to print databases in databases file, then have user select one
int selectDatabase(FILE *fp) {
   //first display databases
   displayDatabases(fp);
   
   //integer to hold database selection
   int database;
            
   //prompt user for database
   printf("\nEnter the number of the database: ");
   scanf("%d", &database);
   
   //return the line
   return database;
}
