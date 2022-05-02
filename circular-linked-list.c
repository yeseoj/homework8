/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* �ʿ��� ������� �߰� */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* �Լ� ����Ʈ */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	printf("[----- �忹��, 2021041018 -----]\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {
	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* �޸� ���� */
int freeList(listNode* h){
	listNode* p = h->rlink;
	listNode* prev = NULL;

	/* ����常 �����ϴ� �� �ƴ϶�� �Ʒ� ���� ���� */
	if (h->rlink != h) {
		while (p != NULL && p != h) {
			prev = p;
			p = p->rlink;
			free(prev);
		}

	}
	/* ����� ���� */
	free(h);

	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(listNode* h, int key) {
	/* ����Ʈ�� ���ǵ��� ���� ��� */
	if (h == NULL) {
		printf("Please initialize list first.\n");
		return 0;
	}
	/* ����Ʈ�� ����� ��� */
	else if (h->rlink == h) {
		printf("�� ����Ʈ�� ù ��° ���� ���Ե˴ϴ�.\n");
		insertFirst(h, key);
		return 0;
	}
	
	listNode* lastnode = h->llink;
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->llink = node->rlink = NULL;
	node->key = key;

	/* ������ ����� rlink�� ��� �ּ� ����
	 * ����� llink���� ���� ������ ��� �ּ� ����, ����� rlink���� ��� ��� �ּ� ����
	 * ��� ����� llink�� ��� �ּ� ���� */
	lastnode->rlink = node;
	node->llink = lastnode;
	node->rlink = h;
	h->llink = node;

	return 1;
}


/**
 * list�� ������ ��� ����
 */
int deleteLast(listNode* h) {
	/* ����Ʈ�� ����� ��� */
	if (h->rlink == h) {
		printf("����Ʈ�� ������ϴ�.\n");
		return 0;
	}

	listNode* lastnode = h->llink;

	/* �������� llink�� ���� ��� �ּ� ����
	 * ���� ����� rlink�� ��� ��� �ּ� �����ϰ� ������ ��� ���� */
	h->llink = lastnode->llink;
	lastnode->llink->rlink = h;

	free(lastnode);

	return 1;
}


/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(listNode* h, int key) {
	/* ����Ʈ�� ���ǵ��� ���� ��� */
	if (h == NULL) {
		printf("Please initialize list first.\n");
		return 0;
	}

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->llink = node->rlink = NULL;
	node->key = key;
	
	/** ����� llink�� ������ �ּ� ����, ����� rlink�� �������� rlink ����
	 * �������� rlink�� llink�� ��� �ּ� ����, ��� ����� rlink�� ��� ����
	 */
	node->llink = h;
	node->rlink = h->rlink;
	h->rlink->llink = node;
	h->rlink = node;

	return 1;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(listNode* h) {
	/* ����Ʈ�� ����� ��� */
	if (h->rlink == h) {
		printf("����Ʈ�� ������ϴ�.\n");
		return 0;
	}

	listNode* firstnode = h->rlink;

	/**
	 * �������� rlink�� ���� ��� �ּ� ����, ���� ����� llink�� ������ �ּ� ����
	 * ���� ù��° ��� ����
	 */
	h->rlink = firstnode->rlink;
	firstnode->rlink->llink = h;

	free(firstnode);

	return 1;

}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(listNode* h) {
	/* ����Ʈ�� ����� ��� */
	if (h->rlink == h) {
		printf("����Ʈ�� ������ϴ�.\n");
		return 0;
	}

	listNode* p = h->rlink;
	listNode* temp = p;

	/**
	 * temp�� �̿��Ͽ� p->rlink�� p->llink�� ��ȯ
	 */
	while (p != h) {
		p = temp;
		temp = p->rlink;
		p->rlink = p->llink;
		p->llink = temp;
	}

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(listNode* h, int key) {
	/* ����Ʈ�� ���ǵ��� ���� ��� */
	if (h == NULL) {
		printf("Please initialize list first.\n");
		return 1;
	}
	/* ����Ʈ�� ����� ��� */
	else if (h->rlink == h) {
		printf("�� ����Ʈ�� ù ��° ���� ���Ե˴ϴ�.\n");
		insertFirst(h, key);
		return 1;
	}
	
	listNode* p = h->rlink;
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->llink = node->rlink = NULL;
	node->key = key;

	/** �Ϲ����� ���
	 * ���� ����� rlink�� ��� �ּ� ����, ����� llink�� ���� ��� �ּ� ����
	 * ����� rlink�� ���� ��� �ּ� ����, ���� ����� llink�� ��� �ּ� ����
	 */
	while (p != h) {
		if (p->key >= key) {
			p->llink->rlink = node;
			node->llink = p->llink;
			node->rlink = p;
			p->llink = node;
			return 0;
		}
		p = p->rlink;
	}
	/* �� ū key ���� ���� ��尡 ���� ���, ������ ���� ���� */
	printf("������ ���� ���Ե˴ϴ�.\n");
	insertLast(h, key);

	return 0;
}


/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(listNode* h, int key) {
	/* ����Ʈ�� ����� ��� */
	if (h->rlink == h) {
		printf("����Ʈ�� ������ϴ�.\n");
		return 0;
	}

	listNode* keynode = h->rlink;

	/** ó������ ������ ����� ���
	 * �������� llink, rlink�� ������ �ּ� ����
	 * �ش� ��� ����
	*/
	if (keynode->rlink == h) {
		if (keynode->key == key) {
			h->llink = h->rlink = h;
			free(keynode);
			return 0;
		}
	}
	/** �߰��̰ų� ������ ����� ���
	 * ���� ����� rlink�� ���� ��� �ּҸ� ����
	 * ���� ����� llink�� ���� ��� �ּҸ� ����
	 * �ش� ��� ����
	*/
	else {
		while (keynode != h) {
			if (keynode->key == key) {
				keynode->llink->rlink = keynode->rlink;
				keynode->rlink->llink = keynode->llink;
				free(keynode);
				return 0;
			}
			keynode = keynode->rlink;
		}
	}
	/* �ش��ϴ� ��尡 ���� ��� */
	printf("�ش� key�� ���� ��带 ã�� ���߽��ϴ�.\n");

	return 0;
}


