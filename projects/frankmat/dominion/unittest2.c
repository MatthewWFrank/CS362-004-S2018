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

/**********************************************************************************************
** TEST UPDATING COINS
** TEST FULL DECK COUNT
** TEST ISGAMEOVER
**/

int main() {
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	struct gameState gameState, testState;

	int currentPlayer = 0;
	int numPlayers = 4;
	int cards_in_game[10] = { adventurer, smithy, village, salvager, council_room, feast, mine, remodel, baron, great_hall };
	int seed = 1;
	initializeGame(numPlayers, cards_in_game, seed, &gameState);
	memcpy(&testState, &gameState, sizeof(struct gameState));

	/* Testing the playCard() function 	*/
	printf("\nTESTING THE playCard() FUNCTION:\n\n");
	playCard(1, choice1, choice2, choice3, &testState);

	printf("\tTesting playCard() does not execute during Phase 1.\n");
	testState.phase = 1;
	if (playCard(1, choice1, choice2, choice3, &testState) == -1) {
		test_passed();
	} else if (playCard(1, choice1, choice2, choice3, &testState) != -1) {
		test_failed();

		printf("\t\tplayCard() function should have failed due to wrong phase.\n");
	}

	printf("\n");

	printf("\tTesting playCard() executes successfully during Phase 0.\n");
	testState.phase = 0;
	testState.hand[currentPlayer][4] = 7;
	if (playCard(4, choice1, choice2, choice3, &testState) == 0) {
		test_passed();
	} else if (playCard(4, choice1, choice2, choice3, &testState) != 0) {
		test_failed();

		printf("\t\tplayCard() function should be able to execute correctly in Phase 0.\n");
	}

	printf("\n");

	/* Testing that playCard() does not execute if the player has 0 actions.*/
	printf("\tTesting playCard() does not execute if player has 0 actions.\n");
	testState.numActions = 0;
	testState.hand[currentPlayer][4] = 7;
	if (playCard(4, choice1, choice2, choice3, &testState) == -1) {
		test_passed();
	}
	else if (playCard(4, choice1, choice2, choice3, &testState) != -1) {
		test_failed();

		printf("\t\tplayCard() executed with 0 available actions.\n");
	}

	printf("\n");

	/* Testing that playCard() executes if the player has 1 action.*/
	printf("\tTesting playCard() executes if the player has at least 1 action.\n");
	testState.numActions = 1;
	testState.hand[currentPlayer][4] = 7;
	if (playCard(4, choice1, choice2, choice3, &testState) == 0) {
		test_passed();
	}
	else if (playCard(4, choice1, choice2, choice3, &testState) != 0) {
		test_failed();

		printf("\t\tplayCard() failed to execute with 1 available action.\n");
	}

	printf("\n");

	/* Testing that playCard() does not execute if the passed card is not an action card. */
	printf("\tTesting playCard() does not execute if passed a non-action card.\n");
	testState.numActions = 1;
	testState.hand[currentPlayer][4] = 1;
	if (playCard(4, choice1, choice2, choice3, &testState) == -1) {
		test_passed();
	}
	else if (playCard(4, choice1, choice2, choice3, &testState) != 0) {
		test_failed();

		printf("\t\tplayCard() executed with a non-action card.\n");
	}

	printf("\n");

	/* Testing that playCard() executes if it is passed an action card. */
	printf("\tTesting playCard() executes if passed an action card.\n");
	testState.numActions = 1;
	testState.hand[currentPlayer][4] = 7;
	if (playCard(4, choice1, choice2, choice3, &testState) == 0) {
		test_passed();
	}
	else if (playCard(4, choice1, choice2, choice3, &testState) != 0) {
		test_failed();

		printf("\t\tplayCard() failed to execute with an action card.\n");
	}

	printf("\n");

	/* Testing that playCard() exits if a card returns -1. */
	printf("\tTesting playCard() exits if a card returns -1.\n");
	testState.numActions = 1;
	testState.hand[currentPlayer][4] = 10;
	if (playCard(4, choice1, choice2, choice3, &testState) == -1 && testState.numActions == 1) {
		test_passed();
	}
	else if (playCard(4, choice1, choice2, choice3, &testState) != -1 || testState.numActions != 1) {
		test_failed();

		printf("\t\tplayCard() didn't exit when a card failed and returnd -1.\n");
	}

	printf("\n");

	/* Testing that playCard() reduces remaining actions after a card is played successfully. */
	printf("\tTesting playCard() reduces actions after playing a card.\n");
	testState.numActions = 1;
	testState.hand[currentPlayer][4] = 7;
	playCard(4, choice1, choice2, choice3, &testState);
	if (testState.numActions == 0) {
		test_passed();
	}
	else if (testState.numActions != 0) {
		test_failed();

		printf("\t\tplayCard() did not decrement the number of remaining actions.\n");
	}

	printf("\n");

	/* DISCOVERED: Embargo does not correctly add bonus coins!
	** Instead, it add coins straight to the state.
	** The way updateCoins works, is it counts treasure cards and then adds bonus coins.
	** Embargo's cardEffect adds +2 coins, but in the playCard() method updateCoins is
	** called afterwards, and it re-counts the coins, excluding Embargo's +2! 
	*/

	/* Testing that playCard() successfully adds coins as a card effect. */
	printf("\tTesting playCard() adds coins as a card effect.\n");
	testState.numActions = 1;
	testState.hand[currentPlayer][4] = 22;

	int initialCoins = testState.coins;
	playCard(4, choice1, choice2, choice3, &testState);
	if (testState.coins == (initialCoins + 2)) {
		test_passed();
	}
	else if (testState.coins != (initialCoins + 2)) {
		test_failed();

		printf("\t\tplayCard() did not correctly add coins.\n");
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