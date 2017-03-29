#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    light.setup();
    light.setPosition(-100, 200,0);
    for(unsigned int i =0; i< nSteps; i++){
        auto step = ofBoxPrimitive(30, stepHeight, 100);
        step.pan(i*10);
        step.move(ofVec3f(0,i*stepHeight,0));
        stair.push_back(step);
    }
    ofEnableDepthTest();

    ofDisableArbTex();
    ofLoadImage(bark,"bark.jpg");
    bark.setTextureWrap(GL_REPEAT, GL_REPEAT);
    bark.generateMipmap(); // it creates a mipmap out of that image
    bark.setTextureMinMagFilter(GL_LINEAR_MIPMAP_LINEAR, GL_NEAREST); //activate mipmap filtering once texture has been loaded
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    camera.begin();
    //ofDrawAxis(100.0);
    bark.bind();
    for(auto s : stair){
        s.draw();
    }
    bark.unbind();
    camera.end();
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
