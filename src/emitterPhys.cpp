#include "emitterPhys.h"


void emitterPhys::missleUpdatePhys()
{

	int i = 0;
	while (i < missleCollect.size()) {
		//delete missle if out of bounds
		if (missleCollect[i].loc.position.y < 0 || missleCollect[i].loc.position.y > ofGetHeight() || missleCollect[i].loc.position.x < 0 || missleCollect[i].loc.position.x > ofGetWidth()) {
			int x = missleCollect.size() - 1;
			std::swap(missleCollect[i], missleCollect[missleCollect.size() - 1]);
			missleCollect.pop_back();
		}
		else {
			missleCollect[i].particle.integrate();
			missleCollect[i].loc.position = missleCollect[i].particle.position;
			i++;
		}

	}


}

void emitterPhys::addEnemyPhys(glm::vec3 direction, float angle, float speed) {
	enemyBase.particle = Particle(player.loc.position, direction, angle, speed);
	enemyBase.loc.position = player.loc.position;
	enemyBase.loc.size = missleSize;
	enemyBase.directionMissle = direction;
	
	enemyBase.missleAngle = -atan2(-direction.x+player.loc.position.x,-direction.y+player.loc.position.y) ;
	enemyBase.missleSpeed = speed;
	missleCollect.push_back(enemyBase);
}

