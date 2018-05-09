#include "FadeManager.h"
#include "Game.h"


FadeManager::FadeManager() : Component(), fade_(nullptr), alpha_(0), difAlpha_(0), finalFade_(false), messageRenderer_(nullptr),
								sentenceOn_(0), sentenceTime_(0), numMessage_(0), alphaSentence_(0)
{
}

FadeManager::FadeManager(Texture * texture) : Component(), fade_(texture), alpha_(MAX_FADE_ALPHA), difAlpha_(10),
												finalFade_(false), messageRenderer_(nullptr), sentenceOn_(0),
	                                          sentenceTime_(5000), numMessage_(0), alphaSentence_(0)
{
	}


FadeManager::~FadeManager()
{
	delete fade_;
}

void FadeManager::render(Entity * e, Uint32 time) {

	SDL_Rect dest = RECT(0, 0, Game::Instance()->getWindowWidth(), Game::Instance()->getWindowHeight());

	if (!finalFade_)
	{
		if (doFade_)
		{
			if (alpha_ < MAX_FADE_ALPHA)
				alpha_ += difAlpha_;
			if (alpha_ > 255 - difAlpha_)
			{
				alpha_ = MAX_FADE_ALPHA;
				doFade_ = false;
			}
		}
		else
		{
			if (alpha_ > 0)
				alpha_ -= difAlpha_;
			if (alpha_ < difAlpha_)
				alpha_ = 0;
		}
	}
	else
	{
		if (alpha_ < MAX_FADE_ALPHA)
			alpha_ += difAlpha_;
		if (alpha_ > 255 - difAlpha_)
		{
			alpha_ = MAX_FADE_ALPHA;
		}
	}
	fade_->ChangeAlphaValue(alpha_);


	fade_->render(Game::Instance()->getRenderer(), dest);
	finalMessage(e, time);
}

void FadeManager::handleInput(Entity * e, Uint32 time, const SDL_Event & event) {

}

void FadeManager::setDoFade(bool b, Uint8 dif)
{
	doFade_ = b;
	difAlpha_ = dif;
}

void FadeManager::setFinalFade(bool b, Uint8 dif, Uint8 difAlphaSentence)
{
	finalFade_ = b;
	setDoFade(b, dif);
	sentenceFade_ = b;
	difAlphaSentence_ = difAlphaSentence;
	if (finalFade_) 
	{
		finalSentences_.clear();
		for (int i = 0; i < NUM_FINALS_SENTENCES; i++)
		{
			Entity* e = new Entity();
			ifstream archivo;
			stringstream ss, file;
			string line;

			file << "textNotes/FinalSentence" << i << ".txt";

			archivo.open(file.str());

			while (getline(archivo, line))
			{
				ss << line << "\n";
			}

			archivo.close();

			e->addComponent(new TextNote(Game::Instance(), ss.str(), 0, 0, nullptr));
			e->getComponent<TextNote>()->setFont(Game::Instance()->getResourceManager()->getFont("VCR_OSD_MONO"));
			e->getComponent<TextNote>()->setColor({ 255, 255, 255, 255 });
			e->getComponent<TextNote>()->setEnabled(false);
			e->getComponent<TextNote>()->setAlpha(alphaSentence_);
			finalSentences_.push_back(e);
			Game::Instance()->getStateMachine()->currentState()->getStage()->push_back(e);
		}
	}
}

void FadeManager::finalMessage(Entity* e, Uint32 time)
{
	if (finalFade_ && alpha_ == MAX_FADE_ALPHA)
	{
		finalSentences_[numMessage_]->getComponent<TextNote>()->setAlpha(alphaSentence_);
		finalSentences_[numMessage_]->getComponent<TextNote>()->setEnabled(true);

		if (sentenceFade_)
		{
			if (alphaSentence_ < MAX_FADE_ALPHA)
				alphaSentence_ += difAlphaSentence_;
			if (alphaSentence_ > 255 - difAlphaSentence_ && alphaSentence_ != MAX_FADE_ALPHA)
			{
				alphaSentence_ = MAX_FADE_ALPHA;
				sentenceOn_ = SDL_GetTicks();
				sentenceFade_ = false;
			}
		}
		else {
			if (sentenceOn_ + sentenceTime_ < time)
			{
				if (alphaSentence_ > 0)
					alphaSentence_ -= difAlphaSentence_;
				if (alphaSentence_ < difAlphaSentence_ && alphaSentence_ != 0)
				{
					sentenceFade_ = true;
					alphaSentence_ = 0;
					finalSentences_[numMessage_]->getComponent<TextNote>()->setEnabled(false);
					numMessage_++;
					alphaSentence_ = 0;
					if (numMessage_ == finalSentences_.size())
						e->getComponent<FadeManager>()->setFinalFade(false, 5, 10);
				}
			}
		}

	}
}
