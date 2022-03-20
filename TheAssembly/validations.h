#pragma once
#ifndef __validations_H
#define __validations_H


int isCommentLine(char* rowFromCode);
int isWhiteSpacesLine(char* rowFromCode);

int isRowContainSymbol(char* rowFromCode);

int isDirectiveLine(char* rowFromCode);
int isActionLine(char* rowFromCode);




#endif