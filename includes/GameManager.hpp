// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GameManager.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/16 19:55:34 by mle-roy           #+#    #+#             //
//   Updated: 2015/03/26 13:26:52 by mle-roy          ###   ########.fr       //
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
	std::vector<Player>				_snakes;
	std::list<Vector2>				_foods;
	std::vector<std::string>		_libs;
	std::string						_endGame;
	IGraphicLib *					_lib;
	bool							_pause;
	bool							_isEnded;
	void *							_dl_handle;
	bool							_isLibInit;
	int								_input;

	bool			_updateMap( void );
	void			_eatFood(Player & play);
	void			_initMap(Vector2 size);
	bool			_checkInput( void );
	void			_movesSnakes( void );
	void			_generateFood( void );
	void			_initLib( std::string lib );
	void			_closeLib( void );
	void			_setMap( void );

	GameManager( void );
	GameManager(GameManager const &src);
	GameManager &	operator=(GameManager const &rhs);

public:
	GameManager(int players, Vector2 size, std::vector<std::string> libs);
	~GameManager();

	void	Update();
};

#endif // ** GAMEMANAGER_HPP ** //
