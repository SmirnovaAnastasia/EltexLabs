#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "taxih.h"


int main() {
    char input[MAX_INPUT_LEN];
    char *args[MAX_ARGS];
    int argc;

    int number_of_drivers = 0;
    pid_t arr_drivers[25];
    int status[25]; // 0 - free, 1 - busy

    // //All status need to be 0
    for (int i = 0; i < 25; i++)
    {
        status[i] = 0;
    }

    printf("Print 'help' for commands.\n");

    while (1) {
        printf("> ");
        fflush(stdout);

        if (!fgets(input, MAX_INPUT_LEN, stdin)) break;
        
        input[strcspn(input, "\n")] = '\0';

        //Parse string frome console
        parse_input(input, args, &argc);

        // printf("Args = %s\n", args[0]);
        
        if (argc == 0) continue;
        
        //Main function for work
        execute_command(args, argc, &number_of_drivers, arr_drivers, status);
    }
    
    return 0;
}

