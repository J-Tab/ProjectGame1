#pragma once
#include "ofMain.h"

class Particle {
public:
	Particle();
	Particle(ofVec3f pos, ofVec3f header, double angle, double initVel);
	Particle(ofVec3f pos,double angle, double initVel);

	ofVec3f position;
	ofVec3f velocity;
	ofVec3f acceleration;
	ofVec3f forces;
	float	damping;
	float   mass;
	float   lifespan;
	float   radius;
	float   birthtime;
	void    integrate();
	void    draw();
	float   age();        // sec
	ofColor color;
};