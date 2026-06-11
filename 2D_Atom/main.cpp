#include <raylib.h>
#include"Atom.h"
#include <vector>
#include <string>

int main() {
    InitWindow(800, 600, "Quantum Atom");
    SetTargetFPS(60);

    std::vector<Atom> Atoms;
    std::string input = "";
    int selectedelement = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        for(int key = KEY_ZERO;key <= KEY_NINE;key++) {
            if(IsKeyPressed(key)) {
                input.push_back((char)'0'+(key-KEY_ZERO));
            }
        }
        if(IsKeyPressed(KEY_ENTER)) {
            selectedelement=std::stoi(input);
            input="";
        }
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && selectedelement!=0) {
            Vector2 mouse=GetMousePosition();
            Atoms.push_back(createatom(mouse.x,mouse.y,selectedelement));
            selectedelement=0;
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