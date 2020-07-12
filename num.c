#include <stdio.h>
#include <stdlib.h>
#include "num.h"

void initnum(num *a) {
	node *x;
	x = (node *)malloc(sizeof(node));
	x->n = '0';
	x->next = x->prev = NULL;
	a->h = a->t = x;
}

void initrnum(num *a) {
	a->h = NULL;
	a->t = NULL;
}
void appendleft(num *a, char ch) {
  	node *tmp, *x;
  	if(a->h == NULL) {
    		tmp = (node *)malloc(sizeof(node));
    		if(ch >= '0' && ch <= '9')
      			tmp->n = ch;
    		tmp->next = tmp->prev = NULL;
    		a->h = a->t = tmp;
  	}

  	else {
    		x = a->h;
    		tmp = (node *)malloc(sizeof(node));
    		if(ch >= '0' && ch <= '9')
      			tmp->n = ch;
    		tmp->next = x;
    		tmp->prev = NULL;
    		x->prev = tmp;
    		a->h = tmp;
  	}
}

void addnumber(num *a, char x) {
	node *tmp, *z;
	if(a->h->n == '0') {
		a->h->n = x;
  	}
  	else {
    		z = a->t;
    		tmp = (node *)malloc(sizeof(node));
   	 	tmp->n = x;
   	 	tmp->prev = z;
   	 	tmp->next = NULL;
   		z->next = tmp;
   	 	a->t = tmp;
  	}
}

void printnum(num a) {
	node *temp;
  	temp = a.h;
  	if(!temp) {
   		printf("\n");
    	return;
  	}
  	do {
    		printf("%c", temp->n);
    		temp = temp->next;
  	}while(temp != NULL);
 	printf("\n");
}


num addnum(num *a, num *b) {
  	num c;
  	node *x, *y, *tmp;
  	char ch;
 	int s, e = 0, d = 0;
	int m, n, ma, nb;
  	initrnum(&c);
	m = fraclen(*a);
	n = fraclen(*b);
	ma = m;
	nb = n;
	if(m > n) {
		while(ma != nb) {
			addnumber(b, '0');
			nb++;
		}
	}
	else if(m < n) {
		while(ma != nb) {
			addnumber(a, '0');
			ma++;
		}
	}		  	
	x = a->t;
  	y = b->t;
	
  	while(x != NULL && y != NULL) {
		if(x->n >= '0' && x->n <= '9' && y->n >= '0' && y->n <= '9') {
     			s = ((x->n - '0') + (y->n - '0') + d);
     			e = s % 10;
     			ch = (char)(e + '0');
     			appendleft(&c, ch);
     			if(s > 9)
     	  			d = 1;
     			else
    				d = 0;
		}
		if(y->n == '.')
			y = y->prev;
		if(x->n == '.')
			x = x->prev;
		else {
			x = x->prev;
    			y = y->prev;
		}
  	}

  	if(x == NULL && y == NULL) {
    		if(d == 1) {
      			ch = (char)(d + '0');
      			appendleft(&c, ch);
    		}
		if(m) {
	  		insert(&c, '.', ma + 1);
		}  	
    		return c;
  	}

 	else {
    		if(x != NULL && y == NULL) {
      			tmp = x;
    		}
    		else {
      			tmp = y;
    		}

    	while(tmp != NULL) {
      		s = ((tmp->n - '0') + d);
      		e = s % 10;
      		ch = (char)(e + '0');
      		appendleft(&c, ch);
      		if(s > 9)
			d = 1;
      		else
			d = 0;
      		tmp = tmp->prev;
    	}
    		if(d == 1) {
      			ch = (char)(d + '0');
      			appendleft(&c, ch);
    		}
  	}
	
	if(m) {
	  	insert(&c, '.', ma + 1);
			
	}  	
	return c;
}


 
int fraclen(num a) {
	
	node *temp;
  	temp = a.t;
	int l = 0;
  	if(!temp) {
   		return l;
  	}
  	do {
		l++;
    		temp = temp->prev;
		if(temp == NULL)
			return 0;
  	}while(temp->n != '.');
	
	return l;
}



void insert(num *a, char str, int pos) {
	int len;
	int i;
	node *x, *tmp;

	len = length(*a);
	if(pos < 0 || pos > len)
		return;	

	x = (node *)malloc(sizeof(node));
	x->n = str;
	if(len == 0) {
		a->h = a->t = x;
		x->prev = x->next = NULL;
		return;
	}

	tmp = a->t;
	for(i = 0; i < pos - 1; i++)
		tmp = tmp->prev;
	if(pos == 0)
		tmp = a->h;

	tmp->next->prev = x;
	x->next = tmp->next;
	tmp->next = x;
	x->prev = tmp;

	if(pos == 0)
		a->h = x;	
	if(pos == len)
		a->t = x;
}

