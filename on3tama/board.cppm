export module board;
import std;
import types;
import card;
import game;



export constexpr auto MAX_MOVES = 2 * 5 * 4; // 2 card choices, 5 piece choices, 4 max targets in each card

export struct Board {
    std::array<U32, 2> p;
    std::array<U32, 2> k;
	U8 cardI;
	U64 zobrist;

	template <bool player, typename Callable>
	void movegen(Callable&& cb) const;
};

export constexpr Board STARTING_BOARD{
	{0b1111, 0b11111 << 20},
	{0b0100, 0b00100 << 20},
	0,
	0
};



export enum Bound : U8 {
	NONE = 0,
	LOWER = 1,
	UPPER = 2,
	EXACT = LOWER | UPPER,
};

export struct Move {
	union {
		U16 full;
		struct {
			union {
				U8 fromBitFull;
				struct {
					U8 fromBit  : 6;
					Bound bound : 2;
				};
			};
			union {
				U8 toBitFull;
				struct {
					U8 toBit      : 6;
					U8 secondCard : 1;
				};
			};
		};
	};
};
