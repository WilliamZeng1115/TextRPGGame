#include <iostream>
#include <string>
#include <random>
#include <ctime>

using namespace std;

int main() {

	default_random_engine randomGenerator(time(0));
	uniform_int_distribution<int> nextMove(10, 50);
	uniform_int_distribution<int> nextEnemy(1, 20);
	uniform_int_distribution<int> randomEnemy(1, 3);
	uniform_int_distribution<int> runAway(1, 100);
	uniform_int_distribution<int> search(1, 100);
	uniform_int_distribution<int> block(1, 10);

	int playerHealth = 100;
	int playerDamage = 10;
	int playerHack = 0;
	int playerPos = 500;


	while ( playerPos > 0 && playerHealth > 0) {
		string action = "";
		string monster = "";
		int Damage = 0;
		int Health = 0;

		cout << "You are " << playerPos << " from destination" << endl;
		cout << "Make your next action: move or search" << endl;
		getline(cin, action);
		if (action == "move") {
			cout << "Moving. . ." << endl;
			playerPos = playerPos - nextMove(randomGenerator);
		}

		else if (action == "search") {
			cout << "Searching. . ." << endl;
			int temp = search(randomGenerator);
			if (temp < 50) {
				cout << "nothing was found" << endl;
			}
			else if (temp < 75) {
				cout << "found an sword enchantment" << endl;
				playerDamage += 1;
				cout << "Damage increase by 1" << endl;
			}
			else if (temp == 100) {
				cout << "GG POWEROVER 9000" << endl;
				playerHack = 9001;
				cout << "have 1 super attack dealing over 9000" << endl;
				playerHealth = 100;
				playerDamage += 5;
			}
		}
		else {
			continue;
		}

		if (nextEnemy(randomGenerator) < 6) {
			int enemy = randomEnemy(randomGenerator);
			switch (enemy) {
			case 1:
				monster = "Warrior";
				Damage = 10;
				Health = 20;
				break;
			case 2:
				monster = "Archer";
				Damage = 5;
				Health = 10;
				break;
			case 3:
				monster = "Berserk";
				Damage = 20;
				Health = 25;
				break;
			default:
				monster = "";
				Damage = 0;
				Health = 0;
				break;
			}
		}

		if (monster != "") {
			cout << "A " << monster << " block your path" << endl;
			cout << "fight or run" << endl;
			bool run = false;
			bool valid = true;
			while (valid) {
				getline(cin, action);

				if (action == "run") {
					valid = false;
					int temp = runAway(randomGenerator);
					if (temp > 75) {
						run = true;
					}
					else {
						cout << "fail to run" << endl;
						cout << "You lost " << Damage << " from " << monster << endl;
						playerHealth -= Damage;
						cout << "current health is " << playerHealth << endl;
						valid = true;
					}
				}

				if (run == false && action == "fight") {
					valid = false;
					string fight = "";
					cout << "You decided to fight" << endl;
					while (Health > 0) {
						cout << "block or attack" << endl;
						getline(cin, fight);
						if (fight == "block") {
							int blockTemp = block(randomGenerator);
							int temp = Damage - blockTemp;
							if (temp < 0)
								temp = 0;
							playerHealth -= temp;
							playerHealth += 4;
							cout << "You recovered 4 hp" << endl;
							cout << "You took " << temp << " from the " << monster << endl;
						}
						else if (fight == "attack") {
							if (playerHack > 9000) {
								Health -= playerHack;
								cout << "BOOOOOOOOOOOOOOM" << endl;
							}
							playerHealth -= Damage;
							cout << "You dealt " << playerDamage << endl;
							Health -= playerDamage;
							cout << "You took " << Damage << endl;
						}
						else continue;

						if (playerHealth <= 0) {
							cout << "You lost" << endl;
							return 0;
						}
						cout << "player health remaining " << playerHealth << endl;
						cout << monster << " health " << Health << endl;
					}
					cout << "Nice!!" << endl;
				}
				else if (action != "fight" && action != "run") {
					cout << "Invalid action" << endl;

				}
			}

			if (run == true) {
				cout << "Successfully ran away" << endl;
			}

		}
		cout << endl;
	}
	return 0;
}