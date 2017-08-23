#include "ofApp.h"

// draw
//------------------------------------------------------------
void ofApp::draw()
{
  ofBackground( ofColor::fromHsb( ofGetFrameNum() % 256, 200, 255 ) );
}


// mousePressed
//------------------------------------------------------------
void ofApp::mousePressed( int _x, int _y , int _button )
{
  // save screenshot to data folder
  if( _button == 0 )
  {
    ofSaveScreen( ofGetTimestampString() + ".png" );
  }
  // remove all png images
  else if( _button == 2 )
  {
    ofDirectory dir( "" );
    
    string cmd = "rm " + dir.getAbsolutePath() + "/*.png";
    cout << cmd << endl;
    command.call( cmd );
  }
}
