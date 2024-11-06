#include "Matrix.h"
#include "globalVar.h"

#define FINDING_MODULAR_INVERSE(dN, n) (dN*n)%ALPABET_SIZE

char result_strArray[STR_SIZE];		// 복호화 평문을 담는 배열


int find_modularInverse(void) // 역원찾기
{
	int num = 0; // 어차피 그냥 되는거면 1곱해도 모듈러연산이 됨.

	while (1)
	{
		if (FINDING_MODULAR_INVERSE(detNum, ++num) == 1) // 최소 역원을 반환
			break;
	}

	return num;
}

void mul_Scalar(int* inverseArr, int keySize)
{
	int modularInverse = find_modularInverse();

	for (int i = 0; i < maxIdx; i++)
		inverseArr[i] *= modularInverse;
}

int cal_inverseDeterminant(int* keyArr, int* inverseArr,int keySize) // 처음에는 전역변수, (int)sqrt(maxIdx+peddedNum) 대입
{
	// 1. 기준행을 정해서, 소행렬식을 쪼개주고, 소행렬식이 깊이탐색

	int** inverseArrays = NULL;			// 첫번째 소행렬들을 보관하는 포인터배열
	int modularInverse = 1;
	int next_tempSize = keySize - 1;	// 행렬식은 깊이 +1 일수록, 행렬의 크기가 -1
	int matrixSize = (int)pow(keySize, 2);

	/*--------------------------------*/
	// 1. 역원구해서, 행렬에 스칼라곱
	/*--------------------------------*/
	

	/*--------------------------------*/
	// 2. 크기만큼 동적할당 -> 해제는 caller에서 계산하자마자!!!
	/*--------------------------------*/

	inverseArrays = (int**)malloc(matrixSize * sizeof(int*));
	if (inverseArrays == NULL)
	{
		errNum = 5;
		goto cal_inverseDeterminant_exit;
	}

	memset(inverseArrays, 0, matrixSize);
	

	/*--------------------------------*/
	// 3. 소행렬식 해제 + 역행렬 완성
	/*--------------------------------*/

	// 첫번째로 할당한 배열 빼고는 전부 할당해제 + 값 대입

	// if(에러코드가 0일시)
	// {
	//	// 값대입
	//	// transpose 함수
	//	// mul_Scalar(inverseArr, keySize);
	// }
	//	
	

	for (int i = 0; i < keySize; i++)
		free(inverseArrays[i]);

	free(inverseArrays);

cal_inverseDeterminant_exit:
	return inverseArrays;
}