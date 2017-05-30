#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

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
int BinaryTree_createFromArray_levelOrder(BinaryTree *tree, BinaryTreeVal arr[], long arrLength) {
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

void BinaryTree_prevOrderRev(BinaryTree tree, void (pFunc_Handle)(BinaryTreeNode *)) {
	if (tree != NULL) {
		pFunc_Handle(tree);
		BinaryTree_prevOrderRev(tree->left, pFunc_Handle);
		BinaryTree_prevOrderRev(tree->right, pFunc_Handle);
	}
}

void BinaryTree_InOrderRev(BinaryTree tree, void (pFunc_Handle)(BinaryTreeNode *)) {
	if (tree != NULL) {
		BinaryTree_prevOrderRev(tree->left, pFunc_Handle);
		pFunc_Handle(tree);
		BinaryTree_prevOrderRev(tree->right, pFunc_Handle);
	}
}

void BinaryTree_postOrderRev(BinaryTree tree, void (pFunc_Handle)(BinaryTreeNode *)) {
	if (tree != NULL) {
		BinaryTree_prevOrderRev(tree->left, pFunc_Handle);
		BinaryTree_prevOrderRev(tree->right, pFunc_Handle);
		pFunc_Handle(tree);
	}
}

void BinaryTree_levelOrderRev(BinaryTree tree, void (pFunc_Handle)(BinaryTreeNode *) ) {
	BinaryTreeNodeQueue *nodeQueue;
	BinaryTreeNode *thisNode = NULL;

	if (tree == NULL)
		return;
	BinaryTreeNodeQueue_new(&nodeQueue);
	BinaryTreeNodeQueue_en(nodeQueue, tree);
	while (!BinaryTreeNodeQueue_isEmpty(nodeQueue)) {
		thisNode = BinaryTreeNodeQueue_de(nodeQueue);
		pFunc_Handle(thisNode);
		if (thisNode->left != NULL)
			BinaryTreeNodeQueue_en(nodeQueue, thisNode->left);

		if (thisNode->right != NULL)
			BinaryTreeNodeQueue_en(nodeQueue, thisNode->right);
	}
	BinaryTreeNodeQueue_free(&nodeQueue);
}

static BinaryTreeVal max3(BinaryTreeVal a, BinaryTreeVal b, BinaryTreeVal c, int (*pFunc_Compare)(BinaryTreeVal , BinaryTreeVal )) {
	int maxVal = a;
	if (pFunc_Compare(maxVal, b) < 0)
		maxVal = b;
	if (pFunc_Compare(maxVal, c) < 0)
		maxVal = c;
	return maxVal;
}

static BinaryTreeVal BinaryTree_maxVal_private(BinaryTree tree, int *_out_flag, int(*pFunc_Compare)(BinaryTreeVal, BinaryTreeVal)) {
	BinaryTreeVal leftMax, temp;
	BinaryTreeVal rightMax;
	BinaryTreeVal maxVal;
	int leftFlag = 0;
	int rightFlag = 0;
	memset(&maxVal, 0, sizeof(maxVal));
	if (tree != NULL) {
		maxVal = tree->data;
		leftMax = maxVal;
		rightMax = maxVal;
		temp = BinaryTree_maxVal_private(tree->left, &leftFlag, pFunc_Compare);
		if (leftFlag == 0) {
			leftMax = temp;
		}

		temp = BinaryTree_maxVal_private(tree->right, &rightFlag, pFunc_Compare);
		if (rightFlag == 0) {
			rightMax = temp;
		}
		
		return max3(maxVal, leftMax, rightMax, pFunc_Compare);
	}
	*_out_flag = 1;
	return maxVal;

}

BinaryTreeVal BinaryTree_maxVal(BinaryTree tree, int(*pFunc_Compare)(BinaryTreeVal, BinaryTreeVal)) {
	int flag = 0;
	return BinaryTree_maxVal_private(tree, &flag, pFunc_Compare);
}

//BinaryTreeVal BinaryTree_maxVal(BinaryTree tree) {
//	BinaryTreeVal 
//leftMax;
//	BinaryTreeVal rightMax;
//	BinaryTreeVal maxVal;
//	memset(&maxVal, 0, sizeof(maxVal));
//	if (tree != NULL) {
//		maxVal = tree->data;
//		leftMax = BinaryTree_maxVal(tree->left);
//		rightMax = BinaryTree_maxVal(tree->right);
//		if (leftMax > maxVal) {
//			return leftMax;
//		}
//		else if (rightMax > maxVal) {
//			return rightMax;
//		}
//		return maxVal;
//	}
//
//	return maxVal;
//}

void HandleFunc(BinaryTreeNode * node) {
	printf("%d,", node->data);
}

int compare(BinaryTreeVal a, BinaryTreeVal b) {
	if (a > b) {
		return -1;
	}
	else if (a < b) {
		return 1;
	}
	return 0;
}


int main() {
	int arr[] = { 123,456,488,45658,18,12,1,8,2,4,6,-20200,-22,-8,-999 };
	BinaryTree tree;
	BinaryTree_createFromArray_levelOrder(&tree, arr, MF_ARR_LEN(arr));
	BinaryTree_prevOrderRev(tree, HandleFunc);
	printf("\nMax:%d", BinaryTree_maxVal(tree, compare));

	return EXIT_SUCCESS;
}


