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
	#define MAX		100		// 배열 크기
	#define NUMBER	45		// 나오는 숫자 범위
	#define DIGIT	6		// 최대 자릿수
#endif
#if DEF_STRING_GROUP
	#define ENTER_NUM		"돌릴 횟수 (최소 10 이상, ex.100): "
	#define CMD_MODE		"mode con cols=148 lines=58"
	#define CMD_TITLE		"title lotto_generator"
	#define EXCEL_CSV		"excel.csv"
	#define N_EXCEL_CSV		"excel파일 없음!\n"
	#define TABLE_COUNT		"\t\t1번째\t2번째\t3번째\t4번째\t5번째\t6번째\t\t\t\t1번째\t2번째\t3번째\t4번째\t5번째\t6번째\t\n"
	#define TABLE_NAME		"\t\t\t자리에 대한 숫자 확률\t\t\t\t\t\t\t랜덤 번호 (한 가로줄에 중복이 있어도 됨.)\n"
	#define N_PERCENT		"[%d]\t확률 :"
	#define N_COUNT			"%2d번째\t\t"
	#define WINNING			"\t★당첨됨★"
	#define HIGHEST_NUM		"\n\n가장 많이 나온 번호 :\t"
	#define RECOM_NUM		"\n일회용 추천 번호 :\t"
	#define THIS_WEEK_NUM	"\n금주의 추천 번호 :\t"
	#define MAKER			"\t\t\t\t\t\t\t\t\t\t\tMade By. ParkJG"
	#define README_TXT		"README.txt"
	#define N_README_TXT	"README.txt 파일을 열 수 없습니다!\n"
	#define PRNT_CLR_YELLOW	"%c[1;33m"
	#define PRNT_CLR_GREEN	"%c[1;32m"
	#define PRNT_CLR_RED	"%c[1;31m"
	#define PRNT_CLR_ORIGN	"%c[0m"
	#define ENTER_ERR		"10 이상의 숫자인지 확인해주세요!\n"
	#define	RENEW			"  <- 이 값에서 중복이 있을시 프로그램 재실행"
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
	
	// 인자값 검증 및 창 설정
	if			(argc >  2) { Howto(); return 0; }
	else if		(argc == 1 || strcmp(argv[1], "-o") == 0) { 
		if (argc == 2 && strcmp(argv[1], "-o") == 0) CpuOver = 1;
		printf(ENTER_NUM); scanf ("%d", &check);
		if		(check < 10) { printf(ENTER_ERR); return 0;}
		while	(getchar() != '\n') {}	// 문자 입력 방지
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
	
	// excel.csv 파일 오픈. 해당 파일은 로또 홈페이지에서 다운.
	FILE *fp = fopen(EXCEL_CSV,"r");
	if (fp == NULL) { printf(N_EXCEL_CSV); return 0; }
	
	// 파일을 읽고 result 배열에 카운트.
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
	
	// result 배열에 카운트한걸 토대로 퍼센트값 추출.
	Chasu = Weeks + 1;
	for (int i = 0; i < DIGIT; i++)
		for (int j = 0; j < NUMBER; j++) {
			aver = result[i][j] / Chasu * 100;
			result[i][j] = floor(aver + 0.5);
		}
	
	// 자리마자 숫자 퍼센테이지 나타내는 표 출력.
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
				if (j == 5) printf("%d번째까지", check*45);
				else printf(" ");
			}
	}
	printf("\n\n");
	
	// 퍼센트에 대하여 다른 100칸짜리 배열에 해당 값을 대입.
	// 예를들어 첫번째 자리에 1이 올 확률이 14%라면 100칸짜리 배열 1~14칸을 1로 넣음.
	// 그럼 첫번째자리에 2가 올 확률이 10%라면 그다음 칸인 15칸~25칸까지 2로 넣음.
	for (int i = 0; i < DIGIT; i++) {
		number = 0;
		for (int j = 0; j < NUMBER; j++)
			if (result[i][j] >= 0.5)
				for (int k = 0; k < result[i][j]; k++) { Num[i][number] = j + 1; number++; }
	}
	
	// 랜덤 값으로 백분율 배열에 대한 값을 뽑고, 추천 번호도 추출.
	// goto함수를 써서 에러나면 큰일남...
	int y = 4; // AUTO 로또 화면 출력 가로 값
	srand(time(NULL));
	recommand = (rand() % check) + 1;
	while (check--) {
		for (int n = 0; n < NUMBER; n++) {
			gotoxy(70, y+n);
			printf(N_COUNT, count++);		
			
			// goto함수를 쓰기 때문에 다시 그 자리에 print를 하려면 공백으로 지워줘야함.
			printf("                                                            ");
			gotoxy(80, y+n);
			
			// 랜덤으로 뜬 숫자에 대한 배열의 값을 출력해주고, 그 숫자가 얼마나 많이 뜨는지 HowManyCount라는 배열에 count를 함.
			for (int k = 0; k < DIGIT; k++) {
				randomNum = rand() % MAX + 1;
				temp = randomNum;
				if (Num[k][randomNum] == 0) k--;	// 0 뜨는거 제거. 
				else {
					k == 0 ? printf("      |\t") : printf("\t");
					printf(PRNT_CLR_RED,27);
					printf("%d", Num[k][temp]);
					printf(PRNT_CLR_ORIGN,27);
					HowManyCount[k][Num[k][temp]]++;
				}
			}
			if (!CpuOver) Sleep(1); // 이거 안해주면 CPU점유율 30%대로 올라감;;;느려지긴 해도 어쩔 수 없을듯.
			
			// 랜덤 추천 값이 되면 해당 배열을 복사.
			if (count - 1 == recommand)
				for (int i = 0; i < DIGIT; i++) {
					Rec[i] = Num[i][randomNum];
					if (Num[i][randomNum] == 0) i--;
				}
			
			// 랜덤값에 대한 백분율 배열을 integer로 변환해야함. strstr쓰려면 어쩔 수 없음.
			for (int i = 0; i < DIGIT; i++) itoa (Num[i][randomNum], NumtoChar[i], 10);
			
			// .csv파일에 해당 번호가 있으면 당첨된거라고 표시. 원래는 1,2,3,4,5등 모두 하려했으나 뭔가가 에러남.
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
	
	// 가장 많이 나온 번호
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
	// 일회용 추천번호
	printf(RECOM_NUM);
	for (int i = 0; i < DIGIT; i++) {
		printf(PRNT_CLR_GREEN,27);
		printf("%2d ", Rec[i]);
		printf(PRNT_CLR_ORIGN,27);
	}
	// 금주의 번호
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

// goto함수. 창의 어디로든 커서를 옮길 수 있음.
void gotoxy(int x,int y) {
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}

// 사용법 및 인트로. README.txt 파일을 읽어서 사용법 출력.
int Howto() {
	printf("\n");
	for (int i = 0; i < 99; i++) printf("/"); printf("\n");
	printf("//      ┌──┐       ┌──────────┐       ┌──┐           ┌──┐      ┌──────────┐                      //\n");
	printf("//      │  │       │  ┌────┐  │  ┌────┘  └────┐ ┌────┘  └────┐ │  ┌────┐  │                      //\n");
	printf("//      │  │       │  │    │  │  └────┐  ┌────┘ └────┐  ┌────┘ │  │    │  │                      //\n");
	printf("//      │  │       │  │    │  │       │  │           │  │      │  │    │  │                      //\n");
	printf("//      │  │       │  │    │  │       │  │           │  │      │  │    │  │                      //\n");
	printf("//      │  │       │  │    │  │       │  │           │  │      │  │    │  │                      //\n");
	printf("//      │  └─────┐ │  └────┘  │       │  │           │  │      │  └────┘  │                      //\n");
	printf("//      └────────┘ └──────────┘       └──┘           └──┘      └──────────┘______generator       //\n");
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
  if (size == 0) return 0;						// 0바이트 문자열은 숫자가 아님
  for (int i = 0; i < (int)size; i++) {
    if (s[i] == '.' || s[i] == '-' || s[i] == '+') continue;
    if (s[i] <  '0' || s[i] >  '9') return 0;	// 알파벳 등이 있으면 숫자 아님
  } return 1;									// 그밖의 경우는 숫자임
}

