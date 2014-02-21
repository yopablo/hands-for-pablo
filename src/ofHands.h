#pragma once

#include "ofMain.h"
#include "ofxImageSequenceRecorder.h"
#include "ofxImageSequence.h"
#include "ofxSimpleTimer.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
class ofHands : public ofBaseApp{
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
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void exit();
    
    void timerEnded(int & args);
    

    ofxSimpleTimer mTimer;
    ofxImageSequenceRecorder mRecorder;
    string mCurrentFile;
    bool bIsRecording;
    deque<string> mFileBuffer;
    ofVideoGrabber cam;
    ofImage mImg;
    deque<ofxImageSequence*> mPlayers;
    deque<float> mPos;
    int mCurrentPos;
    int mSize;
};
