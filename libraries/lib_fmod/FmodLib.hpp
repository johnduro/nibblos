// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   FmodLib.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/01 17:06:29 by mle-roy           #+#    #+#             //
//   Updated: 2015/04/06 19:06:42 by mle-roy          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //


#ifndef FMODLIB_HPP
# define FMODLIB_HPP

#include "fmod/fmod.hpp"
#include "ISoundLib.hpp"
#include "LibraryException.hpp"

class FmodLib : public ISoundLib
{
private:
	FMOD::System     *_system; //handle to FMOD engine
	FMOD::Sound      *_eat;
	FMOD::Sound      *_death; //sound that will be loaded and played
	FmodLib(FmodLib const & src);
	FmodLib &		operator=(FmodLib const & src);

public:

	~FmodLib( void );
	FmodLib( void );
	void			playMusic( void );
	void			playEat( void );
	void			playDeath( void );
};

extern "C" {
	FmodLib		*createLib( void );
	void		deleteLib( FmodLib * lib );
	char		getType( void );
}

#endif // ** FMODLIB_HPP ** //
