#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <unistd.h>
#include <aio.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <netdb.h> 
  
#define PORT     8900 
#define MAXLINE 1024 


#define LOG_FILE "game.log"

#define DIALOG_WIDTH 40
#define DIALOG_HEIGHT 20
#define CONTENT_WIDTH (DIALOG_WIDTH - 2)


#define HEAD   'A'
#define BODY   'O'
#define BLANK  ' '
#define DIR_UP     0
#define DIR_DOWN   1
#define DIR_LEFT   2
#define DIR_RIGHT  3

int dir= DIR_RIGHT;
int cx=0;
int cy=0;
struct snake_body
{
	int posx;
	int posy;

};

int body_len =2;
struct snake_body body[20];

int c;

void set_colors() 
{
  // these don't actually have anything to do with binary, so we are free to use "normal" numbers
  init_pair(1, COLOR_RED, COLOR_BLACK); // red on black
  init_pair(2, COLOR_GREEN, COLOR_BLACK); // green on black
  init_pair(3, COLOR_YELLOW, COLOR_BLACK); // yellow on black
  init_pair(4, COLOR_BLUE, COLOR_BLACK); // blue on black
  init_pair(5, COLOR_MAGENTA, COLOR_BLACK); // magenta on black
  init_pair(6, COLOR_CYAN, COLOR_BLACK); // cyan on black
  init_pair(7, COLOR_WHITE, COLOR_BLACK); // white on black
}

void end_curses() 
{
  endwin();
}

// a simple log function, works similar to printf
void glog(const char *format, ... ) 
{
  va_list args; // argument list
  static FILE *logfile = NULL; // file pointer to the logfile
  char *fformat; // the modified format of the string which will be written to the logfile
  int length; // length of the format

  if(!(format == NULL && logfile == NULL)) {
    // open the logfile if not already opened
    if(logfile == NULL) {
      logfile = fopen(LOG_FILE, "w");
      // if that doesn't work exit with an error message
      if(logfile == NULL) {
        fprintf(stderr, "Cannot open logfile %s\n", LOG_FILE);
        exit(EXIT_FAILURE);
      }
    }

    // if NULL is given as format, close the opened file
    if(format != NULL) {
      // increase length by 2 (for \n\0
      length = strlen(format) + 2;
      // allocate memory
      fformat = malloc(sizeof(char) * length);
      // copy the format over
      strncpy(fformat, format, length - 2);
      // append \n\0
      fformat[length - 2] = '\n';
      fformat[length - 1] = '\0';

      // get the rest of the arguments
      va_start(args, format);

      // use vfprintf() to 
      vfprintf(logfile, fformat, args); 
      // forces the logmessage to be written into the file right now
      fflush(logfile);
     
      va_end(args);

      // free the allocated memory for the format string
      free(fformat);
    } 
    else 
    {
      // close the logfile
      fclose(logfile);
    }
  }
}



// create a basic dialog with title which looks like this:
//
// +--------------------------------------+
// +---------------- TITLE ---------------+
// +--------------------------------------+
// |                                      |
// |                                      |
// |                                      |
// |                                      |
// |                                      |
// |                                      |
// |                                      |
// |                                      |
// |                                      |
// |                                      |
// |                                      |
// |                                      |
// |                                      |
// |                                      |
// |                                      |
// |                                      |
// +--------------------------------------+
//
WINDOW *create_dialog_window(const char *title) {
  WINDOW *win;
  int sx, sy, i, u, startpos;

  // get the screen size
  getmaxyx(stdscr, sy, sx);
  // create a little window in the center of the screen with a border and a size of 40x20
  win = newwin(DIALOG_HEIGHT, DIALOG_WIDTH, sy / 2 - DIALOG_HEIGHT / 2, sx / 2 - DIALOG_WIDTH / 2);

  // create the border
  wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');

  // fill the first two lines with "-" and "+" on the border
  for(u = 1; u <= 2; u++) {
    for(i = 0; i < DIALOG_WIDTH; i++) {
      mvwprintw(win, u, i, "%c", i == 0 || i == DIALOG_WIDTH - 1 ? '+' : '-');
    }
  }

  // print the title in the middle of the dialog
  startpos = DIALOG_WIDTH / 2 - strlen(title) / 2;
  // print a space before the title
  mvwprintw(win, 1, startpos - 1, " ");
  // print the title itself
  mvwprintw(win, 1, startpos, "%s", title);
  // print a space after the title
  mvwprintw(win, 1, startpos + strlen(title), " ");
  return win;
}


