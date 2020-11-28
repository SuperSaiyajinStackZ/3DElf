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

#include "cards.hpp"

/*
	Karten Klasse konstruktor.
*/
Cards::Cards() { }

/*
	Setze Karten von einem Kartenstrukt.

	const std::vector<CardStruct> &cards: Die Karten.
*/
void Cards::ImportCards(const std::vector<CardStruct> &cards) { this->hand = cards; }

/*
	Füge eine Karte der Hand hinzu vom Kartendeck.

	std::unique_ptr<Deck> &cardDeck: Das Karten-Deck.
*/
void Cards::AddCard(std::unique_ptr<Deck> &cardDeck) {
	if (!cardDeck) return; // Karten-Deck ist ein nullpointer und somit nicht gültig.

	if (cardDeck->GetDeckSize() > 0) {
		this->hand.push_back({ cardDeck->GetCard() }); // Füge eine Karte vom Karten-Deck hinzu.
	}
}

/*
	Entferne eine Karte von der Hand.

	uint8_t index: Der Karten-Index.
*/
void Cards::RemoveCard(uint8_t index) {
	if (index < this->GetHandSize()) this->hand.erase(this->hand.begin() + index);
}

/*
	Wiedergebe den Kartentyp.

	uint8_t index: Der Karten-Index.
*/
CardType Cards::GetType(uint8_t index) const {
	if (index < this->GetHandSize()) return this->hand[index].CT;

	return CardType::NUMBER_EMPTY;
}

/*
	Wiedergebe die Kartenfarbe.

	uint8_t index: Der Karten-Index.
*/
CardColor Cards::GetColor(uint8_t index) const {
	if (index < this->GetHandSize()) return this->hand[index].CC;

	return CardColor::COLOR_EMPTY;
}

/*
	Wiedergebe die Karte.

	uint8_t index: Der Karten-Index.
*/
CardStruct Cards::GetCard(uint8_t index) const {
	if (index < this->GetHandSize()) return this->hand[index];

	return { CardType::NUMBER_EMPTY, CardColor::COLOR_EMPTY };
}

/*
	Wiedergebe die anzahl der Karten von der Hand.
*/
uint8_t Cards::GetHandSize() const { return (uint8_t)this->hand.size(); }

/*
	Wiedergebe, ob die Karte gespielt werden kann.

	uint8_t index: Der Karten-Index.
	const std::unique_ptr<Table> &table: Eine Referenz zum Tischkarten Zeiger.
*/
bool Cards::Playable(uint8_t index, const std::unique_ptr<Table> &table) {
	if (!table) return false;

	const bool isUpper = (uint8_t)this->GetType(index) >= 11 ? true : false; // 12 + ist die obere Karte.
	return table->CanPlay(this->GetColor(index), isUpper, this->GetType(index));

	return false;
}