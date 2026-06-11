#include <raylib.h>
#include"Atom.h"
#include <cmath>

int main() {
    InitWindow(800, 600, "Quantum Atom");
    SetTargetFPS(60);

    Atom Hydrogen(400,300,"H",WHITE,50);
    Hydrogen.addshell(120,1);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        Hydrogen.draw();
        Hydrogen.update(GetFrameTime());
        EndDrawing();
    }

    CloseWindow();
    return 0;
}