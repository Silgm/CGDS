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
//ͨ����׺���ʽ������ʽ��ֵ
//
//
//��׺���ʽa + b*c + (d * e + f) * g����ת���ɺ�׺���ʽ��Ϊa b c * + d e * f  + g * +��
//ת��������Ҫ�õ�ջ������������£�
//1��������������������Ǿ�ֱ�ӽ��������
//2����������������������ǽ�����뵽ջ�У�����������ʱ����Ҳ�������ջ�С�
//3���������һ�������ţ���ջԪ�ص������������Ĳ��������ֱ������������Ϊֹ��ע�⣬������ֻ�������������
//4����������κ������Ĳ��������磨��+���� ��*�������������ȣ���ջ�е���Ԫ��ֱ���������ָ������ȼ���Ԫ��(����ջΪ��)Ϊֹ����������ЩԪ�غ�
//	�Ž������Ĳ�����ѹ�뵽ջ�С���һ����Ҫע�⣬ֻ��������" ) "����������ǲŵ���" ( "������������Ƕ����ᵯ��" ( "��
//5��������Ƕ����������ĩβ����ջ������Ԫ�����ε�����
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
//		for (; !ISLEGAL(*exp) && *exp != '\0'; exp++);	//����һ�в��Ϸ��ַ�
//		flagFirst = 0;
//		return exp;
//	}
//
//	for (; !ISLEGAL(*exp) && *exp != '\0'; exp++);	//����һ�в��Ϸ��ַ�
//
//	if (isdigit(*exp) || *exp == '.') { //�����ǰ������
//		for (exp++; isdigit(*exp) || *exp == '.' && *exp != '\0'; exp++);//��������
//		for (; !ISLEGAL(*exp); exp++);//�������Ƿ��ַ�
//
//	}
//	else if (ISOPERATOR(*exp)){	//����ǲ�����
//		for (exp++; !ISLEGAL(*exp) && *exp != '\0'; exp++);	//�����˲�����������зǷ��ַ�
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
//		if (isdigit(*exp) || *exp == '.') { //���������, ����ջ
//			DoubleStack_push(stack, atof(exp));
//		} else { //����������, �ʹ�ջ����������ֵ������Ӧ������
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



