#include "code.h" // ��ø� ���ؼ�

void main(void)
{
	int key_size = 0;
	int* keyMatrix = NULL;
	int loopNum = 0;

	while (!errNum)
	{
		/*---------------------------*/
		// 1. key ��� �����
		/*---------------------------*/
		
		keyMatrix = make_keyMatrix(&key_size);
		if (keyMatrix == NULL)
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

		encodingFunc(key_size, keyMatrix);

		/*---------------------------*/
		// 4. ��ȣȭ����
		/*---------------------------*/
		
		decodingFunc(key_size, deliverMatrix, keyMatrix);


		_getch();


		system("cls"); // �� �ϼ����� ��
		printf("����� ���� [%s] �Դϴ�!\n",result_strArray);

		/*---------------------------*/
		// 5. ����
		/*---------------------------*/


		cleanUp_func();

		
		if (g_deleteKey_flag)
			free(keyMatrix);

		printf("Num of loop : %d\n",loopNum++);
	}

	if ((errNum == 4) || !(errNum == 0) )
		printf("errCode : %d\n", errNum);
	
	printf("���͸� �Է��ϼ���!");
	do {} while (getchar() != '\n');
	
	return;
}