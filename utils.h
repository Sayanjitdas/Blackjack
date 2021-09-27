#pragma once

int RandomNumber(int lowerBound, int upperBound);
int GetIntInput(const char* PROMPT_MESSAGE);
char GetCharInput(const char* PROMPT_MESSAGE, char validInputs[] = {}, int length = 0);
void clearScreen();