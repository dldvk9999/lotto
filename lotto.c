#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#define DEF_INTEGER_GROUP	1
#define DEF_STRING_GROUP	1

#if DEF_INTEGER_GROUP
	#define MAX		100		// �迭 ũ��
	#define NUMBER	45		// ������ ���� ����
	#define DIGIT	6		// �ִ� �ڸ���
#endif
#if DEF_STRING_GROUP
	#define ENTER_NUM		"���� Ƚ�� (�ּ� 10 �̻�, ex.100): "
	#define CMD_MODE		"mode con cols=148 lines=58"
	#define CMD_TITLE		"title lotto_generator"
	#define EXCEL_CSV		"excel.csv"
	#define N_EXCEL_CSV		"excel���� ����!\n"
	#define TABLE_COUNT		"\t\t1��°\t2��°\t3��°\t4��°\t5��°\t6��°\t\t\t\t1��°\t2��°\t3��°\t4��°\t5��°\t6��°\t\n"
	#define TABLE_NAME		"\t\t\t�ڸ��� ���� ���� Ȯ��\t\t\t\t\t\t\t���� ��ȣ (�� �����ٿ� �ߺ��� �־ ��.)\n"
	#define N_PERCENT		"[%d]\tȮ�� :"
	#define N_COUNT			"%2d��°\t\t"
	#define WINNING			"\t�ڴ�÷�ʡ�"
	#define HIGHEST_NUM		"\n\n���� ���� ���� ��ȣ :\t"
	#define RECOM_NUM		"\n��ȸ�� ��õ ��ȣ :\t"
	#define THIS_WEEK_NUM	"\n������ ��õ ��ȣ :\t"
	#define MAKER			"\t\t\t\t\t\t\t\t\t\t\tMade By. ParkJG"
	#define README_TXT		"README.txt"
	#define N_README_TXT	"README.txt ������ �� �� �����ϴ�!\n"
	#define PRNT_CLR_YELLOW	"%c[1;33m"
	#define PRNT_CLR_GREEN	"%c[1;32m"
	#define PRNT_CLR_RED	"%c[1;31m"
	#define PRNT_CLR_ORIGN	"%c[0m"
	#define ENTER_ERR		"10 �̻��� �������� Ȯ�����ּ���!\n"
	#define	RENEW			"  <- �� ������ �ߺ��� ������ ���α׷� �����"
#endif

int		Num[DIGIT][MAX];
int		HowManyCount[DIGIT][NUMBER];
int		Howto();
int		isStringDouble(char *s);
double	result[DIGIT][NUMBER];
void	gotoxy(int x,int y);

