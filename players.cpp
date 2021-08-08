#include "players.h"

player::player(int plyr, texture *tpawn, texture *tkpawn, texture *tborder) : player_id(plyr)
{
	//initialise vector of pawns

	if (player_id == PLAYER_TWO)
	{
		for (int i = PAWN_NUMBER - 1; i >= 0; --i)
			player_pawn.push_back(pawns(player_id, i, tpawn, tkpawn, tborder));

		base = 7; //board limit
	}
	if (player_id == PLAYER_ONE)
	{
		for (int i = 0; i < PAWN_NUMBER; ++i)
			player_pawn.push_back(pawns(player_id, i, tpawn, tkpawn, tborder));

		base = 0; //board limit
	}
}

player::player(){};

void player::status(player *opp)
{

	player2 = opp; //pointer to opponent player

	eatormove = false;

	erazemove(11); //clear past move

	if (player_id == PLAYER_TWO) //player two start from position 7 and player one stat form position 0
		magic = -1;

	if (player_id == PLAYER_ONE)
		magic = 1;

	for (int i = 0; i < PAWN_NUMBER; ++i)
	{
		if (multieat > 0 && multieat != i)
			continue;

		if (player_pawn[i].struct_id().id < PAWN_NUMBER)
		{
			indexxx = i;

			pawn_rightright(player_pawn[i].struct_id(), true);
			pawn_leftleft(player_pawn[i].struct_id(), true);
			if (player_pawn[i].king == true)
			{
				magic = magic * (-1);

				pawn_rightright(player_pawn[i].struct_id(), true);
				pawn_leftleft(player_pawn[i].struct_id(), true);
				magic = magic * (-1);
			}
		}
	}
}

int player::emptyright(pawnmove right, int eatflag) //eatflag can be 0 or 1 to add offset to eat
{
	for (int i = 0; i < PAWN_NUMBER; ++i)
	{

		if (right.x - magic - eatflag == player2->player_pawn[i].struct_id().x && right.y + magic + eatflag == player2->player_pawn[i].struct_id().y)
			return i;

		if (right.x - magic - eatflag == player_pawn[i].struct_id().x && right.y + magic + eatflag == player_pawn[i].struct_id().y)
			return -1;
	}
	return -2;
}
int player::emptyleft(pawnmove right, int eatflag)
{
	for (int i = 0; i < PAWN_NUMBER; ++i)
	{

		if (right.x + magic + eatflag == player2->player_pawn[i].struct_id().x && right.y + magic + eatflag == player2->player_pawn[i].struct_id().y)
			return i;

		if (right.x + magic + eatflag == player_pawn[i].struct_id().x && right.y + magic + eatflag == player_pawn[i].struct_id().y)
			return -1;
	}
	return -2;
}

bool player::borderleft(pawnmove left, int eatflag)
{
	if (left.x + magic + eatflag > 7 || left.x + magic + eatflag < 0 || left.y + magic + eatflag > 7 || left.y + magic + eatflag < 0)
		return false;

	return true;
}
bool player::borderright(pawnmove right, int eatflag)
{
	if (right.x - magic - eatflag < 0 || right.x - magic - eatflag > 7 || right.y + magic + eatflag > 7 || right.y + magic + eatflag < 0)
		return false;

	return true;
}

bool player::movelegal(int idd, sf::Vector2i coor)
{

	multieat = -1;

	if (legalmove_id(idd) == true)
		return mv(idd, coor);

	return false;
}
void player::olm(std::vector<path> &v, int idd)
{
	for (auto &elem : player_pawn[idd].path_pawn)
	{

		if (elem.first == true)
			v.push_back(elem);
	}
}

bool player::mv(int idd, sf::Vector2i coor)
{

	std::vector<path> moveonlythis;
	olm(moveonlythis, idd);

	for (auto &elem : moveonlythis)
	{

		if (coor.x == elem.end.x && coor.y == elem.end.y)
		{
			if (elem.multi)
				multieat = idd;

			pathmove = elem;
			return true;
		}
	}
	return false;
}

////////////
void player::movepawn(int idd, sf::Vector2i cord)
{

	if (pathmove.opponentid >= 0)
		player2->deletepawn(pathmove.opponentid);

	player_pawn[idd].moveforward(cord);

	if (std::abs(player_pawn[idd].struct_id().y - base) == 7)
		transform(idd);
}
////////////////
void player::deletepawn(int x)
{
	int i;
	for (int f = 0; f < PAWN_NUMBER; ++f)
	{

		if (player_pawn[f].struct_id().id == x)
			i = f;
	}
	player_pawn[i].dell();
}

pawns &player::pawn(int index)
{
	return player_pawn[index];
}

