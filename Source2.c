#define _CRT_SECURE_NO_DEPRECATE

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

int data(); //создание файла с данными о командах
int edit(); //редактирование файла
int search(int final[25][2], int N, int count1, int count2); //поиск команд, имеющих более N очков 
int statistics(int final[25][2], int count); //вычисление статистики по командам
int final(int tabl[25][5]); //создание файла с итоговой таблицей результатов

data()
{
	char* filename = "data.txt";
	FILE* fp = fopen(filename, "w");
	if (!fp)
	{
		puts("Файл не обнаружен!");
		system("pause");
		exit(EXIT_SUCCESS);
	}
	int tabl[25][5];
	if (fp) //заполнение таблицы значениями
	{
		for (int i = 0; i < 25; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (j == 2) tabl[i][j] = 0 + rand() % 2;
				else if (j == 3) tabl[i][j] = 0 + rand() % 4;
				else if (j == 4) tabl[i][j] = i + 1;
				else tabl[i][j] = 0 + rand() % 6;
				fprintf(fp, "%i ", tabl[i][j]);
				if (j == 4) fprintf(fp, "\n");
			}
		}
	}
	fclose(fp);
	puts("Данные перезаписаны!");
	return 0;
}

edit() //редактирование файла с данными
{
	FILE* fp1 = fopen("data.txt", "a+t");
	if (!fp1)
	{
		puts("Файл не обнаружен!");
		system("pause");
		exit(EXIT_SUCCESS);
	}
	int row, col, new;
	printf("Редактирование\nВведите номер команды (1 - 25): ");
	scanf("%i", &row);
	printf("\nВведите значение(0 - Забито, 1 - Пропущено, 2 - Штрафные, 3 - Удары по воротам), которое нужно изменить: ");
	scanf("%i", &col);
	printf("\nВведите новое значение ячейки: ");
	scanf("%i", &new);
	int tabl[25][5];
	for (int i = 0; i < 25; ++i) //запись данных из файла в массив
	{
		fscanf(fp1, "%i %i %i %i %i \n", &tabl[i][0], &tabl[i][1], &tabl[i][2], &tabl[i][3], &tabl[i][4]);
	}
	fclose(fp1);
	FILE* fp2 = fopen("data.txt", "w");
	if (!fp2)
	{
		puts("Файл не обнаружен!");
		system("pause");
		exit(EXIT_SUCCESS);
	}
	if (fp2) //запись изменённых данных из массива в файл
	{
		for (int i = 0; i < 25; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (i == row - 1 && j == col)
				{
					tabl[i][j] = new;
				}
				else
				{
					tabl[i][j] = tabl[i][j];
				}
				fprintf(fp2, "%i ", tabl[i][j]);
				if (j == 4) fprintf(fp2, "\n");
			}
		}
	}
	fclose(fp2);
	puts("Данные перезаписаны!");
	return 0;
}

int search(int final[25][2], int N, int count1, int count2)
{
	int found[25][2];
	for (int count = 0; count < 25; ++count)
	{
		if (final[count][0] > N)
		{
			found[count][0] = final[count][0];
			found[count][1] = final[count][1];
		}
		else
		{
			found[count][0] = 0;
			found[count][1] = 0;
		}
	}
	return found[count1][count2];
}

int statistics(int final[25][2], int count)
{
	int stats[4];
	int sum = 0;
	int min = final[0][0];
	int minpos;
	for (int count = 0; count < 25; ++count)
	{
		sum += final[count][0]; //вычисление общей суммы очков
		if (final[count][0] < min)
		{
			min = final[count][0]; //вычисление команды с минимальным количеством очков
			minpos = final[count][1] - 1; // позиция команды с минимальным количеством очков
		}
	}
	int avg = (int)((float)sum / 25); //вычисление среднего результата по командам
	stats[0] = sum;
	stats[1] = min;
	stats[2] = minpos;
	stats[3] = avg;
	return stats[count];
}

int finaltabl(int tabl[25][5])
{
	FILE* fpfinal = fopen("final.txt", "w");
	if (!fpfinal)
	{
		puts("Файл не обнаружен!");
		system("pause");
		exit(EXIT_SUCCESS);
	}
	int sort_a, sort_b;
	int final[25][2];
	for (int count = 0; count < 25; ++count) //вычисление итоговых очков по формуле и занесение их в таблицу
	{
		final[count][0] = 3 * tabl[count][0] + 3 * tabl[count][3] - tabl[count][1] + 2 * tabl[count][2];
		final[count][1] = tabl[count][4];
	}
	for (int count = 0; count < 25; ++count) //сортировка по наибольшему количеству очков
	{
		for (int count2 = 25 - 2; count2 >= count; --count2)
		{
			if (final[count2][0] < final[count2 + 1][0])
			{
				sort_a = final[count2][0];
				sort_b = final[count2][1];
				final[count2][0] = final[count2 + 1][0];
				final[count2][1] = final[count2 + 1][1];
				final[count2 + 1][0] = sort_a;
				final[count2 + 1][1] = sort_b;
			}
		}
	}
	if (fpfinal) //запись данных в файл
	{
		for (int count = 0; count < 25; ++count)
		{
			fprintf(fpfinal, "%i %i\n", final[count][0], final[count][1]);
		}
	}
	fclose(fpfinal);
	return 0;
}

