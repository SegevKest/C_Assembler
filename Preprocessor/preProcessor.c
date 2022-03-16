#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "macroNode.h"


#define MIN_NUM_OF_ARGS 2
#define TRUE 1      
#define FALSE 0
#define LINE_LENGTH 81
#define NAME_LENGTH 70

//int checkForValidArgs(int argc);











//int main(int argc , char *argv[]){
//
//    // int validArgs = FALSE, validInput = TRUE;
//
//    // validArgs = checkForValidArgs(argc);
//
//    // if (!validArgs)
//    //     validInput = FALSE;
//   
//    // if (validInput) {
//
//
//    // }
//
//    // else 
//    //     exit(TRUE);
//
//
//	macroTable* start = NULL;
//	int ch;
//	char name[NAME_LENGTH];
//
//	do
//	{
//		printf("\n\n\n1. Insert Last\n2. Display\n3.Exit\n");
//		printf("\nEnter your choice: ");
//		scanf("%d", &ch);
//
//
//
//		switch (ch)
//		{
//		case 1: {
//			insert_NewMacroName(&start, "Segev");
//			break;
//		}
//		case 2:
//			displayMacroTable(start);
//			break;
//		case 3:
//			exit(0);
//		default:
//			printf("\n\nInvalid choice: Please try again.\n");
//		}
//	} while (1);
//
//
//
//}

// Validate if the number of arguments received from the 
int checkForValidArgs(int argc){

    if( argc < MIN_NUM_OF_ARGS)
    {
        printf("Not a valid number of arguments\n");
        return FALSE;
    }

    //Remove this log
    //printf("valid number of arguments\n");
    return TRUE;
}




int spreadMacrosInFile(){

}


