#pragma once

#include "ofMain.h"
#include "ofxOpenCV.h"

static const int gWidth = 380 , gHeight = 240, margin = 2;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);

		ofVideoGrabber grabber;
		
		ofxCvColorImage RGB_IMAGE;
		ofxCvColorImage HSV_IMAGE;

		ofxCvGrayscaleImage hue;
		ofxCvGrayscaleImage sat;
		ofxCvGrayscaleImage val;
		ofxCvGrayscaleImage filtered;

		ofTrueTypeFont font;

		int currentSelection, logList;

		vector<int> selection;

		void keyPressed(int key);
};
