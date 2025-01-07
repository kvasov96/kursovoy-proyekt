#include <stdio.h>
#include <locale.h>
void data()
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
				if (j == 2) tabl[i][j] = 5 * (0 + rand() % 4);
				else if (j == 3) tabl[i][j] = 0 + rand() % 4;
				else if (j == 4) tabl[i][j] = i + 1;
				else tabl[i][j] = 0 + rand() % 6;
				fprintf(fp, "%i ", tabl[i][j]);
				if (j == 4) fprintf(fp, "\n");
			};
		};
    }
	fclose(fp);
	puts("Данные перезаписаны!");
}
void task()
{
	char* filename = "data.txt";
	int tabl[25][5];
	int a, b, c, d, e;
	FILE* fp = fopen(filename, "r");
	for (int i = 0; i < 25; ++i)
	{
		fscanf(fp, "%i %i %i %i %i \n", &tabl[i][0], &tabl[i][1], &tabl[i][2], &tabl[i][3], &tabl[i][4]);
	};
	fclose(fp);
	printf("\n №|    Забито| Пропущено|    Минуты|    Ворота|\n");
	for (int i = 0; i < 25; ++i)
	{
		printf("%2i|%10i|%10i|%10i|%10i|\n", tabl[i][4], tabl[i][0], tabl[i][1], tabl[i][2], tabl[i][3]);
	};
	printf("\nРезультат = забитые шайбы + броски по воротам - (пропущенные шайбы + штрафные минуты)\n\nМесто| № команды|    Забито| Пропущено|    Минуты|    Ворота|");
	for (int count = 0; count < 25; ++count) //сортировка по наибольшему количеству очков
	{
		for (int count2 = 25 - 2; count2 >= count; --count2)
		{
			if (tabl[count2][0] - tabl[count2][1] - tabl[count2][2] + tabl[count2][3] < tabl[count2 + 1][0] - tabl[count2 + 1][1] - tabl[count2 + 1][2] + tabl[count2 + 1][3])
			{
				a = tabl[count2][0];
				b = tabl[count2][1];
				c = tabl[count2][2];
				d = tabl[count2][3];
				e = tabl[count2][4];
				tabl[count2][0] = tabl[count2 + 1][0];
				tabl[count2][1] = tabl[count2 + 1][1];
				tabl[count2][2] = tabl[count2 + 1][2];
				tabl[count2][3] = tabl[count2 + 1][3];
				tabl[count2][4] = tabl[count2 + 1][4];
				tabl[count2 + 1][0] = a;
				tabl[count2 + 1][1] = b;
				tabl[count2 + 1][2] = c;
				tabl[count2 + 1][3] = d;
				tabl[count2 + 1][4] = e;
			};
		};
		printf("\n%5i|%10i|%10i|%10i|%10i|%10i|", count + 1, tabl[count][4], tabl[count][0], tabl[count][1], tabl[count][2], tabl[count][3]);
	};
	printf("\n\n");
}
void main0()
{
	setlocale(LC_ALL, "RUS");
	puts("1 - Запуск программы\n2 - Перезаписать файл данных");
	int cycle = 0;
	while (cycle == 0)
	{
		int operation;
		scanf("%i", &operation);
		if (operation == 1) task();
		else if (operation == 2) data();
	};
}