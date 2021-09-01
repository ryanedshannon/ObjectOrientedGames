#pragma once
#include "GameMove.h"
#include "BoardPosition.h"
#include "BoardDirection.h"

class TicTacToeMove : public GameMove {
private:
	BoardPosition mPosition;

	friend class TicTacToeBoard;
public:
	TicTacToeMove(BoardPosition p) : mPosition(p) {}

	inline BoardPosition GetPosition() const { return mPosition; }

	inline bool IsPass() const { return mPosition.GetCol() == -1 && mPosition.GetRow() == -1; }

	virtual operator std::string() const override;
	virtual bool operator==(const GameMove & rhs) const override;
};

