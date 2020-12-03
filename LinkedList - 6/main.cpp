#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "LinkedList.h"
using namespace std;

//MAIN
int main() {

	ifstream inFile;
	inFile.open("composers.txt");

	int SIZE = getNumberOfComposers(inFile);
	Composers* compPtr = new Composers[SIZE];
	createDatabase(compPtr, inFile, SIZE);

	inFile.close();

	LinkedList<Composers> composerList;

	//creates nodes for the list which
	//holds Composer objects and their data
	for (int i = 0; i < SIZE; i++) {
		composerList.insert(compPtr[i]);
	}

	//deletes Composer objects in heap since
	//all of them were copied into nodes of the list
	delete[] compPtr;

	//User inputs to be used in main
	//searchFor.name will be used for the string input
	char choice = '\0';
	Composers searchFor;

	//will keep on iterating until user chooses to exit
	//input validation is completely applied so there will be
	//no invalid inputs at all
	while (choice != 'e') {
		choice = processInput(choice, searchFor, composerList);
	}
}

/*===================PART 1 SAMPLE RUN==================================
The list is empty
appending 1, 5, 9, 13
1 5 9 13
prepending -1 & -2
-2 -1 1 5 9 13
inserting 3 & 7
-2 -1 1 3 5 7 9 13
removing front
-1 1 3 5 7 9 13
removing 1, 5, 9, 13
-1 3 7
finding 7
7 was found
getting first and last value
-1
====================PART 2 SAMPLE RUN====================================
Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: x

			   INVALID INPUT

Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: z

			   INVALID INPUT

Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: laskdl

			   INVALID INPUT

Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: 103

			   INVALID INPUT

Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: d
 Claudio Monteverdi - 1643
 Henry Purcell - 1695
 Antonio Vivaldi - 1741
 Johann Sebastian Bach - 1750
 George Frideric Handel - 1759
 Wolfgang Amadeus Mozart - 1791
 Joseph Haydn - 1809
 Ludwig van Beethoven - 1827
 Franz Schubert - 1828
 Felix Mendelssohn - 1847
 Frederic Chopin - 1849
 Robert Schumann - 1856
 Hector Berlioz - 1869
 Richard Wagner - 1883
 Franz Liszt - 1886
 Pyotr Ilyich Tchaikovsky - 1893
 Johannes Brahms - 1897
 Giuseppe Verdi - 1901
 Antonin Dvorak - 1904
 Edvard Grieg - 1907
 Gustav Mahler - 1911
 Claude Debussy - 1918
 Camille Saint-Saens - 1921
 Giacomo Puccini - 1924
 Maurice Ravel - 1937
 George Gershwin - 1937
 Sergei Rachmaninoff - 1943
 Bela Bartok - 1945
 Arnold Schoenberg - 1951
 Sergei Prokofiev - 1953
 Igor Stravinsky - 1971
 Dmitri Shostakovich - 1975
 Aaron Copland - 1990
 Leonard Bernstein - 1990
Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: s
Enter a composers name to search for: wagner

			   Richard Wagner was found in the list

Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: s
Enter a composers name to search for: ilyich

			   Pyotr Ilyich Tchaikovsky was found in the list

Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: s
Enter a composers name to search for: some random dude

			   some random dude was not found

Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: r
Enter a composer's name to remove: ShostaKoVich

			   Dmitri Shostakovich was successfully removed from the list

Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: r
Enter a composer's name to remove: bartok

			   Bela Bartok was successfully removed from the list

Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: r
Enter a composer's name to remove: bernstein

			   Leonard Bernstein was successfully removed from the list

Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: r
Enter a composer's name to remove: monteverdi

			   Claudio Monteverdi was successfully removed from the list

Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: d
 Henry Purcell - 1695
 Antonio Vivaldi - 1741
 Johann Sebastian Bach - 1750
 George Frideric Handel - 1759
 Wolfgang Amadeus Mozart - 1791
 Joseph Haydn - 1809
 Ludwig van Beethoven - 1827
 Franz Schubert - 1828
 Felix Mendelssohn - 1847
 Frederic Chopin - 1849
 Robert Schumann - 1856
 Hector Berlioz - 1869
 Richard Wagner - 1883
 Franz Liszt - 1886
 Pyotr Ilyich Tchaikovsky - 1893
 Johannes Brahms - 1897
 Giuseppe Verdi - 1901
 Antonin Dvorak - 1904
 Edvard Grieg - 1907
 Gustav Mahler - 1911
 Claude Debussy - 1918
 Camille Saint-Saens - 1921
 Giacomo Puccini - 1924
 Maurice Ravel - 1937
 George Gershwin - 1937
 Sergei Rachmaninoff - 1943
 Arnold Schoenberg - 1951
 Sergei Prokofiev - 1953
 Igor Stravinsky - 1971
 Aaron Copland - 1990
Enter 's' to search, 'r' to remove, 'd' to display, or 'e' to exit: e

			   Exiting...

*/