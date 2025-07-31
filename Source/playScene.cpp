#include "playScene.h"
#include <DxLib.h>
#include <assert.h>
#include "player.h"
#include "app.h"
#include "struct.h"
#include "math.h"
#include <vector>
#include "planet.h"

static const float PLANET_CENTER = 48.0;

namespace {
	Planet planetFunction;
	enum class PlayStatus {
		BEFORE_PLAY,
		IN_PLAY,
		AFTER_PLAY,
	};
	PlayStatus status;
	static const int PLANET_MAX = 19;
	//static const int planet_size = PLANET_MAX; 
	VectorI2 planet[PLANET_MAX];
	//extern Planet planets[PLANET_MAX];
	//extern VectorI2 defaultPos[PLANET_MAX];
	//extern VectorI2 planet[];



	const VectorI2 defaultPos[PLANET_MAX] = {
		{689,128},{848, 96},{1008, 128},
		{1136, 224},{1192, 368},{1096, 509},
		{1456, 428},{1408, 592},{1280, 720},
		{1104, 768},{944, 704},{848, 560},
		{848.5, 911},{704, 800},{624, 640},
		{655, 464},{785, 352},{960, 336},{960,476}
	};




	int galaxy = -1;		//gameÇÃîwåiâÊëúÇÃÉnÉìÉhÉã
	int groundImage = -1;	//ínñ ÇÃâÊëúÉnÉìÉhÉã
	int lines = -1;

	int startCounter;	//ÉQÅ[ÉÄÇÃénÇ‹ÇÈÇ∆Ç´ÇÃÉJÉEÉìÉ^Å[
	int deadCounter;		//éÄÇÒÇæéûÇÃÉJÉEÉìÉ^Å[

	int distanceImage = -1;	//êiÇÒÇæãóó£Çï\Ç∑âÊëú
	int playTime;	//êiÇÒÇæãóó£Çï\Ç∑ÉJÉEÉìÉ^Å[

	int playSound = -1;	//ÉXÉ^Å[ÉgÇÃâπÉnÉìÉhÉã
	int walkCounter;
	//static const int PLANET_MAX = 20;
	int lineWalkCounter;
	//----------------------------------------------


	//VectorI2 planet[] = { {689,128},{848, 96},{1008, 128},
	//						{1136, 224},{1192, 368},{1096, 509},
	//						{1456, 428},{1408, 592},{1280, 720},
	//						{1104, 768},{944, 704},{848, 560},
	//						{848.5, 911},{704, 800},{624, 640},
	//						{655, 464},{785, 352},{960, 336},{960,476} };
	//const int planet_size = sizeof(planet) / sizeof(planet[0]);
	////----------------------------------------------
	//

	VectorI2 line[] = { {689,128},{848, 96},{1008, 128},
						{1136, 224},{1192, 368},{1096, 509},
						{1456, 428},{1408, 592},{1280, 720},
						{1104, 768},{944, 704},{848, 560},
						{848.5, 911},{704, 800},{624, 640},
						{655, 464},{785, 352},{960, 336},{960,476} };
	const int line_size = sizeof(line) / sizeof(line[0]);

	//----------------------------------------------
	const std::pair<int, int> extraConnections[] = {
		{3, 17}, {4, 17}, {5, 18}, {9, 5},
		{10, 5}, {5, 11}, {11, 17}, {16, 11},
		{18, 11}, {17, 5},{15, 11}
	};



	//----------------------------------------------
	VectorI2 lineToPlanet;

	int patternLine;
	//int patternPlanet;
	//----------------------------------------------
	//VectorI2 lineAngle[];
	//double dx;
	//double dy;


	//static const int planet_size = PLANET_MAX;
	double planetAngle[line_size];


	double extraAngles[11];
	//double planetAngle = 1.57f;
	//double enemyScale = 0.5f;

	//double enemyPosX = 848.0f;	//ÉGÉlÉ~Å[ÇÃç¿ïW
	//double enemyPosY = 96.0f;


