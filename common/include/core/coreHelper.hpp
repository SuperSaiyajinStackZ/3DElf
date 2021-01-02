/*
	Diese Datei ist Teil von 3DElf.
	Copyright (C) 2020-2021 bei SuperSaiyajinStackZ.

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

	Additional Terms 7.b and 7.c of GPLv3 apply to this file:
		* Requiring preservation of specified reasonable legal notices or
		  author attributions in that material or in the Appropriate Legal
		  Notices displayed by works containing it.
		* Prohibiting misrepresentation of the origin of that material,
		  or requiring that modified versions of such material be marked in
		  reasonable ways as different from the original version.
*/

#ifndef _3DELF_CORE_HELPER_HPP
#define _3DELF_CORE_HELPER_HPP

#include <memory>
#include <string>
#include <random>

inline std::mt19937 randomGen; // Zufalls-Generator.

/*
	Bei 2 Spielern verbleiben 40 Karten im Karten-Deck.
	Bei 3 Spielern verbleiben 20 Karten im Karten-Deck.
	Bei 4 Spielern verbleiben 15 Karten im Karten-Deck.
	Bei 5 Spielern verbleiben 12 Karten im Karten-Deck.
	Bei 6 Spielern verbleiben 10 Karten im Karten-Deck.
*/

/* Kartentypen Enum Klasse. */
enum class CardType : uint8_t {
	NUMBER_EMPTY,
	NUMBER_1,
	NUMBER_2,
	NUMBER_3,
	NUMBER_4,
	NUMBER_5,
	NUMBER_6,
	NUMBER_7,
	NUMBER_8,
	NUMBER_9,
	NUMBER_10,
	NUMBER_11,
	NUMBER_12,
	NUMBER_13,
	NUMBER_14,
	NUMBER_15,
	NUMBER_16,
	NUMBER_17,
	NUMBER_18,
	NUMBER_19,
	NUMBER_20
};

/* Kartenfarbe Enum Klasse. */
enum class CardColor : uint8_t {
	COLOR_EMPTY,
	COLOR_1,
	COLOR_2,
	COLOR_3,
	COLOR_4
};

/*
	Eine Karte besteht aus einem Kartentyp, und einer Kartenfarbe.. somit CardType + CardColor.
	Beide sind jeweils ein uint8_t, was einen byte entspricht.
	Beides zusammen entspricht einem uint16_t / 2 byte.
*/
struct CardStruct {
	CardType CT;
	CardColor CC;
};

namespace CoreHelper {
	void GenerateSeed();

	uint8_t GetStartupCards(uint8_t players);

	CardType Uint8ToCardType(uint8_t card);
	uint16_t GetCardBytes(CardStruct CS);
	CardStruct GetCardStruct(const std::unique_ptr<uint8_t[]> &rawData, uint32_t offset);
};

#endif