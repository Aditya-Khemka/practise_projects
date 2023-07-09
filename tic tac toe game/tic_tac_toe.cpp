#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

//global variables
int grid[3][3]; //3x3 grid that represents the matrix
int rem = 9 ; //indicates number of empty cells
const int sr[3] = { 10, 20, 30 } ,sc[3] = { 5, 15, 25 } ,er[3] = { 20, 30, 40 } , ec[3] = { 15, 25, 35 } ; //row and col index

//function to move cursor to the specified location
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//prints matrix at the start of the game 
void PrintGrid() 
{
    int i, j, r, c, n = 1;
    HWND hwnd = GetConsoleWindow(); 
    ShowWindow(hwnd, SW_MAXIMIZE); //full screen

    //print table (using | and __ only)
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            for (r = sr[i]; r <= er[i]; r++) {
                gotoxy(r, sc[j]); cout << char(196);
                gotoxy(r, ec[j]); cout << char(196);
            }
            for (c = sc[j]; c <= ec[j]; c++) {
                gotoxy(sr[i], c); cout << char(179);
                gotoxy(er[i], c); cout << char(179);
            }
        }
    }

    // Borders
    for (i = 1; i <= 2; i++) {
        gotoxy(sr[i], sc[0]); cout << char(194);
        gotoxy(sr[i], ec[2]); cout << char(193);
        gotoxy(sr[0], sc[i]); cout << char(195);
        gotoxy(er[2], sc[i]); cout << char(180);
    }

    // Edges
    gotoxy(sr[0], sc[0]); cout << char(218);
    gotoxy(er[2], sc[0]); cout << char(191);
    gotoxy(sr[0], ec[2]); cout << char(192);
    gotoxy(er[2], ec[2]); cout << char(217);

    // Cells
    for (i = 1; i <= 2; i++) {
        for (j = 1; j <= 2; j++) {
            gotoxy(sr[i], sc[j]); cout << char(197);
        }
    }

    // Cell numbers
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            grid[i][j] = 0; // all ceels in grid[][] to 0 . 
            r = sr[i] + 1;
            c = sc[j] + 1;
            gotoxy(r, c); cout << n;
            n++;
        }
    }
}

bool checkWinner(int player) 
{
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (grid[i][0] == player && grid[i][1] == player && grid[i][2] == player) {
            return true;
        }
    }

    // Check columns
    for (int j = 0; j < 3; j++) {
        if (grid[0][j] == player && grid[1][j] == player && grid[2][j] == player) {
            return true;
        }
    }

    // Check diagonals
    if (grid[0][0] == player && grid[1][1] == player && grid[2][2] == player) {
        return true;
    }
    if (grid[0][2] == player && grid[1][1] == player && grid[2][0] == player) {
        return true;
    }

    return false;
}


void play(int player) 
{
    int cell, i , j , c, r, num=1;

    gotoxy(10, 1); cout << "Cell for player number " << player << " : ";
    gotoxy(38, 1); cout << "   ";
    gotoxy(38, 1); cin >> cell; cell = cell-1; //input for player. -1 to adjust 

    if(cell <0 || cell>8)
    {
        play(player) ; //invalid cell no 
    }


    i=cell/3 ; //row 
    j=cell%3; //col
    if(grid[i][j] == 0) //available
    {
        grid[i][j] = player ; 
        rem--;
        r = sr[i] + (er[i] - sr[i]) / 2 ;
        c = sc[j] + (ec[j] - sc[j]) / 2 ;
        if (player == 1) 
        {
             gotoxy(r, c); cout << "X";
        }
        else if (player == 2) 
        {
            gotoxy(r, c); cout << "O";
        }
        
    }
    else
    {
        play(player) ;
    }
}

int main() {
    PrintGrid();
    int player = 1; 

    while (rem >= 1 && rem <= 9) 
    {
        if (player == 1) 
        {
            play(player) ;
            if(checkWinner(player))
            {
                gotoxy(10,1) ; cout<<"                                                    " ;
                gotoxy(10,1) ; cout<<"player "<<player<<" won " ; 
                break ; 
            }
            player = 2;
        }
        else if (player == 2) 
        {
            player = 1;
            play(player) ;
            if(checkWinner(player))
            {
                gotoxy(10,1) ; cout<<"                                                    " ;
                gotoxy(10,1) ; cout<<"player "<<player<<" won " ; 
                break ; 
            }
        }
        else 
        {
            cout << "error";
            break;
        }
    }

    if(rem<=0 || rem>=10)
    {
        gotoxy(10,1) ;     cout<<"                                                    " ;
        gotoxy(10,1) ;     cout<<"DRAW" ;  
    }
    getch();
    return 0;
}