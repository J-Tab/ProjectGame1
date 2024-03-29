#include "particle.h"

Particle::Particle() {
	velocity.set(0, 0, 0);
	acceleration.set(0, 0, 0);
	position.set(0, 0, 0);
	forces.set(0, 0, 0);
	lifespan = 5;
	birthtime = 0;
	radius = 1;
	damping = .99;
	mass = 1;
	color = ofColor::red;
}

Particle::Particle(ofVec3f pos ,double angle, double initVel) {
	position.set(pos);
	ofVec3f direction = ofVec3f(position.x, position.y - 1);
	
	//Rotate the velocity vector
	float s = sin(angle);
	float c = cos(angle);
	float xVel = direction.x * c - direction.y * s;
	float yVel = direction.x * s + direction.y * c;

	velocity.set(xVel*initVel, yVel*initVel, 0);
	acceleration.set(-xVel * initVel / 10, -yVel * initVel / 10, 0);
	lifespan = 5;
	birthtime = 0;
	radius = 1;
	damping = .99;
	mass = 1;
	color = ofColor::red;

}

void Particle::integrate()
{
	// check for 0 framerate to avoid divide errors
	//
	float framerate = ofGetFrameRate();

	// avoid accumulating forces on startup before frame is drawn
	//
	if (framerate < 5.0)
	{
		forces.set(0, 0, 0);
		return;
	}

	// interval for this step
	//
	float dt = 1.0 / framerate;

	// update position based on velocity
	//
	position += (velocity * dt);

	// update acceleration with accumulated paritcles forces
	// remember :  (f = ma) OR (a = 1/m * f)
	//
	ofVec3f accel = acceleration;    // start with any acceleration already on the particle
	accel += (forces * (1.0 / mass));
	velocity += accel * dt;


	// add a little damping for good measure
	//
	velocity *= damping;

	// clear forces on particle (they get re-added each step)
	//
	forces.set(0, 0, 0);
}

void Particle::draw()
{
	ofSetColor(color);
	//	ofSetColor(ofMap(age(), 0, lifespan, 255, 10), 0, 0);
	ofDrawCircle(position, radius);
}

float Particle::age()
{
	return (ofGetElapsedTimeMillis() - birthtime) / 1000.0;
}
