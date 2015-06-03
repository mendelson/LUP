#include "Text.h"
#include "Resources.h"
#include "Camera.h"
#include "Game.h"

Text::Text(std::string fontFile, int fontSize, TextStyle style,
		std::string text, SDL_Color color, int x, int y) :
		box(x, y, 0, 0) {
	font = Resources::GetFont(fontFile, fontSize);
	texture = NULL;
	this->text = text;
	this->style = style;
	this->color = color;
	this->fontSize = fontSize;
	RemakeTexture();
}

Text::~Text() {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
	}
}

void Text::Render(int cameraX, int cameraY) {
	if (texture == NULL) {
		cout << "ERRO ao renderizar o texto!" << endl;
		exit(1);
	}
	SDL_Rect cliprect;
	cliprect.x = 0;
	cliprect.y = 0;
	cliprect.w = box.w;
	cliprect.h = box.h;
	SDL_Rect auxrect;
	auxrect.x = box.x + cameraX;
	auxrect.y = box.y + cameraY;
	auxrect.w = box.w;
	auxrect.h = box.h;
	if (SDL_RenderCopy((Game::GetInstance().GetRenderer()), texture, &cliprect,
			&auxrect) != 0) {
		std::cout << "Erro ao renderizar texto!!" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		exit(1);
	}
}

void Text::SetPos(int x, int y, bool centerX, bool centerY) {
	if (centerX) {
		box.setX(x - (int) box.getW() / 2);
	} else {
		box.setX(x);
	}
	if (centerY) {
		box.setY(y - (int) box.getH() / 2);
	} else {
		box.setY(y);
	}
}

void Text::SetText(string text) {
	this->text = text;
	RemakeTexture();
}

void Text::SetColor(SDL_Color color) {
	this->color = color;
	RemakeTexture();
}

void Text::SetStyle(TextStyle style) {
	this->style = style;
	RemakeTexture();
}

void Text::SetFontSize(int fontSize) {
	this->fontSize = fontSize;
	RemakeTexture();
}

void Text::RemakeTexture() {
	if (texture != NULL) {
		SDL_DestroyTexture(texture);
	}
	SDL_Surface* surface;
	if (style == SOLID) {
		surface = TTF_RenderText_Solid(font, text.c_str(), color);
	}
	if (style == SHADED) {
		surface = TTF_RenderText_Shaded(font, text.c_str(), color, { 0, 0, 0 });
	}
	if (style == BLENDED) {
		surface = TTF_RenderText_Blended(font, text.c_str(), color);
	}

	texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(),
			surface);
	SDL_FreeSurface(surface);
	int w;
	int h;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	box.setW(w);
	box.setH(h);
}
