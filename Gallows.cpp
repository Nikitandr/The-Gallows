# include <stdio.h>
# include <stdlib.h>
# include <locale.h>
# include <Windows.h>
# include <time.h>
# include <conio.h>
# include "Functions.h"

int SoloGame(char words[][25]);
int PairGame(char words[][25]);

int main()
{
	setlocale(LC_ALL,"Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char words[35][25], *answer;

	answer = (char*)malloc(51 * sizeof(char));

	OptionSelect("�����������"); // ����� ������������� �������

	UsersAnswer("���������", "���� �� �����", answer); // ������������ �������� �����
	// ���� ������ "���������"
	if (strcmp(answer, "���������") == 0)
	{
		do
		{
			OptionSelect("����������"); // ����� ������������� �������
			// ������ ��������� ���� � ������������ ��������, ��� ���� ���� �� �����
			if (SoloGame(words))
			{
				break;
			}

			puts("\n�������� ��� �����?");
			UsersAnswer("��", "���", answer); // ������������ ��������: ������ ��� ��� ��� ���
			// ���� ������������ ������������, ��������� �����������
			if (strcmp(answer, "���") == 0)
			{
				break;
			}
		}
		while (1);
		free(answer);
	}
	// ���� ������ "���� �� �����"
	else
	{
		do
		{
			OptionSelect("����������"); // ����� ������������� �������
			// ������ ���� �� �����
			if (PairGame(words))
			{
				break;
			}

			puts("\n��� ������?");
			UsersAnswer("��", "���", answer); // ������������ ��������: ������ ��� ��� ��� ���
			// ���� ������������ ������������, ��������� �����������
			if (strcmp(answer, "���") == 0)
			{
				break;
			}
		} while (1);
		free(answer);
	}
	return 0;
}

int SoloGame(char words[][25])
{
	char *word, *ground, *top, *used;
	int stop, mistakes, increment, letter_repeated; // increment - ����� ���������� ��������� ��������� ground, ����� ��� �����������
	mistakes = increment = letter_repeated = 0; // letter_repeated - ����� ����� �������, ���� �����, �������� �������������, ��� ���� �������
	used = (char*)malloc(50 * sizeof(char));
	ground = top = used;
	// ��������� ������ "words" ������� � ����� ���������, ��� �� �� ����
	if (GetWords(words))
	{
		printf("����������� ���� ����, ��������� ��������������� �����");
		_getch();
		return 1;
	}
	srand(time(NULL));
	word = words[rand() % 29]; // �������� �� ������� "words" �������� ����� "word"
	stop = strlen(word) - 1; // stop - ���������� ������ ������, �� �� - ������ ���������
	do
	{
		stop = Draw_Solo(word, top, ground, &mistakes, stop, increment, &letter_repeated); // ������ ������ � ��������
		letter_repeated = 0;
		// ������ ��������� ����� ����� 0, ���� ��� ����� ��������, � 404, ���� ���� ��������� ������������ ���������� ������
		if (stop && (stop != 404))
		{
			OptionSelect("����������"); // ����� ������������� �������
			printf("������� �����: ");
			do
			{
				*top = tolower(_getch()); // ��� ��������� ������ ���� ���� ������������ ���������� � ������� ��������
			} 
			while (*top == '\r'); // ��������, ��� ������������ �� ����� Enter
			printf("%c\n\n", *top);
			Iterating(4, top, ground, increment, &letter_repeated); // ���������, ���� �� ��� ������� ����� �����
			// ���� ����� ����� �� ��������� �����, �� ��������� ����������� ��
			if (!letter_repeated)
			{
				top++;
			}
			// ���� ����� ����� ��������� �����, �� ��������� �� ����������� ��
			else
			{
				puts("!�� ��� ������� ��� �����!\n");
			}
		}
	}
	while (stop && (stop != 404));
	// ������������� ���� ���������
	if (stop == 404)
	{
		OptionSelect("����������"); // ����� ������������� �������
		puts("������� ����� ������! ���� ��������");
	}
	else
	{
		OptionSelect("����������"); // ����� ������������� �������
		puts("�� �������� �����!");
	}
	free(used);
}

int PairGame(char words[][25])
{
	char* word, * ground, * top, *used;
	int stop, mistakes_of_the_first, mistakes_of_the_second, increment, letter_repeated, player; // increment - ����� ���������� ��������� ��������� ground, ����� ��� �����������
	mistakes_of_the_first = mistakes_of_the_second = increment = letter_repeated = player = 0; // letter_repeated - ����� ����� �������, ���� �����, �������� �������������, ��� ���� �������
	used = (char*)malloc(50 * sizeof(char));
	ground = top = used;
	// ��������� ������ "words" �������
	if (GetWords(words))
	{
		printf("����������� ���� ����, ��������� ��������������� �����");
		_getch();
		return 1;
	}
	srand(time(NULL));
	word = words[rand() % 29]; // �������� �� ������� "words" �������� ����� "word"
	stop = strlen(word) - 1; // stop - ���������� ������ ������, �� �� - ������ ���������
	do
	{
		stop = Draw_Pair(word, top, ground, player, &mistakes_of_the_first, &mistakes_of_the_second, stop, increment, &letter_repeated); // ������ ������ � ��������
		letter_repeated = 0;
		// ������ ��������� ����� ����� 0, ���� ��� ����� ��������, � 404, ���� ���� ��������� ������������ ���������� ������
		if (stop && (stop != 404))
		{
			OptionSelect("����������"); // ����� ������������� �������
			// ������ ����� ����, ��� 0 - ��� ������ �����, � 1 - ������ �����
			if (!player)
			{
				printf("������� ������� ������\n\n");
			}
			else
			{
				printf("������� ������� ������\n\n");
			}
			printf("������� �����: ");
			do
			{
				*top = tolower(_getch()); // ��� ��������� ������ ���� ���� ������������ ���������� � ������� ��������
			}
			while (*top == '\r'); // ��������, ��� ������������ �� ����� Enter
			printf("%c\n\n", *top);
			Iterating(4, top, ground, increment, &letter_repeated); // ���������, ���� �� ��� ������� ����� �����
			// ���� ����� ����� �� ��������� �����, �� ��������� ����������� ��
			if (!letter_repeated)
			{
				top++;
				player = !player;
			}
			// ���� ����� ����� ��������� �����, �� ��������� �� ����������� ��
			else
			{
				puts("!��� ����� ��� ���� �������!\n");
			}
		}
	}
	while (stop && (stop != 404));
	// ������������� ���� ���������
	if ((stop == 404) && player)
	{
		OptionSelect("����������"); // ����� ������������� �������
		puts("������� ����� ������! ���� ��������\n\n\t������� ������ �����!");
	}
	else if ((stop == 404) && (player == 0))
	{
		OptionSelect("����������"); // ����� ������������� �������
		puts("������� ����� ������! ���� ��������\n\n\t������� ������ �����!");
	}
	else if (!stop && player)
	{
		OptionSelect("����������"); // ����� ������������� �������
		if (mistakes_of_the_first > mistakes_of_the_second)
		{
			puts("������ ����� �������\n�� ������� ������ ����");
		}
		else
		{
			puts("������� ������ �����!");
		}
	}
	else if (!stop && (player == 0))
	{
		OptionSelect("����������"); // ����� ������������� �������
		if (mistakes_of_the_second > mistakes_of_the_first)
		{
			puts("������ ����� �������\n�� ������� ������ ����");
		}
		else
		{
			puts("������� ������ �����!");
		}
	}
	free(used);
}