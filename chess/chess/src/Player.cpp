#include "Player.h"
#include <iostream>
#include <string>

void Player::play(std::vector<chess_set>& cs, GLFWwindow*& window) {
    moved = false;
	chess_sets = &cs;
	while (moved != true)
        glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetMouseButtonCallback(window, 0);
}

void Player::mouse_button_callback(GLFWwindow* window, int button, int action, int mods){
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		glfwGetCursorPos(window, &xpos, &ypos);
		for (auto& i : *chess_sets)
			if (xpos > i.x * 100.0 && xpos < (i.x + 1.0) * 100.0 && 800 - ypos > i.y * 100.0 && 800 - ypos < (i.y + 1.0) * 100.0){
                if (i.knockout == true) {
                    
                    if (selected->type == pawn_type::player_pawn) {
                        if (i.y == 7) {
                            std::cout << "Please type in the Promotion (r for rook, q for queen, k for knight, b for bishop): " << std::endl;
                            char str;
                            std::cin >> str;
                            if (str == 'q') {
                                selected->type = pawn_type::player_queen;
                                if (selected->type == pawn_type::player_queen) {
                                    for (auto& y : *chess_sets) {
                                        if (y.type == pawn_type::player_queen) {
                                            y.x = i.x;
                                            y.y = i.y;
                                        }
                                    }
                                }
                            }
                            else if (str == 'r')
                                selected->type = pawn_type::player_rook;
                            else if (str == 'b')
                                selected->type = pawn_type::player_bishop;
                            else if (str == 'k')
                                selected->type = pawn_type::player_knight;
                            else {
                                std::cout << "ERROR!" << std::endl;
                            }
                        }
                    }

                    selected->x = i.x;
                    selected->y = i.y;

                    if (selected->type == pawn_type::player_queen) {
                        for (auto& y : *chess_sets) {
                            if (y.type == pawn_type::player_queen) {
                                y.x = i.x;
                                y.y = i.y;
                            }
                        }
                    }

                    auto j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = i.x, y = i.y](const chess_set& cs) -> bool {return (cs.knockout == true) && (cs.x == x) && (cs.y == y); });
                    chess_sets->erase(j);

                    moved = true;
                    break;
                }
                else if (i.type == pawn_type::step) {
                    if (selected->type == pawn_type::player_rook || selected->type == pawn_type::player_king)
                        if (selected->type == pawn_type::player_rook && selected->x == 0)
                            castle_left = false;
                        else if (selected->type == pawn_type::player_king) {
                            if ((i.x - selected->x) == 2 && castle_right == true) {
                                auto j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = 7, y = 0](const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y); });
                                j->x = i.x - 1;
                                castle_right = false;
                            }
                            else if ((i.x - selected->x) == -2 && castle_left == true) {
                                auto j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = 0, y = 0](const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y); });
                                j->x = i.x + 1;
                                castle_left = false;
                            }
                        }
                        else if(selected->type == pawn_type::player_rook && selected->x == 7)
                            castle_right = false;

                    else if (selected->type == pawn_type::player_pawn) {
                        if (i.y == 7) {
                            std::cout << "Please type in the Promotion (r for rook, q for queen, k for knight, b for bishop): " << std::endl;
                            char str;
                            std::cin >> str;
                            if (str == 'q') {
                                selected->type = pawn_type::player_queen;
                                if (selected->type == pawn_type::player_queen) {
                                    for (auto& y : *chess_sets) {
                                        if (y.type == pawn_type::player_queen) {
                                            y.x = i.x;
                                            y.y = i.y;
                                        }
                                    }
                                }
                            }
                            else if (str == 'r')
                                selected->type = pawn_type::player_rook;
                            else if (str == 'b')
                                selected->type = pawn_type::player_bishop;
                            else if (str == 'k')
                                selected->type = pawn_type::player_knight;
                            else {
                                std::cout << "ERROR!" << std::endl;
                                static_assert(true, "BYE!");
                            }
                        }
                    }
                    
                    selected->x = i.x;
                    selected->y = i.y;

                    if (selected->type == pawn_type::player_queen) {
                        for (auto& y : *chess_sets) {
                            if (y.type == pawn_type::player_queen) {
                                y.x = i.x;
                                y.y = i.y;
                            }
                        }
                    }

                    moved = true;

                    if (selected->type == pawn_type::player_king) {
                        castle_right = false;
                        castle_left = false;
                    }
                    break;
                }
                else {
                    auto j = std::find_if(chess_sets->begin(), chess_sets->end(), [step = pawn_type::step](const chess_set& cs) -> bool {return cs.type == step ; });
                    while (j != chess_sets->end()) {
                        chess_sets->erase(j);
                        j = std::find_if(chess_sets->begin(), chess_sets->end(), [step = pawn_type::step](const chess_set& cs) -> bool {return cs.type == step ; });
                    }

                    for (auto&k : *chess_sets)
                        k.knockout = false;

                    switch (i.type) {
                    case(pawn_type::player_bishop):
                        calculate_steps<pawn_type::player_bishop>(i);
                        break;
                    case(pawn_type::player_king):
                        calculate_steps<pawn_type::player_king>(i);
                        break;
                    case(pawn_type::player_knight):
                        calculate_steps<pawn_type::player_knight>(i);
                        break;
                    case(pawn_type::player_pawn):
                        calculate_steps<pawn_type::player_pawn>(i);
                        break;
                    case(pawn_type::player_queen):
                        calculate_steps<pawn_type::player_queen>(i);
                        break;
                    case(pawn_type::player_rook):
                        calculate_steps<pawn_type::player_rook>(i);
                        break;
                    }
                }
			}
            else {
                i.outline = false;
            }
	}
}

double Player::xpos = -1.0;
double Player::ypos = -1.0;
std::vector<chess_set>* Player::chess_sets;
chess_set* Player::selected;
bool Player::moved = false;
bool Player::castle_left = true;
bool Player::castle_right = true;
