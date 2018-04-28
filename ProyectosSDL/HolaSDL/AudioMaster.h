#pragma once

#include <al.h>
#include <alc.h>
#include <vector>
#include <iostream>

using namespace std;

class AudioMaster
{
public:
	AudioMaster();
	~AudioMaster();

	static void list_audio_devices(const ALCchar *devices);

	

private:
	ALCdevice* device;
	ALboolean enumeration;
	ALCcontext* context;
	ALuint source;
	ALuint buffer;


	void initSource();
	void LoadSources();
};


