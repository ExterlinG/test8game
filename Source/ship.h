#pragma once
#include "planet.h"

class Ship {
public:
    Ship(float startX, float startY, Planet* target, Planet::Owner owner, int image);
    void Update();
    void Render() const;

private:
    float x, y, speed;
    Planet* target;
    Planet::Owner owner;
    int humanShipImage;
};
