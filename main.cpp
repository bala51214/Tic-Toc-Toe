#include <iostream>
#include <windows.h>
using namespace std;

const int ROWS = 3, COLS = 3;
char board[ROWS][COLS] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

void gotoRowCol(int rpos, int cpos)
{
    COORD scrn;
    scrn.X = cpos;
    scrn.Y = rpos;
    HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOuput, scrn);
}

void printBoard()
{
    system("CLS");
    for (int i = 0; i < ROWS; ++i)
    {
        for (int j = 0; j < COLS; ++j)
        {
            int row_pos = 18 + i * 4;
            int col_pos = 20 + j * 9;
            gotoRowCol(row_pos, col_pos);
            cout << board[i][j];
            if (j < COLS - 1)
            {
                gotoRowCol(row_pos, col_pos + 4);
                cout << "|";
            }
        }
        if (i < ROWS - 1)
        {
            for (int j = 20; j <= 44; ++j)
            {
                gotoRowCol(20 + i * 4, j);
                cout << "-";
            }
        }
    }
}

bool checkWin(char player)
{
    for (int i = 0; i < ROWS; ++i)
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
    for (int i = 0; i < COLS; ++i)
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;

    return false;
}

bool isDraw()
{
    for (int i = 0; i < ROWS; ++i)
        for (int j = 0; j < COLS; ++j)
            if (board[i][j] == ' ')
                return false;
    return true;
}

void makeMove(int choice, char player)
{
    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;
    board[row][col] = player;
}

bool isValidMove(int choice)
{
    if (choice < 1 || choice > 9)
        return false;

    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;
    return board[row][col] == ' ';
}

void playGame()
{
    char currentPlayer = 'X';
    while (true)
    {
        printBoard();
        cout << "\nPlayer " << currentPlayer << "'s turn. Enter a box number (1-9): ";
        int choice;
        cin >> choice;

        if (!isValidMove(choice))
        {
            cout << "Invalid move! Try again.\n";
            continue;
        }

        makeMove(choice, currentPlayer);

        if (checkWin(currentPlayer))
        {
            printBoard();
            cout << "\nPlayer " << currentPlayer << " wins!\n";
            break;
        }

        if (isDraw())
        {
            printBoard();
            cout << "\nThe game is a draw!\n";
            break;
        }
        if (currentPlayer == 'X')
            currentPlayer = 'O';
        else
            currentPlayer = 'X';
    }
}

int main()
{
    playGame();
    return 0;
}


