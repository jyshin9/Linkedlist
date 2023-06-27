#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h> //malloc(memory allocation) �Լ��� ���Ե� ��� ����

typedef struct _Node {
	int data;
	struct _Node* next; //���� ����� �ּҸ� ������ �ڱ����� ����ü������, NODE����ü�� �ּҸ� ������ �� ����.
}Node;

Node* head; //�� �տ� ��带 ����ų head������

void init() {
	head = NULL;
}

void insert(int data) {
	/*1. �Ǿտ� ����
	�󸮽�Ʈ -> head�� newnode ����Ű��
	�ƴϸ� -> head�� ����Ű�� node�� newnode�� ����Ű�� head�� newnode ����Ű��
	2. �߰��� ����
	���� node�� ����Ű�� node�� newnode�� ����Ű�� ���� ��尡 newnode ����Ű��
	3. �ǵڿ� ����
	 newnode ���� �� ������ node�� next�����Ͱ� newnode�� ����Ű��*/

	Node* ptr; //Node������ �ϳ� ����
	Node* newNode = (Node*)malloc(sizeof(Node)); //newNode �Ҵ�. malloc�Լ��� ���Ͽ� ���ϵ� void*�� Node*�� ĳ����(����ȯ)
	newNode->data = data; //������ �Ҵ�
	newNode->next = NULL; //next ������ �ʱ�ȭ

	if (head == NULL) {
		head = newNode;
	}
	else {
		if (head->data > newNode->data) { //not empty, �� �տ� ��� �߰�.
			newNode->next = head;
			head = newNode;
			return;
		}
		for (ptr = head; ptr->next; ptr = ptr->next) { //�߰��� ��� �߰�.
			if (ptr->data<newNode->data && ptr->next->data>newNode->data) {
				newNode->next = ptr->next;
				ptr->next = newNode;
				return;
			}
		}
		ptr->next = newNode; //�� �ڿ� ��� �߰�.
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