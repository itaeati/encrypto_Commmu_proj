#include "Matrix.h"

char input_strArray[STR_SIZE];		// 평문을 담는 배열
int deliverMatrix[STR_SIZE];	// 평문 * key행렬 결과를 담는 배열
int g_maxIdx = 0;					// 평문의 크기
int numMatrix[STR_SIZE];			// 평문을 대응하는 숫자로 변환한 값을 저장하는 배열
int g_detNum = 1;					// 행렬식값
int g_peddedSize = 0;				// 패딩사이즈

bool g_deleteKey_flag = false;	// 혹시모르는 검사
int errNum = 0;					// 에러체크

void copyIdx(int* destMatrix, int* srcMatrix, int srcStd_idx, int srcMatrix_sideSize);
int cal_Determinant(int* keyMatrix, int keyMatrix_sideSize);
void keyElement_input(int* keyMatrix, int keyMatrix_sideSize);

int cal_Determinant(int* keyMatrix, int keyMatrix_sideSize) // key 행렬의 행렬식이 0인지를 검사하는 함수
{
	// 0. 배열의 한변크기의 배열을 담을 포인터 배열 선언

	int keyMatrix_Size = (int)pow(keyMatrix_sideSize, 2);
	int result = 0;				// default 값으로 0을 반환시 caller에서 오류가 발생하게 예외처리!!

	int** subMatrixs = (int**)malloc(keyMatrix_Size * sizeof(int*)); // 소행렬식을 저장할 배열
	int nextMatrix_sideSize = keyMatrix_sideSize - 1;	// 행렬식은 깊이 +1 일수록, 행렬의 크기가 -1
	int nextMatrix_Size = nextMatrix_sideSize * nextMatrix_sideSize;

	if (errNum || subMatrixs == NULL)
	{
		errNum = 2;
		goto cal_Determinant_exit1;
	}

	memset(subMatrixs, 0, keyMatrix_Size);

	if (keyMatrix_sideSize == 2)
	{
		result = keyMatrix[0] * keyMatrix[3] - keyMatrix[1] * keyMatrix[2]; // 2X2 행렬식 계산하자마자 반환
	}
	else // 깊이탐색알고리즘
	{
		// 1. 소행렬식을 위한 배열 선언
		for (int i = 0; i < keyMatrix_sideSize; i++)
		{
			subMatrixs[i] = (int*)malloc(nextMatrix_Size * sizeof(int));
			if (errNum || subMatrixs == NULL)
			{
				errNum = 3;
				goto cal_Determinant_exit2;
			}

			// 2. 해당 인덱스의 행과 열을 제외한 나머지 인덱스 대입
			copyIdx(subMatrixs[i], keyMatrix, i, keyMatrix_sideSize);

			// 3. 결과값에 대입
			result += (int)pow(-1, i) * keyMatrix[i] * cal_Determinant(subMatrixs[i], nextMatrix_sideSize);
		}

		// 4. 할당배열 해제
		for (int i = 0; i < keyMatrix_sideSize; i++)
			free(subMatrixs[i]);
	}
cal_Determinant_exit2:

	if (errNum == 3) // 소행렬식 할당 실패시, 할당된 배열들 전부 해제
	{
		for (int i = 0; i < keyMatrix_Size; i++)
			if (subMatrixs[i] != NULL) free(subMatrixs[i]);
			else break; // 할당은 순차적으로 되기 때문
	}

	free(subMatrixs);

cal_Determinant_exit1:
	return result;
}

void copyIdx(int* destMatrix, int* srcMatrix, int srcStd_idx, int srcMatrix_sideSize)
{
	// 2.1 기준 행과 열 구하기
	int srcStd_row = srcStd_idx / srcMatrix_sideSize;
	int srcStd_col = srcStd_idx % srcMatrix_sideSize;
	int destIdx = 0;

	for (int row = 0; row < srcMatrix_sideSize; row++)
	{
		for (int col = 0; col < srcMatrix_sideSize; col++)
		{
			// 2.2 기준 행과 열 빼고 카피
			if (col == srcStd_col || row == srcStd_row)
				continue;

			destMatrix[destIdx++] = srcMatrix[row * srcMatrix_sideSize + col];
		}
	}
}

void mul_Matrix(int* leftMatrix, int leftMatrix_sideSize, int* rightMatrix, int rightMatrix_size, int* resultMatrix) // 둘의 행렬곱만 해주는 함수
// 유연성을 위해 전역변수여도 파라미터로 받게끔 제작
// leftMatrix : 키행렬
// rightMatrix : 평문을 숫자화 한 행렬
// rightMatrix_size : g_maxIdx
// resultMatrix : ??
{
	int sum = 0;
	g_peddedSize = leftMatrix_sideSize - (rightMatrix_size % leftMatrix_sideSize);
	int rightMatrix_maxCol = 0;
	int resultMatrix_idx = 0;

	/*------------------------*/
	// 1. 문자패딩
	/*------------------------*/

	if (g_peddedSize != 0) //strArray가 key행렬의 행의 길이의 배수가 아니라면 패딩시작
	{
		for (int i = 0; i < g_peddedSize; i++)
		{
			numMatrix[rightMatrix_size + i] = 26; // 추가되는 값은 27번째 문자의 값을 대입. (27번째 문자는 '@')
		}
	}

	/*------------------------*/
	// 2. 평문자르기 -> 몫구하기
	/*------------------------*/

	rightMatrix_maxCol = rightMatrix_size / leftMatrix_sideSize;

	/*------------------------*/
	// 3. 몫만큼 반복해서 행렬곱 -> 결과저장
	/*------------------------*/

	for (int leftRow = 0; leftRow < leftMatrix_sideSize; leftRow++)
	{
		for (int rightCol = 0; rightCol < rightMatrix_maxCol; rightCol++)
		{
			sum = 0;

			for (int targetVector_idx = 0; targetVector_idx < leftMatrix_sideSize; targetVector_idx++) 
			{
				// 벡터의 인덱스는 행렬위치에 따라 의미가 달라짐
				// 좌행렬 : 열
				// 우행렬 : 행

				sum += leftMatrix[leftRow * leftMatrix_sideSize + targetVector_idx] * rightMatrix[targetVector_idx * rightMatrix_maxCol + rightCol];
			}
			resultMatrix[resultMatrix_idx++] = sum;
		}
	}

	if (resultMatrix_idx != rightMatrix_size)
	{
		printf("Error!! multiplying Matrix algorhithm doesnt work!!\n\n");
		errNum = 6;
	}
}