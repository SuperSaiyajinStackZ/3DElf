/*
	Diese Datei ist Teil von 3DElf.
	Copyright (C) 2020 bei SuperSaiyajinStackZ.

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

#include "deck.hpp"
#include <algorithm>

/* Das Standard Kartendeck, mit 80 Karten. */
const std::vector<CardStruct> DefaultDeck = {
				/* Rote Karten. */
	{ CardType::NUMBER_1, CardColor::COLOR_RED },
	{ CardType::NUMBER_2, CardColor::COLOR_RED },
	{ CardType::NUMBER_3, CardColor::COLOR_RED },
	{ CardType::NUMBER_4, CardColor::COLOR_RED },
	{ CardType::NUMBER_5, CardColor::COLOR_RED },
	{ CardType::NUMBER_6, CardColor::COLOR_RED },
	{ CardType::NUMBER_7, CardColor::COLOR_RED },
	{ CardType::NUMBER_8, CardColor::COLOR_RED },
	{ CardType::NUMBER_9, CardColor::COLOR_RED },
	{ CardType::NUMBER_10, CardColor::COLOR_RED },
	{ CardType::NUMBER_11, CardColor::COLOR_RED },
	{ CardType::NUMBER_12, CardColor::COLOR_RED },
	{ CardType::NUMBER_13, CardColor::COLOR_RED },
	{ CardType::NUMBER_14, CardColor::COLOR_RED },
	{ CardType::NUMBER_15, CardColor::COLOR_RED },
	{ CardType::NUMBER_16, CardColor::COLOR_RED },
	{ CardType::NUMBER_17, CardColor::COLOR_RED },
	{ CardType::NUMBER_18, CardColor::COLOR_RED },
	{ CardType::NUMBER_19, CardColor::COLOR_RED },
	{ CardType::NUMBER_20, CardColor::COLOR_RED },

				/* Gelbe Karten. */
	{ CardType::NUMBER_1, CardColor::COLOR_YELLOW },
	{ CardType::NUMBER_2, CardColor::COLOR_YELLOW },
	{ CardType::NUMBER_3, CardColor::COLOR_YELLOW },
	{ CardType::NUMBER_4, CardColor::COLOR_YELLOW },
	{ CardType::NUMBER_5, CardColor::COLOR_YELLOW },
	{ CardType::NUMBER_6, CardColor::COLOR_YELLOW },
	{ CardType::NUMBER_7, CardColor::COLOR_YELLOW },
	{ CardType::NUMBER_8, CardColor::COLOR_YELLOW },
	{ CardType::NUMBER_9, CardColor::COLOR_YELLOW },
	{ CardType::NUMBER_10, CardColor::COLOR_YELLOW },
	{ CardType::NUMBER_11, CardColor::COLOR_YELLOW },
	{ CardType::NUMBER_12, CardColor::COLOR_YELLOW },
	{ CardType::NUMBER_13, CardColor::COLOR_YELLOW },
	{ CardType::NUMBER_14, CardColor::COLOR_YELLOW },
	{ CardType::NUMBER_15, CardColor::COLOR_YELLOW },
	{ CardType::NUMBER_16, CardColor::COLOR_YELLOW },
	{ CardType::NUMBER_17, CardColor::COLOR_YELLOW },
	{ CardType::NUMBER_18, CardColor::COLOR_YELLOW },
	{ CardType::NUMBER_19, CardColor::COLOR_YELLOW },
	{ CardType::NUMBER_20, CardColor::COLOR_YELLOW },

				/* Grüne Karten. */
	{ CardType::NUMBER_1, CardColor::COLOR_GREEN },
	{ CardType::NUMBER_2, CardColor::COLOR_GREEN },
	{ CardType::NUMBER_3, CardColor::COLOR_GREEN },
	{ CardType::NUMBER_4, CardColor::COLOR_GREEN },
	{ CardType::NUMBER_5, CardColor::COLOR_GREEN },
	{ CardType::NUMBER_6, CardColor::COLOR_GREEN },
	{ CardType::NUMBER_7, CardColor::COLOR_GREEN },
	{ CardType::NUMBER_8, CardColor::COLOR_GREEN },
	{ CardType::NUMBER_9, CardColor::COLOR_GREEN },
	{ CardType::NUMBER_10, CardColor::COLOR_GREEN },
	{ CardType::NUMBER_11, CardColor::COLOR_GREEN },
	{ CardType::NUMBER_12, CardColor::COLOR_GREEN },
	{ CardType::NUMBER_13, CardColor::COLOR_GREEN },
	{ CardType::NUMBER_14, CardColor::COLOR_GREEN },
	{ CardType::NUMBER_15, CardColor::COLOR_GREEN },
	{ CardType::NUMBER_16, CardColor::COLOR_GREEN },
	{ CardType::NUMBER_17, CardColor::COLOR_GREEN },
	{ CardType::NUMBER_18, CardColor::COLOR_GREEN },
	{ CardType::NUMBER_19, CardColor::COLOR_GREEN },
	{ CardType::NUMBER_20, CardColor::COLOR_GREEN },

				/* Blaue Karten. */
	{ CardType::NUMBER_1, CardColor::COLOR_BLUE },
	{ CardType::NUMBER_2, CardColor::COLOR_BLUE },
	{ CardType::NUMBER_3, CardColor::COLOR_BLUE },
	{ CardType::NUMBER_4, CardColor::COLOR_BLUE },
	{ CardType::NUMBER_5, CardColor::COLOR_BLUE },
	{ CardType::NUMBER_6, CardColor::COLOR_BLUE },
	{ CardType::NUMBER_7, CardColor::COLOR_BLUE },
	{ CardType::NUMBER_8, CardColor::COLOR_BLUE },
	{ CardType::NUMBER_9, CardColor::COLOR_BLUE },
	{ CardType::NUMBER_10, CardColor::COLOR_BLUE },
	{ CardType::NUMBER_11, CardColor::COLOR_BLUE },
	{ CardType::NUMBER_12, CardColor::COLOR_BLUE },
	{ CardType::NUMBER_13, CardColor::COLOR_BLUE },
	{ CardType::NUMBER_14, CardColor::COLOR_BLUE },
	{ CardType::NUMBER_15, CardColor::COLOR_BLUE },
	{ CardType::NUMBER_16, CardColor::COLOR_BLUE },
	{ CardType::NUMBER_17, CardColor::COLOR_BLUE },
	{ CardType::NUMBER_18, CardColor::COLOR_BLUE },
	{ CardType::NUMBER_19, CardColor::COLOR_BLUE },
	{ CardType::NUMBER_20, CardColor::COLOR_BLUE }
};

