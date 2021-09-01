#include "TicTacToeMove.h"
#include <string>
using namespace std;

TicTacToeMove::operator std::string() const {
	return mPosition;
}

bool TicTacToeMove::operator==(const GameMove & rhs) const {
	const TicTacToeMove &m = dynamic_cast<const TicTacToeMove&>(rhs);
	return mPosition == m.mPosition;
}


