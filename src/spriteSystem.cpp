#include "spriteSystem.h"

void spriteSystem::addMissle(glm::vec3 direction, float angle,float speed)
{
	
	missleBase.loc.position = player.loc.position;
	missleBase.loc.size = missleSize;
	glm::vec3 heading = glm::normalize(direction - missleBase.loc.position);

	float s = sin(angle);
	float c = cos(angle);



	



	// translate point back to origin:
	direction.x -= missleBase.loc.position.x;
	direction.y -= missleBase.loc.position.y;

	// rotate point
	float xnew = direction.x * c - direction.y * s;
	float ynew = direction.x * s + direction.y * c;

	// translate point back:
	direction.x = xnew + missleBase.loc.position.x;
	direction.y = ynew + missleBase.loc.position.y;
	missleBase.directionMissle = direction;
	missleBase.missleAngle = angle;
	missleBase.missleSpeed = speed;
	missleCollect.push_back(missleBase);
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





void spriteSystem::missleUpdate()
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

void spriteSystem::missleKill(int i)
{
	int x = missleCollect.size()-1;

	std::swap(missleCollect[i], missleCollect[missleCollect.size()-1]);
	missleCollect.pop_back();
}
