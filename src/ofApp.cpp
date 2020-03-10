#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	playerFire.load("Fire.mp3");
	playerFire.setMultiPlay(true);
	playerSprite.player.img.load("Player.png");
	background.load("placeHolderBackGround.jpg");
	playerSprite.player.loc.position = glm::vec3(ofGetWidth() / 2.0, ofGetHeight() / 2.0, 0);
	gui.setup();
	gui.add(angleSlider.setup("angle", 0, 0, 5));
	gui.add(fireSlider.setup("firespeed", 5, 1, 10));
	gui.add(lineButton.setup("Missle Line toggle", false));

	// Exam;ple on how to add elements to a vector<>
	// Store the vertices to the triangle relative to origin (0, 0, 0);
	// The triangle is moveable in that we add these vertices to it's
	// position to get screen space coordinates (for drawing).
	//
	playerSprite.player.loc.verts.push_back(glm::vec3(100, -100, 0));
	playerSprite.player.loc.verts.push_back(glm::vec3(0, 100, 0));
	playerSprite.player.loc.verts.push_back(glm::vec3(-100, -100, 0));
	ofSetBackgroundColor(ofColor::black);
}

//--------------------------------------------------------------
void ofApp::update() {
	//Determine next postion of the player by buttons pressed
	if (bSpaceKeyDown) {
		if (MissleTimer < 0) {
			playerFire.play();
			float x = angleSlider;
			playerSprite.addMissle(playerSprite.missleUp(), x,fireSlider);
			MissleTimer = 30;
		}
		else {
			MissleTimer--;
		}
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


	//Update missles
	playerSprite.missleUpdate();
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
	

		// draw player in screen space (we need to add the position to get screen coordinates)
		//


		ofPushMatrix();
		glm::mat4 m = glm::translate(glm::mat4(1.0), glm::vec3(playerSprite.player.loc.position));
		ofMultMatrix(m);
		ofSetColor(255, 255, 255);
		playerSprite.player.img.draw(-50, -50, 100, 100);
		ofPopMatrix();

		playerSprite.missleDraw(lineButton);
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
		else {
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
		MissleTimer = 0;
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

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
