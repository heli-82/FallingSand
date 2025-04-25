#include <math.h>
#include <raylib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

const int GRID_WIDTH = 96;
const int GRID_HEIGHT = 64;
const int SCALE = 6;

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

void process_grid(bool **grid) {
    for (int i = GRID_HEIGHT - 2; i >= 0; i--) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            if (!grid[i + 1][j] && grid[i][j]) {
                grid[i + 1][j] = 1;
                grid[i][j] = 0;
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
    SetTargetFPS(45);

    Vector2 mousepos = (Vector2){.x = 0.0, .y = 0.0};
    while (!WindowShouldClose()) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            mousepos = GetMousePosition();

            mousepos.y = mousepos.y >= 0.0 ? mousepos.y : 0.0;
            mousepos.y = roundf(mousepos.y / SCALE) < GRID_HEIGHT - 1
                             ? roundf(mousepos.y / SCALE)
                             : GRID_HEIGHT - 1;
            mousepos.x = mousepos.x >= 0.0 ? mousepos.x : 0.0;
            mousepos.x = roundf(mousepos.x / SCALE) < GRID_WIDTH - 1
                             ? roundf(mousepos.x / SCALE)
                             : GRID_WIDTH - 1;


            grid[(int)mousepos.y][(int)mousepos.x] = 1;
        }

        if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            mousepos = GetMousePosition();

            mousepos.y = mousepos.y >= 0.0 ? mousepos.y : 0.0;
            mousepos.y = roundf(mousepos.y / SCALE) < GRID_HEIGHT - 1
                             ? roundf(mousepos.y / SCALE)
                             : GRID_HEIGHT - 1;
            mousepos.x = mousepos.x >= 0.0 ? mousepos.x : 0.0;
            mousepos.x = roundf(mousepos.x / SCALE) < GRID_WIDTH - 1
                             ? roundf(mousepos.x / SCALE)
                             : GRID_WIDTH - 1;

            grid[(int)mousepos.y][(int)mousepos.x] = 0;
        }

        process_grid(grid) ;

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
