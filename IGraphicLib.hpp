
#ifndef IGRAPHICLIB_HPP
# define IGRAPHICLIB_HPP

class IGraphicLib
{
public:
	virtual void	printMap(t_map & map) const = 0;
	virtual int		getInput( void ) const = 0;
	virtual void	gameOver( std::string toPrint ) const = 0;
	virtual void	initLibrary( void ) = 0;
	virtual void	closeLibrary( void ) = 0;
	virtual ~IGraphicLib( void ) {};
};

#endif // ** IGRAPHICLIB_HPP ** //
