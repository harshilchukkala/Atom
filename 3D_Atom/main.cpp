#include <raylib.h>
#include <math.h>
#include <vector>

Vector3 SphericaltoCartisian(float r,float theta,float phi) {
    float x = r * cos(phi) * sin(theta);
    float y = r * sin(phi);
    float z = r * cos(phi) * cos(theta);
    return {x,y,z};
}

int main() {
    InitWindow(800,600,"3D Quantum Atom");
    SetTargetFPS(60);

    Camera3D camera = {0};
    camera.position = {25,25,25};
    camera.target = {0,0,0};
    camera.up = {0,1,0};
    camera.fovy = 45.0f;
    camera.projection =CAMERA_PERSPECTIVE;

    float camYaw = 0;
    float camPitch = 0.3f;
    float camDist = 20.0f;

    std::vector<Vector3> points;
    for(int i = 0 ; i < 10000 ; i++) {
        float r = 10 * GetRandomValue(0,100) / 100.0f;
        float theta = 2 * M_PI * GetRandomValue(0,100) / 100.0f;
        float phi = 2 * M_PI * GetRandomValue(0,100) / 100.0f;
        Vector3 point = SphericaltoCartisian(r,theta,phi);
        points.push_back(point);
    }
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        float dist = GetMouseWheelMove();
        camDist += dist * 5 ;

        if(IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            Vector2 change = GetMouseDelta();
            camPitch += change.y * 0.005f;
            camYaw += change.x * -0.005f;
        }

        camera.position = {camDist * cos(camPitch) * sin(camYaw),camDist * sin(camPitch),camDist * cos(camPitch) * cos(camYaw)};

        BeginMode3D(camera);
        DrawLine3D({-10000,0,0}, {10000,0,0}, RED);   
        DrawLine3D({0,-10000,0}, {0,10000,0}, GREEN); 
        DrawLine3D({0,0,-10000}, {0,0,10000}, BLUE);      
        
        EndMode3D();

        for(int i = 0; i < 10000 ; i++)
        {
            DrawPixelV(GetWorldToScreen(points.at(i),camera),SKYBLUE);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}