#include <stdio.h>
#include <locale.h>
void data() //�������� ����� � �������
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
			};
		};
	}
	fclose(fp);
	puts("������ ������������!");
}
void edit() //�������������� ����� � �������
{
	FILE* fp1 = fopen("data.txt", "a+t");
	int x, y, z;
	printf("��������������\n������� ����� ������� (1 - 25): ");
	scanf("%i", &x);
	printf("\n������� ��������(0 - ������, 1 - ���������, 2 - ��������, 3 - ����� �� �������), ������� ����� ��������: ");
	scanf("%i", &y);
	printf("\n������� ����� �������� ������: ");
	scanf("%i", &z);
	int tabl[25][5];
	for (int i = 0; i < 25; ++i)
	{
		fscanf(fp1, "%i %i %i %i %i \n", &tabl[i][0], &tabl[i][1], &tabl[i][2], &tabl[i][3], &tabl[i][4]);
	};
	fclose(fp1);
	FILE* fp2 = fopen("data.txt", "w");
	if (fp2)
	{
		for (int i = 0; i < 25; ++i)
		{
			for (int j = 0; j < 5; ++j)
			{
				if (i == x - 1 && j == y)
				{
					tabl[i][j] = z;
				}
				else
				{
					tabl[i][j] = tabl[i][j];
				}
				fprintf(fp2, "%i ", tabl[i][j]);
				if (j == 4) fprintf(fp2, "\n");
			};
		};
	}
	fclose(fp2);
	puts("������ ������������!");
}
void search(int m[25][2], char teams[25][10]) //����� ������, ������� ����� N �����
{
	int n, c;
	int i = 0;
	puts("\n����� ������, ������� ����� N �����: ");
	scanf("%i", &n);
	printf("\n�����| � �������|      ����|��� �������");
	for (int count = 0; count < 25; ++count)
	{
		if (m[count][0] > n)
		{
			++i;
			c = m[count][1] - 1;
			printf("\n%5i|%10i|%10i|%s", i, m[count][1], m[count][0], teams[c]);
		}
	}
}
void statistics(int scor[25][2], char teams[25][10]) //���������� �� ��������
{
	int sum = 0;
	int min = scor[0][0];
	int minpos;
	for (int count = 0; count < 25; ++count)
	{
		sum += scor[count][0];
		if (scor[count][0] < min)
		{
			min = scor[count][0];
			minpos = scor[count][1];
		}
	}
	int avg = (int)((float)sum / 25);
	printf("\n\n����������\n��������� ���-�� ����� �� ���� ��������: %i\n������� ���-�� ����� �� ���� ��������: %i\n����������� ���������� �����: %i � %s", sum, avg, min, teams[minpos - 1]);
}
void task() //����� �������, ����� ������ � �����
{
	char* filename = "data.txt";
	char* teamsname = "teams.txt";
	int tabl[25][5];
	char teams[25][10];
	int scor[25][2];
	int a, b, c;
	FILE* fp = fopen(filename, "r");
	FILE* fp1 = fopen(teamsname, "r");
	for (int count = 0; count < 25; ++count)
	{
		fscanf(fp1, "%s\n", &teams[count]);
	}
	for (int i = 0; i < 25; ++i)
	{
		fscanf(fp, "%i %i %i %i %i \n", &tabl[i][0], &tabl[i][1], &tabl[i][2], &tabl[i][3], &tabl[i][4]);
	};
	fclose(fp);
	for (int count = 0; count < 25; ++count)
	{
		scor[count][0] = 3 * tabl[count][0] + 3 * tabl[count][3] - tabl[count][1] + 2 * tabl[count][2];
		scor[count][1] = tabl[count][4];
	};
	printf("\n �|    ������| ���������|     �����|    ������|��� �������\n");
	for (int i = 0; i < 25; ++i)
	{
		printf("%2i|%10i|%10i|%10i|%10i|%s\n", tabl[i][4], tabl[i][0], tabl[i][1], tabl[i][2], tabl[i][3], teams[i]);
	};
	printf("\n��������� = 3 * ������� ����� + 3 * ������ �� ������� + 2 * ����� � �������� ������ - ����������� �����\n\n�����| � �������|      ����|��� �������");
	for (int count = 0; count < 25; ++count) //���������� �� ����������� ���������� �����
	{
		for (int count2 = 25 - 2; count2 >= count; --count2)
		{
			if (scor[count2][0] < scor[count2 + 1][0])
			{
				a = scor[count2][0];
				b = scor[count2][1];
				scor[count2][0] = scor[count2 + 1][0];
				scor[count2][1] = scor[count2 + 1][1];
				scor[count2 + 1][0] = a;
				scor[count2 + 1][1] = b;
			};
		};
		c = scor[count][1] - 1;
		printf("\n%5i|%10i|%10i|%s", count + 1, scor[count][1], scor[count][0], teams[c]);
	};
	printf("\n\n");
	search(scor, teams);
	statistics(scor, teams);
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
	};
}