/* 
    Author: Matthew Frank
    Course: CS 362
    Assignment: Assignment 4, Random Adventurer Card Testing
    Date: 05/12/2018
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Utility functions for reporting results
void test_passed();
void test_failed();
void reportTestResults();

// Utility variables for reporting results
int TESTSPASSED = 0;
int TOTALTESTS = 0;

int main() {
	int cards_in_game[10] = { adventurer, smithy, village, salvager, council_room, feast, mine, remodel, baron, great_hall };
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int handpos = 0;
	int bonus = 0;
	int numAddedCards =2;
	int numDiscardedCards = 1;
	int seed;
	int numPlayers;
	int testCounter = 0;
	int counter = 0;
	int numTests = 5000;
	struct gameState actual, test;
	srand(time(0));

	for (testCounter = 0; testCounter < numTests; testCounter++) {
		seed = (rand() % 10) + 1;
		numPlayers = (rand() % 3) + 2;

		TESTSPASSED = 0;
		TOTALTESTS = 0;

		// Initialize the actual state
		initializeGame(numPlayers, cards_in_game, seed, &actual);	

		// Randomize the hand counts and number of actions for each player
		for (counter = 0; counter < numPlayers; counter++) {
			actual.handCount[counter] = (rand() % 21) + 1; // 0 to 20
			actual.whoseTurn = counter; // Set the current player to the counter so we can randomize actions
			actual.numActions = rand() % 11; // 0 to 10
		}

		// Randomize which player will play the card
		int randomPlayer = rand() % numPlayers;
		actual.whoseTurn = randomPlayer;

		printf("Number of players: %d --- Whose turn it is: %d\n", numPlayers, randomPlayer);

		// Copy the actual state to the test state and play the Adventurer card
		memcpy(&test, &actual, sizeof(struct gameState));
		cardEffect(adventurer, choice1, choice2, choice3, &test, handpos, &bonus); 

		for (counter = 0; counter < numPlayers; counter++) {
			printf("\tTesting the number of cards in PLAYER %d's hand.\n", counter);
			// Test hand of the player who played the Adventurer card
			if (counter == randomPlayer) {
				if (test.handCount[counter] == (actual.handCount[counter] + numAddedCards - numDiscardedCards)) {
					test_passed();
				}
				else if (test.handCount[counter] != (actual.handCount[counter] + numAddedCards - numDiscardedCards))
				{
					test_failed();

					//printf("\t\tExpected Number of Cards in Hand: %d\n", (actual.handCount[counter] + numAddedCards - numDiscardedCards));
					//printf("\t\tActual Number of Cards in Hand: %d\n", test.handCount[counter]);
				}
			}
			else {
				// Test the hand of the other players
				if (test.handCount[counter] == actual.handCount[counter]) {
					test_passed();
				}
				else if (test.handCount[counter] != actual.handCount[counter]) {
					test_failed();

					//printf("\t\tExpected Number of Cards in Hand: %d\n", actual.handCount[counter]);
					//printf("\t\tActual Number of Cards in Hand: %d\n", test.handCount[counter]);
				}
			}

			printf("\n");

			// No other players should have discarded at this point, so checking that their discard piles are 0 after playing the card
			if (counter != randomPlayer) {
				printf("\tTesting the number of discarded cards in PLAYER %d's discard pile.\n", counter);
				if (test.discardCount[counter] == 0) {
					test_passed();
				}
				else if (test.discardCount[counter] != 0) {
					test_failed();

					//printf("\t\tExpected Number of Cards in Discard: %d\n", 0);
					//printf("\t\tActual Number of Cards in Discard: %d\n", test.discardCount[counter]);
				}
			}

			// Testing that none of the discarded cards by the person who played Adventurer are treasure cards
			if (counter == randomPlayer) {
				printf("\tTesting none of the cards in PLAYER %d's discard pile are treasure cards.\n", randomPlayer);
				int discardCounter = 0;
				int discardedTreasureCard = 0;
				for (discardCounter = 0; discardCounter < test.discardCount[randomPlayer]; discardCounter++) {
					if (test.discard[randomPlayer][discardCounter] == copper || test.discard[randomPlayer][discardCounter] == silver || test.discard[randomPlayer][discardCounter] == gold) {
						discardedTreasureCard = 1;
					}
				}

				if (discardedTreasureCard != 0) {
					test_failed();
				}

				if (discardedTreasureCard == 0) {
					test_passed();
				}
			}

			printf("\n");
		}

		/* For JUST the player who played the Adventurer card,
		** test that the 2 cards on the top of their hand,
		** are treasure cards.
		*/
		test.whoseTurn = randomPlayer;
		printf("\tTesting the top 2 cards in PLAYER %d's hand.\n", randomPlayer);
		int currentCard;
		char cardName[20] = "";
		for (counter = test.handCount[randomPlayer] - 2; counter < test.handCount[randomPlayer]; counter++) {
			currentCard = test.hand[randomPlayer][counter];

			if (currentCard == copper || currentCard == silver || currentCard == gold) {
				test_passed();
			}
			else {
				test_failed();

				cardNumToName(currentCard, cardName);
				printf("\t\tExpected copper, silver, or gold.\n");
				printf("\t\tActual card is: %s\n", cardName);
			}
		}

		printf("\n");
		reportTestResults();
	}

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