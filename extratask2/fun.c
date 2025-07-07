#include "taxih.h"

//Parse string from console
void parse_input(char *input, char **args, int *argc) {
    int var = 0;
    *argc = 0;
    char *token = strtok(input, " ");
    
    while (token != NULL && *argc < MAX_ARGS - 1) {
        args[(*argc)++] = token;
        token = strtok(NULL, " ");
        var++;
    }
    
    if(var == 0){
        strcat(args[(*argc)++], input);
    }
}

int search_driver(pid_t *arr_drivers, int driver, int *number_of_drivers)
{
    int num = -1;
    for (int i = 0; i < *number_of_drivers; i++)
    {
        if(arr_drivers[i] == driver)
        {
            num = i;
        }
    }
    return num;
    
}

int is_number(char const* arg)
{
    int n;
    return(sscanf(arg, "%d", &n) == 1);
}

//Main function
void execute_command(char **args, int argc, int *number_of_drivers, pid_t *arr_drivers, int *status) {
    
    //If exit
    if (strcmp(args[0], "exit") == 0) {
        printf("Exiting CLI...\n");
        exit(0);
    }
    
    //If help
    else if (strcmp(args[0], "help") == 0) {
        printf("Available commands:\n");
        printf("  create_driver                               - Create new driver\n");
        printf("  send_task [number of driver] [time of task] - Send task for driver\n");
        printf("  get_drivers                                 - Get lost of all drivers\n");
        printf("  get_status [number of driver]               - Get status of one driver\n");
        printf("  exit                                        - Exit program\n");
        return;
    }
    
    //If create_driver
    else if ((strcmp(args[0], "create_driver") == 0 || strcmp(args[0], "cd") == 0 ) ) {

        if (*number_of_drivers >= 25)
        {
            printf("Can't create drivers. Don't have car!\n");
            exit(0);
        }

        pid_t pid = create_driver();

        arr_drivers[(*number_of_drivers)] = pid;
        *number_of_drivers = *number_of_drivers + 1;
                

        if(pid <= 0){
            printf("Driver wasn't create!\n");
            exit(0);
        }else{
            printf("Driver was create!\n");
        }
    }

    //If send_task
    else if (strcmp(args[0], "send_task") == 0 || strcmp(args[0], "s") == 0 ) {
        if(argc > 2){
            if((strcmp(args[1], "") != 0) && (strcmp(args[2], "") != 0) && search_driver(arr_drivers, atoi(args[1]), number_of_drivers) != -1 
                && atoi(args[2]) >= 0 && is_number(args[2]))
            {
                int not_char_pid = atoi(args[1]);
                int not_char_timer = atoi(args[2]);
                send_task(not_char_pid, not_char_timer);
            }else if(search_driver(arr_drivers, atoi(args[1]), number_of_drivers) == -1){
                printf("Wrong number of driver!\n");
            }else{
                printf("Wrong argumens for function!\n");
            }
        }else{
            printf("Wrong argumens for function!\n");
        }
    }
    
    //If get_status
    else if (strcmp(args[0], "get_status") == 0 || strcmp(args[0], "gs") == 0) {
        if(argc > 1)
        {
            get_status(arr_drivers, status, number_of_drivers, args[1]);
        }else{
            printf("Wrong argumens for function!\n");
        }

    }
    
    else if (strcmp(args[0], "get_drivers") == 0 || strcmp(args[0], "gd") == 0) {
        get_drivers(arr_drivers, status, number_of_drivers);
    }
    
    else{
        printf("Unknown command: %s\n", args[0]);   
    }
}