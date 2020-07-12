#include "num.h"
#define MAX 32
typedef struct stack{
	num a[MAX];
	int i;
}stack;
int isempty(stack *s);
int isfull(stack *s);
void init(stack *s);
void push(stack *s, num x);
num pop(stack *s);

