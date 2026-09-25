export module on3tama:board;
import std;
import :types;
import :score;
import :card;



export constexpr auto MAX_MOVES = 2 * 5 * 4; // 2 card choices, 5 piece choices, 4 max targets in each card

export struct Game;
export struct RootResult;
export struct Board {
    std::array<U32, 2> p;
    std::array<U32, 2> k;
	U8 cardI;
	U64 zobrist;

	template <bool player, typename Callable>
	auto movegen(const CardsInfo& cards, Callable&& cb) const -> void;

	template<bool player, bool root = false, bool quiescence = false>
	std::conditional_t<root, RootResult, Score> search(Game& game, Score alpha, Score beta, Depth depthLeft);

	static constexpr std::array<U32, 2> TEMPLE = { 22, 2 };

	template <bool player>
	static U32 isKingAttackedBy(const MoveBoardList& moveList, U32 bbk, U32 bbp);
	template <bool player>
	U32 isKingAttacked(const MoveBoardList& moveList, U32 bbk) const;
	template <bool player>
	bool isTempleKingInRange(const MoveBoardList& moveList) const;
	template <bool player>
	bool isTempleFree() const;

	template <bool player>
	bool isTempleWinInOne(const MoveBoardList& moveList) const;
	template <bool player>
	U32 isTakeWinInOne(const MoveBoardList& moveList) const;
	template <bool player>
	bool isWinInOne(const MoveBoardList& moveList) const;

	template <bool player>
	void doWinInOne(const MoveBoardList& moveList);

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
