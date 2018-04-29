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

#define TESTCARD "village"

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
    int handpos = 0;
    int bonus = 0;
    struct gameState gameState, testState;

	int currentPlayer = 0;
	int cardsAdded = 1;
	int cardsDiscarded = 1;
	int actionsAdded = 2;

    int numPlayers = 4;
    int cards_in_game[10] = {adventurer, smithy, village, salvager, council_room, feast, mine, remodel, baron, great_hall};
    int seed = 1;
	initializeGame(numPlayers, cards_in_game, seed, &gameState);
	memcpy(&testState, &gameState, sizeof(struct gameState));

    /* Testing the card, specifically that:
        - Every player has the correct number of cards after someone plays Village
		- The player who played Village has the correct number of actions after playing the Village card
    */

	// Starting the testing run
    printf("\nTESTING THE VILLAGE CARD:\n\n");
	cardEffect(village, choice1, choice2, choice3, &testState, handpos, &bonus);

	/* For each player, test the numbers of cards they have after someone plays the Village Card
	** - the player who played Village should have +1 cards for the card effect, and -1 for their discard
	** - the other players should have +/-0 cards, as the Village card doesn't affect them when another player plays it
	*/
	int a = 0;
	for (a = 0; a < numPlayers; a++) {
		printf("\tTesting the number of cards in PLAYER %d's hand.\n", a);

		// Check the number of cards in the hand of the player who played the Village card
		if (a == currentPlayer) {
			if ((testState.handCount[currentPlayer]) == (gameState.handCount[currentPlayer] + cardsAdded - cardsDiscarded)) {
				test_passed();
			}
			else if ((testState.handCount[currentPlayer]) != (gameState.handCount[currentPlayer] + cardsAdded - cardsDiscarded)) {
				test_failed();

				printf("\t\tExpected Number of Cards in Hand: %d\n", (gameState.handCount[currentPlayer] + cardsAdded - cardsDiscarded));
				printf("\t\tActual Number of Cards in Hand: %d\n", testState.handCount[currentPlayer]);
			}
		}
		else {
			// Test the hand of the other players
			if (testState.handCount[a] == gameState.handCount[a]) {
				test_passed();
			}
			else if (testState.handCount[a] != gameState.handCount[a]) {
				test_failed();

				printf("\t\tExpected Number of Cards in Hand: %d\n", gameState.handCount[a]);
				printf("\t\tActual Number of Cards in Hand: %d\n", testState.handCount[a]);
			}
		}

		printf("\n");
	}

	/* For JUST the current player, test the numbers of actions remaining after playing the Village card.
	** The player should have +2 actions for the card effect. 
	**
	** NOTE: We do NOT subtract -1 Actions for playing the Village card because this action is taken in the
	** playCard() function AFTER cardEffect() is called.  Decrementing the number of actions for playing
	** a card is NOT part of the card's effect.
	**
	** The others players do not need to be tested as actions are tracked per player turn in the game state.
	*/
	printf("\tTesting the number of actions for PLAYER %d\n", currentPlayer);
	if ((testState.numActions) == (gameState.numActions + actionsAdded)) {
		test_passed();
	} 
	/* We hard-code in the number of actions used by playing the Great Hall card,
	** as the number of actions is reduced AFTER cardEffect() is called inside the
	** playCard() function.  We know each action card costs -1 Action, so it's
	** acceptable to hard-code the simulation.
	*/
	else if ((testState.numActions) != (gameState.numActions + actionsAdded)) {
		test_failed();

		printf("\t\tExpected Number of Actions: %d\n", (gameState.numActions + actionsAdded));
		printf("\t\tActual Number of Actions: %d\n", (testState.numActions));
	}
	else {
		printf("Outside case check: \n\n");

		printf("Test State Actions: %d\n", testState.numActions);
		printf("Game State Actions: %d\n", gameState.numActions);
		printf("Actions Added: %d\n", actionsAdded);
	}

	printf("\n");

	// Reports the test results and exit
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