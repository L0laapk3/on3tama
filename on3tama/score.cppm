export module on3tama:score;
import std;
import :types;



export using Depth = S16;

export constexpr Depth DEPTH_MAX = 512;

export using Score = int;
export enum SCORE : int {
	MAX  = std::numeric_limits<int>::max() - DEPTH_MAX * 2,
	WIN  = MAX - DEPTH_MAX * 2,
	DRAW = 0,
	LOSS = -WIN,
	MIN  = -MAX,
};

export constexpr Score MUL_POSITION_ADVANTAGE = 1024;
export constexpr Score MUL_PIECE_ADVANTAGE    = 1024 * MUL_POSITION_ADVANTAGE;



export struct ScoreParsed {
	Score outcome; // win, lose, 0
	Depth outcomeDistance;
	Score eval; // score of the position
};
// export ScoreParsed parseScore(Score score);
// export std::string scoreToString(Score score, bool player = 0);
// export std::string scoreToString(ScoreParsed score, bool player = 0);