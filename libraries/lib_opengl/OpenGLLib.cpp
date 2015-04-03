#include "OpenGLLib.hpp"
#include "Player.hpp"

// Constructeur de Destucteur

SceneOpenGL::SceneOpenGL() : m_titreFenetre("SNAKE"), m_largeurFenetre(1200), m_hauteurFenetre(800), m_fenetre(0), m_contexteOpenGL(0) {}

void 	SceneOpenGL::initLibrary( TMap & map )
{
	scale = Vector3(40, 40, 20) / 0.5f;
	scale.setZ(scale.getZ() * -0.5);

	if(this->initialiserFenetre() == false)
	{
		std::cout << "window init" << std::endl;
		return;
	}
	if(this->initGL() == false)
	{
		std::cout << "GL init" << std::endl;
		return;
	}

	// Variables
	this->echelle = (64/15);

	// Boucle principale
	glEnable (GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1, 0, 1, 0, 3);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0.5, 0.4, -2.); // (0.8, 0.3, -2.)
	// glRotatef(180, 0, 1, 0);
	// glRotatef(60, 0, 0, 1);
	glRotatef(180, 1, 0, 0);
	glRotatef(45, 0, 0, 1);
	glScalef(1/this->scale.getX(), 1/this->scale.getY(), 1/this->scale.getZ());
}

SceneOpenGL::~SceneOpenGL() {}

void	SceneOpenGL::closeLibrary( void )
{
	SDL_GL_DeleteContext(m_contexteOpenGL);
	SDL_DestroyWindow(m_fenetre);
	SDL_Quit();
}

// Methodes

bool SceneOpenGL::initialiserFenetre( void )
{
	// Initialisation de la SDL

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << std::endl;
		SDL_Quit();

		return false;
	}

	// Version d'OpenGL

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	// Double Buffer

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// Creation de la fenetre

	m_fenetre = SDL_CreateWindow(m_titreFenetre.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_largeurFenetre, m_hauteurFenetre, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	if(m_fenetre == 0)
	{
		std::cout << "Erreur lors de la creation de la fenetre : " << SDL_GetError() << std::endl;
		SDL_Quit();

		return false;
	}

	// Creation du contexte OpenGL

	m_contexteOpenGL = SDL_GL_CreateContext(m_fenetre);

	if(m_contexteOpenGL == 0)
	{
		std::cout << SDL_GetError() << std::endl;
		SDL_DestroyWindow(m_fenetre);
		SDL_Quit();

		return false;
	}

	return true;
}

bool SceneOpenGL::initGL( void )
{
#ifdef WIN32

	// On initialise GLEW

	GLenum initialisationGLEW(glewInit());

	// Si l'initialisation a echoue :

	if(initialisationGLEW != GLEW_OK)
	{
		// On affiche l'erreur grace a la fonction : glewGetErrorString(GLenum code)

		std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;

		// On quitte la SDL

		SDL_GL_DeleteContext(m_contexteOpenGL);
		SDL_DestroyWindow(m_fenetre);
		SDL_Quit();

		return false;
	}

#endif

	// Tout s'est bien passe, on retourne true
	return true;
}

Vector3 SceneOpenGL::setColor(float height, float echelle)
{
	height = (height) / echelle;
	if (height < 0.3f)
		return Vector3(height, height, height);
	else if (height < 0.8f)
		return Vector3(0, height, 0);
	else
		return Vector3(height, height, height);

	return Vector3();
}

void SceneOpenGL::drawDot(Vector3 p)
{
	glBegin(GL_POINTS);
	glVertex3f(p.getX(), p.getY(), p.getZ());
	glEnd();
	glFlush();
}

void SceneOpenGL::drawLine(Vector3 p1, Vector3 p2)
{
	glBegin(GL_LINES);
	glVertex3f(p1.getX(), p1.getY(), p1.getZ());
	glVertex3f(p2.getX(), p2.getY(), p2.getZ());
	glEnd();
	glFlush();
}

void SceneOpenGL::drawTriangles(Vector3 p1, Vector3 p2, Vector3 p3, float echelle)
{
	glBegin(GL_TRIANGLE_STRIP);
	setColor(p1.getZ(), echelle);
	glVertex3f(p1.getX(), p1.getY(), p1.getZ());
	setColor(p2.getZ(), echelle);
	glVertex3f(p2.getX(), p2.getY(), p2.getZ());
	setColor(p3.getZ(), echelle);
	glVertex3f(p3.getX(), p3.getY(), p3.getZ());
	glEnd();
	glFlush();
}

void SceneOpenGL::drawQuad(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4)
{
	glBegin(GL_QUADS);
	glVertex3f(p1.getX(), p1.getY(), p1.getZ());
	glVertex3f(p2.getX(), p2.getY(), p2.getZ());
	glVertex3f(p3.getX(), p3.getY(), p3.getZ());
	glVertex3f(p4.getX(), p4.getY(), p4.getZ());
	glEnd();
	glFlush();
}

