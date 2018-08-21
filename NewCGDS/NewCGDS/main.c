#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdint.h>

#include "cgds/cgds_stack.h"
#include "cgds/cgds_arraylist.h"
#include "cgds/cgds_queue.h"

#define ENABLE_2

#ifdef ENABLE_2
typedef double	FigureType;
typedef char	OperatorType;
#define ERROR				-1
#define ELM_TAG_FIGURE		1
#define ELM_TAG_OPERATOR	0

typedef struct _ExpressionElm {
	union Elm
	{
		FigureType		unionElm_figure;
		OperatorType	unionElm_operator;
	};
	uint8_t elmTag;
}ExpressionElm;

CGDS_GENERATE_STACK_INC(ExpressionElmStack, ExpressionElm)
CGDS_GENERATE_STACK_SRC(ExpressionElmStack, ExpressionElm)

CGDS_GENERATE_ARRAYLIST_INC(ExpressionElmArray, ExpressionElm)
CGDS_GENERATE_ARRAYLIST_SRC(ExpressionElmArray, ExpressionElm)

static int8_t CurtIsFigure(const char expStr[])
{
	if (expStr == NULL)
		return ERROR;
	if ((*expStr >= '0' && *expStr <= '9') || (*expStr == '.'))
		return ELM_TAG_FIGURE;
	return ELM_TAG_OPERATOR;
}

static const char* JumpNext(const char expStr[])
{
	if (expStr == NULL)
		return NULL;
	if (CurtIsFigure(expStr))
	{
		for (; *expStr != '\0' && (CurtIsFigure(expStr) || (*expStr == ' ')); ++expStr);
	}
	else
	{
		for (++expStr; *expStr != '\0' && *expStr == ' '; ++expStr);
	}
	return expStr;
}

static void Convert_Str2NifixExpression(ExpressionElmArray *expArr, const char expStr[])
{
	if (expStr == NULL)
		return;

	ExpressionElm expElm;
	while (*expStr != '\0')
	{
		if (CurtIsFigure(expStr))
		{
			expElm.elmTag = ELM_TAG_FIGURE;
			expElm.unionElm_figure = atof(expStr);
		}
		else
		{
			expElm.elmTag = ELM_TAG_OPERATOR;
			expElm.unionElm_operator = *expStr;
		}
		expStr = JumpNext(expStr);
		ExpressionElmArray_append(expArr, expElm);
	}
}

static char OperatorPriorityTable[5][5] =
{
	/*+    -    *    /    (  */
	/* + */{ '=', '=', '<', '<', '>' },
	/* - */{ '=', '=', '<', '<', '>' },
	/* * */{ '>', '>', '=', '=', '>' },
	/* / */{ '>', '>', '=', '=', '>' },
	/* ( */{ '<', '<', '<', '<', '=' }
};

char OperatorPriorityCompare(char operatorA, char operatorB)
{
	size_t row, col;
	switch (operatorA)
	{
	case '+': row = 0; break;
	case '-': row = 1; break;
	case '*': row = 2; break;
	case '/': row = 3; break;
	case '(': row = 4; break;
	default: break;
	}

	switch (operatorB)
	{
	case '+': col = 0; break;
	case '-': col = 1; break;
	case '*': col = 2; break;
	case '/': col = 3; break;
	case '(': col = 4; break;
	default: break;
	}
	return OperatorPriorityTable[row][col];
}

static void Convert_NifixExpression2PostfixExpression(ExpressionElmArray *expArrNE, ExpressionElmArray *expArrPE)
{
	if (expArrNE == NULL || expArrPE == NULL)
		return;

	ExpressionElmStack *operatorStack;
	ExpressionElmStack_new(&operatorStack, 32);

	ExpressionElm expElm;


	for (int index = 0; index < ExpressionElmArray_length(expArrNE); ++index)
	{
		expElm = ExpressionElmArray_nth_data(expArrNE, index);
		if (expElm.elmTag == ELM_TAG_FIGURE)
		{
			ExpressionElmArray_append(expArrPE, expElm); //output
		}
		else
		{
			if (ExpressionElmStack_isEmpty(operatorStack))
			{
				ExpressionElmStack_push(operatorStack, expElm);
			}
			else if (expElm.unionElm_operator == '(')
			{
				ExpressionElmStack_push(operatorStack, expElm);
			}
			else if (expElm.unionElm_operator == ')')
			{
				ExpressionElm expElmTemp;
				for (;;)
				{
					if (!ExpressionElmStack_isEmpty(operatorStack))
					{
						expElmTemp = ExpressionElmStack_pop(operatorStack);
						if (expElmTemp.unionElm_operator != '(')
						{
							ExpressionElmArray_append(expArrPE, expElmTemp); //output
						}
						else
						{
							break;
						}
					}
					else
					{
						break;
					}
				}
			}
			else
			{
				char compareResult = OperatorPriorityCompare(expElm.unionElm_operator, ExpressionElmStack_top(operatorStack).unionElm_operator);
				if (compareResult == '>')
				{
					ExpressionElmStack_push(operatorStack, expElm);
				}
				else
				{
					while (!ExpressionElmStack_isEmpty(operatorStack) && OperatorPriorityCompare(expElm.unionElm_operator, ExpressionElmStack_top(operatorStack).unionElm_operator) != '>')
					{
						ExpressionElmArray_append(expArrPE, ExpressionElmStack_pop(operatorStack));//Ouput
					}
					ExpressionElmStack_push(operatorStack, expElm);
				}
			}
		}
	}
	while (!ExpressionElmStack_isEmpty(operatorStack))
	{
		ExpressionElmArray_append(expArrPE, ExpressionElmStack_pop(operatorStack));//Ouput
	}
	ExpressionElmStack_free(operatorStack);
}

