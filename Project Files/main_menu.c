//main_menu.c
//Julianne Elbin
//this file contains main, which contains the main menu for the program
//the main menu will allow users to create, delete, and edit databases
//editing a database will open a second database menu, with options to edit the data

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "menu_functions.h"



int main() {   
   //create an integer variable to hold user input, set it to something non-zero so that the while loop will run
   int input = -1;
   
   //declare variables that will be used in multiple cases
   //variable to hold file pointer
   FILE *fp = NULL;
   //variable to hold database name
   char *name = NULL;
   //variable to hold file path
   char *filePath = NULL;
   //variable to hold databse selection
   int database;
   
   //Print opening message
   printf("Population Management Databases Program\n");
   
   //display the menu while user did not choose exit
   while(input != 0) {
      //first we will print the menu
      printf("\n1. Create new database\n");
      printf("2. View databases\n");
      printf("3. Edit database\n");
      printf("4. Delete Database\n");
      printf("0. Exit\n");
      printf("Enter number of your choice: ");
      scanf("%d", &input);
      
      //after scanning in input, clear keybaord buffer
      getchar();
      
      switch(input) {
         case 0:
            //do nothing, simply exit this loop
            printf("\nExiting Program...\n");
            break;
         case 1: //add database
            //prompt user for the name of the databse
            printf("\nEnter database name: ");
            name = readLine();
            
            //open databases file to read
            fp = fopen("Databases.txt", "r");
            
            int match = checkForMatch(fp, name);
                        
            //check if name is already in use
            if(match == 1) {               
               //close databses file
               fclose(fp);
               
               //tell user the name is taken
               printf("\nDatabase name taken. Please choose another name.\n");
            }
            
            //if not, add line to databases file and create new file
            else {
               //close databses file
               fclose(fp);
               
               //open databases file to append
               fp = fopen("Databases.txt", "a");
               
               //print database name
               fprintf(fp, "%s\n", name);
               
               //close databses file
               fclose(fp);
               
               //now make name into file path
               filePath = createFilePath(name);
               
               //then create file using file path
               fp = fopen(filePath, "w");
               
               //close file that you just created
               fclose(fp);
               
               //print message 
               printf("\n%s created.\n", name);
            }
            
            //free any memory that we need to free
            free(name);
            free(filePath);
                                    
            break;
         case 2: //View databases
            //open databases file to read
            fp = fopen("Databases.txt", "r");
           
            //check if any databases exist
            if(fileEmpty(fp)) {
               //close databases file 
               fclose(fp);
               
               //print message
               printf("\nNo databases exist. Please create one.\n");
            }
            
            else {
               //display databases
               displayDatabases(fp);
               
               //close database file
               fclose(fp);
            }
              
            break;
         case 3: //edit database
            //open databases file to read
            fp = fopen("Databases.txt", "r");
            
            //check if any databases exist
            if(fileEmpty(fp)) {
               //close database file
               fclose(fp);
               
               //print message
               printf("\nNo databases exist. Please create one.\n");
            }
            
            else {
               //display databses and have user select one               
               //get the database nmae
               name = getFileLine(fp, selectDatabase(fp));
               
               //close database file
               fclose(fp);
            
               //turn that name into a file path
               filePath = createFilePath(name);
               
               //print database name
               printf("\n%s Database\n", name);
               
               //run database menu on that file
               database_menu(filePath, name);
            }
            
            //free any memory that we need to free
            free(name);
            free(filePath);
   
            break;

         case 4: //delete database
            //open databases file to read
            fp = fopen("Databases.txt", "r");
           
            //check if any databases exist
            if(fileEmpty(fp)) {
               //close databases file 
               fclose(fp);
               
               //print message
               printf("\nNo databases exist. Please create one.\n");
            }
            
            else {               
               //display databses and have user select one
               database = selectDatabase(fp);
               
               //get the database name
               name = getFileLine(fp, database);
               
               //turn name into a file path
               filePath = createFilePath(name);
               
               //close database file
               fclose(fp);
               
               //delete that line
               deleteFileLine("Databases.txt", database);
               
               //delete the file
               remove(filePath);
               
               //print message 
               printf("\n%s deleted.\n", name);
            }
            
            //free any memory that we need to free
            free(name);
            free(filePath);
                    
            break;

         default:
            printf("\nPlease enter a valid menu option.\n");
            break;
      }
   } 
   //print exit message
   printf("\nExit Complete\n");
}