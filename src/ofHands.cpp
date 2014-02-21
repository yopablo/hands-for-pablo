#include "ofHands.h"
using namespace ofxCv;
using namespace cv;
//--------------------------------------------------------------
void ofHands::setup(){
    
    cam.initGrabber(320, 240);
    
    bIsRecording = false;
    mTimer.setup(3000);
    ofAddListener(mTimer.TIMER_COMPLETE, this, &ofHands::timerEnded);
    imitate(cam, mImg);
    mCurrentPos = -1;
    mSize = 0;
}

//--------------------------------------------------------------
void ofHands::update(){
    cam.update();
	
	if (cam.isFrameNew()){
        convertColor(cam, mImg, CV_RGB2GRAY);
        mImg.update();
        if(bIsRecording)
            mRecorder.addFrame(mImg);
    }
    
    if(mFileBuffer.size() > 0){
        mCurrentPos++;
        if(mCurrentPos >= mPlayers.size())
            mCurrentPos = 0;
    
        ofxImageSequence * fooPlayer = new ofxImageSequence();
        
        fooPlayer->loadSequence(mFileBuffer[0]);
        fooPlayer->setFrameRate(ofRandom(10, 24));
        mPlayers.push_front(fooPlayer);
        if(mPlayers.size() > ofGetWidth()/320*ofGetHeight()/240){
            ofxImageSequence * player = mPlayers.back();
            mPlayers.pop_back();
            delete player;
        }
        mFileBuffer.pop_front();
    }
}

void ofHands::timerEnded(int & args){
    bIsRecording = false;
    
    mFileBuffer.push_back(mCurrentFile);
    
    if(mRecorder.isThreadRunning() && mRecorder.q.size() == 0)
        mRecorder.stopThread();
    

}
//--------------------------------------------------------------
void ofHands::draw(){
    ofBackground(125);
    mImg.draw(0,0);
    
    ofSetColor(255);
    
    stringstream c;
    c << "Recording: " << bIsRecording << "\nThread running: " << mRecorder.isThreadRunning() <<  "\nQueue Size: " << mRecorder.q.size() << "\n\nPress 'r' to toggle recording.\nPress 't' to toggle worker thread." << endl;
    
    ofDrawBitmapString(c.str(), 650, 10);
    
    ofPushMatrix();
    int x = 0;
    int y = 0;
    for(int i = 0; i < mPlayers.size(); i++){
        mPlayers[i]->getFrameForTime(ofGetElapsedTimef())->draw(x, y);
        x+=320;
        if(x+320 > ofGetWidth()){
            x = 0;
            y+=240;
        }
    }
    ofPopMatrix();
    
    
}

void ofHands::exit(){
    mRecorder.waitForThread();
}

//--------------------------------------------------------------
void ofHands::keyPressed(int key){
    if(key == 'r' && !bIsRecording){
        
        mCurrentFile = ofGetTimestampString();
        ofDirectory::createDirectory(ofToDataPath(mCurrentFile));
        mRecorder.setPrefix(ofToDataPath(mCurrentFile+"/frame_"));
        mRecorder.setFormat("jpg");
        mTimer.start(false);
        if(!mRecorder.isThreadRunning())
            mRecorder.startThread(false, false);
        
        
        bIsRecording = !bIsRecording;
    }
    
    if(key == 't'){
        if(mRecorder.isThreadRunning()){
            mRecorder.stopThread();
        } else {
            mRecorder.startThread(false, true);
        }
    }
}

//--------------------------------------------------------------
void ofHands::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofHands::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofHands::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofHands::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofHands::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofHands::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofHands::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofHands::dragEvent(ofDragInfo dragInfo){
    
}