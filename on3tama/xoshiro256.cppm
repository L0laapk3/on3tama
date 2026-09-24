export module xoshiro256;
import std;
import types;

// https://prng.di.unimi.it/xoshiro256plusplus.c
export struct Xoshiro256 {
	std::array<U64, 4> s;

	constexpr U64 next(void) {
		const U64 result = std::rotl(s[0] + s[3], 23) + s[0];

		const U64 t = s[1] << 17;

		s[2] ^= s[0];
		s[3] ^= s[1];
		s[1] ^= s[2];
		s[0] ^= s[3];

		s[2] ^= t;

		s[3] = std::rotl(s[3], 45);
		return result;
	}
};