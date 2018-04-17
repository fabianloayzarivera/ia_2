#include <stdafx.h>
#include "seekSteering.h"
#include "character.h"
#include <tinyxml.h>
#include <params.h>

USVec2D SeekSteering::mDesiredVelocity(0,0);
USVec2D SeekSteering::mDesiredAcceleration(0,0);
USVec2D SeekSteering::CalculateAcceleration(Character& character, USVec2D targetLocation) {
	
	USVec2D mDesiredVel(targetLocation - character.GetLoc());
	mDesiredVel.Norm();
	mDesiredVel.Scale(character.GetParams().max_velocity);
	mDesiredVelocity = mDesiredVel;
	USVec2D mDesiredAcc(mDesiredVel - character.GetLinearVelocity());
	mDesiredAcc.Norm();	
	mDesiredAcc.Scale(character.GetParams().max_acceleration);	
	mDesiredAcceleration = mDesiredAcc;

	return mDesiredAcc;
}

void SeekSteering::DrawVelocityDebug(USVec2D characterLoc) {	

	MOAIDraw::DrawLine(characterLoc, characterLoc + mDesiredVelocity);
	
}

void SeekSteering::DrawAccelerationDebug(USVec2D characterLoc) {

	MOAIDraw::DrawLine(characterLoc, characterLoc + mDesiredAcceleration);

}


