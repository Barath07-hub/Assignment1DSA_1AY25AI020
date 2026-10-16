
#include <stdio.h>

typedef struct {
    int degree;
    float coef[101];
} polynomial;

// Function to read a polynomial
polynomial read_polynomial() {
    polynomial p;
    int i;

    printf("Enter degree of polynomial: ");
    scanf("%d", &p.degree);

    if (p.degree < 0 || p.degree > 100) {
        printf("Invalid degree!\n");
        p.degree = -1;
        return p;
    }

    printf("Enter coefficients from highest degree to constant:\n");

    for (i = 0; i <= p.degree; i++) {
        printf("Coefficient of x^%d: ", p.degree - i);
        scanf("%f", &p.coef[i]);
    }

    return p;
}

// Function to add two polynomials
polynomial polynomial_add(polynomial a, polynomial b) {
    polynomial sum;
    int i, exp;

    sum.degree = (a.degree > b.degree) ? a.degree : b.degree;

    for (i = 0; i <= sum.degree; i++) {
        exp = sum.degree - i;

        float x = 0, y = 0;

        if (exp <= a.degree)
            x = a.coef[a.degree - exp];

        if (exp <= b.degree)
            y = b.coef[b.degree - exp];

        sum.coef[i] = x + y;
    }

    // Remove leading zero coefficients
    while (sum.degree > 0 && sum.coef[0] == 0) {
        for (i = 0; i < sum.degree; i++)
            sum.coef[i] = sum.coef[i + 1];

        sum.degree--;
    }

    return sum;
}

// Function to display a polynomial
void display(polynomial p) {
    int i, exp, first = 1;
    float c;

    for (i = 0; i <= p.degree; i++) {
        exp = p.degree - i;
        c = p.coef[i];

        if (c == 0)
            continue;

        if (!first) {
            if (c > 0)
                printf(" + ");
            else
                printf(" - ");
        } else if (c < 0) {
            printf("-");
        }

        if (c < 0)
            c = -c;

        if (exp == 0 || c != 1)
            printf("%g", c);

        if (exp > 0) {
            printf("x");
            if (exp > 1)
                printf("^%d", exp);
        }

        first = 0;
    }

    if (first)
        printf("0");

    printf("\n");
}

int main() {
    polynomial a, b, sum;

    printf("Enter first polynomial:\n");
    a = read_polynomial();

    if (a.degree == -1)
        return 1;

    printf("\nEnter second polynomial:\n");
    b = read_polynomial();

    if (b.degree == -1)
        return 1;

    printf("\nFirst polynomial: ");
    display(a);

    printf("Second polynomial: ");
    display(b);

    sum = polynomial_add(a, b);

    printf("Sum of polynomials: ");
    display(sum);

    return 0;
}

