#ifndef AUDIOPLAYERTEST_H
#define AUDIOPLAYERTEST_H

#include "AudioPlayer.h"
#include <cppunit/extensions/HelperMacros.h>

///Includes unittest for the AudioPlayer class.
class AudioPlayerTest : public CppUnit::TestFixture
{ 
	///Initializes the TestSuite called AudioPlayerTest.
	CPPUNIT_TEST_SUITE( AudioPlayerTest );
	
	///Calls the unittest for the method testChooseSoundPath.
	CPPUNIT_TEST( testChooseSoundPath );
	///Calls the unittest for the method testChooseSoundPath.
	CPPUNIT_TEST( testChooseSoundIndex );

	///Ends the TestSuite.
	CPPUNIT_TEST_SUITE_END();

	
public: 
	void setUp();
	void tearDown();
	
	void testChooseSoundPath();
	void testChooseSoundIndex();
  
private:
	///AudioPlayer object.
	AudioPlayer* ap1;
	///AudioPlayer object.
	AudioPlayer* ap2;
	///AudioPlayer object.
	AudioPlayer* ap3;
	///AudioPlayer object.
	AudioPlayer* ap4;
	///AudioPlayer object.
	AudioPlayer* ap5;
	

};

#endif
