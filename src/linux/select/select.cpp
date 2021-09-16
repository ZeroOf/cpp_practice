//
// Created by Will Lee on 2021/9/10.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>

void SetFD(fd_set &rfds, int fd);

void SetTimeVal(timeval &tv);

int main(void) {
    fd_set rfds[1023];


    struct timeval tv;

    for (;;) {
        SetFD(rfds[0], STDIN_FILENO);
        SetFD(rfds[1], STDOUT_FILENO);
        SetTimeVal(tv);
        int retval = select(1025, rfds, NULL, NULL, &tv);
        /* Don't rely on the value of tv now! */
        if (retval == -1)
            perror("select()");
        else if (retval) {
            for (int i = 0; i < 1023 && retval > 0; ++i) {
                char buf[10]{0};
                if (FD_ISSET(i, rfds)) {
                    int nbytes = read(i, buf, 1024);
                    printf("Data size %d . data <%s> \n", nbytes, buf);
                }
            }
            /* FD_ISSET(0, &rfds) will be true. */
            continue;
        } else {
            printf("No data within five seconds.\n");
            continue;
        }

        exit(EXIT_SUCCESS);
    }

}

void SetTimeVal(timeval &tv) {
    tv.tv_sec = 5;
    tv.tv_usec = 0;
}

void SetFD(fd_set &rfds, int fd) {
    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);
}
