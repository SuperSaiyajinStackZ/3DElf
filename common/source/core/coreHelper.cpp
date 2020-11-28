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

#include "coreHelper.hpp"
#include <time.h>

bool hasSeeded = false;

/*
	Generiere einen Seed für den Zufallsgenerator.
*/
void CoreHelper::GenerateSeed() {
	if (!hasSeeded) {
		hasSeeded = true;
		randomGen.seed(time(NULL));
	}
}

/*
	Für 2 Spieler, 40 Karten verbleiben im Deck.
	Für 3 - 6 Spieler, 20 Karten verbleiben im Deck.
	Diese Funktion wiedergibt die anzahl der Karten, die ein Spieler am anfang des spieles zugeschrieben bekommt.

	uint8_t players: Die Spieleranzahl. (2 - 6 sind gültig).
*/
uint8_t CoreHelper::GetStartupCards(uint8_t players) {
	switch(players) {
		case 2:
		case 3:
			return 20;

		case 4:
			return 15;

		case 5:
			return 12;

		case 6:
			return 10;
	}

	return 20;
}

/*
	Konvertiere einen uint8_t zu einem Kartentypen.

	uint8_t card: Der Kartentyp index.

	Dies wird verwendet, falls man einen uint8_t zu einem Kartentypen konvertieren muss.
*/
CardType CoreHelper::Uint8ToCardType(uint8_t card) {
	switch(card) {
		case 0:
			return CardType::NUMBER_EMPTY;

		case 1:
			return CardType::NUMBER_1;

		case 2:
			return CardType::NUMBER_2;

		case 3:
			return CardType::NUMBER_3;

		case 4:
			return CardType::NUMBER_4;

		case 5:
			return CardType::NUMBER_5;

		case 6:
			return CardType::NUMBER_6;

		case 7:
			return CardType::NUMBER_7;

		case 8:
			return CardType::NUMBER_8;

		case 9:
			return CardType::NUMBER_9;

		case 10:
			return CardType::NUMBER_10;

		case 11:
			return CardType::NUMBER_11;

		case 12:
			return CardType::NUMBER_12;

		case 13:
			return CardType::NUMBER_13;

		case 14:
			return CardType::NUMBER_14;

		case 15:
			return CardType::NUMBER_15;

		case 16:
			return CardType::NUMBER_16;

		case 17:
			return CardType::NUMBER_17;

		case 18:
			return CardType::NUMBER_18;

		case 19:
			return CardType::NUMBER_19;

		case 20:
			return CardType::NUMBER_20;
	}

	return CardType::NUMBER_EMPTY;
}

/*
	Generiere einen uint16_t (2 byte) von einem Kartenstrukt.
	Dies wird verwendet, um einen Kartenstrukt als bytes wiederzugeben.

	CardStruct CS: Der Kartenstrukt, welcher zu einem uint16_t konvertiert werden soll.
*/
uint16_t CoreHelper::GetCardBytes(CardStruct CS) {
	uint8_t CType = 0x0, CColor = 0x0;

	/* Kartentypn zu uint8_t. */
	switch(CS.CT) {
		case CardType::NUMBER_EMPTY:
			CType = 0x0;
			break;

		case CardType::NUMBER_1:
			CType = 0x1;
			break;

		case CardType::NUMBER_2:
			CType = 0x2;
			break;

		case CardType::NUMBER_3:
			CType = 0x3;
			break;

		case CardType::NUMBER_4:
			CType = 0x4;
			break;

		case CardType::NUMBER_5:
			CType = 0x5;
			break;

		case CardType::NUMBER_6:
			CType = 0x6;
			break;

		case CardType::NUMBER_7:
			CType = 0x7;
			break;

		case CardType::NUMBER_8:
			CType = 0x8;
			break;

		case CardType::NUMBER_9:
			CType = 0x9;
			break;

		case CardType::NUMBER_10:
			CType = 0xA;
			break;

		case CardType::NUMBER_11:
			CType = 0xB;
			break;

		case CardType::NUMBER_12:
			CType = 0xC;
			break;

		case CardType::NUMBER_13:
			CType = 0xD;
			break;

		case CardType::NUMBER_14:
			CType = 0xE;
			break;

		case CardType::NUMBER_15:
			CType = 0xF;
			break;

		case CardType::NUMBER_16:
			CType = 0x10;
			break;

		case CardType::NUMBER_17:
			CType = 0x11;
			break;

		case CardType::NUMBER_18:
			CType = 0x12;
			break;

		case CardType::NUMBER_19:
			CType = 0x13;
			break;

		case CardType::NUMBER_20:
			CType = 0x14;
			break;
	}

	/* Kartenfarbe zu uint8_t. */
	switch(CS.CC) {
		case CardColor::COLOR_EMPTY:
			CColor = 0x0;
			break;

		case CardColor::COLOR_RED:
			CColor = 0x1;
			break;

		case CardColor::COLOR_YELLOW:
			CColor = 0x2;
			break;

		case CardColor::COLOR_GREEN:
			CColor = 0x3;
			break;

		case CardColor::COLOR_BLUE:
			CColor = 0x4;
			break;
	}

	return 256U * CColor + CType;
}

