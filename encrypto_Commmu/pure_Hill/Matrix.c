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

bool cal_Determinant(int* keyArray, int keySize) // key ����� ��Ľ��� 0������ �˻��ϴ� �Լ�
{
	// ��� �Լ��� ����Ľ��� ���ϴ� �Լ�

	/*-------------------------*/
	// 1. ��͸� ������
	/*-------------------------*/

	if (keySize <= 2) // ������ ����
	{
		return;
	}

	/*-------------------------*/
	// 2. ������� ���鶧 ������ �Ǵ� ���� ����
	/*-------------------------*/

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