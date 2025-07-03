# ToDo List using File Handling

This is a simple console-based To-Do List application written in C. It uses file handling to persist data, allowing users to manage their tasks across multiple sessions.

## 💡 Features

- Add new tasks with priorities
- Display tasks filtered by priority
- Mark tasks as completed
- Modify existing tasks
- Delete tasks by index
- Save tasks using file handling (`task.txt`)
- Motivational quote displayed on viewing the list

## 📂 File Structure

- `main.c` – The main source code file.
- `task.txt` – Auto-created to store tasks (binary format).
- `.cbp`, `.depend`, `.layout` – Code::Blocks project files.

## 🛠️ Usage

1. Compile using a C compiler (e.g., GCC or Code::Blocks).
2. Run the executable.
3. Follow the menu options to manage your tasks.

## 📌 Task Priority Levels

1. Must Do  
2. Should Do  
3. Could Do  
4. If I Have Time

## 💻 Requirements

- Windows OS (uses `windows.h` and `SetConsoleCursorPosition`)
- C compiler (GCC, Code::Blocks)

## 📜 Notes

- The app uses binary file I/O, so editing `task.txt` manually isn't recommended.
- All console output is styled for a better CLI experience using `gotoxy()`.

## 🧠 Motivation

This was created to practice C programming, especially file handling and simple data structures.

---

### 🎯 Sample Quote Output

> "The best way to predict the future is to create it."

---

## 📃 License

This project is open source and free to use.
