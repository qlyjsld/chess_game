#include "Bot.h"

void Bot::play(std::vector<chess_set>& cs) {
    auto j = std::find_if(cs.begin(), cs.end(), [step = pawn_type::step](const chess_set& cs) -> bool {return cs.type == step; });
    while (j != cs.end()) {
        cs.erase(j);
        j = std::find_if(cs.begin(), cs.end(), [step = pawn_type::step](const chess_set& cs) -> bool {return cs.type == step; });
    }

    for (auto& k : cs) {
        k.knockout = false;
        k.outline = false;
    }

    AlphaBeta ab;
    ab.a = -2147483648;
    ab.b = 2147483647;
    ab = max(cs, 1, ab);
    cs = ab.cs;
}

AlphaBeta Bot::max(std::vector<chess_set> cs, const int& depth, const AlphaBeta& input_ab) {
    AlphaBeta ab = input_ab;
    AlphaBeta tmp_ab;
    std::vector<chess_set> solution = cs;
    for (auto& j : cs) {
        std::vector<chess_set> new_cs;
        new_cs = cs;
        switch (j.type) {
        case(pawn_type::bot_pawn):
            {new_cs = cs; 
            auto i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y-1](const chess_set& cs) {return cs.x == x && cs.y == y; });
            if (i == new_cs.end()) {
                if (j.y == 6) {
                    new_cs = cs;
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->y -= 1;
                    tmp_ab = min(new_cs, depth + 1, ab);
                    if (ab.a < tmp_ab.a) {
                        ab.a = tmp_ab.a;
                        solution = new_cs;
                    }
                    if (ab.a < tmp_ab.b) {
                        ab.a = tmp_ab.b;
                        solution = new_cs;
                    }
                    if (ab.a > ab.b)
                        break;

                    new_cs = cs;
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y - 2](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    if (i == new_cs.end()) {
                        i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                        i->y -= 2;
                        tmp_ab = min(new_cs, depth + 1, ab);
                        if (ab.a < tmp_ab.a) {
                            ab.a = tmp_ab.a;
                            solution = new_cs;
                        }
                        if (ab.a < tmp_ab.b) {
                            ab.a = tmp_ab.b;
                            solution = new_cs;
                        }
                        if (ab.a > ab.b)
                            break;
                    }
                }
                else {
                    new_cs = cs;
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->y -= 1;
                    if (i->y == 0)
                        i->type = pawn_type::bot_queen;
                    tmp_ab = min(new_cs, depth + 1, ab);
                    if (ab.a < tmp_ab.a) {
                        ab.a = tmp_ab.a;
                        solution = new_cs;
                    }
                    if (ab.a < tmp_ab.b) {
                        ab.a = tmp_ab.b;
                        solution = new_cs;
                    }
                    if (ab.a > ab.b)
                        break;
                }
            }
            
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y - 1,
                pk = pawn_type::player_king,
                pb = pawn_type::player_bishop,
                pp = pawn_type::player_pawn,
                pkn = pawn_type::player_knight,
                pq = pawn_type::player_queen,
                pr = pawn_type::player_rook] 
                (const chess_set& cs) {return cs.x == x && cs.y == y && (cs.type == pk || cs.type == pb || cs.type == pp || cs.type == pkn || cs.type == pq || cs.type == pr); });
            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y - 1](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x += 1;
                i->y -= 1;
                if (i->y == 0)
                    i->type = pawn_type::bot_queen;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y - 1,
                pk = pawn_type::player_king,
                pb = pawn_type::player_bishop,
                pp = pawn_type::player_pawn,
                pkn = pawn_type::player_knight,
                pq = pawn_type::player_queen,
                pr = pawn_type::player_rook]
                (const chess_set& cs) {return cs.x == x && cs.y == y && (cs.type == pk || cs.type == pb || cs.type == pp || cs.type == pkn || cs.type == pq || cs.type == pr); });
            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y - 1](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x -= 1;
                i->y -= 1;
                if (i->y == 0)
                    i->type = pawn_type::bot_queen;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }}

            break;

        case(pawn_type::bot_bishop):
            {int k = 1;
            new_cs = cs;
            auto i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y + k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x + k;
                i->y = j.y + k;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b){
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y + k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y + k,
                pp = pawn_type::player_pawn,
                pk = pawn_type::player_king,
                pq = pawn_type::player_queen,
                pkn = pawn_type::player_knight,
                pr = pawn_type::player_rook,
                pb = pawn_type::player_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });
            
            if (i != new_cs.end()){
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y + k](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x + k;
                i->y = j.y + k;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }

            k = 1;
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y - k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x + k;
                i->y = j.y - k;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y - k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y - k,
                pp = pawn_type::player_pawn,
                pk = pawn_type::player_king,
                pq = pawn_type::player_queen,
                pkn = pawn_type::player_knight,
                pr = pawn_type::player_rook,
                pb = pawn_type::player_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y - k](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x + k;
                i->y = j.y - k;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }

            k = 1;
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y + k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x - k;
                i->y = j.y + k;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y + k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y + k,
                pp = pawn_type::player_pawn,
                pk = pawn_type::player_king,
                pq = pawn_type::player_queen,
                pkn = pawn_type::player_knight,
                pr = pawn_type::player_rook,
                pb = pawn_type::player_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y + k](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x - k;
                i->y = j.y + k;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }

            k = 1;
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y - k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x - k;
                i->y = j.y - k;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y - k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y - k,
                pp = pawn_type::player_pawn,
                pk = pawn_type::player_king,
                pq = pawn_type::player_queen,
                pkn = pawn_type::player_knight,
                pr = pawn_type::player_rook,
                pb = pawn_type::player_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y - k](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x - k;
                i->y = j.y - k;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }}

            break;

        case(pawn_type::bot_king):
            {new_cs = cs;
            auto i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x + 1;
                i->y = j.y;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y,
                    pp = pawn_type::player_pawn,
                    pk = pawn_type::player_king,
                    pq = pawn_type::player_queen,
                    pkn = pawn_type::player_knight,
                    pr = pawn_type::player_rook,
                    pb = pawn_type::player_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x + 1;
                    i->y = j.y;
                    tmp_ab = min(new_cs, depth + 1, ab);
                    if (ab.a < tmp_ab.a) {
                        ab.a = tmp_ab.a;
                        solution = new_cs;
                    }
                    if (ab.a < tmp_ab.b) {
                        ab.a = tmp_ab.b;
                        solution = new_cs;
                    }
                    if (ab.a > ab.b)
                        break;
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y - 1](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x + 1;
                i->y = j.y - 1;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y - 1,
                    pp = pawn_type::player_pawn,
                    pk = pawn_type::player_king,
                    pq = pawn_type::player_queen,
                    pkn = pawn_type::player_knight,
                    pr = pawn_type::player_rook,
                    pb = pawn_type::player_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y - 1](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x + 1;
                    i->y = j.y - 1;
                    tmp_ab = min(new_cs, depth + 1, ab);
                    if (ab.a < tmp_ab.a) {
                        ab.a = tmp_ab.a;
                        solution = new_cs;
                    }
                    if (ab.a < tmp_ab.b) {
                        ab.a = tmp_ab.b;
                        solution = new_cs;
                    }
                    if (ab.a > ab.b)
                        break;
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y - 1](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x;
                i->y = j.y - 1;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y - 1,
                    pp = pawn_type::player_pawn,
                    pk = pawn_type::player_king,
                    pq = pawn_type::player_queen,
                    pkn = pawn_type::player_knight,
                    pr = pawn_type::player_rook,
                    pb = pawn_type::player_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y - 1](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x;
                    i->y = j.y - 1;
                    tmp_ab = min(new_cs, depth + 1, ab);
                    if (ab.a < tmp_ab.a) {
                        ab.a = tmp_ab.a;
                        solution = new_cs;
                    }
                    if (ab.a < tmp_ab.b) {
                        ab.a = tmp_ab.b;
                        solution = new_cs;
                    }
                    if (ab.a > ab.b)
                        break;
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y - 1](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x - 1;
                i->y = j.y - 1;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y - 1,
                    pp = pawn_type::player_pawn,
                    pk = pawn_type::player_king,
                    pq = pawn_type::player_queen,
                    pkn = pawn_type::player_knight,
                    pr = pawn_type::player_rook,
                    pb = pawn_type::player_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y - 1](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x - 1;
                    i->y = j.y - 1;
                    tmp_ab = min(new_cs, depth + 1, ab);
                    if (ab.a < tmp_ab.a) {
                        ab.a = tmp_ab.a;
                        solution = new_cs;
                    }
                    if (ab.a < tmp_ab.b) {
                        ab.a = tmp_ab.b;
                        solution = new_cs;
                    }
                    if (ab.a > ab.b)
                        break;
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y + 1](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x - 1;
                i->y = j.y + 1;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y + 1,
                    pp = pawn_type::player_pawn,
                    pk = pawn_type::player_king,
                    pq = pawn_type::player_queen,
                    pkn = pawn_type::player_knight,
                    pr = pawn_type::player_rook,
                    pb = pawn_type::player_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y + 1](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x - 1;
                    i->y = j.y + 1;
                    tmp_ab = min(new_cs, depth + 1, ab);
                    if (ab.a < tmp_ab.a) {
                        ab.a = tmp_ab.a;
                        solution = new_cs;
                    }
                    if (ab.a < tmp_ab.b) {
                        ab.a = tmp_ab.b;
                        solution = new_cs;
                    }
                    if (ab.a > ab.b)
                        break;
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y + 1](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x;
                i->y = j.y + 1;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y + 1,
                    pp = pawn_type::player_pawn,
                    pk = pawn_type::player_king,
                    pq = pawn_type::player_queen,
                    pkn = pawn_type::player_knight,
                    pr = pawn_type::player_rook,
                    pb = pawn_type::player_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y + 1](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x;
                    i->y = j.y + 1;
                    tmp_ab = min(new_cs, depth + 1, ab);
                    if (ab.a < tmp_ab.a) {
                        ab.a = tmp_ab.a;
                        solution = new_cs;
                    }
                    if (ab.a < tmp_ab.b) {
                        ab.a = tmp_ab.b;
                        solution = new_cs;
                    }
                    if (ab.a > ab.b)
                        break;
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y + 1](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x + 1;
                i->y = j.y + 1;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y + 1,
                    pp = pawn_type::player_pawn,
                    pk = pawn_type::player_king,
                    pq = pawn_type::player_queen,
                    pkn = pawn_type::player_knight,
                    pr = pawn_type::player_rook,
                    pb = pawn_type::player_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y + 1](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x + 1;
                    i->y = j.y + 1;
                    tmp_ab = min(new_cs, depth + 1, ab);
                    if (ab.a < tmp_ab.a) {
                        ab.a = tmp_ab.a;
                        solution = new_cs;
                    }
                    if (ab.a < tmp_ab.b) {
                        ab.a = tmp_ab.b;
                        solution = new_cs;
                    }
                    if (ab.a > ab.b)
                        break;
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x - 1;
                i->y = j.y;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y,
                    pp = pawn_type::player_pawn,
                    pk = pawn_type::player_king,
                    pq = pawn_type::player_queen,
                    pkn = pawn_type::player_knight,
                    pr = pawn_type::player_rook,
                    pb = pawn_type::player_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x - 1;
                    i->y = j.y;
                    tmp_ab = min(new_cs, depth + 1, ab);
                    if (ab.a < tmp_ab.a) {
                        ab.a = tmp_ab.a;
                        solution = new_cs;
                    }
                    if (ab.a < tmp_ab.b) {
                        ab.a = tmp_ab.b;
                        solution = new_cs;
                    }
                    if (ab.a > ab.b)
                        break;
                }
            }}

            break;

        case(pawn_type::bot_knight):
            {new_cs = cs;
            auto i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y + 2](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x + 1;
                i->y = j.y + 2;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y + 2,
                    pp = pawn_type::player_pawn,
                    pk = pawn_type::player_king,
                    pq = pawn_type::player_queen,
                    pkn = pawn_type::player_knight,
                    pr = pawn_type::player_rook,
                    pb = pawn_type::player_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y + 2](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x + 1;
                    i->y = j.y + 2;
                    tmp_ab = min(new_cs, depth + 1, ab);
                    if (ab.a < tmp_ab.a) {
                        ab.a = tmp_ab.a;
                        solution = new_cs;
                    }
                    if (ab.a < tmp_ab.b) {
                        ab.a = tmp_ab.b;
                        solution = new_cs;
                    }
                    if (ab.a > ab.b)
                        break;
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y + 2](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x - 1;
                i->y = j.y + 2;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y + 2,
                    pp = pawn_type::player_pawn,
                    pk = pawn_type::player_king,
                    pq = pawn_type::player_queen,
                    pkn = pawn_type::player_knight,
                    pr = pawn_type::player_rook,
                    pb = pawn_type::player_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y + 2](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x - 1;
                    i->y = j.y + 2;
                    tmp_ab = min(new_cs, depth + 1, ab);
                    if (ab.a < tmp_ab.a) {
                        ab.a = tmp_ab.a;
                        solution = new_cs;
                    }
                    if (ab.a < tmp_ab.b) {
                        ab.a = tmp_ab.b;
                        solution = new_cs;
                    }
                    if (ab.a > ab.b)
                        break;
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y - 2](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x + 1;
                i->y = j.y - 2;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y - 2,
                    pp = pawn_type::player_pawn,
                    pk = pawn_type::player_king,
                    pq = pawn_type::player_queen,
                    pkn = pawn_type::player_knight,
                    pr = pawn_type::player_rook,
                    pb = pawn_type::player_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y - 2](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x + 1;
                    i->y = j.y - 2;
                    tmp_ab = min(new_cs, depth + 1, ab);
                    if (ab.a < tmp_ab.a) {
                        ab.a = tmp_ab.a;
                        solution = new_cs;
                    }
                    if (ab.a < tmp_ab.b) {
                        ab.a = tmp_ab.b;
                        solution = new_cs;
                    }
                    if (ab.a > ab.b)
                        break;
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y - 2](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x - 1;
                i->y = j.y - 2;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y - 2,
                    pp = pawn_type::player_pawn,
                    pk = pawn_type::player_king,
                    pq = pawn_type::player_queen,
                    pkn = pawn_type::player_knight,
                    pr = pawn_type::player_rook,
                    pb = pawn_type::player_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y - 2](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x - 1;
                    i->y = j.y - 2;
                    tmp_ab = min(new_cs, depth + 1, ab);
                    if (ab.a < tmp_ab.a) {
                        ab.a = tmp_ab.a;
                        solution = new_cs;
                    }
                    if (ab.a < tmp_ab.b) {
                        ab.a = tmp_ab.b;
                        solution = new_cs;
                    }
                    if (ab.a > ab.b)
                        break;
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 2, y = j.y + 1](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x + 2;
                i->y = j.y + 1;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 2, y = j.y + 1,
                    pp = pawn_type::player_pawn,
                    pk = pawn_type::player_king,
                    pq = pawn_type::player_queen,
                    pkn = pawn_type::player_knight,
                    pr = pawn_type::player_rook,
                    pb = pawn_type::player_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 2, y = j.y + 1](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x + 2;
                    i->y = j.y + 1;
                    tmp_ab = min(new_cs, depth + 1, ab);
                    if (ab.a < tmp_ab.a) {
                        ab.a = tmp_ab.a;
                        solution = new_cs;
                    }
                    if (ab.a < tmp_ab.b) {
                        ab.a = tmp_ab.b;
                        solution = new_cs;
                    }
                    if (ab.a > ab.b)
                        break;
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 2, y = j.y + 1](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x - 2;
                i->y = j.y + 1;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 2, y = j.y + 1,
                    pp = pawn_type::player_pawn,
                    pk = pawn_type::player_king,
                    pq = pawn_type::player_queen,
                    pkn = pawn_type::player_knight,
                    pr = pawn_type::player_rook,
                    pb = pawn_type::player_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 2, y = j.y + 1](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x - 2;
                    i->y = j.y + 1;
                    tmp_ab = min(new_cs, depth + 1, ab);
                    if (ab.a < tmp_ab.a) {
                        ab.a = tmp_ab.a;
                        solution = new_cs;
                    }
                    if (ab.a < tmp_ab.b) {
                        ab.a = tmp_ab.b;
                        solution = new_cs;
                    }
                    if (ab.a > ab.b)
                        break;
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 2, y = j.y - 1](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x + 2;
                i->y = j.y - 1;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 2, y = j.y - 1,
                    pp = pawn_type::player_pawn,
                    pk = pawn_type::player_king,
                    pq = pawn_type::player_queen,
                    pkn = pawn_type::player_knight,
                    pr = pawn_type::player_rook,
                    pb = pawn_type::player_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 2, y = j.y - 1](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x + 2;
                    i->y = j.y - 1;
                    tmp_ab = min(new_cs, depth + 1, ab);
                    if (ab.a < tmp_ab.a) {
                        ab.a = tmp_ab.a;
                        solution = new_cs;
                    }
                    if (ab.a < tmp_ab.b) {
                        ab.a = tmp_ab.b;
                        solution = new_cs;
                    }
                    if (ab.a > ab.b)
                        break;
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 2, y = j.y - 1](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x - 2;
                i->y = j.y - 1;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 2, y = j.y - 1,
                    pp = pawn_type::player_pawn,
                    pk = pawn_type::player_king,
                    pq = pawn_type::player_queen,
                    pkn = pawn_type::player_knight,
                    pr = pawn_type::player_rook,
                    pb = pawn_type::player_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 2, y = j.y - 1](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x - 2;
                    i->y = j.y - 1;
                    tmp_ab = min(new_cs, depth + 1, ab);
                    if (ab.a < tmp_ab.a) {
                        ab.a = tmp_ab.a;
                        solution = new_cs;
                    }
                    if (ab.a < tmp_ab.b) {
                        ab.a = tmp_ab.b;
                        solution = new_cs;
                    }
                    if (ab.a > ab.b)
                        break;
                }
            }}

            break;

        case(pawn_type::bot_queen):
            {int k = 1;
            new_cs = cs;
            auto i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y + k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::bot_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::bot_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x;
                        y.y = j.y + k;
                    }
                i->x = j.x;
                i->y = j.y + k;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y + k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y + k,
                pp = pawn_type::player_pawn,
                pk = pawn_type::player_king,
                pq = pawn_type::player_queen,
                pkn = pawn_type::player_knight,
                pr = pawn_type::player_rook,
                pb = pawn_type::player_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y + k](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::bot_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::bot_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x;
                        y.y = j.y + k;
                    }
                i->x = j.x;
                i->y = j.y + k;
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }

            k = 1;
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y - k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::bot_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::bot_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x;
                        y.y = j.y - k;
                    }
                i->x = j.x;
                i->y = j.y - k;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y - k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y - k,
                pp = pawn_type::player_pawn,
                pk = pawn_type::player_king,
                pq = pawn_type::player_queen,
                pkn = pawn_type::player_knight,
                pr = pawn_type::player_rook,
                pb = pawn_type::player_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y - k](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::bot_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::bot_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x;
                        y.y = j.y - k;
                    }
                i->x = j.x;
                i->y = j.y - k;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }

            k = 1;
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::bot_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::bot_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x - k;
                        y.y = j.y;
                    }
                i->x = j.x - k;
                i->y = j.y;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y,
                pp = pawn_type::player_pawn,
                pk = pawn_type::player_king,
                pq = pawn_type::player_queen,
                pkn = pawn_type::player_knight,
                pr = pawn_type::player_rook,
                pb = pawn_type::player_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::bot_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::bot_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x - k;
                        y.y = j.y;
                    }
                i->x = j.x - k;
                i->y = j.y;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }

            k = 1;
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::bot_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::bot_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x + k;
                        y.y = j.y;
                    }
                i->x = j.x + k;
                i->y = j.y;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y,
                pp = pawn_type::player_pawn,
                pk = pawn_type::player_king,
                pq = pawn_type::player_queen,
                pkn = pawn_type::player_knight,
                pr = pawn_type::player_rook,
                pb = pawn_type::player_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::bot_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::bot_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x + k;
                        y.y = j.y;
                    }
                i->x = j.x + k;
                i->y = j.y;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }

            k = 1;
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y + k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::bot_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::bot_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x + k;
                        y.y = j.y + k;
                    }
                i->x = j.x + k;
                i->y = j.y + k;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y + k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y + k,
                pp = pawn_type::player_pawn,
                pk = pawn_type::player_king,
                pq = pawn_type::player_queen,
                pkn = pawn_type::player_knight,
                pr = pawn_type::player_rook,
                pb = pawn_type::player_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y + k](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::bot_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::bot_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x + k;
                        y.y = j.y + k;
                    }
                i->x = j.x + k;
                i->y = j.y + k;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }

            k = 1;
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y - k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::bot_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::bot_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x + k;
                        y.y = j.y - k;
                    }
                i->x = j.x + k;
                i->y = j.y - k;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y - k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y - k,
                pp = pawn_type::player_pawn,
                pk = pawn_type::player_king,
                pq = pawn_type::player_queen,
                pkn = pawn_type::player_knight,
                pr = pawn_type::player_rook,
                pb = pawn_type::player_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y - k](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::bot_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::bot_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x + k;
                        y.y = j.y - k;
                    }
                i->x = j.x + k;
                i->y = j.y - k;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }

            k = 1;
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y + k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::bot_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::bot_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x - k;
                        y.y = j.y + k;
                    }
                i->x = j.x - k;
                i->y = j.y + k;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y + k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y + k,
                pp = pawn_type::player_pawn,
                pk = pawn_type::player_king,
                pq = pawn_type::player_queen,
                pkn = pawn_type::player_knight,
                pr = pawn_type::player_rook,
                pb = pawn_type::player_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y + k](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::bot_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::bot_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x - k;
                        y.y = j.y + k;
                    }
                i->x = j.x - k;
                i->y = j.y + k;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }

            k = 1;
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y - k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::bot_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::bot_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x - k;
                        y.y = j.y - k;
                    }
                i->x = j.x - k;
                i->y = j.y - k;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y - k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y - k,
                pp = pawn_type::player_pawn,
                pk = pawn_type::player_king,
                pq = pawn_type::player_queen,
                pkn = pawn_type::player_knight,
                pr = pawn_type::player_rook,
                pb = pawn_type::player_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y - k](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::bot_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::bot_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x - k;
                        y.y = j.y - k;
                    }
                i->x = j.x - k;
                i->y = j.y - k;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }}

            break;
        case(pawn_type::bot_rook):
            {int k = 1;
            new_cs = cs;
            auto i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y + k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x;
                i->y = j.y + k;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y + k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y + k,
                pp = pawn_type::player_pawn,
                pk = pawn_type::player_king,
                pq = pawn_type::player_queen,
                pkn = pawn_type::player_knight,
                pr = pawn_type::player_rook,
                pb = pawn_type::player_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y + k](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x;
                i->y = j.y + k;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }

            k = 1;
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y - k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x;
                i->y = j.y - k;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y - k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y - k,
                pp = pawn_type::player_pawn,
                pk = pawn_type::player_king,
                pq = pawn_type::player_queen,
                pkn = pawn_type::player_knight,
                pr = pawn_type::player_rook,
                pb = pawn_type::player_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y - k](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x;
                i->y = j.y - k;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }

            k = 1;
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x - k;
                i->y = j.y;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y,
                pp = pawn_type::player_pawn,
                pk = pawn_type::player_king,
                pq = pawn_type::player_queen,
                pkn = pawn_type::player_knight,
                pr = pawn_type::player_rook,
                pb = pawn_type::player_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x - k;
                i->y = j.y;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }

            k = 1;
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x + k;
                i->y = j.y;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y,
                pp = pawn_type::player_pawn,
                pk = pawn_type::player_king,
                pq = pawn_type::player_queen,
                pkn = pawn_type::player_knight,
                pr = pawn_type::player_rook,
                pb = pawn_type::player_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == pp || cs.type == pk || cs.type == pq || cs.type == pkn || cs.type == pr || cs.type == pb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x + k;
                i->y = j.y;
                tmp_ab = min(new_cs, depth + 1, ab);
                if (ab.a < tmp_ab.a) {
                    ab.a = tmp_ab.a;
                    solution = new_cs;
                }
                if (ab.a < tmp_ab.b) {
                    ab.a = tmp_ab.b;
                    solution = new_cs;
                }
                if (ab.a > ab.b)
                    break;
            }}
            break;
        default:
            break;
        }
    }
    ab.cs = solution;
    return ab;
}

