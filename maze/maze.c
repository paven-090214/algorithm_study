#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE 5

typedef struct POINT {
	int x;
	int y;
} POINT;

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

POINT stack[SIZE * SIZE];
int top = -1;

int visited[SIZE][SIZE];

int isEmpty() {
    return top == -1;
}

int isFull() {
    return top == (SIZE * SIZE - 1);
}

void pushStack(POINT p) {
    if (isFull()) {
        printf("stack is full");
        return;
    }
    top++;
    stack[top] = p;
}

POINT popStack() {
    POINT err = { -1, -1 };
    if (isEmpty()) {
        return err;
    }
    return stack[top--];
}

POINT current() {
    return stack[top];
}

int isValid(int maze[][SIZE], int x, int y) {
    return 0 <= x && x < SIZE && 0 <= y && y < SIZE &&
        maze[x][y] == 0 && !visited[x][y];
}

int main() {
    top = -1;

    int path[25];

    int maze[SIZE][SIZE] = {
        {0, 0, 0, 0, 0},
        {1, 0, 1, 1, 1},
        {1, 0, 1, 1, 1},
        {1, 0, 1, 1, 1},
        {1, 0, 0, 0, 0} 
    };

    POINT start = { 0, 0 };
    POINT finish = { SIZE - 1, SIZE - 1 };
    pushStack(start);
    visited[start.x][start.y];
    
    while (!isEmpty()) {
        POINT cur = current();//current point

        if (cur.x == finish.x && cur.y == finish.y) {
            break;
        }
        int move = 0;
        for (int i = 0; i < 4; i++) {
            int nx = cur.x + dx[i];
            int ny = cur.y + dy[i];
            if (isValid(maze, nx, ny)) {
                visited[nx][ny] = 1;
                POINT next = { nx, ny };
                pushStack(next);
                printf("current point : %d %d -> \n", cur.x, cur.y);
                move++;
                break;
            }
        }
        if (!move) {
            POINT dead = popStack();
            printf("dead stage : %d, %d <- \n", dead.x, dead.y);
        }
    }
    return 0;
}
