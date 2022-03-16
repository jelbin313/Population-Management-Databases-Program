//functions.c
//Julianne Elbin
//functions used throughout the whole project
//

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "functions.h"



//function to read in a string from standard io until new line char is reached
char * readLine() {
   //get memory for a char array of 81
   char *string = malloc(sizeof((char)81));
   
   //read in while char is not \n
   char c = getchar();
   int i = 0;
   while(c != '\n') {
      *(string + i) = c;
      c = getchar();
      i++;
   }
   
   //add on null char
   *(string + i) = '\0';
   
   //return pointer to the string
   return string;
}



//function to read in a string from a file until new line char is reached
char * readFileLine(FILE *fp) {
   //get memory for a char array of 81
   char *string = malloc(sizeof((char)81));
  
  //get line
  fgets(string, 81, fp);
  
  int i = 0;
  
  //for loop to replace new line char with null char
  while(*(string + i) != '\n') {
      i++;
  }
  
  //replace \n with \0
  *(string + i) = '\0';
  
  //return pointer to char array
  return string;
}



//function to find the end posistion of a file, then rewind to the start
int findEnd(FILE *fp) {
   //first make sure we're at the start of the file
   rewind(fp);
   
   //find end position of file
   fseek(fp, 0, SEEK_END);

   //store end position
   int end = ftell(fp);
   
   //rewind to beginning of the document
   rewind(fp);
   
   //return end
   return end;
}



//this function will check if a file is empty
//will return 1 if file is empty and 0 if not
int fileEmpty(FILE *fp) {
   //find end
   int end = findEnd(fp);
   
   //rewind file to start
   rewind(fp);
   
   //checking if current (start) position is same as end position
   
   if(ftell(fp) == end) {
      return 1;
   }
   
   else {
      return 0;
   }
}



//function to read a line from a file, given an int specifying which line it is
char * getFileLine(FILE *fp, int line) {
   //first make sure we're at the start of the file
   rewind(fp);
   
   //get memory for string
   char *string;
   string = NULL;
      
   //go through the file and get i lines to get to the line the user selected
   for(int i = 1; i < line; i++) {
      //move fp down a line
      string = readFileLine(fp);
      
      //make sure to free, since readFileLine uses malloc
      free(string);
   }
   
   //then, when i equals line, read in that line
   string = readFileLine(fp);
   
   //return line
   return string;
}



//function to delete a line from a file
void deleteFileLine(char *filePath, int lineNum) {
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