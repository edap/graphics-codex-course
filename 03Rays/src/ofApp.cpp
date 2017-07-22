#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //addEventListener();
    //gui.setup();
    //gui.add("render", render);
    ofBackground(255,255,255);
    ofSetVerticalSync(true);
    ofEnableDepthTest();

    model.loadModel("CornellBox-Original.obj", 20);
    model.setRotation(0, 180, 0, 0, 1);
    model.setPosition(0, -300, -460);

    initImage(160, 100);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    if (show3DScene) {
        cam.begin();
        //light.enable();
        //light.draw();
        model.drawFaces();
        //light.disable();
        ofDrawAxis(100);
        myCam.draw();
        cam.end();
    } else {
        img.draw(10,10, 160, 100);
    }


    ofDrawBitmapString(ofToString(ofGetFrameRate(),0), 20, 20);
}

void ofApp::initImage(int _width, int _height){
    img.allocate(_width, _height, OF_IMAGE_COLOR);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
