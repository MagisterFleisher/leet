#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void
printArray(int* nums, const int numsSize) {
    for(int index = 0; index < numsSize; index++) {
        (void) printf(" %d |\t", nums[index]);
    }
    (void) printf("\n");
    return;
}

void
printCopyState(int copyTo, int copyFrom, int nums[], int numsSize) {
    (void) printArray(nums, numsSize);

    for(int tab_nums = 0; tab_nums < copyTo; tab_nums++) {
        (void) printf("\t");
    }
    (void) printf("CopyTo\n");

    for(int tab_nums = 0; tab_nums < copyFrom; tab_nums++) {
        (void) printf("\t");
    }
    (void) printf("CopyFrom\n\n");
    return;
}

int
nullOutMatches(int val, int *nums, int numsSize) {
    const int c_val = val;
    
    (void) printArray(nums, numsSize);

    if(1 == numsSize) {
        if(c_val == nums[0]) {
            nums[0] = -1;
            return 1;
        } else {
            return 0;
        }
    }

    unsigned int matches = 0;
    (void) printf("\nGo through array to null out matches\n-----------------------\n");
    /* Go through array to null out matches */
    for(int index = 0; index < numsSize; index++) {
        (void) printf("nums[%d]: %d\n", index, nums[index]);
        if(c_val == nums[index]) {
            (void) printf("val: %d\tnums[%d]: %d\n", c_val, index, nums[index]);
            nums[index] = -1;
            matches++;
        }
    }
    if(0 == matches) {
        return 0;
    }
    return matches;
}

void
cleanUpArray(int matches, int *nums, int numsSize) {
    /**
     * ptr1 will only need to move numsSize - matches
     *   after that many moves, no more values will require copying
     */
    int copyTo = 0;
    int copyFrom = 1;
    while(copyTo < (numsSize - matches)) {
        (void) printCopyState(copyTo, copyFrom, nums, numsSize);
        if(copyFrom == copyTo) {
            copyFrom++; }
        (void) printCopyState(copyTo, copyFrom, nums, numsSize);
        if(-1 == nums[copyTo]) {
            (void) printCopyState(copyTo, copyFrom, nums, numsSize);
            if(-1 != nums[copyFrom]) {
                nums[copyTo] = nums[copyFrom];
                nums[copyFrom] = -1;
                (void) printCopyState(copyTo, copyFrom, nums, numsSize);
            } else {
                while(-1 == nums[copyFrom] && copyFrom < numsSize -1) {
                    copyFrom++;
                }
                nums[copyTo] = nums[copyFrom];
                nums[copyFrom] =  -1;
                (void) printCopyState(copyTo, copyFrom, nums, numsSize);
            }
        }
        copyTo++;
    }
    (void) printArray(nums, numsSize);
    return;
}

int removeElement(int* nums, int numsSize, int val) {
    if(0 == numsSize) { return 0; }
    
    int matches = nullOutMatches(val, nums, numsSize);
    (void) printArray(nums, numsSize);

    /* Clean up array */
    (void) printf("\nClean up array\n---------------\n");
    (void) cleanUpArray(matches, nums, numsSize);
    return matches;
}


/* 
    Head states:
        state 1: valid
        state 2: invalid

        state 3: not last number
        state 4: last number
        
        state 5: in front of other
        state 6: behind other head
        state 7: same position as other head
    Note:
       CopyTo (1, 4,  5), CopyTo (1, 4, 6) are impossible states
    CopyTo:
       (1, 3, 5) -> move forward -> trigger same head
       (1, 3, 6) -> do not move -> trigger other head 
       (1, 3, 7) -> do not move -> trigger other head   
       (1, 4, 7) -> do not move -> end evaluation
       (2, 3, 5) -> do not move -> trigger CopyFrom state action
       (2, 4, 7) -> do not move -> end evaluation
    Addition Head states for CopyTo:
        state 8: triggered by other head
        state 9: triggered by same head
    CopyFrom:
       (1, 3, 5, 8 or 9) -> move forward -> trigger same head
       (1, 3, 7, 8 or 9) -> move forward -> trigger other head
       (1, 3, 6) -> initialize CopyTo state action
       (1, 4, 6) -> initialize CopyTo state action
       (1, 4, 7) -> end evaluation
 */

/**
 * Constraints:
0 <= nums.length <= 100
0 <= nums[i] <= 50
0 <= val <= 100

[3, 2, 2, 3], val = 3, numsSize = 4 -> [2, 2, NULL, NULL]
[0,1,2,2,3,0,4,2], val = 2, numsSize = 8 -> [0, 1, 3, 0, 4, NULL, NULL, NULL]
 */

int
main(int argument_count, char **argument_vector) {
    int example1_numsSize = 4;
    int *example1 = malloc(sizeof(int) * example1_numsSize);
    example1[0] = 3;
    example1[1] = 2;
    example1[2] = 2;
    example1[3] = 3;
    int example1_val = 3;

    int test1 = removeElement(example1, example1_numsSize, example1_val);
    (void) printf("matches: %d\n", test1);
    (void) free(example1);

    int example2_numsSize = 8;
    int *example2 = malloc(sizeof(int) * example2_numsSize);
    
    example2[0] = 0;
    example2[1] = 1;
    example2[2] = 2;
    example2[3] = 2;
    example2[4] = 3;
    example2[5] = 0;
    example2[6] = 4;
    example2[7] = 2;

    int example2_val = 2;
    
    int test2 = removeElement(example2, example2_numsSize, example2_val);
    (void) printf("matches: %d\n", test2);
    (void) free(example2);

    return 0;
}