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

    // dodawanie nowego elementu na koncu listy
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
        // gdy nie ma jeszcze wezla
        if(korzen==NULL)
        {
            Lisc* nowy=new Lisc;

            nowy->wartosc=wartosc;
            nowy->lewy=NULL;
            nowy->prawy=NULL;

            return nowy;
        }

        // mniejsza wartosc trafia do lewej galezi
        if(wartosc<korzen->wartosc)
        {
            korzen->lewy=dodaj(korzen->lewy,wartosc);
        }

        // wieksza lub rowna wartosc trafia w prawo
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

    // przejscie po drzewie i zapis wartosci do tablicy
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

    // zwalnianie pamieci po zakonczeniu pracy
    ~drzewo()
    {
        usun(korzen);
    }
};


int main()
{
    const int ile=100000;

    // tablica przechowujaca wylosowane dane
    int liczby[ile];

    // uruchomienie generatora liczb losowych
    srand(time(NULL));

    for(int i=0;i<ile;i++)
    {
        liczby[i]=rand()%1000000;
    }


    // zmienne wykorzystywane do pomiaru czasu
    chrono::high_resolution_clock::time_point start;
    chrono::high_resolution_clock::time_point stop;


    // tablica zwykla

    int tablica[200000];

    // zapisanie pierwszych 100000 liczb
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


    // zapisanie nastepnych 100000 elementow
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        tablica[ile+i]=liczby[i];
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_tablica_kolejne=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // vector

    vector<int> v;

    // dodanie pierwszej porcji elementow
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        v.push_back(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_vector_dodawanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // sortowanie vectora
    start=chrono::high_resolution_clock::now();

    sort(v.begin(),v.end());

    stop=chrono::high_resolution_clock::now();

    auto czas_vector_sortowanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // dodanie kolejnej partii liczb
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        v.push_back(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_vector_kolejne=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);

    // kolejka FIFO

    queue<int> fifo;

    // dodawanie pierwszych elementow do kolejki
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        fifo.push(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_fifo_dodawanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // sortowanie danych znajdujacych sie w kolejce
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


    // dopisanie kolejnych 100000 liczb
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        fifo.push(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_fifo_kolejne=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);

    // stos LIFO

    stack<int> lifo;

    // umieszczenie pierwszej partii liczb na stosie
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        lifo.push(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_lifo_dodawanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // sortowanie elementow stosu
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


    // dodanie drugiej porcji danych
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        lifo.push(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_lifo_kolejne=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);

    // wlasna kolejka oparta na liscie

    uczen u;

    // dodawanie pierwszych 100000 elementow
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        u.dodaj(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_kolejka_dodawanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // sortowanie elementow kolejki
    start=chrono::high_resolution_clock::now();

    u.sort_bubble();

    stop=chrono::high_resolution_clock::now();

    auto czas_kolejka_sortowanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // dodawanie kolejnych elementow
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        u.dodaj(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_kolejka_kolejne=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // drzewo binarne

    drzewo d;

    // wstawianie pierwszych 100000 wartosci
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        d.dodaj(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_drzewo_dodawanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // pomiar czasu sortowania drzewa
    start=chrono::high_resolution_clock::now();

    d.sortuj();

    stop=chrono::high_resolution_clock::now();

    auto czas_drzewo_sortowanie=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // dodanie kolejnej grupy elementow
    start=chrono::high_resolution_clock::now();

    for(int i=0;i<ile;i++)
    {
        d.dodaj(liczby[i]);
    }

    stop=chrono::high_resolution_clock::now();

    auto czas_drzewo_kolejne=
        chrono::duration_cast<chrono::microseconds>
        (stop-start);


    // pokazanie zmierzonych czasow

    cout<<"WYNIKI POMIAROW"<<endl;

    cout<<endl;
    cout<<"Tablica zwykla:"<<endl;

    cout<<"Dodanie 100000 elementow: "
        <<czas_tablica_dodawanie.count()
        <<" us"<<endl;

    cout<<"Sortowanie: "
        <<czas_tablica_sortowanie.count()
        <<" us"<<endl;

    cout<<"Dodanie kolejnych 100000 elementow: "
        <<czas_tablica_kolejne.count()
        <<" us"<<endl;


    cout<<endl;
    cout<<"Vector:"<<endl;

    cout<<"Dodanie 100000 elementow: "
        <<czas_vector_dodawanie.count()
        <<" us"<<endl;

    cout<<"Sortowanie: "
        <<czas_vector_sortowanie.count()
        <<" us"<<endl;

    cout<<"Dodanie kolejnych 100000 elementow: "
        <<czas_vector_kolejne.count()
        <<" us"<<endl;


    cout<<endl;
    cout<<"Kolejka FIFO:"<<endl;

    cout<<"Dodanie 100000 elementow: "
        <<czas_fifo_dodawanie.count()
        <<" us"<<endl;

    cout<<"Sortowanie: "
        <<czas_fifo_sortowanie.count()
        <<" us"<<endl;

    cout<<"Dodanie kolejnych 100000 elementow: "
        <<czas_fifo_kolejne.count()
        <<" us"<<endl;


    cout<<endl;
    cout<<"Stos LIFO:"<<endl;

    cout<<"Dodanie 100000 elementow: "
        <<czas_lifo_dodawanie.count()
        <<" us"<<endl;

    cout<<"Sortowanie: "
        <<czas_lifo_sortowanie.count()
        <<" us"<<endl;

    cout<<"Dodanie kolejnych 100000 elementow: "
        <<czas_lifo_kolejne.count()
        <<" us"<<endl;


    cout<<endl;
    cout<<"Kolejka - lista linked list:"<<endl;

    cout<<"Dodanie 100000 elementow: "
        <<czas_kolejka_dodawanie.count()
        <<" us"<<endl;

    cout<<"Sortowanie: "
        <<czas_kolejka_sortowanie.count()
        <<" us"<<endl;

    cout<<"Dodanie kolejnych 100000 elementow: "
        <<czas_kolejka_kolejne.count()
        <<" us"<<endl;


    cout<<endl;
    cout<<"Drzewo binarne:"<<endl;

    cout<<"Dodanie 100000 elementow: "
        <<czas_drzewo_dodawanie.count()
        <<" us"<<endl;

    cout<<"Sortowanie: "
        <<czas_drzewo_sortowanie.count()
        <<" us"<<endl;

    cout<<"Dodanie kolejnych 100000 elementow: "
        <<czas_drzewo_kolejne.count()
        <<" us"<<endl;


    return 0;
}
