#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include "stack.h"
#include "cstack.h"

typedef struct var {
	char v;					/* This is for variable and it's value */
	num no;
}var;

var x;

num infixeval(char *infix);

int main() {
  	char *str;
  	int i, j, flag = 0, g = 0;
	initnum(&(x.no));
  	num result;
  	initnum(&result);
  	str = (char *)malloc(sizeof(char) * 1024);
  
	while(1) {
    		for(i = 0; (str[i] = getchar()) != '\n'; i++) {
    		}
    		str[i] = '\0';
		g = 0;
		flag = 0;
		for(j = 0; j < i; j++) {
			if(isalpha(str[j])) {
				x.v = str[j];				/*It store's a variable which is given by user */
				flag = 1;
			}
			if(str[j] == '=')
				g = 1;
		}
		if(flag == 1 && g == 1) {
			j = 0;
			while(str[j] != '\0') {
				if(isdigit(str[j]))
					addnumber(&(x.no), str[j]);
				j++;			
			}
		}
		if(g == 0) {
			printnum(infixeval(str));
			initnum(&(x.no));		
		}
   	}
  	return 0;
}

#define	OPERATOR	10
#define	OPERAND		20
#define	END		30
#define	ERROR		40
#define VAR		50

typedef struct token{
	int type;
	union data {
		num n;
		char op;
		char var;
  	}data;
}token;

enum states {START, DIG, OP, STOP, ERR, SPC};

token getnext(char *str, int *restart) {
  	static int currstate = START;
  	int nextstate;
  	static int i = 0;
  	token t;
  	static int sum = 0;
  	char currchar;
  	static char currop;
  	num a;
  	initnum(&a);
  	if(*restart == 1) {
    		i = 0;
    		currstate = START;
    		*restart = 0;
  	}

  	while(1) {
    		currchar = str[i++];
    		switch(currstate) {
    			case START:
      				switch(currchar) {
      					case '0': case '1': case '2':
      					case '3': case '4': case '5':
      					case '7': case '8': case '9':
					case '6': case '.':
						nextstate = DIG;
						addnumber(&a, currchar);	
						break;
	
      					case '+': case '-': case '*':
      					case '/': case '%': case '(':
      					case ')': case '^': case '<':
						nextstate = OP;
						currop = currchar;
						break;
	
      					case ' ': case '\t':
						nextstate = SPC;
						break;
	
      					case '\0':
						nextstate = STOP;
						break;
      					
					default:
						if(isalpha(currchar)) {
							t.data.var = currchar;
							t.type = VAR;
							return t;
						}
						break;
      				}
     	 			break;
	
    			case DIG:
	
     	 			switch(currchar) {
     					case '0': case '1': case '2':
     	 				case '3': case '4': case '5':
     	 				case '7': case '8': case '9':
     	 				case '6': case '.':
						nextstate = DIG;
						addnumber(&a, currchar);
						break;
	
     	 				case '+': case '-': case '*':
     	 				case '/': case '%': case '(':
     	 				case ')': case '^': case '<':
						nextstate = OP;
						t.type = OPERAND;
						t.data.n = a;
						sum = 0;
						initnum(&a);
						currop = currchar;
						currstate = nextstate;
						if(currchar == '<')
							i++;
						return t;
						break;
	
     	 				case ' ': case '\t':
						nextstate = SPC;
						t.type = OPERAND;
						t.data.n = a;
						sum = 0;
						initnum(&a);
						currstate = nextstate;
						return t;
					break;
	
     	 				case '\0':
						nextstate = STOP;
						t.type = OPERAND;
						t.data.n = a;
						sum = 0;
						initnum(&a);	
						currstate = nextstate;
						return t;
						break;
 	
				     	default:
						nextstate = ERR;
						t.type = OPERAND;
						t.data.n = a;
						sum = 0;
						initnum(&a);
						currstate = nextstate;
						return t;
						break;
      				}
      				break;
	
    			case OP:
      				switch(currchar) {
				      	case '0': case '1': case '2':
				      	case '3': case '4': case '5':
				      	case '7': case '8': case '9':
				      	case '6': case '.':
						nextstate = DIG;
						addnumber(&a, currchar);
						t.type = OPERATOR;
						t.data.op = currop;
						currop = currchar;
						currstate = nextstate;
						return t;
						break;
	
				      	case '+': case '-': case '*':
				      	case '/': case '%': case '(':
				      	case ')': case '^': case '<':
						nextstate = OP;
						t.type = OPERATOR;
						t.data.op = currop;
						currop = currchar;
						currstate = nextstate;
						return t;
						break;
	
      					case ' ': case '\t':
						nextstate = SPC;
						t.type = OPERATOR;
						t.data.op = currop;
						currstate = nextstate;
						return t;
						break;
      	
					case '\0':
						nextstate = STOP;
						t.type = OPERATOR;
						t.data.op = currop;
						currstate = nextstate;
						return t;
						break;
      	
					default:
						nextstate = ERR;
						t.type = OPERATOR;
						t.data.op = currop;
						currstate = nextstate;
						return t;
						break;
				}
				break;
    	
			case SPC:
      				switch(currchar) {
      					case '0': case '1': case '2':
      					case '3': case '4': case '5':
      					case '7': case '8': case '9':
      					case '6': case '.':
						nextstate = DIG;
						addnumber(&a, currchar);
						break;
	
					case '+': case '-': case '*':
					case '/': case '%': case '(':
					case ')': case '^': case '<':
						nextstate = OP;
						currop = currchar;
						if(currchar == '<')
							i++;
						break;
	
      					case ' ': case '\t':
						nextstate = SPC;
						break;
	
      					case '\0':
						nextstate = STOP;
						break;
	
      					default:
						nextstate = ERR;
						break;
      				}
      				break;
    	
			case STOP:
      				t.type = END;
      				return t;
      				break;
    	
			case ERR:
      				t.type = ERROR;
      				return t;
      				break;
    			}
		
    			currstate = nextstate;
		}
}	
	
