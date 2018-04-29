/*
Author: Matthew Frank
Course: CS 362
Assignment: Assignment 3, Unit Testing
Date: 04/28/2018
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
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
	struct gameState gameState, testState;

	int numPlayers = 2;
	char cardName[20] = "";
	int cards_in_game[10] = { adventurer, smithy, village, salvager, council_room, feast, mine, remodel, baron, great_hall };
	int seed = 1;
	initializeGame(numPlayers, cards_in_game, seed, &gameState);
	memcpy(&testState, &gameState, sizeof(struct gameState));

	/* Testing the handCard() function 	*/
	printf("\nTESTING THE handCard() FUNCTION:\n\n");

	// Manually setting the hands for the 1st players, so each card is different
	testState.hand[0][0] = copper;
	testState.hand[0][1] = silver;
	testState.hand[0][2] = gold;
	testState.hand[0][3] = estate;
	testState.hand[0][4] = duchy;

	/* Testing handCard correctly polls the next 1st player's 1st card.
	** this ensures both (a) the player is correct and (b) the card
	** is correct, as we've manually set cards.
	*/
	printf("Testing handCard() correctly polls the 1st player's 1st card.\n");
	if (handCard(0, &testState) == copper) {
		test_passed();
	} else if (handCard(0, &testState) != copper) {
		test_failed();

		cardNumToName(0, cardName);
		printf("\t\tExpected card: copper.\n");
		printf("\t\tActual card: %s.\n", cardName);
	}

	printf("\n");

	reportTestResults();
	return 0;

	/* Lists all the cards in the players hand for easy checking
	int a;
	int currentCard;
	char cardName[20] = "";
	for (a = 0; a < testState.handCount[currentPlayer]; a++) {
	currentCard = testState.hand[currentPlayer][a];

	cardNumToName(currentCard, cardName);
	printf("The card in hand position %d is %s\n.", a, cardName);
	}
	*/
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