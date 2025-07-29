#include "ship.h"
#include "math.h"
Ship::Ship(float startX, float startY, Planet* target, Planet::Owner owner, int image)
    : x(startX), y(startY), target(target), owner(owner), humanShipImage(image), speed(2.0f) {
}

void Ship::Update() {
    // „D„r„y„w„u„~„y„u „{ „ˆ„u„|„y
    float dx = target->GetX() - x;
    float dy = target->GetY() - y;
    float dist = sqrtf(dx * dx + dy * dy);

    if (dist > 5.0f) {
        x += (dx / dist) * speed;
        y += (dy / dist) * speed;
    }
}