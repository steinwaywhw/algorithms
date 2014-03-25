#include <string.h>
#include <stdio.h>
#include <malloc.h>



char* extract(char *str, int i) {
    char *extracted = (char *)malloc(sizeof(char) * strlen(str));
    memset(extracted, '\0', strlen(str));
    
    int j;
    for (j = 0; j < strlen(str); j++) {
        if (j < i)
            extracted[j] = str[j];
        else if (j >= i)
            extracted[j] = str[j+1];
    }
    
    return extracted;
}

char* append(char *str, char c) {
    char *ret = (char *)malloc(sizeof(char) * (strlen(str) + 2));
    memset(ret, 0, strlen(str) + 2);
    
    strcpy(ret, str);
    ret[strlen(str)] = c;
    
    return ret;
}

void perm(char *str, char *prefix) {

    int i;
    
    if (strlen(str) == 1) {
        printf("%s%s\n", prefix, str);
        return;
    }
        
    
    for (i = 0; i < strlen(str); i++) {
        char *tmp = extract(str, i);
        char *prf = append(prefix, str[i]);
        perm(tmp, prf);
        free(tmp);
        free(prf);
    }
}

int main() {
    perm("12345", "");
}

