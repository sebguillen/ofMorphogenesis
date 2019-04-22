#include "ofApp.h"

//--------------------------------------------------------------
// Belousov Zhabotinsky reaction
// Made with the ofxReactionDiffusion addon
// Imitate 'Turing's pattern' of morphogenesis
// Morphogenesis occurs at cell level
// It is responsible for the creation of patters on the skin of animals, like for instance the patterns on the shell of a mollusc or the striped on the fur of a zebra
// rd = reaction-diffusion

void ofApp::setup(){
    showGui = false;
    ofSetBackgroundColor(0);
    ofSetFrameRate(60);

    rd.allocate(ofGetWidth(), ofGetHeight());
    
    gui.setup();
    gui.setName("Parameters");
    gui.add(mode.setup("Mode", 2, 0, 2));
    gui.add(passes.setup("Passes", rd.getPasses(), 0.01, 2));
    gui.add(clearButton.setup("Clear"));
    clearButton.addListener(this, &ofApp::clear);

// Gui parameters
    gui.add(bz.setup());
    bz.setName("Belousov Zhabotinsky");
    bz.add(alpha.setup("Alpha", rd.getAlpha(), -5.0, 5.0));
    bz.add(beta.setup("Beta", rd.getBeta(), -5.0, 5.0));
    bz.add(gamma.setup("Gamma", rd.getGamma(), -5.0, 5.0));
    
// Colours parameters
    colors.setup();
    colors.setPosition(ofGetWidth() - colors.getWidth(), 0);
    colors.setName("Colors");
    colors.add(color1.setup("Color 1", 0.0 , 0, 1.0));
    colors.add(thresh1.setup("Thresh 1", 0.0 , 0, 1.0));
    colors.add(color2.setup("Color 2", 0.25, 0, 1.0));
    colors.add(thresh2.setup("Thresh 2", 0.2 , 0, 1.0));
    colors.add(color3.setup("Color 3", 0.5 , 0, 1.0));
    colors.add(thresh3.setup("Thresh 3", 0.4 , 0, 1.0));
    colors.add(color4.setup("Color 4", 0.75, 0, 1.0));
    colors.add(thresh4.setup("Thresh 4", 0.6 , 0, 1.0));
    colors.add(color5.setup("Color 5", 1.0 , 0, 1.0));
    colors.add(thresh5.setup("Thresh 5", 0.8 , 0, 1.0));
    
    color1 = rd.getColor1();
    color2 = rd.getColor2();
    color3 = rd.getColor3();
    color4 = rd.getColor4();
    color5 = rd.getColor5();
}

void ofApp::clear() {
    rd.clearAll();
}

//--------------------------------------------------------------
void ofApp::update(){
    
// Set Modes
    rd.setPasses(passes);
    rd.setMode(RD_MODE_BELOUSOV_ZHABOTINSKY);
    rd.setBzParams(alpha, beta, gamma);

// Set colours
    rd.setColor1(color1);
    rd.setColor1Threshold(thresh1);
    rd.setColor2(color2);
    rd.setColor2Threshold(thresh2);
    rd.setColor3(color3);
    rd.setColor3Threshold(thresh3);
    rd.setColor4(color4);
    rd.setColor4Threshold(thresh4);
    rd.setColor5(color5);
    rd.setColor5Threshold(thresh5);
   
// Update
    rd.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
// Change coordinates and radius
    float time = ofGetElapsedTimef();
    float x = ofGetWidth() * (ofNoise(time * 0.4));
    float y = ofGetHeight() * (ofNoise(time * 0.6));
    float radius = 5;
    rd.addSource(x, y, radius);

// Animate variables
    float t = ofGetElapsedTimef();
    float val = ofNoise(time);
    float val_2 = ofNoise(time * 0.8);
    float val_3 = ofNoise(time);
    passes = ofMap (val, -1, 1, 0, 2);
    gamma = ofMap (val_3, -1, 1, -10, 5);
    alpha = ofMap (val_2, -1, 1, 0, 0.2);
    
// Draw reaction
    rd.draw();
    
// Show Gui
    if (showGui) {
        gui.draw();
        colors.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's'){
        showGui = !showGui;
    }
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
