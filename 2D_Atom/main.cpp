#include <raylib.h>
#include"Atom.h"
#include <vector>
#include <string>

int main() {
    InitWindow(800, 600, "2D Bohr Atom");
    SetTargetFPS(60);

    std::vector<Atom> Atoms;
    std::string input = "";
    int selectedelement = 0;
    Vector2 offset = {0,0};

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        if(IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            Vector2 delta = GetMouseDelta();
            offset.x += delta.x;
            offset.y += delta.y;
        }
        for(int key = KEY_ZERO;key <= KEY_NINE;key++) {
            if(IsKeyPressed(key)) {
                input.push_back((char)'0'+(key-KEY_ZERO));
            }
        }
        if(IsKeyPressed(KEY_ENTER) && input.size()!=0) {
            selectedelement=std::stoi(input);
            input="";
        }
        if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && selectedelement!=0) {
            Vector2 mouse=GetMousePosition();
            Atoms.push_back(createatom(mouse.x - offset.x,mouse.y - offset.y,selectedelement));
            selectedelement=0;
        }
        for(int i=0;i<Atoms.size();i++) {
            Atoms.at(i).draw(offset);
            Atoms.at(i).update(GetFrameTime());
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}