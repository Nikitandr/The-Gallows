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
	letter_found = 0; // ���� - ����� ��������� 1, ���� �������� ������������� ����� ����� � �����
	// ��������� ������� ����� ����� ��� �����
	for (int i = 0; i < len; i++)
	{
		printf("--");
	}
	puts("-");
	// ��������� ������ ����� - ������ ����������� ��������, ���� ������ ����� ��� �� ���� ��������, ��� ������, ���� ��� ��� ���� ��������
	for (int i = 0; i < len; i++)
	{
		// ���� � ������ ��������� ���� ����� ��, ��� � ������� ����� �����
		Iterating(6, top, ground, increment, word, &letter_found, i);
		// ���� ����� ����� ����� ����������, �� ������ ������� ����� ����� � ������
		if (letter_found)
		{
			printf("|%c", word[i]);
			letter_found = 0;
			counter -= 1; // � ��� ���������� ���������� ���������� ������ �����
		}
		// ���� ����� ����� ����� �� ����������, �� ������ ������ ������
		else
		{
			printf("| ");
		}
	}
	printf("|\n-");
	// ��������� ������ ����� ����� ��� �����
	for (int i = 0; i < len; i++)
	{
		printf("--");
	}
	puts("\n\n��������� �������:");
	// ����� ������ ��������� ��������
	Iterating(3, top, ground, increment);
	puts("\n");
	// ���������� �������� �� ������ ������������
	if ((ground != top) && (stop == counter) && (*letter_repeated != 1))
	{
		*mistakes += 1;
	}
	// ����� �������, ������� ������ �������� � ���������� 0 ��� 404, ���� ���� �������� ������������ ���������� ������
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
	letter_found = 0; // ���� - ����� ��������� 1, ���� �������� ������������� ����� ����� � �����
	player = !player;
	// ��������� ������� ����� ����� ��� �����
	for (int i = 0; i < len; i++)
	{
		printf("--");
	}
	puts("-");
	// ��������� ������ ����� - ������ ����������� ��������, ���� ������ ����� ��� �� ���� ��������, ��� ������, ���� ��� ��� ���� ��������
	for (int i = 0; i < len; i++)
	{
		// ���� � ������ ��������� ���� ����� ��, ��� � ������� ����� �����
		Iterating(6, top, ground, increment, word, &letter_found, i);
		// ���� ����� ����� ����� ����������, �� ������ ������� ����� ����� � ������
		if (letter_found)
		{
			printf("|%c", word[i]);
			letter_found = 0;
			counter -= 1;	// � ��� ���������� ���������� ���������� ������ �����
		}
		// ���� ����� ����� ����� �� ����������, �� ������ ������ ������
		else
		{
			printf("| ");
		}
	}
	printf("|\n-");
	// ��������� ������ ����� ����� ��� �����
	for (int i = 0; i < len; i++)
	{
		printf("--");
	}
	puts("\n\n��������� �������:");
	// ����� ������ ��������� ��������
	Iterating(3, top, ground, increment);
	puts("\n");
	// ���������� �������� �� ������ ������������
	if ((ground != top) && (stop == counter) && (*letter_repeated != 1) && (player == 0))
	{
		*mistakes_of_the_first += 1;
	}
	else if ((ground != top) && (stop == counter) && (*letter_repeated != 1) && (player == 1))
	{
		*mistakes_of_the_second += 1;
	}
	// ����� �������, ������� ������ �������� � ���������� 0 ��� 404, ���� ���� �������� ������������ ���������� ������
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
		printf("\n������� \"%s\" ��� \"%s\"\n\n", answer_one, answer_two);
		gets_s(answer, 50); // ��������� ����� ������������
		if (strlen(answer))
		{
			int len = strlen(answer);
			for (int i = 0; i < len; i++)
			{
				answer[i] = tolower(answer[i]); // ����������� �������� ����� � ������� ��������
			}
		}
	} while ((strcmp(answer, answer_one) != 0) && (strcmp(answer, answer_two) != 0));
}

void Iterating(int namber, ...)
{
	va_list parameters;
	va_start(parameters, namber);
	// ������������� ���������� �������� � ���������� ���������� ��������
	if (namber == 3)
	{
		// ������� ������� ��������� �������� � ����� ������� �� ���
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
		// � ������� ��������� �������� ���� ����� ��, ������� ������ ��� ���� ������������
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
		// � ������� ��������� �������� ���� ����� ��, ������� ������ ��� ���� ������������
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
	if (option == "�����������")
	{
		puts("\t����� ���������� �� ��������\n\n\n������ �����:\n\n\"���������\" ��� \"���� �� �����\"");
	}
	else if (option == "����������")
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