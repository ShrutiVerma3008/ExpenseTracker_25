//#include "personal.c"
//#include "group.c"
// inside main loop:
//groupMenu();
// main_menu_cli.c
#include <stdio.h>

int personalMenu();   // from personal.c
void groupMenu();      // from group.c

int main() {
    int choice;
    while (1) {
        printf("\n=========== 💸 Cash Flow Manager 💸 ===========\n");
        printf("1. 🧍 Personal Expense Management\n");
        printf("2. 👥 Group Expense Splitting\n");
        printf("3. 🚪 Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                personalMenu();
                break;
            case 2:
                groupMenu();
                break;
            case 3:
                printf("Exiting Cash Flow Manager.\n");
                return 0;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
