
#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 50
#define MAX_WARDS 3

// structure of patient
struct Patient {
    char name[30];
    int age;
    int severity;
    int ward_no;
    int isAdmitted;
};

struct Patient p[MAX_PATIENTS];
int p_count = 0;  

// ward detail
char *wardNames[MAX_WARDS] = { "General", "Semi-Private", "ICU" };
int wardCapacity[MAX_WARDS] = { 5, 3, 2 };
int wardUsed[MAX_WARDS] = { 0, 0, 0 };


void admitPatient() {
    if(p_count >= MAX_PATIENTS) {
        printf("Patient limit full hai!\n");
        return;
    }

    printf("\n--- New patient admit ---\n");
    printf("Enter Name: ");
    scanf("%s", p[p_count].name);

    printf("Enter Age: ");
    scanf("%d", &p[p_count].age);

    printf("Enter Severity (1-10): ");
    scanf("%d", &p[p_count].severity);

    // ward selection based on severity
    int w = 0;
    if(p[p_count].severity >= 8) w = 2;
    else if(p[p_count].severity >= 5) w = 1;
    else w = 0;

    if(wardUsed[w] < wardCapacity[w]) {
        wardUsed[w]++;
        p[p_count].ward_no = w;
        p[p_count].isAdmitted = 1;
        printf("Patient %s admitted to %s ward.\n", p[p_count].name, wardNames[w]);
    } else {
        printf("Ward full hai, bed nahi mila. Sorry!\n");
        p[p_count].isAdmitted = 0;
    }

    p_count++;
}

void dischargePatient() {
    char name[30];
    printf("\nEnter patient name to discharge: ");
    scanf("%s", name);

    for(int i=0; i<p_count; i++) {
        if(strcmp(p[i].name, name) == 0 && p[i].isAdmitted == 1) {
            printf("Discharging %s from ward %s.\n", p[i].name, wardNames[p[i].ward_no]);
            wardUsed[p[i].ward_no]--;
            p[i].isAdmitted = 0;
            return;
        }
    }
    printf("Patient not found / already discharged.\n");
}

void displayWards() {
    printf("\n--- Ward Status ---\n");
    for(int i=0; i<MAX_WARDS; i++) {
        printf("%s: %d/%d occupied\n", wardNames[i], wardUsed[i], wardCapacity[i]);
    }
}

void displayPatients() {
    printf("\n--- All Patients ---\n");
    for(int i=0; i<p_count; i++) {
        printf("%s (Age %d) - ", p[i].name, p[i].age);
        
        if(p[i].isAdmitted)
            printf("In ward: %s\n", wardNames[p[i].ward_no]);
        else
            printf("Not admitted\n");
    }
}

int main() {
    int ch;

    while(1) {
        printf("\n====== Hospital Management ======\n");
        printf("1. Admit Patient\n");
        printf("2. Discharge Patient\n");
        printf("3. Ward Status\n");
        printf("4. Patient List\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        switch(ch) {
            case 1: admitPatient(); break;
            case 2: dischargePatient(); break;
            case 3: displayWards(); break;
            case 4: displayPatients(); break;
            case 5: printf("Exiting...\n"); return 0;
            default: printf("Galat choice hai bhai.\n");
        }
    }
}
