#pragma once
#include "ofMain.h"
#include "particle.h"

typedef enum { Small, Medium, Large } EmitterType;
//class that utilizes the particle class to make explosions when an enemy sprite dies

class explosionEmitter {
	public:
		//Constructor
		explosionEmitter(ofVec2f position,EmitterType x);
		EmitterType type;

		void explode();
		void draw();
		void update();
		float explosionSpeed = .5;

		ofVec2f position;
		std::vector <Particle> particles;
		
};



