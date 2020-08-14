#include <stdio.h>
#include <stdlib.h>

#include <time.h>

#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    
    time_t current_time = time(NULL);
    char * c_time_string = ctime(&current_time);

    /* Eliminate tail '\n' */
    int newline_position = strlen(c_time_string) - 1;
    if (c_time_string[newline_position] == '\n') {
        c_time_string[newline_position] = '\0';
    }
    
    char * log = getenv("LOG");
    if (!log) {
        log = "/var/log/fdtsexecutablelogger.log";
    }

    FILE * fd = fopen(log, "a+");

    if (!fd) {
        fprintf(stderr, "%s %s %s\n", c_time_string, log, strerror(errno));
        exit(errno);
    }

    fprintf(fd, "%s ", c_time_string);
    for (int i = 0; i < argc; ++i) {
        fprintf(fd, "%s ", argv[i]);
    }
    fprintf(fd, "\n");

    fclose(fd);

    return 0;
}