// creates a dialog with menu entries, you can press numbers to select a menu entry and close the dialog
int create_numbered_dialog(const char *title, const char *contents, int lines) {
  WINDOW *win = create_dialog_window(title);
  int i, ch, number = 0;

  // insert menu entries into the dialog
  for(i = 0; i < lines; i++) {
    mvwprintw(win, i + 3, 1, &contents[i * CONTENT_WIDTH], i + 1);
  }

  // display the dialog
  wrefresh(win);

  // wait for some input
  while((ch = wgetch(win))) {
    // error? begin again.
    //if(ch == ERR) continue;

    // select the first menu entry if enter is pressed
    if(ch == '\n') ch = '1';
    // a number pressed?
    if(ch >= '0' && ch <= '9') {
      number = ch - '0';
      // prevent from handling numbers which are > than the number of menu entries
      if(ch - '0' <= lines) {
        // get out of the loop
        break;
      }
    }
  }

  // delete the window
  delwin(win);

  // return the number pressed
  return number;
}


// displays the main menu
int display_menu() 
{
  // the contents of the menu
  // %i will be replaced with the number of the menu entry
  char menu[][CONTENT_WIDTH] = 
  {
  "%i) Start the game",
  "%i) Highscores",
  "%i) Controls",
  "%i) Help",
  "%i) Clear Highscores",
  "%i) Exit"
  };
  // create a numbered dialog
  return create_numbered_dialog("MENU", (char *)menu, 6);
}


void main_menu() 
{
  int selected_menu_entry;
  do {
    selected_menu_entry = display_menu();
    if(selected_menu_entry == 1) {
      // run the game
      //run();
    } else if(selected_menu_entry == 2) {
      // display the highscores
      //show_highscores();
    } else if(selected_menu_entry == 3) {
      // display a dialog which explains the controls of the game
      //display_controls();
    } else if(selected_menu_entry == 4) {
      // display a dialog which explains the elements of the game
      //display_help();
    } else if(selected_menu_entry == 5) {
      // clear highscores
#if 0
      if(clear_score_dialog() == 1) 
      {
          clear_highscore();
      }
#endif
    }
    // leave if the menu entry "exit" is chosen
  } while(selected_menu_entry != 6);
}

#if 0
void enable_kbd_signals(void)
{

	int fd_flags;

	fcntl(0,F_SETOWN,getpid());
	fd_flags = fcntl(0,F_GETFL);

	fcntl(0,F_SETFL,(fd_flags|O_ASYNC));
	//fcntl(0,F_SETFL,(fd_flags|O_RSYNC));

}
#endif


struct aiocb  kbcbuf;
void setup_aio_buffer(void)
{

	static char input[1];

	kbcbuf.aio_fildes = 0;
	kbcbuf.aio_buf = input;
	kbcbuf.aio_nbytes = 1;
	kbcbuf.aio_offset = 0;


	kbcbuf.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
	kbcbuf.aio_sigevent.sigev_signo = SIGIO;
	


}

int set_ticker(int n_msecs)
{
	struct itimerval new_timeset;
	long n_sec,n_usec;

	n_sec = n_msecs/1000;
	n_usec = (n_msecs%1000)*1000L;

	new_timeset.it_interval.tv_sec = n_sec;
	new_timeset.it_interval.tv_usec = n_usec;

	new_timeset.it_value.tv_sec = n_sec;
	new_timeset.it_value.tv_usec = n_usec;

	return setitimer(ITIMER_REAL,&new_timeset,NULL);

}

void on_timer(int signum)
{
	int j;
	static int i=0;
	move(10,10);	
	printw("hello world %d",i++);
	refresh();


	switch(dir)
	{
		case DIR_UP:
			cx -=1;
			break;

		case DIR_DOWN:

			cx +=1;
			break;

		case DIR_LEFT:

			cy -=1;
			break;

		case DIR_RIGHT:

			cy +=1;
			break;
	}

	move(11,10);	
	printw("body_len is  %d",body_len);

#if 1
	for(j=body_len;j>0;j--)
	{

		body[j].posx = body[j-1].posx;
		body[j].posy = body[j-1].posy;

	}

	body[j].posx =cx;
	body[j].posy =cy;

	for(j=0;j<body_len;j++)
	{
		move(body[j].posx,body[j].posy); 
		if(j ==0)
		{
			addch(HEAD);
		}
		else
		{

			addch(BODY);
		}

	}


	move(body[body_len].posx,body[body_len].posy);
	addch(BLANK);
#endif
	refresh(); 
} 


