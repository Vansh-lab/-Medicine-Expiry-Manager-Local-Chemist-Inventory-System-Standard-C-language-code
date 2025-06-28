C, file-handling, medicine-tracker, inventory, pharmacy, CLI, mini-project, ATS-friendly, system-date

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILE_NAME "medicines.txt"

typedef struct {
    char name[50];
    int day, month, year;
    int quantity;
} Medicine;

void addMedicine() {
    FILE *fp = fopen(FILE_NAME, "a");
    if (!fp) {
        printf(" Error opening file.\n");
        return;
    }

    Medicine m;
    getchar();  // clear newline
    printf("Enter medicine name:\n ");
    fgets(m.name, sizeof(m.name), stdin);
    m.name[strcspn(m.name, "\n")] = '\0';

    printf("Enter expiry date (dd mm yyyy):\n ");
    scanf("%d %d %d", &m.day, &m.month, &m.year);
    printf("Enter quantity:\n ");
    scanf("%d", &m.quantity);

    fprintf(fp, "%s %02d %02d %04d %d\n", m.name, m.day, m.month, m.year, m.quantity);
    fclose(fp);
    printf(" Medicine added successfully!\n");
}

int isExpired(int d, int m, int y) {
    time_t t = time(NULL);
    struct tm *today = localtime(&t);

    if (y < (today->tm_year + 1900))
      return 1;
    if (y == (today->tm_year + 1900) && m < (today->tm_mon + 1))
      return 1;
    if (y == (today->tm_year + 1900) && m == (today->tm_mon + 1) && d < today->tm_mday) 
      return 1;
    return 0;
}

void viewMedicines() {
    FILE *fp = fopen(FILE_NAME, "r");
    if (!fp) {
        printf(" No records found.\n");
        return;
    }

    Medicine m;
    printf(" All Medicines:\n");
    while (fscanf(fp, "%s %d %d %d %d", m.name, &m.day, &m.month, &m.year, &m.quantity) != EOF) {
        printf(" %s | Expiry: %02d-%02d-%04d | Qty: %d %s\n", m.name, m.day, m.month, m.year, m.quantity,
               isExpired(m.day, m.month, m.year) ? " EXPIRED" : "");
    }
    fclose(fp);
}

int main() {
    int choice;

    while (1) {
        printf("\n🧪 Medicine Expiry Manager\n");
        printf("1. Add Medicine\n");
        printf("2. View All Medicines\n");
        printf("0. Exit\n");
        printf("Choose:\n ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addMedicine();
              break;
            case 2: viewMedicines();
              break;
            case 0: printf(" Exiting.\n"); 
              return 0;
            default: 
          printf(" Invalid option.\n");
          return 0;
        }
    }
}