int main(int argc, char *argv[]) {
	int		number = 0, count = 1, check = 0, Chasu = 0, Weeks = 0, flag = 0, CpuOver = 0;
	int		randomNum = 0, jackpot = 0, dangchum = 0, recommand = 0, temp = 0;
	int		Rec[10];
	char	buff[MAX];
	char	NumtoChar[10][10];
	double 	aver = 0;
	
	// ���ڰ� ���� �� â ����
	if			(argc >  2) { Howto(); return 0; }
	else if		(argc == 1 || strcmp(argv[1], "-o") == 0) { 
		if (argc == 2 && strcmp(argv[1], "-o") == 0) CpuOver = 1;
		printf(ENTER_NUM); scanf ("%d", &check);
		if		(check < 10) { printf(ENTER_ERR); return 0;}
		while	(getchar() != '\n') {}	// ���� �Է� ����
	}
	else	{
		if		(!isStringDouble(argv[1])) { Howto(); return 0; }
		else	{
			check = atoi(argv[1]);
			if	(check < 10) { printf(ENTER_ERR); return 0;}
		}
	}
	system(CMD_MODE);
	system(CMD_TITLE);
	printf(PRNT_CLR_ORIGN,27);
	
	// excel.csv ���� ����. �ش� ������ �ζ� Ȩ���������� �ٿ�.
	FILE *fp = fopen(EXCEL_CSV,"r");
	if (fp == NULL) { printf(N_EXCEL_CSV); return 0; }
	
	// ������ �а� result �迭�� ī��Ʈ.
	fscanf(fp, "%d,", &Weeks);
	flag = 1; Chasu = Weeks + 1;
	while(--Chasu) {
		if	(flag != 1) fscanf(fp, "%d,", &temp);
		for (int i = 0; i < 5; i++) {
			fscanf(fp, "%d,", &number);
			result[i][number-1]++;
		}
		fscanf(fp, "%d\n", &number);
		result[DIGIT-1][number-1]++; flag = 0;
	}
	fclose(fp);
	
	// result �迭�� ī��Ʈ�Ѱ� ���� �ۼ�Ʈ�� ����.
	Chasu = Weeks + 1;
	for (int i = 0; i < DIGIT; i++)
		for (int j = 0; j < NUMBER; j++) {
			aver = result[i][j] / Chasu * 100;
			result[i][j] = floor(aver + 0.5);
		}
	
	// �ڸ����� ���� �ۼ������� ��Ÿ���� ǥ ���.
	printf("\n"); printf(TABLE_NAME); printf(TABLE_COUNT);
	for (int i = 0; i < 125; i++) { printf("="); if (i == 64) for (int j = 0; j < 21; j++) printf(" "); } 
	printf("\n");
	for (int i = 0; i < NUMBER; i++) {
		printf(N_PERCENT, i+1);
		for (int j = 0; j < DIGIT; j++)
			if (result[j][i] >= 0.5) {
				printf(PRNT_CLR_YELLOW,27);
				printf("\t%.f%%", result[j][i]);
				printf(PRNT_CLR_ORIGN,27);
			} else printf("\t%.f%%", result[j][i]);
		printf("\t|\n");
	}
	for (int i = 0; i < 125; i++) { 
		printf("="); 
		if (i == 64) 
			for (int j = 0; j < 11; j++) {
				if (j == 5) printf("%d��°����", check*45);
				else printf(" ");
			}
	}
	printf("\n\n");
	
	// �ۼ�Ʈ�� ���Ͽ� �ٸ� 100ĭ¥�� �迭�� �ش� ���� ����.
	// ������� ù��° �ڸ��� 1�� �� Ȯ���� 14%��� 100ĭ¥�� �迭 1~14ĭ�� 1�� ����.
	// �׷� ù��°�ڸ��� 2�� �� Ȯ���� 10%��� �״��� ĭ�� 15ĭ~25ĭ���� 2�� ����.
	for (int i = 0; i < DIGIT; i++) {
		number = 0;
		for (int j = 0; j < NUMBER; j++)
			if (result[i][j] >= 0.5)
				for (int k = 0; k < result[i][j]; k++) { Num[i][number] = j + 1; number++; }
	}
	
	// ���� ������ ����� �迭�� ���� ���� �̰�, ��õ ��ȣ�� ����.
	// goto�Լ��� �Ἥ �������� ū�ϳ�...
	int y = 4; // AUTO �ζ� ȭ�� ��� ���� ��
	srand(time(NULL));
	recommand = (rand() % check) + 1;
	while (check--) {
		for (int n = 0; n < NUMBER; n++) {
			gotoxy(70, y+n);
			printf(N_COUNT, count++);		
			
			// goto�Լ��� ���� ������ �ٽ� �� �ڸ��� print�� �Ϸ��� �������� ���������.
			printf("                                                            ");
			gotoxy(80, y+n);
			
			// �������� �� ���ڿ� ���� �迭�� ���� ������ְ�, �� ���ڰ� �󸶳� ���� �ߴ��� HowManyCount��� �迭�� count�� ��.
			for (int k = 0; k < DIGIT; k++) {
				randomNum = rand() % MAX + 1;
				temp = randomNum;
				if (Num[k][randomNum] == 0) k--;	// 0 �ߴ°� ����. 
				else {
					k == 0 ? printf("      |\t") : printf("\t");
					printf(PRNT_CLR_RED,27);
					printf("%d", Num[k][temp]);
					printf(PRNT_CLR_ORIGN,27);
					HowManyCount[k][Num[k][temp]]++;
				}
			}
			if (!CpuOver) Sleep(1); // �̰� �����ָ� CPU������ 30%��� �ö�;;;�������� �ص� ��¿ �� ������.
			
			// ���� ��õ ���� �Ǹ� �ش� �迭�� ����.
			if (count - 1 == recommand)
				for (int i = 0; i < DIGIT; i++) {
					Rec[i] = Num[i][randomNum];
					if (Num[i][randomNum] == 0) i--;
				}
			
			// �������� ���� ����� �迭�� integer�� ��ȯ�ؾ���. strstr������ ��¿ �� ����.
			for (int i = 0; i < DIGIT; i++) itoa (Num[i][randomNum], NumtoChar[i], 10);
			
			// .csv���Ͽ� �ش� ��ȣ�� ������ ��÷�ȰŶ�� ǥ��. ������ 1,2,3,4,5�� ��� �Ϸ������� ������ ������.
			FILE *fp = fopen(EXCEL_CSV,"r");
			if (fp == NULL) { printf(N_EXCEL_CSV); return 0; }
			fseek(fp, 0, SEEK_SET);
			while (fgets(buff, MAX, fp)) {
				for (int i = 0; i < DIGIT; i++)
					if (strstr(buff, NumtoChar[i]) != NULL) jackpot++;
				if (jackpot == DIGIT) { printf(WINNING); break; } 
				jackpot = 0;
			}
			fclose(fp); printf("\n");
		}
	}
	
	// ���� ���� ���� ��ȣ
	printf(HIGHEST_NUM);
	temp = 0;
	for (int i = 0; i < DIGIT; i++) {
		for (int j = 1; j < NUMBER; j++)
			if (temp < HowManyCount[i][j]) temp = j;
		printf(PRNT_CLR_GREEN,27);
		printf("%2d ", temp);
		printf(PRNT_CLR_ORIGN,27);
	}
	printf(RENEW);
	// ��ȸ�� ��õ��ȣ
	printf(RECOM_NUM);
	for (int i = 0; i < DIGIT; i++) {
		printf(PRNT_CLR_GREEN,27);
		printf("%2d ", Rec[i]);
		printf(PRNT_CLR_ORIGN,27);
	}
	// ������ ��ȣ
	printf(THIS_WEEK_NUM);
	for (int i = 0; i < DIGIT; i++) {
		srand(Weeks);
		printf(PRNT_CLR_GREEN,27);
		printf("%2d ", Num[i][(rand()%NUMBER)+1]);
		printf(PRNT_CLR_ORIGN,27);
	}
	printf(MAKER);
	printf("\n\n");
	system("pause"); return 0;
}

