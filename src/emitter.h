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

	glm::vec3 missleDown();



	void enemyDraw(bool x);
	void addEnemy(glm::vec3 directionNew, float angle, float speed);
	sprite location;

};

