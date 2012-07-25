/********************************************************************
	created:	2012/05/31
	created:	31:5:2012   3:26
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter\Player.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Dissertacao\AdaptiveShooter\src\AdaptiveShooter
	file base:	Player
	file ext:	cpp
	author:		Bruno Ba�re Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#include "Player.h"
#include "Entity.h"
#include "PlayerModelImpl.h"
#include "GameManager.h"
#include "TestScenePlayer.h"
#include "KeyboardController.h"
#include "GamepadController.h"

// Logging tool
//#define LOGOG_USE_PREFIX 1
//#include "logog.hpp"

Player::Player(float x, float y, float speedX, float speedY, unsigned int number, std::string sprite, PlayerModel* model, 
	unsigned int lives )
	: DynamicEntity( x, y, speedX, speedY ), _playerNumber( number ), _lives( lives ), _score( 0 ) ,_model( model ),
	_spriteResourceKey( sprite ), _weapon( new Weapon("Standard laser", "sprites/shot", 500) ),
	_controller( GamepadController::getNewGamepad( 0 ) )
{
	setCurrentWeapon( _weapon );

	if (_controller == NULL)
	{
		_controller = new KeyboardController();
	}

	GameManager* manager = GameManager::getInstance();
	CL_GraphicContext gc = manager->getWindow()->get_gc();
	_currentSprite = new CL_Sprite( gc, sprite, manager->getResourceManager() );

	CL_String descriptor = sprite.substr( sprite.find_last_of( "/" ) + 1 );

	for (int i = 0; i < _currentSprite->get_frame_count(); i++)
	{
		CL_String collisionResource = cl_format( "outlines/player/%1_00%2", descriptor, i );
		_currentOutlines.push_back( new CL_CollisionOutline( collisionResource.c_str(), manager->getResourceManager() ) );
	}

}



Player::~Player()
{
	delete _model;
	delete _currentSprite;
	delete _weapon;
	delete _controller;
}



#ifdef _DEBUG
void Player::draw()
{
	this->DynamicEntity::draw();
	int frame = getCurrentSprite()->get_current_frame();
	_currentOutlines[frame]->draw( getPosition().x, getPosition().y, CL_Colorf::red,
		GameManager::getInstance()->getWindow()->get_gc() );
}
#endif


void Player::update()
{
	float dt = GameManager::getInstance()->getDeltaTime();

	Shooter::update();

	if (_controller)
	{
		if (_controller->isControllerLeft())
		{
			setPositionX( getPosition().x - getSpeed().x * dt * 0.001f );
		}

		if (_controller->isControllerRight())
		{
			setPositionX( getPosition().x + getSpeed().x * dt * 0.001f );
		}

		if (_controller->isControllerUp())
		{
			setPositionY( getPosition().y - getSpeed().y * dt * 0.001f );
		}

		if (_controller->isControllerDown())
		{
			setPositionY( getPosition().y + getSpeed().y * dt * 0.001f );
		}

		if (_controller->isControllerFire())
		{
			addShots( getCurrentWeapon()->shoot( this ) );
		}
	}

	_currentSprite->update();

	boundToScreen();
}



unsigned int Player::getPlayerNumber() const 
{ 
	return _playerNumber; 
}



void Player::setPlayerNumber(unsigned int val) 
{ 
	_playerNumber = val; 
}



unsigned int Player::getLives() const 
{ 
	return _lives; 
}



void Player::setLives(unsigned int val) 
{ 
	_lives = val; 
}



void Player::addLives(unsigned int val)
{
	_lives += val;
}



void Player::subtractLives(unsigned int val)
{
	if (val <= _lives)
	{
		_lives -= val;
	}
	else
	{
		_lives = 0;
	}
}



PlayerModel* Player::getPlayerModel() const
{
	return _model;
}



void Player::setScore( int score )
{
	_score = score;
}



int Player::getScore() const
{
	return _score;
}



void Player::addToScore( int value )
{
	_score += value;
}



void Player::addShots( std::vector<Shot*> shots )
{
	TestScenePlayer *currentScene = dynamic_cast<TestScenePlayer*>( GameManager::getInstance()->peekScene() );

	for (std::vector<Shot*>::iterator it = shots.begin(); it != shots.end(); it++)
	{
		currentScene->addPlayerShot( (*it) );
	}
}
