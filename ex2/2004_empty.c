#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <stdbool.h>

struct TreeNode *findNode(struct TreeNode *root, int num);//找到对应数据域的结点
void findPath(struct TreeNode *root, struct TreeNode *p, struct TreeNode *q);//打印路径
bool judge(struct TreeNode *root, int start, int end);//判断两结点是否可达
struct TreeNode *createTreeNode(int val, struct TreeNode *left, struct TreeNode *right);//创建树的节点
struct TreeNode *createTreeWithLevelOrder(int *data, int size);//按照层次序列创建二叉树

typedef struct TreeNode {
	int id;
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
} TreeNode, *TreeNodePtr;

typedef struct ListNode {
	struct TreeNode *node; // 队列的值的类型是树节点指针
	struct ListNode *next;
} ListNode, *ListNodePtr;

typedef struct Queue {
	ListNodePtr dummyHead;
	ListNodePtr tail;
	int size;
} *QueuePtr;

// 创建链表的节点
ListNodePtr createListNode(TreeNodePtr node, ListNodePtr next) {
	ListNodePtr curr = (ListNodePtr) (malloc(sizeof(ListNode)));
	curr->node = node;
	curr->next = next;
	return curr;
}

// 创建树的节点
int TreeId = 0;

TreeNodePtr createTreeNode(int val, TreeNodePtr left, TreeNodePtr right) {
	TreeNodePtr curr = (TreeNodePtr) (malloc(sizeof(TreeNode)));
	curr->id = TreeId++;
	curr->val = val;
	curr->left = left;
	curr->right = right;
	return curr;
}

// 单链表队列初始化
QueuePtr InitQueue() {
	QueuePtr queue = (QueuePtr) malloc(sizeof(struct Queue));
	TreeNodePtr dummyTreeNode = createTreeNode(-1, NULL, NULL);
	queue->size = 0;
	queue->dummyHead = createListNode(dummyTreeNode, NULL);
	queue->tail = queue->dummyHead;
	return queue;
}

// 在 queue 的尾部添加一个元素的副本
void EnQueue(QueuePtr queue, TreeNodePtr node) {
	ListNodePtr curr = createListNode(node, NULL);
	queue->tail->next = curr;
	queue->tail = queue->tail->next;
//	if (node!=0)
		queue->size++;
}

// 删除 queue 中的第一个元素
void DeQueue(QueuePtr queue) {
	if (queue->size == 0) {
		perror("error! the size of queue is zero when call DeQueue().");
		return;
	}
	ListNodePtr head = queue->dummyHead->next;
	queue->dummyHead->next = head->next;
	queue->size--;
	if (queue->size == 0)
		queue->tail = queue->dummyHead;
	free(head);
}

// 如果 queue 中没有元素, 返回 true
bool QueueEmpty(QueuePtr queue) {
	return queue->size == 0;
}

// 返回 queue 中第一个元素的引用
TreeNodePtr GetHead(QueuePtr queue) {
	if (QueueEmpty(queue)) {
		perror("error! the size of queue is zero when call front().");
		return NULL;
	} else {
		return queue->dummyHead->next->node;
	}
}

int max(int a, int b) {
	return (a >= b) ? a : b;
}


// 将输入转换为数组
void getDigits(char *buff, int *data) {
	int len = strlen(buff);
	int index = 0;
	for (int i = 0; i < len; i++) {
		int num = 0;
		if (buff[i] == '#') {
			num = -1;
			i++;
		} else {
			while (buff[i] != ' ' && buff[i] != '\0') {
				num = num * 10 + (buff[i++] - '0');
			}
		}
		data[index++] = num;
	}
}


