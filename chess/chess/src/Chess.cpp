#include "Chess.h"
#include <iostream>

void Chess::play() {
	while (end != true){
		player.play(chess_sets, window);
		if (end == true)
			break;
		bot.play(chess_sets);
		ends();
	}
}

void Chess::ends() {
	auto it = std::find_if(chess_sets.begin(), chess_sets.end(), [bk = pawn_type::bot_king](const chess_set& cs) -> bool {return cs.type == bk; });
	if (it == chess_sets.end()) {
		std::cout << "You win!" << std::endl;
		end = true;
		std::cin.get();
	}
	else {
		it = std::find_if(chess_sets.begin(), chess_sets.end(), [pk = pawn_type::player_king](const chess_set& cs) -> bool {return cs.type == pk; });
		if (it == chess_sets.end()) {
			std::cout << "You lose!" << std::endl;
			end = true;
			std::cin.get();
		}
	}
}
