#include <stdafx.h>
#include "character.h"
#include <tinyxml.h>
#include "ArriveSteering.h"
#include <params.h>


Character::Character() : mLinearVelocity(0.0f, 0.0f), mAngularVelocity(0.0f)
{
	RTTI_BEGIN
		RTTI_EXTEND (MOAIEntity2D)
	RTTI_END
}

Character::~Character()
{

}

void Character::OnStart()
{
    ReadParams("params.xml", mParams);
	mLocation = GetLoc();
	ArriveSteering::mArriveRadius = mParams.arrive_radius;
	ArriveSteering::mLerpFactor = 0.5f;
}

void Character::OnStop()
{

}

void Character::OnUpdate(float step)
{
	mAcceleration = ArriveSteering::CalculateAcceleration(*this, mParams.targetPosition, step);
	mLocation = GetLoc();
	SetLocation(mLocation.mX + mLinearVelocity.mX * step, mLocation.mY + mLinearVelocity.mY * step, 0);
	SetLoc(mLocation);
	SetLinearVelocity(mLinearVelocity.mX + mAcceleration.mX * step, mLinearVelocity.mY + mAcceleration.mY * step);
	
}

void Character::DrawDebug()
{
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(1.0f, 0.0f, 1.0f, 1.0f);
	MOAIDraw::DrawPoint(mParams.targetPosition);
	ArriveSteering::DrawVelocityDebug(this->GetLoc());
	gfxDevice.SetPenColor(0.0f, 1.0f, 1.0f, 1.0f);
	ArriveSteering::DrawAccelerationDebug(this->GetLoc());
	ArriveSteering::DrawArriveRadiusDebug(mParams.targetPosition);
	printf("Velocity --> X: %4.2f  Y: %4.2f   Acceleration --> X: %4.2f  Y: %4.2f\n", this->GetLinearVelocity().mX, this->GetLinearVelocity().mY, mAcceleration.mX, mAcceleration.mY);
}





// Lua configuration

void Character::RegisterLuaFuncs(MOAILuaState& state)
{
	MOAIEntity2D::RegisterLuaFuncs(state);
	
	luaL_Reg regTable [] = {
		{ "setLinearVel",			_setLinearVel},
		{ "setAngularVel",			_setAngularVel},
		{ NULL, NULL }
	};

	luaL_register(state, 0, regTable);
}

int Character::_setLinearVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float pX = state.GetValue<float>(2, 0.0f);
	float pY = state.GetValue<float>(3, 0.0f);
	self->SetLinearVelocity(pX, pY);
	return 0;	
}

int Character::_setAngularVel(lua_State* L)
{
	MOAI_LUA_SETUP(Character, "U")
	
	float angle = state.GetValue<float>(2, 0.0f);
	self->SetAngularVelocity(angle);

	return 0;
}
