#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define _USE_MATH_DEFINES
#include <math.h>

#define STR_SIZE 500
#define ALPABET_SIZE 27 // ���� ���ĺ� + @(�е�)

void cleanUp_func(void);

//extern char strArray[STR_SIZE];		// ���� ��� �迭
//extern int resultArray[STR_SIZE];		// �� * key��� ����� ��� �迭
//extern int maxIdx;					// ���� ũ�⸦ �˸��� ����