#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include "Piece.h"
#include "ChessBoard.h"

std::random_device rd;
std::mt19937 rng(rd());

int main() {
    ChessBoard chessboard;
    chessboard.make();
    chessboard.printBoard();
    int steps;
    std::cout << "Input step: ";
    std::cin >> steps;
    std::cout << "-------------\n";
    std::vector<std::vector<int>> moves;
    bool t = 1;
    while (t) {
        chessboard.make();
        for (int i = 0; i < steps; i++) {
            if (chessboard.black.size() == 0 || chessboard.white.size() == 0) { break; }
            if (i % 2 == 1) {
                std::shuffle(chessboard.black.begin(), chessboard.black.end(), rng);
                moves = chessboard.move(chessboard.black[0]);
                std::shuffle(moves.begin(), moves.end(), rng);
                if (moves.size() == 0) {
                    continue;
                }
                chessboard.board[moves[0][0]][moves[0][1]] = chessboard.black[0];

                chessboard.board[chessboard.black[0].y][chessboard.black[0].x] = Piece();
                for (int j = 0; j < chessboard.white.size(); j++) {
                    if (chessboard.white[j].x == moves[0][1] && chessboard.white[j].y == moves[0][0]) {
                        chessboard.white[j] = chessboard.white[chessboard.white.size() - 1];
                        chessboard.white.pop_back();
                        break;
                    }
                }
                chessboard.black[0].x = moves[0][1];
                chessboard.black[0].y = moves[0][0];
            }
            else
            {
                std::shuffle(chessboard.white.begin(), chessboard.white.end(), rng);
                moves = chessboard.move(chessboard.white[0]);
                std::shuffle(moves.begin(), moves.end(), rng);
                if (moves.size() == 0) {
                    continue;
                }
                chessboard.board[moves[0][0]][moves[0][1]] = chessboard.white[0];
                chessboard.board[chessboard.white[0].y][chessboard.white[0].x] = Piece();
                for (int j = 0; j < chessboard.black.size(); j++) {
                    if (chessboard.black[j].x == moves[0][1] && chessboard.black[j].y == moves[0][0]) {
                        chessboard.black[j] = chessboard.black[chessboard.black.size() - 1];
                        chessboard.black.pop_back();
                        break;
                    }
                }
                chessboard.white[0].x = moves[0][1];
                chessboard.white[0].y = moves[0][0];
            }


        }
        int king = 0;
        int knight = 0;
        int bishop = 0;
        int rook = 0;
        for (int i = 0; i < chessboard.white.size(); i++) {
            if (chessboard.white[i].name == "king") { king += 1; }
            if (chessboard.white[i].name == "knight") { knight += 1; }
            if (chessboard.white[i].name == "bishop") { bishop += 1; }
            if (chessboard.white[i].name == "rook") { rook += 1; }
        }
        for (int i = 0; i < chessboard.black.size(); i++) {
            if (chessboard.black[i].name == "King") { king += 1; }
            if (chessboard.black[i].name == "Knight") { knight += 1; }
            if (chessboard.black[i].name == "Bishop") { bishop += 1; }
            if (chessboard.black[i].name == "Rook") { rook += 1; }

        }
        if (king == 2 && knight > 2 && bishop > 2 && rook > 2) { t = 0; }
        for (int i = 0; i < chessboard.white.size(); i++) {
            moves = chessboard.move(chessboard.white[i]);
            for (int j = 0; j < moves.size(); j++) {
                if (chessboard.board[moves[j][0]][moves[j][1]].name == "King") { t = 1; break; }
            }
        }
        for (int i = 0; i < chessboard.black.size(); i++) {
            moves = chessboard.move(chessboard.black[i]);
            for (int j = 0; j < moves.size(); j++) {
                if (chessboard.board[moves[j][0]][moves[j][1]].name == "king") { t = 1; break; }
            }
        }
    }
    chessboard.printBoard();
    ChessBoard cb;
    int first = 0;
    int second = 0;
    int third = 0;
    int fourth = 0;
    std::vector<std::vector<int>> winmoves1;
    std::vector<std::vector<int>> winmoves2;
    std::vector<std::vector<int>> winmoves3;
    std::vector<std::vector<int>> winmoves4;
    for (int i = 0; i < chessboard.white.size(); i++) {
        moves = chessboard.move(chessboard.white[i]);
        for (int j = 0; j < moves.size(); j++) {
            int score = 0;
            cb.make();
            cb.white.clear();
            cb.board.clear();
            cb.board = chessboard.board;
            cb.white = chessboard.white;
            if (cb.board[moves[j][0]][moves[j][1]].name == "Pawn") { score += 1; }
            if (cb.board[moves[j][0]][moves[j][1]].name == "Bishop") { score += 3; }
            if (cb.board[moves[j][0]][moves[j][1]].name == "Knight") { score += 3; }
            if (cb.board[moves[j][0]][moves[j][1]].name == "Rook") { score += 5; }
            cb.board[moves[j][0]][moves[j][1]] = cb.white[i];
            cb.board[cb.white[i].y][cb.white[i].x] = Piece();
            cb.white[i].x = moves[j][1];
            cb.white[i].y = moves[j][0];
            for (int k = 0; k < cb.white.size(); k++) {
                std::vector<std::vector<int>> moves1;
                moves1 = chessboard.move(cb.white[k]);
                for (int l = 0; l < moves1.size(); l++) {
                    int score1 = score;
                    ChessBoard cb1;
                    cb1.make();
                    cb1.white.clear();
                    cb1.board.clear();
                    cb1.board = cb.board;
                    cb1.white = cb.white;
                    if (cb1.board[moves1[l][0]][moves1[l][1]].name == "Pawn") { score1 += 1; }
                    if (cb1.board[moves1[l][0]][moves1[l][1]].name == "Bishop") { score1 += 3; }
                    if (cb1.board[moves1[l][0]][moves1[l][1]].name == "Knight") { score1 += 3; }
                    if (cb1.board[moves1[l][0]][moves1[l][1]].name == "Rook") { score1 += 5; }
                    if (cb1.board[moves1[l][0]][moves1[l][1]].name == "King") {
                        score1 += 1;
                        if (fourth < score1) {
                            winmoves4.clear();
                            fourth = score1;
                            winmoves4 = { {chessboard.white[i].y, chessboard.white[i].x}, moves[j], {cb1.white[k].y, cb1.white[k].x}, moves1[l] };
                        }
                        if (third < fourth) {
                            int repl;
                            std::vector<std::vector<int>> replvec;
                            replvec.clear();
                            repl = fourth;
                            fourth = third;
                            third = repl;
                            replvec = winmoves3;
                            winmoves3.clear();
                            winmoves3 = winmoves4;
                            winmoves4.clear();
                            winmoves4 = replvec;
                        }
                        if (second < third) {
                            int repl;
                            std::vector<std::vector<int>> replvec;
                            replvec.clear();
                            repl = third;
                            third = second;
                            second = repl;
                            replvec = winmoves2;
                            winmoves2.clear();
                            winmoves2 = winmoves3;
                            winmoves3.clear();
                            winmoves3 = replvec;
                        }
                        if (first < second) {
                            int repl;
                            std::vector<std::vector<int>> replvec;
                            replvec.clear();
                            repl = second;
                            second = first;
                            first = repl;
                            replvec = winmoves1;
                            winmoves1.clear();
                            winmoves1 = winmoves2;
                            winmoves2.clear();
                            winmoves2 = replvec;
                        }


                        continue;

                    }
                    cb1.board[moves1[l][0]][moves1[l][1]] = cb1.white[k];
                    cb1.board[cb1.white[k].y][cb1.white[k].x] = Piece();
                    cb1.white[k].x = moves1[l][1];
                    cb1.white[k].y = moves1[l][0];
                    for (int m = 0; m < cb1.white.size(); m++) {
                        std::vector<std::vector<int>> moves2;
                        moves2 = chessboard.move(cb1.white[m]);
                        for (int n = 0; n < moves2.size(); n++) {
                            ChessBoard cb2;
                            cb2.make();
                            cb2.white.clear();
                            cb2.board.clear();
                            cb2.board = cb1.board;
                            cb2.white = cb1.white;
                            int score2 = score1;
                            if (cb2.board[moves2[n][0]][moves2[n][1]].name == "Pawn") { score2 += 1; }
                            if (cb2.board[moves2[n][0]][moves2[n][1]].name == "Bishop") { score2 += 3; }
                            if (cb2.board[moves2[n][0]][moves2[n][1]].name == "Knight") { score2 += 3; }
                            if (cb2.board[moves2[n][0]][moves2[n][1]].name == "Rook") { score2 += 5; }
                            if (cb2.board[moves2[n][0]][moves2[n][1]].name == "King") {
                                score2 += 1;
                                if (fourth < score2) {
                                    winmoves4.clear();
                                    fourth = score2;
                                    winmoves4 = { {chessboard.white[i].y, chessboard.white[i].x}, moves[j], {cb.white[k].y, cb.white[k].x}, moves1[l], {cb1.white[m].y, cb1.white[m].x} , moves2[n] };
                                }
                                if (third < fourth) {
                                    int repl;
                                    std::vector<std::vector<int>> replvec;
                                    replvec.clear();
                                    repl = fourth;
                                    fourth = third;
                                    third = repl;
                                    replvec = winmoves3;
                                    winmoves3.clear();
                                    winmoves3 = winmoves4;
                                    winmoves4.clear();
                                    winmoves4 = replvec;
                                }
                                if (second < third) {
                                    int repl;
                                    std::vector<std::vector<int>> replvec;
                                    replvec.clear();
                                    repl = third;
                                    third = second;
                                    second = repl;
                                    replvec = winmoves2;
                                    winmoves2.clear();
                                    winmoves2 = winmoves3;
                                    winmoves3.clear();
                                    winmoves3 = replvec;
                                }
                                if (first < second) {
                                    int repl;
                                    std::vector<std::vector<int>> replvec;
                                    replvec.clear();
                                    repl = second;
                                    second = first;
                                    first = repl;
                                    replvec = winmoves1;
                                    winmoves1.clear();
                                    winmoves1 = winmoves2;
                                    winmoves2.clear();
                                    winmoves2 = replvec;
                                }
                                continue;

                            }
                            cb2.board[moves2[n][0]][moves2[n][1]] = cb2.white[m];
                            cb2.board[cb2.white[m].y][cb2.white[m].x] = Piece();
                            cb2.white[m].x = moves2[n][1];
                            cb2.white[m].y = moves2[n][0];
                            std::vector<std::vector<int>> moves3;
                            moves3 = chessboard.move(cb2.white[m]);
                            for (int p = 0; p < moves3.size(); p++) {
                                if (cb2.board[moves3[p][0]][moves3[p][1]].name == "King") { score2 += 1; break; }
                                
                            }

                            if (fourth < score2) {
                                winmoves4.clear();
                                fourth = score2;
                                winmoves4 = { {chessboard.white[i].y, chessboard.white[i].x}, moves[j], {cb.white[k].y, cb.white[k].x}, moves1[l], {cb1.white[m].y, cb1.white[m].x} , moves2[n] };
                            }
                            if (third < fourth) {
                                int repl;
                                std::vector<std::vector<int>> replvec;
                                replvec.clear();
                                repl = fourth;
                                fourth = third;
                                third = repl;
                                replvec = winmoves3;
                                winmoves3.clear();
                                winmoves3 = winmoves4;
                                winmoves4.clear();
                                winmoves4 = replvec;
                            }
                            if (second < third) {
                                int repl;
                                std::vector<std::vector<int>> replvec;
                                replvec.clear();
                                repl = third;
                                third = second;
                                second = repl;
                                replvec = winmoves2;
                                winmoves2.clear();
                                winmoves2 = winmoves3;
                                winmoves3.clear();
                                winmoves3 = replvec;
                            }
                            if (first < second) {
                                int repl;
                                std::vector<std::vector<int>> replvec;
                                replvec.clear();
                                repl = second;
                                second = first;
                                first = repl;
                                replvec = winmoves1;
                                winmoves1.clear();
                                winmoves1 = winmoves2;
                                winmoves2.clear();
                                winmoves2 = replvec;
                            }

                        }
                    }
                }
            }
        }
        
    }
    std::cout << "1st" << "\n";
    std::vector<char> cords = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
    for (int i = 0; i < winmoves1.size(); i += 2) {
        std::cout << cords[winmoves1[i][1]] << winmoves1[i][0]+1;
        std::cout << " -> ";
        std::cout << cords[winmoves1[i + 1][1]] << winmoves1[i + 1][0]+1 << '\n';
    }
    std::cout << "Score: " << first << "\n";
    std::cout << "2nd" << "\n";
    for (int i = 0; i < winmoves2.size(); i += 2) {
        std::cout << cords[winmoves2[i][1]] << winmoves2[i][0] + 1;
        std::cout << " -> ";
        std::cout << cords[winmoves2[i + 1][1]] << winmoves2[i + 1][0] + 1 << '\n';
    }
    std::cout << "Score: " << second << "\n";
    std::cout << "3rd" << "\n";
    for (int i = 0; i < winmoves3.size(); i += 2) {
        std::cout << cords[winmoves3[i][1]] << winmoves3[i][0] + 1;
        std::cout << " -> ";
        std::cout << cords[winmoves3[i + 1][1]] << winmoves3[i + 1][0] + 1 << '\n';
    }
    std::cout << "Score: " << third << "\n";
    std::cout << "4th" << "\n";
    for (int i = 0; i < winmoves4.size(); i += 2) {
        std::cout << cords[winmoves4[i][1]] << winmoves4[i][0] + 1;
        std::cout << " -> ";
        std::cout << cords[winmoves4[i + 1][1]] << winmoves4[i + 1][0] + 1 << '\n';
    }
    std::cout << "Score: " << fourth << "\n";
    return 0;
}