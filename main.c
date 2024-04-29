#include <stdio.h>
#include <stdlib.h>

void bucketSort(int arr[], int n) {
    int i, j, k;
    int max = arr[0];
    int min = arr[0];
    int* buckets;

    // Find the maximum and minimum values in the array
    for (i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        } else if (arr[i] < min) {
            min = arr[i];
        }
    }

    // Determine the number of buckets to create
    int numBuckets = max - min + 1;

    // Allocate memory for the buckets
    buckets = (int*) malloc(numBuckets * sizeof(int));

    // Initialize each bucket to an empty array
    for (i = 0; i < numBuckets; i++) {
        buckets[i] = -1;
    }

    // Distribute the elements of the array into the buckets
    for (i = 0; i < n; i++) {
        int bucketIndex = arr[i] - min;
        if (buckets[bucketIndex] == -1) {
            buckets[bucketIndex] = arr[i];
        } else {
            // The bucket is not empty, so create a new array to hold the elements
            int* newArray = (int*) malloc((n - i) * sizeof(int));
            j = 0;
            for (k = bucketIndex; k < numBuckets; k++) {
                if (buckets[k] != -1) {
                    newArray[j++] = buckets[k];
                    buckets[k] = -1;
                }
            }
            newArray[j++] = arr[i];

            // Sort the new array using insertion sort
            for (k = 1; k < j; k++) {
                int key = newArray[k];
                int m = k - 1;
                while (m >= 0 && newArray[m] > key) {
                    newArray[m + 1] = newArray[m];
                    m--;
                }
                newArray[m + 1] = key;
            }

            // Replace the old array with the new sorted array
            for (k = 0; k < j; k++) {
                buckets[k + bucketIndex] = newArray[k];
            }

            // Free the memory allocated for the new array
            free(newArray);
        }
    }

    // Copy the sorted elements back into the original array
    j = 0;
    for (i = 0; i < numBuckets; i++) {
        if (buckets[i] != -1) {
            arr[j++] = buckets[i];
        }
    }

    // Free the memory allocated for the buckets
    free(buckets);
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    bucketSort(arr, n);

    printf("Sorted array:   ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
