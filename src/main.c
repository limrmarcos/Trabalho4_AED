#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int size;
} Map;

int compare( const void* first, const void* second ) {
    return ((Map*)first)->size - ((Map*)second)->size;
}

int* topKFrequent( int* nums, int numsSize, int k, int* returnSize ) {
    if( k == numsSize ) {
        *returnSize = numsSize;
        return nums;
    }

    Map* table = ( Map* ) malloc ( numsSize * sizeof( Map ));
    int count = 0;

    for( int i = 0; i < numsSize; i++ ) {
        int found = 0;
        for( int j = 0; j < count; j++ ) {
            if( table[j].value == nums[i] ) {
                table[j].size++;
                found = 1;
                break;
            }
        }
        if( !found ) {
            table[count].value = nums[i];
            table[count].size = 1;
            count++;
        }
    }
    qsort( table, count, sizeof( Map ), compare );

    int* mostFrequent = ( int* ) malloc ( k * sizeof( int ));
    for( int i = 0; i < k; i++ ) {
        mostFrequent[i] = table[count - 1 - i].value;
    } 

    free( table );

    *returnSize = k;
    return mostFrequent;
}

int main() {
    int nums[] = {1, 1, 1, 2, 2, 3};
    int k = 2;
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize;
    int* result = topKFrequent(nums, numsSize, k, &returnSize);
    
    printf("Top %d frequent elements: ", k);
    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");
    
    free(result);
    
    return 0;
}

