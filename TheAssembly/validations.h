#pragma once
#ifndef __validations_H
#define __validations_H


int isCommentLine(char* rowFromCode);
int isWhiteSpacesLine(char* rowFromCode);

int isRowContainSymbol(char* rowFromCode);
int isValidNameOfSymbol(char* symbolFromLine);

int isDirectiveLine(char* rowFromCode);
int isActionLine(char* rowFromCode);

int isValidRegister(char* rgstrFromLine);

int validateRowOfCode(char** arrayOfArgumentFromCode, int lengthOfArr);
#endif