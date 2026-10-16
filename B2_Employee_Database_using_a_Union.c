
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[20];
    int emp_id;
    enum { FULL_TIME, CONTRACT } type;

    union {
        float salary;
        struct {
            float hourly_rate;
            int hours_worked;
        } contract_info;
    } pay;
} Employee;

int main() {
    int n, i;
    float total_bill = 0, total_pay;
    Employee *emp;

    printf("Enter number of employees: ");
    scanf("%d", &n);

    emp = (Employee *)malloc(n * sizeof(Employee));

    if (emp == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Read employee details
    for (i = 0; i < n; i++) {
        printf("\nEnter details of employee %d\n", i + 1);

        printf("Enter name: ");
        scanf("%19s", emp[i].name);

        printf("Enter employee ID: ");
        scanf("%d", &emp[i].emp_id);

        printf("Enter type (0-Full-time, 1-Contract): ");
        scanf("%d", (int *)&emp[i].type);

        if (emp[i].type == FULL_TIME) {
            printf("Enter monthly salary: ");
            scanf("%f", &emp[i].pay.salary);
        } else if (emp[i].type == CONTRACT) {
            printf("Enter hourly rate: ");
            scanf("%f", &emp[i].pay.contract_info.hourly_rate);

            printf("Enter hours worked: ");
            scanf("%d", &emp[i].pay.contract_info.hours_worked);
        } else {
            printf("Invalid employee type!\n");
            free(emp);
            return 1;
        }
    }

    // Print payslips
    printf("\n========== EMPLOYEE PAYSLIPS ==========\n");

    for (i = 0; i < n; i++) {
        if (emp[i].type == FULL_TIME) {
            total_pay = emp[i].pay.salary;
        } else {
            total_pay = emp[i].pay.contract_info.hourly_rate
                      * emp[i].pay.contract_info.hours_worked;
        }

        printf("\nEmployee Name : %s\n", emp[i].name);
        printf("Employee ID   : %d\n", emp[i].emp_id);
        printf("Employee Type : ");

        if (emp[i].type == FULL_TIME)
            printf("Full-time\n");
        else
            printf("Contract\n");

        printf("Total Pay     : Rs. %.2f\n", total_pay);

        total_bill += total_pay;
    }

    printf("\nTotal Salary Bill = Rs. %.2f\n", total_bill);

    free(emp);

    return 0;
}

