#include "spriteSystem.h"

void spriteSystem::addMissle(glm::vec3 directionNew, float angle,float speed)
{
	sprite missle;
	glm::vec3 direction = directionNew;
	missle.img.load("placeHolder.png");
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

glm::vec3 spriteSystem::missleUp()
{
	return glm::vec3(player.loc.position.x, -10000,0);
}



void spriteSystem::missleDraw(bool x)
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
		missleCollect.at(i).img.draw(-50, -50, 100, 100);
		ofPopMatrix();
		i++;
	}
}

void spriteSystem::missleUpdate()
{
	
	int i = 0;
	while (i < missleCollect.size()) {
		//delete missle if out of bounds
		if (missleCollect[i].loc.position.y < 0 || missleCollect[i].loc.position.y > ofGetHeight() || missleCollect[i].loc.position.x < 0 || missleCollect[i].loc.position.x > ofGetWidth()) {
			missleCollect.erase(missleCollect.begin() + i);
			i--;
		}
		else {
			float nextPosition;
			glm::vec3 header = glm::vec3(missleCollect[i].directionMissle.x - missleCollect[i].loc.position.x, missleCollect[i].directionMissle.y - missleCollect[i].loc.position.y, 0);
			glm::vec3 nextPos = missleCollect[i].loc.position + glm::normalize(header) * missleCollect[i].missleSpeed;
			missleCollect[i].loc.position = nextPos;
			i++;
		}
		
	}
	
	
	
	/*stack <sprite> missleTemp = missleCollect;
	stack <sprite> missleNew;
	while (!missleTemp.empty()) {
		sprite temp = missleTemp.top();
		missleTemp.pop();


		float nextPosition;
		float missleSpeed =  50;
		glm::vec3 header = glm::vec3(temp.directionMissle.x - temp.loc.position.x, temp.directionMissle.y - temp.loc.position.y, 0);
		glm::vec3 nextPos = temp.loc.position + glm::normalize(header) * 25;
		temp.loc.position = nextPos;
		missleTemp.push(temp);
	}
	missleCollect.swap(missleNew);*/
}
