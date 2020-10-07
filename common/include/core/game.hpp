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

#define _GAME_CURRENT_PLAYER 0x0
#define _GAME_CARDDECK_CARD_AMOUNT 0x1
#define _GAME_PLAYER_AMOUNT 0x2
#define _GAME_DRAW_AMOUNT 0x3
#define _GAME_CARDDECK_CARDS 0x4

#define _GAME_DECKSIZE 0xA0
#define _GAME_TABLECARD_SIZE 0x2
#define _GAME_PLAYERCARDSIZE 0xA0
#define _GAME_HANDSIZE 0x50
#define _GAME_CARDSIZE 0x2
#define _GAME_MAXPLAYERS 6

#define _GAME_TABLECARD_RED 0xA4
#define _GAME_TABLECARD_YELLOW 0xA6
#define _GAME_TABLECARD_GREEN 0xA8
#define _GAME_TABLECARD_BLUE 0xAA

#define _GAME_PLAYER_1 0xAC
#define _GAME_PLAYER_2 0x14D
#define _GAME_PLAYER_3 0x1EE
#define _GAME_PLAYER_4 0x28F
#define _GAME_PLAYER_5 0x330
#define _GAME_PLAYER_6 0x3D1

#define _GAME_PLAYER_1_CARDINDEX 0x472
#define _GAME_PLAYER_2_CARDINDEX 0x473
#define _GAME_PLAYER_3_CARDINDEX 0x474
#define _GAME_PLAYER_4_CARDINDEX 0x475
#define _GAME_PLAYER_5_CARDINDEX 0x476
#define _GAME_PLAYER_6_CARDINDEX 0x477

#define _GAME_PLAYER_1_PAGEINDEX 0x478
#define _GAME_PLAYER_2_PAGEINDEX 0x479
#define _GAME_PLAYER_3_PAGEINDEX 0x47A
#define _GAME_PLAYER_4_PAGEINDEX 0x47B
#define _GAME_PLAYER_5_PAGEINDEX 0x47C
#define _GAME_PLAYER_6_PAGEINDEX 0x47D

#define _GAME_USES_AI 0x47E
#define _GAME_SIZE 0x47F

#define _GAME_DATA_FILE "sdmc:/3ds/3DElf/GameData.dat" // Die Spiel-Daten werden hier gespeichert.

/*
	Spieldaten Struktur...

	Bemerkung zu den Spielerkarten:
		- Weil wir nicht wissen, wie viele Karten die Spieler besitzen, müssen wir Platz für mindestens des Kartendecks vorbehalten.
		- Ebenfalls wissen wir nicht, wie viele Spieler genau beim spiel teilnehmen, deshalb müssen wir einen Platzhalter für 6 Spieler vorbehalten.
		- Jedoch sind 80 Karten an einem Spieler nicht möglich, aber sicher ist sicher.


	0x0: Aktueller Spieler.
	0x1: Anzahl der Karten vom Kartendeck.
	0x2: Spieleranzahl.
	0x3: Die Anzahl der gezogenen Karten.
	0x4 - 0xA3: KartenDeck Karten. Größe: 0xA0. (80 Karten)

		/ Tischkarten. \
	0xA4 - 0xA5: Tischkarte Rot. (Jeweils 2 KartenTypen (uint16_t) für die Ober und Unter-karte).
	0xA6 - 0xA7: Tischkarte Gelb. (Jeweils 2 KartenTypen (uint16_t) für die Ober und Unter-karte).
	0xA8 - 0xA9: Tischkarte Grün. (Jeweils 2 KartenTypen (uint16_t) für die Ober und Unter-karte).
	0xAA - 0xAB: Tischkarte Blau. (Jeweils 2 KartenTypen (uint16_t) für die Ober und Unter-karte).

		/ Spielerkarten. \
	 0xAC - 0x14C: Spieler 1 Karten. Größe: 0xA0. (80 Karten)
	0x14D - 0x1ED: Spieler 2 Karten. Größe: 0xA0. (80 Karten)
	0x1EE - 0x28E: Spieler 3 Karten. Größe: 0xA0. (80 Karten)
	0x28F - 0x32F: Spieler 4 Karten. Größe: 0xA0. (80 Karten)
	0x330 - 0x3D0: Spieler 5 Karten. Größe: 0xA0. (80 Karten)
	0x3D1 - 0x471: Spieler 6 Karten. Größe: 0xA0. (80 Karten)

		/ Zuletzt noch die Karten und Seiten Indexe. \
	0x472: Spieler 1 Karten Index.
	0x473: Spieler 2 Karten Index.
	0x474: Spieler 3 Karten Index.
	0x475: Spieler 4 Karten Index.
	0x476: Spieler 5 Karten Index.
	0x477: Spieler 6 Karten Index.

	0x478: Spieler 1 Seiten Index.
	0x479: Spieler 2 Seiten Index.
	0x47A: Spieler 1 Seiten Index.
	0x47B: Spieler 2 Seiten Index.
	0x47C: Spieler 1 Seiten Index.
	0x47D: Spieler 2 Seiten Index.

	0x47E: Ob der Computer benutzt wurde.

	Datengröße: 0x47F, dies entspricht etwa 1,12 KB.
*/

