#define _CRT_SECURE_NO_DEPRECATE

#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

int data(); //�������� ����� � ������� � ��������
int edit(); //�������������� �����
int search(int final[25][2], int N, int count1, int count2); //����� ������, ������� ����� N ����� 
int statistics(int final[25][2], int count); //���������� ���������� �� ��������
int final(int tabl[25][5]); //�������� ����� � �������� �������� �����������

data()
{
	char* filename = "data.txt";
	FILE* fp = fopen(filename, "w");
	if (!fp)
	{
		puts("���� �� ���������!");
		system("pause");
		exit(EXIT_SUCCESS);
	}
	int tabl[25][5];
	if (fp) //���������� ������� ����������
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
	puts("������ ������������!");
	return 0;
}

edit() //�������������� ����� � �������
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
	FILE* fp2 = fopen("data.txt", "w");
	if (!fp2)
	{
		puts("���� �� ���������!");
		system("pause");
		exit(EXIT_SUCCESS);
	}
	if (fp2) //������ ��������� ������ �� ������� � ����
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
	puts("������ ������������!");
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

int finaltabl(int tabl[25][5])
{
	FILE* fpfinal = fopen("final.txt", "w");
	if (!fpfinal)
	{
		puts("���� �� ���������!");
		system("pause");
		exit(EXIT_SUCCESS);
	}
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
	if (fpfinal) //������ ������ � ����
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
	FILE* fp = fopen("data.txt", "r"); //�������� ������ � �������� ����������� � ���������� ������
	if (!fp)
	{
		puts("���� �� ���������!");
		system("pause");
		exit(EXIT_SUCCESS);
	}
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
	int cycle = 0;
	int operation;
	int N;
	for (int count = 0; count < 25; ++count) //������ ������ �� ������
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
		puts("���� �� ���������!");
		system("pause");
		exit(EXIT_SUCCESS);
	}
	finaltabl(tabl);
	for (int count = 0; count < 25; ++count)
	{
		fscanf(fpfinal, "%i %i\n", &final[count][0], &final[count][1]);
	}
	fclose(fpfinal);
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
			data();
			for (int i = 0; i < 25; ++i)
			{
				fscanf(fp, "%i %i %i %i %i \n", &tabl[i][0], &tabl[i][1], &tabl[i][2], &tabl[i][3], &tabl[i][4]);
			}
			finaltabl(tabl);
		}
		else if (operation == 6) //�������������� ������
		{
			FILE* fp = fopen("data.txt", "r");
			if (!fp)
			{
				puts("���� �� ���������!");
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