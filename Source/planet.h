#pragma once
#include "struct.h"


class Planet {
public:
    enum class Owner { NEUTRAL, PLAYER, ENEMY };
    static const int PLANET_MAX = 20; // „M„p„{„ƒ„y„}„p„|„„~„€„u „{„€„|„y„‰„u„ƒ„„„r„€ „„|„p„~„u„„
	static const int PLANET_CENTER = 48; // „Q„p„t„y„…„ƒ „„|„p„~„u„„„
    //static const VectorI2 defaultPos[PLANET_MAX];
    //Planet planets[PLANET_MAX];
    Planet() : x(0), y(0), radius(0), owner(Owner::NEUTRAL), resources(0), groundImage(-1) {} // „D„€„q„p„r„|„u„~ „{„€„~„ƒ„„„‚„…„{„„„€„‚ „„€ „…„}„€„|„‰„p„~„y„
    Planet(float x, float y, float radius, Owner owner, int resources, int image);
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

//private:
    float x, y, radius;
    Owner owner;
    int resources;
    int groundImage;
};