AlphaBeta Bot::min(std::vector<chess_set> cs, const int& depth, const AlphaBeta& input_ab) {
    AlphaBeta ab = input_ab;
    AlphaBeta tmp_ab;
    for (auto& j : cs) {
        std::vector<chess_set> new_cs;
        new_cs = cs;
        switch (j.type) {
        case(pawn_type::player_pawn):
            {new_cs = cs;
            auto i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y + 1](const chess_set& cs) {return cs.x == x && cs.y == y; });
            if (i == new_cs.end()) {
                if (j.y == 1) {
                    new_cs = cs;
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->y += 1;
                    if (depth != 4) {
                        tmp_ab = max(new_cs, depth + 1, ab);
                        if (ab.b > tmp_ab.a)
                            ab.b = tmp_ab.a;
                        if (ab.b > tmp_ab.b)
                            ab.b = tmp_ab.b;
                        if (ab.a > ab.b)
                            break;
                    }
                    else {
                        double value = evaluate_func(new_cs);
                        if (ab.b > value)
                            ab.b = value;
                        if (ab.a > ab.b)
                            break;
                    }
                    new_cs = cs;
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->y += 2;
                    if (depth != 4) {
                        tmp_ab = max(new_cs, depth + 1, ab);
                        if (ab.b > tmp_ab.a)
                            ab.b = tmp_ab.a;
                        if (ab.b > tmp_ab.b)
                            ab.b = tmp_ab.b;
                        if (ab.a > ab.b)
                            break;
                    }
                    else {
                        double value = evaluate_func(new_cs);
                        if (ab.b > value)
                            ab.b = value;
                        if (ab.a > ab.b)
                            break;
                    }
                }
                else {
                    new_cs = cs;
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->y += 1;
                    if (depth != 4) {
                        tmp_ab = max(new_cs, depth + 1, ab);
                        if (ab.b > tmp_ab.a)
                            ab.b = tmp_ab.a;
                        if (ab.b > tmp_ab.b)
                            ab.b = tmp_ab.b;
                        if (ab.a > ab.b)
                            break;
                    }
                    else {
                        double value = evaluate_func(new_cs);
                        if (ab.b > value)
                            ab.b = value;
                        if (ab.a > ab.b)
                            break;
                    }
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y + 1,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });
            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y + 1](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x += 1;
                i->y += 1;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y + 1,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });
            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y + 1](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x -= 1;
                i->y += 1;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }}

            break;

        case(pawn_type::player_bishop):
            {int k = 1;
            new_cs = cs;
            auto i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y + k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x + k;
                i->y = j.y + k;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y + k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y + k,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y + k](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x + k;
                i->y = j.y + k;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }

            k = 1;
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y - k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x + k;
                i->y = j.y - k;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y - k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y - k,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y - k](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x + k;
                i->y = j.y - k;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }

            k = 1;
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y + k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x - k;
                i->y = j.y + k;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y + k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y + k,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y + k](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x - k;
                i->y = j.y + k;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }

            k = 1;
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y - k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x - k;
                i->y = j.y - k;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y - k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y - k,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y - k](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x - k;
                i->y = j.y - k;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }}

            break;

        case(pawn_type::player_king):
            {new_cs = cs;
            auto i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x + 1;
                i->y = j.y;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y,
                    bp = pawn_type::bot_pawn,
                    bk = pawn_type::bot_king,
                    bq = pawn_type::bot_queen,
                    bkn = pawn_type::bot_knight,
                    br = pawn_type::bot_rook,
                    bb = pawn_type::bot_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x + 1;
                    i->y = j.y;
                    if (depth != 4) {
                        tmp_ab = max(new_cs, depth + 1, ab);
                        if (ab.b > tmp_ab.a)
                            ab.b = tmp_ab.a;
                        if (ab.b > tmp_ab.b)
                            ab.b = tmp_ab.b;
                        if (ab.a > ab.b)
                            break;
                    }
                    else {
                        double value = evaluate_func(new_cs);
                        if (ab.b > value)
                            ab.b = value;
                        if (ab.a > ab.b)
                            break;
                    }
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y - 1](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x + 1;
                i->y = j.y - 1;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y - 1,
                    bp = pawn_type::bot_pawn,
                    bk = pawn_type::bot_king,
                    bq = pawn_type::bot_queen,
                    bkn = pawn_type::bot_knight,
                    br = pawn_type::bot_rook,
                    bb = pawn_type::bot_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y - 1](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x + 1;
                    i->y = j.y - 1;
                    if (depth != 4) {
                        tmp_ab = max(new_cs, depth + 1, ab);
                        if (ab.b > tmp_ab.a)
                            ab.b = tmp_ab.a;
                        if (ab.b > tmp_ab.b)
                            ab.b = tmp_ab.b;
                        if (ab.a > ab.b)
                            break;
                    }
                    else {
                        double value = evaluate_func(new_cs);
                        if (ab.b > value)
                            ab.b = value;
                        if (ab.a > ab.b)
                            break;
                    }
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y - 1](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x;
                i->y = j.y - 1;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y - 1,
                    bp = pawn_type::bot_pawn,
                    bk = pawn_type::bot_king,
                    bq = pawn_type::bot_queen,
                    bkn = pawn_type::bot_knight,
                    br = pawn_type::bot_rook,
                    bb = pawn_type::bot_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y - 1](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x;
                    i->y = j.y - 1;
                    if (depth != 4) {
                        tmp_ab = max(new_cs, depth + 1, ab);
                        if (ab.b > tmp_ab.a)
                            ab.b = tmp_ab.a;
                        if (ab.b > tmp_ab.b)
                            ab.b = tmp_ab.b;
                        if (ab.a > ab.b)
                            break;
                    }
                    else {
                        double value = evaluate_func(new_cs);
                        if (ab.b > value)
                            ab.b = value;
                        if (ab.a > ab.b)
                            break;
                    }
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y - 1](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x - 1;
                i->y = j.y - 1;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y - 1,
                    bp = pawn_type::bot_pawn,
                    bk = pawn_type::bot_king,
                    bq = pawn_type::bot_queen,
                    bkn = pawn_type::bot_knight,
                    br = pawn_type::bot_rook,
                    bb = pawn_type::bot_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y - 1](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x - 1;
                    i->y = j.y - 1;
                    if (depth != 4) {
                        tmp_ab = max(new_cs, depth + 1, ab);
                        if (ab.b > tmp_ab.a)
                            ab.b = tmp_ab.a;
                        if (ab.b > tmp_ab.b)
                            ab.b = tmp_ab.b;
                        if (ab.a > ab.b)
                            break;
                    }
                    else {
                        double value = evaluate_func(new_cs);
                        if (ab.b > value)
                            ab.b = value;
                        if (ab.a > ab.b)
                            break;
                    }
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y + 1](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x - 1;
                i->y = j.y + 1;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y + 1,
                    bp = pawn_type::bot_pawn,
                    bk = pawn_type::bot_king,
                    bq = pawn_type::bot_queen,
                    bkn = pawn_type::bot_knight,
                    br = pawn_type::bot_rook,
                    bb = pawn_type::bot_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y + 1](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x - 1;
                    i->y = j.y + 1;
                    if (depth != 4) {
                        tmp_ab = max(new_cs, depth + 1, ab);
                        if (ab.b > tmp_ab.a)
                            ab.b = tmp_ab.a;
                        if (ab.b > tmp_ab.b)
                            ab.b = tmp_ab.b;
                        if (ab.a > ab.b)
                            break;
                    }
                    else {
                        double value = evaluate_func(new_cs);
                        if (ab.b > value)
                            ab.b = value;
                        if (ab.a > ab.b)
                            break;
                    }
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y + 1](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x;
                i->y = j.y + 1;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y + 1,
                    bp = pawn_type::bot_pawn,
                    bk = pawn_type::bot_king,
                    bq = pawn_type::bot_queen,
                    bkn = pawn_type::bot_knight,
                    br = pawn_type::bot_rook,
                    bb = pawn_type::bot_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y + 1](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x;
                    i->y = j.y + 1;
                    if (depth != 4) {
                        tmp_ab = max(new_cs, depth + 1, ab);
                        if (ab.b > tmp_ab.a)
                            ab.b = tmp_ab.a;
                        if (ab.b > tmp_ab.b)
                            ab.b = tmp_ab.b;
                        if (ab.a > ab.b)
                            break;
                    }
                    else {
                        double value = evaluate_func(new_cs);
                        if (ab.b > value)
                            ab.b = value;
                        if (ab.a > ab.b)
                            break;
                    }
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y + 1](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x + 1;
                i->y = j.y + 1;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y + 1,
                    bp = pawn_type::bot_pawn,
                    bk = pawn_type::bot_king,
                    bq = pawn_type::bot_queen,
                    bkn = pawn_type::bot_knight,
                    br = pawn_type::bot_rook,
                    bb = pawn_type::bot_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y + 1](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x + 1;
                    i->y = j.y + 1;
                    if (depth != 4) {
                        tmp_ab = max(new_cs, depth + 1, ab);
                        if (ab.b > tmp_ab.a)
                            ab.b = tmp_ab.a;
                        if (ab.b > tmp_ab.b)
                            ab.b = tmp_ab.b;
                        if (ab.a > ab.b)
                            break;
                    }
                    else {
                        double value = evaluate_func(new_cs);
                        if (ab.b > value)
                            ab.b = value;
                        if (ab.a > ab.b)
                            break;
                    }
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x - 1;
                i->y = j.y;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y,
                    bp = pawn_type::bot_pawn,
                    bk = pawn_type::bot_king,
                    bq = pawn_type::bot_queen,
                    bkn = pawn_type::bot_knight,
                    br = pawn_type::bot_rook,
                    bb = pawn_type::bot_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x - 1;
                    i->y = j.y;
                    if (depth != 4) {
                        tmp_ab = max(new_cs, depth + 1, ab);
                        if (ab.b > tmp_ab.a)
                            ab.b = tmp_ab.a;
                        if (ab.b > tmp_ab.b)
                            ab.b = tmp_ab.b;
                        if (ab.a > ab.b)
                            break;
                    }
                    else {
                        double value = evaluate_func(new_cs);
                        if (ab.b > value)
                            ab.b = value;
                        if (ab.a > ab.b)
                            break;
                    }
                }
            }}

            break;

        case(pawn_type::player_knight):
            {new_cs = cs;
            auto i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y + 2](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x + 1;
                i->y = j.y + 2;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y + 2,
                    bp = pawn_type::bot_pawn,
                    bk = pawn_type::bot_king,
                    bq = pawn_type::bot_queen,
                    bkn = pawn_type::bot_knight,
                    br = pawn_type::bot_rook,
                    bb = pawn_type::bot_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y + 2](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x + 1;
                    i->y = j.y + 2;
                    if (depth != 4) {
                        tmp_ab = max(new_cs, depth + 1, ab);
                        if (ab.b > tmp_ab.a)
                            ab.b = tmp_ab.a;
                        if (ab.b > tmp_ab.b)
                            ab.b = tmp_ab.b;
                        if (ab.a > ab.b)
                            break;
                    }
                    else {
                        double value = evaluate_func(new_cs);
                        if (ab.b > value)
                            ab.b = value;
                        if (ab.a > ab.b)
                            break;
                    }
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y + 2](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x - 1;
                i->y = j.y + 2;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y + 2,
                    bp = pawn_type::bot_pawn,
                    bk = pawn_type::bot_king,
                    bq = pawn_type::bot_queen,
                    bkn = pawn_type::bot_knight,
                    br = pawn_type::bot_rook,
                    bb = pawn_type::bot_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y + 2](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x - 1;
                    i->y = j.y + 2;
                    if (depth != 4) {
                        tmp_ab = max(new_cs, depth + 1, ab);
                        if (ab.b > tmp_ab.a)
                            ab.b = tmp_ab.a;
                        if (ab.b > tmp_ab.b)
                            ab.b = tmp_ab.b;
                        if (ab.a > ab.b)
                            break;
                    }
                    else {
                        double value = evaluate_func(new_cs);
                        if (ab.b > value)
                            ab.b = value;
                        if (ab.a > ab.b)
                            break;
                    }
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y - 2](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x + 1;
                i->y = j.y - 2;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y - 2,
                    bp = pawn_type::bot_pawn,
                    bk = pawn_type::bot_king,
                    bq = pawn_type::bot_queen,
                    bkn = pawn_type::bot_knight,
                    br = pawn_type::bot_rook,
                    bb = pawn_type::bot_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 1, y = j.y - 2](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x + 1;
                    i->y = j.y - 2;
                    if (depth != 4) {
                        tmp_ab = max(new_cs, depth + 1, ab);
                        if (ab.b > tmp_ab.a)
                            ab.b = tmp_ab.a;
                        if (ab.b > tmp_ab.b)
                            ab.b = tmp_ab.b;
                        if (ab.a > ab.b)
                            break;
                    }
                    else {
                        double value = evaluate_func(new_cs);
                        if (ab.b > value)
                            ab.b = value;
                        if (ab.a > ab.b)
                            break;
                    }
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y - 2](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x - 1;
                i->y = j.y - 2;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y - 2,
                    bp = pawn_type::bot_pawn,
                    bk = pawn_type::bot_king,
                    bq = pawn_type::bot_queen,
                    bkn = pawn_type::bot_knight,
                    br = pawn_type::bot_rook,
                    bb = pawn_type::bot_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 1, y = j.y - 2](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x - 1;
                    i->y = j.y - 2;
                    if (depth != 4) {
                        tmp_ab = max(new_cs, depth + 1, ab);
                        if (ab.b > tmp_ab.a)
                            ab.b = tmp_ab.a;
                        if (ab.b > tmp_ab.b)
                            ab.b = tmp_ab.b;
                        if (ab.a > ab.b)
                            break;
                    }
                    else {
                        double value = evaluate_func(new_cs);
                        if (ab.b > value)
                            ab.b = value;
                        if (ab.a > ab.b)
                            break;
                    }
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 2, y = j.y + 1](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x + 2;
                i->y = j.y + 1;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 2, y = j.y + 1,
                    bp = pawn_type::bot_pawn,
                    bk = pawn_type::bot_king,
                    bq = pawn_type::bot_queen,
                    bkn = pawn_type::bot_knight,
                    br = pawn_type::bot_rook,
                    bb = pawn_type::bot_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 2, y = j.y + 1](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x + 2;
                    i->y = j.y + 1;
                    if (depth != 4) {
                        tmp_ab = max(new_cs, depth + 1, ab);
                        if (ab.b > tmp_ab.a)
                            ab.b = tmp_ab.a;
                        if (ab.b > tmp_ab.b)
                            ab.b = tmp_ab.b;
                        if (ab.a > ab.b)
                            break;
                    }
                    else {
                        double value = evaluate_func(new_cs);
                        if (ab.b > value)
                            ab.b = value;
                        if (ab.a > ab.b)
                            break;
                    }
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 2, y = j.y + 1](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x - 2;
                i->y = j.y + 1;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 2, y = j.y + 1,
                    bp = pawn_type::bot_pawn,
                    bk = pawn_type::bot_king,
                    bq = pawn_type::bot_queen,
                    bkn = pawn_type::bot_knight,
                    br = pawn_type::bot_rook,
                    bb = pawn_type::bot_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 2, y = j.y + 1](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x - 2;
                    i->y = j.y + 1;
                    if (depth != 4) {
                        tmp_ab = max(new_cs, depth + 1, ab);
                        if (ab.b > tmp_ab.a)
                            ab.b = tmp_ab.a;
                        if (ab.b > tmp_ab.b)
                            ab.b = tmp_ab.b;
                        if (ab.a > ab.b)
                            break;
                    }
                    else {
                        double value = evaluate_func(new_cs);
                        if (ab.b > value)
                            ab.b = value;
                        if (ab.a > ab.b)
                            break;
                    }
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 2, y = j.y - 1](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x + 2;
                i->y = j.y - 1;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 2, y = j.y - 1,
                    bp = pawn_type::bot_pawn,
                    bk = pawn_type::bot_king,
                    bq = pawn_type::bot_queen,
                    bkn = pawn_type::bot_knight,
                    br = pawn_type::bot_rook,
                    bb = pawn_type::bot_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + 2, y = j.y - 1](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x + 2;
                    i->y = j.y - 1;
                    if (depth != 4) {
                        tmp_ab = max(new_cs, depth + 1, ab);
                        if (ab.b > tmp_ab.a)
                            ab.b = tmp_ab.a;
                        if (ab.b > tmp_ab.b)
                            ab.b = tmp_ab.b;
                        if (ab.a > ab.b)
                            break;
                    }
                    else {
                        double value = evaluate_func(new_cs);
                        if (ab.b > value)
                            ab.b = value;
                        if (ab.a > ab.b)
                            break;
                    }
                }
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 2, y = j.y - 1](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            if (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x - 2;
                i->y = j.y - 1;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }
            else {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 2, y = j.y - 1,
                    bp = pawn_type::bot_pawn,
                    bk = pawn_type::bot_king,
                    bq = pawn_type::bot_queen,
                    bkn = pawn_type::bot_knight,
                    br = pawn_type::bot_rook,
                    bb = pawn_type::bot_bishop]
                    (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });
                if (i != new_cs.end()) {
                    new_cs = cs;
                    new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - 2, y = j.y - 1](const chess_set& cs){return cs.x == x && cs.y == y; }));
                    i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                    i->x = j.x - 2;
                    i->y = j.y - 1;
                    if (depth != 4) {
                        tmp_ab = max(new_cs, depth + 1, ab);
                        if (ab.b > tmp_ab.a)
                            ab.b = tmp_ab.a;
                        if (ab.b > tmp_ab.b)
                            ab.b = tmp_ab.b;
                        if (ab.a > ab.b)
                            break;
                    }
                    else {
                        double value = evaluate_func(new_cs);
                        if (ab.b > value)
                            ab.b = value;
                        if (ab.a > ab.b)
                            break;
                    }
                }
            }}

            break;

        case(pawn_type::player_queen):
            {int k = 1;
            new_cs = cs;
            auto i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y + k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::player_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::player_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x;
                        y.y = j.y + k;
                    }
                i->x = j.x;
                i->y = j.y + k;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y + k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y + k,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y + k](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::player_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::player_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x;
                        y.y = j.y + k;
                    }
                i->x = j.x;
                i->y = j.y + k;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }

            k = 1;
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y - k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::player_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::player_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x;
                        y.y = j.y - k;
                    }
                i->x = j.x;
                i->y = j.y - k;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y - k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y - k,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y - k](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::player_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::player_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x;
                        y.y = j.y - k;
                    }
                i->x = j.x;
                i->y = j.y - k;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }

            k = 1;
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::player_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::player_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x - k;
                        y.y = j.y;
                    }
                i->x = j.x - k;
                i->y = j.y;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::player_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::player_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x - k;
                        y.y = j.y;
                    }
                i->x = j.x - k;
                i->y = j.y;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }

            k = 1;
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::player_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::player_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x + k;
                        y.y = j.y;
                    }
                i->x = j.x + k;
                i->y = j.y;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::player_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::player_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x + k;
                        y.y = j.y;
                    }
                i->x = j.x + k;
                i->y = j.y;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }

            k = 1;
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y + k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::player_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::player_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x + k;
                        y.y = j.y + k;
                    }
                i->x = j.x + k;
                i->y = j.y + k;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y + k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y + k,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y + k](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::player_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::player_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x + k;
                        y.y = j.y + k;
                    }
                i->x = j.x + k;
                i->y = j.y + k;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }

            k = 1;
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y - k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::player_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::player_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x + k;
                        y.y = j.y - k;
                    }
                i->x = j.x + k;
                i->y = j.y - k;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y - k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y - k,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y - k](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::player_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::player_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x + k;
                        y.y = j.y - k;
                    }
                i->x = j.x + k;
                i->y = j.y - k;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }

            k = 1;
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y + k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::player_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::player_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x - k;
                        y.y = j.y + k;
                    }
                i->x = j.x - k;
                i->y = j.y + k;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y + k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y + k,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y + k](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::player_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::player_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x - k;
                        y.y = j.y + k;
                    }
                i->x = j.x - k;
                i->y = j.y + k;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }

            k = 1;
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y - k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::player_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::player_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x - k;
                        y.y = j.y - k;
                    }
                i->x = j.x - k;
                i->y = j.y - k;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y - k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y - k,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y - k](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y && cs.type == pawn_type::player_queen; });
                for (auto& y : new_cs)
                    if ((y.type == pawn_type::player_queen) && (y.x == j.x) && (y.y == j.y)) {
                        y.x = j.x - k;
                        y.y = j.y - k;
                    }
                i->x = j.x - k;
                i->y = j.y - k;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }}

            break;
        case(pawn_type::player_rook):
            {int k = 1;
            new_cs = cs;
            auto i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y + k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x;
                i->y = j.y + k;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y + k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y + k,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y + k](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x;
                i->y = j.y + k;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }

            k = 1;
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y - k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x;
                i->y = j.y - k;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y - k](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y - k,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y - k](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x;
                i->y = j.y - k;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }

            k = 1;
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x - k;
                i->y = j.y;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x - k, y = j.y](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x - k;
                i->y = j.y;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }

            k = 1;
            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            while (i == new_cs.end()) {
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x + k;
                i->y = j.y;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
                k++;
                new_cs = cs;
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y](const chess_set& cs) -> bool {return ((cs.x == x) && (cs.y == y)) || (x < 0 || x > 7) || (y < 0 || y > 7); });
            }

            new_cs = cs;
            i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y,
                bp = pawn_type::bot_pawn,
                bk = pawn_type::bot_king,
                bq = pawn_type::bot_queen,
                bkn = pawn_type::bot_knight,
                br = pawn_type::bot_rook,
                bb = pawn_type::bot_bishop]
                (const chess_set& cs) -> bool {return (cs.x == x) && (cs.y == y) && (cs.type == bp || cs.type == bk || cs.type == bq || cs.type == bkn || cs.type == br || cs.type == bb); });

            if (i != new_cs.end()) {
                new_cs = cs;
                new_cs.erase(std::find_if(new_cs.begin(), new_cs.end(), [x = j.x + k, y = j.y](const chess_set& cs){return cs.x == x && cs.y == y; }));
                i = std::find_if(new_cs.begin(), new_cs.end(), [x = j.x, y = j.y](const chess_set& cs) {return cs.x == x && cs.y == y; });
                i->x = j.x + k;
                i->y = j.y;
                if (depth != 4) {
                    tmp_ab = max(new_cs, depth + 1, ab);
                    if (ab.b > tmp_ab.a)
                        ab.b = tmp_ab.a;
                    if (ab.b > tmp_ab.b)
                        ab.b = tmp_ab.b;
                    if (ab.a > ab.b)
                        break;
                }
                else {
                    double value = evaluate_func(new_cs);
                    if (ab.b > value)
                        ab.b = value;
                    if (ab.a > ab.b)
                        break;
                }
            }}

            break;

        default:
            break;
        }
    }
    return ab;
}

