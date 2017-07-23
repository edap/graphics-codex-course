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

    PinholeCamera camera;
    image = initImage(160, 100);
    render(camera, image);
}

// C++ Ray Casting [_rn_rayCst] from http://graphicscodex.com
void ofApp::render(const PinholeCamera& camera, shared_ptr<ofImage>& image) const {
    const int width = int(image->getWidth());
    const int height = int(image->getHeight());

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            glm::vec3 P;
            glm::vec3 w;

            // Find the ray through (x, y) and the center of projection
            camera.getPrimaryRay(float(x) + 0.5f, float(y) + 0.5f, width, height, P, w);

            ofColor col= ofColor(12,12,255);
            image->setColor(x, y, L_i(P, w));
            //image->set(x, y, L_i(P, w));
        }
    }
    image->update();
}

// Debugging implementation that computes white if there is any surface on this ray and black
ofColor ofApp::L_i(const glm::vec3& X, const glm::vec3& wi) const{
    // Find the first intersection with the scene
    //const shared_ptr<Surfel>& s = findFirstIntersection(X, wi);

    //if (notNull(s)) {
        return ofColor(255,255,255);
    //} else {
        //return ofColor(0,0,0);
    //}
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
        //image->draw(10,10, 160, 100);
    }


    ofDrawBitmapString(ofToString(ofGetFrameRate(),0), 20, 20);
}

shared_ptr<ofImage> ofApp::initImage(int _width, int _height){
    shared_ptr<ofImage> img = std::make_shared<ofImage>();
    img->allocate(_width, _height, OF_IMAGE_COLOR);
    return img;
}

//--------------------------------------------------------------
void ofApp::update(){

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
