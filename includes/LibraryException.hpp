// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   LibraryException.hpp                               :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/04/06 12:55:32 by mle-roy           #+#    #+#             //
//   Updated: 2015/04/06 13:29:47 by mle-roy          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef LIBRARYEXCEPTION_HPP
# define LIBRARYEXCEPTION_HPP

#include <stdexcept>

class LibraryException : public std::runtime_error
{
private:
	LibraryException const & operator=(LibraryException const &) throw();
	LibraryException() throw();

public:
	LibraryException(std::string const & errorMsg) throw();
	~LibraryException() throw();
	virtual const char* 		what() const throw();
};

# endif // ** LIBRARYEXCEPTION_HPP ** //
