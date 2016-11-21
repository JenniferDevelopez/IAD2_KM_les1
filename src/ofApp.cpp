
#include "ofApp.h"


void ofApp::setup()
{
	ofBackground(50, 20, 20);
	font.loadFont("EXO_BLACK.otf", 8);

	grabber.setup(gWidth, gHeight, true);

	// RGB-HSV-FILTERED
	RGB_IMAGE.allocate(gWidth, gHeight);
	HSV_IMAGE.allocate(gWidth, gHeight);
	filtered.allocate(gWidth, gHeight);

	// HSV CHANNELS
	hue.allocate(gWidth, gHeight);
	sat.allocate(gWidth, gHeight);
	val.allocate(gWidth, gHeight);

	currentSelection = 0;
	logList = 0;
}

void ofApp::update()
{
	grabber.update();

	if (grabber.isFrameNew())
	{
		RGB_IMAGE.setFromPixels(grabber.getPixels().getData(), gWidth, gHeight);
		RGB_IMAGE.mirror(false, true);

		HSV_IMAGE = RGB_IMAGE;
		HSV_IMAGE.convertRgbToHsv();
		HSV_IMAGE.convertToGrayscalePlanarImages(hue, sat, val);

		for (int i = 0; i < gWidth * gHeight; i++) // For each pixel..
		{
			if (Selection.size() != 0)
			{
				for (int x = 0; x < Selection.size(); x++)  // For each value in the selection list..
				{
					if (ofInRange(hue.getPixels()[x], Selection[x] - margin, Selection[x] + margin)) // Within the range of 'margin'
					{
						filtered.getPixels()[x] = 255; // Make it white
					}
					else
					{
						filtered.getPixels()[x] = 0; // Or black..
					}
				}
			}
		}
		// Flag Image Changed? Figure this out later...
		filtered.flagImageChanged();
	}

	if (logList == 1)
	{
		cout << "okay..." << endl;
		if (!Selection.size())
		{
			cout << "list is empty!" << endl;
		}
		else
		{
			for (int i = 0; i < Selection.size(); i++)
			{
				cout << "selected hue [" << i << "]: )" << Selection[i] << endl;
				if (i == Selection.size())
				{
					logList != logList;
				}
			}
		}
	}

}

void ofApp::draw()
{
	HSV_IMAGE.draw(50, 50);
	RGB_IMAGE.draw(380 + 50 + 20, 50);
	filtered.draw(740 + 50 + 40, 50);

	hue.draw(50, 240 + 50 + 20);
	sat.draw(380 + 50 + 20, 240 + 50 + 20);
	val.draw(740 + 50 + 20, 240 + 50 + 20);

	// LOG CURRENT VALUE ON SCREEN
	font.drawString("HUE VALUE: " + ofToString(currentSelection), 500, ofGetHeight() - 500);
}

void ofApp::mousePressed(int x, int y, int button)
{
}

void ofApp::mouseReleased(int x, int y, int button)
{
}

void ofApp::keyPressed(int key) 
{
	if (key == 'c')
	{
		Selection.clear();
	}
	if (key == 'x')
	{
		// Get current selection.;
		currentSelection = hue.getPixels()[ofGetMouseY() * gWidth + ofGetMouseY()];
		// Append current selection to list.
		Selection.push_back(currentSelection);
	}
	if (key == 'l') 
	{
		cout << "First Input:" << logList << endl;
		if (logList == 0) 
		{
			logList++;
		}
		else
		{
			logList--;
		}
		cout << "second Input:" << logList << endl;

	}
}
