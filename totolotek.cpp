#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

/*
 * Program służy do symulacji gier typu toto-lotek. Dane pobierane są z pliku, którego struktura znajduje się poniżej
 *
 * Przykładowy plik wejściowy:

Rafal 4
Lotto 6
5 7 8 9 10 6
Multi 10
2 6 9 10 34 7 8 12 15 9
Multi 10
31 32 33 34 35 36 37 38 39 40
Mini 5
2 50 3 4 49

 * Program przyjmuje 2 dodatkowe parametry obowiązkowe: plik_wejściowy.txt plik_wyjsciowy.txt
 */

struct SKupon {
	/*
	 * Struktura reprezentuje nazwę gry, liczbę możliwych skreśleń oraz wskaźnik na skreślenia
	 */
    std::string gra;
    unsigned l_skreslen;
    unsigned* skreslenia;
};

struct SGracz {
	/*
	 * Struktura z polami reprezentującymi imię gracza, liczbę skreślonych przez niego kuponów oraz wskaźnik na kupony
	 */
    std::string imie;
    unsigned l_kuponow;
    SKupon* kupony;
};

bool wczytaj(std::ifstream& fin, SGracz& g) {
	/*
	 * Funkcja umożliwia wczytanie danych o obiekcie typu SGracz ze strumienia plikowego.
	 * Funkcja zwraca true, gdy wszystko będzie w porządku.  W przypadku stwierdzenia błędu
	 * zwróci false.
	 * Funkcja przyjmuje jako argumenty referencję na obiekt fin typu ifstream oraz referencję na typ SGracz
	 */
    if(!fin.good()){ // Sprawdzenie, czy plik otwiera się poprawnie
        std::cerr << "Blad otwarcia pliku wejsciowego!";
        return false;
    }
	// Odczyt danych z pliku
    fin >> g.imie >> g.l_kuponow;
    g.kupony = new SKupon [g.l_kuponow]; // Rezerwacja pamięci na kupony
	//Dalsze wczytywanie danych z pliku
    for(unsigned i = 0; i < g.l_kuponow; i++) {
        fin >> g.kupony[i].gra >> g.kupony[i].l_skreslen;
        g.kupony[i].skreslenia = new unsigned [g.kupony[i].l_skreslen];
        for(unsigned j = 0; j < g.kupony[i].l_skreslen; j++) {
            fin >> g.kupony[i].skreslenia[j];
        }
    }
    fin.close(); // Zamknięcie pliku
    return true;
}

void wypisz(std::ostream& str, const SKupon& k) {
	/*
	 * Funkcja nic nie zwracająca, wypisuje na dowolny strumień informacje o kuponie
	 * Funkcja przyjmuje jako argumenty referencję na typ ostream str oraz referencję na obiekt typu SKupon
	 */
    str << std::endl << k.gra << std::endl << "Liczba skreslen: " << k.l_skreslen << std::endl;
    for(unsigned i = 0; i < k.l_skreslen; i++)
        str << k.skreslenia[i] << " ";
}

void wypisz(std::ostream& str, const SGracz* g) {
	/*
	 * Funkcja przeciążona wypisz, wypisująca na dowolny strumień informacje o graczu, korzystając z funkcji
	 * wypisz do wypisania pojedynczego kuponu
	 * Funkcja przyjmuje jako argumenty typ strumienia str oraz wskaźnk na stały obiekt typu SGracz
	 */
    str << g->imie << ' ' << g->l_kuponow;
    for(unsigned i = 0; i < g->l_kuponow; i++){
        str << std::endl;
        wypisz(str,g->kupony[i]);
    }
}

