#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "macroNode.h"
#include "helperFunctions.h"



#define MIN_NUM_OF_ARGS 2
#define TRUE 1      
#define FALSE 0
#define LINE_LENGTH 81
#define NAME_LENGTH 70

//int checkForValidArgs(int argc);




void handleSingleFile(char* filePath) {

    int foundMacro = FALSE, startIndex = 0;
    FILE* filePointer;

    macroTable* currMacro;

    char currLine[ LINE_LENGTH];

    filePointer = fopen(filePath, "r");

    if (filePointer == NULL) {
        printf("File pointer received is an ERROR");
        return 0;
    }

    while () {

        if (foundMacro == TRUE) {
            // enter the contnet of this row to the array of content of the macro
            // concat the content of the macro to the array
        }
    }
   
        
}

// This method will get the file pointer and will return the next Line to analyize
char* getSingleLineFromFile(FILE* filePointer) {

    int indexOfNewLine;

    char currLine[LINE_LENGTH];

  

    return currLine;
}


char* getFileName(char* filePath) {
    int indexOfLastDot;

    indexOfLastDot = 
}

FILE* createNewFileForOutPut() {

    FILE* newFilePointer = NULL;

    newFilePointer = fopen("", "w");
}

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




int main(int argc, char* argv[]) {

    int validArgs;

    validArgs = checkForValidArgs(argc);

    handleSingleFile("test.as");
}

