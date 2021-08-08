
#include "pawns.h"

#include <cstdlib>

//texture pawn_border("borderr.png");
//texture red_texture("fire.png");
//texture blue_texture("blue.png");
//texture red_king_texture("fire_king.png");
//texture blue_king_texture("blue_king.png");

pawns::pawns(int redorblue, int loop_id, texture *gtpawn, texture *gtkpawn, texture *gtborder)
{

	player_id = redorblue;
	tpawn = gtpawn;
	tkpawn = gtkpawn;
	tborder = gtborder;
	circle = (sf::CircleShape(50));

	squareborder = sf::RectangleShape(sf::Vector2f(100, 100));
	squareborder.setTexture(tborder->map());

	circle.setTexture(tpawn->map());
	position(loop_id);
}

pawnmove &pawns::struct_id()
{
	return id_cord;
}
void pawns::position(int id)
{
	int x_cord, y_cord;
	if ((id / 4) % 2 == 0)
	{
		x_cord = id % 4 * 2 + !player_id;
		y_cord = id / 4 + player_id;
		circle.setPosition(G_xcord[x_cord], G_ycord[y_cord]);
		squareborder.setPosition(G_xcord[x_cord], G_ycord[y_cord]);
	}
	else
	{
		x_cord = id % 4 * 2 + !!player_id;
		y_cord = id / 4 + player_id;
		circle.setPosition(G_xcord[x_cord], G_ycord[y_cord]);

		squareborder.setPosition(G_xcord[x_cord], G_ycord[y_cord]);
	}
	id_cord = pawnmove{id, x_cord, y_cord};
}

sf::CircleShape &pawns::display()
{
	return circle;
}
sf::RectangleShape &pawns::displayborder()
{
	return squareborder;
}

void pawns::select(int x, int y)
{
	lastpos = circle.getPosition();
	mouseRectOffset.x = x - circle.getGlobalBounds().left - circle.getOrigin().x;
	mouseRectOffset.y = y - circle.getGlobalBounds().top - circle.getOrigin().y;
}
void pawns::move(int movex, int movey)
{
	circle.setPosition(movex - mouseRectOffset.x, movey - mouseRectOffset.x);
	squareborder.setPosition(movex - mouseRectOffset.x, movey - mouseRectOffset.x);
}

void pawns::resetmove()
{
	circle.setPosition(lastpos);
	squareborder.setPosition(lastpos);
}
void pawns::moveforward(sf::Vector2i coor)
{

	id_cord.x = coor.x;
	id_cord.y = coor.y;
	circle.setPosition(G_xcord[coor.x], G_ycord[coor.y]);
	squareborder.setPosition(G_xcord[coor.x], G_ycord[coor.y]);
}
void pawns::transform()
{

	circle.setTexture(tkpawn->map());
}
void pawns::dell()
{

	id_cord = pawnmove{12, -1, -1};
	circle.setRadius(0);
	squareborder.setSize(sf::Vector2f(0, 0));
}
sf::Vector2i pawns::cord()
{
	return sf::Vector2i(id_cord.x, id_cord.y);
}

/*
void pawns::symmetry()
{
	x_cord = std::abs(x_cord - 7);
	y_cord = std::abs(y_cord - 7);
	id_cord = pawnmove{ id, x_cord, y_cord };
	circle.setPosition(x[x_cord], y[y_cord]);
}
*/
