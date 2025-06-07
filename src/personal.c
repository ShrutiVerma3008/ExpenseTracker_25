// personal_expense_cli.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_CATEGORY_LEN 50
#define MAX_LINE_LEN 256
#define CSV_FILE "data/personal_expenses.csv"

void addPersonalExpense();
void viewSummaryByPeriod();
void setMonthlyBudget();
void compareBudget();
float getMonthlyBudget();

int personalMenu() {
    int choice;
    while (1) {
        printf("\n------ Personal Expense Menu ------\n");
        printf("1. Add Expense\n");
        printf("2. View Summary by Period\n");
        printf("3. Set Monthly Budget\n");
        printf("4. Compare Budget\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addPersonalExpense();
                break;
            case 2:
                viewSummaryByPeriod();
                break;
            case 3:
                setMonthlyBudget();
                break;
            case 4:
                compareBudget();
                break;
            case 5:
                printf("Exiting Personal Expense Module.\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}

void addPersonalExpense() {
    char date[20], category[MAX_CATEGORY_LEN];
    float amount;

    printf("Enter date (YYYY-MM-DD): ");
    scanf("%s", date);
    printf("Enter category (e.g., Food, Rent): ");
    scanf("%s", category);
    printf("Enter amount: ");
    scanf("%f", &amount);

    FILE *file = fopen(CSV_FILE, "a");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, "%s,%s,%.2f\n", date, category, amount);
    fclose(file);
    printf("Expense recorded successfully.\n");
}

void viewSummaryByPeriod() {
    FILE *file = fopen(CSV_FILE, "r");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    char line[MAX_LINE_LEN];
    float total = 0;
    char month[8];
    time_t t = time(NULL);
    struct tm *current = localtime(&t);
    snprintf(month, sizeof(month), "%04d-%02d", current->tm_year + 1900, current->tm_mon + 1);

    printf("\nShowing summary for current month: %s\n", month);
    while (fgets(line, sizeof(line), file)) {
        char date[20], category[MAX_CATEGORY_LEN];
        float amount;
        sscanf(line, "%[^,],%[^,],%f", date, category, &amount);
        if (strncmp(date, month, 7) == 0) {
            total += amount;
        }
    }
    fclose(file);
    printf("Total spent this month: Rs %.2f\n", total);
}

void setMonthlyBudget() {
    float budget;
    printf("Enter monthly budget amount: ");
    scanf("%f", &budget);

    FILE *file = fopen("data/monthly_budget.txt", "w");
    if (!file) {
        printf("Error saving budget.\n");
        return;
    }
    fprintf(file, "%.2f", budget);
    fclose(file);
    printf("Monthly budget set successfully.\n");
}

float getMonthlyBudget() {
    FILE *file = fopen("data/monthly_budget.txt", "r");
    if (!file) return 0;
    float budget;
    fscanf(file, "%f", &budget);
    fclose(file);
    return budget;
}

void compareBudget() {
    FILE *file = fopen(CSV_FILE, "r");
    if (!file) {
        printf("Error opening expense file.\n");
        return;
    }

    float total = 0;
    char line[MAX_LINE_LEN], month[8];
    time_t t = time(NULL);
    struct tm *current = localtime(&t);
    snprintf(month, sizeof(month), "%04d-%02d", current->tm_year + 1900, current->tm_mon + 1);

    while (fgets(line, sizeof(line), file)) {
        char date[20], category[MAX_CATEGORY_LEN];
        float amount;
        sscanf(line, "%[^,],%[^,],%f", date, category, &amount);
        if (strncmp(date, month, 7) == 0) {
            total += amount;
        }
    }
    fclose(file);

    float budget = getMonthlyBudget();
    printf("\nYour set budget: Rs %.2f\n", budget);
    printf("Total spent this month: Rs %.2f\n", total);

    if (total <= budget)
        printf("🎉 You are within budget! Saved: Rs %.2f\n", budget - total);
    else
        printf("⚠️  You overspent by Rs %.2f\n", total - budget);
}