class Game {
public:
	Game(uint8_t plAmount);
	~Game();

	/* Spiel-Utilities. */
	void InitNewGame(uint8_t plAmount);
	void LoadGameFromFile(); // Lade die Spiel-Daten von der Datei.
	void convertDataToGame(); // Konvertiere die Spiel-Daten zu einem Spiel.
	void SaveConversion(); // Konvertiere das aktuelle Spiel zu einem Buffer.
	void SaveToFile(bool update = true); // Konvertiere wenn true und schreibe zur Datei.

	/* Spielerkarten wiedergebung funktionen. */
	CardType GetPlayerCardType(uint8_t player, uint8_t index) const;
	CardColor GetPlayerCardColor(uint8_t player, uint8_t index) const;
	CardStruct GetPlayerCard(uint8_t player, uint8_t index) const;

	/* Karten mit Spielerhand funktionen. */
	void AddPlayerCard(uint8_t player);
	void RemovePlayerCard(uint8_t player, uint8_t index);
	bool Playable(uint8_t player, uint8_t index);
	uint8_t GetPlayerHandSize(uint8_t player) const;

	/* Aktueller Spieler & Anzahl funktionen. */
	uint8_t GetCurrentPlayer() const { return this->currentPlayer; }
	void SetCurrentPlayer(uint8_t p) { this->currentPlayer = p; }
	uint8_t GetPlayerAmount() const { return this->PlayerAmount; }
	void SetPlayerAmount(uint8_t amount) { this->PlayerAmount = amount; }

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

	/* Wiedergebe ob das Spiel gültig ist. */
	bool validLoaded() const { return this->validGame; };

	/* Computer part. */
	bool GetAI() const { return this->useAI; }
	void SetAI(bool AI) { this->useAI = AI; }
private:
	/* Setze die Karten in den Save Buffer. */
	void SetCard(uint32_t offset, CardStruct CS);
	void SetEmptyCard(uint32_t offset);

	/* Zeiger-Klassen für das Spiel. */
	std::unique_ptr<Deck> CardDeck = nullptr;
	std::unique_ptr<Table> TableCard = nullptr;
	std::vector<std::unique_ptr<Player>> Players;

	/* Variablen für das Spiel. */
	uint8_t cardIndexes[6] = { 0 }, cardPages[6] = { 0 };
	uint8_t PlayerAmount = 2, currentPlayer = 0, drawAmount = 0;
	bool validGame = false, useAI = false;

	std::unique_ptr<uint8_t[]> GameData = nullptr; // Spiel-Daten Buffer.
};

#endif