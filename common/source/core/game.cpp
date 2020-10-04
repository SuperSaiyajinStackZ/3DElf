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

#include "game.hpp"

/*
	Füge eine Karte zum buffer hinzu.

	uint32_t offset: Der Offset, auf welche die Karte gesetzt werden soll.
	CardStruct CS: Der Kartenstrukt.
*/
void Game::SetCard(uint32_t offset, CardStruct CS) {
	*reinterpret_cast<uint16_t*>(this->GameData.get() + offset) = CoreHelper::GetCardBytes(CS);
}

/*
	Füge eine leere Karte zum buffer hinzu.

	uint32_t offset: Der Offset, auf welche die Karte gesetzt werden soll.
*/
void Game::SetEmptyCard(uint32_t offset) {
	*reinterpret_cast<uint16_t*>(this->GameData.get() + offset) = 0;
}

/*
	Der Spiel Konstruktor.

	uint8_t plAmount: Die Spieleranzahl.
*/
Game::Game(uint8_t plAmount) {
	if (plAmount > _GAME_MAXPLAYERS) this->PlayerAmount = _GAME_MAXPLAYERS; // 6 ist die maximale anzahl. Mehr sind nicht erlaubt.
	else this->PlayerAmount = plAmount;

	this->CardDeck = std::make_unique<Deck>(); // Initialisiere Kartendeck.
	this->TableCard = std::make_unique<Table>(); // Initialisiere Tischkarte.

	/* Initialisiere alle Spieler inklusive KartenIndex & Karten-Seite welche für den Spiel-Screen relevant sind. */
	for (uint8_t i = 0; i < this->PlayerAmount; i++) {
		this->Players.push_back({ std::make_unique<Player>() });
		this->cardIndexes.push_back({ 0 });
		this->cardPages.push_back({ 0 });
	}

	/* Ziehe die Initiale Karten vom Kartendeck für die Spieler. */
	for (uint8_t i2 = 0; i2 < this->PlayerAmount; i2++) {
		for (uint8_t i = 0; i < CoreHelper::GetStartupCards(this->PlayerAmount); i++) {
			this->Players[i2]->AddCard(this->CardDeck);
		}
	}

	this->GameData = std::unique_ptr<uint8_t[]>(new uint8_t[_GAME_SIZE]); // Initialisiere den Spieldaten buffer für das aktuelle Spiel.
	this->SaveConversion(); // Konvertiere das aktuelle spiel zu dem Spiel-Buffer.
}

/*
	Konvertiere das aktuelle spiel zu einer Speicherdatei / Buffer.
*/
void Game::SaveConversion() {
	this->GameData.get()[_GAME_CURRENT_PLAYER] = this->currentPlayer; // Der aktuelle Spieler.
	this->GameData.get()[_GAME_CARDDECK_CARD_AMOUNT] = this->CardDeck->GetDeckSize(); // Die Deck-Größe.
	this->GameData.get()[_GAME_PLAYER_AMOUNT] = this->PlayerAmount; // Die Spieler-Anzahl.

	/* Die Karten vom Deck. */
	for (uint8_t deckKarten = 0; deckKarten < _GAME_DECKSIZE; deckKarten++) {
		this->SetCard((_GAME_CARDDECK_CARDS + (deckKarten * _GAME_CARDSIZE)), this->CardDeck->GetCardFromDeck(deckKarten));
	}

	/*
		Die Tischkarten.
	*/

	/* Roten Karten. */
	*reinterpret_cast<uint16_t*>(this->GameData.get() + _GAME_TABLECARD_RED) =
		(uint8_t)this->TableCard->GetCurrent(CardColor::COLOR_RED).first + (uint8_t)this->TableCard->GetCurrent(CardColor::COLOR_RED).second;

	/* Gelben Karten. */
	*reinterpret_cast<uint16_t*>(this->GameData.get() + _GAME_TABLECARD_YELLOW) =
		(uint8_t)this->TableCard->GetCurrent(CardColor::COLOR_YELLOW).first + (uint8_t)this->TableCard->GetCurrent(CardColor::COLOR_YELLOW).second;

	/* Grünen Karten. */
	*reinterpret_cast<uint16_t*>(this->GameData.get() + _GAME_TABLECARD_GREEN) =
		(uint8_t)this->TableCard->GetCurrent(CardColor::COLOR_GREEN).first + (uint8_t)this->TableCard->GetCurrent(CardColor::COLOR_GREEN).second;

	/* Blauen Karten. */
	*reinterpret_cast<uint16_t*>(this->GameData.get() + _GAME_TABLECARD_BLUE) =
		(uint8_t)this->TableCard->GetCurrent(CardColor::COLOR_BLUE).first + (uint8_t)this->TableCard->GetCurrent(CardColor::COLOR_BLUE).second;


	/* Und hier die Spielerkarten. */
	for (uint8_t spieler = 0; spieler < _GAME_MAXPLAYERS; spieler++) {

		/* Für den Spieler, 80 Karten. (0x50) */
		for (uint8_t karten = 0; karten < _GAME_HANDSIZE; karten++) {

			/* Falls der Spieler am spiel teilnimmt, schreibe seine Karten in den Buffer. */
			if ((uint8_t)this->Players.size() > spieler) {

				this->SetCard(_GAME_PLAYER_1 + (karten * _GAME_CARDSIZE) + (spieler * _GAME_PLAYERCARDSIZE), this->Players[spieler]->GetCard(karten));

			/* Ansonsten.. setze leere Karten in den Buffer. */
			} else {
				this->SetEmptyCard(_GAME_PLAYER_1 + (karten * _GAME_CARDSIZE) + (spieler * _GAME_PLAYERCARDSIZE));
			}
		}
	}
}

