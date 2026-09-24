#include <iostream>
import board;
import std;
import types;
import xoshiro256;


auto main() -> int {
	// auto b = STARTING_BOARD;

	Xoshiro256 rng{{ 0x0123456789abcdef, 0xfedcba9876543210, 0xdeadbeefcafebabe, 0x1337c0def00dface }};

	constexpr U64 SIZE = 1ULL << 30;
	auto thing = std::make_unique<std::array<U64, SIZE>>();
	auto& shit = *thing;
	for (U64 i = 0; i < SIZE; i++) {
		shit[i] = i;
	}

	for (U64 i = SIZE - 1; i > 0; i--) {
		U64 j   = rng.next() % (i + 1);
		std::swap(shit[i], shit[j]);
	}

	std::cout << "Done alloc of size " << sizeof(U64) * SIZE / 1E9 << "GB" << std::endl;
	U64 out = 0;
	U64 kak = 0;

	auto start = std::chrono::high_resolution_clock::now();


	U64 REPEAT = 1E8;
	constexpr U64 PARALLEL = 20;
	std::array<U64, PARALLEL> outArr;
	for (U64 i = 0; i < PARALLEL; i++) {
		outArr[i] = rng.next() % SIZE;
	}

	for (U64 l = 0; l < REPEAT; l++) {
		for (U64 i = 0; i < PARALLEL; i++) {
			outArr[i] = shit[outArr[i]];
		}
	}

	auto end = std::chrono::high_resolution_clock::now();
	std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
	for (U64 i = 0; i < PARALLEL; i++) {
		std::cout << " out: " << outArr[i];
	}

	return 0;
}
