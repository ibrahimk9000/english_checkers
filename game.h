#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <SFML/Window.hpp>
#include <iostream>
#include "texture.h"

#include "board.h"
#include "players.h"
#include "stdint.h"

#define BLACK_BOARD_NUM 32
#ifdef _WIN32
#define FONTPATH "C:/Windows/Fonts/arial.ttf"

#elif __linux__

#define FONTPATH "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"
#endif


class Game
{

private:
	sf::Event event;
	sf::RectangleShape finish;
	sf::RenderWindow window;
	player playerone;
	player playertwo;
	player *turn;
	player *nturn;
	std::vector<board> boardblack;
	std::vector<board> boardwhite;
	sf::Text txt;
	sf::Font font;
	
	texture black_board_texture;    
	texture white_board_texture;
	texture border;

	texture pawn_border;
	texture red_texture;
	texture blue_texture;
	texture red_king_texture;
	texture blue_king_texture;

	void draw();
	bool events();

	void boardinit();
	void playerinit();
	void endblackrectangle();
	bool initfont();
	bool textureinit();
	void swap();
public:
	Game();
	
	bool run();
	
};