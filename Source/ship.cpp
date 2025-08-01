#include "ship.h"
#include "math.h"
Ship::Ship(float x, float y, Planet* target, Planet::Owner owner, int image)
    : x(x), y(y), target(target), owner(owner), humanShipImage(image), speed(2.0f) {
}

void Ship::Update() 
{
    //playScene
    if (!target) return;


    //-----------------------------------------------

    // „D„r„y„w„u„~„y„u „{ „ˆ„u„|„y
    float dx = target->GetX() - x;
    float dy = target->GetY() - y;
    float dist = sqrtf(dx * dx + dy * dy);

    if (dist > target->GetRadius()) 
    {
        x += (dx / dist) * speed;
        y += (dy / dist) * speed;
    }
   
}
void Ship::Render() const 
{

    int color;
    switch (owner) 
    {
    case Planet::Owner::PLAYER: color = GetColor(0, 255, 0); break; // „H„u„|„u„~„„z
    case Planet::Owner::ENEMY: color = GetColor(255, 0, 0); break;  // „K„‚„p„ƒ„~„„z
    default: color = GetColor(150, 150, 150); break;                // „R„u„‚„„z
    }

    DrawCircle(x, y, 5, color, TRUE); // „Q„y„ƒ„…„u„} „„‚„€„ƒ„„„€„z „{„‚„…„s „r„}„u„ƒ„„„€ „{„€„‚„p„q„|„‘
}
bool Ship::HasReachedTarget() const 
{
    if (!target) return false;
    float dx = target->GetX() - x;
    float dy = target->GetY() - y;
    return (dx * dx + dy * dy) <= (target->GetRadius() * target->GetRadius());
}