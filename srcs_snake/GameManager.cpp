// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GameManager.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/16 20:06:33 by mle-roy           #+#    #+#             //
//   Updated: 2015/03/30 19:46:06 by mle-roy          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <stdlib.h>
#include <string.h>
#include <string>
#include <dlfcn.h>
#include "GameManager.hpp"

// const std::vector<std::vector<mapBlock>>		GameManager::_blocks [] =
// {
// 	std::vector<mapBlock> [] = {};
// };

// ** PRIVATE FUNCTION ** //

void			GameManager::_playerCollision(Player & play, std::string reason)
{
	this->_endGame = "Player " + play.getName() + reason;
	this->_isEnded = true;
}

// TMap::mapBlock		GameManager::_updateHead(Vector2 const & direction, int player)
// {
// 	if (direction == UP && player == 1)
// 		return TMap::mapBlock::head_u_1;
// 	else if (direction == DOWN && player == 1)
// 		return TMap::mapBlock::head_d_1;
// 	else if (direction == LEFT && player == 1)
// 		return TMap::mapBlock::head_l_1;
// 	else if (direction == RIGHT && player == 1)
// 		return TMap::mapBlock::head_r_1;
// 	else if (direction == UP && player == 2)
// 		return TMap::mapBlock::head_u_2;
// 	else if (direction == DOWN && player == 2)
// 		return TMap::mapBlock::head_d_2;
// 	else if (direction == LEFT && player == 2)
// 		return TMap::mapBlock::head_l_2;
// 	else if (direction == RIGHT && player == 2)
// 		return TMap::mapBlock::head_r_2;
// 	return TMap::mapBlock::rock;
// }

void			GameManager::_updateMap( void )
{
	std::list<Vector2>::iterator		itVect;
	// std::list<Vector2>::iterator		iteFood = this->_foods.end();
	std::vector<Player>::iterator		itPlayer;
	std::vector<Player>::iterator		itePlayer = this->_snakes.end();
	std::vector<Player>::iterator		itOtherPlayer;
	std::vector<Player>::iterator		iteOtherPlayer = this->_snakes.end();
	// Vector2								playerHead;
	// int									player = 1;

	// this->_setMap();


	// for (itFood = this->_foods.begin(); itFood != iteFood; itFood++)
	// 	this->_map.map[itFood->getY()][itFood->getX()] = TMap::mapBlock::food;

	// char c = '1';
	for (itPlayer = this->_snakes.begin(); itPlayer != itePlayer; itPlayer++)
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
			if (this->_checkCollision(itPlayer->getHead(), itVect, itPlayer->getLinks.end()))
				this->_playerCollision(*itPlayer, " ate himself !");
			else
			{
				for (itOtherPlayer = this->_snakes.begin(); itOtherPlayer != iteOtherPlayer; itOtherPlayer++)
				{
					if (itOtherPlayer != itPlayer)
					{
						if (this->_checkCollision(itPlayer->getHead(), itOtherPlayer->getLinks.begin(), itOtherPlayer->getLinks.end()))
							this->_playerCollision(*itPlayer, " ate a friend !");
					}
				}
			}
		}
	}
	if (this->_foods.empty())
		this->_generateFood();






	// 	std::list<Vector2>::const_reverse_iterator		itLinks;
	// 	std::list<Vector2>::const_reverse_iterator		iteLinks = itPlayer->getLinks().rend();
	// 	int												pos = 0;
	// 	int												size = itPlayer->getLinks().size();

	// 	this->_map.scores += " " + itPlayer->getName() + " : " + std::to_string(itPlayer->getScore());

	// 	for (itLinks = itPlayer->getLinks().rbegin(); itLinks != iteLinks; itLinks++)
	// 	{

	// 		if (pos == (size - 1))
	// 		{

	// 			if (itLinks->getY() < 0 || itLinks->getY() >= this->_map.size.getY()
	// 				|| itLinks->getX() < 0 || itLinks->getX() >= this->_map.size.getX())
	// 				this->_playerCollision(*itPlayer, " hitted a wall !");
	// 			else
	// 			{
	// 				if (this->_map.map[itLinks->getY()][itLinks->getX()] == TMap::mapBlock::food)
	// 					this->_eatFood(*itPlayer);
	// 				else if (this->_map.map[itLinks->getY()][itLinks->getX()] != TMap::mapBlock::empty)
	// 					this->_playerCollision(*itPlayer, " ate himself !");
	// 				this->_map.map[itLinks->getY()][itLinks->getX()] = this->_updateHead(itPlayer->getDir(), player);
	// 			}
	// 		}
	// 		else if (player == 1)
	// 			this->_map.map[itLinks->getY()][itLinks->getX()] = TMap::mapBlock::body_1;
	// 		else if (player == 2)
	// 			this->_map.map[itLinks->getY()][itLinks->getX()] = TMap::mapBlock::body_2;
	// 		pos++;
	// 	}
	// 	c++;
	// 	player++;
	// }
	// if (this->_foods.empty())
	// 	this->_generateFood();
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
	std::list<Player>::const_iterator		itP;
	std::list<Player>::const_iterator		iteP = this->_map.snakes.end();
	Vector2									newFood;

	do
	{
		bool			isOk = true;

		newFood.setX(rand() % this->_map.size._x);
		newFood.setY(rand() % this->_map.size._y);

		if (this->_checkCollision(newFood, this->_map.foods.begin(), this->_map.foods.end())
			|| this->_checkCollision(newFood, this->_map.rocks.begin(), this->_map.rocks.end()))
			isOk = false;

		for (itP = this->_map.snakes.begin(); itP != iteP; itP++)
		{
			if (this->_checkCollision(newFood, it->links.begin(), it->links.end()))
				isOk = false;
		}
		if (isOK)
			this->_map.foods.push_back(newFood);

		// int rx = rand() % this->_map.size._x;
		// int ry = rand() % this->_map.size._y;

		// // if (this->_map.map[ry][rx] == 32)
		// if (this->_map.map[ry][rx] == TMap::mapBlock::empty)
		// 	this->_foods.push_back(Vector2(rx, ry));

	}
	while (this->_foods.empty());
}

void			GameManager::_eatFood( Player & play )
{
	Vector2 const *		head = &(play.getHead());

	this->_map.foods.remove(*head);
	play.addLink();
}

// void			GameManager::_setMap( void )
// {
// 	for (int i = 0; i < this->_map.size.getY(); i++)
// 	{
// 		for (int x = 0; x < this->_map.size.getX(); x++)
// 			this->_map.map[i][x] = TMap::mapBlock::empty;
// 			// this->_map.map[i][x] = 32;
// 	}
// 	this->_map.scores = "";
// }

void			GameManager::_initMap( Vector2 size )
{
	// std::cout << "malloc table y : " << size._y << " - x : " << size._x << std::endl;
	this->_map.size = size;
	this->_map.pause = false;
	this->_map.isEnded = false;
	// this->_map.size = size;
	// this->_map.map = new char*[size._y];
	// for (int i = 0; i < size._y; i++)
	// 	this->_map.map[i] = new char[size._x];

	// this->_setMap();
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
	: _players(players), _libs(libs), _isLibInit(false), _input(0), _timeTick(TIME_BASE)
	// : _map.size(size), _map.pause(false), _map.isEnded(false), _players(players), _libs(libs), _isLibInit(false), _input(0), _timeTick(TIME_BASE)
	// : _players(players), _libs(libs), _pause(false), _isEnded(false), _isLibInit(false), _input(0), _timeTick(TIME_BASE)
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
			if (this->_checkInput())
				break ;
			// if (this->_isEnded)
			// 	continue ;
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
