/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector2.class.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/10 15:05:46 by ael-kadh          #+#    #+#             */
/*   Updated: 2015/03/16 19:14:56 by mle-roy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Vector2_CLASS_HPP
# define Vector2_CLASS_HPP

#include <cmath>
#include <iostream>

class Vector2
{
   private :

   /* ---------- Attributes ---------- */


   public :

   /* ---------- Functions ---------- */
   ~Vector2();
   Vector2();
   Vector2(int x, int y);
   Vector2(Vector2 const &src);
   Vector2 &   operator=(Vector2 const &rhs);

   Vector2 const   operator+(Vector2 const &rhs);
   Vector2 &   operator+=(Vector2 const &rhs);
   Vector2 const   operator-(Vector2 const &rhs);
   Vector2 &   operator-=(Vector2 const &rhs);
   Vector2 const   operator*(Vector2 const &rhs);
   Vector2 &   operator*=(Vector2 const &rhs);
   Vector2 const   operator/(Vector2 const &rhs);
   Vector2 &   operator/=(Vector2 const &rhs);

   Vector2 const   operator+(int const &rhs);
   Vector2 &   operator+=(int const &rhs);
   Vector2 const   operator-(int const &rhs);
   Vector2 &   operator-=(int const &rhs);
   Vector2 const   operator*(int const &rhs);
   Vector2 &   operator*=(int const &rhs);
   Vector2 const   operator/(int const &rhs);
   Vector2 &   operator/=(int const &rhs);

   bool        operator==(Vector2 const &rhs) const;
   bool        operator!=(Vector2 const &rhs) const;

   double      Length();

   /* ---------- Setters & Getters ---------- */
   int   getX() const;
   int   getY() const;

   void   setX(int const x);
   void   setY(int const y);

   int   _x;
   int   _y;
};

std::ostream &   operator<<(std::ostream &a, Vector2 const &vec);

#endif
