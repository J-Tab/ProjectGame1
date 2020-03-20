#pragma once
#include "C:\Users\jemy_\Documents\Visual Studio 2017\of_v0.11.0_vs2017_release\libs\openFrameworks\app\ofBaseApp.h"
#include "spriteSystem.h"
#include "ofMain.h"
#include "ofxGui.h"
#include "sprite.h"



class emitter :
	public spriteSystem
{
public:
	glm::vec3 missleDown();
	sprite location;

};