float *SceneOpenGL::getTheFucknColor(float r, float g, float b, float a) const
{
	float *color = new float[120];
	float co[] =
	{
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a,
		r, g, b, a
	};
	for (int i = 0; i < 120; i++)
		color[i] = co[i];
	return color;
}

void SceneOpenGL::drawVox(Vector3 p, int mmm) const
{
	float x0 = p.getX() - 0.5f;
	float x1 = p.getX() + 0.5f;
	float y0 = p.getY() - 0.5f;
	float y1 = p.getY() + 0.5f;
	float z0 = p.getZ() - 0.5f;
	float z1 = p.getZ() + 0.5f;

	Vector3 pLBU = Vector3(x0, y0, z0);
	Vector3 pLBD = Vector3(x0, y0, z1);
	Vector3 pRBD = Vector3(x1, y0, z1);
	Vector3 pRBU = Vector3(x1, y0, z0);

	Vector3 pLFU = Vector3(x0, y1, z0);
	Vector3 pLFD = Vector3(x0, y1, z1);
	Vector3 pRFD = Vector3(x1, y1, z1);
	Vector3 pRFU = Vector3(x1, y1, z0);


	GLfloat vertices[] =
	{
		// FACE LEFT //
		pLBU._x, pLBU._y, pLBU._z, /* sommet 0 */
		pLBD._x, pLBD._y, pLBD._z, /* sommet 1 */
		pLFU._x, pLFU._y, pLFU._z, /* sommet 2 */

		pLBU._x, pLBU._y, pLBU._z, /* sommet 0 */
		pLBD._x, pLBD._y, pLBD._z, /* sommet 1 */
		pLFD._x, pLFD._y, pLFD._z, /* sommet 2 */

		// FACE RIGHT //
		pRBU._x, pRBU._y, pRBU._z, /* sommet 0 */
		pRBD._x, pRBD._y, pRBD._z, /* sommet 1 */
		pRFU._x, pRFU._y, pRFU._z, /* sommet 2 */

		pRBU._x, pRBU._y, pRBU._z, /* sommet 0 */
		pRBD._x, pRBD._y, pRBD._z, /* sommet 1 */
		pRFD._x, pRFD._y, pRFD._z, /* sommet 2 */

		// FACE UP //
		pLBU._x, pLBU._y, pLBU._z, /* sommet 0 */
		pRBU._x, pRBU._y, pRBU._z, /* sommet 1 */
		pLFU._x, pLFU._y, pLFU._z, /* sommet 2 */

		pLBU._x, pLBU._y, pLBU._z, /* sommet 0 */
		pRBU._x, pRBU._y, pRBU._z, /* sommet 1 */
		pRFU._x, pRFU._y, pRFU._z, /* sommet 2 */

		// FACE FRONT //
		pLFU._x, pLFU._y, pLFU._z, /* sommet 0 */
		pLFD._x, pLFD._y, pLFD._z, /* sommet 1 */
		pRFU._x, pRFU._y, pRFU._z, /* sommet 2 */

		pLFU._x, pLFU._y, pLFU._z, /* sommet 0 */
		pLFD._x, pLFD._y, pLFD._z, /* sommet 1 */
		pRFD._x, pRFD._y, pRFD._z, /* sommet 2 */

		// FACE BACK //
		pLBU._x, pLBU._y, pLBU._z, /* sommet 0 */
		pLFD._x, pLFD._y, pLFD._z, /* sommet 1 */
		pRFU._x, pRFU._y, pRFU._z, /* sommet 2 */

		pLBU._x, pLBU._y, pLBU._z, /* sommet 0 */
		pLFD._x, pLFD._y, pLFD._z, /* sommet 1 */
		pRFD._x, pRFD._y, pRFD._z, /* sommet 2 */
	};

	float *color;

	switch (mmm)
	{
		case 1:
			color = getTheFucknColor(1, 0.4f, 0, 1);
			break;
		case 2:
			color = getTheFucknColor(1, 1, 1, 1);
			break;
		case 3:
			color = getTheFucknColor(1, 0, 0, 1);
			break;
		case 4:
			color = getTheFucknColor(0.7f, 0.7f, 0, 1);
			break;
	case 5:
		color = getTheFucknColor(0, 0, 0, 1);
		break;
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glColorPointer(4, GL_FLOAT, 0, color);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glDrawArrays(GL_TRIANGLES, 0, 30);

	delete[] color;

	// deactivate vertex arrays after drawing
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

void				SceneOpenGL::drawFace(Vector2 a, Vector2 b, Vector2 c, Vector2 g)
{
	GLfloat vertices[] =
	{
		a._x, a._y, 0, /* sommet 0 */
		b._x, b._y, 0, /* sommet 1 */
		c._x, c._y, 0, /* sommet 2 */

		a._x, a._y, 0, /* sommet 0 */
		g._x, g._y, 0, /* sommet 1 */
		c._x, c._y, 0  /* sommet 2 */
	};

	float color[] = {
		0, 1, 0, 1,
		0, 1, 0, 1,
		0, 1, 0, 1,
		0, 1, 0, 1,
		0, 1, 0, 1,
		0, 1, 0, 1
	};

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glColorPointer(4, GL_FLOAT, 0, color);
	glVertexPointer(3, GL_FLOAT, 0, vertices);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	// deactivate vertex arrays after drawing
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
}

int		SceneOpenGL::getInput( void )
{
		// Gestion des evenements

	SDL_PollEvent(&m_evenements);

	if (m_evenements.window.event == SDL_WINDOWEVENT_CLOSE || m_evenements.window.event == SDLK_q)
		return STD_EXIT;
	if (m_evenements.window.event == SDLK_SPACE)
		return STD_SPACE;
	if (m_evenements.key.keysym.sym == SDLK_RIGHT)
		return STD_RIGHT;
	if (m_evenements.key.keysym.sym == SDLK_LEFT)
		return STD_LEFT;
	if (m_evenements.key.keysym.sym == SDLK_UP)
		return STD_UP;
	if (m_evenements.key.keysym.sym == SDLK_DOWN)
		return STD_DOWN;
	if (m_evenements.key.keysym.sym == SDLK_F1)
		return STD_LIB1;
	if (m_evenements.key.keysym.sym == SDLK_F2)
		return STD_LIB2;
	if (m_evenements.key.keysym.sym == SDLK_F3)
		return STD_LIB3;
	return 0;
}

void SceneOpenGL::printMap( TMap const & map )
{
	// Nettoyage de l'ecran

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int sY = static_cast<int>(round((map.size.getY() + 2) / 2));
	int sX = static_cast<int>(round((map.size.getX() + 2) / 2));

	this->drawFace(Vector2(-sX, -sY), Vector2(-sX, sY - 1), Vector2(sX - 1, sY - 1), Vector2(sX - 1, -sY));

	for (int y = -sY-1; y < sY; y++)
	{
		for (int x = -sX-1; x < sX; x++)
		{
			if ((y == -sY-1 || x == -sX-1) || (y == sY - 1 || x == sX - 1))
				this->drawVox(Vector3(x, y, 1), 2);
		}
	}

	std::list<Vector2>::const_iterator		it;
	std::list<Vector2>::const_iterator		ite;

	std::vector<Player>::const_iterator		itP;
	std::vector<Player>::const_iterator		iteP;

	if (map.rocks.size() > 0)
	{
		ite = map.rocks.end();
		for (it = map.rocks.begin(); it != ite; it++)
			this->drawVox(Vector3(it->getX() - sX, it->getY() - sY, 1), 5);
		//this->_printEntity(*it, '%', NC_RED, map.size);
	}

	if (map.foods.size() > 0)
	{
		ite = map.foods.end();
		for (it = map.foods.begin(); it != ite; it++)
		{
			// std::cout << "x= " <<  it->getX() << ", y= " << it->getY() << std::endl;
			this->drawVox(Vector3(it->getX() - sX, it->getY() - sY, 1), 1);
		}
	}

	if (map.snakes.size() > 0)
	{
		bool		head;

		iteP = map.snakes.end();
		for (itP = map.snakes.begin(); itP != iteP; itP++)
		{
			head = true;
			// if (itP != map.snakes.begin())
			// {
			// 	headPrint = NC_YELLOW;
			// 	bodyPrint = NC_MAGENTA;
			// }
			ite = itP->getLinks().end();
			for (it = itP->getLinks().begin(); it != ite; it++)
			{
				if (head)
				{
					// std::cout << "x = " << it->getX() << ", y= " << it->getY() << std::endl;
					this->drawVox(Vector3(it->getX() - sX, it->getY() - sY, 1), 3);
					head = false;
				}
				else
					this->drawVox(Vector3(it->getX() - sX, it->getY() - sY, 1), 4);
			}
		}
	}

	// for (int y = 0; y < map.size.getY(); y++)
	// {
	// 	for (int x = 0; x < map.size.getX(); x++)
	// 	{
	// 		if (map.map[y][x] == 'F')
	// 			this->drawVox(Vector3(x - sX, y - sY, 1), 1);
	// 		if (map.map[y][x] == '1')
	// 			this->drawVox(Vector3(x - sX, y - sY, 1), 3);
	// 		if (map.map[y][x] == '*')
	// 			this->drawVox(Vector3(x - sX, y - sY, 1), 4);
	// 	}
	// }

	// Actualisation de la fenetre

	glFlush();
	SDL_GL_SwapWindow(m_fenetre);
}

// void 	SceneOpenGL::gameOver( std::string toPrint ) const {}

SceneOpenGL		*createLib( void )
{
	return new SceneOpenGL();
}

void			deleteLib(SceneOpenGL * lib)
{
	delete lib;
}
