#include <iostream>
#include <windows.h>
#include <conio.h>


using namespace std;

//function to move cursor to the specified location
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

//prints matrix at the start of the game


void PrintGrid(int row , int col) {
    int i, j, r, c,n = 1; 

    int grid[row][col] ; 
    int sr[row] ,er[row],sc[row],ec[row] ; 
    
    r=24/row ;
    c=24%row;
    sr[0]=0; 
    er[0]=r;
    for(i=1 ; i<row ; i++)
    {
        sr[i] = er[i-1]; 
        er[i] = sr[i]+r;
        if(c>0)
        {
            er[i]+=1;
            c--;
        }
    }

    c=80/col ;
    r=80%col;
    sc[0]=0; 
    ec[0]=c;
    for(j=1 ; j<col ; j++)
    {
        sc[j] = ec[j-1]; 
        ec[j] = sc[j]+c;
        if(r>0)
        {
            ec[j]+=1;
            r--;
        }
    }

    cout<<endl ;

    //print table (using | and __ only)
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
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
    for (i = 1; i < row; i++) {
        gotoxy(sr[i], sc[0]); cout << char(194);
        gotoxy(sr[i], ec[col-1]); cout << char(193);
        gotoxy(sr[0], sc[i]); cout << char(195);
        gotoxy(er[row-1], sc[i]); cout << char(180);
    }

    // Edges
    gotoxy(sr[0], sc[0]); cout << char(218);
    gotoxy(er[row-1], sc[0]); cout << char(191);
    gotoxy(sr[0], ec[col-1]); cout << char(192);
    gotoxy(er[row-1], ec[col-1]); cout << char(217);

    // Cells
    for (i = 1; i < row; i++) {
        for (j = 1; j < col; j++) {
            gotoxy(sr[i], sc[j]); cout << char(197);
        }
    }

    // Cell numbers
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            grid[i][j] = 0; // all ceels in grid[][] to 0 . 
            r = sr[i] + 1;
            c = sc[j] + 1;
            gotoxy(r, c); cout << n;
            n++;
        }
    }
}

int main ()
{
    int row ,col ;
    HWND hwnd = GetConsoleWindow(); 
    ShowWindow(hwnd, SW_MAXIMIZE); //full screen
    cout<<"Enter Columns: " ; cin>>col ; 
    cout<<"Enter Rows: "; cin>>row ;
    PrintGrid(row ,col);
    getch() ;
    return 0 ;
}