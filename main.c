#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct task{

char description[100];
int completed;
int day;
int month;
int year;
int hour;
int min;
int priority;

};
    struct list{
    struct task tasks[50];
    int size;
    };

void addTask(struct list *list, const char *description, int day, int month, int year, int hour, int min, int priority) {
    if (list-> size < 50) {
        struct task newTask;
        strcpy(newTask.description, description);
        newTask.completed = 0;
        newTask.day = day;
        newTask.month = month;
        newTask.year = year;
        newTask.hour = hour;
        newTask.min = min;
        newTask.priority = priority;

        list->tasks[list->size++] = newTask;
        printf("Task added successfully!\n");
    } else {
        printf("Task list is full!\n");
    }
}

void displayTasks(const struct list *list) {
    printf("Tasks:\n");
    if (list->size == 0) {
        printf("No tasks found!\n");
    } else {
        for (int i = 0; i < list->size; ++i) {
            printf("%d. [%c] %s - %02d/%02d/%d %02d:%02d\n", i+1, (list->tasks[i].completed ? 'X' : ' '),
                   list->tasks[i].description, list->tasks[i].day, list->tasks[i].month, list->tasks[i].year,
                   list->tasks[i].hour, list->tasks[i].min,list->tasks[i].priority);
        }
    }
}

void completeTask(struct list *list, int index) {
    if (index >= 0 && index < list->size) {
        list->tasks[index].completed = 1;
        printf("Task marked as completed!\n");
    } else {
        printf("Invalid task index!\n");
    }
}

void modifyTask(struct list *list, int index, const char *description, int day, int month, int year, int hour, int min, int priority) {
    if (index >= 0 && index < list->size) {
        strcpy(list->tasks[index].description, description);
        list->tasks[index].day = day;
        list->tasks[index].month = month;
        list->tasks[index].year = year;
        list->tasks[index].hour = hour;
        list->tasks[index].min = min;
        list->tasks[index].priority = priority;
        printf("Task modified successfully!\n");
    } else {
        printf("Invalid task index!\n");
    }
}

void deleteTask(struct list *list, int index) {
    if (index >= 0 && index < list->size) {
        for (int i = index; i < list->size - 1; ++i) {
            list->tasks[i] = list->tasks[i + 1];
        }
        list->size--;
        printf("Task deleted successfully!\n");
    } else {
        printf("Invalid task index!\n");
    }
}



void filter(const struct list *list, int priority) {
    printf("Tasks with priority %d:\n", priority);
    int found = 0;
    for (int i = 0; i < list->size; ++i) {
        if (list->tasks[i].priority == priority) {
            found = 1;
            printf("%d. [%c] %s - %02d/%02d/%d %02d:%02d\n", i+1, (list->tasks[i].completed ? 'X' : ' '),
                   list->tasks[i].description, list->tasks[i].day, list->tasks[i].month, list->tasks[i].year,
                   list->tasks[i].hour, list->tasks[i].min, list->tasks[i].priority);
        }
    }
    if (!found) {
        printf("No tasks with priority %d found!\n", priority);
    }

}

int main() {
    struct list tasks = { .size = 0 };

    int choice;
    char description[100];
    int index, day, month, year, hour ,min ,priority;

    do {
        printf("\n1. Add Task\n");
        printf("2. Display Tasks\n");
        printf("3. Complete Task\n");
        printf("4. Modify Task\n");
        printf("5. Delete Task\n");
        printf("6. Task by priority\n");
        printf("7. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter task description: ");
                scanf(" %[^\n]s", description);
                printf("Enter task deadline (dd mm yyyy hh mm): ");
                scanf("%d %d %d %d %d", &day, &month, &year, &hour, &min);
                printf("Enter task priority: ");
                scanf("%d", &priority);
                addTask(&tasks, description, day, month, year, hour, min, priority);
                break;
            case 2:

                displayTasks(&tasks);
                break;
            case 3:
                printf("Enter index of task to complete: ");
                scanf("%d", &index);
                completeTask(&tasks, index - 1);
                break;
            case 4:
                printf("Enter index of task to modify: ");
                scanf("%d", &index);
                printf("Enter new task description: ");
                scanf(" %[^\n]s", description);
                printf("Enter new task deadline (dd mm yyyy hh mm): ");
                scanf("%d %d %d %d %d", &day, &month, &year, &hour, &min);
                modifyTask(&tasks, index - 1, description, day, month, year, hour, min, priority);
                printf("Enter new task priority: ");
                scanf("%d", &priority);
                modifyTask(&tasks, index - 1, description, day, month, year, hour, min, priority);
                break;
            case 5:
                printf("Enter index of task to delete: ");
                scanf("%d", &index);
                deleteTask(&tasks, index - 1);
            case 6:
                printf("Enter priority to filter by: ");
                scanf("%d", &priority);
                filter(&tasks, priority);
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice!\n");

                return 0;
        }
    } while (choice < 6);

    return 0;
}
