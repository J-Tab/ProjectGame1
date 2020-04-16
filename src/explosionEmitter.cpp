#include "explosionEmitter.h"

explosionEmitter::explosionEmitter(ofVec2f positionT,EmitterType x)
{
	position = positionT;
	type = x;
	explode();
}

void explosionEmitter::explode()
{
	switch (type) {
	case Small:
	{
		for (int i = 0; i < 4; i++) {
			Particle temp = Particle(position, i*PI / 2, explosionSpeed);
			particles.push_back(temp);
		}
	}
	break;
	case Medium:
	{
		for (int i = 0; i < 8; i++) {
			Particle temp = Particle(position, i*PI / 4, explosionSpeed);
			particles.push_back(temp);
		}
	}
	break;
	case Large:
	{
		for (int i = 0; i < 16; i++) {
			Particle temp = Particle(position, i*PI / 8, explosionSpeed);
			particles.push_back(temp);
		}
	}
	break;
	}
	

}

void explosionEmitter::draw()
{
	for (Particle& x : particles) {
		x.draw();
	}
}

void explosionEmitter::update()
{


	for (int i = 0; i < particles.size(); i++) {

		if (particles[i].age() > particles[i].lifespan) {
			particles.erase(particles.begin()+ i);
		}
		else {
			particles[i].integrate();
		}
		
	}
}
