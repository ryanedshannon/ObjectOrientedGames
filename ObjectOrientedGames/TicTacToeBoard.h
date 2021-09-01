#pragma once
#include "GameBoard.h"
#include <array>
#include <memory>
#include <vector>
#include "BoardPosition.h"

class TicTacToeBoard : public GameBoard {
private:
	static const int BOARD_SIZE = 3;
	enum class Player { EMPTY = 0, X = 1, O = -1 };
	std::array<std::array<Player, BOARD_SIZE>, BOARD_SIZE> mBoard;
	std::vector<std::unique_ptr<GameMove>> mHistory;
	
	Player mCurrentPlayer;
	int mCurrentValue;

	friend class TicTacToeView;

	void CheckForWinner();
	bool InBounds(BoardPosition p) { return p.InBounds(mBoard.size(), mBoard[0].size()); }

	inline Player GetPlayerAtPosition(BoardPosition position) const {
		return mBoard[position.GetRow()][position.GetCol()];
	}

public:
	TicTacToeBoard();

	// Inherited via GameBoard
	std::vector<std::unique_ptr<GameMove>> GetPossibleMoves() const override;
	void ApplyMove(std::unique_ptr<GameMove> move) override;
	void UndoLastMove() override;
	bool IsFinished() const override;
	int GetValue() const override;
	int GetCurrentPlayer() const override;
	const std::vector<std::unique_ptr<GameMove>>& GetMoveHistory() const override;
};