bool player::legalmove_id(int idd)
{
	if (!player_pawn[idd].path_pawn.empty())
		return true;

	return false;
}

bool player::checkfinish()
{
	for (int i = 0; i < PAWN_NUMBER; ++i)
	{
		if (legalmove_id(i))
			return false;
	}
	return true;
}
void player::lightpath(int idd)
{
	possible_move = idd;
}

bool player::return_path(sf::Vector2i cord) //  mess
{

	if (possible_move < 0 || possible_move > 11)
		return false;

	for (auto &elem : player_pawn[possible_move].path_pawn)
	{

		if (cord.x == elem.end.x && cord.y == elem.end.y)
			return true;
	}

	return false;
}

void player::transform(int index)
{
	player_pawn[index].king = true;
	player_pawn[index].transform();
}

void player::erazemove(int index)
{

	for (int i = 0; i < index + 1; ++i)
		player_pawn[i].path_pawn.clear();
}

void player::increright(pawnmove &r)
{
	r.x = r.x - magic;
	r.y = r.y + magic;
}

void player::increleft(pawnmove &r)
{
	r.x = r.x + magic;
	r.y = r.y + magic;
}

void player::eatright(pawnmove &r)
{
	increright(r);
	increright(r);
}

void player::eatleft(pawnmove &r)
{
	increleft(r);
	increleft(r);
}

int player::auraright(pawnmove array_pawnn)
{
	if (!borderright(array_pawnn))
		return -1;

	int i = emptyright(array_pawnn);

	if (i == -2)
		return -2;

	if (i == -1)
		return -1;

	if (i >= 0)
	{

		if (emptyright(array_pawnn, magic) == -2 && borderright(array_pawnn, magic))
			return player2->player_pawn[i].struct_id().id;

		return -1;
	}
	return -1;
}

int player::auraleft(pawnmove array_pawnn)
{

	if (!borderleft(array_pawnn))
		return -1;

	int i = emptyleft(array_pawnn);

	if (i == -2)
		return -2;

	if (i == -1)
		return -1;

	if (i >= 0)
	{

		if (emptyleft(array_pawnn, magic) == -2 && borderleft(array_pawnn, magic))
			return player2->player_pawn[i].struct_id().id;

		return -1;
	}
	return -1;
}

bool player::pawn_rightright(pawnmove array_pawnn, bool first)
{
	bool multi = false;

	pawnmove beginpath = array_pawnn;

	int i;
	bool b1, b2;
	bool eat = false;
	int holdid = -2;

	i = auraright(array_pawnn);

	if (i == -2)
	{
		if (!eatormove)
		{
			increright(array_pawnn);
			player_pawn[indexxx].path_pawn.push_back(path{beginpath, array_pawnn, holdid, first, multi});
		}
	}

	if (i >= 0)
	{
		if (!eatormove)

		{
			eatormove = true;
			erazemove(indexxx);
		}
		holdid = i;
		eat = true;

		eatright(array_pawnn);

		b1 = pawn_leftleft(array_pawnn, false);
		b2 = pawn_rightright(array_pawnn, false);

		if (player_pawn[indexxx].king == true)
		{
			magic = magic * (-1);

			multi = pawn_leftleft(array_pawnn, false);

			magic = magic * (-1);
		}

		multi = multi || b1 || b2;

		player_pawn[indexxx].path_pawn.push_back(path{beginpath, array_pawnn, holdid, first, multi});
	}

	return eat;
}

bool player::pawn_leftleft(pawnmove array_pawnn, bool first)
{
	bool multi = false;

	pawnmove beginpath = array_pawnn;

	int i;
	bool b1, b2;
	bool eat = false;
	int holdid = -2;

	i = auraleft(array_pawnn);

	if (i == -2)
	{

		if (!eatormove)
		{
			increleft(array_pawnn);
			player_pawn[indexxx].path_pawn.push_back(path{beginpath, array_pawnn, holdid, first, multi});
		}
	}

	if (i >= 0)
	{
		if (!eatormove)
		{
			eatormove = true;
			erazemove(indexxx);
		}
		holdid = i;
		eat = true;
		eatleft(array_pawnn);

		b1 = pawn_rightright(array_pawnn, false);
		b2 = pawn_leftleft(array_pawnn, false);

		if (player_pawn[indexxx].king == true)
		{
			magic = magic * (-1);

			multi = pawn_rightright(array_pawnn, false);

			magic = magic * (-1);
		}

		multi = multi || b1 || b2;
		player_pawn[indexxx].path_pawn.push_back(path{beginpath, array_pawnn, holdid, first, multi});
	}

	return eat;
}
