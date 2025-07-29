#include <DxLib.h>
#include <assert.h>
#include "config.h"
#include "struct.h"
#include "player.h"


namespace
{
	static const int COLLISION_SIZE = 36;
	int humanShipImage = -1;
	Vector2 pos;		//planet���M�����̍��W
	VectorI2 cell;		//planet�̉摜�̃A�j���[�V�������W

	bool xFlip;			//player�̌���
	bool dead;			//player ����ł��邩�ۂ�

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
void Player::Update(std::vector<Planet>& planets, std::vector<Ship>& ships) {
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		int mouseX, mouseY;
		GetMousePoint(&mouseX, &mouseY);

		for (auto& planet : planets) {
			// �P�����r�u�����u�} ���p�����������~�y�u �� �����v�����} ���p�t�y�����p
			float dx = planet.GetX() - mouseX;
			float dy = planet.GetY() - mouseY;
			float dist = sqrtf(dx * dx + dy * dy);

			if (dist <= planet.GetRadius()) {
				selectedPlanetId = planet.GetId();
				printf("�B���q���p�~�p ���|�p�~�u���p ID: %d (�Q�p�t�y����: %.1f)\n",
					selectedPlanetId, planet.GetRadius());
				break;
			}
		}
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
}