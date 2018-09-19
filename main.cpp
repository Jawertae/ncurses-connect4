#include <iostream>
#include <ncurses.h>
#include <iomanip> 
#include <stdlib.h>


using namespace std;

void drawboard(WINDOW*);
void init();

int main()
{
    WINDOW *score;
    WINDOW *board;
    WINDOW *bottm;
    init();

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);


    refresh();


    attron(COLOR_PAIR(1));

    score = newwin(LINES,20,0,COLS-20);
    box(score, 0 , 0);
    wrefresh(score);


    board = newwin(LINES-5,COLS-20,0,0);
    box(board, 0 , 0);
    wrefresh(board);

    drawboard(board);

    bottm = newwin(5,COLS-20,LINES-5,0);
    box(bottm, 0 , 0);
    wrefresh(bottm);

    attroff(COLOR_PAIR(1));

    //score_win();
   
    getch();
    endwin();

    return 0;
};
void init()
{

    initscr();
    raw();
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    





}




void drawboard(WINDOW *win)
{
    int height,width;

    getmaxyx(win,height,width);

    for(int i=0;i<=10;i++)
    {
        mvwprintw(win,height/2-5+i ,width/2-15 ,"[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]\n");
    }

    box(win,0,0);

    wrefresh(win);

}
