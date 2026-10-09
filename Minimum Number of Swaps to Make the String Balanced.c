#include <stdio.h>

int minSwaps(char* s) {
    int imbalance = 0;
    int maxImbalance = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == ']') {
            imbalance++;
        } else {
            imbalance--;
        }

        // Track the maximum excess of ']' over '['
        if (imbalance > maxImbalance) {
            maxImbalance = imbalance;
        }
    }

    // Each swap resolves 2 unmatched pairs
    return (maxImbalance + 1) / 2;
}

int main() {
    char s1[] = "][][";
    char s2[] = "]]][[[";
    char s3[] = "[]";

    printf("Swaps for \"%s\": %d\n", s1, minSwaps(s1)); // Output: 1
    printf("Swaps for \"%s\": %d\n", s2, minSwaps(s2)); // Output: 2
    printf("Swaps for \"%s\": %d\n", s3, minSwaps(s3)); // Output: 0

    return 0;
}
