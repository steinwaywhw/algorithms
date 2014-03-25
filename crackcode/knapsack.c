
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*
    pack (0, 0) = 0
    pack (n, 0) = 0
    pack (i, j) = pack (i-1, j)
                = pack (i-1, j - items[i]) + items[i]
*/

int max(int a, int b) {
    return a > b ? a : b;
}

int print(int *matrix, int m, int n) {
    printf("==========================\n");
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%3d", matrix[i * n + j]);
        }
        putchar('\n');
    }
    
}

int pack(int *items, int n, int cap) {
    assert(items != NULL);
    assert(cap >= 0);
    
    if (cap == 0)
        return 0;
    
    int *matrix = (int *)malloc(sizeof(int) * (n+1) * (cap+1));
    memset(matrix, 0, sizeof(int) * (n+1) * (cap+1));
    
    int i, j;
    
    for (i = 0; i <= n; i++) {
        for (j = 0; j <= cap; j++) {
            if (j == 0 || i == 0)
                continue;
            
            if (j < items[i])
                matrix[i * (cap+1) + j] = matrix[(i-1) * (cap+1) + j];
            else {
                matrix[i * (cap+1) + j] = 
                max(
                    matrix[(i-1) * (cap+1) + j],
                    matrix[i * (cap+1) + j - items[i]] + items[i]
                );
               
            }
            
            
            
        }
    }
    print(matrix, n+1, cap+1);
    int ret = matrix[n * (cap+1) + cap];
    free(matrix);

    return ret;
}


int main() {
    int items[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printf("%d\n", pack(items, 10, 20));
    
}
    
    


 