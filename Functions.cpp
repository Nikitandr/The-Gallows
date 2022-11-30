# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>
# include <stdarg.h>
# include "Functions.h"

int GetWords(char words[][25])
{
	FILE* file;
	fopen_s(&file, "words.txt", "r");
	if (file != NULL)
	{
		for (int i = 0; i < 29; i++)
		{
			fgets(words[i], 20, file);
		}
		fclose(file);
	}
	else
	{
		return 1;
	}
}

int Draw_Solo(char* word, char* top, char* ground, int* mistakes, int stop, int increment, int* letter_repeated)
{
	//puts(word);
	int len, counter, letter_found;
	len = counter = strlen(word) - 1;
	letter_found = 0; // флаг - будет равняться 1, если введеная пользователем буква будет в слове
	// отрисовка верхней части ячеек под слово
	for (int i = 0; i < len; i++)
	{
		printf("--");
	}
	puts("-");
	// отрисовка стенок ячеек - ячейка заполняется пробелом, если нужная буква еще не была отгадана, или буквой, если она уже была отгадана
	for (int i = 0; i < len; i++)
	{
		// ищет в списке введенных букв такую же, как и текущая буква слова
		Iterating(6, top, ground, increment, word, &letter_found, i);
		// если такая такая буква существует, то рисует текущую букву слова в ячейку
		if (letter_found)
		{
			printf("|%c", word[i]);
			letter_found = 0;
			counter -= 1; // в эту переменную записывает количество пустых ячеек
		}
		// если такая такая буква не существует, то рисует пустую ячейку
		else
		{
			printf("| ");
		}
	}
	printf("|\n-");
	// отрисовка нижней части ячеек под слово
	for (int i = 0; i < len; i++)
	{
		printf("--");
	}
	puts("\n\nВведенные символы:");
	// вывод списка введенных символов
	Iterating(3, top, ground, increment);
	puts("\n");
	// обоработка ситуации на ошибку пользователя
	if ((ground != top) && (stop == counter) && (*letter_repeated != 1))
	{
		*mistakes += 1;
	}
	// вызыв функции, которая рисует виселицу и возвращает 0 или 404, если было допущено максимальное количество ошибок
	if (Gallows(mistakes))
	{
		return 404;
	}
	else
	{
		return counter;
	}
}

int Draw_Pair(char* word, char* top, char* ground, int player, int* mistakes_of_the_first, int* mistakes_of_the_second, int stop, int increment, int* letter_repeated)
{
	//puts(word);
	int len, counter, letter_found;
	len = counter = strlen(word) - 1;
	letter_found = 0; // флаг - будет равняться 1, если введеная пользователем буква будет в слове
	player = !player;
	// отрисовка верхней части ячеек под слово
	for (int i = 0; i < len; i++)
	{
		printf("--");
	}
	puts("-");
	// отрисовка стенок ячеек - ячейка заполняется пробелом, если нужная буква еще не была отгадана, или буквой, если она уже была отгадана
	for (int i = 0; i < len; i++)
	{
		// ищет в списке введенных букв такую же, как и текущая буква слова
		Iterating(6, top, ground, increment, word, &letter_found, i);
		// если такая такая буква существует, то рисует текущую букву слова в ячейку
		if (letter_found)
		{
			printf("|%c", word[i]);
			letter_found = 0;
			counter -= 1;	// в эту переменную записывает количество пустых ячеек
		}
		// если такая такая буква не существует, то рисует пустую ячейку
		else
		{
			printf("| ");
		}
	}
	printf("|\n-");
	// отрисовка нижней части ячеек под слово
	for (int i = 0; i < len; i++)
	{
		printf("--");
	}
	puts("\n\nВведенные символы:");
	// вывод списка введенных символов
	Iterating(3, top, ground, increment);
	puts("\n");
	// обоработка ситуации на ошибку пользователя
	if ((ground != top) && (stop == counter) && (*letter_repeated != 1) && (player == 0))
	{
		*mistakes_of_the_first += 1;
	}
	else if ((ground != top) && (stop == counter) && (*letter_repeated != 1) && (player == 1))
	{
		*mistakes_of_the_second += 1;
	}
	// вызыв функции, которая рисует виселицу и возвращает 0 или 404, если было допущено максимальное количество ошибок
	if (player == 0)
	{
		if (Gallows(mistakes_of_the_first))
		{
			return 404;
		}
		else
		{
			return counter;
		}
	}
	else
	{
		if (Gallows(mistakes_of_the_second))
		{
			return 404;
		}
		else
		{
			return counter;
		}
	}
}

void UsersAnswer(const char* answer_one, const char* answer_two, char answer[])
{
	do
	{
		printf("\nВведите \"%s\" или \"%s\"\n\n", answer_one, answer_two);
		gets_s(answer, 50); // принимает ответ пользователя
		if (strlen(answer))
		{
			int len = strlen(answer);
			for (int i = 0; i < len; i++)
			{
				answer[i] = tolower(answer[i]); // посимвольно приводит ответ к нижнему регистру
			}
		}
	} while ((strcmp(answer, answer_one) != 0) && (strcmp(answer, answer_two) != 0));
}

