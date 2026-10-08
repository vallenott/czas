#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// lista jednokierunkowa
struct kolejka
{
    int nr;
    kolejka* nastepny;

    kolejka(int _nr)
    {
        nr=_nr;
        nastepny=NULL;
    }
};

class uczen
{
    kolejka* poczatek;
    kolejka* koniec;

public:

    // tworzenie pustej kolejki
    uczen()
    {
        poczatek=NULL;
        koniec=NULL;
    }

    // dodawanie elementu na koniec listy
    void dodaj(int nr)
    {
        kolejka* nowy=new kolejka(nr);

        if(poczatek==NULL)
        {
            poczatek=nowy;
            koniec=nowy;
        }
        else
        {
            koniec->nastepny=nowy;
            koniec=nowy;
        }
    }

    // sortowanie listy metoda babelkowa
    void sort_bubble()
    {
        if(poczatek==NULL || poczatek->nastepny==NULL)
        {
            return;
        }

        bool zamiana;
        kolejka* temp;
        kolejka* koniec_sortowania=NULL;

        do
        {
            zamiana=false;
            temp=poczatek;

            while(temp->nastepny!=koniec_sortowania)
            {
                if(temp->nr>temp->nastepny->nr)
                {
                    int t=temp->nr;

                    temp->nr=temp->nastepny->nr;

                    temp->nastepny->nr=t;

                    zamiana=true;
                }

                temp=temp->nastepny;
            }

            koniec_sortowania=temp;

        } while(zamiana);
    }

    // usuwanie wszystkich elementow listy
    ~uczen()
    {
        while(poczatek!=NULL)
        {
            kolejka* temp=poczatek;

            poczatek=poczatek->nastepny;

            delete temp;
        }

        koniec=NULL;
    }
};

// drzewo binarne
// pojedynczy wezel drzewa
struct Lisc
{
    int wartosc;

    Lisc* lewy;
    Lisc* prawy;
};

class drzewo
{
public:

    Lisc* korzen;

    // utworzenie pustego drzewa
    drzewo()
    {
        korzen=NULL;
    }

    // dodawanie elementu do drzewa
    Lisc* dodaj(Lisc* korzen, int wartosc)
    {
        if(korzen==NULL)
        {
            Lisc* nowy=new Lisc;

            nowy->wartosc=wartosc;
            nowy->lewy=NULL;
            nowy->prawy=NULL;

            return nowy;
        }

        if(wartosc<korzen->wartosc)
        {
            korzen->lewy=dodaj(korzen->lewy,wartosc);
        }
        else
        {
            korzen->prawy=dodaj(korzen->prawy,wartosc);
        }

        return korzen;
    }

    void dodaj(int wartosc)
    {
        korzen=dodaj(korzen,wartosc);
    }

    // przejscie po drzewie i zapisanie wartosci
    void przejdz(Lisc* korzen, vector<int>& tab)
    {
        if(korzen==NULL)
        {
            return;
        }

        przejdz(korzen->lewy,tab);

        tab.push_back(korzen->wartosc);

        przejdz(korzen->prawy,tab);
    }

    // sortowanie elementow drzewa
    void sortuj()
    {
        vector<int> tab;

        przejdz(korzen,tab);

        sort(tab.begin(),tab.end());
    }

    // usuwanie wezlow drzewa
    void usun(Lisc* korzen)
    {
        if(korzen==NULL)
        {
            return;
        }

        usun(korzen->lewy);

        usun(korzen->prawy);

        delete korzen;
    }

    // zwalnianie pamieci
    ~drzewo()
    {
        usun(korzen);
    }
};

