#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

struct termios stdterm;

enum KEY_ACTION{
        KEY_NULL = 0,       /* NULL */
        CTRL_C = 3,         /* Ctrl-c */
        CTRL_D = 4,         /* Ctrl-d */
        CTRL_F = 6,         /* Ctrl-f */
        CTRL_H = 8,         /* Ctrl-h */
        TAB = 9,            /* Tab */
        CTRL_L = 12,        /* Ctrl+l */
        ENTER = 13,         /* Enter */
        CTRL_Q = 17,        /* Ctrl-q */
        CTRL_S = 19,        /* Ctrl-s */
        CTRL_U = 21,        /* Ctrl-u */
        ESC = 27,           /* Escape */
        BACKSPACE =  127,   /* Backspace */
        /* The following are just soft codes, not really reported by the
         * terminal directly. */
        ARROW_LEFT = 1000,
        ARROW_RIGHT,
        ARROW_UP,
        ARROW_DOWN,
        DEL_KEY,
        HOME_KEY,
        END_KEY,
        PAGE_UP,
        PAGE_DOWN
};

void resetTerm(int fd) {
    tcsetattr(fd,TCSAFLUSH,&stdterm);
}

void disableRawMode(void) {
    resetTerm(STDIN_FILENO);
}

void enableRawMode(int fd) {
    struct termios newterm;
    newterm = stdterm;
    atexit(disableRawMode);

    newterm.c_lflag &= ~(ECHO | ICANON | ISIG);

    tcsetattr(fd,TCSAFLUSH,&newterm);
}

int main() {
    enableRawMode(STDIN_FILENO);

    char c;
    while (read(STDIN_FILENO, &c, 1) == 1);

    printf("%d\n", c);
}