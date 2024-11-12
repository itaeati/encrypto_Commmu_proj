#include "Librarys.h" // ��ø� ���ؼ�
#include "globalVar.h"
#include "Matrix.h"
#include "Utils.h"

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

		system("clear"); // �� �ϼ����� ��
		printf("����� ���� [%s] �Դϴ�!\n",result_strArray);

		/*---------------------------*/
		// 5. ����
		/*---------------------------*/


		cleanUp_func();

		
		if (g_deleteKey_flag)
			free(keyArr);


	}

	if ((errNum == 4) || !(errNum == 0) )
		printf("errCode : %d\n", errNum);
	
	printf("���͸� �Է��ϼ���!");
	do {} while (getchar() == '\n');
	
	return;
}