# Simple Shell Project

This Simple Shell project, created by Abigael Karushi and Ian Gongo for 0x16, is a command-line interpreter implemented in C.

## General Requirements

- **Allowed Editors:** vi, vim, emacs
- **Compilation:** All files will be compiled on Ubuntu 20.04 LTS using gcc, with the options `-Wall -Werror -Wextra -pedantic -std=gnu89`.
- **File Conventions:** All files should end with a new line.
- **Mandatory README:** A README.md file at the root of the project is mandatory.
- **Coding Style:** Code should follow the Betty style and will be checked using `betty-style.pl` and `betty-doc.pl`.
- **Memory Management:** The shell should not have any memory leaks.
- **Function Limit:** No more than 5 functions per file.
- **Header Files:** All header files should be include guarded.
- **System Calls:** Use system calls only when necessary (why?).

## List of Allowed Functions and System Calls

- (List provided in the prompt)

## Project Description

**hsh** is a simple UNIX command language interpreter that reads commands from either a file or standard input and executes them.

### How hsh works:

1. Prints a prompt (`$ `) and waits for a command from the user.
2. Creates a child process in which the command is checked.
3. Checks for built-ins, aliases in the PATH, and local executable programs.
4. Replaces the child process with the command, which accepts arguments.
5. When the command is done, the program returns to the parent process and prints the prompt.
6. The program is ready to receive a new command.
7. To exit, press Ctrl-D or enter "exit" (with or without a status).

### Compilation

Compile the shell with the following command:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

