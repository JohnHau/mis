#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>


int main(int argc, char*argv[])
{
initscr();
move(5,15);
printw("%s","hello world");
refresh();

sleep(10);

endwin();
exit(EXIT_SUCCESS);
	



}