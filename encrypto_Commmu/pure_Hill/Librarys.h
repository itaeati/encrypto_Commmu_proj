#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define _USE_MATH_DEFINES
#include <math.h>

#define STR_SIZE 500
#define ALPABET_SIZE 27 // 기존 알파벳 + @(패딩)

void cleanUp_func(void);

//extern char strArray[STR_SIZE];		// 평문을 담는 배열
//extern int resultArray[STR_SIZE];		// 평문 * key행렬 결과를 담는 배열
//extern int maxIdx;					// 평문의 크기를 알리는 변수