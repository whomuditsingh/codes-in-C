#include <stdlib.h>

typedef struct {
    int val;
    int index;
} Element;

int compareElements(const void* a, const void* b) {
    Element* elemA = (Element*)a;
    Element* elemB = (Element*)b;
    if (elemA->val < elemB->val) return -1;
    if (elemA->val > elemB->val) return 1;
    return 0;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int* result = (int*)malloc(2 * sizeof(int));
    Element* elements = (Element*)malloc(numsSize * sizeof(Element));

    // Preserve original indices
    for (int i = 0; i < numsSize; i++) {
        elements[i].val = nums[i];
        elements[i].index = i;
    }

    // Sort by value in O(n log n)
    qsort(elements, numsSize, sizeof(Element), compareElements);

    // Two-pointer search
    int left = 0;
    int right = numsSize - 1;

    while (left < right) {
        long sum = (long)elements[left].val + elements[right].val;
        if (sum == target) {
            result[0] = elements[left].index;
            result[1] = elements[right].index;
            free(elements);
            return result;
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }

    free(elements);
    *returnSize = 0;
    return NULL;
}
