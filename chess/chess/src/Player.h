#pragma once
#include <GLFW/glfw3.h>
#include <vector>
#include "chess_set.h"

class Player {
public:
	void play(std::vector<chess_set>& cs, GLFWwindow*& window);
private:
	template<pawn_type T>
	static void calculate_steps(chess_set& i) {
		static_assert(false);
	}

	template<>
    static void calculate_steps<pawn_type::player_bishop>(chess_set& i) {
        selected = &i;
        i.outline = true;
        unsigned int k = 1;
        chess_set tmp;
        tmp.type = pawn_type::step;
        tmp.outline = false;
        tmp.knockout = false;

        k = 1;
        tmp.x = i.x + k;
        tmp.y = i.y + k;
        auto j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        while (j == chess_sets->end()) {
            chess_sets->push_back(tmp);
            k++;
            tmp.x = i.x + k;
            tmp.y = i.y + k;
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        }

        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
            bp = pawn_type::bot_pawn,
            bk = pawn_type::bot_king,
            bq = pawn_type::bot_queen,
            bkn = pawn_type::bot_knight,
            br = pawn_type::bot_rook,
            bb = pawn_type::bot_bishop]
            (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
        if (j != chess_sets->end())
            j->knockout = true;

        k = 1;
        tmp.x = i.x - k;
        tmp.y = i.y - k;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        while (j == chess_sets->end()) {
            chess_sets->push_back(tmp);
            k++;
            tmp.x = i.x - k;
            tmp.y = i.y - k;
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        }

        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
            bp = pawn_type::bot_pawn,
            bk = pawn_type::bot_king,
            bq = pawn_type::bot_queen,
            bkn = pawn_type::bot_knight,
            br = pawn_type::bot_rook,
            bb = pawn_type::bot_bishop]
            (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
        if (j != chess_sets->end())
            j->knockout = true;

        k = 1;
        tmp.x = i.x - k;
        tmp.y = i.y + k;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        while (j == chess_sets->end()) {
            chess_sets->push_back(tmp);
            k++;
            tmp.x = i.x - k;
            tmp.y = i.y + k;
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        }

        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
            bp = pawn_type::bot_pawn,
            bk = pawn_type::bot_king,
            bq = pawn_type::bot_queen,
            bkn = pawn_type::bot_knight,
            br = pawn_type::bot_rook,
            bb = pawn_type::bot_bishop]
            (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
        if (j != chess_sets->end())
            j->knockout = true;

        k = 1;
        tmp.x = i.x + k;
        tmp.y = i.y - k;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        while (j == chess_sets->end()) {
            chess_sets->push_back(tmp);
            k++;
            tmp.x = i.x + k;
            tmp.y = i.y - k;
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        }

        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
            bp = pawn_type::bot_pawn,
            bk = pawn_type::bot_king,
            bq = pawn_type::bot_queen,
            bkn = pawn_type::bot_knight,
            br = pawn_type::bot_rook,
            bb = pawn_type::bot_bishop]
            (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
        if (j != chess_sets->end())
            j->knockout = true;
	}

