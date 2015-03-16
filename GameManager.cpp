// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GameManager.cpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/16 20:06:33 by mle-roy           #+#    #+#             //
//   Updated: 2015/03/16 20:55:11 by mle-roy          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "GameManager.hpp"

// ** PRIVATE FUNCTION ** //

bool			GameManager::_updateMap( void )
{

}

void			GameManager::_initMap( Vector2 size )
{
	this->_map.size = size;
	this->_map.map = new char*[size._y];
	for (int i = 0; i < size._y; i++)
		this->_map.map[i] = new char[size._x];

	memset(this->_map.map, 0, (this->_map.size._x * this->_map.size._y) * sizeof(char));
}

// ** CANONICAL ** //
// GameManager::GameManager( void );
GameManager::GameManager(int players, Vector2 size, std::vector<std::string> libs)
	: _players(players), _libs(libs)
{
	this->_initMap(size);
}

GameManager::~GameManager() { delete this->_map.map; }

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
	this->_timer.updateTimeAdd(100000, MICRO_SECONDS);
	while (1)
	{
		this->_lib->_printMap(this->_map);
		if (this->_timer.isTick())
		{
			this->_checkInput();//a faire
			this->_movesSnakes();//a faire
			if (!this->_updateMap()) // a faire
				this->_lib->_gameOver(this->_endGame);
		}
	}
}
