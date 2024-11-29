#include "Matrix.h"
#include "globalVar.h"

int cal_Determinant(int* keyMatrix, int keyMatrix_sideSize);
void copyIdx(int* destMatrix, int* srcMatrix, int srcStd_idx, int srcMatrix_sideSize);

char result_strArray[STR_SIZE];	// 복호화 평문을 담는 배열

inline int FINDING_MODULAR_INVERSE(int detNum, int moduloNum) 
{
	int temp = (detNum * moduloNum) % ALPABET_SIZE; // 기본 연산

	if (temp < 0) 
		temp += ALPABET_SIZE;            
	// 역원은 26진수라고 가정해보자, 음수라면 보수처리가 되어있을것. -> 왜냐하면 나머지연산이니까 나머지만 확인하면됨
	// 그렇기 때문에 역원이 -25라면, 보수이기때문에 +26을 해주어야함. -> +1 (원형 wrapping 처리)
	// 일단 모듈러 값이 1이 되면 완성임

	return temp;
}

int find_modularInverse(void) // 역원찾기   (문제 있음)
{
	int num = 0; // 어차피 그냥 되는거면 1곱해도 모듈러연산이 됨.

	while (1)
	{
		if (FINDING_MODULAR_INVERSE(g_detNum, ++num) == 1) // 최소 역원을 반환 (음수에서 래핑 처리 필요...)
			break;
		else if (num == sqrt(INT_MAX)) // 찾을 수 없음
		{
			errNum = 8;
			num = 0;
			break;
		}
	}
#if defined(DEBUG)
	printf("inverseModulation_number : %d\n", num);
#endif

	return num;
}

void mul_Scalar(int* inverseMatrix, int keyMatrix_sideSize)
{
	int modularInverse = find_modularInverse();

	if (modularInverse == 0)
	{
		printf("your KeyMatrix is not disjoint!!!\n"); // 키행렬식이 26과 서로소여야만 모듈러 역원을 계산가능
		return 0;
	}
		

	for (int i = 0; i < keyMatrix_sideSize* keyMatrix_sideSize; i++)
		inverseMatrix[i] *= modularInverse; 
}

void transpose_Matrix(int* Matrix, int matrix_sideSize)
{
	int srcPOS = 0;
	int desPOS = 0;
	for (int row = 0; row < matrix_sideSize; row++) // 행렬의 대각선을 기준으로만 연산하면 됨
	{
		for (int col = row + 1; col < matrix_sideSize; col++)
		{
			srcPOS = row * matrix_sideSize + col;
			desPOS = col * matrix_sideSize + row;

			// srcPOS와 desPOS가 같다면 연산을 통해 값이 0이됨. 서로 달라야하만 함 (xor의 논리구조)
			Matrix[srcPOS] = Matrix[srcPOS] ^ Matrix[desPOS]; // src = src ^ des 
			Matrix[desPOS] = Matrix[srcPOS] ^ Matrix[desPOS]; // des = src = (src ^ des) ^ des
			Matrix[srcPOS] = Matrix[srcPOS] ^ Matrix[desPOS]; // src = des = (src ^ des) ^ src(=desPOS)
		}
	}
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

#ifdef DEBUG
	printf("after just inversing matrix..\n");
	printMatrix(result_InverseMatrix, keyMatrix_sideSize, keyMatrix_sideSize);
#endif

	/*--------------------------------*/
	// 4. 수반행렬화 + 역원 스칼라 연산
	/*--------------------------------*/


	transpose_Matrix(result_InverseMatrix, keyMatrix_sideSize); 
#ifdef DEBUG
	printf("after transposing..\n");
	printMatrix(result_InverseMatrix, keyMatrix_sideSize, keyMatrix_sideSize);
#endif


	mul_Scalar(result_InverseMatrix, keyMatrix_sideSize);
#ifdef DEBUG
	printf("after multplying scalar..\n");
	printMatrix(result_InverseMatrix, keyMatrix_sideSize, keyMatrix_sideSize);
#endif
	
	/*--------------------------------*/
	// 5.. 정리
	/*--------------------------------*/

cal_inverseDeterminant_exit2:
	for (int i = 0; i < keyMatrix_Size; i++)
		free(subMatrixs[i]);

	free(subMatrixs);

cal_inverseDeterminant_exit1:
	return;
}