#include "TicTacToeBoard.h"
#include "TicTacToeMove.h"
#include "BoardDirection.h"
#include "BoardPosition.h"
#include <iostream>
using namespace std;

void TicTacToeBoard::CheckForWinner() {
	for (auto pos : BoardPosition::GetRectangularPositions(mBoard.size(), mBoard[0].size())) {
		for (auto dir : CARDINAL_DIRECTIONS) {
			BoardPosition current = pos;
			bool threeInARow = true;

			for (int steps = 0; steps < 3; steps++) {
				if (!InBounds(current) || mCurrentPlayer != GetPlayerAtPosition(current)) {
					threeInARow = false;
					break;
				}
				current = current + dir;
			}

			if (threeInARow) {
				mCurrentValue = static_cast<int>(mCurrentPlayer);
				return;
			}
		}
	}
}

TicTacToeBoard::TicTacToeBoard() : mBoard({ Player::EMPTY }), mCurrentPlayer(Player::X), mCurrentValue(0) {
}

vector<unique_ptr<GameMove>> TicTacToeBoard::GetPossibleMoves() const {
	auto possibleMoves = std::vector<std::unique_ptr<GameMove>>();

	for (int r = 0; r < BOARD_SIZE; r++) {
		for (int c = 0; c < BOARD_SIZE; c++) {
			if (mBoard[r][c] == Player::EMPTY) {
				possibleMoves.push_back(std::make_unique<TicTacToeMove>(TicTacToeMove(BoardPosition(r, c))));
			}
		}
	}

	return possibleMoves;
}

void TicTacToeBoard::ApplyMove(unique_ptr<GameMove> move) {
	TicTacToeMove *m = dynamic_cast<TicTacToeMove*>(move.get());
	if (mBoard[m->GetPosition().GetRow()][m->GetPosition().GetCol()] == Player::EMPTY)
		mBoard[m->GetPosition().GetRow()][m->GetPosition().GetCol()] = mCurrentPlayer;

	CheckForWinner();

	// Push the move into the history vector, switch sides.
	mHistory.push_back(std::move(move));
	mCurrentPlayer = mCurrentPlayer == Player::X ? Player::O : Player::X;
}

void TicTacToeBoard::UndoLastMove() {
	if (mHistory.size() != 0) {
		auto temp = dynamic_cast<TicTacToeMove*>(mHistory.back().get());
		mBoard[temp->GetPosition().GetRow()][temp->GetPosition().GetCol()] = Player::EMPTY;

		mHistory.pop_back();
		mCurrentPlayer = (Player)(-(int)mCurrentPlayer);
	}
}

bool TicTacToeBoard::IsFinished() const {
	return mCurrentValue != 0 || mHistory.size() == mBoard.size() * mBoard[0].size();
}

int TicTacToeBoard::GetValue() const {
	return mCurrentValue;
}

int TicTacToeBoard::GetCurrentPlayer() const {
	return mCurrentPlayer == Player::X ? 1 : 2;
}

const vector<unique_ptr<GameMove>>& TicTacToeBoard::GetMoveHistory() const {
	return mHistory;
}
