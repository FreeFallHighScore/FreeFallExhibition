/*
 *  ofxFFPlayingMovie.h
 *  FourUpDisplay
 *
 *  Created by Jim on 10/10/11.
 *  Copyright 2011 FlightPhase. All rights reserved.
 *
 */

#pragma once


#include "ofxQTKitVideoPlayer.h"

class ofxFFPlayingMovie {
  public:
	void playFile(string file);
	void update();
	void draw();
	void setDrawRect(ofRectangle rect);
	
	ofxQTKitVideoPlayer* player;
	ofRectangle currentDrawRect;
	ofImage playbutton;
	float calculatedStartTime;
	bool triggeredPlay;
	string currentFile;
};

