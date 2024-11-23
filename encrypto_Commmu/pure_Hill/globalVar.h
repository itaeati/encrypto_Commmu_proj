#pragma once
#include "Librarys.h"

extern bool g_deleteKey_flag;
extern int g_maxIdx;
extern int g_detNum;
extern int g_peddedSize;

extern char input_strArray[STR_SIZE];
extern char result_strArray[STR_SIZE];
extern int numMatrix[STR_SIZE];
extern int deliverMatrix[STR_SIZE];


extern int errNum;

/*----------------------------
* 0 : 문제없음
* 1 : key 행렬 할당 실패
* 2 : 소행렬식의 배열 할당실패
* 3 : 소행렬식 할당 실패
* 4 : 사용자가 직접 종료
* 5 : 역행렬에서 배열 할당실패
* 6 : 행렬곱이 제대로 이루어지지 않음
* 7 : 역행렬 할당 실패
------------------------------*/