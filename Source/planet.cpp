#include "planet.h"
#include "math.h"
#include "struct.h"
#include <vector>
#include <DxLib.h>
#include <assert.h>

namespace
{

	static const float PLANET_CENTER = 48.0; //planet radius
    int groundImage = -1;	//ínñ ÇÃâÊëúÉnÉìÉhÉã
    int lines = -1;


	VectorI2 planet[] = { {689,128},{848, 96},{1008, 128},
						{1136, 224},{1192, 368},{1096, 509},
						{1456, 428},{1408, 592},{1280, 720},
						{1104, 768},{944, 704},{848, 560},
						{848.5, 911},{704, 800},{624, 640},
						{655, 464},{785, 352},{960, 336},{960,476} };
	const int planet_size = sizeof(planet) / sizeof(planet[0]);
	//----------------------------------------------


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
	//animation
	int patternLine;
	int patternPlanet;
	//----------------------------------------------
	VectorI2 lineAngle[];
	double dx;
	double dy;
	//----------------------------------------------
	double planetAngle[planet_size];
	double extraAngles[11];

}
Planet::Planet(float x, float y, float radius, Owner owner, int resources, int image)
	: x(x), y(y), radius(radius), owner(owner), resources(resources), image(image) {
}
void Planet::Init() 
{
	//----------------------------------------------
	if (groundImage < 0) {
		groundImage = LoadGraph("data\\texture\\ground\\ground1.png");
		assert(groundImage >= 0);
	}
	if (lines < 0) {
		lines = LoadGraph("data\\texture\\lines\\mylines1.png");
		assert(lines >= 0);
	}
	//----------------------------------------------
	patternLine = 0;
	patternPlanet = 0;
}
void Planet::Update() 
{
	//angle
	Planet::CalculatePlanetAngles(planetAngle);
	//extra angle
	Planet::CalculateExtraAngles(extraAngles);

	// Update logic for the planet can be added here
}

void Planet::Draw()
{
	const int LINE_SPRITE_WIDTH = 16;
	const int LINE_SPRITE_HEIGHT = 80;
	for (int i = 0; i < line_size; i++)
	{
		bool skipLine = (i == 5 || i == 11 || i == 18);


		if (!skipLine) {
			DrawRectRotaGraph2((line[i].x + PLANET_CENTER), line[i].y + PLANET_CENTER, patternLine * 16, 112, 80, LINE_SPRITE_WIDTH + PLANET_CENTER, LINE_SPRITE_HEIGHT + PLANET_CENTER, 0, 1, planetAngle[i], lines, true, false);
		}
	}

	//more center lines ÑtÑÄÑÅÑÄÑ|Ñ~ÑyÑÑÑuÑ|ÑéÑ~ÑçÑu Ñ|ÑyÑ~ÑyÑy.
	Planet::DrawExtraLines(extraAngles);

	//planet position

	for (int i = 0; i < planet_size; i++)

	{
		DrawRectGraph(planet[i].x, planet[i].y, patternPlanet * 96, 0, 96, 96, groundImage, true, false);
	}
}
void Planet::Release() 
{
	// Release resources if needed
	if (groundImage >= 0) {
		DeleteGraph(groundImage);
		groundImage = -1;
	}
	if (lines >= 0) {
		DeleteGraph(lines);
		lines = -1;
	}
}

void Planet::SetOwner(Owner newOwner) 
{
    owner = newOwner;
}

void Planet::CalculatePlanetAngles(double planetAngle[]) {  // first lines Ñ|ÑyÑ~ÑyÑy ÑÉÑrÑëÑxÑçÑrÑpÑêÑãÑyÑu ÑÅÑ|ÑpÑ~ÑuÑÑÑç ÑÅÑÄÑÉÑ|ÑuÑtÑÄÑrÑpÑÑÑuÑ|ÑéÑ~ÑÄ
	for (int i = 0; i < planet_size; i++) {
		int next_idx = (i + 1) % planet_size;

		double dx = (planet[i].x + PLANET_CENTER) - (planet[next_idx].x + PLANET_CENTER);
		double dy = (planet[i].y + PLANET_CENTER) - (planet[next_idx].y + PLANET_CENTER);


		planetAngle[i] = atan2(dy, dx);  // atan2 ÑrÑÄÑxÑrÑÇÑpÑãÑpÑuÑÑ double
	}
}

// more lines ÑtÑÄÑÅÑÄÑ|Ñ~ÑyÑÑÑuÑ|ÑéÑ~ÑçÑu Ñ|ÑyÑ~ÑyÑy
void Planet::CalculateExtraAngles(double extraAngles[]) {
	// ÑPÑpÑÇÑç ÑÅÑ|ÑpÑ~ÑuÑÑ ÑtÑ|Ñë ÑtÑÄÑÅÑÄÑ|Ñ~ÑyÑÑÑuÑ|ÑéÑ~ÑçÑá ÑÉÑÄÑuÑtÑyÑ~ÑuÑ~ÑyÑz

	for (int i = 0; i < 11; i++) {
		int idx1 = extraConnections[i].first;
		int idx2 = extraConnections[i].second;

		double dx = (planet[idx2].x + PLANET_CENTER) - (planet[idx1].x + PLANET_CENTER);
		double dy = (planet[idx2].y + PLANET_CENTER) - (planet[idx1].y + PLANET_CENTER);
		extraAngles[i] = atan2(dy, dx);
	}
}

void Planet::DrawExtraLines(double extraAngles[]) {
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
		int midX = (planet[idx1].x + planet[idx2].x) / 2;
		int midY = (planet[idx1].y + planet[idx2].y) / 2;

		// ÑOÑÑÑÇÑyÑÉÑÄÑrÑçÑrÑpÑuÑ} ÑpÑ~ÑyÑ}ÑyÑÇÑÄÑrÑpÑ~Ñ~ÑÖÑê Ñ|ÑyÑ~ÑyÑê
		DrawRectRotaGraph2(midX + PLANET_CENTER, midY + PLANET_CENTER, patternLine * 16, 112, 80, LINE_SPRITE_WIDTH, LINE_SPRITE_HEIGHT, 0, 1, extraAngles[i], lines, true, false);
	}
}