num eval(char ch, num *a, num *b) {
  	switch(ch) {
		case '+':
			return addnum(a, b);
    		case '-':
			return subnum(a, b);
    		case '*':
			return multinum(a, b);
    		case '/':
			//return divnum(a, b);
    		case '%':
			//return modnum(a, b);
		case '^':
			return pownum(a, b);
		case '<':
			return leftshift(a, b);
    		default:
			printf("\nInvalid operator : %c\n", ch);
      			exit(1);
    	}
}

int precedence(char ch) {
  	if(ch == '$' || ch == '#')
    		return 10;
  	else if(ch == '+' || ch == '-')
    		return 20;
  	else if(ch == '*' || ch == '/')
    		return 30;
  	else if(ch == '%')
    		return 40;
	else if(ch == '^')
		return 50;
	else if(ch == '<')
		return 60;
  	else {
    		printf("\nInvalid operator : %c\n", ch);
    		exit(1);
  	}
}



num infixeval(char *infix) {
  	token t;
  	int restart = 1;
  	num opnd1, opnd2, res;
  	initnum(&opnd1);
  	initnum(&opnd2);
  	initnum(&res);
  	char ch;
  	stack s;
  	cstack cs;
  	init(&s);
  	cinit(&cs);
  	cpush(&cs, '#');
  	int i = 0;
  	char optr2, optr3;
  
  	while(1) {
    		t = getnext(infix, &restart);
		
		if(t.type == VAR) {
			push(&s, x.no);
		}
    		else if(t.type == OPERAND) {
      			push(&s, t.data.n);
    		}
    		else if(t.type == OPERATOR) {
      			if(t.data.op == '(') {
				cpush(&cs, '$');
				continue;
      			}
      			else if(t.data.op == ')') {
				optr2 = cpop(&cs);
				optr3 = cpop(&cs);
					if(precedence(optr2) > precedence(optr3)) {
	  					cpush(&cs, optr3);
	  					cpush(&cs, optr2);
					}
					else {
	  					while(precedence(optr2) <= precedence(optr3)) {
	    						opnd2 = pop(&s);
	    						opnd1 = pop(&s);
	    						res = eval(optr3, &opnd1, &opnd2);
	    						push(&s, res);
	    						optr3 = cpop(&cs);
	  					}
	  					cpush(&cs, optr3);
	  					cpush(&cs, optr2);
					}
		
				while((ch = cpop(&cs)) != '$') {
	    				opnd2 = pop(&s);
	    				opnd1 = pop(&s);
	    				res = eval(ch, &opnd1, &opnd2);
	    				push(&s, res);
	  			}
      			}
      
      			else {
				optr2 = cpop(&cs);
				if(precedence(t.data.op) > precedence(optr2)) {
	  				cpush(&cs, optr2);
	  				cpush(&cs, t.data.op);
				}
				else {
		 			while(precedence(t.data.op) <= precedence(optr2)) {
	      					opnd2 = pop(&s);
	      					opnd1 = pop(&s);
	      					res = eval(optr2, &opnd1, &opnd2);
	      					push(&s, res);
	      					optr2 = cpop(&cs);
	    				}
	    				cpush(&cs, optr2);
	    				cpush(&cs, t.data.op);
	  			}
      			}
    		}
    		else if(t.type == END) {
     			break;
    		}
    		else if(t.type == ERROR) {     
    		}
  	}

  	while((ch = cpop(&cs)) != '#') {
      		if(ch == '$') {
			printf("Error in expression\n");
			break;
		}
      
      		opnd2 = pop(&s);
      		opnd1 = pop(&s);
      		res = eval(ch, &opnd1, &opnd2);
      		push(&s, res);
    	}
  	return(pop(&s));
}
