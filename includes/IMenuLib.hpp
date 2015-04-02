// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IMenuLib.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/02 13:12:27 by mle-roy           #+#    #+#             //
//   Updated: 2015/04/02 17:49:00 by mle-roy          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef IMENULIB_HPP
# define IMENULIB_HPP

#include <utility>
#include <string>

struct TOption
{
	std::pair<std::string, std::string>		names;
	bool									twoPlayers;
	bool									obstacles;
	bool									sound;
	bool									isExited;
};

class IMenuLib
{
public:
	virtual TOption		startMenu( void ) = 0;
	// virtual TOption		getMenuOption( void ) const = 0;
	virtual ~IMenuLib( void ) {};
};

#endif // ** IMENULIB_HPP ** //
