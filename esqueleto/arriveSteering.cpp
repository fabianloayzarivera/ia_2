#include <stdafx.h>
#include "arriveSteering.h"
#include "character.h"
#include <tinyxml.h>
#include <params.h>

USVec2D ArriveSteering::mDesiredVelocity(0, 0);
USVec2D ArriveSteering::mDesiredAcceleration(0, 0);
float ArriveSteering::mArriveRadius = 0.0f;
float ArriveSteering::mLerpFactor = 0.1f;

USVec2D ArriveSteering::CalculateAcceleration(Character& character, USVec2D targetLocation, float step) {
	
	USVec2D mDesiredVel(targetLocation - character.GetLoc());
	USVec2D mDistance = mDesiredVel;
	mDesiredVel.Norm();
	mDesiredVel.Scale(character.GetParams().max_velocity);
	mDesiredVelocity = mDesiredVel;

	USVec2D mDesiredAcc(mDesiredVel - character.GetLinearVelocity());
	mDesiredAcc.Norm();
	mDesiredAcc.Scale(character.GetParams().max_acceleration);
	mDesiredAcceleration = mDesiredAcc;
	
	if (mDistance.Length() < character.GetParams().arrive_radius) {
		//Inside Arrive Radius
		USVec2D mCurrentLinearVelocity = character.GetLinearVelocity();
		USVec2D mTargetVelocity(0.0f, 0.0f);
		USVec2D mInterpolatedVelocity = (mDesiredVelocity * (mDistance.Length() / character.GetParams().arrive_radius));
		character.SetLinearVelocity(mInterpolatedVelocity.mX, mInterpolatedVelocity.mY);
		
		return USVec2D(0.0f, 0.0f);
	}
	
	return mDesiredAcceleration;
	
}

void ArriveSteering::DrawVelocityDebug(USVec2D characterLoc) {

	MOAIDraw::DrawLine(characterLoc, characterLoc + mDesiredVelocity);

}

void ArriveSteering::DrawAccelerationDebug(USVec2D characterLoc) {

	MOAIDraw::DrawLine(characterLoc, characterLoc + mDesiredAcceleration);

}

void ArriveSteering::DrawArriveRadiusDebug(USVec2D targetLocation) {

	MOAIDraw::DrawEllipseOutline(targetLocation.mX, targetLocation.mY, mArriveRadius, mArriveRadius, 100);
}

