export module on3tama:board;
import std;
import :types;
import :score;
import :card;



export constexpr auto MAX_MOVES = 2 * 5 * 4; // 2 card choices, 5 piece choices, 4 max targets in each card

export struct Game;
export struct RootResult;
export struct 	Board {
    std::array<U32, 2> p;
    std::array<U32, 2> k;
	U8 cardI;
	U64 zobrist;

	template <bool player, typename Callable>
	auto movegen(const CardsInfo& cards, Callable&& cb) const -> void;


	template<bool player, bool root = false, bool quiescence = false>
	auto search(Game& game, Score alpha, Score beta, Depth depthLeft) -> std::conditional_t<root, RootResult, Score>;


	static constexpr std::array<U32, 2> TEMPLE = { 22, 2 };

	template <bool player>
	static auto isKingAttackedBy(const MoveBoardList& moveList, U32 bbk, U32 bbp) -> U32;
	template <bool player>
	auto isKingAttacked(const MoveBoardList& moveList, U32 bbk) const -> U32;
	template <bool player>
	auto isTempleKingInRange(const MoveBoardList& moveList) const -> bool;
	template <bool player>
	auto isTempleFree() const -> bool;

	template <bool player>
	auto isTempleWinInOne(const MoveBoardList& moveList) const -> bool;
	template <bool player>
	auto isTakeWinInOne(const MoveBoardList& moveList) const -> U32;
	template <bool player>
	auto isWinInOne(const MoveBoardList& moveList) const -> bool;

	template <bool player>
	auto doWinInOne(const MoveBoardList& moveList) -> void;


	static auto create(bool player = 0, std::array<U32, 2> p = { 0b00000'00000'00000'00000'11111, 0b11111'00000'00000'00000'00000 }, std::array<U32, 2> k = { 0b00000'00000'00000'00000'00100, 0b00100'00000'00000'00000'00000 }) -> Board;
private:
	static auto toString(const CardsInfo& cards, const std::vector<Board>& boards, std::vector<char> turnIndicators) -> std::string;
public:
	static auto toString(const CardsInfo& cards, const std::vector<Board>& boards, std::vector<bool> players) -> std::string;
	static auto toString(const CardsInfo& cards, const std::vector<Board>& boards) -> std::string;
	auto toString(const CardsInfo& cards, bool player) const -> std::string;
	auto toString(const CardsInfo& cards) const -> std::string;
	auto print(const CardsInfo& cards) const -> void;
	auto print(const CardsInfo& cards, bool player) const -> void;
	auto invert(bool player) const -> Board;
	auto checkValid(const CardsInfo& cards, bool player, bool isWon = false) const -> void;
	auto assertValid(const CardsInfo& cards, bool player, bool isWon = false) const -> void;

};

export constexpr Board STARTING_BOARD{
	{0b1111, 0b11111 << 20},
	{0b0100, 0b00100 << 20},
	0,
	0
};

export struct RootResult {
	Score score;
	Board board;
	bool foundMove = true;
	bool winningMove = false;
	operator Score() const { return score; };
};



export enum Bound : U8 {
	NONE = 0,
	LOWER = 1,
	UPPER = 2,
	EXACT = LOWER | UPPER,
};
