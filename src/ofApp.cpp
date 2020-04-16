#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	playerFire.load("Fire.mp3");
	playerFire.setMultiPlay(true);
	enemyDeathSound.load("EnemyDeath.ogg");
	enemyDeathSound.setVolume(.3f);
	playerSprite.player.img.load("Player.png");
	background.load("placeHolderBackGround.jpg");
	playerSprite.player.loc.position = glm::vec3(ofGetWidth() / 2.0, ofGetHeight() / 2.0, 0);
	gui.setup();
	gui.add(angleSlider.setup("angle", 0, 0, 5));
	gui.add(fireSlider.setup("firespeed", 5, 1, 10));
	gui.add(spawnRate.setup("enemy spawn speed", 80, 1, 200));
	gui.add(enemySpeedSlider.setup("enemy velocity", 2, 1, 5));
	gui.add(lineButton.setup("Missle Line toggle", false));
	gui.add(enemyHitbox.setup("Enemy Hitbox Toggle", false));

	spawner1.player.loc.position = glm::vec3(ofGetWidth()/2, 20, 0);
	spawner2.player.loc.position = glm::vec3(ofGetWidth() / 4, 20, 0);
	spawner3.player.loc.position = glm::vec3(ofGetWidth() / 4 + ofGetWidth() / 2, 20, 0);
	spawner1.player.img.load("Player.png");
	spawner2.player.img.load("Player.png");
	spawner3.player.img.load("Player.png");

	// Exam;ple on how to add elements to a vector<>
	// Store the vertices to the triangle relative to origin (0, 0, 0);
	// The triangle is moveable in that we add these vertices to it's
	// position to get screen space coordinates (for drawing).
	//
	playerSprite.player.loc.verts.push_back(glm::vec3(100, -100, 0));
	playerSprite.player.loc.verts.push_back(glm::vec3(0, 100, 0));
	playerSprite.player.loc.verts.push_back(glm::vec3(-100, -100, 0));
	spawner1.player.loc.verts.push_back(glm::vec3(-30, 30, 0));
	spawner1.player.loc.verts.push_back(glm::vec3(0, -30, 0));
	spawner1.player.loc.verts.push_back(glm::vec3(30, 30, 0));
	spawner2.player.loc.verts.push_back(glm::vec3(-30, 30, 0));
	spawner2.player.loc.verts.push_back(glm::vec3(0, -30, 0));
	spawner2.player.loc.verts.push_back(glm::vec3(30, 30, 0));
	spawner3.player.loc.verts.push_back(glm::vec3(-30, 30, 0));
	spawner3.player.loc.verts.push_back(glm::vec3(0, -30, 0));
	spawner3.player.loc.verts.push_back(glm::vec3(30, 30, 0));
	spawner4.player.loc.position = glm::vec3(ofGetWidth() / 2, 20, 0);
	spawner4.player.loc.verts.push_back(glm::vec3(30, 30, 0));
	spawnSpeed = spawnRate;
	enemySpeed = enemySpeedSlider;


	ofSetBackgroundColor(ofColor::black);
}

