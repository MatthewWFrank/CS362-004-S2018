/*
Author: Matthew Frank
Course: CS 362
Assignment: Assignment 3, Unit Testing
Date: 04/28/2018
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

// Utility functions for reporting results
void test_passed();
void test_failed();
void reportTestResults();

// Utility variables for reporting results
int TESTSPASSED = 0;
int TOTALTESTS = 0;

int main() {
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	struct gameState gameState, testState;

	int cardCount;

	int currentPlayer = 0;
	int numPlayers = 2;
	int cards_in_game[10] = { adventurer, smithy, village, salvager, council_room, feast, mine, remodel, baron, great_hall };
	int seed = 1;
	initializeGame(numPlayers, cards_in_game, seed, &gameState);
	memcpy(&testState, &gameState, sizeof(struct gameState));

	/* Testing the fullDeckCount function 	
	** - Full Deck Count checks how many copies of a SPECIFIC 
	** card exist, in total, for a player, including in their
	** deck, hand, and discard pile.
	*/
	printf("\nTESTING THE fullDeckCount() FUNCTION:\n\n");
	testState.hand[currentPlayer][4] = council_room;

	printf("\tTesting it correctly counts the copper coins.\n");
	cardCount = fullDeckCount(currentPlayer, copper, &testState);
	if (cardCount == 7) {
		test_passed();
	} else if (cardCount != 7) {
		test_failed();

		printf("/t/tWrong number of copper coins - there should be 7.\n");
		printf("/t/tInstead, found %d copper coins.\n", cardCount);
	}

	printf("\n");

	playCard(4, choice1, choice2, choice3, &testState);
	printf("\tTesting it correctly counts cards in hand.\n");
	if (testState.handCount[currentPlayer] == 8) {
		test_passed();
	} else if (testState.handCount[currentPlayer] != 8) {
		test_failed();

		printf("\t\tShould be 8 cards in HAND after playing council room.\n");
		printf("\t\tThere are %d cards in HAND.\n", testState.handCount[currentPlayer]);
	}

	printf("\n");

	printf("\tTesting it correctly counts cards in deck.\n");
	if (testState.deckCount[currentPlayer] == 1) {
		test_passed();
	}
	else if (testState.deckCount[currentPlayer] != 1) {
		test_failed();
	
		printf("\t\tShould be 1 cards in DECK after playing council room.\n");
		printf("\t\tThere are %d cards in DECK.\n", testState.deckCount[currentPlayer]);
	}

	printf("\n");

	/* DISCOVERED that discardCard() function isn't actually tracking
	** the number of discarded cards.  Which points out why it's
	** unreliable to rely on other functions you haven't tested.
	** 
	** Things are discarded from the HAND, but then not actually
	** added to a DISCARD pile.
	*/

	printf("\tTesting it correctly counts cards in discard.\n");
	if (testState.discardCount[currentPlayer] == 1) {
		test_passed();
	}
	else if (testState.discardCount[currentPlayer] != 1) {
		test_failed();
		
		printf("\t\tShould be 1 cards in DISCARD after playing council room.\n");
		printf("\t\tThere are %d cards in DISCARD.\n", testState.discardCount[currentPlayer]);
	}

	/* Lists all the cards in the players hand/deck/discard for easy checking
	int a;
	int currentCard;
	char cardName[20] = "";

	printf("\n\nCards in HAND:\n");
	for (a = 0; a < testState.handCount[currentPlayer]; a++) {
	currentCard = testState.hand[currentPlayer][a];

	cardNumToName(currentCard, cardName);
	printf("The card in hand position %d is %s\n", a, cardName);
	}

	printf("\n\nCards in DECK:\n");
	for (a = 0; a < testState.deckCount[currentPlayer]; a++) {
		currentCard = testState.deck[currentPlayer][a];

		cardNumToName(currentCard, cardName);
		printf("The card in deck position %d is %s\n.", a, cardName);
	}

	printf("\n\nCards in DISCARD:\n");
	for (a = 0; a < testState.discardCount[currentPlayer]; a++) {
		currentCard = testState.discard[currentPlayer][a];

		cardNumToName(currentCard, cardName);
		printf("The card in discard position %d is %s\n.", a, cardName);
	}
	*/

	printf("\n");

	reportTestResults();
	return 0;
}

// Output that the test passed and increment TESTSPASSED and TOTALTESTS
void test_passed() {
	printf("\tTEST PASSED\n");

	TESTSPASSED++;
	TOTALTESTS++;
}

// Output that the test failed, and only increment TOTALTESTS
void test_failed() {
	printf("\tTEST FAILED\n");

	TOTALTESTS++;
}

// Output the results
void reportTestResults() {
	printf("%d/%d Tests Passed\n\n", TESTSPASSED, TOTALTESTS);
}