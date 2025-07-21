#include "playScene.h"
#include <DxLib.h>
#include <assert.h>
#include "player.h"
#include "app.h"
#include "struct.h"
#include "math.h"


namespace {
	enum class PlayStatus {
		BEFORE_PLAY,
		IN_PLAY,
		AFTER_PLAY,
	};
	PlayStatus status;

	int galaxy = -1;		//gameの背景画像のハンドル
	int groundImage = -1;	//地面の画像ハンドル
	int lines = -1;

	int startCounter;	//ゲームの始まるときのカウンター
	int deadCounter;		//死んだ時のカウンター

	int distanceImage = -1;	//進んだ距離を表す画像
	int playTime;	//進んだ距離を表すカウンター

	int playSound = -1;	//スタートの音ハンドル
	int walkCounter;

	int lineWalkCounter;
	VectorI2 planet;

	VectorI2 linePos;
	VectorI2 lineToPlanet;
	int pattern;

	static const float planet_center = 48.0;



	double planetAngle = 1.57f;
	//double enemyScale = 0.5f;

	double enemyPosX = 848.0f;	//エネミーの座標
	double enemyPosY = 96.0f;


	//debug
	int color;
	static const bool DEBUG_FONT = true;
};

void PlaySceneInit()
{
	if (galaxy < 0) {
		galaxy = LoadGraph("data\\texture\\galaxy\\galaxy1.png");
		assert(galaxy >= 0);
	}
	if (lines < 0) {
		lines = LoadGraph("data\\texture\\lines\\mylines1.png");
		assert(lines >= 0);
	}
	if (groundImage < 0) {
		groundImage = LoadGraph("data\\texture\\planet\\planet.png");
		assert(groundImage >= 0);
	}
	if (distanceImage < 0) {
		distanceImage = LoadGraph("data\\texture\\ui\\num02.png");
		assert(distanceImage >= 0);
	}
	if (playSound < 0) {
		playSound = LoadSoundMem("data\\sound\\playSound\\playSound.wav");
		assert(playSound >= 0);
	}
	
	PlayerInit();
	walkCounter= 0;
	pattern = 0;
	


	//debug
	color = GetColor(255, 255, 255);

}
void PlaySceneUpdate()
{
	
	planet.x = (walkCounter / 6)% 77;

	walkCounter++;
	lineWalkCounter++;
	linePos.x = (lineWalkCounter / 10) % 6;
	
	//if (lineWalkCounter > 60)
	//{
	//	lineToPlanet.x += 2;
	//	lineWalkCounter = 0;
	//	lineToPlanet.x - ;
	//}
		//目標座標（プレイヤー）からエネミーの座標をを引いてベクトルdを求める(dx,dy)
	double dx =737.0-(enemyPosX+48);
	double dy =176.0-(enemyPosY+48);

	planetAngle = atan2(dy, dx);

	//Angleと速度を足して座標を変える
	//enemyPosX = cos(planetAngle);
	//enemyPosY = sin(planetAngle);
	
}
void PlaySceneDraw()
{
	

	//DrawRotaGraph(500, 500,1.0,45,lines,false, false);
	DrawGraph(0, 0, galaxy, true);
	DistanceMeter(170, 30);

	DrawRectRotaGraph2(848 + 48, 96 + 48, linePos.x * 16, 112, 80, 16, -48, 0, 1, planetAngle, lines, true, false);//lines rotated

	DrawRectGraph(960,476, planet.x *96, 0, 96, 96, groundImage, true, false); //middle
	DrawRectGraph(960, 336, planet.x * 96, 0, 96, 96, groundImage, true, false); //grey
	DrawRectGraph(785, 352, planet.x * 96, 0, 96, 96, groundImage, true, false); //grey
	DrawRectGraph(655, 464, planet.x * 96, 0, 96, 96, groundImage, true, false); //grey
	DrawRectGraph(624, 640, planet.x * 96, 0, 96, 96, groundImage, true, false); //grey
	DrawRectGraph(704, 800, planet.x * 96, 0, 96, 96, groundImage, true, false); //grey
	DrawRectGraph(848.5, 911, planet.x * 96, 0, 96, 96, groundImage, true, false); //blue

	DrawRectGraph(848, 560, planet.x * 96, 0, 96, 96, groundImage, true, false); //grey
	DrawRectGraph(944, 704, planet.x * 96, 0, 96, 96, groundImage, true, false); //grey
	DrawRectGraph(1104, 768, planet.x * 96, 0, 96, 96, groundImage, true, false); //grey
	DrawRectGraph(1280, 720, planet.x * 96, 0, 96, 96, groundImage, true, false); //grey
	DrawRectGraph(1408, 592, planet.x * 96, 0, 96, 96, groundImage, true, false); //grey
	DrawRectGraph(1456, 428, planet.x * 96, 0, 96, 96, groundImage, true, false); //yelloy

	DrawRectGraph(1096, 509, planet.x * 96, 0, 96, 96, groundImage, true, false); //grey
	DrawRectGraph(1192, 368, planet.x * 96, 0, 96, 96, groundImage, true, false); //grey
	DrawRectGraph(1136, 224, planet.x * 96, 0, 96, 96, groundImage, true, false); //grey
	DrawRectGraph(1008, 128, planet.x * 96, 0, 96, 96, groundImage, true, false); //grey
	DrawRectGraph(848, 96, planet.x * 96, 0, 96, 96, groundImage, true, false); //grey
	DrawRectGraph(689, 128, planet.x * 96, 0, 96, 96, groundImage, true, false); //red


	//DrawRectGraph(689, 128, linePos.x*16, 112, 80, 16, lines, true, false); //lines
	//DrawRotaGraph2(848, 128, linePos.x*16, 112, 1, planetAngle, lines, true, false);
	//DrawRectRotaGraph(enemyPosX, enemyPosY, linePos.x*16, 112,80,16, 1, planetAngle, lines, true, false);//lines rotated
	//DrawRectRotaGraph2(848+48, 96+48, linePos.x * 16, 112, 80, 16, 0, 0, 1, planetAngle, lines, true, false);//lines rotated
	PlayerDraw();
	

	if (DEBUG_FONT) {
		DrawFormatString(20, 30, color, "EnemyStatus");
		DrawFormatString(20, 50, color, "PosX %f, PosY %f ", enemyPosX, enemyPosY);

		//Angleは角度ではなく、ラジアン（1.57＝90度）で表現される
		//75行目の中身
		DrawFormatString(20, 70, color, "Angle %f ", planetAngle);

		//X座標とY座標への移動量
		//78行目、79行目の中身
		DrawFormatString(20, 120, color, "XMove %f ", cos(planetAngle));
		DrawFormatString(20, 140, color, "YMove %f ", sin(planetAngle));
	}
}
void PlaySceneRelease()
{
	PlayerRelease();

	if (playSound > 0) {
		DeleteSoundMem(playSound);
		playSound = -1;
	}
	if (groundImage > 0) {
		DeleteGraph(groundImage);
		groundImage = -1;
	}
	if (galaxy > 0) {
		DeleteGraph(galaxy);
		galaxy = -1;
	}
	if (lines > 0) {
		DeleteGraph(lines);
		lines = -1;
	}
	if (distanceImage > 0) {
		DeleteGraph(distanceImage);
		distanceImage = -1;
	}
}

void PlaySceneReset()
{
	status = PlayStatus::BEFORE_PLAY;
	playTime = 0;
	startCounter = 0;
	deadCounter = 0;
	PlaySoundMem(playSound, DX_PLAYTYPE_BACK);
	PlayerReset();
}

void DistanceMeter(int x, int y) {
	int meter = playTime / 5;
	int copy = meter;
	int dig = 0;
	do {
		DrawRectGraph(x - (32 * dig), y, copy % 10 * 32, 0, 32, 64, distanceImage, true, false);
		copy = copy / 10;
		dig++;
	} while (copy > 0);
}