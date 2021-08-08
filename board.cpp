#include "board.h"

//texture black_board_texture("black.png");    // load texture
//texture white_board_texture("white.png");
//texture border("frame.png");

board::board(int clr, int id_loop, texture *tboard, texture *tborder) : color(clr)
{

	square = sf::RectangleShape(sf::Vector2f(100, 100)); //inisitalise rectangle 100x100 for barod case
	id = id_loop;										 // id of board
	square.setTexture(tboard->map());

	if (color == 0) // if 1 the board is black
	{
		square_path = sf::RectangleShape(sf::Vector2f(100, 100)); //create texture that surround board case when pawn selected
		square_path.setTexture(tborder->map());
		//square_path.setFillColor(sf::Color())
	}
	position();
}

sf::RectangleShape &board::display()
{
	return square;
}
sf::RectangleShape &board::display_path()
{
	return square_path;
}
void board::position()
{

	//make position of black and white board case

	if ((id / 4) % 2 == 0)
	{
		x_cord = id % 4 * 2 + !color; //white offset coordinate
		y_cord = id / 4;
		square.setPosition(G_xcord[x_cord], G_ycord[y_cord]);
	}
	else
	{
		x_cord = id % 4 * 2 + color;
		y_cord = id / 4;
		square.setPosition(G_xcord[x_cord], G_ycord[y_cord]);
	}
	if (color == 0)
		square_path.setPosition(G_xcord[x_cord], G_ycord[y_cord]);
}

sf::Vector2i board::cord()
{
	return sf::Vector2i(x_cord, y_cord);
}
