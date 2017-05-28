#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#include "cgds/cgds_tool.h"
#include "cgds/cgds_queue.h"



typedef int BinaryTreeVal;
typedef struct _BinaryTreeNode {
	BinaryTreeVal data;
	struct _BinaryTreeNode * left;
	struct _BinaryTreeNode * right;
}BinaryTreeNode, *BinaryTree;
CGDS_GENERATE_QUEUE_INC(BinaryTreeNodeQueue, BinaryTreeNode *)
CGDS_GENERATE_QUEUE_SRC(BinaryTreeNodeQueue, BinaryTreeNode *)
/*²ãÐò´´½¨¶þ²æÊ÷*/
int BinaryTree_createFromArray(BinaryTree *tree, BinaryTreeVal arr[], long arrLength) {
	BinaryTreeNode *rootNode = NULL, *thisNode = NULL, *newNodeLeft = NULL, *newNodeRight = NULL;
	BinaryTreeNodeQueue *nodeQueue;

	long index = 0;

	if (arrLength <= 0 || arr == NULL) {
		*tree = NULL;
		return SUCCESS;
	}

	rootNode = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
	if (rootNode == NULL) {
		return FAILURE;
	}
	BinaryTreeNodeQueue_new(&nodeQueue);
	BinaryTreeNodeQueue_en(nodeQueue, rootNode);
	rootNode->data = arr[index++];
	rootNode->left = NULL;
	rootNode->right = NULL;
	while (index < arrLength) {
		while (!BinaryTreeNodeQueue_isEmpty(nodeQueue)) {
			thisNode = BinaryTreeNodeQueue_de(nodeQueue);

			if (index < arrLength){
				newNodeLeft = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
				if (newNodeLeft == NULL) {
					*tree = rootNode;
					return FAILURE;
				}
				newNodeLeft->data = arr[index++];
				newNodeLeft->left = NULL;
				newNodeLeft->right = NULL;
				thisNode->left = newNodeLeft;
				BinaryTreeNodeQueue_en(nodeQueue, thisNode->left);
			}

			if (index < arrLength) {
				newNodeRight = (BinaryTreeNode *)malloc(sizeof(BinaryTreeNode));
				if (newNodeRight == NULL) {
					*tree = rootNode;
					return FAILURE;
				}
				newNodeRight->data = arr[index++];
				newNodeRight->left = NULL;
				newNodeRight->right = NULL;
				thisNode->right = newNodeRight;
				BinaryTreeNodeQueue_en(nodeQueue, thisNode->right);
			}
		}
	}
	BinaryTreeNodeQueue_free(&nodeQueue);
	*tree = rootNode;
	return SUCCESS;
}

void BinaryTree_levelOrderRev(BinaryTree tree) {
	BinaryTreeNodeQueue *nodeQueue;
	BinaryTreeNode *thisNode = NULL;

	if (tree == NULL)
		return;
	BinaryTreeNodeQueue_new(&nodeQueue);
	BinaryTreeNodeQueue_en(nodeQueue, tree);
	while (!BinaryTreeNodeQueue_isEmpty(nodeQueue)) {
		thisNode = BinaryTreeNodeQueue_de(nodeQueue);
		printf("%d", thisNode->data);
		
		if (thisNode->left != NULL)
			BinaryTreeNodeQueue_en(nodeQueue, thisNode->left);

		if (thisNode->right != NULL)
			BinaryTreeNodeQueue_en(nodeQueue, thisNode->right);
	}
	BinaryTreeNodeQueue_free(&nodeQueue);
}


int main() {
	int arr[] = { 3,2,5,8,4,7,6,9 };
	BinaryTree tree;
	BinaryTree_createFromArray(&tree, arr, MF_ARR_LEN(arr));
	BinaryTree_levelOrderRev(tree);
	return EXIT_SUCCESS;
}


