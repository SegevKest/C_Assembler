#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "helperFunctions.h"
#include "macroNode.h"
#include "validations.h"
#include "firstPass.h"



#define MIN_NUM_OF_ARGS 2
#define TRUE 1      
#define FALSE 0
#define LINE_LENGTH 81
#define NAME_LENGTH 70
#define MACRO_MAX_LENGTH 80


//int checkForValidArgs(int argc);
char* handleSingleFile(char* filePath);
char* getSingleLineFromFile(FILE* filePointer);
char* getFileName(char* filePath);
FILE* createNewFileForOutPut(char* newFileName);


char* handleSingleFile(char* filePath) {

    int foundMacro = FALSE, startIndex = 0, indexOfFirstSpace, indexOfLastCharInRow;

    macroTable* macroList = NULL;

    FILE* filePointer;
    FILE* outPutFilePointer;
    macroTable* currMacro;

    char currLine[LINE_LENGTH];
    char* macroContent;
    char* fileName;
    char* newMacroName;
    char* nameOfPossibleMacro;

    char* fullFilePath = malloc(sizeof(filePath) + 3);
    
    if (fullFilePath != NULL) {
        strcpy(fullFilePath, filePath);
        strcat(fullFilePath,".as");
        filePointer = fopen(fullFilePath, "r");
    }

    if (filePointer == NULL) {
        printf("File pointer received is an ERROR");
        return 0;
    }

    // get the file name of the original file
    fileName = getFileName(filePath);
    // The new file pointer
    outPutFilePointer = createNewFileForOutPut(fileName);
    
    // Iterate on the File - until we will receive EOF
    while (fgets(currLine, LINE_LENGTH, filePointer)) {

        // handle each line
        printf("%s", currLine);

            // outside definition of macro
            indexOfFirstSpace = returnFirstIndexOfChar(currLine, ' ');
            
            if (indexOfFirstSpace >=0 )
                nameOfPossibleMacro = subString(currLine, 0, indexOfFirstSpace);
            else
                nameOfPossibleMacro = subString(currLine, 0, strlen(currLine));

            // check if it an existing macro
            if (isExistMacro(macroList, getTrimmedCodeRow(nameOfPossibleMacro)))
            {
                // This is an existing macro. Get the content of it and insert to the new File
                macroContent = getContentOfMacro(macroList, nameOfPossibleMacro);

                // insert the new macro content to the output file
                fputs(macroContent, outPutFilePointer);
            }
            else
            {
                if (strcmp(nameOfPossibleMacro, "macro") == 0) {
                    // if it is 0 - then there is a new definition of a new macro
                    foundMacro = TRUE;

                    indexOfLastCharInRow = returnFirstIndexOfChar(currLine, '\n');
                    newMacroName = subString(currLine, indexOfFirstSpace + 1, indexOfLastCharInRow);

                    // insert the new content to the macroList
                    insertNewMacroName( macroList, newMacroName);
                }
                else
                {
                    // inside definition of a macro
                    if (foundMacro == TRUE && strcmp(getTrimmedCodeRow(currLine), "endm") != 0) {

                        // nameOfPossibleMacro is the last found macro
                        insertNewMacroContent(macroList, nameOfPossibleMacro, getTrimmedCodeRow(currLine));
                    }
                    else
                    {
                        // else - no macro - regular line
                        foundMacro = FALSE;
                        if (strcmp(getTrimmedCodeRow(currLine), "endm") != 0) {

                            // if the line is not end - regular line insert to original file
                            fputs(currLine, outPutFilePointer);
                        }
                        else {
                            // this is end of macro definition - leave it and dont add to output file
                        }
                    }
   
                }
            }
    }
  
    fclose(outPutFilePointer);
  
    return fileName;
    //free(newMacroName);
    //free(currLine);
    //free(nameOfPossibleMacro);

}

// This method will get the file pointer and will return the next Line to analyize
char* getSingleLineFromFile(FILE* filePointer ) {

    int indexOfNewLine;

    char currLine[LINE_LENGTH];

    fgets(currLine, LINE_LENGTH, filePointer);

    //strcpy(currLine, fseek(filePointer, returnFirstIndexOfChar(filePointer,'\n'), SEEK_SET));
  
    return currLine;
}

// This method will get the file  name received and extract the name of it to all other files
char* getFileName(char* filePath) {
    
    int indexOfLastDot;
    char* fileName;

    //indexOfLastDot = returnFirstIndexOfChar(filePath,'.');

    //fileName = subString(filePath, 0, indexOfLastDot);
    fileName = subString(filePath, 0, strlen(filePath));

    return fileName;

}

// This function will create the new additional File for the output
FILE* createNewFileForOutPut(char* newFileName) {

    FILE* newFilePointer = NULL;
    char* finishOfFile = ".am";
    char* finalFileName = (char*)malloc(sizeof(newFileName));

    if (finalFileName != NULL) {
        // new final name will get the newFileName before concating 
        strcpy(finalFileName, newFileName);

        // concat the endOfFile - '.am'
        strcat(finalFileName, finishOfFile);

        // create the file
        newFilePointer = fopen(finalFileName, "a");
    }
    else
        printf("Error while creating the new File for the output");


    return newFilePointer;
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





// this main should be located in the mainProgramfile
//int main() {
////
//    int validArgs;
//
//    char* fileNameToPass;
//
////    //validArgs = checkForValidArgs(argc);
//    fileNameToPass = handleSingleFile("test");
//
//    
//
//    return 0;
//}

