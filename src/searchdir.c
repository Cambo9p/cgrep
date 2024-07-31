#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define INP 1
#define OUTP 0

void cgrep_search_dir(char *dir, char *pattern) {
    printf("searching for '%s' in %s\n", pattern, dir);
    // redirect stdout to buffer
    // dup() saves std... to the var for later use
    // set stdout back to normal
    int out_pipe[2];
    int stdout_saved;
    char buffer[500];

    stdout_saved = dup(STDIN_FILENO);
    if (pipe(out_pipe) != 0) {
        perror("failed to open pipe\n");
        exit(1);
    }

    execl("/bin/ls", "ls", "-l", NULL);

    read(out_pipe[0], buffer, 500);

    dup2(stdout_saved, STDOUT_FILENO); // stdout back to normal
    printf("read: %s\n", buffer);
}
