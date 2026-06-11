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

Atom createatom(float x,float y,int Atomicnum) {
    switch (Atomicnum)
    {
    case 1: {
        Atom a(x,y,"H",WHITE,30);
        a.addshell(120,1);
        return a;
    }
    case 2: {
        Atom a(x,y,"He",WHITE,30);
        a.addshell(120,2);
        return a;
    }
    case 3: {
        Atom a(x,y,"Li",WHITE,30);
        a.addshell(120,2);
        a.addshell(160,1);
        return a;
    }
    case 4: {
        Atom a(x,y,"Be",WHITE,30);
        a.addshell(120,2);
        a.addshell(160,2);
        return a;
    }
    case 5: {
        Atom a(x,y,"B",WHITE,30);
        a.addshell(120,2);
        a.addshell(160,3);
        return a;
    }
    case 6: {
        Atom a(x,y,"C",WHITE,30);
        a.addshell(120,2);
        a.addshell(160,4);
        return a;
    }
    case 7: {
        Atom a(x,y,"N",WHITE,30);
        a.addshell(120,2);
        a.addshell(160,5);
        return a;
    }
    case 8: {
        Atom a(x,y,"O",WHITE,30);
        a.addshell(120,2);
        a.addshell(160,6);
        return a;
    }
    case 9: {
        Atom a(x,y,"F",WHITE,30);
        a.addshell(120,2);
        a.addshell(160,7);
        return a;
    }
    case 10: {
        Atom a(x,y,"Ne",WHITE,30);
        a.addshell(120,2);
        a.addshell(160,8);
        return a;
    }
    case 11: {
        Atom a(x,y,"Na",WHITE,30);
        a.addshell(120,2);
        a.addshell(160,8);
        a.addshell(200,1);
        return a;
    }
    case 12: {
        Atom a(x,y,"Mg",WHITE,30);
        a.addshell(120,2);
        a.addshell(160,8);
        a.addshell(200,2);
        return a;
    }
    case 13: {
        Atom a(x,y,"Al",WHITE,30);
        a.addshell(120,2);
        a.addshell(160,8);
        a.addshell(200,3);
        return a;
    }
    case 14: {
        Atom a(x,y,"Si",WHITE,30);
        a.addshell(120,2);
        a.addshell(160,8);
        a.addshell(200,4);
        return a;
    }
    case 15: {
        Atom a(x,y,"P",WHITE,30);
        a.addshell(120,2);
        a.addshell(160,8);
        a.addshell(200,5);
        return a;
    }
    case 16: {
        Atom a(x,y,"S",WHITE,30);
        a.addshell(120,2);
        a.addshell(160,8);
        a.addshell(200,6);
        return a;
    }
    case 17: {
        Atom a(x,y,"Cl",WHITE,30);
        a.addshell(120,2);
        a.addshell(160,8);
        a.addshell(200,7);
        return a;
    }
    case 18: {
        Atom a(x,y,"Ar",WHITE,30);
        a.addshell(120,2);
        a.addshell(160,8);
        a.addshell(200,8);
        return a;
    }
    case 19: {
        Atom a(x,y,"K",WHITE,30);
        a.addshell(120,2);
        a.addshell(160,8);
        a.addshell(200,8);
        a.addshell(240,1);
        return a;
    }
    case 20: {
        Atom a(x,y,"Ca",WHITE,30);
        a.addshell(120,2);
        a.addshell(160,8);
        a.addshell(200,8);
        a.addshell(240,2);
        return a;
    }
    default: {
        Atom a(x,y,"",WHITE,0);
        return a;
    }
    }
}