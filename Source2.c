#include <stdio.h>
#include <locale.h>

int data() //�������� ����� � �������
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
	puts("������ ������������!");
	return 0;
}

int edit() //�������������� ����� � �������
{
	FILE* fp1 = fopen("data.txt", "a+t");
	int row, col, new;
	printf("��������������\n������� ����� ������� (1 - 25): ");
	scanf("%i", &row);
	printf("\n������� ��������(0 - ������, 1 - ���������, 2 - ��������, 3 - ����� �� �������), ������� ����� ��������: ");
	scanf("%i", &col);
	printf("\n������� ����� �������� ������: ");
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
	puts("������ ������������!");
	return 0;
}

int search(int final[25][2], char teams[25][10]) //����� ������, ������� ����� N �����
{
	int N, teamnum;
	int cycle = 0;
	puts("\n����� ������, ������� ����� N �����: ");
	scanf("%i", &N);
	printf("\n�����| � �������|      ����|��� �������");
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

int statistics(int final[25][2], char teams[25][10]) //���������� �� ��������
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
	printf("\n\n����������\n��������� ���-�� ����� �� ���� ��������: %i\n������� ���-�� ����� �� ���� ��������: %i\n����������� ���������� �����: %i � %s", sum, avg, min, teams[minpos - 1]);
	return 0;
}

int task() //����� �������, ����� ������ � �����
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
	printf("\n �|    ������| ���������|     �����|    ������|��� �������\n");
	for (int i = 0; i < 25; ++i)
	{
		printf("%2i|%10i|%10i|%10i|%10i|%s\n", tabl[i][4], tabl[i][0], tabl[i][1], tabl[i][2], tabl[i][3], teams[i]);
	}
	printf("\n��������� = 3 * ������� ����� + 3 * ������ �� ������� + 2 * ����� � �������� ������ - ����������� �����\n\n�����| � �������|      ����|��� �������");
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
	puts("1 - ������ ���������\n2 - ������������ ���� ������\n3 - �������� ������");
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