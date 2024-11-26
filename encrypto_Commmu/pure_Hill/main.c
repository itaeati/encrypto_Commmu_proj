#include "code.h" // Declare HEADER

void main(void)
{
	int key_size = 0;
	int* keyMatrix = NULL;
	int loopNum = 0;

	while (!errNum)
	{
		/*---------------------------*/
		// 1. Make key Array
		/*---------------------------*/
		
		keyMatrix = make_keyMatrix(&key_size);
		if (keyMatrix == NULL)
		{
			break;
		}
		
		/*---------------------------*/
		// 2. input plaintext
		/*---------------------------*/

		input_to_strArray();

		/*---------------------------*/
		// 3. encoding process
		/*---------------------------*/

		encodingFunc(key_size, keyMatrix);

		/*---------------------------*/
		// 4. decoding process
		/*---------------------------*/
		
		decodingFunc(key_size, deliverMatrix, keyMatrix);


		_getch();


		system("cls"); // if done, clear cmd window

		printf("your plaintext is [%s]\n",result_strArray);

		/*---------------------------*/
		// 5. Á¤¸®
		/*---------------------------*/


		cleanUp_func();

		
		if (g_deleteKey_flag)
			free(keyMatrix);

		printf("Num of loop : %d\n",loopNum++);
	}

	if ((errNum == 4) || !(errNum == 0) )
		printf("errCode : %d\n", errNum);
	
	printf("input Enter!");
	do {} while (getchar() != '\n');
	
	return;
}