// goto�Լ�. â�� ���ε� Ŀ���� �ű� �� ����.
void gotoxy(int x,int y) {
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}

// ���� �� ��Ʈ��. README.txt ������ �о ���� ���.
int Howto() {
	printf("\n");
	for (int i = 0; i < 99; i++) printf("/"); printf("\n");
	printf("//      ��������       ������������������������       ��������           ��������      ������������������������                      //\n");
	printf("//      ��  ��       ��  ������������  ��  ������������  ������������ ������������  ������������ ��  ������������  ��                      //\n");
	printf("//      ��  ��       ��  ��    ��  ��  ������������  ������������ ������������  ������������ ��  ��    ��  ��                      //\n");
	printf("//      ��  ��       ��  ��    ��  ��       ��  ��           ��  ��      ��  ��    ��  ��                      //\n");
	printf("//      ��  ��       ��  ��    ��  ��       ��  ��           ��  ��      ��  ��    ��  ��                      //\n");
	printf("//      ��  ��       ��  ��    ��  ��       ��  ��           ��  ��      ��  ��    ��  ��                      //\n");
	printf("//      ��  �������������� ��  ������������  ��       ��  ��           ��  ��      ��  ������������  ��                      //\n");
	printf("//      �������������������� ������������������������       ��������           ��������      ������������������������______generator       //\n");
	for (int i = 0; i < 99; i++) printf("/"); printf("\n\n");
	FILE *fp;
	char buff[MAX];
	fp = fopen(README_TXT,"r");
	if (fp == NULL) { printf(N_README_TXT); return 0; }
	while(fgets(buff, MAX, fp)) {
		if	 (strcmp(buff, "\0") == 0) break;
		else printf("%s", buff);
	}
	fclose(fp);
}

int isStringDouble(char *s) {
  size_t size = strlen(s);
  if (size == 0) return 0;						// 0����Ʈ ���ڿ��� ���ڰ� �ƴ�
  for (int i = 0; i < (int)size; i++) {
    if (s[i] == '.' || s[i] == '-' || s[i] == '+') continue;
    if (s[i] <  '0' || s[i] >  '9') return 0;	// ���ĺ� ���� ������ ���� �ƴ�
  } return 1;									// �׹��� ���� ������
}

