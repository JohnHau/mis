#include<stdio.h>
#include<curses.h>


int main(int argc,char* argv[])
{


	initscr();
	cbreak();
	noecho();
	clear();

	mvaddch(10,10,'A');
	refresh();

	getch();

	endwin();



	//	printf("hello world\n");

	return 0;
}
