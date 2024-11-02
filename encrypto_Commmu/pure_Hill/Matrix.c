#include "Matrix.h"

char strArray[STR_SIZE];	// 평문을 담는 배열
int resultArray[STR_SIZE];	// 평문 * key행렬 결과를 담는 배열
int maxIdx = 0;

int* make_keyArray(int* keySize) // key 크기를 입력받고, key 행렬을 만드는 함수
{
	/*--------------------------*/
	// 1. 키 행렬 사이즈 입력받기
	/*--------------------------*/

	int* keyArray = NULL;
	printf("키의 행의 크기를 입력하세요:");
	scanf("%d", keySize);
	printf("\n");

	if (!(keySize > 0))
	{
		goto make_keyArray_exit;
	}

	/*--------------------------*/
	// 2. 키행렬 할당
	/*--------------------------*/

	keyArray = (int*)malloc((int)pow(*keySize, 2) * sizeof(int));

	if (keyArray == NULL)
	{
		goto make_keyArray_exit;
	}

	// 혹시몰라 더 써질지?

make_keyArray_exit:
	return keyArray;
}

void keyElement_input(int* keyArray, int keySize) // key 행렬에 값을 써주는 함수
{
	// 류현수 구현

	return;
}

bool cal_Determinant(int* keyArray, int keySize) // key 행렬의 행렬식이 0인지를 검사하는 함수
{
	// 재귀 함수로 소행렬식을 구하는 함수

	/*-------------------------*/
	// 1. 재귀를 끊어줌
	/*-------------------------*/

	if (keySize <= 2) // 집에서 구현
	{
		return;
	}

	/*-------------------------*/
	// 2. 소행렬을 만들때 기준이 되는 행을 구함
	/*-------------------------*/

}

void input_strArray(int* strSize) // 평문의 사이즈를 입력받고, 평문배열을 입력받는 함수
{
	// 류현수 구현

	/*--------------------------*/
	// 1. 평문의 길이를 받음
	/*--------------------------*/

	/*--------------------------*/
	// 2. string 입력받기
	/*--------------------------*/

	/*--------------------------*/
	// 3. int 배열에 다시 넣기
	/*--------------------------*/

	return;
}



bool mul_Matrix(int* keyArray, char* strArray) // 둘의 행렬곱만 해주는 함수
{
	// 1. 
}