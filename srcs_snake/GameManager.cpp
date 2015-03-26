// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GameManager.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/16 20:06:33 by mle-roy           #+#    #+#             //
//   Updated: 2015/03/26 17:00:16 by mle-roy          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <stdlib.h>
#include <string.h>
#include <string>
#include <dlfcn.h>
#include "GameManager.hpp"

// ** PRIVATE FUNCTION ** //

bool			GameManager::_playerCollision(Player & play)
{

}

bool			GameManager::_updateMap( void )
{
	bool								collision = false;
	std::list<Vector2>::iterator		itFood;
	std::list<Vector2>::iterator		iteFood = this->_foods.end();
	std::vector<Player>::iterator		itPlayer;
	std::vector<Player>::iterator		itePlayer = this->_snakes.end();

	// std::cout << "11" << std::endl;
	this->_setMap();
	// memset(this->_map.map, 32, (this->_map.size._x * this->_map.size._y) * sizeof(char));

	// std::cout << "22" << std::endl;
	for (itFood = this->_foods.begin(); itFood != iteFood; itFood++)
		this->_map.map[itFood->getY()][itFood->getX()] = 'F';
	// std::cout << "33" << std::endl;

	char c = '1';
	for (itPlayer = this->_snakes.begin(); itPlayer != itePlayer; itPlayer++)
	{
		// std::list<Vector2> const *				links = &(itPlayer->getLinks());
		std::list<Vector2>::const_reverse_iterator		itLinks;
		std::list<Vector2>::const_reverse_iterator		iteLinks = itPlayer->getLinks().rend();
		// std::list<Vector2>::const_iterator		iteLinks = links->end();
		//bool											head = true;
		// std::cout << "44" << std::endl;
		// std::cout << "size of " << itPlayer->getName() <<  " into the update ==> " << itPlayer->getLinks().size() << std::endl;
		// std::cout << "55" << std::endl;
		int pos = 0;
		int size = itPlayer->getLinks().size();
		this->_map.scores += " " + itPlayer->getName() + " : " + std::to_string(itPlayer->getScore());
		// for (itLinks = links->begin(); itLinks != iteLinks; itLinks++)
		for (itLinks = itPlayer->getLinks().rbegin(); itLinks != iteLinks; itLinks++)
		{
			// std::cout << "YOLOOOO" << std::endl;
			// std::cout << "Link Y : " << itLinks->getY() << " - X : " << itLinks->getX() << std::endl;
			if (pos == (size - 1))
			{
				if (itLinks->getY() < 0 || itLinks->getY() >= this->_map.size.getY() || itLinks->getX() < 0 || itLinks->getX() >= this->_map.size.getX())
				{
					collision = true;
					// std::cout << "YOLOOOO111GAMELKMDFKLMSDF" << std::endl;
					this->_endGame = "Player " + itPlayer->getName() + " hit a wall !";
					this->_pause = true;
					this->_isEnded = true;
				}
				else
				{
					if (this->_map.map[itLinks->getY()][itLinks->getX()] == 'F')
						this->_eatFood(*itPlayer);
					else if (this->_map.map[itLinks->getY()][itLinks->getX()] != 32)
					{
						collision = true;
						// std::cout << "YOLOOOO2GAMEOBER" << std::endl;
						this->_endGame = "Player " + itPlayer->getName() + " ate himself !";
						this->_pause = true;
						this->_isEnded = true;
					}
					this->_map.map[itLinks->getY()][itLinks->getX()] = '*';
				}
				//head = false;
			}
			else
				this->_map.map[itLinks->getY()][itLinks->getX()] = c;
			pos++;
		}
		// std::cout << "WUT ?????1111" << std::endl;
		c++;
	}
	if (this->_foods.empty())
		this->_generateFood();
	return (collision);
}

void	GameManager::_generateFood( void )
{

	do
	{
		int rx = rand() % this->_map.size._x;
		int ry = rand() % this->_map.size._y;

		if (this->_map.map[ry][rx] == 32)
			this->_foods.push_back(Vector2(rx, ry));

	}
	while (this->_foods.empty());
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
	this->_map.scores = "";
}

void			GameManager::_initMap( Vector2 size )
{
	// std::cout << "malloc table y : " << size._y << " - x : " << size._x << std::endl;
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

void			GameManager::_changeTimer( int input )
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

bool			GameManager::_checkInput( void )
{
	int		input;
	// bool	ret = false;

	// input = this->_lib->getInput();
	// std::cout << "INPUT2 : " << input << std::endl;
	input = this->_input;
	this->_input = 0;
	switch (input)
	{
		case STD_RIGHT: case STD_LEFT: case STD_UP: case STD_DOWN:
		{
			this->_snakes.front().setDir(input);
			break ;
		}
		case STD_SPACE:
		{
			// std::cout  << "IICICIICIIICICIC"  << std::endl;
			this->_pause = !(this->_pause);
			break ;
		}
		case STD_PLUS: case STD_MINUS:
		{
			this->_changeTimer(input);
			break ;
		}
		case STD_EXIT:
		{
			return (true);
			// ret = true;
			// break ;
			// std::cout << "exit INPUT" << std::endl;
			// exit(EXIT_SUCCESS);
		}
	}
	return (false);
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
	: _players(players), _libs(libs), _pause(false), _isEnded(false), _isLibInit(false), _input(0), _timeTick(TIME_BASE)
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
	int		input = 0;
	// int		timeTick = TIME_BASE;

	// this->_timer.updateTimeAdd(300000, MICRO_SECONDS);
	this->_timer.updateTimeAdd(this->_timeTick, MICRO_SECONDS);
	// this->_timer.updateTimeAdd(100000, MICRO_SECONDS);
	this->_lib->initLibrary(this->_map);
	this->_updateMap();
	while (42)
	{
		// for(int y=0; y<_map.size._y; y++)
		// {
		// 	for(int x=0; x<_map.size._x; x++)
		// 		std::cout << _map.map[y][x];
		// 	std::cout << "<--" << std::endl;
		// }
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
			if (this->_checkInput())
				break ;
			if (this->_pause || this->_isEnded)
				continue;
			// std::cout << "GM6" << std::endl;
			this->_movesSnakes();
			// std::cout << "GM7" << std::endl;
			if (this->_updateMap())
			{
				this->_lib->gameOver(this->_endGame);
				// break ;
			}
			// input = -1;
		}
	}
}
