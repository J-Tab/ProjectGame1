#pragma once
#include "C:\Users\jemy_\Documents\Visual Studio 2017\of_v0.11.0_vs2017_release\libs\openFrameworks\app\ofBaseApp.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "sprite.h"
class spriteSystem 
{
public:
	spriteSystem() {
		missleBase.img.load("missleP.png");
		missleBase.loc.verts.push_back(glm::vec3(missleSize, -missleSize, 0));
		missleBase.loc.verts.push_back(glm::vec3(0, missleSize, 0));
		missleBase.loc.verts.push_back(glm::vec3(-missleSize, -missleSize, 0));
	}




	void addMissle(glm::vec3 direction, float angle, float speed);
	glm::vec3 missleUp();
	void missleDraw(bool x);
	void missleUpdate();
	bool spawnHitbox;
	void missleKill(int i);

	int missleSize = 30;
	sprite player;
	sprite missleBase;


	std::vector <sprite> missleCollect;
};

