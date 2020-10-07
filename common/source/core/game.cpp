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
#include <unistd.h>

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
Game::Game(uint8_t plAmount) { this->InitNewGame(plAmount); }

/*
	Initialisiere ein neues Spiel.

	uint8_t plAmount: Die Spieleranzahl.
*/
void Game::InitNewGame(uint8_t plAmount) {
	/* Bereinige alles. */
	if (this->GameData) this->GameData = nullptr;
	if (this->CardDeck) this->CardDeck = nullptr;
	if (this->TableCard) this->TableCard = nullptr;
	if (this->Players.size() > 0) this->Players.clear();

	for (uint8_t i = 0; i < 6; i++) {
		this->cardIndexes[i] = 0;
		this->cardPages[i] = 0;
	}

	if (plAmount < 2 || plAmount > _GAME_MAXPLAYERS) this->PlayerAmount = 2; // 2 - 6 ist die maximale Spieleranzahl. Mehr sind nicht erlaubt.
	else this->PlayerAmount = plAmount;

	this->CardDeck = std::make_unique<Deck>(); // Initialisiere das Karten-Deck.
	this->TableCard = std::make_unique<Table>(); // Initialisiere die Tischkarten.

	/*
		Initialisiere alle Spieler inklusive Karten-Index & Karten-Seite
		welche für den Spiel-Screen relevant sind.
	*/
	for (uint8_t i = 0; i < this->PlayerAmount; i++) {
		this->Players.push_back({ std::make_unique<Player>() });
		this->cardIndexes[i] = 0;
		this->cardPages[i] = 0;
	}

	/* Ziehe die Initialen Karten vom Karten-Deck für die Spieler. */
	for (uint8_t i2 = 0; i2 < this->PlayerAmount; i2++) {
		for (uint8_t i = 0; i < CoreHelper::GetStartupCards(this->PlayerAmount); i++) {
			this->Players[i2]->AddCard(this->CardDeck);
		}
	}

	this->GameData = std::unique_ptr<uint8_t[]>(new uint8_t[_GAME_SIZE]);
	this->SaveConversion(); // Konvertiere das aktuelle Spiel zu dem Spiel-Buffer.
}

/*
	Lade ein Spiel von Spiel-Daten.
*/
void Game::LoadGameFromFile() {
	this->validGame = false; // Setze das immer zu falsch, wenn die Funktion startet.
	if (access(_GAME_DATA_FILE, F_OK) != 0) return; // Datei existiert nicht.

	FILE *file = fopen(_GAME_DATA_FILE, "r");

	if (file) {
		fseek(file, 0, SEEK_END);
		uint32_t size = ftell(file); // Teile uns die größe der Datei mit.
		fseek(file, 0, SEEK_SET);

		if (size == _GAME_SIZE) {
			this->GameData = nullptr;
			this->GameData = std::unique_ptr<uint8_t[]>(new uint8_t[_GAME_SIZE]);
			fread(this->GameData.get(), 1, _GAME_SIZE, file);
			this->validGame = true;
		}

		fclose(file);
	}
}

