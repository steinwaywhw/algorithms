#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include "stack.h"

#define DELETION 	0
#define INSERTION 	1
#define MATCH		2
#define MISMATCH	3


struct matrix {
	int max;
	int max_x, max_y;
	int rows, columns;
	int *matrix;
};

struct point {
	int x;
	int y;
	int type;
};

int matrix_get (struct matrix *m, int x, int y) {
	assert (m != NULL);
	assert (x >= 0 && x < m->rows);
	assert (y >= 0 && y < m->columns);

	int *p = m->matrix;
	p += m->columns * x;
	p += y;

	return *p;
} 

int matrix_set (struct matrix *m, int x, int y, int value) {
	assert (m != NULL);
	assert (x >= 0 && x < m->rows);
	assert (y >= 0 && y < m->columns);

	int *p = m->matrix;
	p += m->columns * x;
	p += y;

	int old = *p;
	*p = value;
	return old;
}

int weight (int operation) {
	switch (operation) {
		case DELETION:
		case INSERTION:
			return 0;
		case MATCH:
			return 1;
		case MISMATCH:
			return -100;
	}
}

int max_4 (int a, int b, int c, int d) {
	int max = a > b ? a : b;
	max = c > max ? c : max;
	max = d > max ? d : max;

	return max;
}

void print (struct matrix *m, char *str1, char *str2) {
	printf ("===== DEBUG =====\n");
	int i, j;

	for (i = 0; i <= m->rows; i++) {
		for (j = 0; j <= m->columns; j++) {

			if (i == 0 && j == 0) {
				printf ("%-3s", "-");
				continue;
			}
			
			if (i == 0) 
				j == 1 ? printf ("%-3s", "-") : printf ("%-3c", *(str2 + j - 2));
			else if (j == 0)
				i == 1 ? printf ("%-3s", "-") : printf ("%-3c", *(str1 + i - 2));
			else 
				printf ("%-3d", matrix_get (m, i-1, j-1));
		}
		putchar ('\n');
	}
}

struct matrix * smith_waterman_align (char *str1, char *str2) {
	assert (str1 != NULL);
	assert (str2 != NULL);

	struct matrix *m = (struct matrix *) malloc (sizeof (struct matrix));
	assert (m != NULL);

	m->rows = strlen (str1) + 1;
	m->columns = strlen (str2) + 1;
	m->matrix = (int *) malloc (m->rows * m->columns * sizeof (int));
	assert (m->matrix != NULL);

	memset ((void *)m->matrix, 0, sizeof (int) * m->columns * m->rows);

	m->max = 0;


	int i, j;
	for (i = 1; i < m->rows; i++) {
		for (j = 1; j < m->columns; j++) {
			char a = *(str1 + i - 1);
			char b = *(str2 + j - 1);
			int score = (a == b) ? weight (MATCH) : weight (MISMATCH);
			int max = max_4 (0, matrix_get (m, i-1, j-1) + score, matrix_get (m, i, j-1) + weight (INSERTION), matrix_get (m, i-1, j) + weight (DELETION));
			matrix_set (m, i, j, max);

			if (max > m->max) {
				m->max = max;
				m->max_x = i;
				m->max_y = j;
			}
		}
	}

	return m;
}

struct matrix * backtrace_count (struct matrix *m, char *str1, char *str2) {
	assert (str1 != NULL);
	assert (str2 != NULL);
	assert (m != NULL);

	struct matrix *h = (struct matrix *) malloc (sizeof (struct matrix));
	assert (h != NULL);

	h->rows = strlen (str1) + 1;
	h->columns = strlen (str2) + 1;
	h->matrix = (int *) malloc (h->rows * h->columns * sizeof (int));
	assert (h->matrix != NULL);

	memset ((void *)h->matrix, 0, sizeof (int) * h->columns * h->rows);

	int i, j;
	for (i = 0; i < h->rows; i++)
		matrix_set (h, i, 0, 1);
	for (j = 0; j < h->columns; j++)
		matrix_set (h, 0, j, 1);

	for (i = 1; i < h->rows; i++) {
		for (j = 1; j < h->columns; j++) {
			char a = *(str1 + i - 1);
			char b = *(str2 + j - 1);

			int m_i1j = matrix_get (m, i-1, j);
			int m_ij1 = matrix_get (m, i, j-1);
			int h_i1j = matrix_get (h, i-1, j);
			int h_ij1 = matrix_get (h, i, j-1);

			if (a == b)
				matrix_set (h, i, j, matrix_get (h, i-1, j-1));
			else if (m_ij1 == m_i1j)
				matrix_set (h, i, j,  h_i1j + h_ij1);
			else 
				matrix_set (h, i, j, m_i1j > m_ij1 ? h_i1j : h_ij1);

		}
	}

	return h;
}

struct stack * backtrace (struct matrix *m, char *str1, char *str2) {
	assert (str1 != NULL);
	assert (str2 != NULL);
	assert (m != NULL);

	int len_1 = strlen (str1);
	int len_2 = strlen (str2);
	int len = len_1 > len_2 ? len_1 : len_2;

	struct stack *s = init_stack (len_1 + len_2, NULL);

	char *ret = (char *) malloc (sizeof (char) * len);
	assert (ret != NULL);
	memset ((void *)ret, 0, sizeof (char) * len);

	int i = m->max_x, j = m->max_y;

	while (matrix_get (m, i, j) != 0 && i > 0 && j > 0) {
		struct point *p = (struct point *) malloc (sizeof (struct point));
		p->x = i, p->y = j;

		char a = *(str1 + i - 1);
		char b = *(str2 + j - 1);
		int score = (a == b) ? weight (MATCH) : weight (MISMATCH);

		int del = matrix_get (m, i-1, j) + weight (DELETION);
		int ins = matrix_get (m, i, j-1) + weight (INSERTION);
		int dig = matrix_get (m, i-1, j-1) + score;

		int current = matrix_get (m, i, j);
		if (current == del)
			i--, p->type = DELETION;
		else if (current == ins)
			j--, p->type = INSERTION;
		else
			i--, j--, p->type = MATCH;

		push (s, (void *)p);

	}

	return s;
}

void print_sequence (struct stack *s, char *str1, char *str2) {
	struct stack *s_2 = init_stack (s->top, NULL);

	while (s->top > 0) {
		struct point *p = (struct point *) pop (s);
		switch (p->type) {
			case MATCH:
			case MISMATCH:
			case DELETION:
				printf ("%-3c", *(str1 + p->x)); break;
			case INSERTION:
				printf ("%-3c", "-");
		}
		push (s_2, p);
	}

	while (s_2->top > 0) {
		push (s, pop (s_2));
	}

	while (s->top > 0) {
		struct point *p = (struct point *) pop (s);
		switch (p->type) {
			case MATCH:
			case MISMATCH:
			case INSERTION:
				printf ("%-3c", *(str2 + p->y)); break;
			case DELETION:
				printf ("%-3c", "-");
		}
		push (s_2, p);
	}

}

int main () {
	char *str1 = "abcbdab", *str2 = "bdcaba";

	struct matrix *m = smith_waterman_align (str1, str2);
	print (m, str1, str2);

	struct matrix *s = backtrace_count (m, str1, str2);
	print (s, str1, str2);

	free (m->matrix);
	free (m);
	return 0;
}
