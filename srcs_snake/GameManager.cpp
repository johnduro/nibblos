// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GameManager.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/16 20:06:33 by mle-roy           #+#    #+#             //
//   Updated: 2015/03/31 19:52:02 by mle-roy          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <stdlib.h>
#include <string.h>
#include <string>
#include <dlfcn.h>
#include "GameManager.hpp"

// ** PRIVATE FUNCTION ** //

void			GameManager::_playerCollision(Player & play, std::string const & reason)
{
	play.setIsAlive(false);
	play.setDeathReason(reason);
	this->_map.isEnded = true;
}


void			GameManager::_updateMap( void )
{
	std::list<Vector2>::const_iterator		itVect;
	std::vector<Player>::iterator		itPlayer;
	std::vector<Player>::iterator		itePlayer = this->_map.snakes.end();
	std::vector<Player>::iterator		itOtherPlayer;
	std::vector<Player>::iterator		iteOtherPlayer = this->_map.snakes.end();

	for (itPlayer = this->_map.snakes.begin(); itPlayer != itePlayer; itPlayer++)
	{
		if (itPlayer->getHead().getY() < 0 || itPlayer->getHead().getY() >= this->_map.size.getY()
			|| itPlayer->getHead().getX() < 0 || itPlayer->getHead().getX() >= this->_map.size.getX())
			this->_playerCollision(*itPlayer, " hitted a wall !");
		else if (this->_checkCollision(itPlayer->getHead(), this->_map.foods.begin(), this->_map.foods.end()))
			this->_eatFood(*itPlayer);
		else if (this->_checkCollision(itPlayer->getHead(), this->_map.rocks.begin(), this->_map.rocks.end()))
			this->_playerCollision(*itPlayer, " hitted a rock !");
		else
		{
			itVect = itPlayer->getLinks().begin();
			itVect++;
			if (this->_checkCollision(itPlayer->getHead(), itVect, itPlayer->getLinks().end()))
				this->_playerCollision(*itPlayer, " ate himself !");
			else
			{
				for (itOtherPlayer = this->_map.snakes.begin(); itOtherPlayer != iteOtherPlayer; itOtherPlayer++)
				{
					if (itOtherPlayer != itPlayer)
					{
						if (this->_checkCollision(itPlayer->getHead(), itOtherPlayer->getLinks().begin(), itOtherPlayer->getLinks().end()))
							this->_playerCollision(*itPlayer, " ate a friend !");
					}
				}
			}
		}
	}
	if (this->_map.foods.empty())
		this->_generateFood();
}

bool	GameManager::_checkCollision(Vector2 somePlace, std::list<Vector2>::const_iterator it, std::list<Vector2>::const_iterator ite)
{
	while (it != ite)
	{
		if (*it == somePlace)
			return (true);
		it++;
	}
	return (false);
}

void	GameManager::_generateFood( void )
{
	std::vector<Player>::const_iterator		itP;
	std::vector<Player>::const_iterator		iteP = this->_map.snakes.end();
	Vector2									newFood;
	bool									isOk = true;

	do
	{
		newFood.setX((rand() % this->_map.size._x - 1) + 1);
		newFood.setY((rand() % this->_map.size._y - 1) + 1);

		if (this->_checkCollision(newFood, this->_map.foods.begin(), this->_map.foods.end())
			|| this->_checkCollision(newFood, this->_map.rocks.begin(), this->_map.rocks.end()))
			isOk = false;

		for (itP = this->_map.snakes.begin(); itP != iteP; itP++)
		{
			if (this->_checkCollision(newFood, itP->getLinks().begin(), itP->getLinks().end()))
				isOk = false;
		}
		if (isOk)
			this->_map.foods.push_back(newFood);
		isOk = true;
	}
	while (this->_map.foods.empty());
	// std::cout << "FOOD X = " << newFood.getX()  << " -- Y = " << newFood.getY() << std::endl;
}

