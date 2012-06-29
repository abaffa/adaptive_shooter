/********************************************************************
	created:	2011/11/29
	created:	29:11:2011   9:15
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Disserta��o\AdaptiveShooter\src\AdaptiveShooter\GameManager.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Disserta��o\AdaptiveShooter\src\AdaptiveShooter
	file base:	GameManager
	file ext:	cpp
	author:		Bruno Ba�re Pederassi Lomba de Araujo
	
	purpose:	GameManager implementation
*********************************************************************/

#include "GameManager.h"
#include "luafunctions.h"
#include "PlayerModelImpl.h"

GameManager* GameManager::_instance = 0;

GameManager::GameManager(): setup_core(), setup_display(), setup_gl(), _resourceManager(0), _quit(false), _player(0)
{
	L = lua_open();
	luaL_openlibs(L);
	RegisterLuaCLHelper(L);

	_window = new CL_DisplayWindow("Hello World", 640, 480);

	_aiManager = new AIManager(L);
	_loggerFile = new logog::LogFile("test.txt");
	// Player can only be created when there is already a GameManager instantiated
}



GameManager::~GameManager()
{
	cleanUp();
}



void GameManager::loadResource( std::string resourceFile )
{
	if (_resourceManager)
	{
		delete _resourceManager;
	}

	_resourceManager = new CL_ResourceManager(resourceFile);
}



int GameManager::loop()
{
	try
	{
		_last_time = CL_System::get_time();

		while (!_quit)
		{
			if(_window->get_ic().get_keyboard().get_keycode(CL_KEY_ESCAPE) == true)
			{
				_quit = true;
				break;
			}

			update();
			draw();

			// Read messages from the windowing system message queue, if any are available:
			CL_KeepAlive::process();

			// Avoid using 100% CPU in the loop:
			CL_System::sleep(10);
		}
	}
	catch(CL_Exception &exception)
	{
		// Create a console window for text-output if not available
		CL_ConsoleWindow console("Console", 80, 160);
		CL_Console::write_line("Exception caught: " + exception.get_message_and_stack_trace());
		console.display_close_message();
		
		cleanUp();

		return -1;
	}

	return 0;
}



void GameManager::pushScene(Scene* scene)
{
	_sceneStack.push(scene);
}



Scene* GameManager::popScene()
{
	Scene* top = NULL;

	if (!_sceneStack.empty())
	{
		top = _sceneStack.top();
		_sceneStack.pop();
	}

	return top;
}



void GameManager::draw()
{
	_window->get_gc().clear(CL_Colorf::black);

	if (!_sceneStack.empty())
	{
		_sceneStack.top()->draw();
	}

	// Make the stuff visible:
	_window->flip();
}



void GameManager::update()
{
	_current_time = CL_System::get_time();
	unsigned int time_difference = _current_time - _last_time;
	if (time_difference > 1000)
		time_difference = 1000;		// Limit the time difference, if the application was paused (eg, moving the window on WIN32)
	_time_delta_ms = static_cast<float> (time_difference);
	_last_time = _current_time;

	//Update
	if (!_sceneStack.empty())
	{
		_sceneStack.top()->update();
	} 
	else
	{
		_quit = true;
	}
}



GameManager* GameManager::getInstance()
{
	if(_instance == 0)
	{
		_instance = new GameManager();
	}

	return _instance;
}



CL_DisplayWindow* GameManager::getWindow()
{
	return _window;
}



CL_ResourceManager* GameManager::getResourceManager()
{
	return _resourceManager;
}



float GameManager::getDeltaTime()
{
	return _time_delta_ms;
}



lua_State* GameManager::getLuaState()
{
	return L;
}



void GameManager::getLuaState( lua_State* l )
{
	if (L != NULL)
	{
		lua_close(L);
	}

	L = l;
}



void GameManager::cleanUp()
{
	delete _aiManager;

	lua_close(L);

	L = NULL;

	delete _resourceManager;

	/** @TODO: Check if there is memory leak */
	/*while(!_sceneStack.empty())
	{
		_sceneStack.pop();
	}*/

	// Closes log operation
	delete _loggerFile;

	delete _window;
	_window = NULL;
}



/** @TODO: Rewrite when more players are supported*/
Player* GameManager::getPlayer( unsigned int n )
{
	return _player;
}



void GameManager::setupPlayer( unsigned int n )
{
	CL_Rect windowViewPort = _window->get_viewport();
	_player = new Player( 0.0f, 0.0f, 50.0f, 50.0f, n, "sprites/rwing", new PlayerModelImpl( 0.3f ), 3 );
	_player->setPositionX( windowViewPort.get_width()*0.5f - _player->getCurrentSprite()->get_width()*0.5f );
	_player->setPositionY(float(windowViewPort.get_height() - _player->getCurrentSprite()->get_height()) );

#ifdef _DEBUG
	_player->getPlayerModel()->setName("Normal");
#endif
}



AIManager* GameManager::getAIManager()
{
	return _aiManager;
}



logog::LogFile* GameManager::getLogger()
{
	return _loggerFile;
}
