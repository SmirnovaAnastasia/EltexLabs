#include <assert.h>
#include <signal.h>
#include <stdbool.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/wait.h> 
#include <unistd.h> 
#include <pthread.h>
#include <string.h>
#include <stdint.h>

void signal_handler(int signum, siginfo_t *siginfo, void *code) {
    char s1[] = "SIGUSR1\n";
    char s2[] = "SIGUSR2\n";
    if (signum == SIGUSR1) {
        write(STDOUT_FILENO, s1, sizeof(s1));
        printf("It's SIGUSR1!\n");
    } else if (signum == SIGUSR2) {
        write(STDOUT_FILENO, s2, sizeof(s2));
        printf("It's SIGUSR2!\n");
    }
    //sigaction(sig, signal_handler, NULL);
}

void set_signal_action()
{
    struct sigaction act1;
    memset(&act1, 0, sizeof(act1));
    act1.sa_sigaction = signal_handler;
    act1.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &act1, NULL);

    struct sigaction act2;
    memset(&act2, 0, sizeof(act2));
    act2.sa_sigaction = signal_handler;
    act2.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR2, &act2, NULL);
}

int main() {
    pid_t pid;

    set_signal_action();

    pid = fork();
    if (pid == -1) {
        perror("fork");
        assert(false);
    } else {
        if (pid == 0) {
            while (1);
            exit(EXIT_SUCCESS);
        }
        while (1) {
            kill(pid, SIGUSR1);
            sleep(1);
            kill(pid, SIGUSR2);
            sleep(1);
        }
    }
    return EXIT_SUCCESS;
}