#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include "Piece.h"


class ChessBoard {
public:
    std::vector<std::vector<Piece>> board;
    std::vector<Piece> white;
    std::vector<Piece> black;
    ChessBoard() {

        board.resize(8, std::vector<Piece>(8));
    }
    void make() {
            
            white.clear();
            black.clear();
            board.clear();
            board.resize(8, std::vector<Piece>(8));

            board[0][0] = { "rook", "White" ,0,0 };
            board[0][1] = { "knight", "White" ,0,1 };
            board[0][2] = { "bishop", "White" ,0,2 };
            board[0][4] = { "king", "White" ,0,4 };
            board[0][5] = { "bishop", "White" ,0,5 };
            board[0][6] = { "knight", "White" ,0,6 };
            board[0][7] = { "rook", "White" ,0,7 };
            for (int i = 0; i < 8; i++) {
                board[1][i] = { "pawn", "White" ,1,i };
                if (i != 3) { white.push_back(board[0][i]); }
                white.push_back(board[1][i]);
                
            }
           

            board[7][0] = { "Rook", "Black" ,7,0 };
            board[7][1] = { "Knight", "Black" ,7,1 };
            board[7][2] = { "Bishop", "Black" ,7,2 };
            board[7][4] = { "King", "Black" ,7,4 };
            board[7][5] = { "Bishop", "Black" ,7,5 };
            board[7][6] = { "Knight", "Black" ,7,6 };
            board[7][7] = { "Rook", "Black" ,7,7 };
            for (int i = 0; i < 8; i++) {
                board[6][i] = { "Pawn", "Black" ,6,i };
                if (i != 3) { black.push_back(board[7][i]); }
                black.push_back(board[6][i]);
            }

    }
    void printBoard() {
        std::cout << "   a  b  c  d  e  f  g  h" << std::endl;
        for (int i = 0; i < 8; i++) {
            std::cout << i + 1 << " ";
            for (int j = 0; j < 8; j++) {
                if (board[i][j].name.empty()) {
                    std::cout << "   ";
                }
                else {
                    if (board[i][j].name[1] != 'n'){ std::cout << " " << board[i][j].name[0] << " "; }
                    else { 
                        if (board[i][j].color == "White") {std::cout << " n "; }
                        else { {std::cout << " N "; }
                        }
                    }
                }
            }
            std::cout << std::endl;
        }
    }
    std::vector<std::vector<int>> move(Piece figure) {
        std::vector<std::vector<int>> moves;
        int x = figure.x;
        int y = figure.y;
        if (figure.name == "pawn" && y != 6) {
            if (board[y + 1][x].color == "") {
                moves.push_back(std::vector<int>{y + 1, x});
            }
            if (x != 7 && board[y + 1][x + 1].color == "Black") {
                moves.push_back(std::vector<int>{y + 1, x + 1});
            }
            if (x != 0 && board[y + 1][x - 1].color == "Black") {
                moves.push_back(std::vector<int>{y + 1, x - 1});
            }
        }
        if (figure.name == "Pawn" && y != 1) {
            if (board[y - 1][x].color == "") {
                moves.push_back(std::vector<int>{y - 1, x});
            }
            if (x != 7 && board[y - 1][x + 1].color == "White") {
                moves.push_back(std::vector<int>{y - 1, x + 1});
            }
            if (x != 0 && board[y - 1][x - 1].color == "White") {
                moves.push_back(std::vector<int>{y - 1, x - 1});
            }
        }
        if (figure.name == "rook" || figure.name == "Rook") {
            for (int i = 1; i < 8; i++) {
                if (y + i > 7 || board[y + i][x].color == figure.color) { break; }
                moves.push_back(std::vector<int>{y + i, x});
                if (board[y + i][x].color == "") { continue; }
                break;
            }
            for (int i = 1; i < 8; i++) {
                if (y - i < 0 || board[y - i][x].color == figure.color) { break; }
                moves.push_back(std::vector<int>{y - i, x});
                if (board[y - i][x].color == "") { continue; }
                break;
            }
            for (int i = 1; i < 8; i++) {
                if (x + i > 7 || board[y][x + i].color == figure.color) { break; }
                moves.push_back(std::vector<int>{y, x + i});
                if (board[y][x + i].color == "") { continue; }
                break;
            }
            for (int i = 1; i < 8; i++) {
                if (x - i < 0 || board[y][x - i].color == figure.color) { break; }
                moves.push_back(std::vector<int>{y, x - i});
                if (board[y][x - i].color == "") { continue; }
                break;
            }
        }
        if (figure.name == "knight" || figure.name == "Knight") {
            for (int i = -2; i < 3; i++) {
                for (int j = -1; j < 2; j++) {
                    if (i * j != 0 && x + i >= 0 && y + 2 / i * j >= 0 && x + i < 8 &&
                        y + 2 / i  * j < 8 && board[y + 2 / i * j][x + i].color != figure.color) {
                        moves.push_back(std::vector<int>{y + 2 / i * j, x + i});
                    }
                }
            }
        }
        if (figure.name == "bishop" || figure.name == "Bishop") {
            for (int i = 1; i < 8; i++) {
                if (y + i > 7 || x - i < 0 || board[y + i][x - i].color == figure.color) { break; }
                moves.push_back(std::vector<int>{y + i, x - i});
                if (board[y + i][x - i].color == "") { continue; }
                break;
            }
            for (int i = 1; i < 8; i++) {
                if (y - i < 0 || x + i > 7 ||  board[y - i][x + i].color == figure.color) { break; }
                moves.push_back(std::vector<int>{y - i, x + i});
                if (board[y - i][x + i].color == "") { continue; }
                break;
            }
            for (int i = 1; i < 8; i++) {
                if (y + i > 7 || x + i > 7 || board[y + i][x + i].color == figure.color) { break; }
                moves.push_back(std::vector<int>{y + i, x + i});
                if (board[y + i][x + i].color == "") { continue; }
                break;
            }
            for (int i = 1; i < 8; i++) {
                if (x - i < 0 || y - i < 0 || board[y - i][x - i].color == figure.color) { break; }
                moves.push_back(std::vector<int>{y - i, x - i});
                if (board[y - i][x - i].color == "") { continue; }
                break;
            }
        }
        if (figure.name == "king" || figure.name == "King") {
            for (int i = -1; i < 2; i++) {
                for (int j = -1; j < 2; j++) {
                    if (i != 0 && j != 0 && x + i >= 0 && y + j >= 0 && x + i < 8 && y + j < 8 && board[y + j][x + i].color != figure.color) {
                        moves.push_back(std::vector<int>{y + j, x + i});
                    }
                }
            }
        }
        return moves;
    }
};