int main()
{
    const int ile=100000;

    // tablica z wylosowanymi liczbami
    int liczby[ile];

    srand(time(NULL));

    for(int i=0;i<ile;i++)
    {
        liczby[i]=rand()%1000000;
    }

    // zmienne do mierzenia czasu
    chrono::high_resolution_clock::time_point start;
    chrono::high_resolution_clock::time_point stop;

    // =========================================================
    // TABLICA
    // =========================================================

    int tablica[200000];

    // dodanie pierwszych 100000 elementow
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        tablica[i]=liczby[i];
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_tablica_dodawanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);

    // sortowanie tablicy
    start=chrono::high_resolution_clock::now();

    sort(tablica,tablica+ile);

    stop=chrono::high_resolution_clock::now();

    auto czas_tablica_sortowanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);

    // dodanie kolejnych 100000 elementow
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        tablica[ile+i]=liczby[i];
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_tablica_kolejne=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);

    // =========================================================
    // VECTOR
    // =========================================================

    vector<int> v;

    // pomiar pierwszego elementu
    start=chrono::high_resolution_clock::now();

    v.push_back(liczby[0]);

    stop=chrono::high_resolution_clock::now();

    auto czas_vector_pierwszy=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);

    // dodanie pozostalych 99999 elementow
    start=chrono::high_resolution_clock::now();

    for(int i=1;i<ile;i++)
    {
        v.push_back(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_vector_pozostale=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);

    // sortowanie vectora
    start=chrono::high_resolution_clock::now();

    sort(v.begin(),v.end());

    stop=chrono::high_resolution_clock::now();

    auto czas_vector_sortowanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);

    // dodanie kolejnych 100000 elementow
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        v.push_back(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_vector_kolejne=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);

    // =========================================================
    // KOLEJKA FIFO
    // =========================================================

    queue<int> fifo;

    // pomiar pierwszego elementu
    start=chrono::high_resolution_clock::now();

    fifo.push(liczby[0]);

    stop=chrono::high_resolution_clock::now();

    auto czas_fifo_pierwszy=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);

    // dodanie pozostalych 99999 elementow
    start=chrono::high_resolution_clock::now();

    for(int i=1;i<ile;i++)
    {
        fifo.push(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_fifo_pozostale=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);

    // sortowanie kolejki
    start=chrono::high_resolution_clock::now();

    vector<int> fifo_sort;

    while(!fifo.empty())
    {
        fifo_sort.push_back(fifo.front());

        fifo.pop();
    }

    sort(fifo_sort.begin(),fifo_sort.end());

    for(int i=0;i<ile;i++)
    {
        fifo.push(fifo_sort[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_fifo_sortowanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);

    // dodanie kolejnych 100000 elementow
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        fifo.push(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_fifo_kolejne=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);

    // =========================================================
    // STOS LIFO
    // =========================================================

    stack<int> lifo;

    // pomiar pierwszego elementu
    start=chrono::high_resolution_clock::now();

    lifo.push(liczby[0]);

    stop=chrono::high_resolution_clock::now();

    auto czas_lifo_pierwszy=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);

    // dodanie pozostalych 99999 elementow
    start=chrono::high_resolution_clock::now();

    for(int i=1;i<ile;i++)
    {
        lifo.push(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_lifo_pozostale=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);

    // sortowanie stosu
    start=chrono::high_resolution_clock::now();

    vector<int> lifo_sort;

    while(!lifo.empty())
    {
        lifo_sort.push_back(lifo.top());

        lifo.pop();
    }

    sort(lifo_sort.begin(),lifo_sort.end());

    for(int i=0;i<ile;i++)
    {
        lifo.push(lifo_sort[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_lifo_sortowanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);

    // dodanie kolejnych 100000 elementow
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        lifo.push(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_lifo_kolejne=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);

    // =========================================================
    // WLASNA KOLEJKA LINKED LIST
    // =========================================================

    uczen u;

    // dodanie pierwszych 100000 elementow
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        u.dodaj(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_kolejka_dodawanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);

    // sortowanie kolejki
    start=chrono::high_resolution_clock::now();

    u.sort_bubble();

    stop=chrono::high_resolution_clock::now();

    auto czas_kolejka_sortowanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);

    // dodanie kolejnych 100000 elementow
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        u.dodaj(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_kolejka_kolejne=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);

    // =========================================================
    // DRZEWO BINARNE
    // =========================================================

    drzewo d;

    // dodanie pierwszych 100000 elementow
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        d.dodaj(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_drzewo_dodawanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);

    // sortowanie drzewa
    start=chrono::high_resolution_clock::now();

    d.sortuj();

    stop=chrono::high_resolution_clock::now();

    auto czas_drzewo_sortowanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);

    // dodanie kolejnych 100000 elementow
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        d.dodaj(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_drzewo_kolejne=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);

    // =========================================================
    // WYNIKI
    // =========================================================

    cout<<"WYNIKI POMIAROW CZASU"<<endl;

    cout<<endl;
    cout<<"Tablica zwykla:"<<endl;

    cout<<"Dodawanie 100000: "
        <<czas_tablica_dodawanie.count()
        <<" us"<<endl;

    cout<<"Sortowanie: "
        <<czas_tablica_sortowanie.count()
        <<" us"<<endl;

    cout<<"Dodawanie kolejnych 100000: "
        <<czas_tablica_kolejne.count()
        <<" us"<<endl;

    cout<<endl;
    cout<<"VECTOR:"<<endl;

    cout<<"Pierwszy element: "
        <<czas_vector_pierwszy.count()
        <<" us"<<endl;

    cout<<"Pozostale 99999 elementow: "
        <<czas_vector_pozostale.count()
        <<" us"<<endl;

    cout<<"Pierwsze 100000 razem: "
        <<czas_vector_pierwszy.count()+czas_vector_pozostale.count()
        <<" us"<<endl;

    cout<<"Sortowanie: "
        <<czas_vector_sortowanie.count()
        <<" us"<<endl;

    cout<<"Kolejne 100000: "
        <<czas_vector_kolejne.count()
        <<" us"<<endl;

    cout<<endl;
    cout<<"KOLEJKA FIFO:"<<endl;

    cout<<"Pierwszy element: "
        <<czas_fifo_pierwszy.count()
        <<" us"<<endl;

    cout<<"Pozostale 99999 elementow: "
        <<czas_fifo_pozostale.count()
        <<" us"<<endl;

    cout<<"Pierwsze 100000 razem: "
        <<czas_fifo_pierwszy.count()+czas_fifo_pozostale.count()
        <<" us"<<endl;

    cout<<"Sortowanie: "
        <<czas_fifo_sortowanie.count()
        <<" us"<<endl;

    cout<<"Kolejne 100000: "
        <<czas_fifo_kolejne.count()
        <<" us"<<endl;

    cout<<endl;
    cout<<"STOS LIFO:"<<endl;

    cout<<"Pierwszy element: "
        <<czas_lifo_pierwszy.count()
        <<" us"<<endl;

    cout<<"Pozostale 99999 elementow: "
        <<czas_lifo_pozostale.count()
        <<" us"<<endl;

    cout<<"Pierwsze 100000 razem: "
        <<czas_lifo_pierwszy.count()+czas_lifo_pozostale.count()
        <<" us"<<endl;

    cout<<"Sortowanie: "
        <<czas_lifo_sortowanie.count()
        <<" us"<<endl;

    cout<<"Kolejne 100000: "
        <<czas_lifo_kolejne.count()
        <<" us"<<endl;

    cout<<endl;
    cout<<"KOLEJKA LINKED LIST:"<<endl;

    cout<<"Dodawanie 100000: "
        <<czas_kolejka_dodawanie.count()
        <<" us"<<endl;

    cout<<"Sortowanie: "
        <<czas_kolejka_sortowanie.count()
        <<" us"<<endl;

    cout<<"Dodawanie kolejnych 100000: "
        <<czas_kolejka_kolejne.count()
        <<" us"<<endl;

    cout<<endl;
    cout<<"DRZEWO BINARNE:"<<endl;

    cout<<"Dodawanie 100000: "
        <<czas_drzewo_dodawanie.count()
        <<" us"<<endl;

    cout<<"Sortowanie: "
        <<czas_drzewo_sortowanie.count()
        <<" us"<<endl;

    cout<<"Dodawanie kolejnych 100000: "
        <<czas_drzewo_kolejne.count()
        <<" us"<<endl;

    return 0;
}
