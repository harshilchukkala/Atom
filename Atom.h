#pragma once
#include <raylib.h>
#include <string>
#include <vector>

struct Electron {
    float angle;
    float speed;
    float orbitRadius;
};

struct OrbitalShell {
    float radius;
    int Electroncount;
    std::vector<Electron> Electrons;
};

class Atom{
    public:

    float x,y;
    float nucleusradius;
    Color nucleuscolor;
    std::string symbol;
    std::vector<OrbitalShell> shells;

    Atom(float x,float y,std::string symbol,Color color,float nucleusradius);
    void addshell(float radius,int Electroncount);
    void update(float dt);
    void draw();
};
