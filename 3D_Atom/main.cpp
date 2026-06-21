#include <raylib.h>
#include <math.h>
#include <vector>

int main() {
    InitWindow(800,600,"3D Quantum Atom");
    SetTargetFPS(60);

    Camera3D camera = {0};
    camera.position = {10,10,10};
    camera.target = {0,0,0};
    camera.up = {0,1,0};
    camera.fovy = 45.0f;
    camera.projection =CAMERA_PERSPECTIVE;

    float Yaw = 0;
    float Pitch = 0.3f;
    float Dist = 20.0f;

    std::vector<Vector3> points;
    for(int i=0;i<10000;i++) {
        float x,y,z,r = 5;
        x = GetRandomValue(-r,r);
        y = GetRandomValue(-r,r);
        z = GetRandomValue(-r,r);
        points.push_back({x,y,z});
    }
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        float dist = GetMouseWheelMove();
        Dist += dist * 5 ;

        if(IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            Vector2 change = GetMouseDelta();
            Pitch += change.y * 0.005f;
            Yaw += change.x * -0.005f;
        }

        camera.position = {Dist * cos(Pitch) * sin(Yaw),Dist * sin(Pitch),Dist * cos(Pitch) * cos(Yaw)};

        BeginMode3D(camera);
        DrawLine3D({-1000,0,0}, {1000,0,0}, RED);   
        DrawLine3D({0,-1000,0}, {0,1000,0}, GREEN); 
        DrawLine3D({0,0,-1000}, {0,0,1000}, BLUE);      
        DrawSphere({0,0,0},0.5f,WHITE);
        
        for(int i = 0; i < 10000;i++)
        { 
            DrawPoint3D(points.at(i),SKYBLUE);
        }
        EndMode3D();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}