//--------------------------------------------------------------
void ofApp::update() {
	//Determine next postion of the player by buttons pressed
	enemySpeedSlider = enemySpeed;
	spawnRate = spawnSpeed;

	if (startGame) {
		MissleTimer++;
		Timer++;

		//update enemy emitters every 5th of the playerscore
		if (fmod(playerScore, 5) == 1 && !enemyUpdate) {
			enemySpeed = enemySpeed + .25;
			if (spawnSpeed > 10) {
				spawnSpeed = spawnSpeed - 5;
			}
			enemyUpdate = true;

		}
		if (fmod(playerScore, 5) == 2) {
			enemyUpdate = false;
		}




		if (bSpaceKeyDown) {
			if (fmod(MissleTimer, fireRate) == 0) {
				playerFire.play();
				float x = angleSlider;
				playerSprite.addMissle(playerSprite.missleUp(), x, fireSlider);
			}
		}

		float random = ((float)rand()) / (float)RAND_MAX;
		float diff = PI / 2;
		float r = random * diff;


		if (fmod(Timer, (int)spawnSpeed) == 0) {
			
			r += PI / 2 + PI / 4;
			spawner1.addEnemy(spawner1.missleUp(), r, enemySpeed);

			
		}





		//New enemy emitters when player reaches certain score
		if (playerScore > 10 && fmod(Timer+20, (int)spawnSpeed) == 0) {
			float random1 = ((float)rand()) / (float)RAND_MAX;
			float r = random1 * diff;
			r += PI / 2 + PI / 4;
			spawner2.addEnemy(spawner2.missleUp(), r, enemySpeed);


			
		}
		if (playerScore > 20 && fmod(Timer + 10, (int)spawnSpeed) == 0) {
			float random2 = ((float)rand()) / (float)RAND_MAX;
			r = random2 * diff;
			r += PI / 2 + PI / 4;
			spawner3.addEnemy(spawner3.missleUp(), r, enemySpeed);
		}
		

		float nextX = 0;
		float nextY = 0;
		if (bUpKeyDown) {
			nextY -= 1;
		}
		if (bDownKeyDown) {
			nextY += 1;
		}
		if (bRightKeyDown) {
			nextX += 1;
		}
		if (bLeftKeyDown) {
			nextX -= 1;
		}
		//Ship movement based on keyboard controls
		//Make a vector that determines the next location of the player, distance determined by the playerSpeed modifier.
		nextX = nextX * playerSpeed;
		nextY = nextY * playerSpeed;
		float nextXVec = playerSprite.player.loc.position.x + nextX;
		float nextYVec = playerSprite.player.loc.position.y + nextY;

		//Places bounds on the screen
		if (nextXVec < 0) {
			nextXVec = 0;
		}
		if (nextXVec > ofGetWidth()) {
			nextXVec = ofGetWidth();
		}
		if (playerSprite.player.loc.position.y + nextY < 0) {
			nextYVec = 0;
		}
		if (nextYVec > ofGetHeight()) {
			nextYVec = ofGetHeight();
		}

		//Sets player location
		playerSprite.player.loc.position = glm::vec3(nextXVec, nextYVec, 0);

		//Check collisions
		collisionUpdate();

		//Update missles
		playerSprite.missleUpdate();
		spawner1.missleUpdate();
		spawner1.spawnHitbox = enemyHitbox;
		spawner2.missleUpdate();
		spawner2.spawnHitbox = enemyHitbox;
		spawner3.missleUpdate();
		spawner3.spawnHitbox = enemyHitbox;
		playerSprite.spawnHitbox = enemyHitbox;

		//Update explosions
		for (explosionEmitter& x : explosionHolder) {

			x.update();
		}
	}
	if (playerDead) {
		playerSprite.player.loc.position = ofVec3f(-500, -500, 0);
	}
	
}

