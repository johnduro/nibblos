// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GameManager.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/16 19:55:34 by mle-roy           #+#    #+#             //
//   Updated: 2015/03/30 19:43:30 by mle-roy          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GAMEMANAGER_HPP
# define GAMEMANAGER_HPP

#include <vector>
#include <list>
#include "Player.hpp"
#include "ft_timer.hpp"
#include "TMap.hpp"
#include "IGraphicLib.hpp"

# define TIME_BASE 300000

class GameManager
{
private:
	TMap							_map;
	int								_players;
	ft_timer						_timer;
	// std::vector<Player>				_snakes;//MAP
	// std::list<Vector2>				_foods;//MAP
	std::vector<std::string>		_libs;
	// std::string						_endGame;//SUPP
	IGraphicLib *					_lib;
	// bool							_pause;//MAP
	// bool							_isEnded;//MAP
	void *							_dl_handle;
	bool							_isLibInit;
	int								_input;
	int								_timeTick;
	// static const std::vector<std::vector<mapBlock>>		_blocks;


	void			_updateMap( void );
	void			_eatFood( Player & play );
	void			_initMap( Vector2 size );
	bool			_checkInput( void );
	void			_movesSnakes( void );
	void			_generateFood( void );
	void			_initLib( std::string lib );
	void			_closeLib( void );
	void			_setMap( void );
	void			_changeTimer( int input );
	void			_playerCollision( Player & play, std::string reason);
	// TMap::mapBlock	_updateHead(Vector2 const & direction, int player);
	bool			_checkCollision(Vector2 somePlace, std::list<Vector2>::const_iterator it, std::list<Vector2>::const_iterator ite)


	GameManager( void );
	GameManager(GameManager const &src);
	GameManager &	operator=(GameManager const &rhs);

public:
	GameManager(int players, Vector2 size, std::vector<std::string> libs);
	~GameManager();

	void	Update();
};

#endif // ** GAMEMANAGER_HPP ** //
