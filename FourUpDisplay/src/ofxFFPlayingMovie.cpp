/*
 *  ofxFFPlayingMovie.cpp
 *  FourUpDisplay
 *
 *  Created by Jim on 10/10/11.
 *  Copyright 2011 FlightPhase. All rights reserved.
 *
 */

#include "ofxFFPlayingMovie.h"
void ofxFFPlayingMovie::playFile(string file){
	player->loadMovie(file, OFXQTVIDEOPLAYER_MODE_TEXTURE_ONLY);
	player->setLoopState(false);
	triggeredPlay = false;
	currentFile = file;
}

void ofxFFPlayingMovie::update(){
	if(ofGetElapsedTimef() > calculatedStartTime && !triggeredPlay){
		player->play();
		triggeredPlay = true;
	}
	player->update();
}

void ofxFFPlayingMovie::draw(float x, float y, float width, float height){
	if(triggeredPlay && player->isPlaying()){
		player->draw(x,y,width,height);
	}
}
