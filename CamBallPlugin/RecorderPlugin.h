#pragma once
#pragma comment( lib, "bakkesmod.lib" )

#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "GameState.h"

class RecorderPlugin : public BakkesMod::Plugin::BakkesModPlugin
{
private:
	std::vector<std::string> history;
	bool ballHit;
	unsigned long frame;
public:
	virtual void onLoad();
	virtual void onUnload();
	void OnPhysicsTick(string);
	void OnPlayerTouchBall(string);
	void writeGameDump();
};