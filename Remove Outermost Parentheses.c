#include <stdlib.h>
#include <string.h>

char* removeOuterParentheses(char* s) {
    int len = strlen(s);
    char* result = (char*)malloc((len + 1) * sizeof(char));
    int depth = 0;
    int k = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            if (depth > 0) {
                result[k++] = s[i];
            }
            depth++;
        } else {
            depth--;
            if (depth > 0) {
                result[k++] = s[i];
            }
        }
    }

    result[k] = '\0';
    return result;
}
