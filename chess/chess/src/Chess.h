#pragma once
#include <GLFW/glfw3.h>
#include <vector>
#include "Player.h"
#include "Bot.h"
#include "chess_set.h"

class Chess {
public:
	Chess(GLFWwindow*& window)
		:end(false), window(window)
	{
		chess_set tmp;
		tmp.knockout = false;
		tmp.type = pawn_type::player_pawn;
		tmp.y = 1;
		tmp.outline = false;
		for (unsigned int i = 0; i < 8; i++) {
			tmp.x = i;
			chess_sets.push_back(tmp);
		}

		tmp.type = pawn_type::bot_pawn;
		tmp.y = 6;
		for (unsigned int i = 0; i < 8; i++) {
			tmp.x = i;
			chess_sets.push_back(tmp);
		}

		tmp.type = pawn_type::player_bishop;
		tmp.x = 2;
		tmp.y = 0;
		chess_sets.push_back(tmp);

		tmp.x = 5;
		chess_sets.push_back(tmp);

		tmp.type = pawn_type::bot_bishop;
		tmp.x = 2;
		tmp.y = 7;
		chess_sets.push_back(tmp);

		tmp.x = 5;
		chess_sets.push_back(tmp);

		tmp.type = pawn_type::player_king;
		tmp.x = 4;
		tmp.y = 0;
		chess_sets.push_back(tmp);

		tmp.type = pawn_type::bot_king;
		tmp.x = 4;
		tmp.y = 7;
		chess_sets.push_back(tmp);

		tmp.type = pawn_type::player_queen;
		tmp.x = 3;
		tmp.y = 0;
		chess_sets.push_back(tmp);

		tmp.type = pawn_type::bot_queen;
		tmp.x = 3;
		tmp.y = 7;
		chess_sets.push_back(tmp);

		tmp.type = pawn_type::player_knight;
		tmp.x = 1;
		tmp.y = 0;
		chess_sets.push_back(tmp);

		tmp.x = 6;
		chess_sets.push_back(tmp);

		tmp.type = pawn_type::bot_knight;
		tmp.x = 1;
		tmp.y = 7;
		chess_sets.push_back(tmp);

		tmp.x = 6;
		chess_sets.push_back(tmp);

		tmp.type = pawn_type::player_rook;
		tmp.x = 0;
		tmp.y = 0;
		chess_sets.push_back(tmp);

		tmp.x = 7;
		chess_sets.push_back(tmp);

		tmp.type = pawn_type::bot_rook;
		tmp.x = 0;
		tmp.y = 7;
		chess_sets.push_back(tmp);

		tmp.x = 7;
		chess_sets.push_back(tmp);
	}

	std::vector<chess_set> chess_sets;
	void play();
	void ends();
	bool end;
private:
	Player player;
	Bot bot;
	GLFWwindow*& window;
};