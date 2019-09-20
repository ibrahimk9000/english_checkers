#pragma once
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "texture.h"
extern const float G_xcord[8];
extern const float G_ycord[8];
class board
{
private:
	sf::RectangleShape square;
	sf::RectangleShape square_path;
	int color;
	int id;
	int x_cord;
	int y_cord;
	void position();

public:
	
	board(int clr, int id_loop, texture * tboard, texture * tborder);
	sf::RectangleShape &display();
	sf::RectangleShape & display_path();
	sf::Vector2i cord();
};
