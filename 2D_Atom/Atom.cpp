#include "Atom.h"
#include <cmath>

const AtomData Elements[] = {
    {"H",  {1}},
    {"He", {2}},
    {"Li", {2,1}},
    {"Be", {2,2}},
    {"B",  {2,3}},
    {"C",  {2,4}},
    {"N",  {2,5}},
    {"O",  {2,6}},
    {"F",  {2,7}},
    {"Ne", {2,8}},
    {"Na", {2,8,1}},
    {"Mg", {2,8,2}},
    {"Al", {2,8,3}},
    {"Si", {2,8,4}},
    {"P",  {2,8,5}},
    {"S",  {2,8,6}},
    {"Cl", {2,8,7}},
    {"Ar", {2,8,8}},
    {"K",  {2,8,8,1}},
    {"Ca", {2,8,8,2}}
};


Atom::Atom(float x,float y,std::string symbol,Color color,float nucleusradius) {
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

Atom createatom(float x,float y,int Atomicnum) {
    Atom newatom(x,y,Elements[Atomicnum-1].symbol,WHITE,30);
    float radius=120;
    for(int count : Elements[Atomicnum-1].shellse) {
        newatom.addshell(radius,count);
        radius += 40;
    }
    return newatom;
}