/*
	Generiere aus einem uint8_t buffer einen Kartenstrukt.
	Dies wird verwendet, um einen Buffer als Kartenstrukt wiederzugeben.

	const std::unique_ptr<uint8_t[]> &rawData: Der Buffer, wovon gelesen werden soll.
	uint32_t offset: Der Offset wovon gelesen werden soll.
*/
CardStruct CoreHelper::GetCardStruct(const std::unique_ptr<uint8_t[]> &rawData, uint32_t offset) {
	if (!rawData) return { CardType::NUMBER_EMPTY, CardColor::COLOR_EMPTY }; // Die Daten sind nicht gültig.

	CardStruct CS = { CardType::NUMBER_EMPTY, CardColor::COLOR_EMPTY };

	uint8_t CT = rawData.get()[offset], CC = rawData.get()[offset + 0x1];

	/* Generiere den KartenTypen. */
	switch(CT) {
		case 0:
			CS.CT = CardType::NUMBER_EMPTY;
			break;

		case 1:
			CS.CT = CardType::NUMBER_1;
			break;

		case 2:
			CS.CT = CardType::NUMBER_2;
			break;

		case 3:
			CS.CT = CardType::NUMBER_3;
			break;

		case 4:
			CS.CT = CardType::NUMBER_4;
			break;

		case 5:
			CS.CT = CardType::NUMBER_5;
			break;

		case 6:
			CS.CT = CardType::NUMBER_6;
			break;

		case 7:
			CS.CT = CardType::NUMBER_7;
			break;

		case 8:
			CS.CT = CardType::NUMBER_8;
			break;

		case 9:
			CS.CT = CardType::NUMBER_9;
			break;

		case 10:
			CS.CT = CardType::NUMBER_10;
			break;

		case 11:
			CS.CT = CardType::NUMBER_11;
			break;

		case 12:
			CS.CT = CardType::NUMBER_12;
			break;

		case 13:
			CS.CT = CardType::NUMBER_13;
			break;

		case 14:
			CS.CT = CardType::NUMBER_14;
			break;

		case 15:
			CS.CT = CardType::NUMBER_15;
			break;

		case 16:
			CS.CT = CardType::NUMBER_16;
			break;

		case 17:
			CS.CT = CardType::NUMBER_17;
			break;

		case 18:
			CS.CT = CardType::NUMBER_18;
			break;

		case 19:
			CS.CT = CardType::NUMBER_19;
			break;

		case 20:
			CS.CT = CardType::NUMBER_20;
			break;
	}

	/* Generiere die Kartenfarbe. */
	switch(CC) {
		case 0:
			CS.CC = CardColor::COLOR_EMPTY;
			break;

		case 1:
			CS.CC = CardColor::COLOR_RED;
			break;

		case 2:
			CS.CC = CardColor::COLOR_YELLOW;
			break;

		case 3:
			CS.CC = CardColor::COLOR_GREEN;
			break;

		case 4:
			CS.CC = CardColor::COLOR_BLUE;
			break;
	}

	return CS;
}