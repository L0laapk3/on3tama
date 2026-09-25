export module on3tama:boardMove;
import std;
import :types;
import :card;
import :board;




export struct Move {
	U32 source;
	U32 land;
	bool cardI;
};

// export struct Move {
// 	union {
// 		U16 full;
// 		struct {
// 			union {
// 				U8 fromBitFull;
// 				struct {
// 					U8 fromBit  : 6;
// 					Bound bound : 2;
// 				};
// 			};
// 			union {
// 				U8 toBitFull;
// 				struct {
// 					U8 toBit      : 6;
// 					U8 secondCard : 1;
// 				};
// 			};
// 		};
// 	};
// };

template <bool player, typename Callable>
auto Board::movegen(const CardsInfo& cards, Callable&& cb) const -> void {
	const auto& moveList = cards.moveBoards[CARDS_HAND[player][cardI]];

	for (int cardI_ = 0; cardI_ < 2; cardI_++) {
		const bool cardI = static_cast<bool>(cardI_);
		U32 sourceBits = p[player];
		for (int i = 0; i < 5; i++) {
			U32 sourcePiece = sourceBits & -sourceBits;
			sourceBits &= sourceBits - 1;
			int fromBit = std::countr_zero(sourcePiece);
			U32 landBits = moveList[fromBit].flip[player].cards[cardI];
			for (int j = 0; j < 5; j++) {
				U32 landPiece = landBits & -landBits;
				landBits &= landBits - 1;
				cb(Move{sourcePiece, landPiece, cardI});
			}
		}
	}
}