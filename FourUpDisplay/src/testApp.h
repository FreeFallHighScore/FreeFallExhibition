#pragma once

#include "ofMain.h"
#include "ofxFFPlayingMovie.h"

typedef struct {
	string file;
	float dropPoint;
	int loopsAgoPlayed;
} VideoOption;

class testApp : public ofBaseApp{

	public:
	void setup();
	void update();
	void draw();

	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
		
	ofxFFPlayingMovie* player[4];

	void updateVideosFromXML();
	void pickNewSet();
	
	int numVideos;
	vector<VideoOption*> options;
};
