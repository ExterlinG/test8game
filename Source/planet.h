#pragma once

class Planet {
public:
    enum class Owner { NEUTRAL, PLAYER, ENEMY };

    Planet() : x(0), y(0), radius(0), owner(Owner::NEUTRAL), resources(0), image(-1) {} // ÑDÑÄÑqÑpÑrÑ|ÑuÑ~ Ñ{ÑÄÑ~ÑÉÑÑÑÇÑÖÑ{ÑÑÑÄÑÇ ÑÅÑÄ ÑÖÑ}ÑÄÑ|ÑâÑpÑ~ÑyÑê
    Planet(float x, float y, float radius, Owner owner, int resources, int image);
    void Render() const;
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