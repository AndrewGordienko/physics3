#include <stdio.h>
#include <stdlib.h>

int main() {
    int* p = (int*)malloc(sizeof(int));
    if (p == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    *p = 42;
    printf("Value at p: %d\n", *p);

    free(p);
    p = NULL;  // Assign NULL to the pointer after freeing

    // Accessing freed memory (NULL pointer)
    printf("Value at p after freeing: %p\n", (void*)p);  // Output: 0 (NULL)

    return 0;
}
