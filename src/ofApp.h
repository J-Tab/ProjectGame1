#pragma once
#include "ofxGui.h"
#include "ofMain.h"
#include "sprite.h"
#include "spriteSystem.h"
#include "emitter.h"



class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	glm::vec3 curveEval(float x, float scale, float cycles);

	
	
	
	// detect a collision between the two inputed sprites
	// detect a collision between the two inputed sprite
	bool detectCollision(sprite a, sprite b);


	// Part of the update function, checks similar sprites to see if they are together.
	//COLLISION CURRENTLY UNOPTIMAL
	void collisionUpdate();


	// Search for potential sprite collision using binary search, return -1 if no match
	


	

	// rotate vertices (vin) by "angle" and return result in (vout).
	//
	void rotate(const vector<glm::vec3> &vin, vector<glm::vec3> &vout, float angle);


	// application data

	glm::vec3 lastMouse;   // location of where mouse moved last (when dragging)
	bool startGame = false;
	float playerSpeed = 5;
	int MissleTimer = 0;

	int Timer = 0;


	// UI control data
	//
	bool bFullscreen = false;
	bool bCtrlKeyDown = false;
	bool bDrag = false;
	bool debugEnable = false;
	bool bSpaceKeyDown = false;

	//Player Controls
	//
	bool bDownKeyDown = false;
	bool bUpKeyDown = false;
	bool bLeftKeyDown = false;
	bool bRightKeyDown = false;

	emitter spawner1;

	int fireRate = 40;

	//Debug data
	//
	ofxPanel gui;
	ofxFloatSlider angleSlider;
	ofxToggle lineButton;
	ofxToggle enemyHitbox;
	ofxFloatSlider fireSlider;
	ofxFloatSlider spawnRate;
	ofxFloatSlider enemySpeed;


	ofSoundPlayer playerFire;
	ofSoundPlayer enemyDeathSound;
	//Sprite Data
	spriteSystem playerSprite;
	ofImage background;

};
