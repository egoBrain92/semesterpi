#include <SFML/Audio.hpp>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <iostream>

int main()
{



//while(1){
pid_t pid = fork();

if (pid == 0){
sf::Sound sound;
sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("NonStandard2.wav")){
	std::cout<<"error"<<std::endl;
        return -1;
    }
	while(1){
	
    sound.setBuffer(buffer);
	
    sound.play();
	std::cout<<sound.getStatus()<<std::endl;
    usleep(500000);
    sound.stop();
	std::cout<<sound.getStatus()<<std::endl;
	//exit(0);
}
}
int status;
waitpid(pid, &status, 0);
    return 0;
}