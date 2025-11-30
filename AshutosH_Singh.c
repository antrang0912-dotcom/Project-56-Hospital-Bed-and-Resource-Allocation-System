#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ward {
    int id;
    int capacity;
    int used;
    char dept[20];
};

struct Patient {
    char name[30];
    int age;
    int severity;
    int ward_no;
};

void addPatient(struct Ward *w, int wc, struct Patient *p, int *pc);
void discharge(struct Ward *w, int wc, struct Patient *p, int *pc);
void showWards(struct Ward *w, int wc);
void showPatients(struct Patient *p, int pc);

int main() {

    int wc, pc = 0;
    printf("Enter number of wards: ");
    scanf("%d", &wc);

    struct Ward *wards = malloc(sizeof(struct Ward) * wc);
    struct Patient *patients = malloc(sizeof(struct Patient) * 200);

    for(int i = 0; i < wc; i++) {
        printf("\nWard %d details:\n", i+1);
        printf("Ward ID: ");
        scanf("%d", &wards[i].id);
        printf("Capacity: ");
        scanf("%d", &wards[i].capacity);
        printf("Department: ");
        scanf("%s", wards[i].dept);
        wards[i].used = 0;
    }

    int ch;
    do {
        printf("\n--- Hospital Menu ---\n");
        printf("1. Admit Patient\n");
        printf("2. Discharge Patient\n");
        printf("3. Show Ward Details\n");
        printf("4. Show Patient List\n");
        printf("5. Exit\n");
        printf("Choice: ");
        scanf("%d", &ch);

        switch(ch) {
            case 1: addPatient(wards, wc, patients, &pc); break;
            case 2: discharge(wards, wc, patients, &pc); break;
            case 3: showWards(wards, wc); break;
            case 4: showPatients(patients, pc); break;
            default: break;
        }

    } while(ch != 5);

    free(wards);
    free(patients);

    return 0;
}

void addPatient(struct Ward *w, int wc, struct Patient *p, int *pc) {

    struct Patient temp;

    printf("\nEnter name: ");
    scanf("%s", temp.name);
    printf("Age: ");
    scanf("%d", &temp.age);
    printf("Severity (1-10): ");
    scanf("%d", &temp.severity);

    int chosen = -1;

    // simple priority: choose ward with free beds
    for(int i = 0; i < wc; i++) {
        if(w[i].used < w[i].capacity) {
            if(chosen == -1) {
                chosen = i;
            } else if(temp.severity > 5 && (w[i].capacity - w[i].used) > (w[chosen].capacity - w[chosen].used)) {
                chosen = i;
            }
        }
    }

    if(chosen == -1) {
        printf("No beds available.\n");
        return;
    }

    w[chosen].used++;
    temp.ward_no = w[chosen].id;
    p[*pc] = temp;
    (*pc)++;

    printf("Patient admitted to ward %d (%s)\n", w[chosen].id, w[chosen].dept);
}

void discharge(struct Ward *w, int wc, struct Patient *p, int *pc) {
    char nm[30];
    printf("\nEnter patient name to discharge: ");
    scanf("%s", nm);

    for(int i = 0; i < *pc; i++) {
        if(strcmp(p[i].name, nm) == 0) {

            // reduce ward count
            for(int j = 0; j < wc; j++) {
                if(w[j].id == p[i].ward_no) {
                    w[j].used--;
                    break;
                }
            }

            // shift array
            for(int x = i; x < *pc - 1; x++) {
                p[x] = p[x+1];
            }
            (*pc)--;

            printf("Patient discharged.\n");
            return;
        }
    }

    printf("Patient not found.\n");
}

void showWards(struct Ward *w, int wc) {
    printf("\n--- Ward Info ---\n");
    for(int i = 0; i < wc; i++) {
        printf("Ward %d | Dept: %s | Used: %d | Free: %d | Capacity: %d\n",
               w[i].id, w[i].dept, w[i].used,
               w[i].capacity - w[i].used, w[i].capacity);
    }
}

void showPatients(struct Patient *p, int pc) {
    printf("\n--- Patients ---\n");
    for(int i = 0; i < pc; i++) {
        printf("%s | Age: %d | Sev: %d | Ward: %d\n",
               p[i].name, p[i].age, p[i].severity, p[i].ward_no);
    }
}