//功能：找到对应数据域的结点
//传参：root为整棵树的树根地址，num为想要查找的结点val值
//返回值：返回值为找到的结点的地址
struct TreeNode *findNode(struct TreeNode *root, int num) {
	QueuePtr Q=InitQueue();
	if (root!=0) 
		EnQueue(Q,root);
	while(!QueueEmpty(Q))
	{
//		printf("GetHead(Q)->val:%d",GetHead(Q)->val) ;
//		printf("\nnum:%d",num) ;
		if (GetHead(Q)->val==num) 
			return GetHead(Q);
		if (GetHead(Q)->left!=NULL) EnQueue(Q,GetHead(Q)->left);
		if (GetHead(Q)->right!=NULL) EnQueue(Q,GetHead(Q)->right);
		DeQueue(Q);
	}	
	return NULL;
}



//功能：打印路径
//传参：root为整棵树的树根地址，p为起始结点的地址，q为结束结点的地址，需要打印p到q的路径，路径包含p，q两个端点
//返回值：无返回值，该函数将完成打印路径的功能
void findPath(struct TreeNode *root, struct TreeNode *p, struct TreeNode *q) {
	if (p!=q) printf("%d->",p->val);
	if (p==q) printf("%d",p->val);
	if (findNode(p->left,q->val)) findPath(root,p->left,q);
	if (findNode(p->right,q->val)) findPath(root,p->right,q);
}


//功能：判断两结点是否可达
//传参：root为整棵树的树根地址，start为起始结点的val，end为结束结点的val
//返回值：返回值为布尔类型，返回true则表示可达，返回false表示不可达，不可达在主函数调用后会打印Too Far!!!，可达则打印两结点间路径
bool judge(struct TreeNode *root, int start, int end) {
	TreeNodePtr S=findNode(root,start),E=findNode(root,end);
	QueuePtr Q=InitQueue();
	EnQueue(Q,S);
	while(!QueueEmpty(Q))
	{
		if (GetHead(Q)==E) return true;
		if (GetHead(Q)->left!=NULL) EnQueue(Q,GetHead(Q)->left);
		if (GetHead(Q)->right!=NULL) EnQueue(Q,GetHead(Q)->right);
		DeQueue(Q);
	}
	return false;
}


//功能：按照层次序列创建二叉树
//传参：data为输入的层次序列经过处理后的数组，-1代表空结点，size为data数组的长度
//返回值：返回值为创建出来的二叉树的根结点的地址值
//注：本函数直接套用前面三题层次序列创建二叉树的函数即可，做过前三题的本题该函数不必单独设计
TreeNodePtr createTreeWithLevelOrder(int *data, int size) {
    if (size==0)
        return NULL;
    int i=0;
    QueuePtr Q=InitQueue();
    TreeNodePtr T=createTreeNode(data[i],NULL,NULL),temp;
    EnQueue(Q,T);
    i++;
    for (;i<size&&Q->size>0;i++)
    {
        if (data[i]!=-1)temp=createTreeNode(data[i],NULL,NULL);
        if (data[i]==-1) temp=NULL;
        if (i%2==1)
            if (GetHead(Q)!=NULL) GetHead(Q)->left=temp;
        if (i%2==0) 
            if (GetHead(Q)!=NULL) GetHead(Q)->right=temp;
        EnQueue(Q,temp);
        if (i%2==0) 
            DeQueue(Q);
    }
    return T;
}

int main(void) {
	int i, j, num, SIZE = 128;
	char buff[SIZE];
	scanf("%d\n", &num);
	fgets(buff, SIZE, stdin);
	char *pos = strchr(buff, '\n');          //查找换行符
	if (pos)                            //如果find不为空指针
		*pos = '\0';                    //就把一个空字符放在这里

	// Mac/Linux 替换\r
	pos = strchr(buff, '\r');
	if (pos)
		*pos = '\0';
	int *data = (int *) malloc(num * sizeof(int));
	getDigits(buff, data);
	struct TreeNode *root = createTreeWithLevelOrder(data, num), *start, *end;
	
	//以上为层次序列创建二叉树
	
	//以下为本题找路径的主函数代码
	
	scanf("%d %d", &i, &j);
	if (!judge(root, i, j))
		printf("Too Far!!!");
	else {
		start = findNode(root, i);
		end = findNode(root, j);
		findPath(root, start, end);
	}
	return 0;
}

