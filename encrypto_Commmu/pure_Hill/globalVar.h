#pragma once
#include "Librarys.h"

extern bool g_deleteKey_flag;
extern int g_maxIdx;
extern int g_detNum;
extern int g_paddingSize;

extern char input_strArray[STR_SIZE];
extern char result_strArray[STR_SIZE];
extern int numMatrix[STR_SIZE];
extern int deliverMatrix[STR_SIZE];


extern int errNum;

/*----------------------------
0 : No issues.
1 : Key matrix allocation failed.
2 : Submatrix array allocation failed.
3 : Submatrix allocation failed.
4 : User termination.
5 : Array allocation failed in inverse matrix.
6 : Matrix multiplication not properly performed.
7 : Inverse matrix allocation failed.
------------------------------*/