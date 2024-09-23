#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100
#define MAX_SKILLS 50
#define MAX_NAME_LEN 50
#define MAX_SKILL_LEN 50

typedef struct {
    int day, month, year;
} Date;

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    char skills[MAX_SKILLS][MAX_SKILL_LEN];
    int skillCount;
    Date workDate;
} Employee;

void addEmployee(Employee employees[], int *count) {
    if (*count >= MAX_EMPLOYEES) {
        printf("Employee limit reached.\n");
        return;
    }
    
    Employee e;
    e.id = *count + 1;

    printf("Enter name: ");
    scanf(" %[^\n]", e.name);

    printf("Enter the number of skills: ");
    scanf("%d", &e.skillCount);

    for (int i = 0; i < e.skillCount; i++) {
        printf("Enter skill %d: ", i + 1);
        scanf(" %[^\n]", e.skills[i]);
    }

    printf("Enter the date (dd mm yyyy): ");
    scanf("%d %d %d", &e.workDate.day, &e.workDate.month, &e.workDate.year);

    employees[*count] = e;
    (*count)++;
    printf("Employee added successfully!\n");
}

void updateEmployee(Employee employees[], int count) {
    int id;
    printf("Enter Employee ID to update: ");
    scanf("%d", &id);

    for (int i = 0; i < count; i++) {
        if (employees[i].id == id) {
            printf("Updating details for %s (ID: %d)\n", employees[i].name, id);

            printf("Enter new name: ");
            scanf(" %[^\n]", employees[i].name);

            printf("Enter the number of skills: ");
            scanf("%d", &employees[i].skillCount);

            for (int j = 0; j < employees[i].skillCount; j++) {
                printf("Enter skill %d: ", j + 1);
                scanf(" %[^\n]", employees[i].skills[j]);
            }

            printf("Enter the new date (dd mm yyyy): ");
            scanf("%d %d %d", &employees[i].workDate.day, &employees[i].workDate.month, &employees[i].workDate.year);

            printf("Employee updated successfully!\n");
            return;
        }
    }
    printf("Employee with ID %d not found.\n", id);
}

void deleteEmployee(Employee employees[], int *count) {
    int id;
    printf("Enter Employee ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < *count; i++) {
        if (employees[i].id == id) {
            for (int j = i; j < *count - 1; j++) {
                employees[j] = employees[j + 1];
            }
            (*count)--;
            printf("Employee deleted successfully!\n");
            return;
        }
    }
    printf("Employee with ID %d not found.\n", id);
}

void searchEmployee(Employee employees[], int count) {
    int id;
    char name[MAX_NAME_LEN];
    printf("Search by 1. ID or 2. Name? ");
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter Employee ID: ");
        scanf("%d", &id);

        for (int i = 0; i < count; i++) {
            if (employees[i].id == id) {
                printf("Employee found: %s\n", employees[i].name);
                return;
            }
        }
    } else if (choice == 2) {
        printf("Enter Employee Name: ");
        scanf(" %[^\n]", name);

        for (int i = 0; i < count; i++) {
            if (strcmp(employees[i].name, name) == 0) {
                printf("Employee found: %s (ID: %d)\n", employees[i].name, employees[i].id);
                return;
            }
        }
    }

    printf("Employee not found.\n");
}

void sortEmployees(Employee employees[], int count) {
    int choice;
    printf("Sort by 1. ID, 2. Name, or 3. Work Date? ");
    scanf("%d", &choice);

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if ((choice == 1 && employees[i].id > employees[j].id) ||
                (choice == 2 && strcmp(employees[i].name, employees[j].name) > 0) ||
                (choice == 3 && (employees[i].workDate.year > employees[j].workDate.year ||
                                (employees[i].workDate.year == employees[j].workDate.year && employees[i].workDate.month > employees[j].workDate.month) ||
                                (employees[i].workDate.year == employees[j].workDate.year && employees[i].workDate.month == employees[j].workDate.month && employees[i].workDate.day > employees[j].workDate.day)))) {
                Employee temp = employees[i];
                employees[i] = employees[j];
                employees[j] = temp;
            }
        }
    }

    printf("Employees sorted successfully!\n");
}

void saveToFile(Employee employees[], int count) {
    FILE *file = fopen("employees.txt", "w");
    if (!file) {
        printf("Could not open file for saving.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%d %s %d ", employees[i].id, employees[i].name, employees[i].skillCount);
        for (int j = 0; j < employees[i].skillCount; j++) {
            fprintf(file, "%s ", employees[i].skills[j]);
        }
        fprintf(file, "%d %d %d\n", employees[i].workDate.day, employees[i].workDate.month, employees[i].workDate.year);
    }

    fclose(file);
    printf("Data saved successfully!\n");
}

void loadFromFile(Employee employees[], int *count) {
    FILE *file = fopen("employees.txt", "r");
    if (!file) {
        printf("Could not open file for loading.\n");
        return;
    }

    *count = 0;
    while (fscanf(file, "%d %[^\n] %d", &employees[*count].id, employees[*count].name, &employees[*count].skillCount) != EOF) {
        for (int i = 0; i < employees[*count].skillCount; i++) {
            fscanf(file, "%s", employees[*count].skills[i]);
        }
        fscanf(file, "%d %d %d", &employees[*count].workDate.day, &employees[*count].workDate.month, &employees[*count].workDate.year);
        (*count)++;
    }

    fclose(file);
    printf("Data loaded successfully!\n");
}

void displayEmployees(Employee employees[], int count) {
    if (count == 0) {
        printf("No employees to display.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("ID: %d\n", employees[i].id);
        printf("Name: %s\n", employees[i].name);
        printf("Skills: ");
        for (int j = 0; j < employees[i].skillCount; j++) {
            printf("%s", employees[i].skills[j]);
            if (j < employees[i].skillCount - 1) printf(", ");
        }
        printf("\nWork Date: %02d-%02d-%d\n", employees[i].workDate.day, employees[i].workDate.month, employees[i].workDate.year);
        printf("---------------------------\n");
    }
}

int main() {
    Employee employees[MAX_EMPLOYEES];
    int count = 0;
    int choice;

    loadFromFile(employees, &count);

    do {
        printf("Employee Management System\n");
        printf("1. Add Employee\n");
        printf("2. Update Employee\n");
        printf("3. Delete Employee\n");
        printf("4. Search Employee\n");
        printf("5. Sort Employees\n");
        printf("6. Display All Employees\n");
        printf("7. Save & Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(employees, &count);
                break;
            case 2:
                updateEmployee(employees, count);
                break;
            case 3:
                deleteEmployee(employees, &count);
                break;
            case 4:
                searchEmployee(employees, count);
                break;
            case 5:
                sortEmployees(employees, count);
                break;
            case 6:
                displayEmployees(employees, count);
                break;
            case 7:
                saveToFile(employees, count);
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}
