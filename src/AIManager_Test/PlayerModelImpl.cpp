/********************************************************************
	created:	2011/11/25
	created:	25:11:2011   16:39
	filename: 	C:\Users\Bruno\Documents\Mestrado\2011.2\Disserta��o\Jogo\src\AIManager_Test\PlayerModelImpl.cpp
	file path:	C:\Users\Bruno\Documents\Mestrado\2011.2\Disserta��o\Jogo\src\AIManager_Test
	file base:	PlayerModelImpl
	file ext:	cpp
	author:		Bruno Ba�re Pederassi Lomba de Araujo
	
	purpose:	
*********************************************************************/

#include "PlayerModelImpl.h"

PlayerModelImpl::PlayerModelImpl(float valor)
{
	_valor = valor;
}

float PlayerModelImpl::Compare( PlayerModel* comparable )
{
	if (comparable)
	{
		return this->_valor - ((PlayerModelImpl*)comparable)->_valor;
	} 
	else
	{
		return this->_valor;
	}
}
