/********************************************************************
	created:	2011/11/29
	created:	29:11:2011   8:25
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Disserta��o\AdaptiveShooter\src\AdaptiveShooter\Menu.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Disserta��o\AdaptiveShooter\src\AdaptiveShooter
	file base:	Menu
	file ext:	h
	author:		Bruno Ba�re Pederassi Lomba de Araujo
	
	purpose:	Menu and MenuState class definitions
*********************************************************************/

#ifndef Menu_h__
#define Menu_h__

#include "Scene.h"
#include "MenuItem.h"

/**
 * Menu is a class for handling menu-like interfaces for changing game options
 */
class Menu : public Scene
{
public:
	Menu();
	~Menu();

	virtual void update();
	virtual void draw();

protected:
	void StateDown();
	void StateUp();
	void ExecuteState();

private:
	int _menuState;
	Entity* _menuPointer;
	std::vector<MenuItem> _menuItems;
};

#endif // Menu_h__