//--------------------------------------------------------------
void ofApp::draw() {
	//Idle Screen at start
	if (!startGame) {
		ofClear(0);
		ofDrawBitmapString("Press Spacebar to Play!", ofGetWidth()/2-100, ofGetHeight()/2);
	}
	//Gameplay drawing when user activates game
	else {
		//Draw background first
		ofSetColor(255, 255, 255);
		background.draw(0, 0, ofGetWidth(), ofGetHeight());
		//Debug menu displayed if key '`' is pressed
		if (debugEnable) {
			gui.draw();
		}
		
		//Score UI
		ofDrawBitmapStringHighlight("Score:"+std::to_string(playerScore), 20, 20, ofColor(0, 0, 0), ofColor(255, 0, 0));

		//draw enemies
		ofPushMatrix();
		glm::mat4 m = glm::translate(glm::mat4(1.0), glm::vec3(spawner1.player.loc.position));
		ofMultMatrix(m);
		ofSetColor(255, 255, 255);
		ofPopMatrix();
		spawner1.enemyDraw(lineButton);
		spawner2.enemyDraw(lineButton);
		spawner3.enemyDraw(lineButton);






		// draw player in screen space (we need to add the position to get screen coordinates)
		//

		if (!playerDead) {
			ofPushMatrix();
			m = glm::translate(glm::mat4(1.0), glm::vec3(playerSprite.player.loc.position));
			ofMultMatrix(m);
			ofSetColor(255, 255, 255);
			playerSprite.player.img.draw(-50, -50, 100, 100);
			ofPopMatrix();

			playerSprite.missleDraw(lineButton);
		}
		

		//draw explosions
		for (explosionEmitter& x : explosionHolder) {
			x.draw();
		}
		
		
	}
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	switch (key) {
	case '`':
		debugEnable = !debugEnable;
		break;
	case 'f':
		bFullscreen = !bFullscreen;
		ofSetFullscreen(bFullscreen);
		break;
	case OF_KEY_CONTROL:
		bCtrlKeyDown = true;
		break;
	//Starts game when space is hit; When game start fires missles
	case ' ':
		if (!startGame) {
			startGame = !startGame;
		}
		else if (!playerDead){
			bSpaceKeyDown = true;
		}
		break;
	case OF_KEY_DOWN:
		bDownKeyDown = true;
		break;
	case OF_KEY_LEFT:
		bLeftKeyDown = true;
		break;
	case OF_KEY_RIGHT:
		bRightKeyDown = true;
		break;
	case OF_KEY_UP:
		bUpKeyDown = true;
		break; 
	default:
		break;
	}
}

