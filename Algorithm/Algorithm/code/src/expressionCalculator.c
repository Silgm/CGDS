#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//#include "cgds/cgds_stack.h"
//
//#define EXP_CAL
//
//#ifdef EXP_CAL
///************************************************************************/
///* 
//通过后缀表达式计算表达式的值
//
//
//中缀表达式a + b*c + (d * e + f) * g，其转换成后缀表达式则为a b c * + d e * f  + g * +。
//转换过程需要用到栈，具体过程如下：
//1）如果遇到操作数，我们就直接将其输出。
//2）如果遇到操作符，则我们将其放入到栈中，遇到左括号时我们也将其放入栈中。
//3）如果遇到一个右括号，则将栈元素弹出，将弹出的操作符输出直到遇到左括号为止。注意，左括号只弹出并不输出。
//4）如果遇到任何其他的操作符，如（“+”， “*”，“（”）等，从栈中弹出元素直到遇到发现更低优先级的元素(或者栈为空)为止。弹出完这些元素后，
//	才将遇到的操作符压入到栈中。有一点需要注意，只有在遇到" ) "的情况下我们才弹出" ( "，其他情况我们都不会弹出" ( "。
//5）如果我们读到了输入的末尾，则将栈中所有元素依次弹出。
//*/
///************************************************************************/
//
//CGDS_GENERATE_STACK_INC(DoubleStack, double)
//
//
//#define ISOPERATOR(x) ((x == '+') || (x == '-') || (x == '*') || (x == '/'))
//#define ISLEGAL(x)	((x == '+') || (x == '-') || (x == '*') || (x == '/') || (isdigit(x)) || (x == '.'))
//static char * nextObj(char * exp) {
//	static int flagFirst = 1;
//	if (flagFirst) {
//		for (; !ISLEGAL(*exp) && *exp != '\0'; exp++);	//跳过一切不合法字符
//		flagFirst = 0;
//		return exp;
//	}
//
//	for (; !ISLEGAL(*exp) && *exp != '\0'; exp++);	//跳过一切不合法字符
//
//	if (isdigit(*exp) || *exp == '.') { //如果当前是数字
//		for (exp++; isdigit(*exp) || *exp == '.' && *exp != '\0'; exp++);//跳过数字
//		for (; !ISLEGAL(*exp); exp++);//再跳过非法字符
//
//	}
//	else if (ISOPERATOR(*exp)){	//如果是操作符
//		for (exp++; !ISLEGAL(*exp) && *exp != '\0'; exp++);	//跳过此操作符后的所有非法字符
//	}
//
//	return exp;
//}
//
//double revPolish (char *expPolish){
//	DoubleStack *stack = NULL;
//	double valA = 0.0, valB = 0.0;
//	double result = 0.0;
//	char *exp = expPolish;
//	DoubleStack_new(&stack, 20);
//
//	while (*(exp = nextObj(exp)) != '\0') {
//		if (isdigit(*exp) || *exp == '.') { //如果是数字, 就入栈
//			DoubleStack_push(stack, atof(exp));
//		} else { //如果是运算符, 就从栈顶弹出两个值进行相应的运算
//			switch (*exp)
//			{
//			case '+':
//				valA = DoubleStack_pop(stack);
//				valB = DoubleStack_pop(stack);
//				DoubleStack_push(stack, valB + valA);
//				break;
//			case '-':
//				valA = DoubleStack_pop(stack);
//				valB = DoubleStack_pop(stack);
//				DoubleStack_push(stack, valB - valA);
//				break;
//			case '*':
//				valA = DoubleStack_pop(stack);
//				valB = DoubleStack_pop(stack);
//				DoubleStack_push(stack, valB * valA);
//				break;
//			case '/':
//				valA = DoubleStack_pop(stack);
//				valB = DoubleStack_pop(stack);
//				DoubleStack_push(stack, valB / valA);
//				break;
//			default:
//				break;
//			}
//		}
//	}
//	result = DoubleStack_pop(stack);
//	DoubleStack_free(stack);
//	stack = NULL;
//	return result;
//}
//
//double exVal(char * exp) {
//	double result = 0.0;
//	
//	return result;
//}
//
//
//
//int main() {
//	char estr[] = "2 0 5 - *";
//	printf("%f\n", revPolish(estr));
//	return EXIT_SUCCESS;
//}
//
//
//CGDS_GENERATE_STACK_SRC(DoubleStack, double)
//
//#endif


int main() {

	return EXIT_SUCCESS;
}



