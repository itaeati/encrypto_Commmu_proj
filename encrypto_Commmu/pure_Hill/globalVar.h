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
* 0 : ��������
* 1 : key ��� �Ҵ� ����
* 2 : ����Ľ��� �迭 �Ҵ����
* 3 : ����Ľ� �Ҵ� ����
* 4 : ����ڰ� ���� ����
* 5 : ����Ŀ��� �迭 �Ҵ����
* 6 : ��İ��� ����� �̷������ ����
* 7 : ����� �Ҵ� ����
------------------------------*/