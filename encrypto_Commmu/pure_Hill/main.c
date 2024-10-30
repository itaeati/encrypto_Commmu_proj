#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int* make_keyArray(int* key_size)
{
	int* keyArray = NULL;
	printf("키의 크기를 입력하세요:");
	scanf("%d", key_size);
	printf("\n");

	if ((key_size > 0))
	{

	}
	keyArray = (int*)malloc((*key_size) * (*key_size) * sizeof(int));

	return keyArray;
}

void keyElement_input(int* keyArray, int key_size)
{
	
}



void main(void)
{
	int key_size = 0;
	int* keyArr = make_keyArray(&key_size);
	

	return;
}