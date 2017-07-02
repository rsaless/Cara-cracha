#ifndef TEXTO
#define TEXTO

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <string>

class Texto {

	std::string ttf_path;
	TTF_Font* t_font;
	SDL_Texture* t_texture;
	SDL_Renderer* t_renderer;
	int t_size;
	SDL_Rect rec_format;
	SDL_Rect rec_srcrect;
	SDL_Color t_color;
	
	SDL_Texture* loadFont();

	public:
		std::string t_text;

		Texto();
		Texto(std::string, SDL_Renderer*, int, SDL_Rect, SDL_Color, std::string, SDL_Rect = {0, 0, 0, 0});
	
		Texto* setPath(std::string);
		//SDL_Renderer* getRenderer() const;
		Texto* setRenderer(SDL_Renderer*);
		//SDL_Texture* getTexture() const;
		//SDL_Point getSize() const;
		Texto* setSize(SDL_Point);
		//SDL_Point getPosition() const;
		Texto* setPosition(SDL_Point);
		Texto* setFormat(SDL_Rect);
		Texto* setSrcrect(SDL_Rect);
		Texto* setColor(SDL_Color);
		Texto* setText(std::string);
		bool render();
};

inline SDL_Texture* Texto::loadFont() {
	// Textura final
	SDL_Texture* newTexture = NULL;

	// Carrega fonte a partir do caminho e tamanho
	this->t_font = TTF_OpenFont(this->ttf_path.c_str(), this->t_size);
	if (this->t_font == NULL) {
		SDL_Log("Unable to load font %s. TTF_OpenFont Error: %s", this->ttf_path.c_str(), TTF_GetError());
	} else {
		// Obtém a largura e altura ocupada pelo texto
		if (TTF_SizeUTF8(this->t_font, this->t_text.c_str(), &this->rec_format.w, &this->rec_format.h))
			SDL_Log("Unable to load get size of %s. TTF_SizeUTF8 Error: %s", this->ttf_path.c_str(), TTF_GetError());

		// Carrega fonte a partir do texto
		SDL_Surface* loadedSurface = TTF_RenderUTF8_Solid(this->t_font, this->t_text.c_str(), this->t_color);
		if (loadedSurface == NULL) {
			SDL_Log("Unable to load surface from %s. TTF_RenderUTF8_Solid Error: %s", this->ttf_path.c_str(), TTF_GetError());
		} else {
			// Cria textura dos pixels da superficie
			newTexture = SDL_CreateTextureFromSurface(this->t_renderer, loadedSurface);
			if ( newTexture == NULL) {
				SDL_Log("Unable to create texture from %s. SDL Error: %s", this->ttf_path.c_str(), SDL_GetError());
			}

			// Deleta a superficie
			SDL_FreeSurface(loadedSurface);
		}
	}

	return newTexture;
}

inline Texto::Texto():
	ttf_path(""),
	t_font(nullptr),
	t_texture(nullptr),
	t_renderer(nullptr),
	t_size(0),
	rec_format({0, 0, 0, 0}),
	rec_srcrect({0, 0, 0, 0}),
	t_color({0, 0, 0}),
	t_text("") {
}
inline Texto::Texto(std::string pp, SDL_Renderer* pr, int ps, SDL_Rect pf, SDL_Color pc, std::string pt, SDL_Rect psr):
	ttf_path(pp),
	t_font(nullptr),
	t_texture(nullptr),
	t_renderer(pr),
	t_size(ps),
	rec_format(pf),
	rec_srcrect(psr),
	t_color(pc),
	t_text(pt) {
	this->t_texture = loadFont();
}

inline Texto* Texto::setPath(std::string pp) {
	this->ttf_path = pp;
	this->t_texture = loadFont();
	return this;
}

inline Texto* Texto::setRenderer(SDL_Renderer* pr) {
	this->t_renderer = pr;
	return this;
}
inline Texto* Texto::setSize(SDL_Point s) {
	this->rec_format.w = s.x;
	this->rec_format.h = s.y;
	this->t_texture = loadFont();
	return this;
}
inline Texto* Texto::setPosition(SDL_Point p) {
	this->rec_format.x = p.x;
	this->rec_format.y = p.y;
	this->t_texture = loadFont();
	return this;
}
inline Texto* Texto::setFormat(SDL_Rect pf) {
	this->rec_format = pf;
	this->t_texture = loadFont();
	return this;
}
inline Texto* Texto::setSrcrect(SDL_Rect psr) {
	this->rec_srcrect = psr;
	this->t_texture = loadFont();
	return this;
}
inline Texto* Texto::setColor(SDL_Color pc) {
	this->t_color = pc;
	this->t_texture = loadFont();
	return this;
}
inline Texto* Texto::setText(std::string pt) {
	this->t_text = pt;
	this->t_texture = loadFont();
	return this;
}
inline bool Texto::render() {
	return SDL_RenderCopy(this->t_renderer, this->t_texture, NULL, &this->rec_format) == 0;
}

#endif