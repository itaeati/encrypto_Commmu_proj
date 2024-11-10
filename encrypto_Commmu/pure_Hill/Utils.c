#include "Librarys.h"
#include "Utils.h"
#include "Matrix.h"
#include "globalVar.h"

void keyElement_input(int* keyMatrix, int keyMatrix_sideSize);

void cleanUp_func(void)
{
	g_detNum = 1;
	g_maxIdx = 0;
	g_peddedSize = 0;
	g_deleteKey_flag = false;

	memset(input_strArray, 0, STR_SIZE * sizeof(char));
	memset(result_strArray, 0, STR_SIZE * sizeof(char));
	memset(deliverMatrix, 0, STR_SIZE * sizeof(int));
	memset(numMatrix, 0, STR_SIZE * sizeof(int));
}

int* make_keyMatrix(int* keyMatrix_sideSize) // key ũ�⸦ �Է¹ް�, key ����� ����� �Լ�
{
	/*--------------------------*/
	// 1. Ű ��� ������ �Է¹ޱ�
	/*--------------------------*/

	int* keyMatrix = NULL;
	printf("Ű�� ���� ũ�⸦ �Է��ϼ���:");

	scanf("%d", keyMatrix_sideSize);

	printf("\n");

	if (!(*keyMatrix_sideSize > 0))
	{
		goto make_keyMatrix_exit;
	}

	/*--------------------------*/
	// 2. Ű��� �Ҵ�
	/*--------------------------*/

	keyMatrix = (int*)malloc((int)pow(*keyMatrix_sideSize, 2) * sizeof(int));

	if (keyMatrix == NULL)
	{
		errNum = 1;
		goto make_keyMatrix_exit;
	}

	g_deleteKey_flag = true; // ������ �� �������� �����!

	/*--------------------------*/
	// 3. Ű��Ŀ� �Է�
	/*--------------------------*/

	keyElement_input(keyMatrix, *keyMatrix_sideSize);

make_keyMatrix_exit:
	return keyMatrix;
}

void keyElement_input(int* keyMatrix, int keyMatrix_sideSize) // key ��Ŀ� ���� ���ִ� �Լ�
{
	bool isZero_flag = true;
	int keyMatrix_size = keyMatrix_sideSize * keyMatrix_sideSize;

	while (isZero_flag)
	{
		for (int i = 0; i < keyMatrix_size; i++)
		{
			printf("Ű�� �Է��ϼ��� [%d][%d] : ", i / keyMatrix_sideSize, i % keyMatrix_sideSize);
			scanf("%d", &keyMatrix[i]);
			// ������ ����
		}

		if ((g_detNum = cal_Determinant(keyMatrix, keyMatrix_sideSize)) == 0)
		{
			printf("��Ľ��� 0�Դϴ�! �ٽ��Է��ϼ���!\n");
			isZero_flag = true;
		}
		else
			isZero_flag = false;
	}

	return;
}

void input_to_strArray(void)
{
	// ������ ����
	bool loopFlag = true;

	do
	{
		/*--------------------------*/
		// 1. strArray �ʱ�ȭ
		/*--------------------------*/

		memset(input_strArray, 0, STR_SIZE); // �迭 �ʱ�ȭ

		/*--------------------------*/
		// 2. string �Է¹ޱ�
		/*--------------------------*/

		printf("���� �Է��ϼ��� (qqq�Է½� ����) : ");

		fgets(input_strArray, STR_SIZE, stdin); //���� strArray�迭�� ���ڿ��� �Է��� �޴´�. (499���� ���� + null)

		if (strcmp(input_strArray, "qqq") || strcmp(input_strArray, "QQQ")) // �������� �˻�
		{
			errNum = 4; // ����ڰ� ��������
			break;
		}

		/*--------------------------*/
		// 3. �������� �˻� + ����ȭ �ϴ� �ݺ���
		/*--------------------------*/

		for (int i = 0; i < strlen(input_strArray); i++) // 
		{
			if ('A' <= input_strArray[i] || input_strArray[i] <= 'Z')
			{
				numMatrix[i] = (int)input_strArray[i] - 'A';
				loopFlag = false;
			}
			else if ('a' <= input_strArray[i] || input_strArray[i] <= 'z')
			{
				numMatrix[i] = (int)input_strArray[i] - ('a' - 'A');
				loopFlag = false;
			}
			else
			{
				printf("invaild charater : %c(%d)\n", input_strArray[i], i);
				printf("try input again\n");

				loopFlag = true;
				break;
			}
		}
	} while (loopFlag);
}