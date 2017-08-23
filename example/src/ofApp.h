#pragma once

#include "ofMain.h"
#include "ofxThreadedCommand.h"


// ofApp
//--------------------------------------------------------------------------------
class ofApp : public ofBaseApp
{
public:
  void setup();
  void draw();
  void mousePressed( int _x, int _y, int _button );
  
  ofxThreadedCommand command;
};
