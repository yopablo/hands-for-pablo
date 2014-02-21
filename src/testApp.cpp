#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    cam.initGrabber(320, 240);
    
    bIsRecording = false;
    mTimer.setup(3000);
    ofAddListener(mTimer.TIMER_COMPLETE, this, &testApp::timerEnded);
    mImg.allocate(320, 240, OF_IMAGE_GRAYSCALE);
    mPlayers.resize((ofGetWidth()/cam.getWidth())*(ofGetHeight()/cam.getHeight()));
    
}

//--------------------------------------------------------------
void testApp::update(){
    cam.update();
	
	if (cam.isFrameNew() && bIsRecording){
        mRecorder.addFrame(mImg);
    }
    
    if(mFileBuffer.size() > 0){
        ofxImageSequence * fooSequence = mPlayers[mCurrentPos];
        fooSequence->loadSequence(ofToDataPath(mFileBuffer.front()));
        fooSequence->setFrameRate(ofRandom(10, 24));
        mFileBuffer.pop_front();
    }
}

void testApp::timerEnded(int & args){
    bIsRecording = false;
    
    mFileBuffer.push_back(mCurrentFile);
    
    if(mRecorder.isThreadRunning() && mRecorder.q.size() == 0)
        mRecorder.stopThread();
}
//--------------------------------------------------------------
void testApp::draw(){
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

void testApp::exit(){
    mRecorder.waitForThread();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
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
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
    
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