#pragma once
#include "planet.h"

class Ship {
public:
    Ship(float x, float y, Planet* target, Planet::Owner owner, int image);
    void Update();
    void Render() const;
    bool HasReachedTarget() const;
    Planet* GetTargetPlanet() const { return target; }
    Planet::Owner GetOwner() const { return owner; }
private:
    float x, y, speed;
    Planet* target;
    Planet::Owner owner;
    int humanShipImage;
};
