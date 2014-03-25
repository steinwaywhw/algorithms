
#include <stdio.h>

int search(int *arr, int n, int x) {
    return _search(arr, x, 0, n-1);
}

int _search(int *arr, int x, int from, int to) {
    if (from > to)
        return -1;
        
    printf("%d - %d\n", arr[from], arr[to]);
        
    int mid = (from + to)/2;
    
    if (arr[mid] == x)
        return mid;
    if (arr[from] <= arr[to]) {
        if (arr[mid] < x)
            return _search(arr, x, mid + 1, to);
        if (x < arr[mid])
            return _search(arr, x, from, mid - 1);
    } else {
        if (arr[mid] <= arr[to]) {
            if (arr[mid] < x && x <= arr[to])
                return _search(arr, x, mid + 1, to);
            else
                return _search(arr, x, from, mid - 1);
        } else if (arr[from] <= arr[mid]) {
            if (x < arr[mid] && arr[from] <= x)
                return _search(arr, x, from, mid - 1);
            else
                return _search(arr, x, mid + 1, to);
        }
    }
        
}

int main() {
    int arr[] = {5, 6, 7, 7, 8, 9, 1, 2, 3, 4, 4};
    printf("{5, 6, 7, 7, 8, 9, 1, 2, 3, 4, 4}\n");
    printf("%d\n", search(arr, 11, 8));
    printf("%d\n", search(arr, 11, 9));
    printf("%d\n", search(arr, 11, 1));
    printf("%d\n", search(arr, 11, 2));
    printf("%d\n", search(arr, 11, 4));

}