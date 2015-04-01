
#include <iostream>
#include <cstdlib>
#include "FmodLib.hpp"
// #include "fmod/fmod.h"

// FMOD_SYSTEM *system;
// FMOD_System_Create(&system);
// FMOD_System_Init(system, 2, FMOD_INIT_NORMAL, NULL);

FmodLib::~FmodLib( void )
{
	this->_eat->release();
    this->_death->release();
    this->_system->close();
    this->_system->release();



	// FMOD_Sound_Release(this->_eat);
	// FMOD_Sound_Release(this->_death);
	// FMOD_System_Close(this->_system);
	// FMOD_System_Release(this->_system);
}

FmodLib::FmodLib( void )
	: _eat(NULL), _death(NULL)
{
//init FMOD
	FMOD::System_Create(&(this->_system));// create an instance of the game engine
	this->_system->init(32, FMOD_INIT_NORMAL, 0);// initialise the game engine with 32 channels

	std::cout << "HEREEEEEEE" << std::endl;
	//load sounds
 	if (this->_system->createSound("libraries/lib_fmod/sound/eat.wav", FMOD_CREATESAMPLE, 0, &(this->_eat)) != FMOD_OK)
		std::cout << "NOPE_1" << std::endl;

	if (this->_system->createSound("libraries/lib_fmod/sound/death.wav", FMOD_CREATESAMPLE, 0, &(this->_death)) != FMOD_OK)
		std::cout << "NOPE_2" << std::endl;
 	// this->_system->createSound("sound/eat.wav", FMOD_HARDWARE, 0, &(this->_eat));
	// this->_system->createSound("sound/death.wav", FMOD_HARDWARE, 0, &(this->_death));
	this->_eat->setMode(FMOD_LOOP_OFF);    /* drumloop.wav has embedded loop points which automatically makes looping turn on, */
	this->_death->setMode(FMOD_LOOP_OFF);    /* drumloop.wav has embedded loop points which automatically makes looping turn on, */
	/* so turn it off here.  We could have also just put FMOD_LOOP_OFF in the above CreateSound call. */

	// system->createSound("../../media/jaguar.wav", FMOD_HARDWARE, 0, &sound2);






	// FMOD_System_Create(&(this->_system));
	// FMOD_System_Init(this->_system, 32, FMOD_INIT_NORMAL, NULL);
	// FMOD_System_CreateSound(this->_system, "sound/eat.wav", FMOD_CREATESAMPLE, 0, &(this->_eat));
	// FMOD_System_CreateSound(this->_system, "sound/death.wav", FMOD_CREATESAMPLE, 0, &(this->_death));
}

void	FmodLib::playMusic( void )
{

}

void	FmodLib::playEat( void )
{

	// FMOD::System *system = NULL; // create and init not shown
	// FMOD::Sound *sound = NULL; // create not shown

	FMOD::Channel *channel = NULL;
	// FMOD_RESULT result = system->playSound(sound, NULL, false, &channel);


	// FMOD_System_PlaySound(this->_system, 1, this->_eat, 0, NULL);
	// FMOD_System_PlaySound(this->_system, FMOD_CHANNEL_FREE, this->_eat, 0, NULL);
	// FMOD_System_PlaySound(this->_system, this->_eat, FMOD_CHANNEL, 0, NULL);
	this->_system->playSound(this->_eat, NULL, false, &channel);
}

void	FmodLib::playDeath( void )
{
	FMOD::Channel *channel = NULL;
	// FMOD_System_PlaySound(this->_system, 2, this->_death, 0, NULL);
	// FMOD_System_PlaySound(this->_system,  this->_death, FMOD_CHANNEL, 0, NULL);
	this->_system->playSound(this->_death, NULL, false, &channel);
}

FmodLib		*createLib( void )
{
	return new FmodLib();
}

void			deleteLib( FmodLib * lib )
{
	delete lib;
}
