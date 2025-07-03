#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct ToDo {
    char task[100];
    char check;
    int priority;
    int index;
} ToDo;

ToDo t;
long int size = sizeof(t);
COORD cord = {0, 0};

void gotoxy(int x, int y) {
    cord.X = x;
    cord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
}

FILE *fp, *ft;

void create() {
    system("cls");
    fseek(fp, 0, SEEK_END);
    char another = 'Y';
    while (another == 'Y' || another == 'y') {
        printf("Enter index of task : ");
        scanf("%d", &t.index);
        printf("\nEnter Task : ");
        scanf(" %99[^\n]", t.task);
        priority();
        t.check = 'n';
        fwrite(&t, size, 1, fp);
        printf("\nWant to add another task(Y/N) :");
        fflush(stdin);
        scanf(" %c", &another);
    }
}

void priority() {
    printf("Priority :\n1.Must Do \n2.Should Do \n3.Could Do \n4.If I have time\n");
    printf("Enter priority : ");
    scanf("%d", &t.priority);
    while (t.priority < 1 || t.priority > 4) {
        printf("INVALID CHOICE FOR PRIORITY\nEnter priority again: ");
        scanf("%d", &t.priority);
    }
}

void deleterecord() {
    system("cls");
    int taskindex;
    char another = 'Y';
    while (another == 'Y' || another == 'y') {
        printf("\nEnter index no of task to be deleted : ");
        scanf("%d", &taskindex);
        ft = fopen("temp.txt", "wb");
        rewind(fp);
        while (fread(&t, size, 1, fp) == 1) {
            if (t.index != taskindex)
                fwrite(&t, size, 1, ft);
        }
        fclose(fp);
        fclose(ft);
        remove("task.txt");
        rename("temp.txt", "task.txt");
        fp = fopen("task.txt", "rb+");
        printf("\nWant to delete another task (Y/N) : ");
        fflush(stdin);
        another = getche();
    }
}

void display() {
    system("cls");
    ToDo temp;
    ToDo *sortedTasks = NULL;
    int i = 0, j, count = 0;

    rewind(fp);
    while (fread(&temp, size, 1, fp) == 1) {
        sortedTasks = (ToDo *) realloc(sortedTasks, (count + 1) * sizeof(ToDo));
        sortedTasks[count] = temp;
        count++;
    }

    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (sortedTasks[j].priority > sortedTasks[j + 1].priority) {
                temp = sortedTasks[j];
                sortedTasks[j] = sortedTasks[j + 1];
                sortedTasks[j + 1] = temp;
            }
        }
    }

    gotoxy(35, 2);
    quote();
    printf("Priority :\n1.Must Do \n2.Should Do \n3.Could Do \n4.If I have time\n");
    printf("Enter priority : ");
    int n;
    scanf("%d", &n);
    printf("-----------------------------------------------------------------------\n");
    printf("Index\t\tTask\n");
    printf("-----------------------------------------------------------------------\n");
    for (i = 0; i < count; i++) {
        if (n == 0 || sortedTasks[i].priority == n) {
            printf("%d\t\t%s [%s]\n", sortedTasks[i].index,
                   sortedTasks[i].task, sortedTasks[i].check == 'd' ? "completed" : "not completed");
        }
    }
    printf("-----------------------------------------------------------------------\n");
    char another = 'Y';
    free(sortedTasks);
    printf("\n");
    system("pause");
}


void modify() {
    system("cls");
    int taskindex;
    char another = 'Y';
    while (another == 'Y') {
        printf("\nEnter index no of task to be modified : ");
        scanf("%d", &taskindex);
        rewind(fp);
        while (fread(&t, size, 1, fp) == 1) {
            if (t.index == taskindex) {
                printf("\nEnter new task : ");
                scanf(" %99[^\n]", t.task);
                priority();
                fseek(fp, -size, SEEK_CUR);
                fwrite(&t, size, 1, fp);
                break;
            }
        }
        printf("\nWant to modify another record (Y/N) : ");
        fflush(stdin);
        scanf(" %c", &another);
    }
}

void markCompleted() {
    system("cls");
    int taskindex;
    char another = 'Y';
    while (another == 'Y') {
        printf("\nEnter index no of task to mark as completed : ");
        scanf("%d", &taskindex);
        rewind(fp);
        while (fread(&t, size, 1, fp) == 1) {
            if (t.index == taskindex) {
                t.check = 'd';
                fseek(fp, -size, SEEK_CUR);
                fwrite(&t, size, 1, fp);
                break;
            }
        }
        printf("\nWant to mark another task as completed (Y/N) : ");
        fflush(stdin);
        scanf(" %c", &another);
    }
}

void quote() {
    int quoteIndex = rand() % 10;
    switch (quoteIndex) {
        case 0:
            printf("Quote: The best way to predict the future is to create it.\n");
            break;
        case 1:
            printf("Quote: You miss 100 percent of the shots you don't take.\n");
            break;
        case 2:
            printf("Quote: Life is what happens when you're busy making other plans.\n");
            break;
        case 3:
            printf("Quote: The purpose of our lives is to be happy.\n");
            break;
        case 4:
            printf("Quote: Get busy living or get busy dying.\n");
            break;
        case 5:
            printf("Quote: It's not about having time; it's about making time.\n");
            break;
        case 6:
            printf("Quote: Start where you are. Use what you have. Do what you can.\n");
            break;
        case 7:
            printf("Quote: You are just one task away from a better day.\n");
            break;
        case 8:
            printf("Quote: Make today so awesome that yesterday gets jealous.\n");
            break;
        case 9:
            printf("Quote: Nothing is Impossible the word itself says I'm possible.\n");
            break;
    }
}

int main() {
    int choice;
    fp = fopen("task.txt", "rb+");
    if (fp == NULL) {
        fp = fopen("task.txt", "wb+");
        if (fp == NULL) {
            printf("\nCannot open file...");
            exit(1);
        }
    }
    system("Color F0");
    gotoxy(40, 2);
    printf("WELCOME TO TO-DO LIST\n\n");
    system("pause");
    while (1) {
        system("cls");
        gotoxy(30, 2);
        printf("\n1. Add Task");
        gotoxy(30, 4);
        printf("\n2. Delete Task");
        gotoxy(30, 6);
        printf("\n3. Display ToDo list");
        gotoxy(30, 8);
        printf("\n4. Modify Task");
        gotoxy(30, 10);
        printf("\n5. Mark as completed");
        gotoxy(30, 12);
        printf("\n6. Exit");
        gotoxy(30, 14);
        printf("\n Enter your choice : ");
        fflush(stdin);
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                create();
                break;
            case 2:
                deleterecord();
                break;
            case 3:
                display();
                break;
            case 4:
                modify();
                break;
            case 5:
                markCompleted();
                break;
            case 6:
                fclose(fp);
                exit(0);
                break;
            default:
                printf("\nINVALID CHOICE\n");
        }
    }
    return 0;
}