static FigureType Calculate_PostfixExpression(ExpressionElmArray *expArrPE)
{
	ExpressionElmStack *stack;
	ExpressionElm expElm;
	ExpressionElmStack_new(&stack, 32);

	for (int index = 0; index < ExpressionElmArray_length(expArrPE); ++index)
	{
		expElm = ExpressionElmArray_nth_data(expArrPE, index);
		if (expElm.elmTag == ELM_TAG_FIGURE)
		{
			ExpressionElmStack_push(stack, expElm);
		}
		else
		{
			ExpressionElm expElmTemp;
			FigureType firstNum;
			FigureType secondNum;
			switch (expElm.unionElm_operator)
			{
			case '+':
				firstNum = ExpressionElmStack_pop(stack).unionElm_figure;
				secondNum = ExpressionElmStack_pop(stack).unionElm_figure;
				expElmTemp.elmTag = ELM_TAG_FIGURE;
				expElmTemp.unionElm_figure = secondNum + firstNum;
				ExpressionElmStack_push(stack, expElmTemp);
				break;
			case '-':
				firstNum = ExpressionElmStack_pop(stack).unionElm_figure;
				secondNum = ExpressionElmStack_pop(stack).unionElm_figure;
				expElmTemp.elmTag = ELM_TAG_FIGURE;
				expElmTemp.unionElm_figure = secondNum - firstNum;
				ExpressionElmStack_push(stack, expElmTemp);
				break;
			case '*':
				firstNum = ExpressionElmStack_pop(stack).unionElm_figure;
				secondNum = ExpressionElmStack_pop(stack).unionElm_figure;
				expElmTemp.elmTag = ELM_TAG_FIGURE;
				expElmTemp.unionElm_figure = secondNum * firstNum;
				ExpressionElmStack_push(stack, expElmTemp);
				break;
			case '/':
				firstNum = ExpressionElmStack_pop(stack).unionElm_figure;
				secondNum = ExpressionElmStack_pop(stack).unionElm_figure;
				expElmTemp.elmTag = ELM_TAG_FIGURE;
				expElmTemp.unionElm_figure = secondNum / firstNum;
				ExpressionElmStack_push(stack, expElmTemp);
				break;
			default:
				break;
			}
		}
	}
	FigureType result = ExpressionElmStack_top(stack).unionElm_figure;
	ExpressionElmStack_free(stack);
	return result;
}

FigureType eval(const char expStr[])
{
	ExpressionElmArray *expArr = NULL;
	ExpressionElmArray *convertedExpArr = NULL;

	ExpressionElmArray_new(&expArr, 32);
	ExpressionElmArray_new(&convertedExpArr, 32);

	Convert_Str2NifixExpression(expArr, expStr);
	Convert_NifixExpression2PostfixExpression(expArr, convertedExpArr);
	FigureType reuslt = Calculate_PostfixExpression(convertedExpArr);

	ExpressionElmArray_free(expArr);
	ExpressionElmArray_free(convertedExpArr);

	return reuslt;
}

int main(int argc, char *argv[])
{
	printf("%f", eval("-10+12"));
	return EXIT_SUCCESS;
}
#endif

#ifdef ENABLE_1

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

int BinaryTree_hasData(BinaryTree tree, BinaryTreeVal data) {
	int result = NO;
	if (tree != NULL) {
		if (tree->data == data) {
			return YES;
		}
		else {
			result = BinaryTree_hasData(tree->left, data);
			if (result) {
				return result;
			}

			result = BinaryTree_hasData(tree->right, data);
			if (result) {
				return result;
			}
		}
	}
	return result;
}

long BinaryTree_nodeNums(BinaryTree tree) {
	if (tree != NULL) {
		return 1 + BinaryTree_nodeNums(tree->left) + BinaryTree_nodeNums(tree->right);
	}
	else {
		return 0;
	}
}

long BinaryTree_getHigh(BinaryTree tree) {
	int leftHigh;
	int rightHigh;
	if (tree != NULL) {
		leftHigh = BinaryTree_getHigh(tree->left);
		rightHigh = BinaryTree_getHigh(tree->left);
		if (rightHigh > leftHigh) {
			return rightHigh + 1;
		}
		else {
			return leftHigh + 1;
		}
	}
	return 0;
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
	printf("\nMax:%d\n", BinaryTree_maxVal(tree, compare));
	printf("\nHas?:%d\n", BinaryTree_hasData(tree, -999));
	printf("\nNodeNums:%d\n", BinaryTree_nodeNums(tree));
	printf("\nTree High:%d\n", BinaryTree_getHigh(tree));
	return EXIT_SUCCESS;
}


#endif