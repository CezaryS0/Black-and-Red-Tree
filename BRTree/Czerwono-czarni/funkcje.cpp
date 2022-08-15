/** @file */
#include "funkcje.h"
#include "nvwa/debug_new.h"
void PrintUsage(char*nazwa)
{
	std::cout << "Usage: " << nazwa << " -i <input_file> " << std::endl; //wypisywanie sposobu u¿ycia aplikacji 
}
bool Parsuj(int argc,char** argv, Parametr& p)
{
	for (int i = 0; i < argc - 1; ++i) //pêtla pobierajaca argumenty 
	{
		std::string arg = argv[i];
		if (arg == "-i")
		{ 
			p.plik_we = argv[++i]; //zapisanie argumentu do struktury Parametr
			return true;//zwroc prawdê w przypadku istnienia argumentu
		}
	}
	return false; //zwroæ fa³sz w przypadku braku argumentu
}
void dodaj(Drzewo*&korzen,Drzewo*s,std::string komenda,std::ifstream&plik)
{
	std::streamoff poz, poz2;
	typ liczba;
	poz = plik.tellg(); //pobór aktulanej pozycji w pliku tekstowym
	while (plik >> liczba); //pêtla pobieraj¹ca dane a¿ do pierwszego b³edu lub do konca pliku 
	if (plik.fail()) //jesli wyst¹pi³ b³ad lub skoczy³ siê plik
	{
		plik.clear(); //czyœæ flagi
		poz2 = plik.tellg(); //
		plik >> komenda;	 // -- pobiera kolejny znak w celu sprawdzenia czy b³edem by³a nastêpna komenda, komentarz, lub coœ innego 
		plik.seekg(poz2);	 //	 
		plik.clear();
		if (komenda != "%" && komenda != "add" && komenda != "graph" && komenda != "remove" && komenda != "print") //jeœli nie komentarz i nie nastepna komenda to ignoruj
			return;
		plik.seekg(poz); //przywrócenie pozycji w pliku tekstowym do pierwszego argumentu komendy
		while (plik >> liczba) // odczytuje kolejne liczby 
			add(korzen, s, liczba); //dodawanie do drzewa
	}
}
void usun(Drzewo*& korzen, Drzewo* s, std::string komenda, std::ifstream& plik)
{
	std::streamoff poz, poz2;
	typ liczba;
	poz = plik.tellg(); //pobór aktulanej pozycji w pliku tekstowym
	while (plik >> liczba); //pêtla pobieraj¹ca dane a¿ do pierwszego b³edu lub do konca pliku 
	if (plik.fail()) //jesli wyst¹pi³ b³ad lub skoczy³ siê plik
	{
		plik.clear(); //czyœæ flagi
		poz2 = plik.tellg(); //
		plik >> komenda;	 // -- pobiera kolejny znak w celu sprawdzenia czy b³edem by³a nastêpna komenda, komentarz, lub coœ innego 
		plik.seekg(poz2);	 //	 
		plik.clear();
		if (komenda != "%" && komenda != "add" && komenda != "graph" && komenda != "remove" && komenda != "print") //jeœli nie komentarz i nie nastepna komenda to ignoruj
			return;
		plik.seekg(poz); //przywrócenie pozycji w pliku tekstowym do pierwszego argumentu komendy
		while (plik >> liczba) // odczytuje kolejne liczby 
		{
			auto p = znajdz(korzen, s, liczba); //znajduje element w drzewie
			remove(korzen, p, s); //usuwanie elementu z drzewa
		}
	}
}
void wypisz_rosnaco(Drzewo*& korzen, Drzewo* s, std::string komenda, std::ifstream& plik)
{
	std::streamoff poz;
	std::ofstream zapis;
	poz = plik.tellg();  //pobór aktulanej pozycji w pliku tekstowym
	plik >> komenda; //pobranie kolejnego napisu
	if (komenda == "+") // jesli + to znaczy dopisywanie do pliku
	{
		plik >> komenda; // pobór nazwy pliku do zapisu
		if (komenda != "%") //jesli nie ma komentarza 
		{
			zapis.open(komenda, std::ios_base::app); //otworz plik do zapisu
			if (zapis.is_open()) // jesli plik otwarty
			{
				print(korzen, s, zapis); //zapisz do pliku elementy drzewa rosnaco
				zapis << std::endl;
				zapis.close(); //zamknij plik
			}
		}
	}
	else if (!plik.fail() && (komenda != "add" && komenda != "graph" && komenda != "remove" && komenda != "print" && komenda != "%"))
		//jesli nie ma + i nie plik sie nie skonczyl i nastepny naspis nie jest komenda 
	{
		zapis.open(komenda); //otworz do zapisu 
		print(korzen, s, zapis); //zapisz do pliku rosnaco
		zapis << std::endl;
		plik.seekg(poz);
		zapis.close();
	}
	else
	{
		print(korzen, s, std::cout); //wypisz rosnaco
		plik.seekg(poz);
		std::cout << std::endl;
	}
}
void rysuj_graf(Drzewo*& korzen, Drzewo* s, std::string komenda, std::ifstream& plik)
{
	std::streamoff poz;
	std::ofstream zapis;
	poz = plik.tellg();  //pobór aktulanej pozycji w pliku tekstowym
	plik >> komenda; //pobranie kolejnego napisu
	if (komenda == "+") // jesli + to znaczy dopisywanie do pliku
	{
		plik >> komenda; // pobór nazwy pliku do zapisu
		if (komenda != "%") //jesli nie ma komentarza 
		{
			zapis.open(komenda, std::ios_base::app); //otworz plik do zapisu
			if (zapis.is_open()) // jesli plik otwarty
			{
				graph(korzen, s, zapis,4); //zapisz do pliku elementy drzewa rosnaco
				zapis << std::endl;
				zapis.close(); //zamknij plik
			}
		}
	}
	else if (!plik.fail() && (komenda != "add" && komenda != "graph" && komenda != "remove" && komenda != "print" && komenda != "%"))
		//jesli nie ma + i nie plik sie nie skonczyl i nastepny naspis nie jest komenda 
	{
		zapis.open(komenda); //otworz do zapisu 
		graph(korzen, s, zapis,4); //zapisz do pliku rosnaco
		zapis << std::endl;
		plik.seekg(poz);
		zapis.close();
	}
	else
	{
		graph(korzen, s, std::cout,4); //wypisz rosnaco
		plik.seekg(poz);
		std::cout << std::endl;
	}
}
void Wykonaj(Parametr&p)
{
	Drzewo s; //deklaracja wêz³a stra¿nika
	Drzewo* korzen=nullptr; //deklaracja wskaŸnika na korzen drzewa 
	s.lewy = &s;
	s.prawy = &s;
	s.poprz = &s;
	s.kolor = czarny; //straznik powinien byæ czarny gdy¿ bedzie liœciem 
	korzen = &s; //na pocz¹tku gdy w drzewie nie ma elementów korzeiem jest wezel stra¿nika
	std::string komenda="";
	std::ifstream plik(p.plik_we); // otwarcie pliku do odczytu
	while (plik >> komenda) //pêtla pobieraj¹ca argumenty 
	{
		if (komenda == "add")
			dodaj(korzen, &s, komenda, plik);
		else if (komenda == "remove")
			usun(korzen, &s, komenda, plik);
		else if (komenda == "print")
			wypisz_rosnaco(korzen, &s, komenda, plik);
		else if (komenda == "graph")
			rysuj_graf(korzen, &s, komenda, plik);
		plik.clear(); //wyczysc flagi pliku
	}
	plik.close(); //zamknij plik
	usun_Drzewo(korzen, &s); //zwolnij pamiec usuwaj¹c drzewo
}
void add(Drzewo*&korzen,Drzewo*s,typ n)
{
	Drzewo* x=nullptr;
	if (korzen == s)
	{
		korzen = new Drzewo{ n,czarny,s,s,s };
		x = korzen;
	}
	else
	{
		auto d = korzen;
		while (1)
		{
			if (n < d->liczba)
			{
				if (d->lewy != s)
					d = d->lewy;
				else
				{
					d->lewy = new Drzewo{ n,czerwony,d,s,s };
					x = d->lewy;
					break;
				}
			}
			else
			{

				if (d->prawy != s)
					d = d->prawy;
				else
				{
					d->prawy = new Drzewo{ n,czerwony,d,s,s };
					x = d->prawy;
					break;
				}
			}
		}
	}
	Drzewo* p = x;
	przywroc_dodaj(korzen, s, x);
}
void przywroc_dodaj(Drzewo*& korzen, Drzewo* s, Drzewo* p)
{
	while (p != korzen && p->poprz->kolor == czerwony) //petla przywracaj¹ca warunki drzewa czerwono-czarnego 
	{
		if (p->poprz == p->poprz->poprz->lewy) //sprawdzenie czy wezel jest z lewej strony wzgledem dziadka
		{
			//przypadki konieczne do rozpatrzenia 
			auto d = p->poprz->poprz->prawy;
			if (d->kolor == czerwony) // przypadek 1: wujek jak i ojciec wezla s¹ czerwoni
			{
				p->poprz->kolor = czarny; //zamien ojca na czarno
				d->kolor = czarny; // zamien wujka na czarno
				p->poprz->poprz->kolor = czerwony; //zamien dziadka na czerwono
				p = p->poprz->poprz; //zamien p na dziadka w celu dalszego sprawdzenia drzewa 
			}
			else
			{
				if (p == p->poprz->prawy) //przypadek 2: wujek jest czarny, a ojciec jest czerwony i wezel jest jego prawym synem
				{
					p = p->poprz; //ustaw p na ojca wezla  
					rotacjaLewo(korzen, p, s); //wykonaj rotacje w lewo wzgledem ojca 
				}
				//przypadek 3: wujek jest czarny ale ojciec jest czerwony i wezel jest jego lewym synem
				p->poprz->kolor = czarny; //zamien ojca na czarno, jest to jego kolor przeciwny
				p->poprz->poprz->kolor = czerwony; //zamien dziadka na czerwono, jest to jego kolor przeciwny
				rotacjaPrawo(korzen, p->poprz->poprz, s); //wykonaj rotacje w prawo wzgledem dziadka
				//break;
			}
		}
		else  //wezel jest z prawej strony wzgledem dziadka
		{
			//przypadki lustrzane
			auto d = p->poprz->poprz->lewy;
			if (d->kolor == czerwony) // przypadek 1: wujek jak i ojciec wezla s¹ czerwoni
			{
				p->poprz->kolor = czarny; //zamien ojca na czarno
				d->kolor = czarny; // zamien wujka na czarno
				p->poprz->poprz->kolor = czerwony; //zamien dziadka na czerwono
				p = p->poprz->poprz; //zamien p na dziadka w celu dalszego sprawdzenia drzewa 
			}
			else
			{
				if (p == p->poprz->lewy) //przypadek 2: wujek jest czarny, a ojciec jest czerwony i wezel jest jego lewym synem
				{
					p = p->poprz; //ustaw p na ojca wezla  
					rotacjaPrawo(korzen, p, s); //wykonaj rotacje w prawo wzgledem ojca 
				}
				//przypadek 3: wujek jest czarny ale ojciec jest czerwony i wezel jest jego lewym synem
				p->poprz->kolor = czarny;  //zamien ojca na czarno, jest to jego kolor przeciwny
				p->poprz->poprz->kolor = czerwony; //zamien dziadka na czerwono, jest to jego kolor przeciwny
				rotacjaLewo(korzen, p->poprz->poprz, s); //wykonaj rotacje w lewo wzgledem dziadk
			}
		}
	}
	korzen->kolor = czarny; //korzen zawsze powinien byc czarny*/
}
void rotacjaPrawo(Drzewo*&korzen,Drzewo*wezel,Drzewo*s)
{
	Drzewo* p = wezel->lewy;
	if ( p==s)
		return;
	wezel->lewy = p->prawy; //
	if (wezel->prawy != s)// 
		p->prawy->poprz = wezel;// utwierdzenie polaczenia
	p->poprz = wezel->poprz; //laczenie zrootem 
	if (wezel->poprz == s)
		korzen = p;
	else if (wezel == wezel->poprz->prawy)
		wezel->poprz->prawy = p;
	else
		wezel->poprz->lewy = p;
	p->prawy = wezel;
	wezel->poprz = p;
}
void rotacjaLewo(Drzewo*& korzen, Drzewo* wezel, Drzewo* s)
{
	
	Drzewo* p = wezel->prawy;

	if (p == s)
		return;
	wezel->prawy = p->lewy;
	if (p->lewy != s)
		p->lewy->poprz = wezel;
	p->poprz = wezel->poprz;
	if (wezel->poprz == s)
		korzen = p;
	else if (wezel == wezel->poprz->lewy)
		wezel->poprz->lewy = p;
	else
		wezel->poprz->prawy = p;
	p->lewy = wezel;
	wezel->poprz = p;
}
Drzewo* min(Drzewo*&korzen,Drzewo*s)
{
	auto p = korzen;
	if (p!= s)
	{
		while (p->lewy != s) //petla znajdujaca minimum
			p = p->lewy;
	}
	return p;
}
Drzewo* zastepstwo(Drzewo* wezel,Drzewo*s)
{
	if (wezel != s)
	{
		if (wezel->prawy != s) //jesli wezel prawy nie jest pusty to nastepnikiem bedzie najmniejsza wartosc, najglebszy lewy
			return min(wezel->prawy, s);
		else //w przeciwnym wypadku przejdz wyzej 
		{

			auto p = wezel;
			auto b = wezel->poprz;
			while ((b != s) && (p == b->prawy))
			{
				p = b;
				b = b->poprz;
			}
			return b;
		}
	}
	return s;
}
Drzewo*znajdz(Drzewo*korzen,Drzewo*s,typ liczba)
{
	if (korzen == s)
		return nullptr;
	while (korzen != s && korzen->liczba != liczba) //petla wyszukujaca element w drzewie
	{
		if (liczba < korzen->liczba)
			korzen = korzen->lewy;
		else
			korzen = korzen->prawy;
	}
	if(korzen==s) 
		return nullptr;
	return korzen;
}
void remove(Drzewo*&korzen,Drzewo*&wezel,Drzewo*s)
{
	Drzewo*a,*b,*c;
	if (korzen == s || wezel == nullptr)
		return;
	if (wezel->lewy == s || wezel->prawy == s) //sprawdza czy ktoryœ z kolejnych wezlow jest pusty
		a = wezel; // na a ustawia usuwany wezel 						  
	else   
		a = zastepstwo(wezel, s); // w przeciwnym wypadku ustawia nastepnika 			  

	if (a->lewy != s) // jesli lewy nie jest pusty to wybiera go lewego syna usuwanego elementu
		b = a->lewy;
	else
		b= a->prawy; // w przeciwnym wypadku prawego
	b->poprz = a->poprz; //ojcem b musi zostac a
	if (a->poprz == s) //jesli poprzednik a jest pusty znaczy sie ze a musi byc korzeniem
		korzen = b;
	else if (a == a->poprz->lewy) //jesli a jest lewym synem
		a->poprz->lewy = b; //to b jest teraz lewym synem  wezla usuwanego
	else
		a->poprz->prawy = b; //to b jest teraz prawym synem  wezla usuwanego
	if (a != wezel) //jesli a nie jest usuwanym wezlem to przenosimy liczbe za do wezla
		wezel->liczba = a->liczba;
	if (a->kolor == czarny)
		przywroc_usun(korzen, s, b);
	b->kolor = czarny;
	delete a;
	a = nullptr;
}
void przywroc_usun(Drzewo*& korzen, Drzewo* s, Drzewo* b)
{
	Drzewo* c = nullptr;
	while ((b != korzen) && (b->kolor == czarny))
	{
		if (b == b->poprz->lewy)
		{
			c = b->poprz->prawy;
			if (c->kolor == czerwony)
			{
				c->kolor = czarny;
				b->poprz->kolor = czerwony;
				rotacjaLewo(korzen, b->poprz, s);
				c = b->poprz->prawy;
			}
			if ((c->lewy->kolor == czarny) && (c->prawy->kolor == czarny))
			{
				c->kolor = czerwony;
				b = b->poprz;
				continue;
			}
			if (c->prawy->kolor == czarny)
			{
				c->lewy->kolor = czarny;
				c->kolor = czerwony;
				rotacjaPrawo(korzen, c, s);
				c = b->poprz->prawy;
			}
			c->kolor = b->poprz->kolor;
			b->poprz->kolor = czarny;
			c->prawy->kolor = czarny;
			rotacjaLewo(korzen, b->poprz, s);
			b = korzen; //zakonczenie petli
		}
		else
		{
			c = b->poprz->lewy;
			if (c->kolor == czerwony)
			{
				c->kolor = czarny;
				b->poprz->kolor = czerwony;
				rotacjaPrawo(korzen, b->poprz, s);
				c = b->poprz->lewy;
			}
			if ((c->lewy->kolor == czarny) && (c->prawy->kolor == czarny))
			{
				c->kolor = czerwony;
				b = b->poprz;
				continue;
			}
			if (c->lewy->kolor == czarny)
			{
				c->prawy->kolor = czarny;
				c->kolor = czerwony;
				rotacjaLewo(korzen, c, s);
				c = b->poprz->lewy;
			}
			c->kolor = b->poprz->kolor;
			b->poprz->kolor = czarny;
			c->lewy->kolor = czarny;
			rotacjaPrawo(korzen, b->poprz, s);
			b = korzen; //zakonczenie petli
		}
	}
}
void graph(Drzewo* korzen,Drzewo*s,std::ostream& stream, long long int wciecie)
{
	if (korzen!=s)
	{
		graph(korzen->prawy, s,stream,wciecie + 1);
		if(korzen->kolor==czarny)
			stream << std::setw(4 * wciecie) <<"["<< korzen->liczba <<"]" << std::endl;
		else
			stream << std::setw(4 * wciecie) << "(" << korzen->liczba << ")" << std::endl;
		graph(korzen->lewy, s,stream,wciecie + 1);
	}
}
void print(Drzewo*korzen,Drzewo*s, std::ostream& stream)
{
	if (korzen!=s)
	{
		print(korzen->lewy,s,stream);
		stream << korzen->liczba<<" ";
		print(korzen->prawy,s,stream);
	}
}
void usun_Drzewo(Drzewo*& korzen,Drzewo*s)
{
	if (korzen != s)
	{
		usun_Drzewo(korzen->lewy, s);
		usun_Drzewo(korzen->prawy, s);
		delete korzen;
		korzen = nullptr;
	}

}
