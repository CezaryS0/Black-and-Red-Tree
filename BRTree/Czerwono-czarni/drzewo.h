/** @file */
#ifndef DRZEWO_H
#define DRZEWO_H
/** typ wykorzystywany w programie */
typedef double typ;
/**kolory wykorzystywane w programie */
enum Kolor{czarny = 0, czerwony=1};
/** Element drzewa Czerwono-czarnego*/
struct Drzewo
{
	typ liczba; ///< liczba wartosc przechowywana w elemencie drzewa
	Kolor kolor; ///< kolor kolor elementu w drzewie 
	Drzewo* poprz; ///< poprz adres elementu porzedniego
	Drzewo* lewy; ///< lewy adres elementu lewego
	Drzewo * prawy; ///< prawy adres elementu prawego
};
#endif // !DRZEWO_H

