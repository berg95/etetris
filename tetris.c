/*
Etetris - Simple tetris clone 
questions or advice? contact me: ethanberg95@gmail.com
*/

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <ctype.h>

#include "tetris.h"

struct termios stdterm; // save standard terminal flags for resetTerm on exit

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

// reset the terminal back to standard canonical mode
void resetTerm(int fd) {
    tcsetattr(fd,TCSAFLUSH,&stdterm);
}

// had to make this function because of trouble with atexit()
void disableRawMode() {
  resetTerm(STDIN_FILENO);
}

// setting up the terminal for proper reading of input
void enableRawMode(int fd) {

    tcgetattr(STDIN_FILENO, &stdterm);
    atexit(disableRawMode);
    
    struct termios newterm = stdterm;
    newterm.c_lflag &= ~(ECHO | ICANON | ISIG);

    tcsetattr(fd,TCSAFLUSH,&newterm);
}

/*----------------------------------------------|
| Main function is not yet started develeopment |
| it is setup like this for debugging purposes  |
|----------------------------------------------*/
int main() {
    enableRawMode(STDIN_FILENO);

    char c;
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q') {
      if (iscntrl(c)) {
	printf("%d\n", c);
      } else {
	printf("%d ('%c')\n", c, c);
      }
    }
}


// TODO: create arrays to represent blocks
// TODO: Set up the tetris board
// TODO: create a block falling system
// TODO: configure keybindings and algorithms to rotate tetris blocks
// TODO: make user input reading run concurrently with the block falling system
// TODO: make a help menu
// TODO: set up point system and tetris row removal
// TODO: make losing the game possible
// TODO: Hiscores
// TODO: documentation and info in readme.md
