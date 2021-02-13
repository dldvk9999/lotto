# LOTTO GENERATOR

- 로또 추첨기 입니다.

/*
** 사용법.
**
** 1. 먼저 로또 홈페이지에 가서 회차별 로또 당첨번호를 다운받아야합니다. (https://dhlottery.co.kr/gameResult.do?method=byWin)
** 2. 다운받은 excel.xls파일에서 1~3번 행과 A열과 T열, C~M 열을 삭제합니다.
** 3. 파일을 다른 이름으로 저장하여 같은 이름의 .csv 파일로 저장합니다.
** 4. 프로그램을 실행합니다.
** 5. 돌릴 차수를 입력합니다.
** 6. 돌릴 차수가 많아지면 많아질수록 프로그램의 완료 시간이 오래걸리지만 정확한 계산을 원한다면 다소 높게 하셔도 됩니다.
** 7. 이때 돌릴 차수는 숫자 1 입력당 기본 x45배 입니다. (100입력시 4500번 돌림)
** 8. "★당첨됨★" 표시는 회차별 당첨번호에서 5등 이상 당첨된 적이 있을때 나타나는 표시입니다.
**
**
** 콘솔 메뉴얼.
** lotto	: LOTTO_generator 실행. 실행 후 돌릴 차수 입력.
** lotto [숫자]	: LOTTO_generator를 실행하며 [숫자]값이 자동으로 돌릴 차수.
** lotto -o	: LOTTO_generator를 cpu가속화하여 사용. 속도가 매우 빨라지나 cpu점유율이 평소보다 약 10배 사용하기 때문에 성능이 저하될 수 있음. ("START_OVER.bat")
**
*/
