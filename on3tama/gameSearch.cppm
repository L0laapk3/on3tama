export module on3tama:gameSearch;
import std;
import :types;
import :card;
import :score;
import :board;
import :boardWin;
import :boardSearch;
import :game;



auto Game::search(Depth depth, Score alpha, Score beta, bool print) -> SearchResult {
	SearchResult result;
	depth++;

	auto start = std::chrono::high_resolution_clock::now();
	if (player)
		(RootResult&)result = board.search<1, true>(*this, alpha, beta, depth);
	else
		(RootResult&)result = board.search<0, true>(*this, alpha, beta, depth);
	auto end = std::chrono::high_resolution_clock::now();

	return result;
}

auto Game::searchTime(SearchStopCriteria stop, SearchPersistent& persistent) -> SearchTimeResult {
	SearchTimeResult result;
	(SearchResult&)result = search(persistent.depth, persistent.alpha, persistent.beta, false);
	return result;
}
auto Game::searchTime(SearchStopCriteria stop) -> SearchTimeResult {
	SearchPersistent persistent;
	return searchTime(stop, persistent);
}
