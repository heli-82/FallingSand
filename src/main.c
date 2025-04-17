#include <math.h>
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

const int GRID_WIDTH = 96;
const int GRID_HEIGHT = 64;
const int SCALE = 5;

void Draw(bool **grid) {
    ClearBackground(BLACK);
    for (size_t y = 0; y < GRID_HEIGHT; y++) {
        for (size_t x = 0; x < GRID_WIDTH; x++) {
            if (grid[y][x]) {
                DrawRectangle(x * SCALE, y * SCALE, SCALE, SCALE, WHITE);
            }
        }
    }
}

int main() {
    bool **grid = malloc(sizeof(bool *) * GRID_HEIGHT);
    for (size_t i = 0; i < GRID_HEIGHT; i++) {
        grid[i] = malloc(sizeof(bool) * GRID_WIDTH);
        for (size_t j = 0; j < GRID_WIDTH; j++) {
            grid[i][j] = 0;
        }
    }

    InitWindow(GRID_WIDTH * SCALE, GRID_HEIGHT * SCALE, "Sand");
    SetTargetFPS(90);

    Vector2 mousepos = (Vector2){.x = 0.0, .y = 0.0};

    while (!WindowShouldClose()) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            mousepos = GetMousePosition();
            printf("x: %.2f, y:%.2f\n", mousepos.x, mousepos.y);
            mousepos.y = mousepos.y >= 0.0 ? mousepos.y : 0.0;
            mousepos.y = roundf(mousepos.y / SCALE) < GRID_HEIGHT - 1
                             ? roundf(mousepos.y / SCALE)
                             : GRID_HEIGHT - 1;
            mousepos.x = mousepos.x >= 0.0 ? mousepos.x : 0.0;
            mousepos.x = roundf(mousepos.x / SCALE) < GRID_WIDTH - 1
                             ? roundf(mousepos.x / SCALE)
                             : GRID_WIDTH - 1;
            printf("x: %.2f, y:%.2f\n", mousepos.x, mousepos.y);

            grid[(int)mousepos.y][(int)mousepos.x] = 1;
        }
        BeginDrawing();
        Draw(grid);
        EndDrawing();
    }

    for (size_t i = 0; i < GRID_HEIGHT; i++) {
        free(grid[i]);
    }
    free(grid);

    return 0;
}