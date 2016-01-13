#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/CompilerOutputter.h>
#include "AudioPlayerTest.h"


using namespace std;

CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( AudioPlayerTest, "AudioPlayerTest" );

void AudioPlayerTest::setUp(){
	ap1 = new AudioPlayer();
	ap2 = new AudioPlayer();
	ap3 = new AudioPlayer();
	ap4 = new AudioPlayer();
	ap5 = new AudioPlayer();
		  
	ap1->getSoundPair()->soundIndex = -1;
	ap2->getSoundPair()->soundIndex = 0;
	ap3->getSoundPair()->soundIndex = 1;
	ap4->getSoundPair()->soundIndex = 2;
	ap5->getSoundPair()->soundIndex = 3;
	
	
}

void AudioPlayerTest::tearDown(){
	delete ap1;
	delete ap2;
	delete ap3;
	delete ap4;
	delete ap5;
}	


void AudioPlayerTest::testChooseSoundPath(){
	string noSound = NO_SOUND;
	string upperSound = SOUND_UPPER;
	string midSound = SOUND_MID;
	string lowSound = SOUND_LOWER;
	string errSound = ERROR_SOUND;
	
	CPPUNIT_ASSERT_EQUAL( ap1->chooseSoundPath(), noSound );
	CPPUNIT_ASSERT_EQUAL( ap2->chooseSoundPath(), upperSound );
	CPPUNIT_ASSERT_EQUAL( ap3->chooseSoundPath(), midSound );
	CPPUNIT_ASSERT_EQUAL( ap4->chooseSoundPath(), lowSound );
	CPPUNIT_ASSERT_EQUAL( ap5->chooseSoundPath(), errSound );
	
}

void AudioPlayerTest::testChooseSoundIndex(){
	int senAmount = 3;
	
	double distances1[] = {1,75,30};
	double distances2[] = {152,150,151};
	double distances3[] = {151,152,-1};
	
	
	CPPUNIT_ASSERT_EQUAL( ap1->chooseSoundindex(distances1, senAmount), 0 ); //Randtest unten
	CPPUNIT_ASSERT_EQUAL( ap1->chooseSoundindex(distances2, senAmount), 1 ); //Randtest oben
	CPPUNIT_ASSERT_EQUAL( ap1->chooseSoundindex(distances3, senAmount), -1 ); //Randtest außen
		
}

 CppUnit::Test *suite()
    {
      CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();

      registry.registerFactory( &CppUnit::TestFactoryRegistry::getRegistry( "AudioPlayerTest" ) );
      return registry.makeTest();
    }


    int main( int argc, char* argv[] )
    {
      // if command line contains "-selftest" then this is the post build check
      // => the output must be in the compiler error format.
      bool selfTest = (argc > 1)  && (std::string("-selftest") == argv[1]);

      CppUnit::TextUi::TestRunner runner;
      runner.addTest( suite() );   // Add the top suite to the test runner

      if ( selfTest )
      { // Change the default outputter to a compiler error format outputter
        // The test runner owns the new outputter.
        runner.setOutputter( CppUnit::CompilerOutputter::defaultOutputter(&runner.result(), std::cerr ) );                                                        
      }

      // Run the test.
      bool wasSucessful = runner.run( "" );

      // Return error code 1 if any tests failed.
      return wasSucessful ? 0 : 1;
    }
