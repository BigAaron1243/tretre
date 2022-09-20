#include <stdio.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

int block[7][4][2] = {{{0,0},{0,1},{0,-2},{0,-1}},{{0,0},{1,-1},{1,0},{-1,0}},{{0,0},{-1,1},{-1,0},{1,0}},{{0,0},{1,0},{0,1},{-1,1}},{{0,0},{0,1},{-1,0},{1,1}},{{0,0},{-1,0},{1,0},{0,-1}},{{0,0},{0,1},{1,1},{1,0}}};
// I = 0; J = 1; L = 2; S = 3; Z = 4; T = 5; O = 6


void draw(int* grid) {
    char print_line[21];
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            if (*grid++ > 0) {
                print_line[j * 2] = '[';
                print_line[j * 2 + 1] = ']';
            } else {
                print_line[j * 2] = ' ';
                print_line[j * 2 + 1] = ' ';
            }
             
        }
        //printf("\n");
        printf("%s\n", print_line);
    }
}

void setminos(int* blocks, int* newblocks, int y, int x) {
    for (int i = 0; i < 4; i++) {
        newblocks[i * 2] = blocks[i * 2] + x; 
        newblocks[i * 2 + 1] = blocks[i * 2 + 1] + y; 
    }
}

struct mino {
    int blocks[8];
    int x;
    int y;
};

int x = 5;
int y = 4;
bool newmino = false;

int main() {

    //Initialise main grid
    int grid[20][10];
    int permanentgrid[20][10];
    for (int x = 0; x <20; x++) {
        for (int y = 0; y < 10; y++) {
            grid[x][y] = 0;
            permanentgrid[x][y] = 0;
        }
    }
    //grid[4][4] = 1;
    int activemino[8];
    int relativemino[8];
    setminos(*block[4], &relativemino[0], 0, 0); 
    for (int i = 0; i < 4; i++) {
        //grid[activemino[i * 2]][activemino[i * 2 + 1]] = 4;
        //grid[5][5] = 0;
        printf("y=%d, x=%d\n", relativemino[i*2], relativemino[i*2+1]);
    }
    int sum = 0;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            sum += grid[j][i];
        }
    }
    printf("%d", sum);
    Sleep(1000);
    int timer;
    //Main game loop
    for (;;) {
        //Clear the screen, add small delay beforehand to make blocks less flickery
        Sleep(1);
        system("cls");
        
        if (newmino == true) {
            x = 5;
            y = 0;
            newmino = false;
        }

        int temp = 0;
        //Get user input
        if (kbhit()) {
            int usrin = _getch();
            switch (usrin) {
                case 100: //d
                    for (int i = 0; i < 4; i++) {
                        temp = relativemino[i*2];
                        relativemino[i*2] = relativemino[i*2+1];
                        relativemino[i*2+1] = -1 * temp;
                    }
                    break;
                case 102: //f
                    for (int i = 0; i < 4; i++) {
                        temp = relativemino[i*2];
                        relativemino[i*2] = relativemino[i*2+1];
                        relativemino[i*2+1] = -1 * temp;
                    }
                    break;
                case 32: //spacebar
                    break;
                case 59: //;
                    x--;
                    system("cls");
                    break;
                case 39: //'
                    x++;
                    system("cls");
                    break;
            }
        }
        setminos(relativemino, &activemino[0], x, y);
        for (int i = 0; i < 4; i++) {
            grid[activemino[i * 2]][activemino[i * 2 + 1]] = 1;
            //printf("saoitdothis");
            printf("%d, %d\n", activemino[i*2], activemino[i*2+1]);
        }
        if (timer++ > 4) {
            //YOU STOPPED HERE LAST NIGHT
            for (int i = 0; i < 4; i++) {
                    if (permanentgrid[activemino[i * 2]+1][activemino[i * 2 + 1]] > 0 || activemino[i * 2] > 18) {
                    for (int j = 0; j < 4; j++) {
                        permanentgrid[activemino[j * 2]][activemino[j * 2+1]] = 1;
                    }
                    newmino = true;
                }
            }
            y++;
            for (int x = 0; x <20; x++) {
                for (int y = 0; y < 10; y++) {
                    grid[x][y] = 0;
                }
            }
            timer = 0;
        }
        setminos(relativemino, &activemino[0], x, y);
        for (int x = 0; x <20; x++) {
            for (int y = 0; y < 10; y++) {
                if (permanentgrid[x][y] > 0) {
                    grid[x][y] = 1;
                }
            }
        }
        draw(grid[0]);
        /*char print_line[21];
        int* pls = grid[0];
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 10; j++) {
                //printf("%d ", grid[i][j]);
                printf("%d ", *pls++);
            }
            printf("\n");
        }*/

    }
}
