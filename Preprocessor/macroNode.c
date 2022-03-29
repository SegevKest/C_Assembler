#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "macroNode.h"



#define NAME_LENGTH 70
#define MACRO_MAX_LENGTH 80
#define TRUE 1      
#define FALSE 0



macroTable* returnMacro(macroTable** head, char* macroNameParam);
void insertNewMacroName(macroTable** head, char* macroNameParam);
void insertNewMacroContent(macroTable** head, char* macroNameParam, char* macroRow);


//typedef struct node 
//{
//     
//    char letter;    // current Char of Macro
//	struct node *nextLetter;    // Next Char Node
//     
//} macroCharNode; 
//

typedef struct macroNode {
     
    char macroName[NAME_LENGTH];      // The name of the Macro
    char* macroContent;     // refers to the content of the Macro - all letter 
	
    struct macroNode *nextMacro;    // Pointer to next Node of Macro
     
}; 

// Insert new macro name
void insertNewMacroName(macroTable* head, char* macroNameParam){

    macroTable* ptr;
    int i = 0;

    //Noted here
    {
        //if(*head == NULL)
        //{
        //    *head = (macroTable *)malloc(sizeof(macroTable));

        //    // Insert the new name of the macro to the Macro Node 
        //    while( macroNameParam[i] != '\0'){
        //        (*head)->macroName[i] = macroNameParam[i];
        //        i++;
        //    } 
        //    while (i <= NAME_LENGTH) {
        //        (*head)->macroName[i] = NULL;
        //        i++;
        //    }
        //    
        //    (*head)->nextMacro = NULL;  //Set next node to null
        //}
        //else 
        //{
        //    ptr = *head;

        //    while( ptr->nextMacro != NULL)
        //        ptr = ptr->nextMacro;

        //    ptr->nextMacro = (macroTable *)malloc(sizeof(macroTable));
        //    ptr = ptr->nextMacro;
        //    ptr->nextMacro = NULL;  //Set next node to null

        //    // Insert the new name of the macro to the Macro Node 
        //    while( macroNameParam[i] != '\0'){
        //        ptr->macroName[i] = macroNameParam[i];
        //        i++;
        //    } 
        //    while (i <= NAME_LENGTH) {
        //        (*head)->macroName[i] = NULL;
        //        i++;
        //    }
        //}
    }

    if (head == NULL)
    {
        head = (macroTable*)malloc(sizeof(macroTable));

        // Insert the new name of the macro to the Macro Node 
        while (macroNameParam[i] != '\0') {
            head->macroName[i] = macroNameParam[i];
            i++;
        }
        while (i <= NAME_LENGTH) {
            head->macroName[i] = NULL;
            i++;
        }

        head->nextMacro = NULL;  //Set next node to null
    }
    else
    {
        ptr = head;

        while (ptr->nextMacro != NULL)
            ptr = ptr->nextMacro;

        ptr->nextMacro = (macroTable*)malloc(sizeof(macroTable));
        ptr = ptr->nextMacro;
        ptr->nextMacro = NULL;  //Set next node to null

        // Insert the new name of the macro to the Macro Node 
        while (macroNameParam[i] != '\0') {
            ptr->macroName[i] = macroNameParam[i];
            i++;
        }
        while (i <= NAME_LENGTH) {
            head->macroName[i] = NULL;
            i++;
        }
    }

    //printf("\n Macro Name inserted: %s\n", head->macroName);

}


// Insert Content - for every row of the macro from the code - use this method.
void insertNewMacroContent(macroTable** head, char* macroNameParam, char* macroRow) {
   
   int i = 0;
    //macroCharNode *pContent;
    macroTable *macroNodeToEnterContentTo = returnMacro(head,macroNameParam);

    //if(macroNodeToEnterContentTo == NULL)
    //    printf("\n Macro that return is empty.\n");
    //else
    //{
    //    pContent = (macroCharNode *)malloc(sizeof(macroCharNode));

    //    if (!pContent  )
    //       printf("\n Allocate failed - returned null.\n");

    //    while(macrorow != null ) // reached end of line
    //    {
    //        pcontent->letter = macrorow[i];
    //        pcontent->nextletter = (macrocharnode *)malloc(sizeof(macrocharnode));
    //        pcontent = pcontent->nextletter;
    //        i++;      // next cell of row
    //    }
    //}

}

// Search in linked list- return the macro if found or null if not
macroTable* returnMacro(macroTable** head, char* macroNameParam){

    macroTable *ptr = head;

    int found = FALSE, i = 0;

    while( ptr != NULL && !found ){
        
        if( strcmp(macroNameParam, ptr->macroName) == 0)
            found = TRUE;
        else
            ptr = ptr->nextMacro; 
    }

    return ptr;
}


//Print List
void displayMacroTable(const macroTable* head){

    macroTable *ptr = head;
    int i = 1;

    if(ptr == NULL)
        	printf("\nLinklist is empty.\n");
    else
    {
        printf("\nSr. No.\t\tAddress\t\tInfo\t\tLink\n");
        while (ptr != NULL)
		{
			printf("\n%d.\t\t%d\t\t%d\t\t%d\n", i, ptr, ptr->nextMacro);

			ptr = ptr->nextMacro;
			i++;
		}

    }
}


// Return a pointer to a char array contains the Macro Content
char* getContentOfMacro(macroTable** head, char* macroName){

    // get the macro Node itself
    macroTable* foundMacro = returnMacro(head,macroName);

    return foundMacro->macroContent;
}

