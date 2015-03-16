/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector2.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 15:05:34 by ael-kadh          #+#    #+#             */
//   Updated: 2015/03/16 19:23:58 by mle-roy          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include "Vector2.class.hpp"

Vector2::~Vector2() {}

Vector2::Vector2() : _x(0), _y(0) {}

Vector2::Vector2(int x, int y) {

   this->_x = x;
   this->_y = y;
}

Vector2::Vector2(Vector2 const &src) {

   this->_x = src.getX();
   this->_y = src.getY();
}

Vector2 &   Vector2::operator=(Vector2 const &rhs) {

   this->_x = rhs.getX();
   this->_y = rhs.getY();
   return (*this);
}

/* ------------------------------------------------------------------------ */
Vector2 const   Vector2::operator+(Vector2 const &rhs) {

   int x = this->_x + rhs.getX();
   int y = this->_y + rhs.getY();

   return Vector2(x, y);
}

Vector2 &   Vector2::operator+=(Vector2 const &rhs) {

   this->_x += rhs.getX();
   this->_y += rhs.getY();
   return (*this);
}

Vector2 const   Vector2::operator-(Vector2 const &rhs) {

   int x = this->_x - rhs.getX();
   int y = this->_y - rhs.getY();

   return Vector2(x, y);
}

Vector2 &   Vector2::operator-=(Vector2 const &rhs) {

   this->_x -= rhs.getX();
   this->_y -= rhs.getY();

   return (*this);
}

Vector2 const   Vector2::operator*(Vector2 const &rhs) {

   int x = this->_x * rhs.getX();
   int y = this->_y * rhs.getY();

   return Vector2(x, y);
}

Vector2 &   Vector2::operator*=(Vector2 const &rhs) {

   this->_x *= rhs.getX();
   this->_y *= rhs.getY();

   return (*this);
}

Vector2 const   Vector2::operator/(Vector2 const &rhs) {

	int x = 0;
	int y = 0;

	if (rhs.getX())
		x = this->_x / rhs.getX();
	if (rhs.getY())
		y = this->_y / rhs.getY();

   return Vector2(x, y);
}

Vector2 &   Vector2::operator/=(Vector2 const &rhs) {

	if (rhs.getX())
		this->_x /= rhs.getX();
	else
		this->_x = 0;
	if (rhs.getY())
		this->_y /= rhs.getY();
	else
		this->_y = 0;

	return (*this);
}

bool      Vector2::operator!=(Vector2 const &rhs) const {

   if (this->_x == rhs.getX() && this->_y == rhs.getY())
      return false;
   return true;
}

bool      Vector2::operator==(Vector2 const &rhs) const {
   if (*this != rhs)
      return false;
   return true;
}

/* ------------------------------------------------------------------------- */
Vector2 const   Vector2::operator+(int const &rhs) {

   int x = this->_x + rhs;
   int y = this->_y + rhs;

   return Vector2(x, y);
}

Vector2 &   Vector2::operator+=(int const &rhs) {

   this->_x += rhs;
   this->_y += rhs;

   return (*this);
}

Vector2 const   Vector2::operator-(int const &rhs) {

   int x = this->_x - rhs;
   int y = this->_y - rhs;

   return Vector2(x, y);
}

Vector2 &   Vector2::operator-=(int const &rhs) {

   this->_x -= rhs;
   this->_y -= rhs;

   return (*this);
}

Vector2 const   Vector2::operator*(int const &rhs) {

   int x = this->_x * rhs;
   int y = this->_y * rhs;

   return Vector2(x, y);
}

Vector2 &   Vector2::operator*=(int const &rhs) {

   this->_x *= rhs;
   this->_y *= rhs;

   return (*this);
}

Vector2 const   Vector2::operator/(int const &rhs) {

	int x = 0;
	int y = 0;

	if (rhs)
	{
		x = this->_x / rhs;
		y = this->_y / rhs;
	}

   return Vector2(x, y);
}

Vector2 &   Vector2::operator/=(int const &rhs) {

	if (rhs)
	{
		this->_x /= rhs;
		this->_y /= rhs;
	}
	else
	{
		this->_x = 0;
		this->_y = 0;
	}
	return (*this);
}

double      Vector2::Length() {

   return pow(this->_x, 2) + pow(this->_y, 2);
}

/* --------------------------- Setters & Getters --------------------------- */
int   Vector2::getX() const {return this->_x;}
int   Vector2::getY() const {return this->_y;}

void   Vector2::setX(int const x) {this->_x = x;}
void   Vector2::setY(int const y) {this->_y = y;}

/* ------------------------------ ToString() ------------------------------ */
std::ostream &   operator<<(std::ostream &a, Vector2 const &vec)
{
   a << "Vector2(" << vec.getX() << ", " << vec.getY() << ")";
   return a;
}
