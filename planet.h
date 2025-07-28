#pragma once
#include "DxLib.h"

class Planet {
public:
    enum class Owner { NEUTRAL, PLAYER, ENEMY };

    Planet(float x, float y, float radius, Owner owner, int resources, int image);
    void Render() const;
    void Init();
    void SetOwner(Owner newOwner);
    void CalculatePlanetAngles(double planetAngle[]);
    void CalculateExtraAngles(double extraAngles[]);
    void DrawExtraLines(double extraAngles[]);

    float GetX() const { return x; }
    float GetY() const { return y; }
    Owner GetOwner() const { return owner; }

private:
    float x, y, radius;
    Owner owner;
    int resources;
    int image;
};