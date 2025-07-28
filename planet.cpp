#include "planet.h"
#include "math.h"
#include "DxLib.h"
#include <vector>
#include "struct.h"

namespace
{
	const float PLANET_CENTER = 48.0f; // „R„}„u„‹„u„~„y„u „ˆ„u„~„„„‚„p „„|„p„~„u„„„
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
}

Planet::Planet(float x, float y, float radius, Owner owner, int resources, int image)
    : x(x), y(y), radius(radius), owner(owner), resources(resources), image(image) {
}
void Planet::Init()
{

}
void Planet::Render() const {
    // „@„~„y„}„p„ˆ„y„‘ „„…„|„„ƒ„p„ˆ„y„y
    static float scale = 1.0f;
    scale = 0.9f + 0.1f * sinf(GetNowCount() * 0.005f);

    DrawRotaGraph(x, y, scale, 0.0, image, TRUE);
}
void Planet:: SetOwner(Owner newOwner)
{
    owner = newOwner;
}

void CalculatePlanetAngles(double planetAngle[]) {  // first lines „|„y„~„y„y „ƒ„r„‘„x„„r„p„„‹„y„u „„|„p„~„u„„„ „„€„ƒ„|„u„t„€„r„p„„„u„|„„~„€
	for (int i = 0; i < planet_size; i++) {
		int next_idx = (i + 1) % planet_size;

		double dx = (planet[i].x + PLANET_CENTER) - (planet[next_idx].x + PLANET_CENTER);
		double dy = (planet[i].y + PLANET_CENTER) - (planet[next_idx].y + PLANET_CENTER);


		planetAngle[i] = atan2(dy, dx);  // atan2 „r„€„x„r„‚„p„‹„p„u„„ double
	}
}
// more lines „t„€„„€„|„~„y„„„u„|„„~„„u „|„y„~„y„y
void CalculateExtraAngles(double extraAngles[]) {
	// „P„p„‚„ „„|„p„~„u„„ „t„|„‘ „t„€„„€„|„~„y„„„u„|„„~„„‡ „ƒ„€„u„t„y„~„u„~„y„z

	for (int i = 0; i < 11; i++) {
		int idx1 = extraConnections[i].first;
		int idx2 = extraConnections[i].second;

		double dx = (planet[idx2].x + PLANET_CENTER) - (planet[idx1].x + PLANET_CENTER);
		double dy = (planet[idx2].y + PLANET_CENTER) - (planet[idx1].y + PLANET_CENTER);
		extraAngles[i] = atan2(dy, dx);
	}
}

void DrawExtraLines(double extraAngles[]) {
	const int LINE_SPRITE_WIDTH = 16;
	const int LINE_SPRITE_HEIGHT = 80;

	// „P„p„‚„ „„|„p„~„u„„ „t„|„‘ „t„€„„€„|„~„y„„„u„|„„~„„‡ „ƒ„€„u„t„y„~„u„~„y„z („„„p„{„y„u „w„u „{„p„{ „r CalculateExtraAngles)
			//1. planet[3] „y planet[17].
			//2. planet[4] „y planet[17].
			//3. planet[5] „y planet[18].
			//4. planet[9] „y planet[5].
			//5. planet[10] „y planet[5].
			//6. planet[5] „y planet[11].
			//7. planet[11] „y planet[17].
			//8. planet[16] „y planet[11].
			//9. planet[11] „y planet[18].
			//10. planet[17] „y planet[5].

	//const std::pair<int, int> extraConnections[] = {
	//	{3, 17}, {4, 17}, {5, 18}, {9, 5},
	//	{10, 5}, {5, 11}, {11, 17}, {16, 11},
	//	{18, 11}, {17, 5}
	//};

	for (int i = 0; i < 11; i++) {
		int idx1 = extraConnections[i].first;
		int idx2 = extraConnections[i].second;

		// „B„„‰„y„ƒ„|„‘„u„} „ƒ„u„‚„u„t„y„~„… „}„u„w„t„… „„|„p„~„u„„„p„}„y
		int midX = (planet[idx1].x + planet[idx2].x) / 2;
		int midY = (planet[idx1].y + planet[idx2].y) / 2;

		// „O„„„‚„y„ƒ„€„r„„r„p„u„} „p„~„y„}„y„‚„€„r„p„~„~„…„ „|„y„~„y„
		DrawRectRotaGraph2(midX + PLANET_CENTER, midY + PLANET_CENTER, patternLine * 16, 112, 80, LINE_SPRITE_WIDTH, LINE_SPRITE_HEIGHT, 0, 1, extraAngles[i], lines, true, false);
	}
}
