#include <stdio.h>
#include <stdlib.h>

void activity_selection(int start[], int finish[], int elements) {
    for (int i = 0; i < elements - 1; i++) {
        for (int j =  i + 1; j < elements; j++) {
            if (finish[i] > finish[j]) {
                int temp = finish[i];
                finish[i] = finish[j];
                finish[j] = temp;

                temp = start[i];
                start[i] = start[j];
                start[j] = temp;
            }
        }
    }

    int count = 1;
    int last_finish = 0;

    printf("Activity %d selected (Start: %d, Finish: %d)\n", last_finish + 1, start[last_finish], finish[last_finish]);

    for (int i = 1; i < elements; i++) {
        if (start[i] >= finish[last_finish]){
            count++;
            last_finish = i;
            printf("Activity %d selected (Start: %d, Finish: %d)\n", i + 1, start[i], finish[i]);
        }
    }

    printf("%d activities selected", count);
}


int main() {
    int start[] = {1, 3, 0, 5, 8, 5};
    int finish[] = {2, 4, 6, 7, 9, 9};
    int n = sizeof(start) / sizeof(start[0]);

    activity_selection(start, finish, n);
    return 0;
}