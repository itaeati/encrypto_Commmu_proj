#include "code.h" // 명시를 위해서

void main(void)
{
	int key_size = 0;
	int* keyMatrix = NULL;

	while (!errNum)
	{
		/*---------------------------*/
		// 1. key 행렬 만들기
		/*---------------------------*/
		
		keyMatrix = make_keyMatrix(&key_size);
		if (keyMatrix == NULL)
		{
			break;
		}
		
		/*---------------------------*/
		// 2. 평문입력
		/*---------------------------*/

		input_to_strArray();

#ifdef DEBUG
		printf("before Encode..\n");
		printStatus(); // 인코딩 후
#endif 

		/*---------------------------*/
		// 3. 암호화과정
		/*---------------------------*/

		encodingFunc(key_size, keyMatrix);

#ifdef DEBUG
		printf("after Encode..\n");
		printStatus(); // 인코딩 후
#endif 

		/*---------------------------*/
		// 4. 복호화과정
		/*---------------------------*/
		
		decodingFunc(key_size, deliverMatrix, keyMatrix);

		/*---------------------------*/
		// 5. 정리
		/*---------------------------*/
		
		_getch();

		system("cls"); // 다 완성했을 때
		if (!errNum)
		{
			printf("당신의 평문은 [%s] 입니다!\n", result_strArray);

#ifdef DEBUG
			printf("after Decode..\n");
			printStatus(); // 디코딩 후
#endif 
		}

		cleanUp_func();
		
		if (g_deleteKey_flag)
			free(keyMatrix);

		printLoopNum();

#if defined(DEBUG)
		if (1) // 루프 한번만 돌아보자
			break;
#endif 

	}

	if ((errNum == 4) || !(errNum == 0) )
		printf("errCode : %d\n", errNum);
	
	printf("엔터를 입력하세요!");
	do {} while (getchar() != '\n');
	
	return;
}