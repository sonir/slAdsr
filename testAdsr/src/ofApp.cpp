#include "ofApp.h"

using namespace std;

//--------------------------------------------------------------
void ofApp::setup(){

    //SetupScreen
    ofBackground(0);
    ofSetCircleResolution(50);
    
    

    
    adsr_t a;
    a.attack = 1500;
    a.decay = 1000;
    a.sustain = 0.3f;
    a.duration = 600;
    a.release = 1000;

    adsr.setup(a);
    adsr.exponential = true;

    
    adsr.bang();
    
}

//--------------------------------------------------------------
void ofApp::update(){

    val = adsr.update();
    cout << val << endl;

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofSetColor(255*val);
    ofCircle(ofGetWidth()/2.0f, ofGetHeight()/2.0f, 500.0f*val);

    ofDrawBitmapString("push \"b\" key to bang", 10, 20);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if(key=='b')adsr.bang();
    
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
