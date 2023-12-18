
Simple Task Manager in C
Overview
The Enhanced Task Manager is an advanced console-based application developed in C to provide users with a robust task management experience. This project incorporates various features, including dynamic memory allocation, task priorities, due dates, task categories, and task status tracking. Additionally, tasks are stored persistently in a file, allowing users to access and manage tasks across program executions.

Features
Add Task:

Users can add detailed tasks with information such as name, description, priority, due date, and initial status.
Dynamic memory allocation enables the management of a flexible number of tasks.
List Tasks:

Displays a comprehensive list of tasks, including their IDs, names, descriptions, priorities, due dates, and statuses.
Supports sorting tasks based on priority, due date, and status for better organization.
Remove Task:

Users can remove a task by specifying its unique ID.
Memory is efficiently managed to release resources upon task removal.
Update Task Status:

Allows users to update the status of a task (To Do, In Progress, Done) based on its lifecycle.
File-Based Storage:

Persists tasks in a file (tasks.txt) to ensure data persistence between program executions.
Tasks are loaded from the file on program startup and saved back to the file upon program exit.
User-Friendly Interface:

Intuitive console interface with an extended menu for advanced functionalities.
Provides a richer user experience with detailed task information.
How to Use
Run the program.

Choose from the extended menu options:

1: Add Task
2: List Tasks
3: Remove Task
4: Update Task Status
5: Exit
Follow the prompts to perform the selected action.
