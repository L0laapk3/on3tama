module;
#include <bit>
export module moveGen;
import std;
import types;
import card;
import board;
import game;




template <bool player, typename Callable>
void movegen(const Board& b, Game& game, Callable&& cb) {

	const auto& moveList = game.cards->moveBoards[CARDS_HAND[player][b.cardI]];


	for (int cardI = 0; cardI < 2; cardI++) {

		U32 sourceBits = b.p[player];
		for (int i = 0; i < 5; i++) {
			U32 sourcePiece = sourceBits & -sourceBits;
			int fromBit = std::countr_zero(sourceBits);
			sourceBits &= sourceBits - 1;
			U32 landBits = moveList[fromBit].flip[player].cards[cardI];
			landBits &= ~b.p[player];


			// b.p[player] ^= sourcePiece;
			U32 sourceKing = sourcePiece & b.k[player];
			// b.k[player] ^= sourceKing;
			U32 kingMask = sourceKing ? ~0 : 0;

			bool cont = true;
			for (int i = 0; i < 4; i++) {
				if (!landBits || !cont) break;
				U32 landPiece = landBits & -landBits;
				U32 toBitFull = std::countr_zero(landBits);
				landBits &= landBits - 1;


			}

		}

	}
}