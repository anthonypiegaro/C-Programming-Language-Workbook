#include <stdio.h>

#define MAX_SIZE 100

int binary_search(int x, int v[], int n);

int main() {
    int v[] = {1, 3, 4, 5};
    int res;

    res = binary_search(1, v, 4);

    printf("%d\n", res);

    return 0;
}

int binary_search(int x, int v[], int n) {
    int low, mid, high;

    low = 0;
    high = n - 1;

    while (low <= high) {
        mid = (low + high) / 2;
        
        if (x <= v[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    if (low < n && v[low] == x) {
        return low;
    }

    return -1;
}
