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

	OptionSelect("Приветствие"); // вывод заготовленной надписи

	UsersAnswer("одиночный", "игра на двоих", answer); // пользователь выбирает режим
	// если выбрал "одиночный"
	if (strcmp(answer, "одиночный") == 0)
	{
		do
		{
			OptionSelect("Ограждение"); // вывод заготовленной надписи
			// запуск одиночный игры и одновременна проверка, что база слов на месте
			if (SoloGame(words))
			{
				break;
			}

			puts("\nЗагадать еще слово?");
			UsersAnswer("да", "нет", answer); // пользователь выбирает: играть еще раз или нет
			// если пользователь отказывается, программа завершается
			if (strcmp(answer, "нет") == 0)
			{
				break;
			}
		}
		while (1);
		free(answer);
	}
	// если выбрал "игра на двоих"
	else
	{
		do
		{
			OptionSelect("Ограждение"); // вывод заготовленной надписи
			// запуск игры на двоих
			if (PairGame(words))
			{
				break;
			}

			puts("\nЕще партию?");
			UsersAnswer("да", "нет", answer); // пользователь выбирает: играть еще раз или нет
			// если пользователь отказывается, программа завершается
			if (strcmp(answer, "нет") == 0)
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
	int stop, mistakes, increment, letter_repeated; // increment - будет показывать изменение указателя ground, когда это понадобится
	mistakes = increment = letter_repeated = 0; // letter_repeated - будет равно единице, если буква, введеная пользователем, уже была введена
	used = (char*)malloc(50 * sizeof(char));
	ground = top = used;
	// заполняем массив "words" словами и сразу проверяем, что он не пуст
	if (GetWords(words))
	{
		printf("Отсутствует база слов, проверьте местонахождение файла");
		_getch();
		return 1;
	}
	srand(time(NULL));
	word = words[rand() % 29]; // выбираем из массива "words" случаное слово "word"
	stop = strlen(word) - 1; // stop - количество пустых клеток, он же - сигнал остановки
	do
	{
		stop = Draw_Solo(word, top, ground, &mistakes, stop, increment, &letter_repeated); // рисуем ячейки и виселицу
		letter_repeated = 0;
		// сигнал остановки будет равен 0, если все буквы отгаданы, и 404, если было допущенно максимальное количество ошибок
		if (stop && (stop != 404))
		{
			OptionSelect("Ограждение"); // вывод заготовленной надписи
			printf("Введите букву: ");
			do
			{
				*top = tolower(_getch()); // для упрощения работы весь ввод пользователя приводится к нижнему регистру
			} 
			while (*top == '\r'); // проверка, что пользователь не нажал Enter
			printf("%c\n\n", *top);
			Iterating(4, top, ground, increment, &letter_repeated); // проверяет, была ли уже введена такая буква
			// если такая буква не вводилась ранее, то программа засчитывает ее
			if (!letter_repeated)
			{
				top++;
			}
			// если такая буква вводилась ранее, то программа не засчитывает ее
			else
			{
				puts("!ВЫ УЖЕ ВВОДИЛИ ЭТУ БУКВУ!\n");
			}
		}
	}
	while (stop && (stop != 404));
	// идентификация кода остановки
	if (stop == 404)
	{
		OptionSelect("Ограждение"); // вывод заготовленной надписи
		puts("Слишком много ошибок! Игра окончена");
	}
	else
	{
		OptionSelect("Ограждение"); // вывод заготовленной надписи
		puts("Вы отгадали слово!");
	}
	free(used);
}

int PairGame(char words[][25])
{
	char* word, * ground, * top, *used;
	int stop, mistakes_of_the_first, mistakes_of_the_second, increment, letter_repeated, player; // increment - будет показывать изменение указателя ground, когда это понадобится
	mistakes_of_the_first = mistakes_of_the_second = increment = letter_repeated = player = 0; // letter_repeated - будет равно единице, если буква, введеная пользователем, уже была введена
	used = (char*)malloc(50 * sizeof(char));
	ground = top = used;
	// заполняем массив "words" словами
	if (GetWords(words))
	{
		printf("Отсутствует база слов, проверьте местонахождение файла");
		_getch();
		return 1;
	}
	srand(time(NULL));
	word = words[rand() % 29]; // выбираем из массива "words" случаное слово "word"
	stop = strlen(word) - 1; // stop - количество пустых клеток, он же - сигнал остановки
	do
	{
		stop = Draw_Pair(word, top, ground, player, &mistakes_of_the_first, &mistakes_of_the_second, stop, increment, &letter_repeated); // рисуем ячейки и виселицу
		letter_repeated = 0;
		// сигнал остановки будет равен 0, если все буквы отгаданы, и 404, если было допущенно максимальное количество ошибок
		if (stop && (stop != 404))
		{
			OptionSelect("Ограждение"); // вывод заготовленной надписи
			// просто чтобы было, что 0 - это первый игрок, а 1 - второй игрок
			if (!player)
			{
				printf("Очередь первого игрока\n\n");
			}
			else
			{
				printf("Очередь второго игрока\n\n");
			}
			printf("Введите букву: ");
			do
			{
				*top = tolower(_getch()); // для упрощения работы весь ввод пользователя приводится к нижнему регистру
			}
			while (*top == '\r'); // проверка, что пользователь не нажал Enter
			printf("%c\n\n", *top);
			Iterating(4, top, ground, increment, &letter_repeated); // проверяет, была ли уже введена такая буква
			// если такая буква не вводилась ранее, то программа засчитывает ее
			if (!letter_repeated)
			{
				top++;
				player = !player;
			}
			// если такая буква вводилась ранее, то программа не засчитывает ее
			else
			{
				puts("!ЭТА БУКВА УЖЕ БЫЛА ВВЕДЕНА!\n");
			}
		}
	}
	while (stop && (stop != 404));
	// идентификация кода остановки
	if ((stop == 404) && player)
	{
		OptionSelect("Ограждение"); // вывод заготовленной надписи
		puts("Слишком много ошибок! Игра окончена\n\n\tПОБЕДИЛ ВТОРОЙ ИГРОК!");
	}
	else if ((stop == 404) && (player == 0))
	{
		OptionSelect("Ограждение"); // вывод заготовленной надписи
		puts("Слишком много ошибок! Игра окончена\n\n\tПОБЕДИЛ ПЕРВЫЙ ИГРОК!");
	}
	else if (!stop && player)
	{
		OptionSelect("Ограждение"); // вывод заготовленной надписи
		if (mistakes_of_the_first > mistakes_of_the_second)
		{
			puts("ВТОРОЙ ИГРОК ПОБЕДИЛ\nон отгадал больше букв");
		}
		else
		{
			puts("ПОБЕДИЛ ПЕРВЫЙ ИГРОК!");
		}
	}
	else if (!stop && (player == 0))
	{
		OptionSelect("Ограждение"); // вывод заготовленной надписи
		if (mistakes_of_the_second > mistakes_of_the_first)
		{
			puts("ПЕРВЫЙ ИГРОК ПОБЕДИЛ\nон отгадал больше букв");
		}
		else
		{
			puts("ПОБЕДИЛ ВТОРОЙ ИГРОК!");
		}
	}
	free(used);
}