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

#define TESTCARD "smithy"

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
	int numAddedCards = 3;
	int numDiscardedCards = 1;

    int numPlayers = 4;
    int cards_in_game[10] = {adventurer, smithy, village, salvager, council_room, feast, mine, remodel, baron, great_hall};
    int seed = 1;
	initializeGame(numPlayers, cards_in_game, seed, &gameState);
	memcpy(&testState, &gameState, sizeof(struct gameState));

    /* Testing the card, specifically that:
        - Every player has the correct number of cards after someone plays Smithy
    */

	// Starting the testing run
    printf("\nTESTING THE SMITHY CARD:\n\n");
	cardEffect(smithy, choice1, choice2, choice3, &testState, handpos, &bonus);

	/* For each player, test the numbers of cards they have after someone plays the card
	** - the player who played Smithy should have +3 cards for the card effect, and -1 for their discard
	** - the other players should have +/- 0 cards, as the Smithy card doesn't affect them when another player plays it
	*/
	int a = 0;
	for (a = 0; a < numPlayers; a++) {
		printf("\tTesting the number of cards in PLAYER %d's hand.\n", a);
		
		// Test hand of the player who played the Smithy card
		if (a == currentPlayer) {
			if (testState.handCount[currentPlayer] == (gameState.handCount[currentPlayer] + numAddedCards - numDiscardedCards)) {
				test_passed();
			}
			else if (testState.handCount[currentPlayer] != (gameState.handCount[currentPlayer] + numAddedCards - numDiscardedCards))
			{
				test_failed();

				printf("\t\tExpected Number of Cards in Hand: %d\n", (gameState.handCount[currentPlayer] + numAddedCards - numDiscardedCards));
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