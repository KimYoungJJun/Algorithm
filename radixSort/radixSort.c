#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
struct node {
	int value;
	struct node* next;
	struct node* prev;
};
typedef struct node node;
node* createNode() {
	node* newNode = (node*)malloc(sizeof(node));
	if (newNode == NULL) {
		printf("newNode error\n");
		exit(EXIT_FAILURE);
	}
	newNode->value = -1;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}
void initNode(node* curNode,int value) {
	curNode->next = NULL;
	curNode->prev = NULL;
	curNode->value = value;
}
int is_empty(node* bucket_index) {
	if (bucket_index->value == -1)
		return TRUE;
	else
		return FALSE;
}
void enqueue(node* curNode,node* bucket_index) {
	node* newNode=NULL;
	if ( is_empty(bucket_index) ) {
		bucket_index->value = curNode->value;
		bucket_index->next = NULL;
		bucket_index->prev = NULL;
	}
	else {
		while ( bucket_index->next != NULL) {
			bucket_index = bucket_index->next;
		}
		newNode = createNode();
		newNode->value = curNode->value;
		newNode->next = NULL;
		newNode->prev = bucket_index;
		bucket_index->next = newNode;
	}
}
void dequeue(node* bucket_index,int result[],int length,int* index) {
	if ( !is_empty(bucket_index) ) {
		while (bucket_index->next != NULL) {
			result[*index] = bucket_index->value;
			(*index)++;
			bucket_index = bucket_index->next;
			free(bucket_index->prev);
			bucket_index->prev = NULL;
		}
		result[*index] = bucket_index->value;
		(*index)++;
		free(bucket_index);
	}
}
void initArray(int arr[], int length) {
	int i;
	for (i = 0; i < length; i++) {
		arr[i] = -1;
	}
}
int maxDigit(int arr[],int length_arr) {
	int i, maxDigitCount = 0, curDigitCount = 0;

	for (i = 0; i < length_arr; i++) {
		while (arr[i] > 0) {
			arr[i] /= 10;
			curDigitCount++;
		}
		if (maxDigitCount < curDigitCount) {
			maxDigitCount = curDigitCount;
		}
		curDigitCount = 0;
	}
	return maxDigitCount;
}
void copyArray(int from[],int to[],int length_from) {
	int i;
	for (i = 0; i < length_from; i++) {
		to[i] = from[i];
	}
}
void radixSort(int arr[],int result[],node bucket[],int length_arr) {
	int i,digit,index=0, division = 10,maxDigitCount=0;
	int imsi[10];
	node* curNode;
	
	for (digit = 0; digit < 10; digit++) {
		initNode(&bucket[digit], -1);
	}
	copyArray(arr, imsi, length_arr);
	maxDigitCount = maxDigit(imsi, length_arr);

	for (int p = 0; p < maxDigitCount;p++) {
		for (i = 0; i < length_arr; i++) {
			for (digit = 0; digit < 10; digit++) {
				if (arr[i] % division == digit) {
					curNode = createNode();
					initNode(curNode, arr[i]);
					enqueue(curNode, &bucket[digit]);
					arr[i] /= 10;
					free(curNode);
					break;
				}
			}
		}
		for (digit = 0; digit < 10; digit++) {
			if (!is_empty(&bucket[digit])) {
				dequeue(&bucket[digit], result, length_arr, &index);
			}
		}
		index = 0;
	}
}
void print(int result[],int length) {
	int i;
	for (i = 0; i < length; i++) {
		printf("%4d", result[i]);
	}
}
void main() {
	int result[10], arr[10] = {54,84,44,39,10,91,72,25,77,66};
	int length_result = sizeof(result) / sizeof(int),length_arr = sizeof(arr) / sizeof(int);
	node bucket[10];

	initArray(result, length_result);
	radixSort(arr,result, bucket, length_arr);
	print(result, length_result);
}