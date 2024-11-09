#pragma once

extern bool deleteKey_flag;
extern int maxIdx;
extern int detNum;
extern int peddedSize;

extern int numMatrix[STR_SIZE];
extern char input_strArray[STR_SIZE];
extern char result_strArray[STR_SIZE];
extern int deliverMatrix[STR_SIZE];

extern int errNum;

/*----------------------------
* 0 : 문제없음
* 1 : key 행렬 할당 실패
* 2 : 소행렬식의 배열 할당실패
* 3 : 소행렬식 할당 실패
* 4 : 사용자가 직접 종료
* 5 : 역행렬에서 배열 할당실패
------------------------------*/