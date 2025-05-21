#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 10

int kbhit(void) {
    struct termios oldt, newt;
    int ch;
    int oldf;
  
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
  
    ch = getchar();
  
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
  
    if(ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }
  
    return 0;
}

void draw(int x, int y, int fx, int fy) {
    system("clear");
    for (int i = 0; i <= HEIGHT; i++) {
        for (int j = 0; j <= WIDTH; j++) {
            if (i == 0 || i == HEIGHT || j == 0 || j == WIDTH)
                printf("#");
            else if (i == y && j == x)
                printf("O");
            else if (i == fy && j == fx)
                printf("F");
            else
                printf(" ");
        }
        printf("\n");
    }
}

int main() {
    int x = WIDTH / 2, y = HEIGHT / 2;
    int fx = rand() % (WIDTH - 2) + 1;
    int fy = rand() % (HEIGHT - 2) + 1;
    int dx = 1, dy = 0;
    char c;

    while (1) {
        draw(x, y, fx, fy);

        if (kbhit()) {
            c = getchar();
            if (c == 'w') { dx = 0; dy = -1; }
            if (c == 's') { dx = 0; dy = 1; }
            if (c == 'a') { dx = -1; dy = 0; }
            if (c == 'd') { dx = 1; dy = 0; }
            if (c == 'q') break;
        }

        x += dx;
        y += dy;

        if (x <= 0 || x >= WIDTH || y <= 0 || y >= HEIGHT) break;

        if (x == fx && y == fy) {
            fx = rand() % (WIDTH - 2) + 1;
            fy = rand() % (HEIGHT - 2) + 1;
        }

        usleep(200000);
    }

    printf("Game Over!\n");
    return 0;
}