/** @file */

#ifndef FUNKCJE_H
#define FUNKCJE_H
#include "drzewo.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

/** Struktura przechowująca argument pliku*/
struct Parametr
{
	std::string plik_we; ///< plik_we nazwa pliku z ktorgo należy odczytać dane
};
/**  Funkcja znajdujacą następnika dla węzła
@param wezel wezeł dla którego ma znalezć następnika
@param s wskaźnik na węzeł strażnika
@return wskaźnik do węzła następnika
*/
Drzewo* zastepstwo(Drzewo* wezel, Drzewo* s);

/** Funkcja wypisująca sposob użycia na standardowe wyjście
@param nazwa wskaźnik do tablicy char z nazwą programu
*/
void PrintUsage(char*nazwa);
/** Funkcja przepisuje argumenty programu do struktury Parametr
@param argc liczba argumentów
@param argv wskaźnik do tablicy dwuwymiarowej przechwującej argumenty programu
@param p referencja do struktury do której będą wpisane argumenty programu
@return wartość logiczna: 1 - przekazano bezbłędnie, 0 - przekazano z błędem
*/
bool Parsuj(int argc, char** argv, Parametr& p);
/** Funkcja wykonująca główne zadanie programu 
@param p referencja do struktury przechowującej argument programu
*/
void Wykonaj(Parametr& p);
/** Funkcja dodająca do drzewa nowy element 
@param korzen wskaźnik na korzeń drzewa
@param s wskaźnik na węzeł strażnika
@param n liczba do dodania
*/
void add(Drzewo*& korzen, Drzewo* s, typ n);
/** Funkcja przesuwająca elementy drzewa o jeden w prawo względem podanego węzła
@param korzen wskaźnik na korzeń drzewa
@param wezel wskaźnik na węzeł względem którego nastąpi przesuwanie
@param s wskaźnik na węzeł strażnika
*/
void rotacjaPrawo(Drzewo*& korzen, Drzewo* wezel, Drzewo* s);
/** Funkcja usuwająca podany element z drzewa
@param korzen korzeń wskaźnik na korzeń drzewa
@param wezel wskaźnik na węzeł do usunięcia
@param s wskaźnik na węzeł strażnika
*/
void remove(Drzewo*& korzen, Drzewo*& wezel, Drzewo* s);
/** Funkcja znajdująca węzeł o podanym elemencie
@param korzen wskaźnik na korzeń drzewa
@param s wskaźnik na węzeł straźnika
@param liczba liczba do znalezienia
@return wskaźnik na znaleziony element
*/
Drzewo* znajdz(Drzewo* korzen, Drzewo* s, typ liczba);
/** Funkcja wypisująca graf drzewa
@param korzen wskaźnik na korzeń drzewa
@param s wskaźnik na węzeł strażnika
@param stream strumień wyjściowy (zapis do pliku lub na standardowe wyjście)
@param wciecie wcięcie z z jakim wypisać graf
*/
void graph(Drzewo* korzen, Drzewo* s, std::ostream&stream, long long int wciecie);
/** Funkcja wypisująca elementy drzewa rosnąco
@param korzen wskaźnik na korzeń drzewa
@param s wskaźnik na węzeł strażnika
@param stream strumień wyjściowy (zapis do pliku lub na standardowe wyjście)
*/
void print(Drzewo* korzen, Drzewo* s, std::ostream& stream);
/** Funkcja usuwająca drzewo z pamięci
@param korzen wskaźnik na korzeń drzewa
@param s wskaźnik na węzeł strażnika
*/
void usun_Drzewo(Drzewo*& korzen, Drzewo* s);
/** Funkcja przesuwająca elementy drzewa o jeden w lewo względem podanego
@param korzen wskaźnik na korzeń drzewa
@param wezel wskaźnik na węzeł strażnika
@param s wskaźnik na węzeł straznika
*/
void rotacjaLewo(Drzewo*& korzen, Drzewo* wezel, Drzewo* s);
/** Funkcja znajdująca węzeł z minimalnym elementem
@param korzen wskaźnik na korzeń drzewa
@param s wskaźnik na węzeł strażnika
@return wskaźnik na znaleziony element
*/
Drzewo* min(Drzewo*& korzen, Drzewo* s);
/** Funkcja odczytująca dane do dodania
@param korzen wskaźnik na korzeń drzewa
@param s wskaźnik na węzeł strażnika
@param komenda łańcuch znaków z danymi
@param plik strumień wyjściowy z pliku z danymi
*/
void dodaj(Drzewo*& korzen, Drzewo* s, std::string komenda, std::ifstream& plik);
/** Funkcja odczytująca dane do usunięcia
@param korzen wskaźnik na korzeń drzewa
@param s wskaźnik na węzeł strażnika
@param komenda łańcuch znaków z danymi
@param plik strumień wejściowy z pliku z danymi
*/
void usun(Drzewo*& korzen, Drzewo* s, std::string komenda, std::ifstream& plik);
/** Funkcja odczytująca dane do wypisania rosnąco
@param korzen wskaźnik na korzeń drzewa
@param s wskaźnik na wezel strażnika
@param komenda łańcuch znaków z danymi
@param plik strumień wyjściowy z pliku z danymi
*/
void wypisz_rosnaco(Drzewo*& korzen, Drzewo* s, std::string komenda, std::ifstream& plik);
/** Funkcja odczytująca dane do narysowania
@param korzen wskaźnik na korzeń drzewa
@param s wskaźnik na węzeł straźnika
@param komenda łańcuch znaków z danymi
@param plik strumień wejściowy z pliku z danymi
*/
void rysuj_graf(Drzewo*& korzen, Drzewo* s, std::string komenda, std::ifstream& plik);
/** Funkcja przywracąjaca warunki drzewa po dodaniu
@param korzen wskaźnik na korzeń drzewa
@param s wskaźnik na wezel straznika
@param p wskaźnik na węzeł dodany
*/
void przywroc_dodaj(Drzewo*& korzen, Drzewo* s, Drzewo* p);
/** Funkcja przywracająca warunki drzewa po usunięciu
@param korzen wskaźnik na korzeń drzewa
@param s wskaźnik na wezel straznika
@param b wskaźnik na lewego lub prawego syna węzzła usuwanego
*/
void przywroc_usun(Drzewo*& korzen, Drzewo* s, Drzewo* b);
#endif // !FUNKCJE_H

