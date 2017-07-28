#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255,255,255);
    ofSetVerticalSync(true);
    ofEnableDepthTest();

    model.loadModel("CornellBox-Original.obj", 20);
    model.setRotation(0, 180, 0, 0, 1);
    model.setPosition(0, -300, -460);
    vector<string> options = {"1x1", "320x200", "640x400",};

    // instantiate and position the gui //
    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );
    gui->setAutoDraw(false);
    gui->addTextInput("message", "Ray Casting");
    gui->addDropdown("Resolution", options);
    gui->addSlider("indirect rays per pixel", 0, 2048);
    gui->onDropdownEvent(this, &ofApp::onResolutionEvent);
    gui->onButtonEvent(this, &ofApp::onRenderEvent);
    gui->onSliderEvent(this, &ofApp::onIndRaysEvent);

    startRender();
}

void ofApp::startRender(){
    PinholeCamera camera;
    image = initImage(160, 100);
    RayCaster rayCaster;
    rayCaster.traceImage(camera, image);
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
        cam.end();
    } else {

        image->draw(10,10, 160, 100);
        ofDisableDepthTest();
        gui->draw();
        ofEnableDepthTest();
        //image->draw(10,10, 160, 100);
    }


    ofDrawBitmapString(ofToString(ofGetFrameRate(),0), 20, 20);
}

shared_ptr<ofImage> ofApp::initImage(int _width, int _height){
    shared_ptr<ofImage> img = std::make_shared<ofImage>();
    img->allocate(_width, _height, OF_IMAGE_COLOR);
    return img;
}

void ofApp::onResolutionEvent(ofxDatGuiDropdownEvent e){
    cout << e.child << endl;
}

void ofApp::onRenderEvent(ofxDatGuiButtonEvent e){
    cout << e.target << endl;
    startRender();
}

void ofApp::onIndRaysEvent(ofxDatGuiSliderEvent e){
    cout << "onSliderEvent: " << e.target->getLabel() << " "; e.target->printValue();
    if (e.target->is("datgui opacity")) gui->setOpacity(e.scale);
}

//--------------------------------------------------------------
void ofApp::update(){
    gui->update();
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