void main()
{
	setlocale(LC_ALL, "RUS");
	FILE* fp = fopen("data.txt", "r"); //открытие файлов с таблицей результатов и названиями команд
	if (!fp)
	{
		puts("Файл не обнаружен!");
		system("pause");
		exit(EXIT_SUCCESS);
	}
	FILE* fpteams = fopen("teams.txt", "r");
	if (!fpteams)
	{
		puts("Файл не обнаружен!");
		system("pause");
		exit(EXIT_SUCCESS);
	}
	int tabl[25][5];
	char teams[25][11];
	int final[25][2];
	int cycle = 0;
	int operation;
	int N;
	for (int count = 0; count < 25; ++count) //чтение данных из файлов
	{
		fscanf(fpteams, "%s\n", &teams[count]);
	}
	fclose(fpteams);
	for (int i = 0; i < 25; ++i)
	{
		fscanf(fp, "%i %i %i %i %i \n", &tabl[i][0], &tabl[i][1], &tabl[i][2], &tabl[i][3], &tabl[i][4]);
	}
	fclose(fp);
	FILE* fpfinal = fopen("final.txt", "r");
	if (!fpfinal)
	{
		puts("Файл не обнаружен!");
		system("pause");
		exit(EXIT_SUCCESS);
	}
	finaltabl(tabl);
	for (int count = 0; count < 25; ++count)
	{
		fscanf(fpfinal, "%i %i\n", &final[count][0], &final[count][1]);
	}
	fclose(fpfinal);
	puts("1 - Вывод таблицы результатов\n2 - Вывод итоговой таблицы\n3 - Поиск команд, имеющих более N очков\n4 - Статистика по командам\n5 - Перезапись данных\n6 - Редактирование данных\n");
	while (cycle == 0)
	{
		scanf("%i", &operation);
		if (operation == 1) //показ таблицы результатов
		{
			printf("\n №|    Забито| Пропущено|     Штраф|    Ворота|Имя Команды\n");
			for (int i = 0; i < 25; ++i)
			{
				printf("%2i|%10i|%10i|%10i|%10i|%s\n", tabl[i][4], tabl[i][0], tabl[i][1], tabl[i][2], tabl[i][3], teams[i]);
			}
			printf("\n");
		}
		if (operation == 2) //показ таблицы с итоговыми очками
		{
			printf("\nРезультат = 3 * забитые шайбы + 3 * броски по воротам + 2 * шайбы в штрафные минуты - пропущенные шайбы\n\nМесто| № команды|      Итог|Имя Команды");
			for (int count = 0; count < 25; ++count)
			{
				printf("\n%5i|%10i|%10i|%s", count + 1, final[count][1], final[count][0], teams[final[count][1] - 1]);
			}
			printf("\n\n");
		}
		if (operation == 3) //поиск команд
		{
			puts("\nПоиск команд, имеющих более N очков: ");
			scanf("%i", &N);
			printf("\nМесто| № команды|      Итог|Имя Команды");
			for (int count = 0; count < 25; ++count)
			{
				if (search(final, N, count, 1) != 0)
				{
					printf("\n%5i|%10i|%10i|%s", count + 1, search(final, N, count, 1), search(final, N, count, 0), teams[final[count][1] - 1]);
				}
			}
			printf("\n\n");
		}
		if (operation == 4) //статистика по командам
		{
			printf("\n\nСтатистика\nСуммарное кол-во очков по всем командам: %i\nСреднее кол-во очков по всем командам: %i\nМинимальное количество очков: %i у %s\n\n", statistics(final, 0), statistics(final, 3), statistics(final, 1), teams[statistics(final, 2)]);
		}
		else if (operation == 5) //перезапись данных
		{
			FILE* fp = fopen("data.txt", "r");
			if (!fp)
			{
				puts("Файл не обнаружен!");
				system("pause");
				exit(EXIT_SUCCESS);
			}
			data();
			for (int i = 0; i < 25; ++i)
			{
				fscanf(fp, "%i %i %i %i %i \n", &tabl[i][0], &tabl[i][1], &tabl[i][2], &tabl[i][3], &tabl[i][4]);
			}
			finaltabl(tabl);
		}
		else if (operation == 6) //редактирование данных
		{
			FILE* fp = fopen("data.txt", "r");
			if (!fp)
			{
				puts("Файл не обнаружен!");
				system("pause");
				exit(EXIT_SUCCESS);
			}
			edit();
			for (int i = 0; i < 25; ++i)
			{
				fscanf(fp, "%i %i %i %i %i \n", &tabl[i][0], &tabl[i][1], &tabl[i][2], &tabl[i][3], &tabl[i][4]);
			}
			finaltabl(tabl);
		}
	}
}