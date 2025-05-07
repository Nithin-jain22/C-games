#include <stdio.h>

char board[3][3];
char player = 'X';

void initBoard() {
    for (int i = 0, c = '1'; i < 3; i++)
        for (int j = 0; j < 3; j++, c++)
            board[i][j] = c;
}

void displayBoard() {
    printf("\n");
    for (int i = 0; i < 3; i++) {
        printf(" %c | %c | %c ", board[i][0], board[i][1], board[i][2]);
        if (i < 2) printf("\n---|---|---\n");
    }
    printf("\n");
}

int checkWin() {
    for (int i = 0; i < 3; i++) {
        // Rows & Columns
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player))
            return 1;
    }
    // Diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player))
        return 1;

    return 0;
}

int isDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return 0;
    return 1;
}

void switchPlayer() {
    player = (player == 'X') ? 'O' : 'X';
}

void playGame() {
    int pos;
    while (1) {
        displayBoard();
        printf("Player %c, enter position (1-9): ", player);
        scanf("%d", &pos);

        if (pos < 1 || pos > 9) {
            printf("Invalid input! Try again.\n");
            continue;
        }

        int row = (pos - 1) / 3;
        int col = (pos - 1) % 3;

        if (board[row][col] == 'X' || board[row][col] == 'O') {
            printf("Position already taken! Try again.\n");
            continue;
        }

        board[row][col] = player;

        if (checkWin()) {
            displayBoard();
            printf("Player %c wins!\n", player);
            break;
        }

        if (isDraw()) {
            displayBoard();
            printf("It's a draw!\n");
            break;
        }

        switchPlayer();
    }
}

int main() {
    initBoard();
    playGame();
    return 0;
}
