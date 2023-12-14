#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

void execut_command(char *arg[]);
void reset_bauf(char *are[]);
void user_input(char *are[]);
void print_head(void);
void printer (char *string);
void for_free(char *buffer[]);
void set_buff(char *argv[], char *buffer[]);

#endif
