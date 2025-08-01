#pragma once

#include "planet.h"
#include "ship.h"
#include "player.h"
#include <vector>



void PlaySceneInit();
void PlaySceneUpdate();
void PlaySceneDraw();
void PlaySceneRelease();

void PlaySceneReset();

void DistanceMeter(int x, int y);
void CalculatePlanetAngles(double planetAngle[]);
void CalculateExtraAngles(double extraAngles[]);
void DrawExtraLines(double extraAngles[]);
void DrawLines(double planetAngle[]);