#include "explosionEmitter.h"

explosionEmitter::explosionEmitter(ofVec2f positionT,EmitterType x)
{
	position = positionT;
	type = x;
}

void explosionEmitter::explode()
{
	switch (type) {
	case Small:
	{
		for (int i = 0; i < 4; i++) {
			Particle temp = Particle(position, i*PI / 2, 3);
			particles.push_back(temp);
		}
	}
	case Medium:
	{
		for (int i = 0; i < 8; i++) {
			Particle temp = Particle(position, i*PI / 4, 3);
			particles.push_back(temp);
		}
	}
	case Large:
	{
		for (int i = 0; i < 16; i++) {
			Particle temp = Particle(position, i*PI / 8, 3);
			particles.push_back(temp);
		}
	}

	}

}

void explosionEmitter::draw()
{
	for (Particle x : particles) {
		x.draw();
	}
}

void explosionEmitter::update()
{
	for (Particle x : particles) {
		x.integrate;
	}
}
