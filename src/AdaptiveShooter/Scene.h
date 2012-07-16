/********************************************************************
	created:	2011/11/29
	created:	29:11:2011   8:19
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Disserta��o\AdaptiveShooter\src\AdaptiveShooter\Scene.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Disserta��o\AdaptiveShooter\src\AdaptiveShooter
	file base:	Scene
	file ext:	h
	author:		Bruno Ba�re Pederassi Lomba de Araujo
	
	purpose:	Scene interface definition
*********************************************************************/

#ifndef Scene_h__
#define Scene_h__

#include "Entity.h"
#include <list>

class Scene
{
public:

	enum SceneState
	{
		SS_RUNNING = 0,
		SS_COMPLETED
	};

	Scene();
	virtual ~Scene();

	virtual void draw();

	virtual void update();

	/**
	 * Inserts an Entity in list control.
	 * 
	 * @param[in]  entity	Pointer to entity to add
	 */
	void insertEntity(Entity* entity);

	/**
	 *	Removes an Entity from the control list.
	 * 
	 * @param[in]  entity	Pointer to entity to remove
	 */
	void removeEntity(Entity* entity);

	/**
	 * Gets an Entity from the control list
	 * 
	 * @param[in]  i		Position of the entity in the list
	 * @return	  Entity*	Pointer to the entity.
	 */
	Entity* getEntity(unsigned int i);

	/**
	 * Gets the pointer to the next scene
	 * 
	 * @return	  Scene*
	 */
	Scene* getNextScene();

	/**
	 * Sets next scene
	 * @param	  next
	 */
	void setNextScene(Scene* next);

protected:
	/**
	 * Changes to the next scene in the stack
	 */
	void changeToNextScene();

	std::list< Entity* > _entities; // List of scene Entities (Enemies, etc.)
	SceneState _sceneState;
	Scene *_nextScene;
private:
};

#endif // Scene_h__