void			GameManager::_eatFood( Player & play )
{
	Vector2 const *		head = &(play.getHead());

	this->_map.foods.remove(*head);
	play.addLink();

	this->_timeTick -= 15000;
	if (this->_timeTick < 100000)
		this->_timeTick = 100000;
	this->_timer.updateTimeAdd(this->_timeTick, MICRO_SECONDS);
}


void			GameManager::_playerOneMvt( int input )
{
	this->_map.snakes.front().setDir(input);
}

void			GameManager::_gamePause( int input )
{
	static_cast<void>(input);
	this->_map.pause = !(this->_map.pause);
}

void			GameManager::_gameExit( int input )
{
	static_cast<void>(input);
	this->_isExited = true;
}

void			GameManager::_gameSpeed( int input )
{
	if (input == STD_PLUS)
		this->_timeTick -= 100000;
	if (input == STD_MINUS)
		this->_timeTick += 100000;

	if (this->_timeTick < 100000)
		this->_timeTick = 100000;
	else if (this->_timeTick > 600000)
		this->_timeTick = 600000;

	this->_timer.updateTimeAdd(this->_timeTick, MICRO_SECONDS);
}

void			GameManager::_gameLib( int input )
{
	int			lib = 0;

	if (input == STD_LIB1)
		lib = 0;
	else if (input == STD_LIB2)
		lib = 1;
	else if (input == STD_LIB3)
		lib = 2;
	if (this->_libs.size() > static_cast<unsigned long>(lib) && this->_libs[lib] != this->_initiatedLib)
	{
		this->_initLib(this->_libs[lib]);
		this->_lib->initLibrary(this->_map);
	}
}

void			GameManager::_playerTwoMvt( int input )
{
	if (this->_map.snakes.size() > 1)
		this->_map.snakes.back().setDir(input);
}


void			GameManager::_initMap( Vector2 size )
{
	this->_map.size = size;
	this->_map.pause = false;
	this->_map.isEnded = false;

	this->_inputFunction[STD_LEFT] = &GameManager::_playerOneMvt;
	this->_inputFunction[STD_RIGHT] = &GameManager::_playerOneMvt;
	this->_inputFunction[STD_UP] = &GameManager::_playerOneMvt;
	this->_inputFunction[STD_DOWN] = &GameManager::_playerOneMvt;
	this->_inputFunction[STD_SPACE] = &GameManager::_gamePause;
	this->_inputFunction[STD_EXIT] = &GameManager::_gameExit;
	this->_inputFunction[STD_PLUS] = &GameManager::_gameSpeed;
	this->_inputFunction[STD_MINUS] = &GameManager::_gameSpeed;
	this->_inputFunction[STD_LIB1] = &GameManager::_gameLib;
	this->_inputFunction[STD_LIB2] = &GameManager::_gameLib;
	this->_inputFunction[STD_LIB3] = &GameManager::_gameLib;
	this->_inputFunction[STD_LEFT_P2] = &GameManager::_playerTwoMvt;
	this->_inputFunction[STD_RIGHT_P2] = &GameManager::_playerTwoMvt;
	this->_inputFunction[STD_UP_P2] = &GameManager::_playerTwoMvt;
	this->_inputFunction[STD_DOWN_P2] = &GameManager::_playerTwoMvt;
}


void			GameManager::_checkInput( void )
{
	int		input;

	// std::cout << "INNN" << std::endl;
	input = this->_input;
	this->_input = 0;
	// std::cout << "INNN2222------>" << input << std::endl;
	(this->*(_inputFunction[input]))(input);
	// std::cout << "OUTTT" << std::endl;
}

void			GameManager::_movesSnakes( void )
{
	std::vector<Player>::iterator		it;
	std::vector<Player>::iterator		ite = this->_map.snakes.end();

	for (it = this->_map.snakes.begin(); it != ite; it++)
		it->movSnake();
}

