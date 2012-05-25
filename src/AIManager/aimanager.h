/********************************************************************
	created:	2011/11/24
	created:	24:11:2011   2:04
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Disserta��o\AdaptiveShooter\src\AIManager\aimanager.h
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Disserta��o\AdaptiveShooter\src\AIManager
	file base:	aimanager
	file ext:	h
	author:		Bruno Ba�re Pederassi Lomba de Araujo
	
	purpose:	AIManager is the class that manages AI updates, collects user data for dynamic difficulty adjustment
				and does the adjustment to each agent it manages. It's functionalities are customized via Lua functions
				implemented by the user-programmer and provided via a Lua state
*********************************************************************/
#ifndef AIManager_h__
#define AIManager_h__

#include <vector>
#include "aiagent.h"
#include "playermodel.h"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

class AIManager
{
public:
	/**
	 * Constructor
	 * 
	 * @param	  L	Lua state that is watched and manipulated
	 */
	AIManager( lua_State* L );

	/** Destructor */
	virtual ~AIManager();

	/**
	 * Checks PlayerModel updates and updates AIAgents accordingly
	 */
	void update();

	/**
	 * Sets Lua state observed
	 * @param	  L	New Lua state
	 */
	void SetLuaState( lua_State* L );

	/**
	 * Gets lua_State currently observed
	 * 
	 * @return	  lua_State*	Current Lua state
	 */
	lua_State* GetLuaState();

	/**
	 * Inserts a new AIAgent in the agents control list
	 *
	 * @param	  agent	AIAgent to be inserted
	 */
	void insertAgent( AIAgent* agent );

	/**
	 * Removes an agent from the agents control list
	 * 
	 * @param	  agent	AIAgent to be removed
	 * @return	  bool	True if agent was found and removed, false otherwise
	 */
	bool removeAgent( AIAgent* agent );
protected:

private:
	lua_State *_luaState;
	PlayerModel *_currentObservedPlayerModel;
	std::vector<PlayerModel*> _playerModels;
	std::vector<AIAgent*> _aiAgents;
};

#endif // AIManager_h__
