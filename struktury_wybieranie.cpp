#include <iostream>
#include <string>
#include <fstream>

/* Przykladowy plik wejsciowy:
Semestr_2
5
Jan Kowalski 123123 1 2
1 Podstawy_Programowania
Alicja Brombak 123345 3 5
3 Podstawy_Programowania Metody_numeryczne Grafika_komputerowa
Krzysztof Piniak 234345 7 13
0
Jan Nowak 543123 6 12
4 Podstawy_Programowania Metody_numeryczne WF Matematyka
Barbara Kosa 243123 2 4
2 Metody_numeryczne Grafika_komputerowa

*/

using namespace std;

struct SPrzedmioty{
    string przedmiot;
};

struct SStudent{
    string imie, nazwisko;
    unsigned nr_indeksu;
    unsigned gr_dziekanska;
    unsigned gr_lab;
    unsigned liczba_przedmiotow;
    SPrzedmioty* przedmioty;
};

struct SLista{
    unsigned n;
    SStudent* zestaw;
};
inline void usun(SLista & a){
    for (unsigned i = 0; i < a.n; i++) {
        delete[] a.zestaw[i].przedmioty;
        a.zestaw[i].przedmioty=0;
    }
    delete [] a.zestaw;
    a.zestaw = 0;
}

bool wczytaj(const string nazwa_pliku, SLista & a){
    ifstream fin;
    string nazwa_listy;
    fin.open(nazwa_pliku);
    if(!fin.good()) {
        cerr << "Blad otwarcia pliku zrodlowego!";
        fin.ignore();
        fin.clear();
        fin.close();
        return false;
    }
    fin >> nazwa_listy >> a.n;
    a.zestaw = new SStudent[a.n];
    if (a.n>0){
        for(unsigned i=0;i<a.n;i++){
            fin >> a.zestaw[i].imie >> a.zestaw[i].nazwisko >> a.zestaw[i].nr_indeksu >> a.zestaw[i].gr_dziekanska >> a.zestaw[i].gr_lab >> a.zestaw[i].liczba_przedmiotow;
            a.zestaw[i].przedmioty = new SPrzedmioty[a.zestaw[i].liczba_przedmiotow];
            for (unsigned j = 0; j < a.zestaw[i].liczba_przedmiotow; j++) {
                fin >> a.zestaw[i].przedmioty[j].przedmiot;
            }
        }
    }
    fin.close();
    return true;
}

bool wypisz(const SLista& a, const unsigned nr_studenta, ostream & os){
    if(nr_studenta < a.n && nr_studenta >=0){
        os << a.zestaw[nr_studenta].imie << " " << a.zestaw[nr_studenta].nazwisko << " " << a.zestaw[nr_studenta].nr_indeksu << " "
           << a.zestaw[nr_studenta].gr_dziekanska << " " << a.zestaw[nr_studenta].gr_lab << endl;
        cout << a.zestaw[nr_studenta].liczba_przedmiotow<<endl;
        for (unsigned i=0; i < a.zestaw[nr_studenta].liczba_przedmiotow; i++){
            os << a.zestaw[nr_studenta].przedmioty[i].przedmiot << " ";
        }
        cout << endl;
        return 0;
    }else{
        cerr << "Przekroczono liczbe studentow na liscie lub podano liczbe ujemna." << endl << "Dozwolony przedzial od 0 do " << a.n-1 << endl;
        return -1;
    }

}

void wypisz(const SLista & a, ostream& os)
{
    for(unsigned i = 0; i < a.n; i++)
        wypisz(a,i,os);
}

double srednia(const SLista & a)
{
    double srednia=0;
    for(unsigned i=0; i<a.n; i++){
        srednia+=a.zestaw[i].liczba_przedmiotow;
    }
    return srednia/a.n;
}

void wyszukaj(SLista& a){
    unsigned najgorszy=0;
    for(unsigned i=0; i<a.n; i++){
        if(a.zestaw[i].liczba_przedmiotow > najgorszy){
            najgorszy=i;
        }

    }
    wypisz(a,najgorszy,cout);
}

