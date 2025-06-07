// group_expense_cli.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define MAX_MEMBERS 20
#define MAX_NAME_LEN 50
#define MAX_TRANSACTIONS 100
#define MAX_GROUPS 10
#define GROUP_FOLDER "data/groups/"

typedef struct {
    char payer[MAX_NAME_LEN];
    char payee[MAX_NAME_LEN];
    float amount;
    char category[MAX_NAME_LEN];
    char timestamp[20];
} GroupTransaction;

typedef struct {
    char name[MAX_NAME_LEN];
    char members[MAX_MEMBERS][MAX_NAME_LEN];
    int numMembers;
    GroupTransaction transactions[MAX_TRANSACTIONS];
    int numTransactions;
} Group;

Group currentGroup;

void createGroup();
void addMember();
void addGroupTransaction();
void settleGroupDebts();
void exportGroupCSV();

void groupMenu() {
    int choice;
    while (1) {
        printf("\n------ Group Expense Menu ------\n");
        printf("1. Create New Group\n");
        printf("2. Add Member\n");
        printf("3. Add Group Transaction\n");
        printf("4. Settle Debts\n");
        printf("5. Export Group to CSV\n");
        printf("6. Exit Group Menu\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: createGroup(); break;
            case 2: addMember(); break;
            case 3: addGroupTransaction(); break;
            case 4: settleGroupDebts(); break;
            case 5: exportGroupCSV(); break;
            case 6: return;
            default: printf("Invalid choice.\n");
        }
    }
}

void createGroup() {
    printf("Enter group name: ");
   // scanf(" %[^\n]", currentGroup.name);  // Read string until newline
    fgets(currentGroup.name, sizeof(currentGroup.name), stdin); 
    currentGroup.numMembers = 0;
    currentGroup.numTransactions = 0;
    printf("Group '%s' created.\n", currentGroup.name);
}

void addMember() {
    if (currentGroup.numMembers >= MAX_MEMBERS) {
        printf("Maximum members reached.\n");
        return;
    }
    printf("Enter member name: ");
    scanf("%s", currentGroup.members[currentGroup.numMembers]);
    printf("Added: %s (ID: %d)\n", currentGroup.members[currentGroup.numMembers], currentGroup.numMembers);
    currentGroup.numMembers++;
}

int findMemberIndex(const char* name) {
    for (int i = 0; i < currentGroup.numMembers; i++) {
        if (strcmp(currentGroup.members[i], name) == 0)
            return i;
    }
    return -1;
}

void addGroupTransaction() {
    if (currentGroup.numTransactions >= MAX_TRANSACTIONS) {
        printf("Transaction limit reached.\n");
        return;
    }
    GroupTransaction* t = &currentGroup.transactions[currentGroup.numTransactions++];

    printf("Enter payer name: ");
    scanf("%s", t->payer);
    printf("Enter payee name: ");
    scanf("%s", t->payee);
    printf("Enter amount: ");
    scanf("%f", &t->amount);
    printf("Enter category: ");
    scanf("%s", t->category);

    time_t now = time(NULL);
    strftime(t->timestamp, sizeof(t->timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));

    printf("Transaction added: %s paid Rs%.2f to %s\n", t->payer, t->amount, t->payee);
}

void settleGroupDebts() {
    float balances[MAX_MEMBERS] = {0};
    for (int i = 0; i < currentGroup.numTransactions; i++) {
        int payerIdx = findMemberIndex(currentGroup.transactions[i].payer);
        int payeeIdx = findMemberIndex(currentGroup.transactions[i].payee);
        if (payerIdx == -1 || payeeIdx == -1) continue;
        balances[payerIdx] -= currentGroup.transactions[i].amount;
        balances[payeeIdx] += currentGroup.transactions[i].amount;
    }
    printf("\n--- Settlement Summary ---\n");
    for (int i = 0; i < currentGroup.numMembers; i++) {
        if (balances[i] != 0) {
            printf("%s: %s Rs%.2f\n", currentGroup.members[i], balances[i] > 0 ? "gets" : "owes", fabs(balances[i]));
        }
    }
}

void exportGroupCSV() {
    char filename[100];
    snprintf(filename, sizeof(filename), "%s%s.csv", GROUP_FOLDER, currentGroup.name);
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error writing group CSV.\n");
        return;
    }
    fprintf(file, "Payer,Payee,Amount,Category,Timestamp\n");
    for (int i = 0; i < currentGroup.numTransactions; i++) {
        GroupTransaction* t = &currentGroup.transactions[i];
        fprintf(file, "%s,%s,%.2f,%s,%s\n", t->payer, t->payee, t->amount, t->category, t->timestamp);
    }
    fclose(file);
    printf("Exported to %s\n", filename);
}
