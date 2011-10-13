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
	ofxQTKitVideoPlayer* player;
	void playFile(string file);
	void update();
	void draw(float x, float y, float width, float height);
	float calculatedStartTime;
	bool triggeredPlay;
	string currentFile;
};

