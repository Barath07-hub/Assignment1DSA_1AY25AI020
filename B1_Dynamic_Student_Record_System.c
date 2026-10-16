#include <stdio.h>
#include <stdlib.h>

struct Student {
    int roll_no;
    char name[20];
    float marks;
};

int main() {
    struct Student *ptr;
    int n, i;
    float sum = 0, average;
    int top = 0;
    char choice;

    printf("Enter number of students: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of students.\n");
        return 1;
    }

    // Dynamically allocate memory using malloc
    ptr = (struct Student *)malloc(n * sizeof(struct Student));

    if (ptr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Read student records using pointer arithmetic
    for (i = 0; i < n; i++) {
        printf("Enter roll, name, marks: ");
        scanf("%d %19s %f",
              &(ptr + i)->roll_no,
              (ptr + i)->name,
              &(ptr + i)->marks);
    }

    // Calculate total marks and find the topper
    for (i = 0; i < n; i++) {
        sum += (ptr + i)->marks;

        if ((ptr + i)->marks > (ptr + top)->marks) {
            top = i;
        }
    }

    average = sum / n;

    printf("Average marks: %.2f\n", average);
    printf("Topper: %s (Roll %d, Marks %.2f)\n",
           (ptr + top)->name,
           (ptr + top)->roll_no,
           (ptr + top)->marks);

    // Ask whether to add two more students
    printf("\nAdd 2 more students? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        int old_n = n;
        n = n + 2;

        // Grow the allocated memory using realloc
        struct Student *temp;
        temp = (struct Student *)realloc(
            ptr, n * sizeof(struct Student));

        if (temp == NULL) {
            printf("Memory reallocation failed.\n");
            free(ptr);
            return 1;
        }

        ptr = temp;

        // Read the two additional student records
        for (i = old_n; i < n; i++) {
            printf("Enter roll, name, marks: ");
            scanf("%d %19s %f",
                  &(ptr + i)->roll_no,
                  (ptr + i)->name,
                  &(ptr + i)->marks);
        }

        // Recalculate total marks for all students
        sum = 0;
        top = 0;

        for (i = 0; i < n; i++) {
            sum += (ptr + i)->marks;

            if ((ptr + i)->marks > (ptr + top)->marks) {
                top = i;
            }
        }

        average = sum / n;

        printf("Updated average marks: %.2f\n", average);
        printf("Topper: %s (Roll %d, Marks %.2f)\n",
               (ptr + top)->name,
               (ptr + top)->roll_no,
               (ptr + top)->marks);
    }

    // Release dynamically allocated memory
    free(ptr);

    return 0;
}

