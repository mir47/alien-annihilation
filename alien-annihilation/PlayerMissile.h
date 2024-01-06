/*
-------------------------------------------------------------------------

	PlayerMissile.h

-------------------------------------------------------------------------
*/

#ifndef PLAYERMISSILE_H
#define PLAYERMISSILE_H

#include <iostream>
#include "PlayerShip.h"
#include "Battlefield.h"
#include "Missile.h"


using namespace std;


//! Class implementation to create a PlayerMissile
/*! PlayerMissile is a class that creates player missiles and contains functions for moving these missiles. PlayerMissile is derived from the Missile class.
*/
class PlayerMissile : public Missile
{
public:
	//! The default constructor
	PlayerMissile();
	//! Constructor with parameters
	PlayerMissile(PlayerShip& gamePlayerShip);

	//! Moves PlayerMissile along Battlefield circles in the direction it was fired
	void MoveAlongCircles(Battlefield& gameBattlefield);
	//! Moves PlayerMissile continuously in the direction it was fired
	void MoveContinuous(Battlefield& gameBattlefield);

private:
	bool _crossCentre; //!< This flag is set to true if PlayerMissile has crossed the centre of the Battlefield
};

#endif