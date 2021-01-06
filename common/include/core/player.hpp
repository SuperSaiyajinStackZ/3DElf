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

#ifndef _3DELF_PLAYER_HPP
#define _3DELF_PLAYER_HPP

#include "cards.hpp"
#include "deck.hpp"
#include "coreHelper.hpp"
#include <vector>

class Player {
protected:
	std::unique_ptr<Cards> hand; // Die Spielerhand.
public:
	Player() : hand(std::make_unique<Cards>()) { };
	void ImportCards(const std::vector<CardStruct> &cards);

	void AddCard(std::unique_ptr<Deck> &cardDeck);
	void RemoveCard(uint8_t index);
	bool Playable(uint8_t index, const std::unique_ptr<Table> &table);

	CardType GetType(uint8_t index) const;
	CardColor GetColor(uint8_t index) const;
	CardStruct GetCard(uint8_t index) const;

	uint8_t GetHandSize() const;
};

#endif