#pragma once
#include "bakkesmod/plugin/bakkesmodplugin.h"

class GameState
{
private:
	BakkesMod::Plugin::BakkesModPlugin world;
public:
	GameState(BakkesMod::Plugin::BakkesModPlugin, bool);
	~GameState();
	std::string toString(unsigned long frame);
	std::string toString(Vector);
	std::string toString(ActorWrapper act);
};

