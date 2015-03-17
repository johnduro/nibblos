// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GameManager.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/16 20:06:33 by mle-roy           #+#    #+#             //
//   Updated: 2015/03/17 20:14:34 by mle-roy          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include "GameManager.hpp"

// ** PRIVATE FUNCTION ** //

bool			GameManager::_updateMap( void )
{
	bool								collision = false;
	std::list<Vector2>::iterator		itFood;
	std::list<Vector2>::iterator		iteFood = this->_foods.end();
	std::vector<Player>::iterator		itPlayer;
	std::vector<Player>::iterator		itePlayer = this->_snakes.end();

	this->_setMap();
	// memset(this->_map.map, 32, (this->_map.size._x * this->_map.size._y) * sizeof(char));

	for (itFood = this->_foods.begin(); itFood != iteFood; itFood++)
		this->_map.map[itFood->getY()][itFood->getX()] = 'F';

	char c = '1';
	for (itPlayer = this->_snakes.begin(); itPlayer != itePlayer; itPlayer++)
	{
		std::list<Vector2> const *				links = &(itPlayer->getLinks());
		std::list<Vector2>::const_iterator		itLinks;
		std::list<Vector2>::const_iterator		iteLinks = links->end();
		bool								head = true;

		for (itLinks = links->begin(); itLinks != iteLinks; itLinks++)
		{
			if (head)
			{
				if (itLinks->getY() < 0 || itLinks->getY() >= this->_map.size.getY() || itLinks->getX() < 0 || itLinks->getX() >= this->_map.size.getX())
				{
					collision = true;
					this->_endGame = "Game Fuck'n Over";
				}
				else
				{
					if (this->_map.map[itLinks->getY()][itLinks->getX()] == 'F')
						this->_eatFood(*itPlayer);
					else if (this->_map.map[itLinks->getY()][itLinks->getX()] != 32)
					{
						collision = true;
						this->_endGame = "Game Fuck'n Over";
					}
					this->_map.map[itLinks->getY()][itLinks->getX()] = '*';
				}
				head = false;
			}
			else
				this->_map.map[itLinks->getY()][itLinks->getX()] = c;
		}
		c++;
	}
	if (this->_foods.empty())
		this->_generateFood();
	return (collision);
}

void	GameManager::_generateFood() {

	do {
	int rx = rand() % this->_map.size._x;
	int ry = rand() % this->_map.size._y;

	if (this->_map.map[ry][rx] == 32)
		this->_foods.push_back(Vector2(rx, ry));

	} while (this->_foods.empty());
}

void			GameManager::_eatFood(Player & play)
{
	Vector2 const *		head = &(play.getHead());

	this->_foods.remove(*head);
	play.addLink();
}

void			GameManager::_setMap( void )
{
	for (int i = 0; i < this->_map.size.getY(); i++)
	{
		for (int x = 0; x < this->_map.size.getX(); x++)
			this->_map.map[i][x] = 32;
	}
}

void			GameManager::_initMap( Vector2 size )
{
	std::cout << "malloc table y : " << size._y << " - x : " << size._x << std::endl;
	this->_map.size = size;
	this->_map.map = new char*[size._y];
	for (int i = 0; i < size._y; i++)
		this->_map.map[i] = new char[size._x];

	this->_setMap();
	// memset(this->_map.map, 32, (this->_map.size._x * this->_map.size._y) * sizeof(char));
	// std::cout << "PRINTMAP " << std::endl;
	// for (int i = 0; i < 30; i++)
	// {
	// 	for (int x = 0; x < 30; x++)
	// 		std::cout << this->_map.map[i][x];
	// 	std::cout << "<+" << std::endl;
	// }
}

void			GameManager::_checkInput( void )
{
	int		input;

	input = this->_lib->getInput();
	switch (input)
	{
		case STD_RIGHT:
			this->_snakes.front().setDir(RIGHT);
		case STD_LEFT:
			this->_snakes.front().setDir(LEFT);
		case STD_EXIT:
		{
			std::cout << "exit" << std::endl;
			exit(EXIT_SUCCESS);
		}
	}
}

void			GameManager::_movesSnakes( void )
{
	std::vector<Player>::iterator		it;
	std::vector<Player>::iterator		ite = this->_snakes.end();

	for (it = this->_snakes.begin(); it != ite; it++)
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
	LibCreator = (IGraphicLib *(*)(void)) dlsym(this->_dl_handle, "createLib");
	if (!LibCreator)
	{
		std::cout << "FAIL LIB CREATOR ! " << std::endl;
		exit(-1);
	}
	this->_lib = LibCreator();
	this->_isLibInit = true;
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
	: _players(players), _libs(libs), _pause(false), _isLibInit(false)
{
	this->_initMap(size);
	this->_snakes.push_back(Player("ahmed", Vector2(15, 15)));
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
	delete this->_map.map;
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
	// std::cout << "GM1" << std::endl;
	this->_timer.updateTimeAdd(100000, MICRO_SECONDS);
	// std::cout << "GM2" << std::endl;
	// for (int i = 0; i < 30; i++)
	// {
	// 	for (int x = 0; x < 30; x++)
	// 		std::cout << this->_map.map[i][x];
	// 	std::cout << "<+" << std::endl;
	// }
	this->_lib->initLibrary(this->_map);
	while (1)
	{
		// std::cout << "GM3" << std::endl;
		this->_lib->printMap(this->_map);
		// std::cout << "GM4" << std::endl;
		if (this->_timer.isTick())
		{
			// std::cout << "GM5" << std::endl;
			this->_checkInput();//a faire
			//if (this->_pause)
			//	continue;
			// std::cout << "GM6" << std::endl;
			this->_movesSnakes();
			// std::cout << "GM7" << std::endl;
			if (this->_updateMap())
			{
				// this->_lib->_gameOver(this->_endGame);
				break ;
			}
		}
	}
}
