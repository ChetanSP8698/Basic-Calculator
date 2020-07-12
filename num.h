typedef struct node {
	char n;
	struct node *prev, *next;
}node;

typedef struct num {
	node *h, *t;
	int sign;
}num;

void initnum(num *a);
void addnumber(num *a, char x);
void appendleft(num *a, char x);
void printnum(num a);
void initrnum(num *a);
void insert(num *a, char str, int pos);
int fraclen(num a);
void replace(num *a, char str);
num addnum(num *a, num *b);
num subnum(num *a, num *b);
num multinum(num *a, num *b);
num divnum(num *a, num *b);
num modnum(num *a, num *b);
num pownum(num *a, num *b);
num Sine(num *a);
num Cosine(num *a);
num Tangent(num *a);
num leftshift(num *a, num *b);
num rightshift(num *a, num *b);
int length(num a);
int compare(num *a, char x);
