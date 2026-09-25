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
	Board board;


	template <bool player>
	auto search(Depth depth, Score alpha, Score beta) -> SearchResult;
};
