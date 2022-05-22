// hola hola.

#include <unistd.h>
#include <ncurses.h>

int main(int argc, char *argv[]){
	int i;
	initscr();
	erase();
	for(i=0;i<20;i++){
		move(3,i);
		printw(" x");
		refresh();
		sleep(1);
    }
	endwin();
  return(0);
}
