/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/03/16 15:48:42 by ael-kadh          #+#    #+#             */
//   Updated: 2015/03/17 19:16:23 by mle-roy          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include "Player.hpp"

/* ----------------------- Constructors & Destructors ----------------------- */

Player::~Player() {}

// Player::Player() : _length(2), _dir(Vector2(1, 0)) {this->_name = "player";}

// Player::Player(Vector2 pos) : _length(1), dir(Vector2(1, 0))
// {
// 	this->_links.push_back(pos);
// 	// last = Vector2(pos.getX() - 1, pos.getY());
// 	this->_links.push_back(Vector2(pos.getX() - 1, pos.getY()));
// 	this->_last = this->_links.back();
// 	this->_name = "player";
// }

void		Player::_initFirstSnake(Vector2 pos, Vector2 dir)
{
	this->_links.push_back(pos);
	for (int i = 0; i < (this->_length - 1); i++)
		this->_links.push_back(pos - (dir * i));

	this->_last = this->_links.back();
}

Player::Player(std::string name, Vector2 pos) : _length(4), _dir(RIGHT), _name(name)
{
	this->_initFirstSnake(pos, RIGHT);
}

Player::Player(std::string name, Vector2 pos, Vector2 dir) : _length(4), _dir(dir), _name(name)
{
	this->_initFirstSnake(pos, dir);
}

Player::Player(Player const &src) {

   this->_length = src.getLength();
   this->_dir = src.getDir();
   this->_name = src.getName();
}

Player &   Player::operator=(Player const &rhs) {

   this->_length = rhs.getLength();
   this->_dir = rhs.getDir();
   this->_name = rhs.getName();

   return (*this);
}

/* --------------------------- SETTERS & GETTERS --------------------------- */

int						Player::getLength() const {return this->_length;}

Vector2 const &			Player::getDir() const {return this->_dir;}

std::string const &		Player::getName() const {return this->_name;}

Vector2 const &			Player::getLast() const {return this->_last;}

Vector2 const &			Player::getHead() const {return this->_links.front();}

std::list<Vector2> const &		Player::getLinks( void ) const {return this->_links;}

void					Player::addLink( void )
{
	this->_links.push_back(this->_last);
	this->_length++;
}

void					Player::setDir(Vector2 dir) {

	if (this->_dir == UP)
		this->_dir = dir;
	else if	(this->_dir == DOWN)
	{
		if (dir == LEFT)
			this->_dir = RIGHT;
		else
			this->_dir = LEFT;
	}
	else if (this->_dir == RIGHT)
	{
		if (dir == RIGHT)
			this->_dir = DOWN;
		else
			this->_dir = UP;
	}
	else
	{
		if (dir == LEFT)
			this->_dir = DOWN;
		else
			this->_dir = UP;
	}
}

void					Player::setLast( void ){ this->_last = this->_links.back(); }

/* ------------------------------ Methodes ---------------------------- */

void			Player::movSnake( void )
{
	std::list<Vector2>::iterator		it;
	std::list<Vector2>::iterator		ite = this->_links.end();
	bool								flag = true;
	Vector2								tmp;
	Vector2								tmp2;

	this->_last = this->_links.back();
	for (it = this->_links.begin(); it != ite; it++)
	{
		tmp2 = *it;
		if (flag)
		{
			tmp = *it;
			*it += this->_dir;
			flag = false;
			continue ;
		}
		*it = tmp;
		tmp = tmp2;
	}
}
