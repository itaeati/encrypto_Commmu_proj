#include "code.h" // ��ø� ���ؼ�

void main(void)
{
	int key_size = 0;
	int* keyMatrix = NULL;

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

#ifdef DEBUG
		printf("before Encode..\n");
		printStatus(); // ���ڵ� ��
#endif 

		/*---------------------------*/
		// 3. ��ȣȭ����
		/*---------------------------*/

		encodingFunc(key_size, keyMatrix);

#ifdef DEBUG
		printf("after Encode..\n");
		printStatus(); // ���ڵ� ��
#endif 

		/*---------------------------*/
		// 4. ��ȣȭ����
		/*---------------------------*/
		
		decodingFunc(key_size, deliverMatrix, keyMatrix);

		/*---------------------------*/
		// 5. ����
		/*---------------------------*/
		
		_getch();

		system("cls"); // �� �ϼ����� ��
		if (!errNum)
		{
			printf("����� ���� [%s] �Դϴ�!\n", result_strArray);

#ifdef DEBUG
			printf("after Decode..\n");
			printStatus(); // ���ڵ� ��
#endif 
		}

		cleanUp_func();
		
		if (g_deleteKey_flag)
			free(keyMatrix);

		printLoopNum();

#if defined(DEBUG)
		if (1) // ���� �ѹ��� ���ƺ���
			break;
#endif 

	}

	if ((errNum == 4) || !(errNum == 0) )
		printf("errCode : %d\n", errNum);
	
	printf("���͸� �Է��ϼ���!");
	do {} while (getchar() != '\n');
	
	return;
}