    template<>
    static void calculate_steps<pawn_type::player_king>(chess_set& i) {
        selected = &i;
        i.outline = true;
        chess_set tmp;
        tmp.type = pawn_type::step;
        tmp.outline = false;
        tmp.knockout = false;

        auto k = std::find_if(chess_sets->begin(), chess_sets->end(), [x = 0, y = 0](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) and (cs.type == pawn_type::player_rook); });
        if (k == chess_sets->end())
            castle_left = false;
        k = std::find_if(chess_sets->begin(), chess_sets->end(), [x = 7, y = 0](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) and (cs.type == pawn_type::player_rook); });
        if (k == chess_sets->end())
            castle_right = false;

        if (castle_left == true) {
            tmp.x = i.x - 2;
            tmp.y = i.y;
            auto j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
            if (j == chess_sets->end()) {
                j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x + 1, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
                if (j == chess_sets->end()) {
                    j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x - 1, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
                    if (j == chess_sets->end())
                        chess_sets->push_back(tmp);
                }
            }
        }

        if (castle_right == true) {
            tmp.x = i.x + 2;
            tmp.y = i.y;
            auto j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x - 1, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
            if (j == chess_sets->end()) {
                j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
                if (j == chess_sets->end())
                    chess_sets->push_back(tmp);
            }
        }


        tmp.x = i.x - 1;
        tmp.y = i.y;
        auto j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        if (j == chess_sets->end())
            chess_sets->push_back(tmp);
        else {
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
            if (j != chess_sets->end())
                j->knockout = true;
        }

        tmp.x = i.x - 1;
        tmp.y = i.y + 1;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        if (j == chess_sets->end())
            chess_sets->push_back(tmp);
        else {
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
            if (j != chess_sets->end())
                j->knockout = true;
        }

        tmp.x = i.x;
        tmp.y = i.y + 1;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        if (j == chess_sets->end())
            chess_sets->push_back(tmp);
        else {
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
            if (j != chess_sets->end())
                j->knockout = true;
        }

        tmp.x = i.x + 1;
        tmp.y = i.y + 1;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        if (j == chess_sets->end())
            chess_sets->push_back(tmp);
        else {
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
            if (j != chess_sets->end())
                j->knockout = true;
        }

        tmp.x = i.x + 1;
        tmp.y = i.y;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        if (j == chess_sets->end())
            chess_sets->push_back(tmp);
        else {
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
            if (j != chess_sets->end())
                j->knockout = true;
        }

        tmp.x = i.x + 1;
        tmp.y = i.y - 1;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        if (j == chess_sets->end())
            chess_sets->push_back(tmp);
        else {
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
            if (j != chess_sets->end())
                j->knockout = true;
        }

        tmp.x = i.x;
        tmp.y = i.y - 1;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        if (j == chess_sets->end())
            chess_sets->push_back(tmp);
        else {
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
            if (j != chess_sets->end())
                j->knockout = true;
        }
        tmp.x = i.x - 1;
        tmp.y = i.y - 1;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        if (j == chess_sets->end())
            chess_sets->push_back(tmp);
        else {
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
            if (j != chess_sets->end())
                j->knockout = true;
        }
    }

    template<>
    static void calculate_steps<pawn_type::player_rook>(chess_set& i) {
        selected = &i;
        i.outline = true;
        unsigned int k = 1;
        chess_set tmp;
        tmp.type = pawn_type::step;
        tmp.outline = false;
        tmp.knockout = false;

        k = 1;
        tmp.x = i.x + k;
        tmp.y = i.y;
        auto j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        while (j == chess_sets->end()) {
            chess_sets->push_back(tmp);
            k++;
            tmp.x = i.x + k;
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        }

        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
            bp = pawn_type::bot_pawn,
            bk = pawn_type::bot_king,
            bq = pawn_type::bot_queen,
            bkn = pawn_type::bot_knight,
            br = pawn_type::bot_rook,
            bb = pawn_type::bot_bishop]
            (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
        if (j != chess_sets->end())
            j->knockout = true;

        k = 1;
        tmp.x = i.x - k;
        tmp.y = i.y;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        while (j == chess_sets->end()) {
            chess_sets->push_back(tmp);
            k++;
            tmp.x = i.x - k;
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        }

        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
            bp = pawn_type::bot_pawn,
            bk = pawn_type::bot_king,
            bq = pawn_type::bot_queen,
            bkn = pawn_type::bot_knight,
            br = pawn_type::bot_rook,
            bb = pawn_type::bot_bishop]
            (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
        if (j != chess_sets->end())
            j->knockout = true;

        k = 1;
        tmp.x = i.x;
        tmp.y = i.y + k;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        while (j == chess_sets->end()) {
            chess_sets->push_back(tmp);
            k++;
            tmp.y = i.y + k;
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        }

        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
            bp = pawn_type::bot_pawn,
            bk = pawn_type::bot_king,
            bq = pawn_type::bot_queen,
            bkn = pawn_type::bot_knight,
            br = pawn_type::bot_rook,
            bb = pawn_type::bot_bishop]
            (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
        if (j != chess_sets->end())
            j->knockout = true;

        k = 1;
        tmp.x = i.x;
        tmp.y = i.y - k;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        while (j == chess_sets->end()) {
            chess_sets->push_back(tmp);
            k++;
            tmp.y = i.y - k;
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        }

        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
            bp = pawn_type::bot_pawn,
            bk = pawn_type::bot_king,
            bq = pawn_type::bot_queen,
            bkn = pawn_type::bot_knight,
            br = pawn_type::bot_rook,
            bb = pawn_type::bot_bishop]
            (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
        if (j != chess_sets->end())
            j->knockout = true;
    }

    template<>
    static void calculate_steps<pawn_type::player_queen>(chess_set& i) {
        selected = &i;
        i.outline = true;
        unsigned int k = 1;
        chess_set tmp;
        tmp.type = pawn_type::step;
        tmp.outline = false;
        tmp.knockout = false;

        k = 1;
        tmp.x = i.x + k;
        tmp.y = i.y + k;
        auto j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        while (j == chess_sets->end()) {
            chess_sets->push_back(tmp);
            k++;
            tmp.x = i.x + k;
            tmp.y = i.y + k;
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        }

        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
            bp = pawn_type::bot_pawn,
            bk = pawn_type::bot_king,
            bq = pawn_type::bot_queen,
            bkn = pawn_type::bot_knight,
            br = pawn_type::bot_rook,
            bb = pawn_type::bot_bishop]
            (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
        if (j != chess_sets->end())
            j->knockout = true;

        k = 1;
        tmp.x = i.x - k;
        tmp.y = i.y - k;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        while (j == chess_sets->end()) {
            chess_sets->push_back(tmp);
            k++;
            tmp.x = i.x - k;
            tmp.y = i.y - k;
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        }

        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
            bp = pawn_type::bot_pawn,
            bk = pawn_type::bot_king,
            bq = pawn_type::bot_queen,
            bkn = pawn_type::bot_knight,
            br = pawn_type::bot_rook,
            bb = pawn_type::bot_bishop]
            (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
        if (j != chess_sets->end())
            j->knockout = true;

        k = 1;
        tmp.x = i.x - k;
        tmp.y = i.y + k;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        while (j == chess_sets->end()) {
            chess_sets->push_back(tmp);
            k++;
            tmp.x = i.x - k;
            tmp.y = i.y + k;
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        }

        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
            bp = pawn_type::bot_pawn,
            bk = pawn_type::bot_king,
            bq = pawn_type::bot_queen,
            bkn = pawn_type::bot_knight,
            br = pawn_type::bot_rook,
            bb = pawn_type::bot_bishop]
            (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
        if (j != chess_sets->end())
            j->knockout = true;

        k = 1;
        tmp.x = i.x + k;
        tmp.y = i.y - k;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        while (j == chess_sets->end()) {
            chess_sets->push_back(tmp);
            k++;
            tmp.x = i.x + k;
            tmp.y = i.y - k;
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        }

        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
            bp = pawn_type::bot_pawn,
            bk = pawn_type::bot_king,
            bq = pawn_type::bot_queen,
            bkn = pawn_type::bot_knight,
            br = pawn_type::bot_rook,
            bb = pawn_type::bot_bishop]
            (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
        if (j != chess_sets->end())
            j->knockout = true;

        k = 1;
        tmp.x = i.x + k;
        tmp.y = i.y;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        while (j == chess_sets->end()) {
            chess_sets->push_back(tmp);
            k++;
            tmp.x = i.x + k;
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        }

        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
            bp = pawn_type::bot_pawn,
            bk = pawn_type::bot_king,
            bq = pawn_type::bot_queen,
            bkn = pawn_type::bot_knight,
            br = pawn_type::bot_rook,
            bb = pawn_type::bot_bishop]
            (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
        if (j != chess_sets->end())
            j->knockout = true;

        k = 1;
        tmp.x = i.x - k;
        tmp.y = i.y;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        while (j == chess_sets->end()) {
            chess_sets->push_back(tmp);
            k++;
            tmp.x = i.x - k;
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        }

        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
            bp = pawn_type::bot_pawn,
            bk = pawn_type::bot_king,
            bq = pawn_type::bot_queen,
            bkn = pawn_type::bot_knight,
            br = pawn_type::bot_rook,
            bb = pawn_type::bot_bishop]
            (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
        if (j != chess_sets->end())
            j->knockout = true;

        k = 1;
        tmp.x = i.x;
        tmp.y = i.y + k;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        while (j == chess_sets->end()) {
            chess_sets->push_back(tmp);
            k++;
            tmp.y = i.y + k;
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        }

        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
            bp = pawn_type::bot_pawn,
            bk = pawn_type::bot_king,
            bq = pawn_type::bot_queen,
            bkn = pawn_type::bot_knight,
            br = pawn_type::bot_rook,
            bb = pawn_type::bot_bishop]
            (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
        if (j != chess_sets->end())
            j->knockout = true;

        k = 1;
        tmp.x = i.x;
        tmp.y = i.y - k;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        while (j == chess_sets->end()) {
            chess_sets->push_back(tmp);
            k++;
            tmp.y = i.y - k;
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        }

        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
            bp = pawn_type::bot_pawn,
            bk = pawn_type::bot_king,
            bq = pawn_type::bot_queen,
            bkn = pawn_type::bot_knight,
            br = pawn_type::bot_rook,
            bb = pawn_type::bot_bishop]
            (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
        if (j != chess_sets->end())
            j->knockout = true;
    }

    template<>
    static void calculate_steps<pawn_type::player_knight>(chess_set& i) {
        selected = &i;
        i.outline = true;
        chess_set tmp;
        tmp.type = pawn_type::step;
        tmp.outline = false;
        tmp.knockout = false;

        tmp.x = i.x + 1;
        tmp.y = i.y + 2;
        auto j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        if (j == chess_sets->end())
            chess_sets->push_back(tmp);
        else {
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
            if (j != chess_sets->end())
                j->knockout = true;
        }

        tmp.x = i.x + 2;
        tmp.y = i.y + 1;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        if (j == chess_sets->end())
            chess_sets->push_back(tmp);
        else {
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
            if (j != chess_sets->end())
                j->knockout = true;
        }

        tmp.x = i.x + 2;
        tmp.y = i.y - 1;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        if (j == chess_sets->end())
            chess_sets->push_back(tmp);
        else {
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
            if (j != chess_sets->end())
                j->knockout = true;
        }

        tmp.x = i.x - 2;
        tmp.y = i.y + 1;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        if (j == chess_sets->end())
            chess_sets->push_back(tmp);
        else {
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
            if (j != chess_sets->end())
                j->knockout = true;
        }

        tmp.x = i.x - 2;
        tmp.y = i.y - 1;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        if (j == chess_sets->end())
            chess_sets->push_back(tmp);
        else {
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
            if (j != chess_sets->end())
                j->knockout = true;
        }

        tmp.x = i.x - 1;
        tmp.y = i.y + 2;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        if (j == chess_sets->end())
            chess_sets->push_back(tmp);
        else {
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
            if (j != chess_sets->end())
                j->knockout = true;
        }

        tmp.x = i.x + 1;
        tmp.y = i.y - 2;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        if (j == chess_sets->end())
            chess_sets->push_back(tmp);
        else {
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
            if (j != chess_sets->end())
                j->knockout = true;
        }

        tmp.x = i.x - 1;
        tmp.y = i.y - 2;
        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return ((cs.x == x) and (cs.y == y)) or (x < 0 or x > 7) or (y < 0 or y > 7); });
        if (j == chess_sets->end())
            chess_sets->push_back(tmp);
        else {
            j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
            if (j != chess_sets->end())
                j->knockout = true;
        }
    }

    template<>
    static void calculate_steps<pawn_type::player_pawn>(chess_set& i) {
        selected = &i;
        i.outline = true;
        if (i.y == 1) {
            chess_set tmp;
            tmp.type = pawn_type::step;
            tmp.y = 2;
            tmp.x = i.x;
            tmp.outline = false;
            tmp.knockout = false;

            auto j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y); });
            if (j == chess_sets->end()) {
                chess_sets->push_back(tmp);
                tmp.y = 3;
                j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y); });
                if (j == chess_sets->end())
                    chess_sets->push_back(tmp);
            }
        }
        else {
            chess_set tmp;
            tmp.type = pawn_type::step;
            tmp.y = i.y + 1;
            tmp.x = i.x;
            tmp.outline = false;
            tmp.knockout = false;

            auto j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = tmp.x, y = tmp.y](const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y); });
            if (j == chess_sets->end())
                chess_sets->push_back(tmp);
        }

        auto j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = i.x + 1, y = i.y + 1,
            bp = pawn_type::bot_pawn,
            bk = pawn_type::bot_king,
            bq = pawn_type::bot_queen,
            bkn = pawn_type::bot_knight,
            br = pawn_type::bot_rook,
            bb = pawn_type::bot_bishop]
            (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
        if (j != chess_sets->end())
            j->knockout = true;

        j = std::find_if(chess_sets->begin(), chess_sets->end(), [x = i.x - 1, y = i.y + 1,
            bp = pawn_type::bot_pawn,
            bk = pawn_type::bot_king,
            bq = pawn_type::bot_queen,
            bkn = pawn_type::bot_knight,
            br = pawn_type::bot_rook,
            bb = pawn_type::bot_bishop]
            (const chess_set& cs) -> bool {return (cs.x == x) and (cs.y == y) and (cs.type == bp or cs.type == bk or cs.type == bq or cs.type == bkn or cs.type == br or cs.type == bb); });
        if (j != chess_sets->end())
            j->knockout = true;
    }

	static std::vector<chess_set>* chess_sets;
	static chess_set* selected;
	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	static double xpos, ypos;
	static bool moved;
	static bool castle_left;
	static bool castle_right;
};
