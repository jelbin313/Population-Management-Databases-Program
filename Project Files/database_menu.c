//database_menu.c
//Julianne Elbin
//This file will contain one function that runs a menu for a specific database
//this function will take one input parameter, a string containing the filePath for the database
//The database will be filled with items of a structure data type that will hold a date and population size
//each item of this structure will be one data point

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "database_functions.h"



void database_menu(char * filePath, char * name) {
   //create an integer variable to hold user input, set it to something non-zero so that the while loop will run
   int input = -1;
   
   //variable to hold file pointer
   FILE *fp = NULL;
   
   //int to hold a selected data point
   int dataPoint;
   
   //display the menu while user did not choose exit
   while(input != 0) {
      //first we will print the menu
      printf("\n1. Add data point\n");
      printf("2. View data points\n");
      printf("3. Edit data point\n");
      printf("4. Delete data point\n");
      printf("5. Export Data (as a .txt file)\n");
      printf("0. Exit\n");
      printf("Enter number of your choice: ");
      scanf("%d", &input);
      
      //after scanning in input, clear keybaord buffer
      getchar();
      
      switch(input) {
         case 0:
            //do nothing, simply exit this loop
            printf("\nExiting Database Menu...\n");
            break;
         case 1: //Add data point
            //open file to append
            fp = fopen(filePath, "a");
            
            //insert data point
            inputDataPoint(fp);
            
            //print message 
            printf("\nData added.\n");
            
            //close file
            fclose(fp);
            
            break;
         case 2: //View data points
            //open file to read
            fp = fopen(filePath, "r");
            
            //check if file is empty
            if(fileEmpty(fp)) {
               //close file
               fclose(fp);
               
               //print message
               printf("\nNo data. Please enter a data point.\n");
            }
            else {               
               //print database
               printDatabase(fp, name);
            
               //close file
               fclose(fp);
            }
                                
            break;
         case 3: //Edit data point
            //open file to read
            fp = fopen(filePath, "r");
            
            //check if file is empty
            if(fileEmpty(fp)) {
               //close file
               fclose(fp);
               
               //print message
               printf("\nNo data. Please enter a data point.\n");
            }
            else {               
               //print database
               printDatabase(fp, name);
            
               //close file
               fclose(fp);
               
               //ask user for the number of the data point to delete
               printf("\nEnter the number of the data point: ");
               scanf("%d", &dataPoint);
               
               //have user re input that line
               editFileLine(filePath, dataPoint);
               
               //print message 
               printf("\nData updated.\n");
            }
            
            break;
         case 4: //Delete data point
            //open file to read
            fp = fopen(filePath, "r");
            
            //check if file is empty
            if(fileEmpty(fp)) {
               //close file
               fclose(fp);
               
               //print message
               printf("\nNo data. Please enter a data point.\n");
            }
            else {
               //print database
               printDatabase(fp, name);
            
               //close file
               fclose(fp);
               
               //ask user for the number of the data point to delete
               printf("\nEnter the number of the data point: ");
               scanf("%d", &dataPoint);
               
               //delete that line
               deleteFileLine(filePath, dataPoint);
               
               //print message 
               printf("\nData deleted.\n");
            }
            
            break;
         case 5:
            //open the file to read
            fp = fopen(filePath, "r");
            
            //print data points to a file
            exportFile(fp, name);
            
            //close fp
            fclose(fp);
            
            //print message
            printf("\nFile exported to folder above program folder.\n");
            
            break;
         default:
            printf("\nPlease enter a valid menu option\n");
            break;       
      }
   }      
}