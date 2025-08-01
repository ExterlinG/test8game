#pragma once
#include "planet.h"
#include "ship.h"
#include <vector>


class Player {
public:
    void Initialize();
    void Update(std::vector<Planet>& planets/*, std::vector<Ship>& ships*/);
    void SendShips(Planet& from, Planet& to, std::vector<Ship>& ships);
private:
    int selectedPlanetId = -1;
};

void PlayerInit();
void PlayerUpdate();
void PlayerDraw();
void PlayerRelease();

void PlayerReset();

bool PlayerIsDead();