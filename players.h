#pragma once
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <cstdlib>
#include <iostream>
#include "pawns.h"
#define PAWN_NUMBER 12
#define PLAYER_ONE 0
#define PLAYER_TWO 5

class player
{

private:
	int indexxx;
	bool eatormove = false;
	path pathmove;

	pawnmove endpath;
	int base;

	int magic;
	player *player2;

	int possible_move = PAWN_NUMBER;
	std::vector<int> banned;
	std::vector<pawns> player_pawn;

	int emptyright(pawnmove right, int eatflag = 0);
	int emptyleft(pawnmove right, int eatflag = 0);
	bool borderleft(pawnmove left, int eatflag = 0);
	bool borderright(pawnmove right, int eatflag = 0);
	void olm(std::vector<path> &v, int idd);
	bool mv(int idd, sf::Vector2i coor);
	void deletepawn(int x);
	void erazemove(int i);

	bool pawn_rightright(pawnmove array_pawnn, bool first);
	bool pawn_leftleft(pawnmove array_pawnn, bool first);

	void increright(pawnmove &r);
	void increleft(pawnmove &r);
	void eatright(pawnmove &r);
	void eatleft(pawnmove &r);
	int auraright(pawnmove array_pawnn);
	int auraleft(pawnmove array_pawnn);

public:
	int player_id;
	int multieat = -1;

	bool movelegal(int indexx, sf::Vector2i coor);
	void status(player *opp);

	player(int plyr, texture *tpawn, texture *tkpawn, texture *tborder);
	player();

	void movepawn(int i, sf::Vector2i cord);

	pawns &pawn(int index);

	bool legalmove_id(int idd);
	bool checkfinish();
	void lightpath(int idd);
	bool return_path(sf::Vector2i cord);
	void transform(int index);
};
