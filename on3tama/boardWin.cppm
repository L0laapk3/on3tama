module;
#include <cassert>
export module on3tama:boardWin;
import std;
import :types;
import :score;
import :card;
import :board;



template <bool player>
inline auto Board::isTempleKingInRange(const MoveBoardList& moveList) const -> bool {
	// player king can move to temple
	return (moveList[TEMPLE[player]].flip[!player].cards[0] | moveList[TEMPLE[player]].flip[!player].cards[1]) & k[player];
}


template <bool player>
inline auto Board::isTempleFree() const -> bool {
	// no player piece is blocking the temple.
	return !(p[player] & (1 << TEMPLE[player]));
}


template <bool player>
inline auto Board::isTempleWinInOne(const MoveBoardList& moveList) const -> bool {
	return isTempleKingInRange<player>(moveList) && isTempleFree<player>();
}


template <bool player>
inline auto Board::isKingAttackedBy(const MoveBoardList& moveList, U32 bbk, U32 bbp) -> U32 {
	U32 pk = std::countr_zero(bbk);
	return (moveList[pk].flip[!player].cards[0] | moveList[pk].flip[!player].cards[1]) & bbp;
}

// is !player king safe?
// is player attacking !players king?
template <bool player>
inline auto Board::isKingAttacked(const MoveBoardList& moveList, U32 bbk) const -> U32 {
	return isKingAttackedBy<player>(moveList, bbk, p[player]);
}



template <bool player>
inline auto Board::isTakeWinInOne(const MoveBoardList& moveList) const -> U32 {
	return isKingAttacked<player>(moveList, k[!player]);
}

template <bool player>
inline auto Board::isWinInOne(const MoveBoardList& moveList) const -> bool {
	if (isTempleWinInOne<player>(moveList))
		return true;
	return isTakeWinInOne<player>(moveList);
}



template <bool player>
inline auto Board::doWinInOne(const MoveBoardList& moveList) -> void {
	assert(isWinInOne<player>(moveList));

	bool secondCard;
	if (isTakeWinInOne<player>(moveList)) {
		U32 attacker = isKingAttacked<player>(moveList, k[!player]);
		attacker &= -attacker; // select first piece that can kill king
		secondCard = moveList[std::countr_zero(k[!player])].flip[1].cards[1] & attacker;
		p[player] ^= attacker ^ k[!player];
		if (attacker & k[player])
			k[player] = k[!player];
		p[!player] ^= k[!player];
		k[!player] = 0;
	} else {
		secondCard = moveList[TEMPLE[player]].flip[1].cards[1] & k[player];
		p[player] ^= k[player] ^ (1 << TEMPLE[player]);
		k[player] = 1 << TEMPLE[player];
		p[!player] &= ~k[player];
	}
	cardI = CARDS_SWAP[cardI][player][secondCard];
}