#pragma once
#include "C:\Users\jemy_\Documents\Visual Studio 2017\of_v0.11.0_vs2017_release\libs\openFrameworks\app\ofBaseApp.h"
#include "ofMain.h"
#include "ofxGui.h"

//Uses triangle class in order to detect the location and area of the sprite.
class Triangle {
public:
	vector<glm::vec3> verts;
	glm::vec3 position;    // position of the triangle (in screen space)
	float angle = 0;       // rotation angle of triangle
};


class sprite
{
public:
	glm::vec3 directionMissle;
	ofImage img;
	Triangle loc;
	float missleAngle = 0;
	float missleSpeed = 5;
};

