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

#include "player.hpp"

/*
	Initialisiere den Spieler.
*/
Player::Player() : hand(std::make_unique<Cards>()) { };

/*
	Setze Karten in die Spielerhand von einem Kartenstrukt.

	const std::vector<CardStruct> &cards: Die Karten.
*/
void Player::ImportCards(const std::vector<CardStruct> &cards) { this->hand->ImportCards(cards); };

/*
	Füge eine Karte hinzu.

	std::unique_ptr<Deck> &cardDeck: Das Karten-Deck.
*/
void Player::AddCard(std::unique_ptr<Deck> &cardDeck) { this->hand->AddCard(cardDeck); };

/*
	Entferne eine Karte von der Hand.

	uint8_t index: Der Karten-Index.
*/
void Player::RemoveCard(uint8_t index) { this->hand->RemoveCard(index); };

/*
	Wiedergebe, ob die Karte gespielt werden kann.

	uint8_t index: Der Karten-Index.
	const std::unique_ptr<Table> &table: Eine Referenz zum Tischkarten Zeiger.
*/
bool Player::Playable(uint8_t index, const std::unique_ptr<Table> &table) {
	if (!table) return false;

	return this->hand->Playable(index, table);
}

/*
	Wiedergebe den Kartentyp einer Karte von der Hand.

	uint8_t index: Der Karten-Index.
*/
CardType Player::GetType(uint8_t index) const { return this->hand->GetType(index); };

/*
	Wiedergebe die Kartenfarbe einer Karte von der Hand.

	uint8_t index: Der Karten-Index.
*/
CardColor Player::GetColor(uint8_t index) const { return this->hand->GetColor(index); };

/*
	Wiedergebe eine Karte von der Hand.

	uint8_t index: Der Karten-Index.
*/
CardStruct Player::GetCard(uint8_t index) const { return this->hand->GetCard(index); };

/*
	Wiedergebe die Anzahl der Karten von der Hand.
*/
uint8_t Player::GetHandSize() const { return this->hand->GetHandSize(); };