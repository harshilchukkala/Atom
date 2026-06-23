#include <raylib.h>
#include <math.h>
#include <vector>

float fac(int n) {
    if(n==0 || n==1) return 1.0f;
    else return n * fac(n-1);
}

float lang(int p,int q,float x) {
    if(p==0) return 1.0f;
    else if(p==1) return 1 + q - x;
    else return ((2*p-1+q-x) * lang(p-1,q,x) - (p-1+q) * lang(p-2,q,x)) / p;
}

float R(int n, int l, float r) {
    float a0 = 1.0f;
    float rho = 2.0f * r / (n*a0);
    float firstterm = pow(2.0f/(n*a0), 3);
    float secondterm = fac(n-l-1) / (2.0f * n * fac(n+l));
    float prefactor = sqrt(firstterm * secondterm);
    return prefactor * exp(-rho/2) * pow(rho, l) * lang(n-l-1, 2*l+1, rho);
}

float legendre(int l, int m, float x) {
    if(l==0) return 1.0f;
    if(l==1 && m==0) return x;
    if(l==1 && m==1) return -sqrt(1-x*x);
    if(l==m) return -(2*l-1) * sqrt(1-x*x) * legendre(l-1,l-1,x);
    if(l==m+1) return x*(2*l-1) * legendre(l-1,m,x);
    return ((2*l-1)*x*legendre(l-1,m,x) - (l+m-1)*legendre(l-2,m,x)) / (l-m);
}

float Y(int l, int m, float theta, float phi) {
    float norm = sqrt((2*l+1)/(4.0f*M_PI) * fac(l-abs(m))/(float)fac(l+abs(m)));
    if(m > 0) return sqrt(2.0f) * norm * legendre(l, m, sin(phi)) * cos(m*theta);
    if(m < 0) return sqrt(2.0f) * norm * legendre(l, -m, sin(phi)) * sin(-m*theta);
    return norm * legendre(l, 0, sin(phi));
}

Vector3 SphericaltoCartisian(float r, float theta, float phi) {
    float x = r * cos(phi) * sin(theta);
    float z = r * sin(phi);
    float y = r * cos(phi) * cos(theta);
    return {x, y, z};
}

Vector3 Getpoint(int n,int l,int m,float rad) {
    while(1) {
        float r = rad * GetRandomValue(0,1000) / 1000.0f;
        float theta = 2 * M_PI * GetRandomValue(0,1000) / 1000.0f;
        float phi = 2 * M_PI * GetRandomValue(0,1000) / 1000.0f;

        float p = R(n,l,r)*R(n,l,r)*Y(l,m,theta,phi)*Y(l,m,theta,phi);
        float num = GetRandomValue(0,1000) / 1000.0f;

        if(num < p * 100000) {
            Vector3 point = SphericaltoCartisian(r,theta,phi);
            return point;
        }
    }
}

int main() {

    int NO_OF_POINTS = 100000;
    int n = 3;
    int l = 2;
    int m = 1;
    float rad = 50;

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
    for(int i = 0 ; i < NO_OF_POINTS ; i++) {
        Vector3 point = Getpoint(n,l,m,rad);
        points.push_back(point);
    }

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        float dist = GetMouseWheelMove();
        camDist += dist * 3;

        if(IsMouseButtonDown(MOUSE_RIGHT_BUTTON)) {
            Vector2 change = GetMouseDelta();
            camPitch += change.y * 0.01f;
            camYaw += change.x * -0.01f;
        }

        camera.position = {camDist * cos(camPitch) * sin(camYaw),camDist * sin(camPitch),camDist * cos(camPitch) * cos(camYaw)};

        BeginMode3D(camera);
        DrawLine3D({-10000,0,0}, {10000,0,0}, RED);   
        DrawLine3D({0,-10000,0}, {0,10000,0}, GREEN); 
        DrawLine3D({0,0,-10000}, {0,0,10000}, BLUE);      
        
        EndMode3D();

        for(int i = 0; i < NO_OF_POINTS ; i++)
        {
            DrawPixelV(GetWorldToScreen(points.at(i),camera),SKYBLUE);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}