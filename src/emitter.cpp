#include "emitter.h"

glm::vec3 emitter::missleDown()
{
	return glm::vec3(location.loc.position.x, 10000, 0);
}

void emitter::enemyDraw(bool x)
{
	int i = 0;
	while (i < missleCollect.size()) {
		//draw missle
		if (x) {
			ofDrawLine(missleCollect.at(i).loc.position, missleCollect.at(i).directionMissle);
		}
		ofPushMatrix();
		glm::mat4 m = glm::translate(glm::mat4(1.0), glm::vec3(missleCollect.at(i).loc.position));
		glm::mat4 M = glm::rotate(m, (missleCollect.at(i).missleAngle), glm::vec3(0, 0, 1));
		ofMultMatrix(M);
		ofSetColor(255, 255, 255);
		if (spawnHitbox) {
			ofSetColor(ofColor::blue);
			ofDrawTriangle(missleCollect.at(i).loc.verts[0], missleCollect.at(i).loc.verts[1], missleCollect.at(i).loc.verts[2]);
		}
		else {
			missleCollect.at(i).img.draw(-35, -35, 70, 70);
		}
		ofPopMatrix();
		i++;
	}
}

void emitter::addEnemy(glm::vec3 directionNew, float angle, float speed)
{
	sprite missle;
	glm::vec3 direction = directionNew;
	missle.img.load("Enemy.png");
	missle.loc = player.loc;
	glm::vec3 heading = glm::normalize(direction - missle.loc.position);

	float s = sin(angle);
	float c = cos(angle);

	// translate point back to origin:
	direction.x -= missle.loc.position.x;
	direction.y -= missle.loc.position.y;

	// rotate point
	float xnew = direction.x * c - direction.y * s;
	float ynew = direction.x * s + direction.y * c;

	// translate point back:
	direction.x = xnew + missle.loc.position.x;
	direction.y = ynew + missle.loc.position.y;
	missle.directionMissle = direction;
	missle.missleAngle = angle;
	missle.missleSpeed = speed;
	missleCollect.push_back(missle);
}
