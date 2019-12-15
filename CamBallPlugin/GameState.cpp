#include "GameState.h"

std::uintptr_t uip;

GameState::GameState(BakkesMod::Plugin::BakkesModPlugin world, bool ballHit)
{
	this->world = world;
}

std::string GameState::toString(unsigned long frame) {
	std::string build;
	auto game = world.gameWrapper->GetGameEventAsServer();
	build += "F" + std::to_string(frame) + " ";
	
	build += "B" + toString(game.GetGameBalls().Get(0)) + " ";

	auto player = game.GetCars().Get(0);
	if (player.IsNull())
	{
		world.cvarManager->log("null player");
	}
	else {
		build += "P" + std::to_string(0) + toString(player);
	}
	
	return build;
}

std::string GameState::toString(ActorWrapper act) {
	return "L" + toString(act.GetLocation()) + "V" + toString(act.GetVelocity());

}
std::string GameState::toString(Vector vec) {
	return std::to_string((int)vec.X) + "," + std::to_string((int)vec.Y) + "," + std::to_string((int)vec.Z);
}

GameState::~GameState()
{
}