/*
	Konvertiere die Daten zu einem Spiel.
*/
void Game::convertDataToGame() {
	if (this->GameData && this->validGame) {
		/* Bereinige alles. */
		if (this->CardDeck) this->CardDeck = nullptr;
		if (this->TableCard) this->TableCard = nullptr;
		if (this->Players.size() > 0) this->Players.clear();

		for (uint8_t i = 0; i < 6; i++) {
			this->cardIndexes[i] = 0;
			this->cardPages[i] = 0;
		}

		this->CardDeck = std::make_unique<Deck>();
		this->TableCard = std::make_unique<Table>();

		this->currentPlayer = this->GameData.get()[_GAME_CURRENT_PLAYER]; // Der aktuelle Spieler.
		this->PlayerAmount = this->GameData.get()[_GAME_PLAYER_AMOUNT]; // Die Spieler-Anzahl.
		this->drawAmount = this->GameData.get()[_GAME_DRAW_AMOUNT]; // Die Zieh-Anzahl.
		this->useAI = this->GameData.get()[_GAME_USES_AI]; // Ob der Computer benutzt wird.

		/* Die Karten vom Karten-Deck. */
		std::vector<CardStruct> deckCards;
		if (this->GameData.get()[_GAME_CARDDECK_CARD_AMOUNT] > 0) {
			for (uint8_t deckKarten = 0; deckKarten < this->GameData.get()[_GAME_CARDDECK_CARD_AMOUNT]; deckKarten++) {
				deckCards.push_back( { CoreHelper::GetCardStruct(this->GameData.get(), _GAME_CARDDECK_CARDS + (deckKarten * _GAME_CARDSIZE)) });
			}
		}

		this->CardDeck->GetCardsFromStruct(deckCards); // Importiere die Karten vom Vektor.

		/*
			Die Tischkarten.
		*/
		std::pair<CardType, CardType> CTypes;

		/* Rote Karten. */
		CTypes.first = CoreHelper::Uint8ToCardType(this->GameData.get()[_GAME_TABLECARD_RED]);
		CTypes.second = CoreHelper::Uint8ToCardType(this->GameData.get()[_GAME_TABLECARD_RED + 1]);
		this->TableCard->ImportCardTypes(CardColor::COLOR_RED, CTypes);

		/* Gelbe Karten. */
		CTypes.first = CoreHelper::Uint8ToCardType(this->GameData.get()[_GAME_TABLECARD_YELLOW]);
		CTypes.second = CoreHelper::Uint8ToCardType(this->GameData.get()[_GAME_TABLECARD_YELLOW + 1]);
		this->TableCard->ImportCardTypes(CardColor::COLOR_YELLOW, CTypes);

		/* Grüne Karten. */
		CTypes.first = CoreHelper::Uint8ToCardType(this->GameData.get()[_GAME_TABLECARD_GREEN]);
		CTypes.second = CoreHelper::Uint8ToCardType(this->GameData.get()[_GAME_TABLECARD_GREEN + 1]);
		this->TableCard->ImportCardTypes(CardColor::COLOR_GREEN, CTypes);

		/* Blaue Karten. */
		CTypes.first = CoreHelper::Uint8ToCardType(this->GameData.get()[_GAME_TABLECARD_BLUE]);
		CTypes.second = CoreHelper::Uint8ToCardType(this->GameData.get()[_GAME_TABLECARD_BLUE + 1]);
		this->TableCard->ImportCardTypes(CardColor::COLOR_BLUE, CTypes);


		/*
			Initialisiere alle Spieler inklusive Karten-Index & Karten-Seite
			welche für den Spiel-Screen relevant sind.
		*/
		for (uint8_t i = 0; i < this->PlayerAmount; i++) {
			this->Players.push_back({ std::make_unique<Player>() });
			this->cardIndexes[i] = this->GameData.get()[_GAME_PLAYER_1_CARDINDEX + i];
			this->cardPages[i] = this->GameData.get()[_GAME_PLAYER_1_PAGEINDEX + i];
		}

		/* Und hier die Spieler-Karten. */
		std::vector<CardStruct> playerCards;
		for (uint8_t spieler = 0; spieler < this->PlayerAmount; spieler++) {
			for (uint8_t karten = 0; karten < _GAME_HANDSIZE; karten++) {

				/* Falls die Karten in der Datei nicht 0 sind, füge sie dem Vektor hinzu. */
				if (this->GameData.get()[_GAME_PLAYER_1 + (karten * _GAME_CARDSIZE) + (spieler * _GAME_PLAYERCARDSIZE)] != 0) {
					playerCards.push_back({ CoreHelper::GetCardStruct(this->GameData.get(), _GAME_PLAYER_1 + (karten * _GAME_CARDSIZE) + (spieler * _GAME_PLAYERCARDSIZE)) });
				}
			}

			this->Players[spieler]->ImportCards(playerCards); // Importiere die Karten vom Vektor.
			playerCards.clear();
		}
	}
}

