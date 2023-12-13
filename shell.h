#ifndef SHELL_H
#define SHELL_H_


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void display_prompt(void);
void user_input(char *command, size_t size);
void execute_command(const char *command);

#endif
