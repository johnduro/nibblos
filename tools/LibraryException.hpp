
#ifndef LIBRARYEXCEPTION_HPP
# define LIBRARYEXCEPTION_HPP

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
