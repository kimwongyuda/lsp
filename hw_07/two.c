#include <stdio.h>


/*앞에서부터 비교 대상과 비교해 1단어씩 비교해서 모두 같다면 리턴한다. 그리고 p++을 통해 앞의 한단어는 버리게 된다.*/
char getLower(char ch) {
    // upper -> lower
    if(ch > 64 && ch < 91) {
        ch += 32;
    }
    return ch;
}

char* mystrcasestr(char str1[], char str2[]) {
    int i, j, k;

    for(i = 0; str1[i] != '\0'; i++) {
        if(getLower(str1[i]) == getLower(str2[0])) {
            for(j = i, k = 0; getLower(str1[j]) == getLower(str2[k]); j++, k++) {
                if(str2[k + 1] == '\0') {
                    return str1 + i;
                }
            }
        }
    }
    return NULL;
}

int main() {
    char str[] = "Hello hello HELLO";
    char* p;

    p = str;
    while(p) {
        p = mystrcasestr(p, "hello");
        if(p != NULL) {
            puts(p);
            p++;
        }
    }
}