unsigned zlicz(const SGracz* g, const std::string gra) {
	/*
	 * Funkcja zwraca wartość całkowitą dodatnią oznaczającą liczbę skreślonych kuponów
	 * Funkcja przyjmuje jako argumenty wskaźnik na stały obiekt typu SGracz oraz ciąg znaków gra - nazwa gry
	 */
    unsigned suma=0; // zmienna pomocnicza
    for(unsigned i = 0; i < g->l_kuponow; i++) {
	    if (g->kupony[i].gra == gra) suma++;
    }
    return suma;
}

void usun(SGracz& g) {
	/*
	 * Funkcja zwalniająca zasoby na stercie z argumentem przekazanym przez wskaźnik
	 */
    for (unsigned i = 0; i < g.l_kuponow; i++) {
        delete[] g.kupony[i].skreslenia;
    }
    delete[] g.kupony;
    g.kupony = nullptr;
}

unsigned losuj(const unsigned a, const unsigned b) {
	/*
	 * Funkcja losująca zwracająca liczby całkowite z przedziału wyznaczonego przez największą i najmniejszą
	 * możliwą do skreślenia w danej grze liczbę
	 * Funkcja zwraca wylosowaną wartość całkowitą bez znaku
	 * Funkcja przyjmuje argumenty a i b - najmniejsza i największa liczba całkowita bez znaku do wylosowania
	 */
    unsigned losowa = rand() % (b-a+1) + a;
    return losowa;
}

unsigned* losowanie(const unsigned n, const unsigned a, const unsigned b) {
	/*
	 * Funkcja wypełniająca tablicę liczbami całkowitymi zwróconymi przez funkcję losuj. Wylosowane liczby nie mogą
	 * się powtarzać. Funkcja zwraca wskaźnik na typ całkowity bez znaku i przyjmuje jako argumenty:
	 * n = stała liczba całkowita - stanowi długość tablicy
	 * a = najmniejsza liczba w losowaniu
	 * b = największa liczba w losowaniu
	 */
    unsigned* t=new unsigned [n], s;
    for(unsigned i = 0; i < n; i++) {
        t[i] = losuj(a,b);
        do{
            s=0;
            for(unsigned j = 0; j < i; j++) {
                if (t[i] == t[j]) {
                    t[i] = losuj(a, b);
                    s++;
                }
            }
        }while(s!=0);
    }
    return t;
}

void wypisz(const unsigned* t, const unsigned n, std::ostream& str = std::cout) {
	/*
	 * Funkcja przeciążona umożliwiająca wypisanie na dowolny strumień wyjściowy informacji o wypełnionej tablicy
	 * (wylosowane liczby dla wybranej gry)
	 * Funkcja przyjmuje jako argumenty wskaźnik na tablicę stałych obiektów typu całkowitego bez znaku,
	 * stałą wartość typu całkowitego bez znaku - n - długość tablicy,
	 * referencję na typ ostream z argumentem domyślnym cout - wyświetlenie w konsoli.
	 * Funkcja nic nie zwraca
	 */
    for(unsigned i = 0; i < n; i++) {
        str << t[i] << '\t';
    }
    str << std::endl;
}
unsigned* sprawdz(const SGracz& g, const std::string gra, const unsigned* t, const unsigned n, const unsigned z) {
	/*
	 * Funkcja zwraca wskaźnik na obiekty typu całkowitego bez znaku
	 * Sprawdza liczbę trafień dla każdego kuponu w wybranej grze.
	 * Przyjmuje jako argumenty referencję na stały obiekt typu SGracz,
	 * stały ciąg znaków z nazwą gry,
	 * wskaźnik na tablicę stałych obiektów całkowitych bez znaku,
	 * stałą liczbę całkowitą bez znaku n - długość tablicy
	 * stałą liczbę całkowitą bez znaku z -
	 */
    unsigned trafienia, *tt=new unsigned[z]; // tt = tablica trafień
    std::cout << "Trafienia: " << std::endl;
    for(unsigned i = 0, l=0; i < g.l_kuponow; i++) {
        if(g.kupony[i].gra == gra) {
            trafienia=0;
            for(unsigned j = 0; j < n; j++) {
                for(unsigned k = 0; k < n; k++) {
	                if (g.kupony[i].skreslenia[j] == t[k]) trafienia++;
                }
            }
            tt[l] = trafienia;
			l++;
        }
    }
    return tt;
}

