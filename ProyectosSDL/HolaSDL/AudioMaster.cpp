#include "AudioMaster.h"



AudioMaster::AudioMaster()
{

	device = alcOpenDevice(NULL);
	if (!device){
		cout << "device no inicializado";
	}

	enumeration = alcIsExtensionPresent(NULL, "ALC_ENUMERATION_EXT");
	if (enumeration == AL_FALSE)
		cout << "enumeración off";
	else
		cout << "enumeración on";

	context = alcCreateContext(device, NULL);
	if (!alcMakeContextCurrent(context)) {
		ALCenum error;
		error = alGetError();
		if (error != AL_NO_ERROR)
			cout << "error creating context";
	}

	list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));

	initSource();
}


AudioMaster::~AudioMaster()
{
}


void AudioMaster::list_audio_devices(const ALCchar * devices)
{
	const ALCchar *device = devices, *next = devices + 1;
	size_t len = 0;

	cout << "Devices list:\n";
	cout << "----------\n";
	while (device && *device != '\0' && next && *next != '\0') {
		cout << "%s\n" << device;
		len = strlen(device);
		device += (len + 1);
		next += (len + 2);
	}
	cout << "----------\n";
}



void AudioMaster::initSource()
{
	alGenSources((ALuint)1, &source);
	alSourcef(source, AL_PITCH, 1);
	alSourcef(source, AL_GAIN, 1);
	alSource3f(source, AL_POSITION, 0, 0, 0);
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	alSourcei(source, AL_LOOPING, AL_FALSE);

	//Inicializo el buffer
	alGenBuffers((ALuint)1, &buffer);
}

void AudioMaster::LoadSources()
{
	
}





