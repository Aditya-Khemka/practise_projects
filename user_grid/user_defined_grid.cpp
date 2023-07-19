#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

// Function to clear the console screen
void clrscr() {
    system("cls");
}

// Function to move cursor to the specified location
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Function to print the grid layout
void PrintGrid(int No_Rows, int No_Col, int screenWidth, int screenHeight) {
    int i, j, RowWidth, ColHeight, RowExtra, ColExtra;
    int StartRow[No_Rows], EndRow[No_Rows], StartCol[No_Col], EndCol[No_Col];

    // Calculate row dimensions
    RowWidth = screenHeight / No_Rows;
    RowExtra = screenHeight % No_Rows;

    // Calculate starting and ending positions for each row
    StartRow[0] = 0;
    EndRow[0] = RowWidth;
    for (i = 1; i < No_Rows; i++) {
        StartRow[i] = EndRow[i - 1];
        EndRow[i] = StartRow[i] + RowWidth;
        if (RowExtra > 0) {
            EndRow[i] += 1;
            RowExtra--;
        }
    }

    // Calculate column dimensions
    ColHeight = screenWidth / No_Col;
    ColExtra = screenWidth % No_Col;

    // Calculate starting and ending positions for each column
    StartCol[0] = 0;
    EndCol[0] = ColHeight;
    for (j = 1; j < No_Col; j++) {
        StartCol[j] = EndCol[j - 1];
        EndCol[j] = StartCol[j] + ColHeight;
        if (ColExtra > 0) {
            EndCol[j] += 1;
            ColExtra--;
        }
    }

    // Print horizontal lines of the grid
    for (i = 0; i < No_Rows; i++) {
        for (j = 0; j < No_Col; j++) {
            for (RowWidth = StartCol[j]; RowWidth < EndCol[j]; RowWidth++) {
                gotoxy(RowWidth, StartRow[i]);
                cout << char(196); // ASCII character for horizontal line
                gotoxy(RowWidth, EndRow[i]);
                cout << char(196); // ASCII character for horizontal line
            }
        }
    }

    // Print vertical lines of the grid
    for (i = 0; i < No_Rows; i++) {
        for (j = 0; j < No_Col; j++) {
            for (ColHeight = StartRow[i]; ColHeight < EndRow[i]; ColHeight++) {
                gotoxy(StartCol[j], ColHeight);
                cout << char(179); // ASCII character for vertical line
                gotoxy(EndCol[j], ColHeight);
                cout << char(179); // ASCII character for vertical line
            }
        }
    }

    // Print edges to complete the grid outline
    for (i = 1; i < No_Col; i++) {
        gotoxy(StartCol[i], StartRow[0]);
        cout << char(194); // ASCII character for T-shaped intersection
        gotoxy(StartCol[i], EndRow[No_Rows - 1]);
        cout << char(193); // ASCII character for upside-down T-shaped intersection
    }

    for (i = 1; i < No_Rows; i++) {
        gotoxy(StartCol[0], StartRow[i]);
        cout << char(195); // ASCII character for L-shaped intersection
        gotoxy(EndCol[No_Col - 1], StartRow[i]);
        cout << char(180); // ASCII character for backward L-shaped intersection
    }

    // Print corners of the grid
    gotoxy(StartCol[0], StartRow[0]);
    cout << char(218); // ASCII character for top-left corner
    gotoxy(EndCol[No_Col - 1], StartRow[0]);
    cout << char(191); // ASCII character for top-right corner
    gotoxy(StartCol[0], EndRow[No_Rows - 1]);
    cout << char(192); // ASCII character for bottom-left corner
    gotoxy(EndCol[No_Col - 1], EndRow[No_Rows - 1]);
    cout << char(217); // ASCII character for bottom-right corner

    // Print intersection characters between cells
    for (i = 1; i < No_Col; i++) {
        for (j = 1; j < No_Rows; j++) {
            gotoxy(StartCol[i], StartRow[j]);
            cout << char(197); // ASCII character for plus-shaped intersection
        }
    }

    // Move the cursor to the bottom-right corner of the grid
    gotoxy(screenWidth, screenHeight);
}

int main() {
    int No_Rows, No_Col;

    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_MAXIMIZE); // Set console window to full screen

    // Prompt user to enter the number of columns and rows for the grid
    cout << "Enter Columns: ";
    cin >> No_Col;
    cout << "Enter Rows: ";
    cin >> No_Rows;

    int screenWidth , screenHeight ; 
    screenWidth=165 , screenHeight=43 ; 
    /*
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    */
   if(No_Rows<=0 || No_Col<=0 || No_Col>=screenWidth || No_Rows>=screenHeight)
    {
        cout<<"Please enter valid dimensions" ; 
        getch();
        return(-1);
    }

    clrscr(); // Clear the console screen
    PrintGrid(No_Rows, No_Col, screenWidth, screenHeight); // Draw the grid with the specified number of rows and columns
    getch() ; 
    
    return 0;
}
