#include "Matrix.h"
#include "globalVar.h"

#define FINDING_MODULAR_INVERSE(dN, n) (dN*n)%ALPABET_SIZE

int cal_Determinant(int* keyMatrix, int keyMatrix_sideSize);
void copyIdx(int* destMatrix, int* srcMatrix, int srcStd_idx, int srcMatrix_sideSize);

char result_strArray[STR_SIZE];	// array to hold the decrypted plaintext


int find_modularInverse(void) // find inverse element  (문제 있음)
{
	int num = 0; // If it works anyway, you can perform modular arithmetic even if you multiply by 1.

	while (1)
	{
		if (FINDING_MODULAR_INVERSE(g_detNum, ++num) == 1) // return the minimum inverse element.
			break;
	}

	return num;
}

void mul_Scalar(int* inverseMatrix, int keyMatrix_sideSize)
{
	int modularInverse = find_modularInverse();

	for (int i = 0; i < keyMatrix_sideSize* keyMatrix_sideSize; i++)
		inverseMatrix[i] *= modularInverse; 
}

void transpose_Matrix(int* Matrix, int matrix_sideSize)
{
	int srcPOS = 0;
	int desPOS = 0;
	for (int row = 0; row < matrix_sideSize; row++) // perform operations based only on the diagonal of the matrix.
	{
		for (int col = row + 1; col < matrix_sideSize; col++)
		{
			srcPOS = row * matrix_sideSize + col;
			desPOS = col * matrix_sideSize + row;

			// If srcPOS and desPOS are the same, the operation will result in a value of 0. They must be different (xor's logical structure)
			Matrix[srcPOS] = Matrix[srcPOS] ^ Matrix[desPOS]; // src = src ^ des 
			Matrix[desPOS] = Matrix[srcPOS] ^ Matrix[desPOS]; // des = src = (src ^ des) ^ des
			Matrix[srcPOS] = Matrix[srcPOS] ^ Matrix[desPOS]; // src = des = (src ^ des) ^ src(=desPOS)
		}
	}

#if 1
	printf("\n");
	for (int i = 0; i < matrix_sideSize; i++)
	{
		for (int j = 0; j < matrix_sideSize; j++)
		{
			printf("%d ", Matrix[i * matrix_sideSize + j]);
		}
		printf("\n");
	}
	printf("\n");
#endif
}

void cal_inverseMaxtrix(int* keyMatrix, int* result_InverseMatrix, int keyMatrix_sideSize) // 처음에는 전역변수, 역행렬을 담을 배열, (int)sqrt(maxIdx+peddedNum) 대입 
// 호출자에서 errNum을 확인하면 루프 break
{
	/*--------------------------------*/
	// 1. 필요한 변수들 미리 선언 
	/*--------------------------------*/

	int** subMatrixs = NULL;					// 첫번째 소행렬들을 보관하는 포인터배열
	int keyMatrix_Size = (int)pow(keyMatrix_sideSize, 2);

	int nextMatrix_sideSize = keyMatrix_sideSize - 1;		// 행렬식은 깊이 +1 일수록, 행렬의 크기가 -1
	int nextMatrix_Size = (int)pow(nextMatrix_sideSize, 2);
	int signNum = 0;
	
	int temp1 = 0, temp2 = 0; // 디버거용

	/*--------------------------------*/
	// 2. 크기만큼 동적할당 
	/*--------------------------------*/

	subMatrixs = (int**)malloc(keyMatrix_Size * sizeof(int*));
	if (subMatrixs == NULL)
	{
		errNum = 5;
		goto cal_inverseDeterminant_exit1;
	}

	memset(subMatrixs, 0, keyMatrix_Size * sizeof(int*));

	/*--------------------------------*/
	// 3. 여인자 행렬화
	/*--------------------------------*/

	for (int i = 0; i < keyMatrix_Size; i++)
	{
		subMatrixs[i] = (int*)malloc(nextMatrix_Size * sizeof(int)); 

		if ( subMatrixs[i] == NULL)
		{
			errNum = 6;
			goto cal_inverseDeterminant_exit2;
		}

		copyIdx(subMatrixs[i], keyMatrix, i, keyMatrix_sideSize); // 키행렬에서의 소행렬을 subMatrixs의 인덱스 행렬에 복사하는 작업
		
		signNum = i / keyMatrix_sideSize + i % keyMatrix_sideSize;

		temp1 = (int)pow(-1, signNum);
		temp2 = cal_Determinant(subMatrixs[i], nextMatrix_sideSize); // 해당 소행렬식 구해서, 결과를 출력할 역행렬에 넣기

		result_InverseMatrix[i] = temp1 * temp2;
	} 

	if (errNum == 3) //행렬식에서 할당 실패 예외처리
	{
		goto cal_inverseDeterminant_exit2;
	}

#if 1
	printf("\n");
	for (int i = 0; i < keyMatrix_sideSize; i++)
	{
		for (int j = 0; j < keyMatrix_sideSize; j++)
		{
			printf("%d ", result_InverseMatrix[i * keyMatrix_sideSize + j]);
		}
		printf("\n");
	}
	printf("\n\n");
#endif

	/*--------------------------------*/
	// 4. 수반행렬화 + 역원 스칼라 연산
	/*--------------------------------*/


	transpose_Matrix(result_InverseMatrix, keyMatrix_sideSize); // 문제 있음
	mul_Scalar(result_InverseMatrix, keyMatrix_sideSize);
	
	/*--------------------------------*/
	// 5.. 정리
	/*--------------------------------*/

#if (1)
	for (int i = 0; i < keyMatrix_Size; i++)
	{
		printf("%d ", result_InverseMatrix[i]);
	}
#endif

cal_inverseDeterminant_exit2:
	for (int i = 0; i < keyMatrix_Size; i++)
		free(subMatrixs[i]);

	free(subMatrixs);

cal_inverseDeterminant_exit1:
	return;
}