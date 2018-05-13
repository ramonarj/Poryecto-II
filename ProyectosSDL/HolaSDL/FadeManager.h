#pragma once
#include "Component.h"
#include "MessageRenderer.h"
#include "MessageTimer.h"

const int MAX_FADE_ALPHA = 255;
const int NUM_FINALS_SENTENCES = 2;

class FadeManager :
	public Component
{
public:
	FadeManager();
	FadeManager(Texture* texture);
	virtual ~FadeManager();
	virtual void render(Entity* e, Uint32 time);
	virtual void handleInput(Entity* e, Uint32 time, const SDL_Event& event);

	void setDoFade(bool b, Uint8 dif);
	bool getDoFade() { return doFade_; };

	void setFinalFade(bool b, Uint8 dif, Uint8 difAlphaSentence);
	
	Uint8 getAlphaFade() { return alpha_; };
	bool getFinalFade() { return finalFade_; };

	void finalMessage(Entity* e, Uint32 time);

private:
	Texture* fade_ = nullptr;
	bool doFade_;
	Uint8 alpha_;
	Uint8 difAlpha_;

	//Variables para el fade del final
	bool finalFade_;
	Entity* messageRenderer_;
	vector<Entity*> finalSentences_;
	int numMessage_;
	Uint32 sentenceOn_;
	Uint32 sentenceTime_;
	Uint8 alphaSentence_;
	Uint8 difAlphaSentence_;
	bool sentenceFade_;
};

