#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "sdl_includes.h"
#include "Font.h"
#include <map>

using namespace std;

class Texture {
public:

	static Texture* Instance()
	{
		if (s_pInstance == 0)
		{
			s_pInstance = new Texture();
			return s_pInstance;
		}
		return s_pInstance;
	}

	//Texture();
	Texture(SDL_Renderer* renderer, string fileName);
	Texture(SDL_Renderer* renderer, string text, const Font& font,
			const SDL_Color color);
	virtual ~Texture();

	int getWidth();
	int getHeight();
	bool loadFromImg(SDL_Renderer* renderer, string fileName);
	bool loadFromText(SDL_Renderer * pRender, string texto,
			Font const& font, SDL_Color color = { 0, 0, 0, 255 });
	void render(SDL_Renderer* renderer, int x, int y) const;
	void render(SDL_Renderer* renderer, SDL_Rect const& dest, SDL_Rect* clip =
			nullptr) const;
	void render(SDL_Renderer* renderer, SDL_Rect const& dest, double angle,
			SDL_Rect* clip = nullptr) const;

	//Para el mapa
	bool load(string fileName, std::string
		id, SDL_Renderer* pRenderer);
	void drawTile(string id, int margin, int
		spacing, int x, int y, int width, int height, int currentRow,
		int currentFrame, SDL_Renderer *pRenderer);

	void close();

private:

	SDL_Texture *texture_;
	int width_;
	int height_;

	map<string, SDL_Texture*> m_textureMap;


	Texture();
	static Texture* s_pInstance;
};


typedef Texture Texture;

#endif /* TEXTURE_H_ */
