export module on3tama:gameSearch;
import std;
import :types;
import :card;
import :board;
import :boardSearch;
import :score;
import :game;



template <bool player>
auto Game::search(Depth depth, Score alpha, Score beta) -> SearchResult {
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