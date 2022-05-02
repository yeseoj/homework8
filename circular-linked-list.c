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
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
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

	printf("[----- 장예서, 2021041018 -----]\n");

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
	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
	listNode* p = h->rlink;
	listNode* prev = NULL;

	/* 헤드노드만 존재하는 게 아니라면 아래 과정 수행 */
	if (h->rlink != h) {
		while (p != NULL && p != h) {
			prev = p;
			p = p->rlink;
			free(prev);
		}

	}
	/* 헤드노드 해제 */
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
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	/* 리스트가 정의되지 않은 경우 */
	if (h == NULL) {
		printf("Please initialize list first.\n");
		return 0;
	}
	/* 리스트가 비었을 경우 */
	else if (h->rlink == h) {
		printf("빈 리스트의 첫 번째 노드로 삽입됩니다.\n");
		insertFirst(h, key);
		return 0;
	}
	
	listNode* lastnode = h->llink;
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->llink = node->rlink = NULL;
	node->key = key;

	/* 마지막 노드의 rlink에 노드 주소 대입
	 * 노드의 llink에는 기존 마지막 노드 주소 대입, 노드의 rlink에는 헤더 노드 주소 대입
	 * 헤더 노드의 llink에 노드 주소 대입 */
	lastnode->rlink = node;
	node->llink = lastnode;
	node->rlink = h;
	h->llink = node;

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	/* 리스트가 비었을 경우 */
	if (h->rlink == h) {
		printf("리스트가 비었습니다.\n");
		return 0;
	}

	listNode* lastnode = h->llink;

	/* 헤더노드의 llink에 이전 노드 주소 대입
	 * 이전 노드의 rlink에 헤더 노드 주소 대입하고 마지막 노드 삭제 */
	h->llink = lastnode->llink;
	lastnode->llink->rlink = h;

	free(lastnode);

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	/* 리스트가 정의되지 않은 경우 */
	if (h == NULL) {
		printf("Please initialize list first.\n");
		return 0;
	}

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->llink = node->rlink = NULL;
	node->key = key;
	
	/** 노드의 llink에 헤더노드 주소 대입, 노드의 rlink에 헤더노드의 rlink 대입
	 * 헤더노드의 rlink의 llink에 노드 주소 대입, 헤더 노드의 rlink에 노드 대입
	 */
	node->llink = h;
	node->rlink = h->rlink;
	h->rlink->llink = node;
	h->rlink = node;

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	/* 리스트가 비었을 경우 */
	if (h->rlink == h) {
		printf("리스트가 비었습니다.\n");
		return 0;
	}

	listNode* firstnode = h->rlink;

	/**
	 * 헤더노드의 rlink에 다음 노드 주소 대입, 다음 노드의 llink에 헤더노드 주소 대입
	 * 이후 첫번째 노드 삭제
	 */
	h->rlink = firstnode->rlink;
	firstnode->rlink->llink = h;

	free(firstnode);

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	/* 리스트가 비었을 경우 */
	if (h->rlink == h) {
		printf("리스트가 비었습니다.\n");
		return 0;
	}

	listNode* p = h->rlink;
	listNode* temp = p;

	/**
	 * temp를 이용하여 p->rlink와 p->llink를 교환
	 */
	while (p != h) {
		p = temp;
		temp = p->rlink;
		p->rlink = p->llink;
		p->llink = temp;
	}

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
	/* 리스트가 정의되지 않은 경우 */
	if (h == NULL) {
		printf("Please initialize list first.\n");
		return 1;
	}
	/* 리스트가 비었을 경우 */
	else if (h->rlink == h) {
		printf("빈 리스트의 첫 번째 노드로 삽입됩니다.\n");
		insertFirst(h, key);
		return 1;
	}
	
	listNode* p = h->rlink;
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->llink = node->rlink = NULL;
	node->key = key;

	/** 일반적인 경우
	 * 이전 노드의 rlink에 노드 주소 대입, 노드의 llink에 이전 노드 주소 대입
	 * 노드의 rlink에 기존 노드 주소 대입, 기존 노드의 llink에 노드 주소 대입
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
	/* 더 큰 key 값을 가진 노드가 없을 경우, 마지막 노드로 삽입 */
	printf("마지막 노드로 삽입됩니다.\n");
	insertLast(h, key);

	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	/* 리스트가 비었을 경우 */
	if (h->rlink == h) {
		printf("리스트가 비었습니다.\n");
		return 0;
	}

	listNode* keynode = h->rlink;

	/** 처음이자 마지막 노드인 경우
	 * 헤더노드의 llink, rlink에 헤더노드 주소 대입
	 * 해당 노드 삭제
	*/
	if (keynode->rlink == h) {
		if (keynode->key == key) {
			h->llink = h->rlink = h;
			free(keynode);
			return 0;
		}
	}
	/** 중간이거나 마지막 노드인 경우
	 * 이전 노드의 rlink에 다음 노드 주소를 대입
	 * 다음 노드의 llink에 이전 노드 주소를 대입
	 * 해당 노드 삭제
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
	/* 해당하는 노드가 없는 경우 */
	printf("해당 key를 가진 노드를 찾지 못했습니다.\n");

	return 0;
}