void Iterating(int namber, ...)
{
	va_list parameters;
	va_start(parameters, namber);
	// идентификация конкретной ситуации и пределение дальнейших действий
	if (namber == 3)
	{
		// перебор массива введенный символов и вывод каждого из них
		char* top = va_arg(parameters, char*);
		char* ground = va_arg(parameters, char*);
		int increment = va_arg(parameters, int);
		while (ground != top)
		{
			printf("%c, ", *ground);
			ground++;
			increment++;
		}
		ground -= increment;
		increment = 0;
	}
	else if (namber == 4)
	{
		// в массиве введенных символов ищет такую же, которую только что ввел пользователь
		char* top = va_arg(parameters, char*);
		char* ground = va_arg(parameters, char*);
		int increment = va_arg(parameters, int);
		int* letter_repeated = va_arg(parameters, int*);
		while (ground != top)
		{
			if (*ground == *top)
			{
				*letter_repeated = 1;
				break;
			}
			ground++;
			increment++;
		}
		ground -= increment;
		increment = 0;
	}
	else if (namber == 6)
	{
		// в массиве введенных символов ищет такую же, которую только что ввел пользователь
		char* top = va_arg(parameters, char*);
		char* ground = va_arg(parameters, char*);
		int increment = va_arg(parameters, int);
		char* word = va_arg(parameters, char*);
		int* letter_found = va_arg(parameters, int*);
		int i = va_arg(parameters, int);
		while (ground != top)
		{
			if (word[i] == *ground)
			{
				*letter_found = 1;
				break;
			}
			ground++;
			increment++;
		}
		ground -= increment;
		increment = 0;
	}
	va_end(parameters);
}

void OptionSelect(const char* option)
{
	if (option == "Приветствие")
	{
		puts("\tДобро пожаловать на виселицу\n\n\nВыбери режим:\n\n\"Одиночный\" или \"Игра на двоих\"");
	}
	else if (option == "Ограждение")
	{
		puts("\n----------------------------------------------\n");
	}
}

int Gallows(int* mistakes)
{
	if (*mistakes == 1)
	{
		printf("     | \n");
		printf("     | \n");
		printf("    _|_");
	}
	else if (*mistakes == 2)
	{
		printf("         /| \n");
		printf("        / | \n");
		printf("    ___/ _|_");
	}
	else if (*mistakes == 3)
	{
		printf("         /|\\     \n");
		printf("        / | \\    \n");
		printf("    ___/ _|_ \\___");
	}
	else if (*mistakes == 4)
	{
		printf("          |       \n");
		printf("          |       \n");
		printf("          |       \n");
		printf("          |       \n");
		printf("          |       \n");
		printf("          |       \n");
		printf("          |       \n");
		printf("         /|\\     \n");
		printf("        / | \\    \n");
		printf("    ___/ _|_ \\___");
	}
	else if (*mistakes == 5)
	{
		printf("   _______        \n");
		printf("  |       |       \n");
		printf("          |       \n");
		printf("          |       \n");
		printf("          |       \n");
		printf("          |       \n");
		printf("          |       \n");
		printf("          |       \n");
		printf("         /|\\     \n");
		printf("        / | \\    \n");
		printf("    ___/ _|_ \\___");
	}
	else if (*mistakes == 6)
	{
		printf("   _______        \n");
		printf("  |       |       \n");
		printf("  O       |       \n");
		printf("          |       \n");
		printf("          |       \n");
		printf("          |       \n");
		printf("          |       \n");
		printf("          |       \n");
		printf("         /|\\     \n");
		printf("        / | \\    \n");
		printf("    ___/ _|_ \\___");
	}
	else if (*mistakes == 7)
	{
		printf("   _______        \n");
		printf("  |       |       \n");
		printf("  O       |       \n");
		printf("  |       |       \n");
		printf("  |       |       \n");
		printf("  |       |       \n");
		printf("          |       \n");
		printf("          |       \n");
		printf("         /|\\     \n");
		printf("        / | \\    \n");
		printf("    ___/ _|_ \\___");
	}
	else if (*mistakes == 8)
	{
		printf("   _______        \n");
		printf("  |       |       \n");
		printf("  O       |       \n");
		printf(" /|       |       \n");
		printf("/ |       |       \n");
		printf("  |       |       \n");
		printf("          |       \n");
		printf("          |       \n");
		printf("         /|\\     \n");
		printf("        / | \\    \n");
		printf("    ___/ _|_ \\___");
	}
	else if (*mistakes == 9)
	{
		printf("   _______        \n");
		printf("  |       |       \n");
		printf("  O       |       \n");
		printf(" /|\\      |      \n");
		printf("/ | \\     |      \n");
		printf("  |       |       \n");
		printf("          |       \n");
		printf("          |       \n");
		printf("         /|\\     \n");
		printf("        / | \\    \n");
		printf("    ___/ _|_ \\___");
	}
	else if (*mistakes == 10)
	{
		printf("   _______        \n");
		printf("  |       |       \n");
		printf("  O       |       \n");
		printf(" /|\\      |      \n");
		printf("/ | \\     |      \n");
		printf("  |       |       \n");
		printf(" /        |       \n");
		printf("/         |       \n");
		printf("         /|\\     \n");
		printf("        / | \\    \n");
		printf("    ___/ _|_ \\___");
	}
	else if (*mistakes > 10)
	{
		printf("   _______        \n");
		printf("  |       |       \n");
		printf("  O       |       \n");
		printf(" /|\\      |      \n");
		printf("/ | \\     |      \n");
		printf("  |       |       \n");
		printf(" / \\      |      \n");
		printf("/   \\     |      \n");
		printf("         /|\\     \n");
		printf("        / | \\    \n");
		printf("    ___/ _|_ \\___");
		return 404;
	}
	return 0;
}