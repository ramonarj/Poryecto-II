#include "Credits.h"
#include "Game.h"
#include<iostream>
#include<fstream>

Credits::Credits(Game* game_, Texture* image, float velocity)  : renderer_(game_->getRenderer()), image_(image), velocity_(velocity)
	//,font_(game_->getResourceManager()->getFont("VCR_OSD_MONO")), color_{ 255, 255, 255, 255 }, spacing_(30)
	{
	//textLines.clear();
	//ifstream txtFile;
	//txtFile.open(txtFilePath);
	//string temp;
	//if (txtFile.is_open()) {
	//	while (!txtFile.eof()) {
	//		getline(txtFile, temp);
	//		textLines.push_back(temp);
	//	}
	//}
	//txtFile.close();
}

Credits::~Credits(){
}

void Credits::update(Entity * e, Uint32 time){
	e->setPosition(Vector2D(e->getPosition().getX(), e->getPosition().getY() + velocity_));
}

void Credits::render(Entity * e, Uint32 time){
	SDL_Rect rect RECT(
		e->getPosition().getX(),
		e->getPosition().getY(),
		e->getWidth(), 
		e->getHeight()
	);

	image_->render(renderer_, rect);

	//int yIncrement = 0;
	//cout << textLines.size() << endl;

	//for (string t : textLines) {
	//	if (t.size() > 0) {
	//		SDL_Surface* textSurface = font_->renderText(t, color_);
	//		SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer_, textSurface);
	//		SDL_SetTextureAlphaMod(textTexture, 255);
	//		int textW = textSurface->w;
	//		int textH = textSurface->h;
	//		SDL_FreeSurface(textSurface);
	//		SDL_Rect renderRect = { e->getPosition().getX(), e->getPosition().getY() + yIncrement, textW, textH };
	//		SDL_RenderCopy(renderer_, textTexture, nullptr, &renderRect);
	//		SDL_DestroyTexture(textTexture);
	//	}
	//	yIncrement += spacing_;
	//}
}