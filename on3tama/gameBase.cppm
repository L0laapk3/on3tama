export module on3tama:game;
import std;
import :types;
import :card;
import :board;
import :score;



export struct SearchResult : public RootResult {
	S64 durationUs;
};
export struct SearchTimeResult : public SearchResult {
	Depth depth;
};


export struct Game {
public:

	const CardsInfo* cards;


	template <bool player>
	SearchResult search(const Board& board, U8 depth, U64 alpha, U64 beta);
};
