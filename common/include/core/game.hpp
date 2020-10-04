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

#ifndef _3DELF_GAME_HPP
#define _3DELF_GAME_HPP

#include "coreHelper.hpp"
#include "deck.hpp"
#include "player.hpp"
#include "table.hpp"
#include <vector>

class Deck;
class Player;
class Table;

#define _GAME_CURRENT_PLAYER 0x0
#define _GAME_CARDDECK_CARD_AMOUNT 0x1
#define _GAME_PLAYER_AMOUNT 0x2

#define _GAME_DECKSIZE 0xA0
#define _GAME_TABLECARD_SIZE 0x2
#define _GAME_PLAYERCARDSIZE 0xA0
#define _GAME_HANDSIZE 0x50
#define _GAME_CARDSIZE 0x2
#define _GAME_MAXPLAYERS 6

#define _GAME_CARDDECK_CARDS 0x3

#define _GAME_TABLECARD_RED 0xA3
#define _GAME_TABLECARD_YELLOW 0xA5
#define _GAME_TABLECARD_GREEN 0xA7
#define _GAME_TABLECARD_BLUE 0xA9

#define _GAME_PLAYER_1 0xAB
#define _GAME_PLAYER_2 0x14C
#define _GAME_PLAYER_3 0x1ED
#define _GAME_PLAYER_4 0x28E
#define _GAME_PLAYER_5 0x32F
#define _GAME_PLAYER_6 0x3D0

#define _GAME_SIZE 0x471

#define _GAME_SAVEPATH "sdmc:/3ds/3DElf/GameData.dat"

/*
	Spieldaten Struktur...

	Bemerkung zu den Spielerkarten:
		- Weil wir nicht wissen, wie viele Karten die Spieler besitzen, müssen wir Platz für mindestens des Kartendecks vorbehalten.
		- Ebenfalls wissen wir nicht, wie viele Spieler genau beim spiel teilnehmen, deshalb müssen wir einen Platzhalter für 6 Spieler vorbehalten.
		- Jedoch sind 80 Karten an einem Spieler nicht möglich, aber sicher ist sicher.


	0x0: Aktueller Spieler.
	0x1: Anzahl der Karten vom Kartendeck.
	0x2: Spieleranzahl.
	0x3 - 0xA2: KartenDeck Karten. Größe: 0xA0. (80 Karten)

		/ Tischkarten. \
	0xA3 - 0xA4: Tischkarte Rot. (Jeweils 2 KartenTypen (uint16_t) für die Ober und Unter-karte).
	0xA5 - 0xA6: Tischkarte Gelb. (Jeweils 2 KartenTypen (uint16_t) für die Ober und Unter-karte).
	0xA7 - 0xA8: Tischkarte Grün. (Jeweils 2 KartenTypen (uint16_t) für die Ober und Unter-karte).
	0xA9 - 0xAA: Tischkarte Blau. (Jeweils 2 KartenTypen (uint16_t) für die Ober und Unter-karte).

		/ Spielerkarten. \
	 0xAB - 0x14B: Spieler 1 Karten. Größe: 0xA0. (80 Karten)
	0x14C - 0x1EC: Spieler 2 Karten. Größe: 0xA0. (80 Karten)
	0x1ED - 0x28D: Spieler 3 Karten. Größe: 0xA0. (80 Karten)
	0x28E - 0x32E: Spieler 4 Karten. Größe: 0xA0. (80 Karten)
	0x32F - 0x3CF: Spieler 5 Karten. Größe: 0xA0. (80 Karten)
	0x3D0 - 0x470: Spieler 6 Karten. Größe: 0xA0. (80 Karten)

	Datengröße: 0x471, dies entspricht etwa 1,10 KB.
*/

class Game {
public:
	Game(uint8_t plAmount);
	~Game();
	bool LoadGameFromFile();
	void convertDataToGame();
	void SaveConversion(); // Konvertiere das aktuelle Spiel zu einem Buffer.
	void SaveToFile(bool update = true); // Konvertiere wenn true und schreibe zu datei.

	/* Spielerkarten wiedergebung funktionen. */
	CardType GetPlayerCardType(uint8_t player, uint8_t index) const;
	CardColor GetPlayerCardColor(uint8_t player, uint8_t index) const;
	CardStruct GetPlayerCard(uint8_t player, uint8_t index) const;

	/* Karten mit Spielerhand funktionen. */
	void AddPlayerCard(uint8_t player);
	void RemovePlayerCard(uint8_t player, uint8_t index);
	uint8_t GetPlayerHandSize(uint8_t player) const;

	/* Aktueller Spieler & Anzahl funktionen. */
	uint8_t GetCurrentPlayer() const { return this->currentPlayer; }
	void SetCurrentPlayer(uint8_t p) { this->currentPlayer = p; }
	uint8_t GetPlayerAmount() const { return this->PlayerAmount; }

	/* Zieh-Anzahl funktionen. */
	uint8_t GetDrawAmount() const { return this->drawAmount; }
	void ResetDrawAmount() { this->drawAmount = 0; }

	/* Karten-Index funktionen. */
	uint8_t GetCardIndex(uint8_t player) const { return this->cardIndexes[player]; }
	void SetCardIndex(uint8_t player, uint8_t indx) { this->cardIndexes[player] = indx; }

	/* Karten-Seiten funktionen. */
	uint8_t GetPageIndex(uint8_t player) const { return this->cardPages[player]; }
	void SetPageIndex(uint8_t player, uint8_t indx) { this->cardPages[player] = indx; }

	/* Haupt-Spiel Logik und so. */
	std::pair<CardType, CardType> getTableCard(CardColor CR) const { return this->TableCard->GetCurrent(CR); }
	bool CanPlay(CardColor CLR, bool upper, CardType CT) { return this->TableCard->CanPlay(CLR, upper, CT); }
	void SetCard(CardColor CLR, bool upper, CardType CT) { this->TableCard->SetCard(CLR, upper, CT); }

	/* Karten-Deck funktionen. */
	uint8_t GetDeckSize() const { return this->CardDeck->GetDeckSize(); }
private:
	/* Setze die Karten in den Save Buffer. */
	void SetCard(uint32_t offset, CardStruct CS);
	void SetEmptyCard(uint32_t offset);

	/* Zeiger-Klassen für das Spiel. */
	std::unique_ptr<Deck> CardDeck = nullptr;
	std::unique_ptr<Table> TableCard = nullptr;
	std::vector<std::unique_ptr<Player>> Players;

	/* Variablen für das Spiel. */
	std::vector<uint8_t> cardIndexes, cardPages;
	uint8_t PlayerAmount = 2, currentPlayer = 0, drawAmount = 0;

	std::unique_ptr<uint8_t[]> GameData = nullptr; // Spieledaten Buffer.
};

#endif