	//debug
	int color;
	static const bool DEBUG_FONT = true;
};
Planet planets[PLANET_MAX] =
{

		Planet(689,128, PLANET_CENTER, Planet::Owner::PLAYER, 200, -1,-1),
		Planet(848, 96, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
		Planet(1008, 128, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
		Planet(1136, 224, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
		Planet(1192, 368, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
		Planet(1096, 509, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
		Planet(1456, 428, PLANET_CENTER, Planet::Owner::ENEMY, 200, -1,-1),
		Planet(1408, 592, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
		Planet(1280, 720, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
		Planet(1104, 768, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
		Planet(944, 704, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
		Planet(848, 560, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
		Planet(848.5, 911, PLANET_CENTER, Planet::Owner::ENEMY, 200, -1,-1),
		Planet(704, 800, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
		Planet(624, 640, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
		Planet(655, 464, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
		Planet(785, 352, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
		Planet(960, 336, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),
		Planet(960,476, PLANET_CENTER, Planet::Owner::NEUTRAL, 200, -1,-1),


};


void PlaySceneInit()
{

	if (galaxy < 0) {
		galaxy = LoadGraph("data\\texture\\galaxy\\galaxy1.png");
		assert(galaxy >= 0);
	}

	if (lines < 0) {
		lines = LoadGraph("data\\texture\\lines\\mylines2.png");
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

	//Planet id
	for (int i = 0; i < PLANET_MAX; i++)
	{
		planets[i].SetId(i);  // ÑPÑÇÑyÑÉÑrÑpÑyÑrÑpÑuÑ} ÑÖÑ~ÑyÑ{ÑpÑ|ÑéÑ~ÑçÑu ID
		
	}

	//planetFunction.CalculatePlanetAngles(planetAngle);
	//planetFunction.CalculateExtraAngles(extraAngles);
	PlayerInit();
	walkCounter = 0;
	patternLine = 0;
	//patternPlanet = 0;
	//for (int i = 0; i < PLANET_MAX; i++) {
	//	planet[i] = defaultPos[i];
	//}
		//angle
	CalculatePlanetAngles(planetAngle);

	//extra angle
	CalculateExtraAngles(extraAngles);
	for (int i = 0; i < PLANET_MAX; i++)
	{
		planets[i] = Planet(
			defaultPos[i].x,
			defaultPos[i].y,
			PLANET_CENTER,
			planets[i].owner,
			200,
			groundImage,
			
			planets[i].planetId
		);
	}

	//planets[0].SetOwner(Planet::Owner::PLAYER);

	//debug
	//color = GetColor(255, 255, 255);

}
void PlaySceneUpdate()
{
	planetFunction.Update();
	//patternPlanet = (walkCounter / 6)% 77;

	//walkCounter++;
	lineWalkCounter++;
	patternLine = (lineWalkCounter / 10) % 10;

	//if (lineWalkCounter > 60)
	//{
	//	lineToPlanet.x += 2;
	//	lineWalkCounter = 0;
	//	lineToPlanet.x - ;
	//}
		//ñ⁄ïWç¿ïWÅiÉvÉåÉCÉÑÅ[ÅjÇ©ÇÁÉGÉlÉ~Å[ÇÃç¿ïWÇÇà¯Ç¢ÇƒÉxÉNÉgÉãdÇãÅÇﬂÇÈ(dx,dy)





	//for (int i = 0; i < planet_size; i++)
	//{
	//	double dx[i] = ((planet[i].x + PLANET_CENTER) - (planet[i + 1].x + PLANET_CENTER));
	//	double dy[i] = ((planet[i].y + PLANET_CENTER) - (planet[i + 1].y + PLANET_CENTER));
	//	planetAngle[i] = atan2(dy[i], dx[i]);
	//}

	//double dx =-(enemyPosX+48);
	//double dy =176.0-(enemyPosY+48);

	//planetAngle = atan2(dy, dx);

	//AngleÇ∆ë¨ìxÇë´ÇµÇƒç¿ïWÇïœÇ¶ÇÈ
	//enemyPosX = cos(planetAngle);
	//enemyPosY = sin(planetAngle);

}

void PlaySceneDraw()
{
	//for (int i = 0; i < PLANET_MAX; i++) {
	//	planetFunction.Draw(); // ÑOÑÑÑÇÑyÑÉÑÄÑrÑçÑrÑpÑuÑ} ÑÅÑ|ÑpÑ~ÑuÑÑÑç ÑyÑx planet.cpp
	//}

	//DrawRotaGraph(500, 500,1.0,45,lines,false, false);
	DrawGraph(0, 0, galaxy, true);
	//planetFunction.SetOwner(Planet::Owner::PLAYER);
	DistanceMeter(170, 30);
	//lines
	DrawLines(planetAngle);
	//more center lines ÑtÑÄÑÅÑÄÑ|Ñ~ÑyÑÑÑuÑ|ÑéÑ~ÑçÑu Ñ|ÑyÑ~ÑyÑy.
	DrawExtraLines(extraAngles);
	//planetFunction.Draw();
	printf("ÑOÑÑÑ|ÑpÑtÑ{Ñp:\n");
	for (int i = 0; i < PLANET_MAX; i++)
	{
		
		if (i == 0)
		{
			
			planets[i].Draw();
			planets[i].SetOwner(Planet::Owner::PLAYER);
			DrawFormatString(20, 50, 0xFFFFFF, "planet owner = %d", planets[i].owner);
		}
		else if (i == 6)
		{
			
			planets[i].Draw();
			planets[i].SetOwner(Planet::Owner::ENEMY);
			DrawFormatString(20, 70, 0xFFFFFF, "planet owner = %d", planets[i].owner);
		}
		else
		{
			
			planets[i].Draw();
			planets[i].SetOwner(Planet::Owner::NEUTRAL);
			DrawFormatString(20, 90, 0xFFFFFF, "planet owner = %d", planets[i].owner);
		}
		
		//DrawCircle(static_cast<int>(planets[i].x + PLANET_CENTER), static_cast<int>(planets[i].y + PLANET_CENTER),35,GetColor(2, 194, 240),FALSE, 5.0f);
			//printf("ÑPÑ|ÑpÑ~ÑuÑÑÑp %d: x=%.1f, y=%.1f, image=%d\n",
			//	i, planets[i].x, planets[i].y, planets[i].groundImage);
		//DrawCircle(planets[i].x+PLANET_CENTER, planets[i].y + PLANET_CENTER, 35, GetColor(2, 194, 240), FALSE,5.0f);


	}
	//line
	//planetFunction.DrawLines(planetAngle);
 //
	//planetFunction.DrawExtraLines(extraAngles);

	//const int LINE_SPRITE_WIDTH = 16;
	//const int LINE_SPRITE_HEIGHT = 80;
	//	for (int i = 0; i < line_size; i++)
	//	{
	//		bool skipLine = (i == 5  || i == 11 || i == 18);

	//	
	//		if(!skipLine){
	//		DrawRectRotaGraph2((line[i].x + PLANET_CENTER), line[i].y + PLANET_CENTER, patternLine * 16, 112, 80, LINE_SPRITE_WIDTH + PLANET_CENTER, LINE_SPRITE_HEIGHT + PLANET_CENTER, 0, 1, planetAngle[i], lines, true, false);
	//		}
	//	}
	// 
	// 

	// 
	// 
		//DrawRectRotaGraph2((line[11].x + PLANET_CENTER), line[11].y + PLANET_CENTER, patternLine * 16, 112, 80, LINE_SPRITE_WIDTH + PLANET_CENTER, LINE_SPRITE_HEIGHT + PLANET_CENTER, 0, 1, planetAngle[11], lines, true, false);

		//DrawRectRotaGraph2(848 + PLANET_CENTER, 96 + PLANET_CENTER, patternLine * 16, 112, 80, 16, -48, 0, 1, planetAngle, lines, true, false);//lines red-gray 1
		//DrawRectRotaGraph2(1008 + PLANET_CENTER, 128 + PLANET_CENTER, patternLine * 16, 112, 80, 16, -48, 0, 1, planetAngle, lines, true, false);//lines gray 1- gray 2

		//planet position

		//for (int i = 0; i < planet_size; i++)

		//{
		//	DrawRectGraph(planet[i].x, planet[i].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false);
		//}
		// 
		// 
		//DrawRectGraph(planet[18].x, planet[18].y, patternPlanet *96, 0, 96, 96, groundImage, true, false); //middle
		//DrawRectGraph(planet[17].x, planet[17].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 15
		//DrawRectGraph(planet[16].x, planet[16].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 14
		//DrawRectGraph(planet[15].x, planet[15].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 13
		//DrawRectGraph(planet[14].x, planet[14].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 12
		//DrawRectGraph(planet[13].x, planet[13].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 11
		//DrawRectGraph(planet[12].x, planet[12].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //blue

		//DrawRectGraph(planet[11].x, planet[11].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 10
		//DrawRectGraph(planet[10].x, planet[10].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 9
		//DrawRectGraph(planet[9].x, planet[9].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 8
		//DrawRectGraph(planet[8].x, planet[8].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 7
		//DrawRectGraph(planet[7].x, planet[7].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 6
		//DrawRectGraph(planet[6].x, planet[6].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //yelloy

		//DrawRectGraph(planet[5].x, planet[5].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 5
		//DrawRectGraph(planet[4].x, planet[4].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 4
		//DrawRectGraph(planet[3].x, planet[3].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 3
		//DrawRectGraph(planet[2].x, planet[2].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 2
		//DrawRectGraph(planet[1].x, planet[1].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //grey 1
		//DrawRectGraph(planet[0].x, planet[0].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false); //red

			//1. planet[3] Ñy planet[17].
			//2. planet[4] Ñy planet[17].
			//3. planet[5] Ñy planet[18].
			//4. planet[9] Ñy planet[5].
			//5. planet[10] Ñy planet[5].
			//6. planet[5] Ñy planet[11].
			//7. planet[11] Ñy planet[17].
			//8. planet[16] Ñy planet[11].
			//9. planet[17] Ñy planet[11].
			//10. planet[17] Ñy planet[5].


			//1. planet[17] Ñy planet[18].
			//2. planet[11] Ñy planet[18].
			//3. planet[3] Ñy planet[11].
			//4. planet[4] Ñy planet[11].
			//5. planet[11] Ñy planet[5].
			//6. planet[17] Ñy planet[11].
			//7. planet[9] Ñy planet[17].
			//8. planet[10] Ñy planet[17].
			//9. planet[16] Ñy planet[5].
			//10. planet[15] Ñy planet[5].
			//11. planet[5] Ñy planet[17].
		//DrawRectGraph(689, 128, linePos.x*16, 112, 80, 16, lines, true, false); //lines
		//DrawRotaGraph2(848, 128, linePos.x*16, 112, 1, planetAngle, lines, true, false);
		//DrawRectRotaGraph(enemyPosX, enemyPosY, linePos.x*16, 112,80,16, 1, planetAngle, lines, true, false);//lines rotated
		//DrawRectRotaGraph2(848+48, 96+48, linePos.x * 16, 112, 80, 16, 0, 0, 1, planetAngle, lines, true, false);//lines rotated
	PlayerDraw();


	if (DEBUG_FONT) {
		DrawFormatString(20, 30, color, "EnemyStatus");
		
		//DrawFormatString(20, 50, (255,255,255), "%d", color);

		//AngleÇÕäpìxÇ≈ÇÕÇ»Ç≠ÅAÉâÉWÉAÉìÅi1.57ÅÅ90ìxÅjÇ≈ï\åªÇ≥ÇÍÇÈ
		//75çsñ⁄ÇÃíÜêg
		//DrawFormatString(20, 70, color, "Angle %f ", planetAngle);

		//Xç¿ïWÇ∆Yç¿ïWÇ÷ÇÃà⁄ìÆó 
		//78çsñ⁄ÅA79çsñ⁄ÇÃíÜêg
		//DrawFormatString(20, 120, color, "XMove %f ", cos(planetAngle));
		//DrawFormatString(20, 140, color, "YMove %f ", sin(planetAngle));
		//for (int i = 0; i < PLANET_MAX; i++)
		//{
		//	planets[i].SetId(i);  // ÑPÑÇÑyÑÉÑrÑpÑyÑrÑpÑuÑ} ÑÖÑ~ÑyÑ{ÑpÑ|ÑéÑ~ÑçÑu ID
		//	DrawFormatString(20, 50, color, "planet id %d", planets[i]);
		//}
	}
}

void PlaySceneRelease()
{
	planetFunction.Release();
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

void CalculatePlanetAngles(double planetAngle[]) {  // first lines Ñ|ÑyÑ~ÑyÑy ÑÉÑrÑëÑxÑçÑrÑpÑêÑãÑyÑu ÑÅÑ|ÑpÑ~ÑuÑÑÑç ÑÅÑÄÑÉÑ|ÑuÑtÑÄÑrÑpÑÑÑuÑ|ÑéÑ~ÑÄ
	for (int i = 0; i < line_size; i++) {
		int next_idx = (i + 1) % line_size;

		double dx = (line[i].x + PLANET_CENTER) - (line[next_idx].x + PLANET_CENTER);
		double dy = (line[i].y + PLANET_CENTER) - (line[next_idx].y + PLANET_CENTER);


		planetAngle[i] = atan2(dy, dx);  // atan2 ÑrÑÄÑxÑrÑÇÑpÑãÑpÑuÑÑ double
	}
}
//more lines ÑtÑÄÑÅÑÄÑ|Ñ~ÑyÑÑÑuÑ|ÑéÑ~ÑçÑu Ñ|ÑyÑ~ÑyÑy
void CalculateExtraAngles(double extraAngles[]) {
	// ÑPÑpÑÇÑç ÑÅÑ|ÑpÑ~ÑuÑÑ ÑtÑ|Ñë ÑtÑÄÑÅÑÄÑ|Ñ~ÑyÑÑÑuÑ|ÑéÑ~ÑçÑá ÑÉÑÄÑuÑtÑyÑ~ÑuÑ~ÑyÑz

	for (int i = 0; i < 11; i++) {
		int idx1 = extraConnections[i].first;
		int idx2 = extraConnections[i].second;

		double dx = (line[idx2].x + PLANET_CENTER) - (line[idx1].x + PLANET_CENTER);
		double dy = (line[idx2].y + PLANET_CENTER) - (line[idx1].y + PLANET_CENTER);
		extraAngles[i] = atan2(dy, dx);
	}
}

void DrawExtraLines(double extraAngles[]) {
	const int LINE_SPRITE_WIDTH = 16;
	const int LINE_SPRITE_HEIGHT = 80;

	// ÑPÑpÑÇÑç ÑÅÑ|ÑpÑ~ÑuÑÑ ÑtÑ|Ñë ÑtÑÄÑÅÑÄÑ|Ñ~ÑyÑÑÑuÑ|ÑéÑ~ÑçÑá ÑÉÑÄÑuÑtÑyÑ~ÑuÑ~ÑyÑz (ÑÑÑpÑ{ÑyÑu ÑwÑu Ñ{ÑpÑ{ Ñr CalculateExtraAngles)
			//1. planet[3] Ñy planet[17].
			//2. planet[4] Ñy planet[17].
			//3. planet[5] Ñy planet[18].
			//4. planet[9] Ñy planet[5].
			//5. planet[10] Ñy planet[5].
			//6. planet[5] Ñy planet[11].
			//7. planet[11] Ñy planet[17].
			//8. planet[16] Ñy planet[11].
			//9. planet[11] Ñy planet[18].
			//10. planet[17] Ñy planet[5].

	//const std::pair<int, int> extraConnections[] = {
	//	{3, 17}, {4, 17}, {5, 18}, {9, 5},
	//	{10, 5}, {5, 11}, {11, 17}, {16, 11},
	//	{18, 11}, {17, 5}
	//};

	for (int i = 0; i < 11; i++) {
		int idx1 = extraConnections[i].first;
		int idx2 = extraConnections[i].second;

		// ÑBÑçÑâÑyÑÉÑ|ÑëÑuÑ} ÑÉÑuÑÇÑuÑtÑyÑ~ÑÖ Ñ}ÑuÑwÑtÑÖ ÑÅÑ|ÑpÑ~ÑuÑÑÑpÑ}Ñy
		int midX = (line[idx1].x + line[idx2].x) / 2;
		int midY = (line[idx1].y + line[idx2].y) / 2;

		// ÑOÑÑÑÇÑyÑÉÑÄÑrÑçÑrÑpÑuÑ} ÑpÑ~ÑyÑ}ÑyÑÇÑÄÑrÑpÑ~Ñ~ÑÖÑê Ñ|ÑyÑ~ÑyÑê
		DrawRectRotaGraph2(midX + PLANET_CENTER, midY + PLANET_CENTER, patternLine * 16, 112, 144, LINE_SPRITE_WIDTH, LINE_SPRITE_HEIGHT, 0, 1, extraAngles[i], lines, true, false);
		DrawLineAA(line[idx1].x + PLANET_CENTER, line[idx1].y + PLANET_CENTER, line[idx2].x + PLANET_CENTER, line[idx2].y + PLANET_CENTER, GetColor(2, 194, 240), 2.0f);
	}
}

void DrawLines(double planetAngle[])
{
	const int LINE_SPRITE_WIDTH = 16;
	const int LINE_SPRITE_HEIGHT = 144;
	for (int i = 0; i < line_size; i++)
	{
		bool skipLine = (i == 5 || i == 11 || i == 18);


		if (!skipLine) {
			DrawRectRotaGraph2((line[i].x + PLANET_CENTER), line[i].y + PLANET_CENTER, patternLine * 16, 112, 144, LINE_SPRITE_WIDTH, LINE_SPRITE_HEIGHT, 0, 1, planetAngle[i], lines, true, false);
			DrawLineAA((line[i].x + PLANET_CENTER), line[i].y + PLANET_CENTER, (line[i + 1].x + PLANET_CENTER), (line[i + 1].y + PLANET_CENTER), GetColor(2, 194, 240), 2.0f);

		}
	}

}

//check