#pragma once
#include "struct.h"
#include <string>
#include "DxLib.h"

class Planet {
public:
    enum class Owner { NEUTRAL, PLAYER, ENEMY };
    static const int PLANET_MAX = 20; // „M„p„{„ƒ„y„}„p„|„Ž„~„€„u „{„€„|„y„‰„u„ƒ„„„r„€ „„|„p„~„u„„
	static const int PLANET_CENTER = 48; // „Q„p„t„y„…„ƒ „„|„p„~„u„„„
    //static const VectorI2 defaultPos[PLANET_MAX];
    //Planet planets[PLANET_MAX];
    float x, y, radius;
    Owner owner;
    int resources;
    int groundImage;
    //int color;
    int planetId;
    Planet(float x, float y, float radius,int units, Owner owner, int resources, int image, int id);
    Planet() : x(0), y(0), radius(0), units(units), owner(Owner::NEUTRAL), resources(0), groundImage(-1), color(GetColor(128, 128, 128)),planetId(-1) {} // „D„€„q„p„r„|„u„~ „{„€„~„ƒ„„„‚„…„{„„„€„‚ „„€ „…„}„€„|„‰„p„~„y„
    //void Render() const;
    void Init();
    void Update();
    void Draw();
    void Release();
    void Reset();
    void SetOwner(Owner newOwner);
    void CalculatePlanetAngles(double planetAngle[]);
    void CalculateExtraAngles(double extraAngles[]);
    void DrawExtraLines(double extraAngles[]);
    void DrawLines(double planetAngles[]);

    float GetX() const { return x; }
    float GetY() const { return y; }
    Owner GetOwner() const { return owner; }
    float GetRadius() const { return radius; }
    int GetId() const { return planetId; }
    void SetId(int newId) { planetId = newId; }
    //int GetColor(int r, int g, int b) const { return color; }
    int GetColor(int r, int g, int b) const { return color; }
    //-----------------------------------------------------
    //playScene
    void RenderSelection() const;
    bool Contains(int mouseX, int mouseY) const;
    bool TryCapture(int attackingShips, Owner newOwner);

    int GetUnits() const { return units; }
    void AddUnits(int count) { units += count; }
    void RemoveUnits(int count) { units = (units > count) ? (units - count) : 0; }
    //-----------------------------------------------------
//private:
    //float x, y, radius;
    //Owner owner;
    int color;

    //-----------------------------------------------------
    //playScene
    int units;
    //-----------------------------------------------------
    };

