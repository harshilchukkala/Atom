#include "Atom.h"
#include <cmath>
using namespace std;

Atom::Atom(float x,float y,string symbol,Color color,float nucleusradius) {
    this->x=x;
    this->y=y;
    this->symbol=symbol;
    this->nucleuscolor=color;
    this->nucleusradius=nucleusradius;
}

void Atom::addshell(float radius,int Electroncount) {
    OrbitalShell shell;
    shell.radius=radius;
    shell.Electroncount=Electroncount;

    for(int i=0;i<Electroncount;i++) {
        Electron e;
        e.angle=360.0f/Electroncount * i;
        e.speed=120.0f;
        e.orbitRadius=radius;
        shell.Electrons.push_back(e);
    }
    shells.push_back(shell);
}

void Atom::update(float dt) {
    for(auto& shell : shells) {
        for(auto& e : shell.Electrons) {
            e.angle += e.speed * dt;
            if(e.angle>360.0f) e.angle -= 360.0f;
        }
    }
}

void Atom::draw() {
    DrawCircle((int)x,(int)y,nucleusradius,nucleuscolor);
    DrawText(symbol.c_str(),x-MeasureText(symbol.c_str(),nucleusradius)/2,y-nucleusradius/2,nucleusradius,BLACK);
    for(auto& shell : shells) {
        DrawCircleLines((int)x,(int)y,shell.radius,RAYWHITE);
        for(auto& e : shell.Electrons) {
            float rad = e.angle * DEG2RAD;
            float ex = x + e.orbitRadius * cos(rad);
            float ey = y + e.orbitRadius * sin(rad);
            DrawCircle((int)ex,(int)ey,8,SKYBLUE);
            DrawText("e-",ex - MeasureText("e-",16)/2,ey-8,16,PURPLE);
            
        }
    }
}