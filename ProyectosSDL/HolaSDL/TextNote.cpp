#include "TextNote.h"
#include<iostream>
#include<fstream>

TextNote::TextNote(Game* game_, string txtFilePath, int x, int y, Texture* backgroundTexture) : renderer_(game_->getRenderer()),
font_(game_->getResourceManager()->getFont("VCR_OSD_MONO")), pos_(Vector2D(x, y)),
color_{ 0, 0, 0, 255 }, spacing_(30),
background_(backgroundTexture), alpha_(255) /*,txtFilePath_(txtFilePath)*/
{
	string aux = "";
	textLines.clear();
	for (char c : txtFilePath) {
		if (c == '\n') {
			textLines.push_back(aux);
			aux.clear();
		}
		else {
			aux = aux + c;
		}
	}
}

TextNote::~TextNote() {
}

void TextNote::render(Entity * e, Uint32 time) {

	SDL_Rect rect RECT(0, 0, Game::Instance()->getWindowWidth(), Game::Instance()->getWindowHeight());

	if (background_ != nullptr)
		background_->render(Game::Instance()->getRenderer(), rect);

	int yIncrement = 0;

	for (string t : textLines) {
		if (t.size() > 0) {
			SDL_Surface* textSurface = font_->renderText(t, color_);
			SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer_, textSurface);
			SDL_SetTextureAlphaMod(textTexture, alpha_);
			int textW = textSurface->w;
			int textH = textSurface->h;
			SDL_FreeSurface(textSurface);
			SDL_Rect renderRect = { pos_.getX(), pos_.getY() + yIncrement, textW, textH };
			SDL_RenderCopy(renderer_, textTexture, nullptr, &renderRect);
			SDL_DestroyTexture(textTexture);
		}
		yIncrement += spacing_;
	}
}

void TextNote::changeString(string txtFilePath)
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
	string aux = "";
	textLines.clear();
	for (char c : txtFilePath) {
		if (c == '\n') {
			textLines.push_back(aux);
			aux.clear();
		}
		else {
			aux = aux + c;
		}
	}

}
