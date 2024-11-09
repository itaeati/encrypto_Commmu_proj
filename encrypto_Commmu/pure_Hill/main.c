#include "Librarys.h" // ��ø� ���ؼ�
#include "globalVar.h"
#include "Matrix.h"

void main(void)
{
	int key_size = 0;
	int* keyArr = NULL;

	while (!errNum)
	{
		/*---------------------------*/
		// 1. key ��� �����
		/*---------------------------*/
		
		keyArr = make_keyMatrix(&key_size);
		if (keyArr == NULL)
		{
			break;
		}

		/*---------------------------*/
		// 2. ���Է�
		/*---------------------------*/

		input_to_strArray();

		/*---------------------------*/
		// 3. ��ȣȭ����
		/*---------------------------*/

		/*---------------------------*/
		// 4. ��ȣȭ����
		/*---------------------------*/

		// system("clear"); // �� �ϼ����� ��
		// printf("����� ���� [%s] �Դϴ�!\n");

		/*---------------------------*/
		// 5. ����
		/*---------------------------*/


		cleanUp_func();

		if (deleteKey_flag)
			free(keyArr);


	}

	if ((errNum == 4) || !(errNum == 0) )
		printf("errCode : %d\n", errNum);
	
	printf("���͸� �Է��ϼ���!");
	do {} while (getch() == '\n');
	
	return;
}

void cleanUp_func(void)
{
	detNum = 1;
	maxIdx = 0;
	peddedSize = 0;
	deleteKey_flag = false;

	memset(input_strArray, 0, STR_SIZE * sizeof(char));
	memset(deliverMatrix, 0, STR_SIZE * sizeof(int));
	memset(numMatrix, 0, STR_SIZE * sizeof(int));
}