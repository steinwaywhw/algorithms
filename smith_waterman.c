#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

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
			return -1;
		case MATCH:
			return 2;
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

int main () {
	char *str1 = "AGCACACA", *str2 = "ACACACTA";
	struct matrix *m = smith_waterman_align (str1, str2);
	print (m, str1, str2);

	free (m->matrix);
	free (m);
	return 0;
}
