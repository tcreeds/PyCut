// PyCut_Pseudocode.cpp : Defines the entry point for the console application.
/*

Drop in an empty c++ project and should run ok, 
basic idea is to just get out some logic for 
creating text clues 


// Result values
0 -> correct guess
1 -> too little
2 -> too much
*/

#include <iostream>
#include <time.h>

using namespace std;

int RandomIntInRange(int min, int max)
{
	return min + (rand() % (int)(max - min + 1));
}

int ValidateGuess(int i, float toppings[4], float guesses[4])
{
	if (toppings[i] == guesses[i])
	{
		cout << "Topping " << i << " is just right" << endl;
		return 0;
	}
	else if (guesses[i] == 0.0f)
	{
		cout << "I want some of topping " << i << endl;
		return 1;
	}
	else if (toppings[i] == 0.0f)
	{
		cout << "I don't want any of topping " << i << endl;
	}
	else if (toppings[i] > guesses[i])
	{
		cout << "Topping " << i << " is too little" << endl;
		return 1;
	}
	else if (toppings[i] < guesses[i])
	{
		cout << "Topping " << i << " is too much" << endl;
		return 2;
	}
	else
	{
		cout << "Validation error!" << endl;
	}

	return 3;
}

void Clue_IsDouble(float toppings[4])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = i + 1; j < 4; j++)
		{
			if (toppings[i] == 2 * toppings[j])
			{
				cout << "I want twice as much topping " << i << " as topping " << j << endl;
			}
			else if (toppings[j] == 2 * toppings[i])
			{
				cout << "I want twice as much topping " << j << " as topping " << i << endl;
			}
		}
	}
}

void Clue_IsTripple(float toppings[4])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = i + 1; j < 4; j++)
		{
			if (toppings[i] == 3 * toppings[j])
			{
				cout << "I want tripple topping " << i << " as topping " << j << endl;
			}
			else if (toppings[j] == 3 * toppings[i])
			{
				cout << "I want tripple topping " << j << " as topping " << i << endl;
			}
		}
	}
}

void Clue_AsMuchAsTwoOthers(float toppings[4])
{
	// This one is super ugly, cleaner solution would be nice 
	for (int i = 0; i < 4; i++)
	{
		for (int a = 0; a < 3; a++)
		{
			for (int b = a + 1; b < 4; b++)
			{
				if (i != a && i != b && a != b)
				{
					if (toppings[i] == toppings[a] + toppings[b])
					{
						cout << "I want as much topping " << i << " as topping " << a << " and " << b << endl;
					}
				}
			}
		}
	}
}

void Clue_AsMuchAsTheRest(float toppings[4])
{
	for (int i = 0; i < 4; i++)
	{
		float total = 0.0f;
		for (int j = 0; j < 4; j++)
		{
			if (i != j) total += toppings[j];
		}

		if (toppings[i] == total)
		{
			cout << "I want as much topping " << i << " as everything else combined" << endl;
		}
	}
}

void Clue_AtLeastAsMuch(float toppings[4])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = i + 1; j < 4; j++)
		{
			if (toppings[i] >= toppings[j])
			{
				cout << "I want at least as much topping " << i << " as topping " << j << endl;
			}
		}
	}
}

void Clue_NoMoreThan(float toppings[4])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = i + 1; j < 4; j++)
		{
			if (toppings[i] <= toppings[j])
			{
				cout << "I want no more topping " << i << " than topping " << j << endl;
			}
		}
	}
}

int main()
{
	srand(time(NULL));

	// Fill out the toppings with random amounts 
	float toppings[4] = { 0, 0, 0, 0 };
	float amounts[5] = { 0, 0.25f, 0.5f, 0.75f, 1.0f };
	for (int i = 0; i < 4; i++)
	{
		toppings[i] = amounts[RandomIntInRange(0, 4)];
		//cout << toppings[i] << endl;
	}
	cout << endl;

	// cheese, mushrooms, pepperoni, pineapple
	float guesses[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	int results[4] = { 0, 0, 0, 0 };

	bool playGame = true;

	cout << "------" << endl;
	cout << "Hey, I would like a pizza please" << endl;
	cout << "------" << endl << endl;

	// List out all clues for now 
	cout << "------" << endl;
	cout << "CLUES: " << endl;
	Clue_IsDouble(toppings);
	Clue_IsTripple(toppings);
	Clue_AsMuchAsTwoOthers(toppings);
	Clue_AsMuchAsTheRest(toppings);
	cout << endl;

	cout << "CLUES TO LIMIT: " << endl;
	Clue_AtLeastAsMuch(toppings);
	Clue_NoMoreThan(toppings);
	cout << "------" << endl << endl;

	while (playGame)
	{
		cout << "Enter cheese amount: ";
		cin >> guesses[0];

		cout << "Enter mushrooms amount: ";
		cin >> guesses[1];

		cout << "Enter pepperoni amount: ";
		cin >> guesses[2];

		cout << "Enter pineapple amount: ";
		cin >> guesses[3];
		cout << endl;

		// Validate all guesses, mark if at least one was wrong 
		bool oneFailed = false;
		cout << "HINTS: " << endl;
		for (int i = 0; i < 4; i++)
		{
			results[i] = ValidateGuess(i, toppings, guesses);
			oneFailed = oneFailed ? true : results[i];
		}
		cout << endl;

		// End the game if they got all correct 
		if (!oneFailed)
		{
			playGame = false;
			break;
		}

		cout << "------" << endl;
		cout << "Try again" << endl;
		cout << "------" << endl << endl;
	}

	return 0;
}