int onkey=0;
void on_input(int signum)
{
#if 0
	int c = getch();
	move(15,15);
	addch(c);

#endif

	char *cp = (char*)kbcbuf.aio_buf;/*cast to char*/

	if(aio_error(&kbcbuf) != 0)
	{
		perror("reading failed");
	}
	else
	{
		if(aio_return(&kbcbuf) == 1)
		{
			c=*cp;
			onkey = c;
			move(15,15);
			addch(c);
			refresh();
#if 1

			if(c == 'x')
			{
				switch(dir)
				{
					case DIR_UP:
						body[body_len].posx = body[body_len -1].posx+1; 
						body[body_len].posy = body[body_len -1].posy;
						body_len++;

						break;

					case DIR_DOWN:

						body[body_len].posx = body[body_len -1].posx-1; 
						body[body_len].posy = body[body_len -1].posy;
						body_len++;


						break;

					case DIR_LEFT:

						body[body_len].posx = body[body_len -1].posx; 
						body[body_len].posy = body[body_len -1].posy+1;
						body_len++;


						break;

					case DIR_RIGHT:

						body[body_len].posx = body[body_len -1].posx; 
						body[body_len].posy = body[body_len -1].posy-1;
						body_len++;

						break;

				}


				int m;

				for(m=0;m<body_len;m++)
				{
					move(body[m].posx,body[m].posy); 
					if(m ==0)
					{
						addch(HEAD);
					}
					else
					{

						addch(BODY);
					}

				}

				refresh();

			}

#endif

			if(c == 'q')
			{
				endwin();	
				printf("that is it\n");
				exit(EXIT_SUCCESS);

			}

		}

		aio_read(&kbcbuf);

	}

}


void init_curses() 
{

#if _BSD_SOURCE || _POSIX_C_SOURCE >= 200112L || _XOPEN_SOURCE >= 600
	// by default, ncurses stops the execution of the program for
	// 1 second if escape is pressed. Disable this behaviour.
	setenv("ESCDELAY", "0", 1);
#endif

	initscr();
	// get more control over the input
	cbreak();
	// getch() returns ERR if no input is present and doesn't wait
	//nodelay(stdscr, TRUE);
	// don't echo the inserted keys to the screen
	noecho();
	// colors!
	start_color();
	set_colors();
	// also grab keys like F1 etc.
	keypad(stdscr, TRUE);

}

int main(int argc, char* argv[])
{    


#if defined(use_UDP)
	int sockfd; 
	char hname[128]={0};
	char buffer[MAXLINE]; 
	char *hello = "Hello from server"; 
	struct sockaddr_in servaddr, cliaddr; 
	struct hostent *hent=NULL;

	gethostname(hname,sizeof(hname));
	hent = gethostbyname(hname);

	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
	{ 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 

	memset(&servaddr, 0, sizeof(servaddr)); 
	memset(&cliaddr, 0, sizeof(cliaddr)); 
	// Filling server information 
	servaddr.sin_family    = AF_INET; // IPv4 
	//servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 
	//servaddr.sin_port = PORT; 

	// Bind the socket with the server address 
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
				sizeof(servaddr)) < 0 ) 
	{ 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 

	int len, n; 
	len = sizeof(cliaddr);  //len is value/resuslt 

#endif

	WINDOW *xw;
		void on_input(int);
	signal(SIGIO,on_input);
	//enable_kbd_signals();

	setup_aio_buffer();
	aio_read(&kbcbuf);


	set_ticker(200);

	signal(SIGALRM,on_timer);
	init_curses();
	curs_set(0);



	int ti,tj;
#if 0
	body[0].posx=30;
	body[0].posy=30;

	body[1].posx=30;
	body[1].posy=29;
#endif

	for(ti=0;ti<body_len;ti++)
	{

		body[ti].posx=30;
		body[ti].posy=30-ti;

		move(body[ti].posx,body[ti].posy);

		if(ti == 0)
		{
			addch(HEAD);
		}
		else
		{

			addch(BODY);
		}

	}
	refresh();


	cx = body[0].posx;
	cy = body[0].posy;

	while(1)
	{

		switch(onkey)
		{

			case 'w':
				dir = DIR_UP;

				break;

			case 's':

				dir = DIR_DOWN;
				break;

			case 'a':

				dir = DIR_LEFT;
				break;

			case 'd':

				dir = DIR_RIGHT;
				break;

		}








#if defined(use_UDP) 
		//pause();
		move(20,25);
		//printf("waiting on port %d\n",PORT);
		printw("waiting on port %d\n",PORT);
		refresh();
#if 0
		n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
				MSG_WAITALL, ( struct sockaddr *) &cliaddr, 
				&len); 
#endif
		n = recvfrom(sockfd, (char *)buffer, MAXLINE,  
				0, ( struct sockaddr *) &cliaddr, 
				&len); 


		buffer[n] = '\0'; 
		//printf("Client : %s\n", buffer); 
		move(25,25);
		printw("Client : %s\n", buffer); 
		refresh();
#endif
		//sleep(5);
	}
	//	main_menu(); 
	//	xw=create_dialog_window("hello"); 
	//	wrefresh(xw);
	//	refresh();

	//	sleep(4);
	end_curses();
}
