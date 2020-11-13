#pragma once

enum class pawn_type
{
	player_pawn,
	player_king,
	player_queen,
	player_knight,
	player_rook,
	player_bishop,
	bot_pawn,
	bot_king,
	bot_queen,
	bot_knight,
	bot_rook,
	bot_bishop,
	step
};

struct chess_set {
	pawn_type type;
	int x;
	int y;
	bool outline;
	bool knockout;
	bool passant;
};