void			GameManager::_initLib( std::string lib )
{
	// void *		dl_handle;
	IGraphicLib*(*LibCreator)(void);

	// std::cout << "LIB : " << lib << std::endl;
	if (this->_isLibInit == true)
		this->_closeLib();
	this->_dl_handle = dlopen(lib.c_str(), RTLD_LAZY | RTLD_LOCAL);
	if (!this->_dl_handle)
	{
		std::cout << "FAIL LIB HANDLE ! " << std::endl;
		exit(-1);
	}
	LibCreator = (IGraphicLib *(*)(void)) dlsym(this->_dl_handle, "createLib");
	if (!LibCreator)
	{
		std::cout << "FAIL LIB CREATOR ! " << std::endl;
		exit(-1);
	}
	this->_lib = LibCreator();
	this->_isLibInit = true;
	this->_initiatedLib = lib;
}

void			GameManager::_closeLib( void )
{
	void    (*LibDestructor)(IGraphicLib *);

	this->_lib->closeLibrary();
	LibDestructor = (void(*)(IGraphicLib*)) dlsym(this->_dl_handle, "deleteLib");
	if (!LibDestructor)
	{
		std::cout << "FAIL LIB DESTRUCTOR ! " << std::endl;
		exit(-1);
	}
	LibDestructor(this->_lib);
	dlclose(this->_dl_handle);
	this->_isLibInit = false;
}

// ** CANONICAL ** //

// GameManager::GameManager( void );
GameManager::GameManager(int players, Vector2 size, std::vector<std::string> libs)
	: _players(players), _libs(libs), _isLibInit(false), _input(0), _timeTick(TIME_BASE), _isExited(false)
	// : _map.size(size), _map.pause(false), _map.isEnded(false), _players(players), _libs(libs), _isLibInit(false), _input(0), _timeTick(TIME_BASE)
	// : _players(players), _libs(libs), _pause(false), _isEnded(false), _isLibInit(false), _input(0), _timeTick(TIME_BASE)
{
	this->_initMap(size);
	this->_map.snakes.push_back(Player("ahmed", Vector2(15, 15)));
	if (this->_libs.size() > 0)
		this->_initLib(this->_libs.front());
	else
	{
		std::cout << "PAS DE LIB !!!!!" << std::endl;
		exit(-1);
	}
}

GameManager::~GameManager( void )
{
	if (this->_isLibInit)
		this->_closeLib();
	// delete this->_map.map;
}

// GameManager::GameManager(GameManager const &src)
// {
// 	*this = src;
// }

// GameManager &	GameManager::operator=(GameManager const &rhs)
// {
// 	return *this;
// }


// ** PUBLIC FUNCTION ** //

void	GameManager::Update( void )
{
	int		input = 0;
	// int		timeTick = TIME_BASE;

	// this->_timer.updateTimeAdd(300000, MICRO_SECONDS);
	this->_timer.updateTimeAdd(this->_timeTick, MICRO_SECONDS);
	// this->_timer.updateTimeAdd(100000, MICRO_SECONDS);
	// std::cout << "GM0" << std::endl;
	this->_lib->initLibrary(this->_map);
	// std::cout << "GM1" << std::endl;
	this->_updateMap();
	// std::cout << "GM2" << std::endl;
	while (42)
	{
		this->_lib->printMap(this->_map);
		// std::cout << "GM4" << std::endl;
		input = this->_lib->getInput();
		if (input != 0)
		{
			this->_input = input;
			input = 0;
		}
		if (this->_timer.isTick())
		{
			// std::cout << "GM5" << std::endl;
			if (this->_input != 0)
				this->_checkInput();
			// std::cout << "ICIICICIICIC" << std::endl;
			if (this->_isExited)
				break ;
			// if (this->_isEnded)
			// 	continue ;
			// std::cout << "ICII333333333333CICIICIC" << std::endl;
			if (this->_map.pause || this->_map.isEnded)
				continue;
			// std::cout << "GM6" << std::endl;
			this->_movesSnakes();
			// std::cout << "GM7" << std::endl;
			this->_updateMap();
			// if (this->_updateMap())
			// {
			// 	this->_lib->gameOver(this->_endGame);
			// 	// break ;
			// }
			// input = -1;
		}
	}
}