void usun(const unsigned * t) {
	/*
	 * Funkcja zwalniająca zasoby na stercie
	 */
    delete [] t;
}

bool wg_liczb(const unsigned a, const unsigned b) {
	/*
	 * Funkcja orzekająca zwracająca wartość porównania dwóch liczb
	 */
	if (a < b)
		return true;
	else
		return false;

}

void sortuj(SGracz& g, bool (*fun)(const unsigned a, const unsigned b)) {
	/*
	 * Funkcja nic nie zwracająca, służy do sortowania malejąco skreślone liczby we wszystkich grach
	 * danego gracza według zadanego kryterium (wskaźnik na funkcję orzekającą)
	 * Funkcja przyjmuje jako argumenty referencję na obiekt typu SGracz (g) oraz
	 * wskaźnik na funkcję orzekającą
	 */
    unsigned temp;
    for(unsigned i = 0; i < g.l_kuponow; i++) {
        for(unsigned j = 0; j < g.kupony[i].l_skreslen - 1; j++) {
            for(unsigned k = 0; k < g.kupony[i].l_skreslen - j - 1; k++) {
                if(fun(g.kupony[i].skreslenia[k], g.kupony[i].skreslenia[k + 1])) {
                    temp = g.kupony[i].skreslenia[k];
                    g.kupony[i].skreslenia[k] = g.kupony[i].skreslenia[k + 1];
                    g.kupony[i].skreslenia[k + 1] = temp;
                }
            }
        }
    }
}

int main(int argc, char ** argv) {
    if(argc!=3) {
		/*
		 * Zabezpieczenie przed błędną ilością argumentów
		 */
        std::cerr << "Nie podano nazwy pliku wejsciowego i wyjsciowego jako argumenty uruchomienia programu lub podano nieprawidlowa liczbe argumentow"<< std::endl
             << "Prawidlowe uruchomienie zawiera nazwe programu oraz nazwe pliku wejsciowego i wyjsciowego!";
        return -10;
    }

// KOD TESTUJĄCY PROGRAM
    std::ifstream fin(argv[1]);
    SGracz gracz;
    if(wczytaj(fin, gracz)){
        wypisz(std::cout, &gracz);
        std::ofstream fout(argv[2]);
//
        srand (time(NULL));

        wypisz(fout, &gracz);
        unsigned z = zlicz(&gracz, "Multi");
        std::cout << z << std::endl;
//
        std::cout << "Liczba kuponow MULTI: " << z << std::endl;
        unsigned* t = losowanie(10, 1, 80);
        wypisz(t, 10);
        unsigned int* wynik = sprawdz(gracz, "Multi", t, 10, z);
        wypisz(wynik, z);

        usun(wynik);
        usun(t);
//
        z = zlicz(&gracz, "Lotto");
        std::cout << "Liczba kuponow LOTTO: " << z << std::endl;
        t = losowanie(6, 1, 49);
        wypisz(t, 6);
        wynik = sprawdz(gracz, "Lotto", t, 6, z);
        wypisz(wynik, z);
        usun(t);
        usun(wynik);
//
        z = zlicz(&gracz, "Mini");
        std::cout << "Liczba kuponow MINI: " << z << std::endl;
        t = losowanie(5, 1, 45);
        wypisz(t, 5);
        wynik = sprawdz(gracz, "Mini", t, 5, z);
        wypisz(wynik, z);
        sortuj(gracz, wg_liczb);
	    std::cout << "Liczby skreslone posortowane:" << std::endl;
        wypisz(std::cout, &gracz);
        usun(wynik);
        usun(t);
    }
    fin.close();
    usun(gracz);
    return 0;
}
