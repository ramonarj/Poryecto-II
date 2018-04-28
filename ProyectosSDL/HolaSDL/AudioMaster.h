#pragma once

#define AL_ALUT_H

#include <al.h>
#include <alc.h>
#include <vector>
#include <iostream>
#include <efx.h>
#include <cstdlib>
#include <efx-creative.h>
#include <EFX-Util.h>

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


