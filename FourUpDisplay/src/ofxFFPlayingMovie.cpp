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
	playbutton.loadImage("youtube_play.png");
}

void ofxFFPlayingMovie::update(){
	if(ofGetElapsedTimef() > calculatedStartTime && !triggeredPlay){
		player->play();
		triggeredPlay = true;
	}
	player->update();
}

void ofxFFPlayingMovie::draw(){
	if(triggeredPlay && player->isPlaying()){
		player->draw(currentDrawRect);
	}
	if(!triggeredPlay){
		playbutton.draw(currentDrawRect.x + currentDrawRect.width/2 - playbutton.getWidth()/2, 
						currentDrawRect.y + currentDrawRect.height/2 - playbutton.getHeight()/2);
	}
}
