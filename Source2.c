#define _CRT_SECURE_NO_DEPRECATE

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

int data(int count1, int count2, int mode); //�������� ����� � ������� � ��������
int edit(int count1, int count2, int mode); //�������������� �����
int search(int final[25][2], int N, int count1, int count2); //����� ������, ������� ����� N ����� 
int statistics(int final[25][2], int count); //���������� ���������� �� ��������
int finaltabl(int tabl[25][5], int count1, int count2, int mode); //�������� ����� � �������� �������� �����������

data(int count1, int count2, int mode)
{
	int tabl[25][5];
	if (mode == 1)
	{
		FILE* fp = fopen("data.txt", "w");
		if (!fp)
		{
			puts("���� �� ���������!");
			system("pause");
			exit(EXIT_SUCCESS);
		}
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
		fclose(fp);
		return 0;
	}
	if (mode == 2)
	{
		FILE* fp1 = fopen("data.txt", "a+t");
		if (!fp1)
		{
			puts("���� �� ���������!");
			system("pause");
			exit(EXIT_SUCCESS);
		}
		for (int i = 0; i < 25; ++i)
		{
			fscanf(fp1, "%i %i %i %i %i \n", &tabl[i][0], &tabl[i][1], &tabl[i][2], &tabl[i][3], &tabl[i][4]);
		}
		return tabl[count1][count2];
	}
}

edit(int count1, int count2, int mode) //�������������� ����� � �������
{
	FILE* fp1 = fopen("data.txt", "a+t");
	if (!fp1)
	{
		puts("���� �� ���������!");
		system("pause");
		exit(EXIT_SUCCESS);
	}
	int row, col, new;
	printf("��������������\n������� ����� ������� (1 - 25): ");
	scanf("%i", &row);
	printf("\n������� ��������(0 - ������, 1 - ���������, 2 - ��������, 3 - ����� �� �������), ������� ����� ��������: ");
	scanf("%i", &col);
	printf("\n������� ����� �������� ������: ");
	scanf("%i", &new);
	int tabl[25][5];
	for (int i = 0; i < 25; ++i) //������ ������ �� ����� � ������
	{
		fscanf(fp1, "%i %i %i %i %i \n", &tabl[i][0], &tabl[i][1], &tabl[i][2], &tabl[i][3], &tabl[i][4]);
	}
	fclose(fp1);
	tabl[row - 1][col] = new;
	if (mode == 1)
	{
		FILE* fp2 = fopen("data.txt", "w");
		if (!fp2)
		{
			puts("���� �� ���������!");
			system("pause");
			exit(EXIT_SUCCESS);
		}
		if (fp2) //������ ���������� ������ �� ������� � ����
		{
			for (int i = 0; i < 25; ++i)
			{
				for (int j = 0; j < 5; ++j)
				{
					fprintf(fp2, "%i ", tabl[i][j]);
					if (j == 4) fprintf(fp2, "\n");
				}
			}
		}
		fclose(fp2);
		return 0;
	}
	if (mode == 2)
	{
		return tabl[count1][count2];
	}
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
		sum += final[count][0]; //���������� ����� ����� �����
		if (final[count][0] < min)
		{
			min = final[count][0]; //���������� ������� � ����������� ����������� �����
			minpos = final[count][1] - 1; // ������� ������� � ����������� ����������� �����
		}
	}
	int avg = (int)((float)sum / 25); //���������� �������� ���������� �� ��������
	stats[0] = sum;
	stats[1] = min;
	stats[2] = minpos;
	stats[3] = avg;
	return stats[count];
}

int finaltabl(int tabl[25][5], int count1, int count2, int mode)
{
	int sort_a, sort_b;
	int final[25][2];
	for (int count = 0; count < 25; ++count) //���������� �������� ����� �� ������� � ��������� �� � �������
	{
		final[count][0] = 3 * tabl[count][0] + 3 * tabl[count][3] - tabl[count][1] + 2 * tabl[count][2];
		final[count][1] = tabl[count][4];
	}
	for (int count = 0; count < 25; ++count) //���������� �� ����������� ���������� �����
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
	if (mode == 1)
	{
		FILE* fpfinal = fopen("final.txt", "w");
		if (!fpfinal)
		{
			puts("���� �� ���������!");
			system("pause");
			exit(EXIT_SUCCESS);
		}
		if (fpfinal) //������ ������ � ����
		{
			for (int count = 0; count < 25; ++count)
			{
				fprintf(fpfinal, "%i %i\n", final[count][0], final[count][1]);
			}
		}
		fclose(fpfinal);
	}
	if (mode == 2)
	{
		return final[count1][count2];
	}
}

