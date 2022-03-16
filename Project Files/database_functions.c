//database_functions.c
//Julianne Elbin
//functions used only by the database menu
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "database_functions.h"



//function to ask user to input a new data point and print that point to a line in a file
void inputDataPoint(FILE *fp) {
   //set up structure to hold data
   struct dataPoint *newPoint = malloc(sizeof(struct dataPoint));
                    
   //ask user for input and store in struct            
   printf("\nEnter date (in numbers)\n");
   printf("Enter month:           ");
   scanf("%d", &newPoint->month);
                     
   printf("Enter day:             ");
   scanf("%d", &newPoint->day);
                     
   printf("Enter year:            ");
   scanf("%d", &newPoint->year);
                     
   printf("\nEnter population size: ");
   scanf("%d", &newPoint->population);
                     
   //print struct to line of file
   fprintf(fp, "%d %d %d %d\n", newPoint->month, newPoint->day, newPoint->year, newPoint->population);
                     
   //free struct pointer
   free(newPoint);
}



//function to get a line from a database, store in dataPoint struct, and then print data
void printDataPoint(FILE *fp) {
   //set up structure to hold data
   struct dataPoint *point = malloc(sizeof(struct dataPoint));
   
   //character pointer to hold line
   char *line = malloc(sizeof(char)*81);
   
   //get line from file
   fgets(line, 81, fp);
   
   //use loc to keep track of location
   int loc = 0;
   
   //char for current character
   char *c = malloc(sizeof(char));
   *c = *(line + loc);
   
   //char pointer to hold number we are reading in
   char *num = calloc(1, sizeof(char)*20);
   
   //we will read in chars 4 times
   for(int i = 0; i < 4; i++) {      
      //read in chars, stop when we hit space or '\n'
      while(*c != '\n') {
         //get next c and increment loc
         *c = *(line + loc);
         loc++;
         
         //if c is a space, break this loop
         if(*c == ' ') {
            break;
         }
         
         //as long as c is not space, add to num
         strcat(num, c);
      }
      
      //now we will turn num into an int and store in different locations depending on what pass we are on
      if(i == 0) {
         //convert to int and store in month
         point->month = atoi(num);
      }
      else if(i == 1) {
         //convert to int and store in day
         point->day = atoi(num);
      }
      else if(i == 2) {
         //convert to int and store in year
         point->year = atoi(num);
      }
      else if(i == 3) {
         //convert to int and store in population
         point->population = atoi(num);
      }
      
      //reset num to be empty again
      free(num);
      num = calloc(1, sizeof(char)*20);
   }
   
   //now we can print the data point
   printf("Date: %d/%d/%d\n", point->month, point->day, point->year);
   printf("   Population: %d", point->population);
   
   //free anyting we need to free
   free(point);
   free(line);
   free(num);
   free(c);
}



//function to print every line of a database as a data point
void printDatabase(FILE *fp, char *name) {
   //find and store end
   int end = findEnd(fp);
   
   //display databases
   printf("\nData in %s:\n", name);

   //integer for number of data point
   int i = 1;
   
   //go through file and get each line
   while(ftell(fp) != end) {
      printf("\n%d. ", i);
      printDataPoint(fp);
      printf("\n");
      i++;
   }
}



//function to edit a data point from a database file
void editFileLine(char *filePath, int lineNum) {
   //open the file
   FILE *old = fopen(filePath, "r");
   
   //create a new file to write lines to
   FILE *new = fopen("temp.txt", "w");
   
   //get end
   int end = findEnd(old);
   
   //string to hold each line
   char *line = NULL;
   
   //int to hold what line we are on
   int i = 1;
   
   //go through each line of the file
   while(ftell(old) != end) {
      //read in each line of the file
      line = readFileLine(old);
      //check if the line is the line to be deleted
      if(i != lineNum) {
         //if it's not, print line to new file
         fprintf(new, "%s\n", line);
      }
      else {
         printf("\nEnter new data point %d: ", lineNum);
         //if we are on the line to edit, have user input new data point
         inputDataPoint(new);
      }
      //free the memory and increment i
      free(line);
      i++;
   }
   //close files
   fclose(new);
   fclose(old);
      
   //delete original file
   remove(filePath);
   
   //rename temp file
   rename("temp.txt", filePath);
}



//function to create file path for a file outside of the project folder
char * createExportFilePath(char *name) {
   //variable to hold file path
   char *filePath = calloc(95, sizeof(char));
   
   //concatenate and store in filePath
   strcat(filePath, "../");
   strcat(filePath, name);
   strcat(filePath, ".txt");
   
   //return
   return filePath;
}



//function to get a line from a database, store in dataPoint struct, and then print data to a file
void printDataPointFile(FILE *fp, FILE *new) {
   //set up structure to hold data
   struct dataPoint *point = malloc(sizeof(struct dataPoint));
   
   //character pointer to hold line
   char *line = malloc(sizeof(char)*81);
   
   //get line from file
   fgets(line, 81, fp);
   
   //use loc to keep track of location
   int loc = 0;
   
   //char for current character
   char *c = malloc(sizeof(char));
   *c = *(line + loc);
   
   //char pointer to hold number we are reading in
   char *num = calloc(1, sizeof(char)*20);
   
   //we will read in chars 4 times
   for(int i = 0; i < 4; i++) {      
      //read in chars, stop when we hit space or '\n'
      while(*c != '\n') {
         //get next c and increment loc
         *c = *(line + loc);
         loc++;
         
         //if c is a space, break this loop
         if(*c == ' ') {
            break;
         }
         
         //as long as c is not space, add to num
         strcat(num, c);
      }
      
      //now we will turn num into an int and store in different locations depending on what pass we are on
      if(i == 0) {
         //convert to int and store in month
         point->month = atoi(num);
      }
      else if(i == 1) {
         //convert to int and store in day
         point->day = atoi(num);
      }
      else if(i == 2) {
         //convert to int and store in year
         point->year = atoi(num);
      }
      else if(i == 3) {
         //convert to int and store in population
         point->population = atoi(num);
      }
      
      //reset num to be empty again
      free(num);
      num = calloc(1, sizeof(char)*20);
   }
   
   //now we can print the data point
   fprintf(new, "Date: %d/%d/%d\n", point->month, point->day, point->year);
   fprintf(new, "   Population: %d", point->population);
   
   //free anyting we need to free
   free(point);
   free(line);
   free(num);
   free(c);
}



//function to print every data point to a txt file
void exportFile(FILE *fp, char *name) {
   //make name into a file path
   char * filePath;
   filePath = createExportFilePath(name);
   
   //create a new file one folder above the program folder
   FILE *exportFile;
   exportFile = fopen(filePath, "w");
   
   //print database name
   fprintf(exportFile, "%s Database\n", name);
   
   //find and store end of database file
   int end = findEnd(fp);

   //integer for number of data point
   int i = 1;
   
   //go through file and get each line
   while(ftell(fp) != end) {
      fprintf(exportFile, "\n%d. ", i);
      printDataPointFile(fp, exportFile);
      fprintf(exportFile, "\n");
      i++;
   }
   
   //close new file
   fclose(exportFile);
}