#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
//#include "ofxGui"
#include "PinholeCamera.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    shared_ptr<ofImage> initImage(int width, int height);
    shared_ptr<ofImage> image;
    void render(const PinholeCamera& camera, shared_ptr<ofImage>& image) const;

    ofxAssimpModelLoader model;
    //ofLight	light;

    // stores the info on the current file.
    string curFileInfo;

    //boolean to toggle help text
    bool bHelpText;
    ofEasyCam cam;
    bool show3DScene = false;

    //ofxGui gui;
    //ofxButton render;

};