void main()
{
	setlocale(LC_ALL, "RUS");
	FILE* fpteams = fopen("teams.txt", "r");
	if (!fpteams)
	{
		puts("���� �� ���������!");
		system("pause");
		exit(EXIT_SUCCESS);
	}
	int tabl[25][5];
	char teams[25][11];
	int final[25][2];
	for (int count1 = 0; count1 < 25; ++count1)
	{
		for (int count2 = 0; count2 < 5; ++count2)
		{
			tabl[count1][count2] = data(count1, count2, 2);
		}
	}
	for (int count1 = 0; count1 < 25; ++count1)
	{
		for (int count2 = 0; count2 < 2; ++count2)
		{
			final[count1][count2] = finaltabl(tabl, count1, count2, 2);
		}
	}
	for (int count = 0; count < 25; ++count) //������ ������ �� ������
	{
		fscanf(fpteams, "%s\n", &teams[count]);
	}
	fclose(fpteams);
	int cycle = 0;
	int operation;
	int N;
	puts("1 - ����� ������� �����������\n2 - ����� �������� �������\n3 - ����� ������, ������� ����� N �����\n4 - ���������� �� ��������\n5 - ���������� ������\n6 - �������������� ������\n");
	while (cycle == 0)
	{
		scanf("%i", &operation);
		if (operation == 1) //����� ������� �����������
		{
			printf("\n �|    ������| ���������|     �����|    ������|��� �������\n");
			for (int i = 0; i < 25; ++i)
			{
				printf("%2i|%10i|%10i|%10i|%10i|%s\n", tabl[i][4], tabl[i][0], tabl[i][1], tabl[i][2], tabl[i][3], teams[i]);
			}
			printf("\n");
		}
		if (operation == 2) //����� ������� � ��������� ������
		{
			printf("\n��������� = 3 * ������� ����� + 3 * ������ �� ������� + 2 * ����� � �������� ������ - ����������� �����\n\n�����| � �������|      ����|��� �������");
			for (int count = 0; count < 25; ++count)
			{
				printf("\n%5i|%10i|%10i|%s", count + 1, final[count][1], final[count][0], teams[final[count][1] - 1]);
			}
			printf("\n\n");
		}
		if (operation == 3) //����� ������
		{
			puts("\n����� ������, ������� ����� N �����: ");
			scanf("%i", &N);
			printf("\n�����| � �������|      ����|��� �������");
			for (int count = 0; count < 25; ++count)
			{
				if (search(final, N, count, 1) != 0)
				{
					printf("\n%5i|%10i|%10i|%s", count + 1, search(final, N, count, 1), search(final, N, count, 0), teams[final[count][1] - 1]);
				}
			}
			printf("\n\n");
		}
		if (operation == 4) //���������� �� ��������
		{
			printf("\n\n����������\n��������� ���-�� ����� �� ���� ��������: %i\n������� ���-�� ����� �� ���� ��������: %i\n����������� ���������� �����: %i � %s\n\n", statistics(final, 0), statistics(final, 3), statistics(final, 1), teams[statistics(final, 2)]);
		}
		else if (operation == 5) //���������� ������
		{
			FILE* fp = fopen("data.txt", "r");
			if (!fp)
			{
				puts("���� �� ���������!");
				system("pause");
				exit(EXIT_SUCCESS);
			}
			data(0, 0, 1);
			for (int count1 = 0; count1 < 25; ++count1)
			{
				for (int count2 = 0; count2 < 2; ++count2)
				{
					tabl[count1][count2] = data(count1, count2, 2);
				}
			}
			for (int count1 = 0; count1 < 25; ++count1)
			{
				for (int count2 = 0; count2 < 2; ++count2)
				{
					final[count1][count2] = finaltabl(tabl, count1, count2, 2);
				}
			}
			puts("������ ������������!");
		}
		else if (operation == 6) //�������������� ������
		{
			edit(0, 0, 1);
			for (int count1 = 0; count1 < 25; ++count1)
			{
				for (int count2 = 0; count2 < 2; ++count2)
				{
					tabl[count1][count2] = edit(count1, count2, 2);
				}
			}
			for (int count1 = 0; count1 < 25; ++count1)
			{
				for (int count2 = 0; count2 < 2; ++count2)
				{
					final[count1][count2] = finaltabl(tabl, count1, count2, 2);
				}
			}
			puts("������ ������������!");
		}
	}
}