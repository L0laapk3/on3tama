export module moveGen;
import std;
import types;
import card;
import board;
import game;




template <bool player, typename Callable>
void movegen(Game& game, const Board& b, Callable&& cb) {

	const auto& moveList = game.cards->moveBoards[CARDS_HAND[player][b.cardI]];



	U32 sourceBits = b.p[player];
	for (int i = 0; i < 5; i++) {
		U32 sourcePiece = sourceBits & -sourceBits;
		sourceBits &= sourceBits - 1;
		int fromBit = std::countr_zero(sourcePiece);
		auto& landBitCards = moveList[fromBit].flip[player].cards;
		U32 landBits = landBitCards[0] | landBitCards[1];

	}
}