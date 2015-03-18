// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   IGraphicLib.hpp                                    :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/03/17 15:34:58 by mle-roy           #+#    #+#             //
//   Updated: 2015/03/18 16:11:05 by mle-roy          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef IGRAPHICLIB_HPP
# define IGRAPHICLIB_HPP

#include "TMap.hpp"

# define STD_LEFT 1
# define STD_RIGHT 2
# define STD_UP 3
# define STD_DOWN 4
# define STD_SPACE 5
# define STD_EXIT 6

class IGraphicLib
{
public:
	virtual void	printMap(TMap & map) = 0;
	virtual int		getInput( void ) = 0;
	virtual void	gameOver( std::string toPrint ) const = 0;
	virtual void	initLibrary( TMap & map ) = 0;
	virtual void	closeLibrary( void ) = 0;
	virtual ~IGraphicLib( void ) {};
};

#endif // ** IGRAPHICLIB_HPP ** //
