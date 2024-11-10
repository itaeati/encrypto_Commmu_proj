#include "Matrix.h"

char input_strArray[STR_SIZE];		// ���� ��� �迭
int deliverMatrix[STR_SIZE];	// �� * key��� ����� ��� �迭
int g_maxIdx = 0;					// ���� ũ��
int numMatrix[STR_SIZE];			// ���� �����ϴ� ���ڷ� ��ȯ�� ���� �����ϴ� �迭
int g_detNum = 1;					// ��Ľİ�
int g_peddedSize = 0;				// �е�������

bool g_deleteKey_flag = false;	// Ȥ�ø𸣴� �˻�
int errNum = 0;					// ����üũ

void copyIdx(int* destMatrix, int* srcMatrix, int srcStd_idx, int srcMatrix_sideSize);
int cal_Determinant(int* keyMatrix, int keyMatrix_sideSize);
void keyElement_input(int* keyMatrix, int keyMatrix_sideSize);

int cal_Determinant(int* keyMatrix, int keyMatrix_sideSize) // key ����� ��Ľ��� 0������ �˻��ϴ� �Լ�
{
	// 0. �迭�� �Ѻ�ũ���� �迭�� ���� ������ �迭 ����

	int keyMatrix_Size = (int)pow(keyMatrix_sideSize, 2);
	int result = 0;				// default ������ 0�� ��ȯ�� caller���� ������ �߻��ϰ� ����ó��!!

	int** subMatrixs = (int**)malloc(keyMatrix_Size * sizeof(int*)); // ����Ľ��� ������ �迭
	int nextMatrix_sideSize = keyMatrix_sideSize - 1;	// ��Ľ��� ���� +1 �ϼ���, ����� ũ�Ⱑ -1
	int nextMatrix_Size = nextMatrix_sideSize * nextMatrix_sideSize;

	if (errNum || subMatrixs == NULL)
	{
		errNum = 2;
		goto cal_Determinant_exit1;
	}

	memset(subMatrixs, 0, keyMatrix_Size);

	if (keyMatrix_sideSize == 2)
	{
		result = keyMatrix[0] * keyMatrix[3] - keyMatrix[1] * keyMatrix[2]; // 2X2 ��Ľ� ������ڸ��� ��ȯ
	}
	else // ����Ž���˰���
	{
		// 1. ����Ľ��� ���� �迭 ����
		for (int i = 0; i < keyMatrix_sideSize; i++)
		{
			subMatrixs[i] = (int*)malloc(nextMatrix_Size * sizeof(int));
			if (errNum || subMatrixs == NULL)
			{
				errNum = 3;
				goto cal_Determinant_exit2;
			}

			// 2. �ش� �ε����� ��� ���� ������ ������ �ε��� ����
			copyIdx(subMatrixs[i], keyMatrix, i, keyMatrix_sideSize);

			// 3. ������� ����
			result += (int)pow(-1, i) * keyMatrix[i] * cal_Determinant(subMatrixs[i], nextMatrix_sideSize);
		}

		// 4. �Ҵ�迭 ����
		for (int i = 0; i < keyMatrix_sideSize; i++)
			free(subMatrixs[i]);
	}
cal_Determinant_exit2:

	if (errNum == 3) // ����Ľ� �Ҵ� ���н�, �Ҵ�� �迭�� ���� ����
	{
		for (int i = 0; i < keyMatrix_Size; i++)
			if (subMatrixs[i] != NULL) free(subMatrixs[i]);
			else break; // �Ҵ��� ���������� �Ǳ� ����
	}

	free(subMatrixs);

cal_Determinant_exit1:
	return result;
}

void copyIdx(int* destMatrix, int* srcMatrix, int srcStd_idx, int srcMatrix_sideSize)
{
	// 2.1 ���� ��� �� ���ϱ�
	int srcStd_row = srcStd_idx / srcMatrix_sideSize;
	int srcStd_col = srcStd_idx % srcMatrix_sideSize;
	int destIdx = 0;

	for (int row = 0; row < srcMatrix_sideSize; row++)
	{
		for (int col = 0; col < srcMatrix_sideSize; col++)
		{
			// 2.2 ���� ��� �� ���� ī��
			if (col == srcStd_col || row == srcStd_row)
				continue;

			destMatrix[destIdx++] = srcMatrix[row * srcMatrix_sideSize + col];
		}
	}
}

void mul_Matrix(int* leftMatrix, int leftMatrix_sideSize, int* rightMatrix, int rightMatrix_size, int* resultMatrix) // ���� ��İ��� ���ִ� �Լ�
// �������� ���� ������������ �Ķ���ͷ� �ްԲ� ����
// leftMatrix : Ű���
// rightMatrix : ���� ����ȭ �� ���
// rightMatrix_size : g_maxIdx
// resultMatrix : ??
{
	int sum = 0;
	g_peddedSize = leftMatrix_sideSize - (rightMatrix_size % leftMatrix_sideSize);
	int rightMatrix_maxCol = 0;
	int resultMatrix_idx = 0;

	/*------------------------*/
	// 1. �����е�
	/*------------------------*/

	if (g_peddedSize != 0) //strArray�� key����� ���� ������ ����� �ƴ϶�� �е�����
	{
		for (int i = 0; i < g_peddedSize; i++)
		{
			numMatrix[rightMatrix_size + i] = 26; // �߰��Ǵ� ���� 27��° ������ ���� ����. (27��° ���ڴ� '@')
		}
	}

	/*------------------------*/
	// 2. ���ڸ��� -> ���ϱ�
	/*------------------------*/

	rightMatrix_maxCol = rightMatrix_size / leftMatrix_sideSize;

	/*------------------------*/
	// 3. ��ŭ �ݺ��ؼ� ��İ� -> �������
	/*------------------------*/

	for (int leftRow = 0; leftRow < leftMatrix_sideSize; leftRow++)
	{
		for (int rightCol = 0; rightCol < rightMatrix_maxCol; rightCol++)
		{
			sum = 0;

			for (int targetVector_idx = 0; targetVector_idx < leftMatrix_sideSize; targetVector_idx++) 
			{
				// ������ �ε����� �����ġ�� ���� �ǹ̰� �޶���
				// ����� : ��
				// ����� : ��

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