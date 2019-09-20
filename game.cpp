
#include "game.h"
//  board square  100x100  coordinate in window 800x800
// pawn circle 50 diameter
//board and pawns coordinate in window 

const float G_xcord[8] = { 0.0f,100.0f,200.0f,300.0f,400.0f,500.0f,600.0f,700.0f };
const float G_ycord[8] = { 0.0f,100.0f,200.f,300.0f,400.0f,500.0f,600.0f,700.0f };


Game::Game():window(sf::VideoMode(800, 800), "Checkers", sf::Style::Close) {};

bool Game::textureinit()
{
	try {
		black_board_texture.init("black.png");    // load texture
		white_board_texture.init("white.png");
		border.init("frame.png");

		pawn_border.init("borderr.png");
		red_texture.init("fire.png");
		blue_texture.init("blue.png");
		red_king_texture.init("fire_king.png");
		blue_king_texture.init("blue_king.png");
	}
	catch (...)
	{

		return true;
	}
	return false;
}

void Game::boardinit()
{
	for (int i = 0; i < BLACK_BOARD_NUM; ++i) 
	{
		//initialise vector of BLACK_BOARD_NUM board black and white 

		boardwhite.push_back(board(1,i, &white_board_texture,nullptr));
	                                 //param 0 and  for positioning 
		boardblack.push_back(board(0,i, &black_board_texture, &border));
	}
}


void Game::playerinit()
{
	playertwo = player(PLAYER_TWO,&blue_texture,&blue_king_texture,&pawn_border);
	playerone = player(PLAYER_ONE,&red_texture, &red_king_texture,&pawn_border);
}
void Game::endblackrectangle() {
	finish = sf::RectangleShape(sf::Vector2f(800, 800));
	finish.setFillColor(sf::Color(0, 0, 0, 70));
}

bool Game::initfont() {
	if (!font.loadFromFile(FONTPATH))
	{

		//return true;  //font is not big deal its only appear in the end
	}

	txt.setFont(font);

	txt.setCharacterSize(40);
	txt.setFillColor(sf::Color::White);
	txt.setPosition(275.0, 375.0);
	return false;
}

bool Game::run() {
	bool stat= false;

	window.setFramerateLimit(40);

	initfont();
	if (textureinit())
		return true;

	boardinit();
	playerinit();
	endblackrectangle();
	
 stat=Game::events();
 return stat;

}
void Game::draw()
{

	window.clear();

	for (auto i = 0; i < BLACK_BOARD_NUM; ++i)
	{
		window.draw(boardwhite[i].display());   // draw board case

		window.draw(boardblack[i].display());
		if (turn->return_path(boardblack[i].cord()))
			window.draw(boardblack[i].display_path());   //draw pawn move possbilities
	}
	for (int i = 0; i < PAWN_NUMBER; ++i)
	{
		if (nturn->pawn(i).struct_id().id != PAWN_NUMBER)
			window.draw(nturn->pawn(i).display());
	}
	for (int i = 0; i < PAWN_NUMBER; ++i)
	{
		if (turn->pawn(i).struct_id().id != PAWN_NUMBER)
			window.draw(turn->pawn(i).display());   //draw pawn texture

		if (turn->legalmove_id(i))
			window.draw(turn->pawn(i).displayborder());   // draw texture of pawn that can be moved
	
		
		}
	if (turn->checkfinish()) {
		window.draw(finish);

		if (turn->player_id == PLAYER_TWO)
			txt.setString("Player_one Win");

		if (turn->player_id == PLAYER_ONE)
			txt.setString("Player_two Win");

		window.draw(txt);

	}


 window.display();
}

bool Game::events()
{
 bool clicked = false;  // for mouse move
 int indexx;
 sf::Event event;

 turn = &playerone;
 nturn = &playertwo;
 turn->status(nturn);  //check status of player pawn if can be moved or can eat

 while (window.isOpen())
 {

  Game::draw();

  while (window.pollEvent(event))
  {
   
   switch (event.type) 
   {
    ////////////////////////////////////
    case sf::Event::MouseButtonPressed:

	  if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && clicked == false)
		{
		  if (turn->checkfinish())
			  return false;
		
		    for (int i = 0; i < PAWN_NUMBER; ++i) 
			 {
			// define the pawn selected by mouse
				
					if (turn->legalmove_id(i) && turn->pawn(i).display().getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
					{
						clicked = true;
						indexx = i;
						turn->lightpath(i);//turn->pawn(i).get_id());  //reveal the possible move of the pawn selectd
						turn->pawn(i).select(event.mouseButton.x, event.mouseButton.y);  //store the mouse position when select pawn
						break;
					}
				
			}
		  
		}
	break;
	////////////////////////////

	///////////////////////////
	case sf::Event::MouseMoved:
		if (event.type == sf::Event::MouseMoved && clicked == true)
		{
			//move the pawn when mouse moved ( drop and down )
			turn->pawn(indexx).move(event.mouseMove.x, event.mouseMove.y);
		}
	break;
	///////////////////////////

	///////////////////////////
	case sf::Event::MouseButtonReleased:
		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && clicked == true )
	  {
	   for (int i = 0; i < BLACK_BOARD_NUM; ++i)
	    {
		//define the board case that pawn moved to  and check if possible to move  to it
		 if (boardblack[i].display().getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y) && turn->movelegal(indexx, boardblack[i].cord()))
		  {
		    turn->movepawn(indexx, boardblack[i].cord());
			//disable selected pawn possible move texture
			turn->lightpath(PAWN_NUMBER);
			if (turn->multieat<0)
			 swap();   //swap to oppoent player

			turn->status(nturn);
			clicked = false;
			break;
		  }
		}

	  if (clicked == true)    //confusing logic
	   {
		//reset move if move is not legal
		turn->pawn(indexx).resetmove();
		clicked = false;
	   }
	 }
	break;
	////////////////////////////////////

   }
  }
  if (event.type == sf::Event::Closed) {
  window.close();
   
	return true; 
  }

 }
}

void Game::swap() // swap  between playerone and playertwo
{
	player *t1;
	t1 = turn;
	turn = nturn;
	nturn = t1;
}