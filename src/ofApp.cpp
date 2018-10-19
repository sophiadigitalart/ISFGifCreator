#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0);
	ofSetLogLevel(OF_LOG_VERBOSE);
	// gif
	frameW = 120;
	frameH = 68;

	gifEncoder.setup(frameW, frameH, .25, 256);
	ofAddListener(ofxGifEncoder::OFX_GIF_SAVE_FINISHED, this, &ofApp::onGifSaved);
	vid.initGrabber(frameW, frameH);
	rgbaFbo.allocate(frameW, frameH, GL_RGB);

	
	isf.setup(frameW, frameH, GL_RGB32F);
	isf.load("shader.fs");
	//isf.load("isf-test.fs");

	isf.setImage("inputImage", vid.getTextureReference());

}
void ofApp::onGifSaved(string & fileName) {
	cout << "gif saved as " << fileName << endl;
	ofLogNotice("onGifSaved: " + fileName);
	gifEncoder.reset();
	ofLogNotice("onGifSaved reset");
}
void ofApp::captureFrame() {

	ofPixels fboPixels;
	rgbaFbo.readToPixels(fboPixels);
	gifEncoder.addFrame(fboPixels.getPixels(), frameW, frameH);

	//gifEncoder.addFrame(fbo.)
	ofTexture * tx = new ofTexture();
	tx->allocate(frameW, frameH, GL_RGB);
	// tx->loadData(vid.getPixels(), GL_RGB);
	// nope! tx = &rgbaFbo.getTextureReference();
	tx->loadData(fboPixels, GL_RGB);
	txs.push_back(tx);

	nFrames++;
}
//--------------------------------------------------------------
void ofApp::update() {
	vid.update();
	float t = ofGetElapsedTimef() * 2;
	// isf.setParam<float>("blurAmount", ofNoise(1, 0, 0, t) * 1.5);
	//isf.setUniform("blurAmount", (double)ofNoise(1, 0, 0, t) * 1.5);
	isf.update();
	ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------------------------------------------------------------
void ofApp::draw() {
	rgbaFbo.begin();
	ofClear(0, 0, 0, 1);
	isf.draw(0, 0);
	rgbaFbo.end();
	rgbaFbo.draw(460, 200);
	for (int i = 0; i < nFrames; i++) {
		txs[i]->draw(i* (frameW / 2 + 5), frameH, frameW / 2, frameH / 2);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	switch (key) {
	case 'f':
		ofToggleFullscreen();
		break;
	case ' ':
		captureFrame();
		break;
	case 's':
		cout << "start saving\n" << endl;
		gifEncoder.save("out.gif");
		break;
	default:
		break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
