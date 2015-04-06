
#include <string>
#include "LibraryException.hpp"

LibraryException::LibraryException(std::string const & errorMsg) throw()
  : std::runtime_error(errorMsg)
{

}

LibraryException::~LibraryException() throw()
{

}

const char* 		LibraryException::what() const throw()
{
	std::string		ret;

	ret = "Library exception : " + std::string(std::runtime_error::what());
	return (ret.c_str());
}
