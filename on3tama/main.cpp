import on3tama;
import std;



void singleSearch() {
	Game game(
		&CARDS_PERFT,
		Board::create(0, { 0b00000'00000'00000'01110'00000, 0b00000'01110'00000'00000'00000 }, { 0b00000'00000'00000'00100'00000, 0b00000'00100'00000'00000'00000 })
	);

	game.board.print(*game.cards, 0);
	SearchResult result = game.searchTime({ .depth = 5 });
	result.board.print(*game.cards, 1);
}



auto main() -> int {
	auto b = STARTING_BOARD;

	return 0;
}