void ofApp::rotate(const vector<glm::vec3> &vin, vector<glm::vec3> &vout, float angle) {
	for (int i = 0; i < vin.size(); i++) {
		vout.push_back(glm::vec3(vin[i].x * cos(angle) - vin[i].y *sin(angle),
			vin[i].x * sin(angle) + vin[i].y *cos(angle), 0));
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	switch (key) {
	case OF_KEY_DOWN:
		bDownKeyDown = false;
		break;
	case OF_KEY_LEFT:
		bLeftKeyDown = false;
		break;
	case OF_KEY_RIGHT:
		bRightKeyDown = false;
		break;
	case OF_KEY_UP:
		bUpKeyDown = false;
		break;
	case ' ':
		bSpaceKeyDown = false;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {
	playerSprite.player.loc.position = glm::vec3(x, y, 0);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	if (!bDrag) return;

	glm::vec3 mousePoint(x, y, 0);


	lastMouse = mousePoint;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	bDrag = false;
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}


// Check if these two sprites are in the same area.
bool ofApp::detectCollision(Triangle a, Triangle b)
{
	int ax = a.position.x;
	int ay = a.position.y;
	int bx = b.position.x;
	int by = b.position.y;
	if (ax<=bx+b.size && ax + a.size >= bx && ay<=by + b.size && ay + a.size >= by) {
		return true;
	}
	else {
		return false;
	}
	
}

void ofApp::collisionUpdate()
{
	bool deleted = false;
	int tempI;

	//Check for collisions with player missles and enemies
	for (int i = 0; i < playerSprite.missleCollect.size(); i++) {
		if (deleted) {
			i = tempI;
			deleted = false;
		}
		for (int j = 0; j < spawner1.missleCollect.size(); j++) {

			if (ofDistSquared(playerSprite.missleCollect[i].loc.position.x, playerSprite.missleCollect[i].loc.position.y, spawner1.missleCollect[j].loc.position.x, spawner1.missleCollect[j].loc.position.y)) {
				if (detectCollision(playerSprite.missleCollect[i].loc, spawner1.missleCollect[j].loc)) {
					explosionHolder.push_back(explosionEmitter(spawner1.missleCollect[j].loc.position,Medium));
					playerSprite.missleKill(i);
					tempI = i;
					spawner1.missleKill(j);
					deleted = true;
					
					playerScore++;
					enemyDeathSound.play();
					j = spawner1.missleCollect.size();
				}
				
			}
			

		}
		for (int j = 0; j < spawner2.missleCollect.size(); j++) {

			if (ofDistSquared(playerSprite.missleCollect[i].loc.position.x, playerSprite.missleCollect[i].loc.position.y, spawner2.missleCollect[j].loc.position.x, spawner2.missleCollect[j].loc.position.y)) {
				if (detectCollision(playerSprite.missleCollect[i].loc, spawner2.missleCollect[j].loc)) {
					explosionHolder.push_back(explosionEmitter(spawner2.missleCollect[j].loc.position, Medium));
					playerSprite.missleKill(i);
					tempI = i;
					spawner2.missleKill(j);
					deleted = true;

					playerScore++;
					enemyDeathSound.play();
					j = spawner2.missleCollect.size();
				}

			}


		}

		for (int j = 0; j < spawner3.missleCollect.size(); j++) {

			if (ofDistSquared(playerSprite.missleCollect[i].loc.position.x, playerSprite.missleCollect[i].loc.position.y, spawner3.missleCollect[j].loc.position.x, spawner3.missleCollect[j].loc.position.y)) {
				if (detectCollision(playerSprite.missleCollect[i].loc, spawner3.missleCollect[j].loc)) {
					explosionHolder.push_back(explosionEmitter(spawner3.missleCollect[j].loc.position, Medium));
					playerSprite.missleKill(i);
					tempI = i;
					spawner3.missleKill(j);
					deleted = true;

					playerScore++;
					enemyDeathSound.play();
					j = spawner3.missleCollect.size();
				}

			}


		}

	}

	//Similar to above but this check is for the player
	if (!playerDead) {
		for (int j = 0; j < spawner1.missleCollect.size(); j++) {

			if (ofDistSquared(playerSprite.player.loc.position.x, playerSprite.player.loc.position.y, spawner1.missleCollect[j].loc.position.x, spawner1.missleCollect[j].loc.position.y)) {
				if (detectCollision(playerSprite.player.loc, spawner1.missleCollect[j].loc)) {
					explosionHolder.push_back(explosionEmitter(playerSprite.player.loc.position, Large));
					playerDead = true;
					spawner1.missleKill(j);
					enemyDeathSound.play();
					j = spawner1.missleCollect.size();
				}
			}


		}

		for (int j = 0; j < spawner2.missleCollect.size(); j++) {

			if (ofDistSquared(playerSprite.player.loc.position.x, playerSprite.player.loc.position.y, spawner2.missleCollect[j].loc.position.x, spawner2.missleCollect[j].loc.position.y)) {
				if (detectCollision(playerSprite.player.loc, spawner2.missleCollect[j].loc)) {
					explosionHolder.push_back(explosionEmitter(playerSprite.player.loc.position, Large));
					playerDead = true;
					spawner2.missleKill(j);
					enemyDeathSound.play();
					j = spawner2.missleCollect.size();
				}
			}


		}
		for (int j = 0; j < spawner3.missleCollect.size(); j++) {

			if (ofDistSquared(playerSprite.player.loc.position.x, playerSprite.player.loc.position.y, spawner3.missleCollect[j].loc.position.x, spawner3.missleCollect[j].loc.position.y)) {
				if (detectCollision(playerSprite.player.loc, spawner3.missleCollect[j].loc)) {
					explosionHolder.push_back(explosionEmitter(playerSprite.player.loc.position, Large));
					playerDead = true;
					spawner3.missleKill(j);
					enemyDeathSound.play();
					j = spawner3.missleCollect.size();
				}
			}


		}
	}
	

}



//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
