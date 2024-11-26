#include "Matrix.h"

char input_strArray[STR_SIZE];		// array to hold plaintext.
int deliverMatrix[STR_SIZE];		// array to hold the result of plaintext multiplied by key matrix.
int g_maxIdx = 0;					// variable indicating the size of the plaintext.
int numMatrix[STR_SIZE];			// "An array that stores the values obtained by converting plaintext to corresponding numbers.
int g_detNum = 1;					// Determinant value.
int g_paddingSize = 0;					// padding size.

bool g_deleteKey_flag = false;	
int errNum = 0;					// error check.

void copyIdx(int* destMatrix, int* srcMatrix, int srcStd_idx, int srcMatrix_sideSize);

void matrixMoudulation(int* targetMatrix, int matrixSize);

int cal_Determinant(int* keyMatrix, int keyMatrix_sideSize) // A function that checks if the determinant of the key matrix is 0.
{
	// 0. Declare a pointer array to hold arrays of the size of one side of the array.

	int keyMatrix_Size = (int)pow(keyMatrix_sideSize, 2);
	int result = 0;				// Handle exceptions so that an error occurs in the caller when the default value of 0 is returned!!

	int** subMatrixs = (int**)malloc(keyMatrix_Size * sizeof(int*)); // An array to store the submatrix determinants.
	int nextMatrix_sideSize = keyMatrix_sideSize - 1;	// As the depth increases by +1, the size of the matrix decreases by -1.
	int nextMatrix_Size = nextMatrix_sideSize * nextMatrix_sideSize;

	if (errNum || subMatrixs == NULL)
	{
		errNum = 2;
		goto cal_Determinant_exit1;
	}

	memset(subMatrixs, 0, keyMatrix_Size);

	if (keyMatrix_sideSize == 1)
	{
		result = *keyMatrix;
	}

	else if (keyMatrix_sideSize == 2)
	{
		result = keyMatrix[0] * keyMatrix[3] - keyMatrix[1] * keyMatrix[2]; // Return the 2x2 determinant as soon as it is calculated.
	}
	else // Depth-first search algorithm.
	{
		// 1. Declare an array for submatrices.
		for (int i = 0; i < keyMatrix_sideSize; i++)
		{
			subMatrixs[i] = (int*)malloc(nextMatrix_Size * sizeof(int));
			if (errNum || subMatrixs == NULL)
			{
				errNum = 3;
				goto cal_Determinant_exit2;
			}

			// 2. "Assign the remaining indices, excluding the row and column of the specified index.
			copyIdx(subMatrixs[i], keyMatrix, i, keyMatrix_sideSize);

			// 3. Assign to the result value.
			result += (int)pow(-1, i) * keyMatrix[i] * cal_Determinant(subMatrixs[i], nextMatrix_sideSize);
		}

		// 4. Deallocate the assigned array.
		for (int i = 0; i < keyMatrix_sideSize; i++)
			free(subMatrixs[i]);
	}
cal_Determinant_exit2:

	if (errNum == 3) // Deallocate all assigned arrays if submatrix allocation fails.
	{
		for (int i = 0; i < keyMatrix_Size; i++)
			if (subMatrixs[i] != NULL) free(subMatrixs[i]);
			else break; // "Allocation is performed sequentially.
	}

	free(subMatrixs);

cal_Determinant_exit1:
	return result;
}

void copyIdx(int* destMatrix, int* srcMatrix, int srcStd_idx, int srcMatrix_sideSize)
{
	// 2.1 Find the reference row and column.
	int srcStd_row = srcStd_idx / srcMatrix_sideSize;
	int srcStd_col = srcStd_idx % srcMatrix_sideSize;
	int destIdx = 0;

	for (int row = 0; row < srcMatrix_sideSize; row++)
	{
		for (int col = 0; col < srcMatrix_sideSize; col++)
		{
			// 2.2 Copy excluding the reference row and column.
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
// resultMatrix : delivery
{

	int sum = 0;
	int rightMatrix_maxCol = 0;
	int resultMatrix_idx = 0;

	int temp = 0;
	/*------------------------*/
	// 1. cut plaintext -> Find the quotient
	/*------------------------*/


	rightMatrix_maxCol = rightMatrix_size / leftMatrix_sideSize;

	/*------------------------*/
	// 2. Repeat the matrix multiplication for the quotient amount -> Store the result.
	/*------------------------*/
#if (0)

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
#else
	for (int leftRow = 0; leftRow < rightMatrix_maxCol; leftRow++)
	{
		for (int rightCol = 0; rightCol < leftMatrix_sideSize; rightCol++)
		{
			sum = 0;

			for (int targetVector_idx = 0; targetVector_idx < leftMatrix_sideSize; targetVector_idx++)
			{
				// The meaning of a vector's index varies according to its position in the matrix.
				// Left matrix: column.
				// Right matrix: row.

				temp = leftMatrix[rightCol * leftMatrix_sideSize + targetVector_idx] * rightMatrix[leftRow * leftMatrix_sideSize + targetVector_idx];

				sum += temp;
			}
			resultMatrix[resultMatrix_idx++] = sum;
		}
	}
#endif
	if (resultMatrix_idx != rightMatrix_size)
	{
		printf("Error!! multiplying Matrix algorhithm doesnt work!!\n\n");
		errNum = 6;
	}

}