#include <iostream>
#include <time.h>
using namespace std;
/*11/30/2020
This program is a battle arena game that pits two creatures against each other.
There are four different creatures (Human, Balrog, CyberDemon and Elf). In each round
there is a chance that a creature will trigger the special attribute which allows them
to deal more damage*/

class Creature {
private:
	// 0 human, 1 cyberdemon, 2 balrog, 3 elf
	int strength;   // How much damage we can inflict
	int hitpoints;  // How much damage we can sustain
	virtual string getSpecies(); // Returns type of species, for Creature class
	                     // returns “unKnown”
public:
	Creature(); // Initialize to  10 strength, 10 hit points
	Creature(int newStrength, int newHit);
	// Initialize creature to strength, hit points
	virtual int getDamage();
	// Returns amount of damage this creature
   // inflicts in one round of combat
	int GetStrength() { return strength; }
	int GetHitpoints() { return hitpoints; }
	string GetSpecies() { return getSpecies(); }
	void SetStrength(int strengthToSet) { strength = strengthToSet; }
	void SetHitpoints(int hpToSet) { hitpoints = hpToSet; }
	// Also add appropriate accessor and mutator functions
	// for strength, and hit points
};

//default constructor
//inherited throughout the classes
Creature::Creature() {
	strength = 10;
	hitpoints = 10;
}

//overloaded constructor
//inherited throughout the classes
Creature::Creature(int newStrength, int newHit) {
	strength = newStrength;
	hitpoints = newHit;
}

string Creature::getSpecies()
{
	return "Unknown";
}

//initial damage dealt by each creature
//is invoked by each creature getDamage()
int Creature::getDamage()
{
	int damage;
	// All creatures inflict damage which is a
	// random number up to their strength
	damage = (rand() % strength) + 1;
	cout << getSpecies() << " attacks for " <<
		damage << " points!" << endl;

	return damage;
}

//Human class definition inheriting from Creature
class Human : public Creature {
private:
	string getSpecies() override { return "Human"; }
public:
	Human() : Creature() {}
	Human(int strength, int hp) : Creature(strength, hp) {}
};

//Elf class definition inheriting from Creature
class Elf : public Creature {
private:
	string getSpecies() override { return "Elf"; }
public:
	Elf() : Creature() {}
	Elf(int strength, int hp) : Creature(strength, hp) {}
	int getDamage() override;
};

//invokes initial getDamage() from creature class
//has a chance to trigger special attribute
//adds total damage dealt and returns it
int Elf::getDamage() {

	int damage = Creature::getDamage();

	// Elves inflict double magical damage with a 10% chance
	if ((rand() % 10) == 0)
	{
		cout << "Magical attack inflicts " << damage <<
			" additional damage points!" << endl;
		damage = damage * 2;
	}

	return damage;
}

//Demon class definition inheriting from Creature
class Demon : public Creature {
public:
	int getDamage() override;
	Demon() : Creature() {}
	Demon(int strength, int hp) : Creature(strength, hp) {}
};

//invokes initial getDamage() from creature class
//has a chance to trigger special attribute
//adds total damage dealt and returns it
int Demon::getDamage() {

	int damage = Creature::getDamage();

	// Demons can inflict damage of 50 with a 5% chance
	if ((rand() % 100) < 5)
	{
		damage = damage + 50;
		cout << "Demonic attack inflicts 50 "
		<< " additional damage points!" << endl;
	}

	return damage;
}

//Balrog class definition inheriting from Demon
class Balrog : public Demon {
private:
	string getSpecies() override { return "Balrog"; }
public:
	int getDamage() override;
	Balrog() : Demon() {}
	Balrog (int strength, int hp) : Demon(strength, hp) {}
};

//invokes initial getDamage() from demon class
//has a chance to trigger special attribute
//adds total damage dealt and returns it
int Balrog::getDamage() {

	int damage = Demon::getDamage();

	// Balrogs are so fast they get to attack twice
	{
		int damage2 = (rand() % GetStrength()) + 1;
		cout << "Balrog speed attack inflicts " << damage2 <<
			" additional damage points!" << endl;
		damage = damage + damage2;
	}

	return damage;
}

//CyberDemon class definition inheriting from Demon
class CyberDemon : public Demon {
private:
	string getSpecies() override { return "Balrog"; }
public:
	CyberDemon() : Demon() {}
	CyberDemon(int strength, int hp) : Demon(strength, hp) {}

};

//Battle arena standalone function
//Lets two creatures fight until one or both have negative hitpoints
void battleArena(Creature& creature1, Creature& creature2) {

	bool fighting = true;
	int remainingHp1 = creature1.GetHitpoints();
	int remainingHp2 = creature2.GetHitpoints();

	while (fighting) {

		remainingHp1 -= creature2.getDamage();
		cout << creature1.GetSpecies() << " has " << remainingHp1 << " HP left" << endl;

		remainingHp2 -= creature1.getDamage();	 	
		cout << creature2.GetSpecies() << " has " << remainingHp2 << " HP left" << endl;

		//nested if block executes when a creature's hp is negative
		//this will set the condition for the while loop to false
		//then, it will check which creature won
		if (remainingHp1 < 0 || remainingHp2 < 0) {
			fighting = false;
			if (remainingHp1 < 0 && remainingHp2 < 0){
				cout << creature1.GetSpecies() << " and " << creature2.GetSpecies() 
				<< " both have negative hitpoints. It's a draw!" << endl;
			}
			else if (remainingHp1 < 0) {
				cout << creature1.GetSpecies() << " has negative hitpoints "
					<< creature2.GetSpecies() << " wins!" << endl;
			}
			else if (remainingHp2 < 0) {
				cout << creature2.GetSpecies() << " has negative hitpoints "
					<< creature1.GetSpecies() << " wins!" << endl;
			}
		}
	}
}

int main() {

	srand(static_cast<int>(time(NULL)));
	Human human1(30, 10);
	human1.getDamage();
	cout << endl;
	Elf elf1;
	elf1.getDamage();
	cout << endl;
	Balrog balrog1(50, 50);;
	balrog1.getDamage();
	cout << endl;
	CyberDemon cdemon(30, 40);
	cdemon.getDamage();
	cout << endl;
	Elf elf2(50, 50);
	Balrog balrog2(50, 50);
	cout << endl;
	battleArena(elf2, balrog2);
}

/* SAMPLE RUN
Human attacks for 29 points!

Elf attacks for 5 points!

Balrog attacks for 26 points!
Balrog speed attack inflicts 49 additional damage points!

Balrog attacks for 18 points!


Balrog attacks for 37 points!
Balrog speed attack inflicts 2 additional damage points!
Elf has 11 HP left
Elf attacks for 16 points!
Balrog has 34 HP left
Balrog attacks for 7 points!
Balrog speed attack inflicts 11 additional damage points!
Elf has -7 HP left
Elf attacks for 36 points!
Balrog has -2 HP left
Elf and Balrog both have negative hitpoints. It's a draw!
*/