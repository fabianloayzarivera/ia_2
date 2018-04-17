#ifndef __SEEK_STEERING_H__
#define __SEEK_STEERING_H__

#include <moaicore/MOAIEntity2D.h>
#include <params.h>
#include <uslscore\USVec2D.h>
#include <uslscore\USVec3D.h>

class Character;

class SeekSteering : public MOAIEntity2D {
private:
	USVec2D mCharacterLocation;
	USVec2D mTargetLocation;
	

public:
	void SetCharacterLocation(USVec2D& loc) { mCharacterLocation = loc; }
	USVec2D GetCharacterLocation() const { return mCharacterLocation; };
	void SetTargetLocation(USVec2D& loc) { mTargetLocation = loc; }
	USVec2D GetTargetLocation() const { return mTargetLocation; };

	static USVec2D mDesiredVelocity;
	static USVec2D mDesiredAcceleration;
	
	static USVec2D CalculateAcceleration(Character& character, USVec2D targetLocation);
	static void DrawVelocityDebug(USVec2D characterLoc);
	static void DrawAccelerationDebug(USVec2D characterLoc);
};

#endif