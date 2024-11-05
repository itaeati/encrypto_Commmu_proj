#include "Matrix.h"

char strArray[STR_SIZE];	// 평문을 담는 배열
int resultArray[STR_SIZE];	// 평문 * key행렬 결과를 담는 배열
int maxIdx = 0;
int strArray_length[STR_SIZE]; // 평문을 대응하는 숫자로 변환한 값을 저장하는 배열

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
	for (int i = 0; i < keySize * keySize; i++)
	{
		printf("키를 입력하세요 [%d][%d] : ", i / keySize, i % keySize);
		scanf("%d", &keyArray[i]);
			// 류현수 구현

	}
	return;
}

int cal_Determinant(int* keyArray, int keySize) // key 행렬의 행렬식이 0인지를 검사하는 함수
{
	// 0. 배열의 한변크기의 배열을 담을 포인터 배열 선언
	int** tempArr = (int**)malloc((int)pow(keySize, keySize) * sizeof(int*)); // 소행렬식을 저장할 배열
	int tempSize = keySize - 1;	// 행렬식은 깊이 +1 일수록, 행렬의 크기가 -1
	int result = 0;				// default 값으로 0을 반환시 caller에서 오류가 발생하게 예외처리!!


	if (keySize == 2)
	{
		result = keyArray[0] * keyArray[3] - keyArray[1] * keyArray[2]; // 2X2 행렬식 계산하자마자 반환
	}
	else // 깊이탐색알고리즘
	{
		// 1. 소행렬식을 위한 배열 선언
		for (int i = 0; i < keySize; i++)
		{
			tempArr[i] = (int*)malloc((int)pow(tempSize, 2) * sizeof(int));

			// 2. 해당 인덱스의 행과 열을 제외한 나머지 인덱스 대입
			copyIdx(tempArr[i], keyArray, i, keySize);

			// 3. 결과값에 대입
			result += (int)pow(-1, i) * keyArray[i] * cal_Determinant(tempArr[i], tempSize);
		}

		// 4. 할당배열 해제
		for (int i = 0; i < keySize; i++)
			free(tempArr[i]);
	}

	free(tempArr);

	return result;
}

void copyIdx(int* destArr, int* srcArr, int srcStd_idx, int srcSize)
{
	// 2.1 기준 행과 열 구하기
	int srcStd_row = srcStd_idx / srcSize;
	int srcStd_col = srcStd_idx % srcSize;
	int destIdx = 0;

	for (int row = 0; row < srcSize; row++)
	{
		for (int col = 0; col < srcSize; col++)
		{
			// 2.2 기준 행과 열 빼고 카피
			if (col == srcStd_col || row == srcStd_row)
				continue;

			destArr[destIdx++] = srcArr[row * srcSize + col];
		}
	}
}

void input_strArray(int* strSize)
{
	// 류현수 구현

	/*--------------------------*/ ////////// 평문 길이를 받아야 하는데 
	// 1. 평문의 길이를 받음
	/*--------------------------*/
	/*--------------------------*/
	// 2. string 입력받기
	/*--------------------------*/
	/*--------------------------*/ ////////// int 배열이 없음.
	// 3. int 배열에 다시 넣기
	/*--------------------------*/

	printf("평문을 입력하세요 : ");
	scanf("%s", strArray); //평문을 strArray배열에 문자열로 입력을 받는다.

	if (strArray == NULL)
	{

	}


	for (int i = 0; i < strlen(strArray); ++i)
	{
		strArray_length[i] = (int)strArray[i] - 'A';
	}


	return;
}

bool mul_Matrix(int* keyArray, char* strArray) // 둘의 행렬곱만 해주는 함수
{
	// 1. 
}