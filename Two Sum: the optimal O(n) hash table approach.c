#include <stdlib.h>
#include "uthash.h"

// Define a hash table node
struct HashItem {
    int key;              // Number value
    int val;              // Original index in nums
    UT_hash_handle hh;    // Makes this structure hashable
};

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int* result = (int*)malloc(2 * sizeof(int));
    struct HashItem *map = NULL, *item = NULL;

    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];

        // 1. Look up if complement already exists in map
        HASH_FIND_INT(map, &complement, item);
        if (item != NULL) {
            result[0] = item->val;
            result[1] = i;

            // Free allocated hash table memory before returning
            struct HashItem *curr, *tmp;
            HASH_ITER(hh, map, curr, tmp) {
                HASH_DEL(map, curr);
                free(curr);
            }
            return result;
        }

        // 2. Add current number and index into the map
        HASH_FIND_INT(map, &nums[i], item);
        if (item == NULL) {
            item = (struct HashItem*)malloc(sizeof(struct HashItem));
            item->key = nums[i];
            item->val = i;
            HASH_ADD_INT(map, key, item);
        }
    }

    *returnSize = 0;
    return NULL;
}
