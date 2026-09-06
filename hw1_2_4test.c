#include <stdio.h>
#include <stdlib.h>

int* reOrder(int* array, int len) {
    int leftBound = 0;
    for(int i = 0; i < len; i++) {
        if(array[i] % 6 == 0) {
            int temp = array[i];
            array[i] = array[leftBound];
            array[leftBound] = temp;
            leftBound++;
        }
    }

    int k = 0;
    for(int i = 0; i < leftBound; i++) {
        if(array[i] % 7 == 0) {
            int temp = array[i];
            array[i] = array[k];
            array[k] = temp;
            k++;
        }
    }

    return array;
}

int main() {
    int len;
    scanf("%d", &len);
    int* array = (int*)malloc(len * sizeof(int));
    for(int i = 0; i < len; i++) {
        scanf("%d", &array[i]);
    }

    int* result = reOrder(array, len);

    for(int i = 0; i < len; i++) {
        printf("%d ", result[i]);
    }

    free(array);

    return 0;
}