bool filtr(SLista& a, const string nazwa){
    ofstream fout;
    fout.open(nazwa);
    if(!fout.good()){
        cerr << "Blad zapisu do pliku";
        return false;
    }
    fout << "Studenci bez zaliczenia Podstaw Programowania:\n";
    for(unsigned i=0; i<a.n; i++)
    {
        if(a.zestaw[i].liczba_przedmiotow==0){
            // Pominiecie zerowych rekordow
        }else {
            if (a.zestaw[i].przedmioty[0].przedmiot == "Podstawy_Programowania") {
                fout << a.zestaw[i].imie << " " << a.zestaw[i].nazwisko << " " << a.zestaw[i].nr_indeksu << endl;
            }
        }
    }
    fout.close();
    return true;
}

void sortuj(SLista & a, ostream & os, bool (*wfun)(SStudent, SStudent)){
    SStudent tymczasowy;
    SStudent* sortowane = new SStudent[a.n];

    for(unsigned int i = 0; i < a.n; i++)
        sortowane[i] = a.zestaw[i];
    bool zamiana = true;
    while(zamiana == true)
    {
        zamiana = false;
        for(unsigned int i = 0; i < a.n-1; i++)
        {
            if(wfun(sortowane[i],sortowane[i+1]) == true)
            {
                zamiana = true;
                tymczasowy = sortowane[i];
                sortowane[i] = sortowane[i+1];
                sortowane[i+1] = tymczasowy;
            }
        }
    }

    for(unsigned int i = 0; i < a.n; i++)
    {
        os << sortowane[i].imie << " " << sortowane[i].nazwisko << " " << sortowane[i].nr_indeksu << " "
        << sortowane[i].gr_dziekanska << " " << sortowane[i].gr_lab << endl << "Liczba kolokwiow do zaliczenia: "
        << sortowane[i].liczba_przedmiotow << endl;
        for(unsigned int j = 0; j < sortowane[i].liczba_przedmiotow; j++)
        {
            os << sortowane[i].przedmioty[j].przedmiot << " ";
        }
        os << endl << endl;
    }
    delete [] sortowane;
}

bool wg_nazwiska(SStudent s1, SStudent s2){
    if(s1.nazwisko > s2.nazwisko)
        return true;
    else
        return false;
}
bool wg_imienia(SStudent s1, SStudent s2){
    if(s1.imie > s2.imie)
        return true;
    else
        return false;
}
bool wg_indeksu(SStudent s1, SStudent s2){
    if(s1.nr_indeksu > s2.nr_indeksu)
        return true;
    else
        return false;
}
bool wg_grupyL(SStudent s1, SStudent s2){
    if(s1.gr_lab > s2.gr_lab)
        return true;
    else
        return false;
}
bool wg_grupyDz(SStudent s1, SStudent s2){
    if(s1.gr_dziekanska > s2.gr_dziekanska)
        return true;
    else
        return false;
}
bool wg_liczbyK(SStudent s1, SStudent s2){
    if(s1.liczba_przedmiotow > s2.liczba_przedmiotow)
        return true;
    else
        return false;
}
int main() {
    cout << "Program realizuje zestaw nr II" << endl << endl;
    string nazwa = "wejscie.txt"; // Plik wejsciowy zgodny z wytycznymi
    SLista studenci; // Tworzenie listy studentow
    wczytaj(nazwa, studenci); // Wczytuje dane z pliku i zapisuje do struktury
    //wypisz(studenci, -1, cout); // Wypisuje dane o drugim studencie. Zabezpieczenie na podanie wiekszej liczby lub ujemnej
    //wypisz(studenci,  cout); // Funkcja przeciazona, wypisuje wszystkich studentow uzywajac poprzedniej funkcji
    //cout << "Srednia liczba niezaliczonych przedmiotow: " << srednia(studenci) << endl; // Polecenie wyswietla srednia liczbe niezaliczonych przedmiotow
    //wyszukaj(studenci); // Funkcja wyszukuje najgorszego studenta na liscie
    filtr(studenci, "out.txt");  // Funkcja filtruje osoby, ktore maja niezaliczone Podstawy_Programowania i zapisuje do pliku out.txt wyniki
    sortuj(studenci,cout,wg_indeksu); // Funkcja sortuje (w typ przypadku wg indeksu) studentow
    usun(studenci); // Usuwanie struktury z pamieci
    return 0;
}
