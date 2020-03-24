#pragma once
#include "C:\Users\jemy_\Documents\Visual Studio 2017\of_v0.11.0_vs2017_release\libs\openFrameworks\app\ofBaseApp.h"
#include "spriteSystem.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "sprite.h"

// Class that is similar to the spriteSystem class but it is for enemy spawners.

class emitter :
	public spriteSystem
{
public:
	emitter() {
		enemyBase.img.load("Enemy.png");
		enemyBase.loc.verts.push_back(glm::vec3(missleSize, -missleSize, 0));
		enemyBase.loc.verts.push_back(glm::vec3(0, missleSize, 0));
		enemyBase.loc.verts.push_back(glm::vec3(-missleSize, -missleSize, 0));
	}



	glm::vec3 missleDown();



	void enemyDraw(bool x);
	void addEnemy(glm::vec3 direction, float angle, float speed);
	sprite location;
	sprite enemyBase;
};

