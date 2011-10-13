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

void ofxFFPlayingMovie::setDrawRect(ofRectangle rect){
	
	//fit into the square based on the ratio
	bool squishHorizonal = rect.width / player->getWidth() > rect.height / player->getHeight();
	
	float convertedWidth,convertedHeight;
	if(squishHorizonal){
		convertedWidth = player->getWidth() * rect.height/player->getHeight();
		convertedHeight = rect.height;
	}
	else {
		convertedWidth = rect.width;
		convertedHeight = player->getHeight() * rect.width/player->getWidth();
	}
	
	currentDrawRect = ofRectangle(rect.x + rect.width/2 - convertedWidth/2,
								  rect.y + rect.height/2 - convertedHeight/2,
								  convertedWidth, convertedHeight);
	
	//currentDrawRect = rect;
}

void ofxFFPlayingMovie::draw(){
	if(triggeredPlay && player->isPlaying()){
		player->draw(currentDrawRect);
	}
//	if(!triggeredPlay){
//		playbutton.draw(currentDrawRect.x + currentDrawRect.width/2 - playbutton.getWidth()/2, 
//						currentDrawRect.y + currentDrawRect.height/2 - playbutton.getHeight()/2);
//	}
}
