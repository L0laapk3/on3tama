export module on3tama:boardSearch;
import std;
import :types;
import :score;
import :card;
import :board;
import :game;



template<bool player, bool root, bool quiescence>
auto Board::search(Game& game, Score alpha, Score beta, Depth depthLeft) -> std::conditional_t<root, RootResult, Score> {

	const auto& moveList = game.cards->moveBoards[CARDS_HAND[player][cardI]];

	if (isWinInOne<player>(moveList)) {
		Board board = *this;
		if (root) {
			board.doWinInOne<player>(moveList);
			board.assertValid(*game.cards, !player, true);
		}
		return RootResult{ SCORE::WIN, board, true, true };
	}

	if constexpr (!root && quiescence) {
		Score standing_pat = evaluate<player>();
		if (standing_pat >= beta)
			return beta;
		if (standing_pat > alpha)
			alpha = standing_pat;
	}

	std::array<Move, 40> moves{};



	if constexpr (root)
		return RootResult{};
	else
		return {};
}