
#include <stdio.h>

#define MAX 100

typedef struct {
    int row, col, value;
} term;

void display(term a[]) {
    int i;

    printf("Row\tCol\tValue\n");
    for (i = 0; i <= a[0].value; i++) {
        printf("%d\t%d\t%d\n",
               a[i].row, a[i].col, a[i].value);
    }
}

void fast_transpose(term a[], term b[]) {
    int row_terms[MAX] = {0};
    int starting_pos[MAX] = {0};
    int i, j, num_cols;

    num_cols = a[0].col;

    // Count non-zero elements in each column
    for (i = 1; i <= a[0].value; i++) {
        row_terms[a[i].col]++;
    }

    // Calculate starting positions
    starting_pos[0] = 1;

    for (i = 1; i < num_cols; i++) {
        starting_pos[i] =
            starting_pos[i - 1] + row_terms[i - 1];
    }

    // Set dimensions of transposed matrix
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = a[0].value;

    // Place elements directly in row-major order
    for (i = 1; i <= a[0].value; i++) {
        j = a[i].col;

        int pos = starting_pos[j]++;

        b[pos].row = a[i].col;
        b[pos].col = a[i].row;
        b[pos].value = a[i].value;
    }

    // Print internal arrays
    printf("\nrow_terms[]:\n");
    for (i = 0; i < num_cols; i++) {
        printf("%d ", row_terms[i]);
    }

    printf("\nstarting_pos[] (initial positions):\n");

    // Reconstruct initial starting positions for display
    int start = 1;
    for (i = 0; i < num_cols; i++) {
        printf("%d ", start);
        start += row_terms[i];
    }

    printf("\n");
}

int main() {
    term a[MAX], b[MAX];
    int rows, cols, i, j, value, count = 0;

    printf("Enter number of rows and columns: ");
    scanf("%d %d", &rows, &cols);

    if (rows <= 0 || cols <= 0 ||
        rows >= MAX || cols >= MAX) {
        printf("Invalid matrix dimensions!\n");
        return 1;
    }

    a[0].row = rows;
    a[0].col = cols;

    printf("Enter matrix elements row by row:\n");

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            scanf("%d", &value);

            if (value != 0) {
                count++;
                if (count >= MAX) {
                    printf("Too many non-zero elements!\n");
                    return 1;
                }

                a[count].row = i;
                a[count].col = j;
                a[count].value = value;
            }
        }
    }

    a[0].value = count;

    printf("\nOriginal matrix triples:\n");
    display(a);

    fast_transpose(a, b);

    printf("\nTransposed matrix triples "
           "(already in row-major order):\n");
    display(b);

    return 0;
}

