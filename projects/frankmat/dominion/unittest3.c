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
	struct gameState gameState, testState;

	int currentPlayer = 0;
	int numPlayers = 4;
	int cards_in_game[10] = { adventurer, smithy, village, salvager, council_room, feast, mine, remodel, baron, great_hall };
	int seed = 1;
	initializeGame(numPlayers, cards_in_game, seed, &gameState);
	memcpy(&testState, &gameState, sizeof(struct gameState));

	/* Testing the updateCoins() function 	*/
	printf("\nTESTING THE updateCoins() FUNCTION:\n\n");

	int a;
	int coinTotal;

	/* Testing that a pure copper hand is added correctly. */
	printf("\tTesting that a pure copper hand is added correctly.\n");
	for (a = 0; a < testState.handCount[currentPlayer]; a++) {
		testState.hand[currentPlayer][a] = copper;
	}

	updateCoins(currentPlayer, &testState, 0);
	coinTotal = testState.coins;

	if (coinTotal == 5) {
		test_passed();
	} else {
		test_failed();

		printf("\t\t5 copper coins should total 5 coins.\n");
		printf("\t\tActual total is: %d\n", coinTotal);
	}

	printf("\n");

	/* Testing that a pure silver hand is added correctly. */
	printf("\tTesting that a pure silver hand is added correctly.\n");
	for (a = 0; a < testState.handCount[currentPlayer]; a++) {
		testState.hand[currentPlayer][a] = silver;
	}

	updateCoins(currentPlayer, &testState, 0);
	coinTotal = testState.coins;

	if (coinTotal == 10) {
		test_passed();
	}
	else {
		test_failed();

		printf("\t\t5 silver coins should total 10 coins.\n");
		printf("\t\tActual total is: %d\n", coinTotal);
	}

	printf("\n");

	/* Testing that a pure gold hand is added correctly. */
	printf("\tTesting that a pure gold hand is added correctly.\n");
	for (a = 0; a < testState.handCount[currentPlayer]; a++) {
		testState.hand[currentPlayer][a] = gold;
	}

	updateCoins(currentPlayer, &testState, 0);
	coinTotal = testState.coins;

	if (coinTotal == 15) {
		test_passed();
	}
	else if (coinTotal != 15) {
		test_failed();

		printf("\t\t5 gold coins should total 15 coins.\n");
		printf("\t\tActual total is: %d\n", coinTotal);
	}

	printf("\n");

	/* Testing that a mixed 2 copper, 2 silver, 1 gold hand is added correctly. */
	printf("\tTesting that a mixed hand is added correctly.\n");
	testState.hand[currentPlayer][0] = copper;
	testState.hand[currentPlayer][1] = copper;
	testState.hand[currentPlayer][2] = silver;
	testState.hand[currentPlayer][3] = silver;
	testState.hand[currentPlayer][4] = gold;

	updateCoins(currentPlayer, &testState, 0);
	coinTotal = testState.coins;

	if (coinTotal == 9) {
		test_passed();
	}
	else if (coinTotal != 9) {
		test_failed();

		printf("\t\t2 coppers, 2 silvers, and 1 gold should total 9 coins.\n");
		printf("\t\tActual total is: %d\n", coinTotal);
	}

	printf("\n");

	/* Testing that bonus coins are added correctly. */
	printf("\tTesting that bonus coins are added correctly.\n");
	for (a = 0; a < testState.handCount[currentPlayer]; a++) {
		testState.hand[currentPlayer][a] = copper;
	}

	updateCoins(currentPlayer, &testState, 2);
	coinTotal = testState.coins;

	if (coinTotal == 7) {
		test_passed();
	}
	else if (coinTotal != 7) {
		test_failed();

		printf("\t\t5 coppers and 2 bonus coins should total 7 coins.\n");
		printf("\t\tActual total is: %d\n", coinTotal);
	}

	printf("\n");

	/* Testing that a hand empty of coins equals 0 */
	printf("\tTesting that a hand with no coins totals 0.\n");
	for (a = 0; a < testState.handCount[currentPlayer]; a++) {
		testState.hand[currentPlayer][a] = estate;
	}

	updateCoins(currentPlayer, &testState, 0);
	coinTotal = testState.coins;

	if (coinTotal == 0) {
		test_passed();
	}
	else if (coinTotal != 0) {
		test_failed();

		printf("\t\t5 estates should total 0 coins.\n");
		printf("\t\tActual total is: %d\n", coinTotal);
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