/*
	Schreibe die Daten zu einer datei.
*/
void Game::SaveToFile(bool update) {
	if (update) this->SaveConversion(); // Konvertiere, falls update ist gewollt (true).

	FILE *out = fopen(_GAME_SAVEPATH, "w");
	fwrite(this->GameData.get(), 1, _GAME_SIZE, out);
	fclose(out);
}

/*
	Der Destruktor.
	Aktuell keinen plan was dort alles kommt. Eventuell einen boolean parameter um auf die Speicherdatei zu schreiben?
*/
Game::~Game() { this->GameData = nullptr; }

/*
	Wiedergebe den Kartentyp von der Spielerhand.

	uint8_t player: Der Spieler-Index.
	uint8_t index: Der Karten-Index.
*/
CardType Game::GetPlayerCardType(uint8_t player, uint8_t index) const {
	if (player < (uint8_t)this->Players.size()) return this->Players[player]->GetType(index);

	return CardType::NUMBER_EMPTY;
}

/*
	Wiedergebe die Kartenfarbe von der Spielerhand.

	uint8_t player: Der Spieler-Index.
	uint8_t index: Der Karten-Index.
*/
CardColor Game::GetPlayerCardColor(uint8_t player, uint8_t index) const {
	if (player < (uint8_t)this->Players.size()) return this->Players[player]->GetColor(index);

	return CardColor::COLOR_EMPTY;
}

/*
	Wiedergebe eine Karte von der Spielerhand.

	uint8_t player: Der Spieler-Index.
	uint8_t index: Der Karten-Index.
*/
CardStruct Game::GetPlayerCard(uint8_t player, uint8_t index) const {
	if (player < (uint8_t)this->Players.size()) return this->Players[player]->GetCard(index);

	return { CardType::NUMBER_EMPTY, CardColor::COLOR_EMPTY };
}

/*
	Füge eine Karte vom Kartendeck zur Spielerhand hinzu.

	uint8_t player: Der Spieler-Index.
*/
void Game::AddPlayerCard(uint8_t player) {
	if (this->drawAmount < 3) {
		if (player < (uint8_t)this->Players.size()) {
			this->Players[player]->AddCard(this->CardDeck);
			this->drawAmount++;
		}
	}
}

/*
	Entferne eine Karte von der Spielerhand.

	uint8_t player: Der Spieler-Index.
	uint8_t index: Der Karten-Index.
*/
void Game::RemovePlayerCard(uint8_t player, uint8_t index) {
	if (player < (uint8_t)this->Players.size()) this->Players[player]->RemoveCard(index);
}

/*
	Wiedergebe die Anzahl der Karten von der Spielerhand.

	uint8_t player: Der Spieler-Index.
*/
uint8_t Game::GetPlayerHandSize(uint8_t player) const {
	if (player < (int)this->Players.size()) return this->Players[player]->GetHandSize();

	return 0;
}