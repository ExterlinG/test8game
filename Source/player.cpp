#include <DxLib.h>
#include <assert.h>
#include "config.h"
#include "struct.h"
#include "player.h"
#include "math.h"

namespace
{

	static const int COLLISION_SIZE = 36;
	int humanShipImage = -1;
	Vector2 pos;		//planetƒƒMƒƒƒ“‚ÌÀ•W
	VectorI2 cell;		//planet‚Ì‰æ‘œ‚ÌƒAƒjƒ[ƒVƒ‡ƒ“À•W

	bool xFlip;			//player‚ÌŒü‚«
	bool dead;			//player €‚ñ‚Å‚¢‚é‚©”Û‚©

	enum class PlayerState {
		NO_STATE = 0,
		STAY,
		RIGHT,
		LEFT,
		DEAD,
	};
	PlayerState state;
}
void Collision();
void Move();
void DeadFall();
void PlayerInit()
{
	if (humanShipImage < 0) {
		humanShipImage = LoadGraph("data\\texture\\humanShip\\battlecruiser.png");
		assert(humanShipImage >= 0);
	}
	PlayerReset();
}
//--------------------------------------------------------------------------------
//playScene
void Player::Update(std::vector<Planet>& planets/*, std::vector<Ship>& ships*/) {
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		int mouseX, mouseY;
		GetMousePoint(&mouseX, &mouseY);

		for (auto& planet : planets) {
			// „P„‚„€„r„u„‚„‘„u„} „‚„p„ƒ„ƒ„„„€„‘„~„y„u „ƒ „…„‰„v„„„€„} „‚„p„t„y„…„ƒ„p
			float dx = planet.GetX() - mouseX;
			float dy = planet.GetY() - mouseY;
			float dist = sqrtf(dx * dx + dy * dy);

			if (dist <= planet.GetRadius()) {
				selectedPlanetId = planet.GetId();
				printf("„B„„q„‚„p„~„p „„|„p„~„u„„„p ID: %d („Q„p„t„y„…„ƒ: %.1f)\n",
					selectedPlanetId, planet.GetRadius());
				break;
			}
		}
	}
}

void Player::SendShips(Planet& from, Planet& to, std::vector<Ship>& ships) 
{
	if (from.GetOwner() == Planet::Owner::PLAYER && from.GetUnits() > 0) 
	{
		int shipsToSend = from.GetUnits() / 2;
		if (shipsToSend < 1) shipsToSend = 1;

		for (int i = 0; i < shipsToSend; ++i) 
		{
			float angle = atan2(to.GetY() - from.GetY(), to.GetX() - from.GetX());
			float offset = (rand() % 20 - 10) * 0.1f;
			float spawnX = from.GetX() + cos(angle + offset) * from.GetRadius();
			float spawnY = from.GetY() + sin(angle + offset) * from.GetRadius();

			ships.emplace_back(spawnX, spawnY, &to, Planet::Owner::PLAYER);
		}
		from.RemoveUnits(shipsToSend);
	}
}

//--------------------------------------------------------------------------------

void PlayerReset()
{
	pos.x = 300.0f;
	
	cell.x = 0;
	cell.y = 0;


	dead = false;

	state = PlayerState::STAY;
	//walkCounter = 0;
	//deadCounter = 0;

	xFlip = false;
}

void PlayerUpdate();
void PlayerDraw()
{
	DrawRectGraph((int)pos.x, (int)pos.y, cell.x * 80, cell.y * 80, 96, 112, humanShipImage, true, xFlip);
}
void PlayerRelease()
{
	if (humanShipImage > 0) {
		DeleteGraph(humanShipImage);
		humanShipImage = -1;
	}
	//ships.clear();
	//planets.clear();
}