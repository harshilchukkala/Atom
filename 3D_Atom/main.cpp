#include <raylib.h>
#include <math.h>

int main() {
    InitWindow(800,600,"3D Quantum Atom");
    SetTargetFPS(60);

    Camera3D camera = {0};
    camera.position = {10,10,10};
    camera.target = {0,0,0};
    camera.up = {0,1,0};
    camera.fovy = 45.0f;
    camera.projection =CAMERA_PERSPECTIVE;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(camera);
        DrawLine3D({-1000,0,0}, {1000,0,0}, RED);   
        DrawLine3D({0,-1000,0}, {0,1000,0}, GREEN); 
        DrawLine3D({0,0,-1000}, {0,0,1000}, BLUE);      
        DrawSphere({0,0,0},0.5f,WHITE);

        EndMode3D();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}