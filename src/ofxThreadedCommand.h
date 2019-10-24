//
//  ofxThreadedCommand.h
//
//  Based on https://gist.github.com/robotconscience/2554110
//

#pragma once
#include "ofThread.h"

class ofxThreadedCommand : private ofThread
{
public:
  ofEvent< string > commandComplete;
  
  bool lock()
  {
    return ofThread::lock();
  }
  
  void unlock()
  {
    ofThread::unlock();
  }

  bool isRunning()
  {
    return isThreadRunning();
  }
  
  void call( string _command )
  {
    cmd = _command;
    stopThread();
    startThread();
  }

  // CALL THIS DIRECTLY FOR BLOCKING COMMAND
  // thanks to: http://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c
  std::string exec( char* _cmd )
  {
#ifdef TARGET_OSX
    FILE* pipe = popen( _cmd, "r" );
#endif
#ifdef TARGET_WIN32
    FILE* pipe = _popen( _cmd, "r" );
#endif
    if( !pipe ) return "ERROR";
    char buffer[ 128 ];
    std::string result = "";
    while( !feof( pipe ) )
    {
      if( fgets( buffer, 128, pipe ) != NULL ) result += buffer;
    }
#ifdef TARGET_OSX
    pclose( pipe );
#endif
#ifdef TARGET_WIN32
    _pclose( pipe );
#endif
    return result;
  }

private:
  void threadedFunction()
  {
    ofLog( OF_LOG_VERBOSE, "[ofxThreadedCommand] call : " + cmd );
    string result = exec( ( char* )cmd.c_str() );
    ofLog( OF_LOG_VERBOSE, "[ofxThreadedCommand] result : " + result );
    stopThread();
    ofNotifyEvent( commandComplete, result, this );
  }

  string cmd;
};
