export module on3tama:gameSearch;
import std;
import :types;
import :card;
import :board;
import :boardSearch;
import :score;
import :game;



template <bool player>
auto Game::search(U8 depth, U64 alpha, U64 beta) -> SearchResult {
	SearchResult result;


	auto start = std::chrono::high_resolution_clock::now();
	if (player)
		(RootResult&)result = board.search<1, true>(*this, alpha, beta, depth + 1);
	else
		(RootResult&)result = board.search<0, true>(*this, alpha, beta, depth + 1);
	auto end = std::chrono::high_resolution_clock::now();

	return result;
}