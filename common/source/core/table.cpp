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

#include "table.hpp"

/*
	Initialisiere die Tisch-Karten.
*/
Table::Table() {
	for (uint8_t i = 0; i < 4; i++) {
		this->TableCards[i] = std::make_pair(CardType::NUMBER_EMPTY, CardType::NUMBER_EMPTY);
	}
}

/*
	Wiedergebe die benötigten Karten als einen std::pair aus 2 Kartentypen.
	Dies wiedergibt die untere (first) und obere (second) Karte.

	CardColor CLR: Die Kartenfarbe.
*/
std::pair<CardType, CardType> Table::GetPlayCard(CardColor CLR) const {
	std::pair<CardType, CardType> temp = { CardType::NUMBER_EMPTY, CardType::NUMBER_EMPTY };


	if (this->TableCards[(uint8_t)CLR - 1].first == CardType::NUMBER_EMPTY &&
		this->TableCards[(uint8_t)CLR - 1].second == CardType::NUMBER_EMPTY) {
			return { CardType::NUMBER_11, CardType::NUMBER_11 };
		}

	/* 1 wäre die erste Karte, somit verhindere den folgenden Code. */
	if (this->TableCards[(uint8_t)CLR - 1].first != CardType::NUMBER_1) {
		temp.first = CoreHelper::Uint8ToCardType((uint8_t)this->TableCards[(uint8_t)CLR - 1].first - 1);

	} else {
		temp.first = CardType::NUMBER_1; // Setze es zu 1.
	}

	/* 20 wäre die letzte Karte, somit verhindere den folgenden Code. */
	if (this->TableCards[(uint8_t)CLR - 1].second != CardType::NUMBER_20) {
		temp.second = CoreHelper::Uint8ToCardType((uint8_t)this->TableCards[(uint8_t)CLR - 1].second + 1);

	} else {
		temp.second = CardType::NUMBER_20; // Setze es zu 20.
	}

	return temp;
}

/*
	Wiedergebe, ob unsere aktuelle Karte gespielt werden kann.

	CardColor CLR: Die Kartenfarbe.
	bool upper: Ob auf die obere oder untere Karte gelegt werden soll.
	CardType CT: Der Kartentyp.
*/
bool Table::CanPlay(CardColor CLR, bool upper, CardType CT) const {
	if (CT == CardType::NUMBER_EMPTY) return false;

	if (upper) {
		if (this->TableCards[(uint8_t)CLR - 1].second == CardType::NUMBER_20) return false;

		if (CT == this->GetPlayCard(CLR).second) return true;

	} else {
		if (this->TableCards[(uint8_t)CLR - 1].first == CardType::NUMBER_1) return false;

		if (CT == this->GetPlayCard(CLR).first) return true;
	}

	return false;
}

/*
	Setze eine Karte.

	CardColor CLR: Die Kartenfarbe.
	bool upper: Ob auf die obere oder untere Karte gelegt werden soll.
	CardType CT: Der Kartentyp.
*/
void Table::SetCard(CardColor CLR, bool upper, CardType CT) {
	if (this->CanPlay(CLR, upper, CT)) {
		/* For 11.. set it to both. */
		if (CT == CardType::NUMBER_11) {
			this->TableCards[(uint8_t)CLR - 1].first = CT;
			this->TableCards[(uint8_t)CLR - 1].second = CT;

		} else {
			if (upper) this->TableCards[(uint8_t)CLR - 1].second = CT;
			else this->TableCards[(uint8_t)CLR - 1].first = CT;
		}
	}
}

/*
	Wiedergebe die aktuelle obere und untere Karte als einen std::pair.
	Die untere ist (first) und die obere ist (second).

	CardColor CLR: Die Kartenfarbe, welche wiedergeben werden soll.
*/
std::pair<CardType, CardType> Table::GetCurrent(CardColor CLR) const { return this->TableCards[(uint8_t)CLR - 1]; };

/*
	Importiere Die Kartentypen vom Buffer.

	CardColor CLR: Kartenfarbe.
	const std::pair<CardType, CardType> &CT = Kartentypen.
*/
void Table::ImportCardTypes(CardColor CLR, const std::pair<CardType, CardType> &CT) { this->TableCards[(uint8_t)CLR - 1] = CT; };