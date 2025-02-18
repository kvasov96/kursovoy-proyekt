#include <stdio.h>
#include <locale.h>

int data() //создание файла с данными
{
	char* filename = "data.txt";
	FILE* fp = fopen(filename, "w");
	int tabl[25][5];
	if (fp)
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

int edit() //редактирование файла с данными
{
	FILE* fp1 = fopen("data.txt", "a+t");
	int row, col, new;
	printf("Редактирование\nВведите номер команды (1 - 25): ");
	scanf("%i", &row);
	printf("\nВведите значение(0 - Забито, 1 - Пропущено, 2 - Штрафные, 3 - Удары по воротам), которое нужно изменить: ");
	scanf("%i", &col);
	printf("\nВведите новое значение ячейки: ");
	scanf("%i", &new);
	int tabl[25][5];
	for (int i = 0; i < 25; ++i)
	{
		fscanf(fp1, "%i %i %i %i %i \n", &tabl[i][0], &tabl[i][1], &tabl[i][2], &tabl[i][3], &tabl[i][4]);
	}
	fclose(fp1);
	FILE* fp2 = fopen("data.txt", "w");
	if (fp2)
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

int search(int final[25][2], char teams[25][10]) //поиск команд, имеющих более N очков
{
	int N, teamnum;
	int cycle = 0;
	puts("\nПоиск команд, имеющих более N очков: ");
	scanf("%i", &N);
	printf("\nМесто| № команды|      Итог|Имя Команды");
	for (int count = 0; count < 25; ++count)
	{
		if (final[count][0] > N)
		{
			++cycle;
			teamnum = final[count][1] - 1;
			printf("\n%5i|%10i|%10i|%s", cycle, final[count][1], final[count][0], teams[teamnum]);
		}
	}
	return 0;
}

int statistics(int final[25][2], char teams[25][10]) //статистика по командам
{
	int sum = 0;
	int min = final[0][0];
	int minpos;
	for (int count = 0; count < 25; ++count)
	{
		sum += final[count][0];
		if (final[count][0] < min)
		{
			min = final[count][0];
			minpos = final[count][1];
		}
	}
	int avg = (int)((float)sum / 25);
	printf("\n\nСтатистика\nСуммарное кол-во очков по всем командам: %i\nСреднее кол-во очков по всем командам: %i\nМинимальное количество очков: %i у %s", sum, avg, min, teams[minpos - 1]);
	return 0;
}

int task() //показ таблицы, показ итогов и поиск
{
	char* filename = "data.txt";
	char* teamsname = "teams.txt";
	int tabl[25][5];
	char teams[25][10];
	int final[25][2];
	int sort_a, sort_b, teamnum;
	FILE* fp = fopen(filename, "r");
	FILE* fp1 = fopen(teamsname, "r");
	for (int count = 0; count < 25; ++count)
	{
		fscanf(fp1, "%s\n", &teams[count]);
	}
	for (int i = 0; i < 25; ++i)
	{
		fscanf(fp, "%i %i %i %i %i \n", &tabl[i][0], &tabl[i][1], &tabl[i][2], &tabl[i][3], &tabl[i][4]);
	}
	fclose(fp);
	for (int count = 0; count < 25; ++count)
	{
		final[count][0] = 3 * tabl[count][0] + 3 * tabl[count][3] - tabl[count][1] + 2 * tabl[count][2];
		final[count][1] = tabl[count][4];
	}
	printf("\n №|    Забито| Пропущено|     Штраф|    Ворота|Имя Команды\n");
	for (int i = 0; i < 25; ++i)
	{
		printf("%2i|%10i|%10i|%10i|%10i|%s\n", tabl[i][4], tabl[i][0], tabl[i][1], tabl[i][2], tabl[i][3], teams[i]);
	}
	printf("\nРезультат = 3 * забитые шайбы + 3 * броски по воротам + 2 * шайбы в штрафные минуты - пропущенные шайбы\n\nМесто| № команды|      Итог|Имя Команды");
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
		teamnum = final[count][1] - 1;
		printf("\n%5i|%10i|%10i|%s", count + 1, final[count][1], final[count][0], teams[teamnum]);
	}
	printf("\n\n");
	search(final, teams);
	statistics(final, teams);
	return 0;
}

void main()
{
	setlocale(LC_ALL, "RUS");
	puts("1 - Запуск программы\n2 - Перезаписать файл данных\n3 - Изменить данные");
	int cycle = 0;
	while (cycle == 0)
	{
		int operation;
		scanf("%i", &operation);
		if (operation == 1) task();
		else if (operation == 2) data();
		else if (operation == 3) edit();
	}
}