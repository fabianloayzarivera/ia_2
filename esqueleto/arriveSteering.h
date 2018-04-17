#ifndef __ARRIVE_STEERING_H__
#define __ARRIVE_STEERING_H__

#include <moaicore/MOAIEntity2D.h>
#include <params.h>
#include <uslscore\USVec2D.h>
#include <uslscore\USVec3D.h>

class Character;

class ArriveSteering : public MOAIEntity2D {
private:
	USVec2D mCharacterLocation;
	USVec2D mTargetLocation;
	
public:
	void SetCharacterLocation(USVec2D& loc) { mCharacterLocation = loc; }
	USVec2D GetCharacterLocation() const { return mCharacterLocation; };
	void SetTargetLocation(USVec2D& loc) { mTargetLocation = loc; }
	USVec2D GetTargetLocation() const { return mTargetLocation; };
	USVec2D Lerp(USVec2D mStart, USVec2D mEnd, float mFactor);

	static USVec2D mDesiredVelocity;
	static USVec2D mDesiredAcceleration;
	static float mArriveRadius;
	static float mLerpFactor;

	static USVec2D CalculateAcceleration(Character& character, USVec2D targetLocation, float step);
	static void DrawVelocityDebug(USVec2D characterLoc);
	static void DrawAccelerationDebug(USVec2D characterLoc);
	static void DrawArriveRadiusDebug(USVec2D targetLocation);
};

#endif