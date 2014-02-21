#include "testApp.h"
#include "ofAppGLFWWindow.h"
//--------------------------------------------------------------
int main(){
    ofAppGLFWWindow window;
    window.setDoubleBuffering(true);
    window.setNumSamples(4);
	//ofAppGlutWindow window; // create a window
	// set width, height, mode (OF_WINDOW or OF_FULLSCREEN)
	ofSetupOpenGL(1024, 768, OF_WINDOW);
	ofRunApp(new testApp()); // start the app
}
