#include "TicTacToeView.h"
#include "TicTacToeMove.h"
#include <memory>
using namespace std;


TicTacToeView::TicTacToeView(shared_ptr<TicTacToeBoard> board) : mTTTBoard(board) {
}

void TicTacToeView::PrintBoard(std::ostream & s) const {
	s << "-";
	for (int b = 0; b < mTTTBoard.get()->BOARD_SIZE; b++)
		s << " " << b;
	for (int r = 0; r < mTTTBoard.get()->BOARD_SIZE; r++) {
		s << std::endl;
		s << r;
		for (int c = 0; c < mTTTBoard.get()->BOARD_SIZE; c++)
			switch (mTTTBoard.get()->GetPlayerAtPosition(BoardPosition(r, c))) {
			case TicTacToeBoard::Player::EMPTY: s << " .";
				break;
			case TicTacToeBoard::Player::X : s << " X";
				break;
			case TicTacToeBoard::Player::O: s << " O";
				break;
			}
	}
}

unique_ptr<GameMove> TicTacToeView::ParseMove(const string & move) const {
	std::istringstream parser{ move };
	char dummy;
	int r, c;
	parser >> dummy >> r >> dummy >> c;
	return std::make_unique<TicTacToeMove>(TicTacToeMove(BoardPosition(r, c)));
}

string TicTacToeView::GetPlayerString(int player) const {
	return player == 1 ? "X" : "O";
}
