#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include <moaicore/MOAIEntity2D.h>
#include <params.h>


class Character : public MOAIEntity2D
{
public:
	DECL_LUA_FACTORY(Character)
protected:
	virtual void OnStart();
	virtual void OnStop();
	virtual void OnUpdate(float step);
public:
	virtual void DrawDebug();

	Character();
	~Character();

	void SetLinearVelocity(float x, float y) { mLinearVelocity.mX = x; mLinearVelocity.mY = y; }
	void SetAngularVelocity(float angle) { mAngularVelocity = angle; }
	void SetLocation(float x, float y, float z) { mLocation.mX = x; mLocation.mY = y; mLocation.mZ; }
	USVec2D GetLinearVelocity() const { return mLinearVelocity; }
	float GetAngularVelocity() const { return mAngularVelocity; }
	Params GetParams() { return mParams; }
	
private:
	USVec2D mLinearVelocity;
	float mAngularVelocity;
	USVec3D mLocation;
	USVec2D mAcceleration;

	Params mParams;
	
	// Lua configuration
public:
	virtual void RegisterLuaFuncs(MOAILuaState& state);
private:
	static int _setLinearVel(lua_State* L);
	static int _setAngularVel(lua_State* L);
};

#endif