/*
	Konvertiere das aktuelle spiel zu einer Speicherdatei / Buffer.
*/
void Game::SaveConversion() {
	this->GameData.get()[_GAME_CURRENT_PLAYER] = this->currentPlayer; // Der aktuelle Spieler.
	this->GameData.get()[_GAME_CARDDECK_CARD_AMOUNT] = this->CardDeck->GetDeckSize(); // Die Karten-Deck Größe.
	this->GameData.get()[_GAME_PLAYER_AMOUNT] = this->PlayerAmount; // Die Spieler-Anzahl.
	this->GameData.get()[_GAME_DRAW_AMOUNT] = this->drawAmount; // Die Zieh-Anzahl.
	this->GameData.get()[_GAME_USES_AI] = this->useAI; // Ob der Computer benutzt wird.

	/* Die Karten vom Karten-Deck. */
	for (uint8_t deckKarten = 0; deckKarten < _GAME_DECKSIZE; deckKarten++) {
		this->SetCard((_GAME_CARDDECK_CARDS + (deckKarten * _GAME_CARDSIZE)), this->CardDeck->GetCardFromDeck(deckKarten));
	}

	/*
		Die Tischkarten.
	*/

	/* Rote Karten. */
	*reinterpret_cast<uint16_t*>(this->GameData.get() + _GAME_TABLECARD_RED) =
		256U * (uint8_t)this->TableCard->GetCurrent(CardColor::COLOR_RED).second + (uint8_t)this->TableCard->GetCurrent(CardColor::COLOR_RED).first;

	/* Gelbe Karten. */
	*reinterpret_cast<uint16_t*>(this->GameData.get() + _GAME_TABLECARD_YELLOW) =
		256U * (uint8_t)this->TableCard->GetCurrent(CardColor::COLOR_YELLOW).second + (uint8_t)this->TableCard->GetCurrent(CardColor::COLOR_YELLOW).first;

	/* Grüne Karten. */
	*reinterpret_cast<uint16_t*>(this->GameData.get() + _GAME_TABLECARD_GREEN) =
		256U * (uint8_t)this->TableCard->GetCurrent(CardColor::COLOR_GREEN).second + (uint8_t)this->TableCard->GetCurrent(CardColor::COLOR_GREEN).first;

	/* Blaue Karten. */
	*reinterpret_cast<uint16_t*>(this->GameData.get() + _GAME_TABLECARD_BLUE) =
		256U * (uint8_t)this->TableCard->GetCurrent(CardColor::COLOR_BLUE).second + (uint8_t)this->TableCard->GetCurrent(CardColor::COLOR_BLUE).first;


	/* Und hier die Spielerkarten. */
	for (uint8_t spieler = 0; spieler < _GAME_MAXPLAYERS; spieler++) {

		/* Für den Spieler, 80 Karten. (0x50) */
		for (uint8_t karten = 0; karten < _GAME_HANDSIZE; karten++) {

			/*
				Falls der Spieler am spiel teilnimmt, schreibe seine Karten und den Karten-Index
				und der Seiten-Index in den Buffer.
			*/
			if ((uint8_t)this->Players.size() > spieler) {
				this->GameData.get()[_GAME_PLAYER_1_CARDINDEX + spieler] = this->cardIndexes[spieler];
				this->GameData.get()[_GAME_PLAYER_1_PAGEINDEX + spieler] = this->cardPages[spieler];
				this->SetCard(_GAME_PLAYER_1 + (karten * _GAME_CARDSIZE) + (spieler * _GAME_PLAYERCARDSIZE), this->Players[spieler]->GetCard(karten));

			/* Ansonsten.. setze leere Karten in den Buffer mit leeren Indexen. */
			} else {
				this->SetEmptyCard(_GAME_PLAYER_1 + (karten * _GAME_CARDSIZE) + (spieler * _GAME_PLAYERCARDSIZE));
				this->GameData.get()[_GAME_PLAYER_1_CARDINDEX + spieler] = 0;
				this->GameData.get()[_GAME_PLAYER_1_PAGEINDEX + spieler] = 0;
			}
		}
	}
}

/*
	Schreibe die Daten zu einer datei.
*/
void Game::SaveToFile(bool update) {
	if (update) this->SaveConversion(); // Konvertiere, falls update ist gewollt (true).

	FILE *out = fopen(_GAME_DATA_FILE, "w");
	fwrite(this->GameData.get(), 1, _GAME_SIZE, out);
	fclose(out);
}

/*
	Der Destruktor.
	Aktuell keinen plan was dort alles kommt.
	Eventuell einen boolean parameter um auf die Speicherdatei zu schreiben?
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
	Wiedergebe, ob die Karte von einem Spieler gespielt werden kann.

	uint8_t player: Der Spieler-Index.
	uint8_t index: Der Karten-Index.
*/
bool Game::Playable(uint8_t player, uint8_t index) {
	if (player < (uint8_t)this->Players.size()) {
		return this->Players[player]->Playable(index, this->TableCard);
	}

	return false;
}

/*
	Wiedergebe die Anzahl der Karten von der Spielerhand.

	uint8_t player: Der Spieler-Index.
*/
uint8_t Game::GetPlayerHandSize(uint8_t player) const {
	if (player < (uint8_t)this->Players.size()) return this->Players[player]->GetHandSize();

	return 0;
}