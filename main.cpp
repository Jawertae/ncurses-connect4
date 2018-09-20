#include <iostream>
#include <ncurses.h>
#include <iomanip> 
#include <stdlib.h>


using namespace std;

void init();
void drawboard(WINDOW*);
void drawcursor(WINDOW*,int);
void pickmove(int,int);
void drawpiece(WINDOW*);

char place[10][10];

int main()
{
    WINDOW *score;                                      //Window for score.
    WINDOW *board;                                      //Window for the game board.
    WINDOW *bottm;                                      //Window for the Turn board.

    bool game_end = false;                              //
    int user_input = 0;                                 //
    int selection = 0;                                  //
    int turn = 0;                                       //

    init();

    score = newwin(LINES,20,0,COLS-20);                 // Score.
    box(score, 0 , 0);
    wrefresh(score);

    board = newwin(LINES-5,COLS-20,0,0);                // Game board.
    box(board, 0 , 0);
    wrefresh(board);

    bottm = newwin(5,COLS-20,LINES-5,0);                // Turn board.
    box(bottm, 0 , 0);
    wrefresh(bottm);

    drawboard(board);                                   //draw initial board

    while(!game_end)
    {
        drawpiece(board);                               //draw all pieces on top of board
        drawcursor(board,selection);                    //draw cursor as it moves
        mvwprintw(bottm,2,2,"Turn: %i",turn);           //write out turn number
        wrefresh(bottm);                                //
        user_input = getch();                           //wait for user input
        switch(user_input)                              //act based on user input
        {
            case KEY_RIGHT:
                selection++;
                if (selection==10){selection=0;}
                break;
            case KEY_LEFT:
                selection--;
                if (selection==-1){selection=9;}
                break;
             case KEY_DOWN:
                pickmove(turn,selection);               //take current selection and turn number and put a piece accordingly
                turn++;
                drawpiece(board);
                break;
            case 81:                                    //Q
            case 113:                                   //q
                game_end = true;
                break;
        }
    }

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
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    refresh();
}

void drawboard(WINDOW *win)
{
    int height,width;

    getmaxyx(win,height,width);

    for(int i=0;i<10;i++)
    {
        mvwprintw(win,height/2-5+i ,width/2-15 ,"[ ][ ][ ][ ][ ][ ][ ][ ][ ][ ]");
    }

    box(win,0,0);

    wrefresh(win);
}

void drawcursor(WINDOW *win,int selection)
{
    int height,width;

    getmaxyx(win,height,width);
    mvwprintw(win,height/2+5 ,width/2-15 ,"                              ");
    mvwprintw(win,height/2+5 ,width/2-14+3*selection ,"^");
    wmove(win,height/2-6 ,width/2-14+3*selection);
    box(win,0,0);
    wrefresh(win);
}

void pickmove(int turn,int selection)
{
    char piece;

    if (turn%2==0){piece='X';}
    else {piece='O';}

    for(int i=0;i<10;i++)
    {
        if (place[selection][i]==NULL)
        {
            place[selection][i]=piece;
            break;
        }
    }
}
void drawpiece(WINDOW *win)
{
    int height,width;
    int jun=0;

    getmaxyx(win,height,width);
    
    for(int i;i<10;i++)
    {
        while(jun<10)
        {
            mvwprintw(win,height/2+4-i ,width/2-14+3*jun ,"%c",place[jun][i]);
            jun++;
        }
    }
    wrefresh(win);
}
