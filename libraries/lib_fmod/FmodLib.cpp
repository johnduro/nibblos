
#include <iostream>
#include <cstdlib>
#include "FmodLib.hpp"

FmodLib::~FmodLib( void )
{
	this->_eat->release();
    this->_death->release();
    this->_system->close();
    this->_system->release();
}

FmodLib::FmodLib( void )
	: _eat(NULL), _death(NULL)
{
//init FMOD
	if (FMOD::System_Create(&(this->_system)) != FMOD_OK)// create an instance of the game engine
		throw LibraryException("FMod-Lib: Couldn't create system");

	if (this->_system->init(32, FMOD_INIT_NORMAL, 0) != FMOD_OK)// initialise the game engine with 32 channels
		throw LibraryException("FMod-Lib: Couldn't initialize system");
	//load sounds
 	if (this->_system->createSound("libraries/lib_fmod/sound/eat.wav", FMOD_CREATESAMPLE, 0, &(this->_eat)) != FMOD_OK)
		throw LibraryException("FMod-Lib: Couldn't load sound : eat.wav");

	if (this->_system->createSound("libraries/lib_fmod/sound/death.wav", FMOD_CREATESAMPLE, 0, &(this->_death)) != FMOD_OK)
		throw LibraryException("FMod-Lib: Couldn't load sound : death.wav");

	this->_eat->setMode(FMOD_LOOP_OFF);    /* drumloop.wav has embedded loop points which automatically makes looping turn on, */
	this->_death->setMode(FMOD_LOOP_OFF);    /* drumloop.wav has embedded loop points which automatically makes looping turn on, */
	/* so turn it off here.  We could have also just put FMOD_LOOP_OFF in the above CreateSound call. */
}

void	FmodLib::playMusic( void )
{

}

void	FmodLib::playEat( void )
{
	FMOD::Channel *channel = NULL;

	this->_system->playSound(this->_eat, NULL, false, &channel);
}

void	FmodLib::playDeath( void )
{
	FMOD::Channel *channel = NULL;

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

char		getType( void )
{
	return 's';
}
