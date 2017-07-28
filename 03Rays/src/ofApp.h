#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "PinholeCamera.h"
#include "ofxDatGui.h"
#include "Surfel.h"
#include "RayCaster.h"

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

    void onResolutionEvent(ofxDatGuiDropdownEvent e);
    void onRenderEvent(ofxDatGuiButtonEvent e);
    void onIndRaysEvent(ofxDatGuiSliderEvent e);


    void startRender();
    shared_ptr<ofImage> initImage(int width, int height);

    shared_ptr<ofImage> image;
    ofxDatGui* gui;
    ofBoxPrimitive box; //debugging box
    ofxAssimpModelLoader model;
    //ofLight	light;



    //debug 3dScene
    ofMaterial material;
    ofEasyCam cam;
    bool show3DScene = false;

};
