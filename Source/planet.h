#pragma once

class Planet {
public:
    enum class Owner { NEUTRAL, PLAYER, ENEMY };
	static const int PLANET_MAX = 20; // „M„p„{„ƒ„y„}„p„|„„~„€„u „{„€„|„y„‰„u„ƒ„„„r„€ „„|„p„~„u„„
    Planet() : x(0), y(0), radius(0), owner(Owner::NEUTRAL), resources(0), image(-1) {} // „D„€„q„p„r„|„u„~ „{„€„~„ƒ„„„‚„…„{„„„€„‚ „„€ „…„}„€„|„‰„p„~„y„
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
    float GetX() const { return x; }
    float GetY() const { return y; }
    Owner GetOwner() const { return owner; }

private:
    float x, y, radius;
    Owner owner;
    int resources;
    int image;
};

