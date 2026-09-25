module;
#include <cassert>
export module on3tama:boardUtil;
import std;
import :types;
import :board;


auto Board::checkValid(const CardsInfo& cards, bool player, bool isWon) const -> void {
	auto test = [&](bool result) {
		if (!result) {
			std::cout << "Invalid board!\n";
			print(cards);
			assert(false);
			std::exit(1);
		}
	};

	test((p[0] & ((1 << 25) - 1)) == p[0]);
	test((p[1] & ((1 << 25) - 1)) == p[1]);
	test(std::popcount(p[0]) <= 5);
	test(std::popcount(p[1]) <= 5);
	if (!isWon) {
		test(1 <= std::popcount(p[0]));
		test(1 <= std::popcount(p[1]));
		test(std::popcount(k[0]) == 1);
		test(std::popcount(k[1]) == 1);
	} else {
		test(std::popcount(k[0]) <= 1);
		test(std::popcount(k[1]) <= 1);
	}
	test(k[0] == (p[0] & k[0]));
	test(k[1] == (p[1] & k[1]));
	test((p[0] & p[1]) == 0);
	test(cardI < 30);

	Board tmpBoard = *this;
	// tmpBoard.recalculateHash(player);
	// test(tmpBoard.hash == hash);
}

auto Board::assertValid(const CardsInfo& cards, bool player, bool isWon) const -> void {
#ifndef NDEBUG
	checkValid(cards, player, isWon);
#endif
}

export auto cardsShortName(Card card, int length) -> std::string {
	std::string res = "";
	for (U32 i = 0; i < length; i++)
		res += card.name.size() > i ? card.name[i] : ' ';
	return res;
}

auto Board::toString(const CardsInfo& cards, const std::vector<Board>& boards, std::vector<char> turnIndicators) -> std::string {
	std::string outString{};
	constexpr int BOARDS_PER_LINE = 8;

	for (int i = 0; i < boards.size(); i += BOARDS_PER_LINE) {
		outString += "\n";
		for (int j = i; j < i + BOARDS_PER_LINE && j < boards.size(); j++) {
			auto perm = CARDS_PERMUTATIONS[boards[j].cardI];
			outString += cardsShortName(cards.cards[perm.playerCards[0][0]], 4) + " " + cardsShortName(cards.cards[perm.playerCards[0][1]], 4) + "  ";
		}
		outString += "\n";

		for (int r = 0; r < 5; r++) {
			for (int j = i; j < i + BOARDS_PER_LINE && j < boards.size(); j++) {
				auto& board = boards[j];
				auto perm = CARDS_PERMUTATIONS[board.cardI];
				outString += std::string(1, r == 4 ? turnIndicators[j] : ' ') + "|";

				for (int c = 5; c --> 0;) {
					const int mask = 1 << (5 * r + c);
					if (board.p[0] & mask) {
						if ((board.p[1] | board.k[1]) & mask)    outString += "?"; // invalid
						else if (board.k[0] & mask)              outString += "X";
						else                                     outString += "+";
					} else if (board.p[1] & mask) {
						if (board.k[1] & mask)                   outString += "0";
						else                                     outString += "o";
					} else if ((board.k[0] | board.k[1]) & mask) outString += "!"; // invalid
					else                                         outString += ".";
				}
				outString += "|" + std::string(1, cardsShortName(cards.cards[perm.sideCard], 5)[r]) + "  ";
			}
			outString += "\n";
		}
		for (int j = i; j < i + BOARDS_PER_LINE && j < boards.size(); j++) {
			auto perm = CARDS_PERMUTATIONS[boards[j].cardI];
			outString += cardsShortName(cards.cards[perm.playerCards[1][0]], 4) + " " + cardsShortName(cards.cards[perm.playerCards[1][1]], 4) + "  ";
		}
		outString += "\n";
	}
	outString += "\n";
	return outString;
}
auto Board::toString(const CardsInfo& cards, const std::vector<Board>& boards, std::vector<bool> players) -> std::string {
	std::vector<char> turnIndicators(players.size());
	for (int i = 0; i < players.size(); i++)
		turnIndicators[i] = players[i] ? '0' : 'X';
	return toString(cards, boards, turnIndicators);
}
auto Board::toString(const CardsInfo& cards, const std::vector<Board>& boards) -> std::string {
	std::vector<char> turnIndicators(boards.size(), ' ');
	return toString(cards, boards, turnIndicators);
}
auto Board::toString(const CardsInfo& cards, bool player) const -> std::string {
	return Board::toString(cards, { *this }, std::vector<bool>{ player });
};
auto Board::toString(const CardsInfo& cards) const -> std::string {
	return Board::toString(cards, { *this });
};
auto Board::print(const CardsInfo& cards) const -> void {
	auto str = toString(cards);
	std::cout << str << std::flush;
};
auto Board::print(const CardsInfo& cards, bool player) const -> void {
	auto str = toString(cards, player);
	std::cout << str << std::flush;
};