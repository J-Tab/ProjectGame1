#pragma once
#include "emitter.h"


//Similar to the emitter class except this utilizes the particle class for physics for the enemies

class emitterPhys :
	public emitter
{
public:
	emitterPhys() {
		enemyBase.img.load("Enemy2.png");
		enemyBase.loc.verts.push_back(glm::vec3(missleSize, -missleSize, 0));
		enemyBase.loc.verts.push_back(glm::vec3(0, missleSize, 0));
		enemyBase.loc.verts.push_back(glm::vec3(-missleSize, -missleSize, 0));
		physicsEnabled = true;
	}
	
	void missleUpdatePhys();
	void addEnemyPhys(glm::vec3 direction, float angle, float speed);
};

