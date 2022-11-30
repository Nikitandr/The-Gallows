#pragma once
int GetWords(char words[][25]);
int Draw_Solo(char* word, char* top, char* ground, int* mistakes, int stop, int increment, int* letter_repeated);
int Draw_Pair(char* word, char* top, char* ground, int player, int* mistakes_of_the_first, int* mistakes_of_the_second, int stop, int increment, int* letter_repeated);
void UsersAnswer(const char* answer_one, const char* answer_two, char users_answer[]);
void Iterating(int namber, ...);
void OptionSelect(const char* option);
int Gallows(int* mistakes);