/*
	Konstruktor von der Deck klasse.
*/
Deck::Deck() { this->shuffle(); }

/*
	Initialisiere das Kartendeck mit dem Standard-Deck.
*/
void Deck::Initialize() { this->deck = DefaultDeck; }

/*
	Initialisiere und mixe das deck.
*/
void Deck::shuffle() {
	this->Initialize();
	std::shuffle(this->deck.begin(), this->deck.end(), std::default_random_engine(randomGen()));
}

/*
	Wiedergebe die letzte Karte vom Deck und entferne sie.
*/
CardStruct Deck::GetCard() {
	CardStruct CS = { CardType::NUMBER_EMPTY, CardColor::COLOR_EMPTY };

	if (this->GetDeckSize() > 0) {
		CS = this->deck[this->GetDeckSize() - 1];
		this->deck.pop_back(); // Entferne letzte Karte vom deck.
	}

	return CS;
}

/*
	Wiedergebe eine Karte vom Deck.

	uint8_t index: Der Karten-Index.
*/
CardStruct Deck::GetCardFromDeck(uint8_t index) const {
	if (this->GetDeckSize() > index) {
		return this->deck[index];
	}

	return { CardType::NUMBER_EMPTY, CardColor::COLOR_EMPTY };
}

/*
	Wiedergebe die Anzahl der Karten vom Deck.
*/
uint8_t Deck::GetDeckSize() const { return (uint8_t)this->deck.size(); }