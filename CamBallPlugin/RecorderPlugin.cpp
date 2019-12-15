#include "RecorderPlugin.h"
#include <iostream>
#include <fstream>
#include <direct.h>

using namespace std::placeholders;

BAKKESMOD_PLUGIN(RecorderPlugin, "Recorder plugin", "1.0", PLUGINTYPE_FREEPLAY)

void RecorderPlugin::onLoad()
{
	cvarManager->log("Loaded plugin");
	cvarManager->registerNotifier("mydump", [&gw = this->gameWrapper, this](vector<string> commands) {
		cvarManager->log("Calling writeGameDump");
		writeGameDump();
	}, "Save this game's date to a file.", PERMISSION_FREEPLAY);

	gameWrapper->HookEvent("Function PlayerController_TA.Driving.PlayerMove", bind(&RecorderPlugin::OnPhysicsTick, this, _1));
	gameWrapper->HookEvent("Function TAGame.Ball_TA.OnCarTouch", bind(&RecorderPlugin::OnPlayerTouchBall, this, _1));
}

void RecorderPlugin::OnPhysicsTick(string cmd)
{
	auto state = GameState(*this, ballHit);
	history.push_back(state.toString(frame));
	if (ballHit)
	{
		ballHit = false;
	}
	frame++;
}

void RecorderPlugin::OnPlayerTouchBall(string cmd)
{
	ballHit = true;
}

void RecorderPlugin::writeGameDump()
{
	cvarManager->log("Starting writeGameDump");
	ofstream outputFile("game.log");
	for (unsigned int i = 0; i < history.size(); i++)
	{
		outputFile << history.at(i) + "\n";
	}

	char path[300];
	_getcwd(path, 300);
	string pathstr(path);
	gameWrapper->LogToChatbox("Path is " + pathstr);
	outputFile.close();
}

void RecorderPlugin::onUnload()
{
}