num subnum(num *a, num *b) {
	num d, e;
  	node *x, *y, *tmp;
  	char ch;
  	int s, q = 0, l, i, f = 0, g = 0;
	int m, n, ma, nb;
	m = fraclen(*a);
	n = fraclen(*b);
	ma = m;
	nb = n;
	if(m > n) {
		while(ma != nb) {
			addnumber(b, '0');
			nb++;
		}
	}
	else if(m < n) {
		while(ma != nb) {
			addnumber(a, '0');
			ma++;
		}
	}		  	  	
	initrnum(&d);
	initnum(&e);
	x = a->t;
  	y = b->t;
  	while(x != NULL && y != NULL) {
		if(x->n >= '0' && x->n <= '9' && y->n >= '0' && y->n <= '9') {
    			s = (((x->n - '0') + 10) - (y->n - '0')) - q;
    			if(s < 10) {
      				q = 1;
    			}
    			else {
      				q = 0;
    			}
    			if(s > 9) {
      				s = s % 10;
				f = 1;
    			}
			else 
				f = 0;
    			ch = (char)(s + '0');
    			appendleft(&d, ch);
		}
		if(y->n == '.')
			y = y->prev;
		if(x->n == '.')
			x = x->prev;
		else {
			x = x->prev;
    			y = y->prev;
		}
  	}

  	if(x == NULL && y == NULL) {
		if(f == 0) {
			l = length(d);
			addnumber(&e, '1');
			for(i = 0; i < l; i++)
				addnumber(&e, '0');
			d = subnum(&e, &d);
			d.sign = 1;
			insert(&d, '-', 0);
		}
		if(m) {
	  		insert(&d, '.', ma + 1);
		}
		return d;
  	}
  	else {
    		if(x != NULL && y == NULL) {
      			tmp = x;
    		}
    		else {
      			tmp = y;
			g = 1;
    		}

    		while(tmp != NULL) {
      			s = ((tmp->n - '0') - q);
      			q = 0;
			if(g == 1) {
				l = length(*b);
				addnumber(&e, '1');
				for(i = 0; i < l; i++)
					addnumber(&e, '0');
				d = subnum(&e, &d);
				d.sign = 1;
				replace(&d, '-');
			}
			else {
      				ch = (char)(s + '0');
      				appendleft(&d, ch);
			}      			
			tmp = tmp->prev;
    		}
  	}
	if(m) {
	  	insert(&d, '.', ma + 1);
	}
  	return d;
}


int length(num l) {
	int len = 0;
	node *tmp;
	tmp = l.h;
	if(!tmp)
		return 0;
	do {
		tmp = tmp->next;
		len++;
	}while(tmp != NULL);
	return len;
}

void replace(num *a, char str) {
	node *tmp;	
	tmp = a->h;
	tmp->n = str;

}

num multinum(num *a, num *b) {
	num m, n[32];
	initrnum(&m);
	initrnum(n);
	node *x, *y, *tmp;
  	char ch;
 	int s, e = 0, d = 0, i = 0, flag = 0;
	x = a->t;
  	y = b->t;
	int l1, l2, k, j;
	int ma, nb;
	ma = fraclen(*a);
	nb = fraclen(*b);
	l1 = length(*a);
	l2 = length(*b);
	if(l1 < l2) {
		return multinum(b, a);
	}
  	while(y != NULL) {
		while(x != NULL) {
			if(x->n >= '0' && x->n <= '9' && y->n >= '0' && y->n <= '9') {
     				s = (((x->n - '0') * (y->n - '0')) + d);
     				e = s % 10;
     				ch = (char)(e + '0');
     				appendleft(&m, ch);
     				if(s > 9) {
     	  				d = s / 10;
					flag = 1;				
				}     				
				else
    					d = 0;
			}
			x = x->prev;
		}
		if(y->n != '.') {
			n[i] = m;
			if(flag == 1) {
				ch = (char)(d + '0');
				if(ch != '0') {
					appendleft(&n[i], ch);
				}		
			}
			i++;
		}
		initrnum(&m);
		flag = 0;
		d = 0;
		y = y->prev;
		x = a->t;
  	}
	
	for(k = 0; k < i; k++) {
		j = k;
		while(j) {
			addnumber(&n[k], '0');
			j--;
		}
	}
	
	while(i > 1) {
		n[i - 2] = addnum(&n[i - 1], &n[i - 2]);
		i--;
	}
	if(ma != 0 && nb != 0)
		insert(&n[0], '.', ma + nb + 1);
	else if(ma != 0 && nb == 0)
		insert(&n[0], '.', ma + 1);
	else if(ma == 0 && nb != 0)
		insert(&n[0], '.', nb + 1);
	return n[0];
}

num pownum(num *a, num *b) {
	num p, e, o, c;
	int i = 1;
	initnum(&e);
	initnum(&o);
	initnum(&c);
	addnumber(&o, '1');
	addnumber(&e, '1');
	initnum(&p);
	addnumber(&p, '1');
	if(b->h == b->t) {
		if(b->h->n == '0')
			return p;
	}
	while(i) {
		c = subnum(b, &e);
		i = compare(&c, '0');
		p = multinum(&p, a);
		e = addnum(&e, &o);
	}
	return p;
}

/*compare function for comparing two num values
 */
int compare(num *a, char x) {
	if(a->h->n == '0') {
		if(a->t->n == '0')
			return 0;
	}
	return 1;
}

num leftshift(num *a, num *b) {
	num l, t, w;
	initrnum(&l);
	initnum(&w);
	addnumber(&w, '2');
	t = pownum(&w, b);
	l = multinum(a, &t);
	return l;
}









