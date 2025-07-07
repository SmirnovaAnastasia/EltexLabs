#ifndef TAXIH_H
#define TAXIH_H

#define MAX_INPUT_LEN 256
#define MAX_ARGS 10
#define BUFFER_SIZE 128

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <time.h>
#include <sys/time.h>
#include <signal.h>
#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>  // для fork(), getpid()
#include <sys/types.h> // для pid_t
#include <sys/wait.h>  // для wait()

void parse_input(char *input, char **args, int *argc);
void execute_command(char **args, int argc, int *number_of_drivers, pid_t *arr_drivers, int *status);
int search_driver(pid_t *arr_drivers, int driver, int *number_of_drivers);
int is_number(char const* arg);

pid_t create_driver();
void send_task(int pid, int task_timer);
void get_status(pid_t *arr_drivers, int *status, int *number_of_drivers, char *cli_pid);
void get_drivers(pid_t *arr_drivers, int *status, int *number_of_drivers);

#endif