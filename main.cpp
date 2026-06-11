#include <raylib.h>
#include"Atom.h"
#include <vector>
#include <cmath>

int main() {
    InitWindow(800, 600, "Quantum Atom");
    SetTargetFPS(60);

    std::vector<Atom> Atoms; 

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mouse=GetMousePosition();
            if(IsKeyDown(KEY_H)) {
                Atoms.push_back(Atom(mouse.x,mouse.y,"H",WHITE,30));
                Atoms.back().addshell(120,1);
            }
            if(IsKeyDown(KEY_L)) {
                Atoms.push_back(Atom(mouse.x,mouse.y,"Li",WHITE,30));
                Atoms.back().addshell(120,2);
                Atoms.back().addshell(160,1);
            }
            if(IsKeyDown(KEY_N)) {
                Atoms.push_back(Atom(mouse.x,mouse.y,"Na",WHITE,30));
                Atoms.back().addshell(120,1);
                Atoms.back().addshell(160,8);
                Atoms.back().addshell(200,1);
            }
        }
        for(int i=0;i<Atoms.size();i++) {
            Atoms.at(i).draw();
            Atoms.at(i).update(GetFrameTime());
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}