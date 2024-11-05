#include "Matrix.h"

char strArray[STR_SIZE];	// ���� ��� �迭
int resultArray[STR_SIZE];	// �� * key��� ����� ��� �迭
int maxIdx = 0;
int strArray_length[STR_SIZE]; // ���� �����ϴ� ���ڷ� ��ȯ�� ���� �����ϴ� �迭

int* make_keyArray(int* keySize) // key ũ�⸦ �Է¹ް�, key ����� ����� �Լ�
{
	/*--------------------------*/
	// 1. Ű ��� ������ �Է¹ޱ�
	/*--------------------------*/

	int* keyArray = NULL;
	printf("Ű�� ���� ũ�⸦ �Է��ϼ���:");
	scanf("%d", keySize);
	printf("\n");

	if (!(keySize > 0))
	{
		goto make_keyArray_exit;
	}

	/*--------------------------*/
	// 2. Ű��� �Ҵ�
	/*--------------------------*/

	keyArray = (int*)malloc((int)pow(*keySize, 2) * sizeof(int));

	if (keyArray == NULL)
	{
		goto make_keyArray_exit;
	}

	// Ȥ�ø��� �� ������?

make_keyArray_exit:
	return keyArray;
}

void keyElement_input(int* keyArray, int keySize) // key ��Ŀ� ���� ���ִ� �Լ�
{
	for (int i = 0; i < keySize * keySize; i++)
	{
		printf("Ű�� �Է��ϼ��� [%d][%d] : ", i / keySize, i % keySize);
		scanf("%d", &keyArray[i]);
			// ������ ����

	}
	return;
}

int cal_Determinant(int* keyArray, int keySize) // key ����� ��Ľ��� 0������ �˻��ϴ� �Լ�
{
	// 0. �迭�� �Ѻ�ũ���� �迭�� ���� ������ �迭 ����
	int** tempArr = (int**)malloc((int)pow(keySize, keySize) * sizeof(int*)); // ����Ľ��� ������ �迭
	int tempSize = keySize - 1;	// ��Ľ��� ���� +1 �ϼ���, ����� ũ�Ⱑ -1
	int result = 0;				// default ������ 0�� ��ȯ�� caller���� ������ �߻��ϰ� ����ó��!!


	if (keySize == 2)
	{
		result = keyArray[0] * keyArray[3] - keyArray[1] * keyArray[2]; // 2X2 ��Ľ� ������ڸ��� ��ȯ
	}
	else // ����Ž���˰���
	{
		// 1. ����Ľ��� ���� �迭 ����
		for (int i = 0; i < keySize; i++)
		{
			tempArr[i] = (int*)malloc((int)pow(tempSize, 2) * sizeof(int));

			// 2. �ش� �ε����� ��� ���� ������ ������ �ε��� ����
			copyIdx(tempArr[i], keyArray, i, keySize);

			// 3. ������� ����
			result += (int)pow(-1, i) * keyArray[i] * cal_Determinant(tempArr[i], tempSize);
		}

		// 4. �Ҵ�迭 ����
		for (int i = 0; i < keySize; i++)
			free(tempArr[i]);
	}

	free(tempArr);

	return result;
}

void copyIdx(int* destArr, int* srcArr, int srcStd_idx, int srcSize)
{
	// 2.1 ���� ��� �� ���ϱ�
	int srcStd_row = srcStd_idx / srcSize;
	int srcStd_col = srcStd_idx % srcSize;
	int destIdx = 0;

	for (int row = 0; row < srcSize; row++)
	{
		for (int col = 0; col < srcSize; col++)
		{
			// 2.2 ���� ��� �� ���� ī��
			if (col == srcStd_col || row == srcStd_row)
				continue;

			destArr[destIdx++] = srcArr[row * srcSize + col];
		}
	}
}

void input_strArray(int* strSize)
{
	// ������ ����

	/*--------------------------*/ ////////// �� ���̸� �޾ƾ� �ϴµ� 
	// 1. ���� ���̸� ����
	/*--------------------------*/
	/*--------------------------*/
	// 2. string �Է¹ޱ�
	/*--------------------------*/
	/*--------------------------*/ ////////// int �迭�� ����.
	// 3. int �迭�� �ٽ� �ֱ�
	/*--------------------------*/

	printf("���� �Է��ϼ��� : ");
	scanf("%s", strArray); //���� strArray�迭�� ���ڿ��� �Է��� �޴´�.

	if (strArray == NULL)
	{

	}


	for (int i = 0; i < strlen(strArray); ++i)
	{
		strArray_length[i] = (int)strArray[i] - 'A';
	}


	return;
}

bool mul_Matrix(int* keyArray, char* strArray) // ���� ��İ��� ���ִ� �Լ�
{
	// 1. 
}