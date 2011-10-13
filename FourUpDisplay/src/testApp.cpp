#include "testApp.h"
#include "ofxXmlSettings.h"

//--------------------------------------------------------------
void testApp::setup(){

	ofEnableAlphaBlending();
	
	maxNumVideos = 4;
	numVideos = 1;
	
	ofSetFrameRate(30);
	ofToggleFullscreen();
	ofBackground(0, 0, 0);
	
	for(int i = 0; i < 4; i++){
		player[i] = new ofxFFPlayingMovie();
		player[i]->player = new ofxQTKitVideoPlayer();
	}
	
//	for(int i = 0; i < 2; i++){
//		player[i]->play();
//	}
	

	updateVideosFromXML();
	pickNewSet();
	
}


//--------------------------------------------------------------
void testApp::update(){
	bool shouldPickNewSet = true;
	for(int i = 0; i < numVideos; i++){
		player[i]->update();
		if(player[i]->player->	isPlaying()){
			shouldPickNewSet = false;
		}
	}
	
	if(shouldPickNewSet){
		pickNewSet();
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	int width = 853*.9;
	int height = 480*.9;
	
	for(int i = 0; i < numVideos; i++){
		player[i]->draw();
	}
	
	//debug
	ofSetColor(255, 0, 0);
	for(int i = 0; i <= numVideos; i++){
		ofLine(0,			 1.0*i/numVideos * ofGetHeight(), 
			   ofGetWidth(), 1.0*i/numVideos * ofGetHeight());
		
		ofLine(1.0*i/numVideos * ofGetWidth(), 0,
			   1.0*i/numVideos * ofGetWidth(), ofGetHeight() );
	}
	ofSetColor(255);
	
//	player[0]->draw(ofGetWidth()/4-width/2,ofGetHeight()/2-height/2,width,height);
//	player[1]->draw(ofGetWidth() - width - (ofGetWidth()/4-width/2),ofGetHeight()/2-height/2,width,height);	
//	player[2]->draw(853,480,853,480);
//	player[3]->draw(0,480,853,480);
	
}

void testApp::updateVideosFromXML(){
	ofxXmlSettings videoDescription;
	if(videoDescription.loadFile("videos.xml")){
		videoDescription.pushTag("vids");
		int numvids = videoDescription.getNumTags("video");
		for(int i = 0; i < numvids; i++){
			videoDescription.pushTag("video", i);
			
			VideoOption* option = new VideoOption();
			option->file = videoDescription.getValue("file", "");
			option->dropPoint = videoDescription.getValue("drop", 0)/30.;
			option->loopsAgoPlayed = 10;
			
			cout << "vid at " << options.size() << " is " << option->file << endl;
			
			options.push_back( option );

			videoDescription.popTag();
		}
		
	}
	cout << "loaded " << options.size() << " videos from xml" << endl;
}

void testApp::pickNewSet(){
	
	//chance to change the number of videos
	if(ofRandomuf() > .8){
		numVideos = (rand() % maxNumVideos) + 1;
	}
	numVideos =4 ;
	//select 4 new videos, ones that haven't been seen for a while
	int currentSelections[numVideos];
	for(int i = 0; i < numVideos; i++){
		currentSelections[i] = -1;
	}
	
	for(int v = 0; v < numVideos; v++){
		int validIndex = 0;
		int tries = 0;
		do {
			validIndex = rand() % options.size();
			bool alreadySelected = false;
			for(int s = 0; s < v; s++){
				if(currentSelections[s] == validIndex){
					cout << "already selected " << s << endl;
					alreadySelected = true;
				}
			}
			if(!alreadySelected && options[validIndex]->loopsAgoPlayed > 1){
				cout << "Accepting movie " << validIndex << " for " << options[validIndex]->file << endl;
				break;
			}

		} while (tries++ < 100);
		
		cout << "current file is " << player[v]->currentFile << " new file is " << options[validIndex]->file << endl;
		
		currentSelections[v] = validIndex;
		player[v]->playFile(options[validIndex]->file);
		options[validIndex]->loopsAgoPlayed = 0;
	}
	
	//update pick count
	for(int i = 0; i < options.size(); i++){
		options[i]->loopsAgoPlayed++;
	}
	
	for(int i = 0; i < numVideos; i++){
		options[ currentSelections[i] ]->loopsAgoPlayed = 0;
	}
	
	//calculate offset times
	float currentTime = ofGetElapsedTimef();
	float maxBuildupTime = 0;
	for(int i = 0; i < numVideos; i++){
		if(options[ currentSelections[i] ]->dropPoint > maxBuildupTime){
			maxBuildupTime = options[ currentSelections[i] ]->dropPoint;
		}
	}
	
	int maxIndex;
	float maxDropLength = 0;
	for(int i = 0; i < numVideos; i++){
		player[i]->calculatedStartTime = currentTime + maxBuildupTime - options[ currentSelections[i] ]->dropPoint;
		float dropLength = player[i]->player->getDuration() - options[ currentSelections[i] ]->dropPoint;
		if(dropLength > maxDropLength){
			maxIndex = i;
			maxDropLength = dropLength;
		}
	}
	
	//turn off sound
	for(int i = 0; i < numVideos; i++){
		player[i]->player->setVolume(0);
	}
	player[maxIndex]->player->setVolume(1);
	
	vector<bool> usedgridspots;
	for(int i = 0; i < numVideos*numVideos; i++) {
		usedgridspots.push_back(false);
	}
	
	for(int i = 0; i < numVideos; i++){
		int gridSpot;
		do{
			gridSpot = rand() % usedgridspots.size();
		} while(usedgridspots[gridSpot]);
		
		usedgridspots[gridSpot] = true;
		
		int x = gridSpot%numVideos;
		int y = gridSpot/numVideos;
		int width = 1.0*ofGetWidth()/numVideos;
		int height = 1.0*ofGetHeight()/numVideos;

		player[i]->setDrawRect( ofRectangle(x*width, y*height, width, height) );
	}
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == ' '){
		updateVideosFromXML();
	}
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}
