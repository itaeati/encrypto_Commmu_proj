#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int* make_keyArray(int* key_size)
{
	/*--------------------------*/
	// 1. Ű ��� ������ �Է¹ޱ�
	/*--------------------------*/

	int* keyArray = NULL;
	printf("Ű�� ũ�⸦ �Է��ϼ���:");
	scanf("%d", key_size);
	printf("\n");

	if (!(key_size > 0))
	{
		goto make_keyArray_exit;
	}

	/*--------------------------*/
	// 2. Ű��� �Ҵ�
	/*--------------------------*/
	
	keyArray = (int*)malloc((int)pow(*key_size, 2) * sizeof(int));

	if (keyArray == NULL)
	{
		goto make_keyArray_exit;
	}

	// Ȥ�ø��� �� ������?

make_keyArray_exit:
	return keyArray;
}

void keyElement_input(int* keyArray, int key_size)
{
	
}

void main(void)
{
	int key_size = 0;
	int* keyArr = make_keyArray(&key_size);

	if (keyArr == NULL)
	{
		goto main_exit;
	}

	keyElement_input(keyArr, key_size);

main_exit:
	return;
}