double Bot::evaluate_func(const std::vector<chess_set>& cs) {
    double result = 0;
    for (auto& j : cs) {
        switch (j.type) {
        case(pawn_type::bot_bishop):
            result += 30 + bishopEval[j.y][j.x];
            break;
        case(pawn_type::bot_king):
            result += 1000 + kingEval[j.y][j.x];
            break;
        case(pawn_type::bot_rook):
            result += 50 + rookEval[j.y][j.x];
            break;
        case(pawn_type::bot_knight):
            result += 30 + knightEval[j.y][j.x];
            break;
        case(pawn_type::bot_pawn):
            result += 10 + pawnEval[j.y][j.x];
            break;
        case(pawn_type::bot_queen):
            result += 90 + queenEval[j.y][j.x];
            break;
        case(pawn_type::player_bishop):
            result -= 30 + bishopEval[7 - j.y][j.x];
            break;
        case(pawn_type::player_king):
            result -= 1000 + kingEval[7 - j.y][j.x];
            break;
        case(pawn_type::player_rook):
            result -= 50 + rookEval[7 - j.y][j.x];
            break;
        case(pawn_type::player_knight):
            result -= 30 + knightEval[7 - j.y][j.x];
            break;
        case(pawn_type::player_pawn):
            result -= 10 + pawnEval[7 - j.y][j.x];
            break;
        case(pawn_type::player_queen):
            result -= 90 + queenEval[7 - j.y][j.x];
            break;
        }
    }
    return result;
}