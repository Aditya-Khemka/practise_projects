#include <iostream>
#include <windows.h>
#include <conio.h>


using namespace std;

void clrscr() {
    system("cls");
}

//function to move cursor to the specified location
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void PrintGrid(int row , int col , int screenWidth , int screenHeight) {
    int i,j,r,c,x,y; 
    int sr[row], sc[col],er[row], ec[col] ;

    //rows or horizontals --
    r=screenHeight/row ;
    x=screenHeight%row;
    sr[0]=0;
    er[0]=r; 
    for(i=1 ; i<row ; i++)
    {
        sr[i]=er[i-1];
        er[i]=sr[i]+r ;
        if(x>0)
        {
            er[i]+=1;
            x--;
        }

    }

    c=screenWidth/col;
    y=screenWidth%col ;
    sc[0]=0;
    ec[0]=c ;
    for(j= 1; j<col ; j++)
    {
        sc[j]=ec[j-1];
        ec[j]=sc[j]+c;
        if(y>0)
        {
            ec[j]+=1;
            y--;
        }
    }


    for (i = 0; i < row; i++) 
    {
        for(j=0 ; j<col ; j++)
        {
            for(r=sc[j];r<ec[j];r++)
            {
                gotoxy(r,sr[i]) ; cout<<char(196);
                gotoxy(r,er[i]) ; cout<<char(196);
            }
            for(c=sr[i];c<er[i];c++)
            {
                gotoxy(sc[j],c) ; cout<<char(179);
                gotoxy(ec[j],c) ; cout<<char(179);
            }
            
        }
    }

    for (i = 1; i <col; i++) 
    {
        gotoxy(sc[i], sr[0]); cout << char(194);
        gotoxy(sc[i], er[row-1]); cout << char(193);
    }

    for (i = 1; i <row; i++) {
        gotoxy(sc[0], sr[i]); cout << char(195);
        gotoxy(ec[col-1], er[i]); cout << char(180);
    }

    // Edges
    gotoxy(sc[0], sr[0]); cout << char(218);
    gotoxy(ec[col-1], sc[0]); cout << char(191);
    gotoxy(sc[0], er[row-1]); cout << char(192);
    gotoxy(ec[col-1], er[row-1]); cout << char(217);

    for (i = 1; i <col; i++) {
        for (j = 1; j <row; j++) {
            gotoxy(sc[i], sr[j]); cout << char(197);
        }
    }

    gotoxy(screenWidth,screenHeight);

}

int main ()
{
    int row ,col ;
    HWND hwnd = GetConsoleWindow(); 
    ShowWindow(hwnd, SW_MAXIMIZE); //full screen
    cout<<"Enter Columns: " ; cin>>col ; 
    cout<<"Enter Rows: "; cin>>row ;
    clrscr();
    PrintGrid(row,col,120,60);
    getch() ;
    return 0 ;
}