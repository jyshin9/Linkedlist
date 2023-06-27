#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h> //malloc(memory allocation) 함수가 포함된 헤더 파일

typedef struct _Node {
	int data;
	struct _Node* next; //다음 노드의 주소를 저장할 자기참조 구조체포인터, NODE구조체의 주소를 저장할 수 있음.
}Node;

Node* head; //맨 앞에 노드를 가리킬 head포인터

void init() {
	head = NULL;
}

void insert(int data) {
	/*1. 맨앞에 삽입
	빈리스트 -> head가 newnode 가리키게
	아니면 -> head가 가리키는 node를 newnode가 가리키고 head가 newnode 가리키게
	2. 중간에 삽입
	이전 node가 가리키는 node를 newnode가 가리키고 이전 노드가 newnode 가리키게
	3. 맨뒤에 삽입
	 newnode 생성 후 마지막 node의 next포인터가 newnode를 가리키게*/

	Node* ptr; //Node포인터 하나 생성
	Node* newNode = (Node*)malloc(sizeof(Node)); //newNode 할당. malloc함수에 의하여 리턴된 void*을 Node*로 캐스팅(형변환)
	newNode->data = data; //데이터 할당
	newNode->next = NULL; //next 포인터 초기화

	if (head == NULL) {
		head = newNode;
	}
	else {
		if (head->data > newNode->data) { //not empty, 맨 앞에 노드 추가.
			newNode->next = head;
			head = newNode;
			return;
		}
		for (ptr = head; ptr->next; ptr = ptr->next) { //중간에 노드 추가.
			if (ptr->data<newNode->data && ptr->next->data>newNode->data) {
				newNode->next = ptr->next;
				ptr->next = newNode;
				return;
			}
		}
		ptr->next = newNode; //맨 뒤에 노드 추가.
	}
}

int deleteNode(int data) {
	Node* curr, * prev;
	curr = prev = head;

	if (head == NULL) {
		printf("error: list is empty!\n");
		return -1;
	}

	if (head->data == data) {
		head = curr->next;
		curr->next = NULL;
		free(curr);
		return 1;
	}

	for (; curr; curr = curr->next) {
		if (curr->data == data) {
			prev->next = curr->next;
			curr->next = NULL;
			free(curr);
			return 1;
		}
	}

	printf("error: there is no %d!\n", data);
	return -1;
}

int search(int data) {
	Node* ptr;
	for (ptr = head; ptr; ptr = ptr->next) {
		if (ptr->data == data) {
			printf("there is %d!\n", data);
			return 1;
		}
	}
	printf("error: there is no %d!\n", data);
	return -1;
}

void printList() {
	Node* ptr;
	for (ptr = head; ptr->next; ptr = ptr->next) {
		printf("%d->", ptr->data);
	}
	printf("%d\n", ptr->data);
}

int main() {
	int data;

	init();
	insert(100);
	insert(300);
	insert(50);
	insert(200);
	printList();
	deleteNode(50);
	printList();
	deleteNode(200);
	printList();

	return 0;
}