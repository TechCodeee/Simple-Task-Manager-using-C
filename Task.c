#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_NAME_LENGTH 50
#define MAX_DESCRIPTION_LENGTH 100
#define FILENAME "tasks.txt"

typedef enum {
    TODO,
    IN_PROGRESS,
    DONE
} TaskStatus;

typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    char description[MAX_DESCRIPTION_LENGTH];
    int priority;
    char dueDate[12]; // Format: YYYY-MM-DD
    TaskStatus status;
} Task;

void saveTasksToFile(Task tasks[], int taskCount);
void loadTasksFromFile(Task tasks[], int *taskCount);
void addTask(Task tasks[], int *taskCount);
void listTasks(Task tasks[], int taskCount);
void removeTask(Task tasks[], int *taskCount, int taskId);
void updateTaskStatus(Task tasks[], int taskCount, int taskId, TaskStatus newStatus);

int main() {
    Task tasks[MAX_TASKS];
    int taskCount = 0;
    int choice;

    loadTasksFromFile(tasks, &taskCount);

    do {
        printf("\nAdvanced Task Manager\n");
        printf("1. Add Task\n");
        printf("2. List Tasks\n");
        printf("3. Remove Task\n");
        printf("4. Update Task Status\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTask(tasks, &taskCount);
                break;
            case 2:
                listTasks(tasks, taskCount);
                break;
            case 3: {
                int taskId;
                printf("Enter the task ID to remove: ");
                scanf("%d", &taskId);
                removeTask(tasks, &taskCount, taskId);
                break;
            }
            case 4: {
                int taskId;
                printf("Enter the task ID to update status: ");
                scanf("%d", &taskId);
                int statusChoice;
                printf("Select new status:\n");
                printf("1. To Do\n");
                printf("2. In Progress\n");
                printf("3. Done\n");
                printf("Enter your choice: ");
                scanf("%d", &statusChoice);
                TaskStatus newStatus;
                switch (statusChoice) {
                    case 1:
                        newStatus = TODO;
                        break;
                    case 2:
                        newStatus = IN_PROGRESS;
                        break;
                    case 3:
                        newStatus = DONE;
                        break;
                    default:
                        printf("Invalid choice. Status not updated.\n");
                        continue;
                }
                updateTaskStatus(tasks, taskCount, taskId, newStatus);
                break;
            }
            case 5:
                printf("Exiting Task Manager. Goodbye!\n");
                saveTasksToFile(tasks, taskCount);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

void saveTasksToFile(Task tasks[], int taskCount) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < taskCount; i++) {
        fprintf(file, "%d;%s;%s;%d;%s;%d\n", tasks[i].id, tasks[i].name, tasks[i].description,
                tasks[i].priority, tasks[i].dueDate, tasks[i].status);
    }

    fclose(file);
}

void loadTasksFromFile(Task tasks[], int *taskCount) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No existing tasks found.\n");
        return;
    }

    while (!feof(file) && *taskCount < MAX_TASKS) {
        Task task;
        fscanf(file, "%d;%49[^;];%99[^;];%d;%11[^;];%d\n", &task.id, task.name, task.description,
               &task.priority, task.dueDate, &task.status);
        tasks[*taskCount] = task;
        (*taskCount)++;
    }

    fclose(file);
}

void addTask(Task tasks[], int *taskCount) {
    if (*taskCount < MAX_TASKS) {
        Task newTask;
        newTask.id = *taskCount + 1;

        printf("Enter task name: ");
        scanf(" %[^\n]", newTask.name);

        printf("Enter task description: ");
        scanf(" %[^\n]", newTask.description);

        printf("Enter task priority (1 - Low, 2 - Medium, 3 - High): ");
        scanf("%d", &newTask.priority);

        printf("Enter due date (YYYY-MM-DD): ");
        scanf("%s", newTask.dueDate);

        newTask.status = TODO;

        tasks[*taskCount] = newTask;
        (*taskCount)++;

        printf("Task added successfully!\n");
    } else {
        printf("Task manager is full. Cannot add more tasks.\n");
    }
}

void listTasks(Task tasks[], int taskCount) {
    if (taskCount == 0) {
        printf("No tasks available.\n");
    } else {
        printf("Task List:\n");
        printf("ID\tName\tPriority\tDue Date\tStatus\n");
        for (int i = 0; i < taskCount; i++) {
            printf("%d\t%s\t%d\t\t%s\t\t", tasks[i].id, tasks[i].name, tasks[i].priority, tasks[i].dueDate);
            switch (tasks[i].status) {
                case TODO:
                    printf("To Do\n");
                    break;
                case IN_PROGRESS:
                    printf("In Progress\n");
                    break;
                case DONE:
                    printf("Done\n");
                    break;
            }
        }
    }
}

void removeTask(Task tasks[], int *taskCount, int taskId) {
    int found = 0;
    for (int i = 0; i < *taskCount; i++) {
        if (tasks[i].id == taskId) {
            found = 1;
            // Remove the task by shifting remaining tasks
            for (int j = i; j < *taskCount - 1; j++) {
                tasks[j] = tasks[j + 1];
            }
            (*taskCount)--;
            printf("Task removed successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("Task not found with ID %d.\n", taskId);
    }
}

void updateTaskStatus(Task tasks[], int taskCount, int taskId, TaskStatus newStatus) {
    int found = 0;
    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].id == taskId) {
            found = 1;
            tasks[i].status = newStatus;
            printf("Task status updated successfully!\n");
            break;
        }
    }
    if (!found) {
        printf("Task not found with ID %d.\n", taskId);
    }
}
