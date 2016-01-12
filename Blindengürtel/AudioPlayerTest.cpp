class AudioPlayerTest : public CppUnit::TestCase { 

private:
	AudioPlayer* ap1;
	AudioPlayer* ap2;
	AudioPlayer* ap3;
	AudioPlayer* ap4;
	
public: 
	void setup(){
		ap1 = new AudioPlayer();
		ap2 = new AudioPlayer();
		ap3 = new AudioPlayer();
		ap4 = new AudioPlayer();
		ap5 = new AudioPlayer();
		  
		ap1->sound->soundIndex = -1;
		ap2->sound->soundIndex = 0;
		ap3->sound->soundIndex = 1;
		ap4->sound->soundIndex = 2;
		ap5->sound->soundIndex = 3;
		
		double distances[] = {1,2,3};
	}
	
	void tearDown(){
		delete ap1;
		delete ap2;
		delete ap3;
		delete ap4;
		delete ap5;
	}	
	
	void testChooseSoundPath(){
		CPPUNIT_ASSERT( ap1.chooseSoundPath == NO_SOUND );
		CPPUNIT_ASSERT( ap2.chooseSoundPath == SOUND_UPPER );
		CPPUNIT_ASSERT( ap3.chooseSoundPath == SOUND_MID );
		CPPUNIT_ASSERT( ap4.chooseSoundPath == SOUND_LOWER );
		CPPUNIT_ASSERT( ap5.chooseSoundPath == ERROR_SOUND );
	}
	
	void testChooseSoundIndex(){
		
	}
  

  
  void runTest() {
	CPPUNIT_ASSERT( chooseSoundPath() == 
    CPPUNIT_ASSERT( Complex (10, 1) == Complex (10, 1) );
    CPPUNIT_ASSERT( !(Complex (1, 1) == Complex (2, 2)) );
  }
};

