export module on3tama:game;
import std;
import :types;
import :card;
import :board;
import :score;



export struct SearchStopCriteria {
	S64 time    = 1000LL * 60 * 24 * 365;
	Depth depth = DEPTH_MAX;
};

export struct SearchPersistent {
	Score alpha = -MUL_PIECE_ADVANTAGE / 10;
	Score beta  =  MUL_PIECE_ADVANTAGE / 10;
	Score score = 0;
	Depth depth = 0;
	bool searchWin = false;
};

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
	bool player = 0;
	bool ended = false;


private:
	auto search(Depth depth, Score alpha = SCORE::LOSS, Score beta = SCORE::WIN, bool print = true) -> SearchResult;
public:
	auto searchTime(SearchStopCriteria stop, SearchPersistent& persistent) -> SearchTimeResult;
	auto searchTime(SearchStopCriteria stop) -> SearchTimeResult;
};
