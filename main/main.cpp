#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <cwchar>
#include <typeinfo>

#define _WIN32_WINNT 0x0502

#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#define DISABLE_NEWLINE_AUTO_RETURN 0x0008

using namespace std;

struct console
{
public:
    console(unsigned width, unsigned height)
    {
        SMALL_RECT r;
        COORD c;
        hConOut = GetStdHandle( STD_OUTPUT_HANDLE );
        if (!GetConsoleScreenBufferInfo( hConOut, &csbi ))
            throw runtime_error("");

        r.Left   =
            r.Top = 0;
        r.Right = width -1;
        r.Bottom = height -1;
        SetConsoleWindowInfo( hConOut, TRUE, &r );

        c.X = width;
        c.Y = height;
        SetConsoleScreenBufferSize(hConOut, c);
    }

    ~console()
    {
        SetConsoleTextAttribute(hConOut, csbi.wAttributes);
        SetConsoleScreenBufferSize( hConOut, csbi.dwSize);
        SetConsoleWindowInfo(hConOut, TRUE, &csbi.srWindow);
    }

    void color(WORD color = 0x07)
    {
        SetConsoleTextAttribute(hConOut, color);
    }

    HANDLE hConOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
};

console con(200, 10000);

// Declarare contoarelor
unsigned int NumarActori = 1, NumarPiese = 1, NumarBilete = 1, NumarSali = 1, NumarPersonalTeatru = 1, NumarSpectatori = 1, NumarPersonaje = 1;
unsigned int copie_ID_Sala_Max = 0, copie_ID_Actor_Max = 0, copie_ID_Piesa_Max = 0;

/// Declarare structuri de date
struct sala
{
public:
    unsigned int ID_Sala;
    unsigned int Nr_Scaune;
    unsigned int Nr_Scaune_Loja;
} salaTeatru[11];

struct actor
{
public:
    unsigned int ID_Actor;
    unsigned int ID_Piesa;
    char Nume_Actor[101];
    char Prenume_Actor[101];
    unsigned int Varsta_Actor;
    char Email_Actor[101];
    char CNP_Actor[15];
    char Sex_Actor;
} actorTeatru[1001];

struct piesa
{
public:
    unsigned int ID_Piesa;
    unsigned int ID_Sala;
    char Nume_Piesa[101];
    char Data_Piesa[11];
    char Ora_Piesa[6];
} piesaTeatru[201];

struct personaj_piesa
{
public:
    unsigned int ID_Piesa;
    unsigned int ID_Actor;
    char Nume_Personaj[201];
} personajPiesa[401];

struct bilet
{
public:
    unsigned int ID_Bilet;
    float Pret_Bilet;
    char Tip_Bilet[41];
} biletPiesa[6];

struct personal
{
public:
    unsigned int ID_PersonalTeatru;
    char Nume_PersonalTeatru[101];
    char Prenume_PersonalTeatru[101];
    char CNP_PersonalTeatru[15];
    unsigned int Varsta_PersonalTeatru;
    char Functie_PersonalTeatru[101];

} personalTeatru[101];

struct spectator
{
public:
    unsigned int ID_Spectator;
    unsigned int ID_Bilet;
    unsigned int ID_Piesa;
} spectatorPiesa[401];

// Functii ajutatoare
void fillLinieConsola(const unsigned int vWidth)
{
    cout << setw(5 - 2) << " ";

    char fillLine;
    fillLine = cout.fill('_');
    cout.width(vWidth);
    cout << '_' << endl;
    cout.fill(fillLine);
    cout << endl;
}

/// Citire date din fisier
void citire_sali()
{
    ifstream fisierSala("sala.txt"); // fisier sali teatru
    while (fisierSala >> salaTeatru[NumarSali].ID_Sala >> salaTeatru[NumarSali].Nr_Scaune >> salaTeatru[NumarSali].Nr_Scaune_Loja)
    {
        copie_ID_Sala_Max = salaTeatru[NumarSali].ID_Sala;
        NumarSali++;
    }
    NumarSali--;
    fisierSala.close();
}

void citire_actori()
{
    ifstream fisierActor("actor.txt"); // fisier actori care joaca in piesele de teatru
    while (fisierActor >> actorTeatru[NumarActori].ID_Actor >> actorTeatru[NumarActori].ID_Piesa >> actorTeatru[NumarActori].Nume_Actor
            >> actorTeatru[NumarActori].Prenume_Actor >> actorTeatru[NumarActori].Varsta_Actor >> actorTeatru[NumarActori].Email_Actor
            >> actorTeatru[NumarActori].CNP_Actor >> actorTeatru[NumarActori].Sex_Actor)
    {
        copie_ID_Actor_Max = actorTeatru[NumarActori].ID_Actor;
        NumarActori++;
    }

    NumarActori--;
    fisierActor.close();
}

void citire_piese()
{
    ifstream fisierPiesa("piesa.txt"); // fisier cu piesele care urmeaza sa fie jucate in urmatoarea saptamana
    while (fisierPiesa >> piesaTeatru[NumarPiese].ID_Piesa >> piesaTeatru[NumarPiese].ID_Sala >> piesaTeatru[NumarPiese].Data_Piesa >> piesaTeatru[NumarPiese].Ora_Piesa)
    {
        copie_ID_Piesa_Max = piesaTeatru[NumarPiese].ID_Piesa;
        fisierPiesa.get();
        fisierPiesa.get(piesaTeatru[NumarPiese].Nume_Piesa, 101);
        NumarPiese++;
    }
    NumarPiese--;
    fisierPiesa.close();
}

void citire_personaje_piese()
{
    ifstream fisierPersonaj("personaj.txt"); // fisier cu personajele din fiecare piesa de teatru
    while (fisierPersonaj >> personajPiesa[NumarPersonaje].ID_Piesa >> personajPiesa[NumarPersonaje].ID_Actor)
    {
        fisierPersonaj.get();
        fisierPersonaj.get(personajPiesa[NumarPersonaje].Nume_Personaj, 201);
        NumarPersonaje++;
    }
    NumarPersonaje--;
    fisierPersonaj.close();
}

void citire_bilete()
{
    ifstream fisierBilet("bilet.txt"); // fisier cu tipurile de bilete disponibile la teatru
    while (fisierBilet >> biletPiesa[NumarBilete].ID_Bilet >> biletPiesa[NumarBilete].Tip_Bilet >> biletPiesa[NumarBilete].Pret_Bilet)
        NumarBilete++;
    NumarBilete--;
    fisierBilet.close();
}

void citire_personal()
{
    ifstream fisierPersonalTeatru("personal.txt"); // fisier cu personalul care lucreaza in incinta teatrului
    while (fisierPersonalTeatru >> personalTeatru[NumarPersonalTeatru].ID_PersonalTeatru >> personalTeatru[NumarPersonalTeatru].Functie_PersonalTeatru >> personalTeatru[NumarPersonalTeatru].Nume_PersonalTeatru >> personalTeatru[NumarPersonalTeatru].Prenume_PersonalTeatru >> personalTeatru[NumarPersonalTeatru].CNP_PersonalTeatru >> personalTeatru[NumarPersonalTeatru].Varsta_PersonalTeatru)
        NumarPersonalTeatru++;
    NumarPersonalTeatru--;
    fisierPersonalTeatru.close();
}

void citire_spectatori()
{
    ifstream fisierSpectator("spectator.txt"); // fisier cu spectatorii care si-au rezervat loc la fiecare piesa de teatru
    while (fisierSpectator >> spectatorPiesa[NumarSpectatori].ID_Spectator >> spectatorPiesa[NumarSpectatori].ID_Bilet >> spectatorPiesa[NumarSpectatori].ID_Piesa)
        NumarSpectatori++;
    NumarSpectatori--;
    fisierSpectator.close();
}

/// Afisare date
void afisare_piese()
{
    // Determinarea piesei cu numar maxim de caractere
    unsigned int NumarMaxCaractere = 0;

    for (unsigned int i = 1; i <= NumarPiese; i++)
        if (strlen(piesaTeatru[i].Nume_Piesa) > NumarMaxCaractere)
            NumarMaxCaractere = strlen(piesaTeatru[i].Nume_Piesa);

    // Afisarea pieselor de teatru (ID, NUME, DATA)
    cout << "\n\n"
         << setw(5 - 1) << " "
         << "ID" << setw(5 + 1) << " "
         << "Nume" << setw(NumarMaxCaractere + 1) << " "
         << "Data" << endl;
    fillLinieConsola(85); // umple toate linia din consola cu  '_'

    for (unsigned int i = 1; i <= NumarPiese; i++)
        cout << setw(5) << " " << piesaTeatru[i].ID_Piesa << setw(5) << " " << piesaTeatru[i].Nume_Piesa
             << setw(NumarMaxCaractere - strlen(piesaTeatru[i].Nume_Piesa) + 5) << " " << piesaTeatru[i].Data_Piesa << endl;

    fillLinieConsola(85); // umple toate linia din consola cu  '_'
}

void afisare_sali()
{
    cout << "\n\n";
    cout << setw(5) << " " << "ID Sala";
    cout << setw(2) << " " << "Numar scaune";
    cout << setw(2) << " " << "Numar scaune loja";
    cout << "\n";
    fillLinieConsola(45);
    for (unsigned int i = 1; i <= NumarSali; i++)
        cout << setw(8) << " " << salaTeatru[i].ID_Sala << setw(10) << " " << salaTeatru[i].Nr_Scaune << setw(12) << " " << salaTeatru[i].Nr_Scaune_Loja << endl;
    fillLinieConsola(45);
}

void afisare_bilete()
{
    for (unsigned int i = 1; i <= NumarBilete; i++)
        cout << biletPiesa[i].ID_Bilet << ": " << biletPiesa[i].Tip_Bilet << ", " << biletPiesa[i].Pret_Bilet << endl;
}

void afisare_actori()
{
    // Determinarea numelui cu numar maxim de caractere
    unsigned int NumarMaxCaractereNume = 0;

    for (unsigned int i = 1; i <= NumarActori; i++)
        if (strlen(actorTeatru[i].Nume_Actor) > NumarMaxCaractereNume)
            NumarMaxCaractereNume = strlen(actorTeatru[i].Nume_Actor);

    // Determinarea prenumelui cu numar maxim de caractere
    unsigned int NumarMaxCaracterePrenume = 0;

    for (unsigned int i = 0; i <= NumarActori; i++)
        if (strlen(actorTeatru[i].Prenume_Actor) > NumarMaxCaracterePrenume)
            NumarMaxCaracterePrenume = strlen(actorTeatru[i].Prenume_Actor);

    // Determinarea Email-ului cu numar maxim de caractere
    unsigned int NumarMaxCaractereEmail = 0;

    for (unsigned int i = 0; i < NumarActori; i++)
        if (strlen(actorTeatru[i].Email_Actor) > NumarMaxCaractereEmail)
            NumarMaxCaractereEmail = strlen(actorTeatru[i].Email_Actor);

    // Afisare Actori
    cout << "\n\n"
         << setw(5 - 1) << " "
         << "ID_Actor"
         << " "
         << "ID_Piesa" << setw(5) << " "
         << "Nume_Actor"
         << setw(NumarMaxCaractereNume) << " "
         << "Prenume_Actor" << setw(NumarMaxCaracterePrenume - 5) << " "
         << "Varsta_Actor" << setw(10) << " "
         << "Email_Actor"
         << "\n";

    fillLinieConsola(115); // umple toate linia din consola cu  '_'

    for (unsigned int i = 1; i <= NumarActori; i++)
        cout << setw(5) << " " << actorTeatru[i].ID_Actor << setw(10 - 1) << " " << actorTeatru[i].ID_Piesa << setw(10 - 1) << " " << actorTeatru[i].Nume_Actor
             << setw(NumarMaxCaractereNume - strlen(actorTeatru[i].Nume_Actor) + 10) << " " << actorTeatru[i].Prenume_Actor
             << setw(NumarMaxCaracterePrenume - strlen(actorTeatru[i].Prenume_Actor) + 10) << " " << actorTeatru[i].Varsta_Actor << " ani"
             << setw(10) << " " << actorTeatru[i].Email_Actor << setw(NumarMaxCaractereEmail - strlen(actorTeatru[i].Email_Actor) + 10) << "\n";

    fillLinieConsola(115);
}

void afisare_personal()
{
    for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
        cout << personalTeatru[i].Nume_PersonalTeatru << endl;
}

/// Componente main
void cautare_piesa_nume() // cauta piesa dupa numele introdus de la tastatura
{
    system("CLS");

    afisare_piese();

    char vNume_Piesa[101];

    cout << endl
         << setw(5 - 1) << " "
         << "Tasteaza numele piesei: ";
    cin.get();
    cin.get(vNume_Piesa, 101);

    for (unsigned int i = 1; i <= NumarPiese; i++)
        if (stricmp(piesaTeatru[i].Nume_Piesa, vNume_Piesa) == 0)
        {
            cout << "\n\n";

            cout << setw(5 - 1) << " " << "ID: " << piesaTeatru[i].ID_Piesa << endl;
            cout << setw(5 - 1) << " " << "Nume: " << piesaTeatru[i].Nume_Piesa << endl;
            cout << setw(5 - 1) << " " << "Sala: " << piesaTeatru[i].ID_Sala << endl;
            cout << setw(5 - 1) << " " << "Data: " << piesaTeatru[i].Data_Piesa << endl;
            cout << setw(5 - 1) << " " << "Ora: " << piesaTeatru[i].Ora_Piesa << '\n';
        }
    cout << '\n';
    cout << setw(5 - 1) << " " << "Apasa enter pentru a te intoarce la meniul precedent...";
}

void cautare_Piesa_ID_Actori() // cauta piesa dupa ID si afiseaza actorul corespunzator personajului din piesa respectiva
{
    unsigned int vID_Piesa;
    unsigned int ok = 0;

    cout << endl
         << "Tasteaza ID-ul piesei cautate: ";
    cin >> vID_Piesa;
    cout << "\n\n";

    for (unsigned int i = 1; i <= NumarPiese && ok == 0; i++)
        if (piesaTeatru[i].ID_Piesa == vID_Piesa)
        {
            for (unsigned int j = 1; j <= NumarPersonaje; j++)
                if (personajPiesa[j].ID_Piesa == piesaTeatru[i].ID_Piesa)
                {
                    cout << personajPiesa[j].Nume_Personaj << endl;

                    /*
                    unsigned int k = 1;
                    while (actorTeatru[k].ID_Actor != personajPiesa[j].ID_Actor)
                        k++;*/

                    //cout << " (jucat de " << actorTeatru[k].Nume_Actor << ")" << endl;
                }

            ok = 1; // iese din 'for'
        }
}

void profituri_vanzare_bilete() // cauta piesa dupa ID si afiseaza profitul adus de o anumita piesa (lei)
{
    unsigned int vID_Piesa;
    unsigned int ok = 0, v = 0;

    cout << endl
         << "Tasteaza ID-ul piesei cautate: ";
    cin >> vID_Piesa;

    for (unsigned int i = 1; i <= NumarPiese && ok == 0; i++)
        if (piesaTeatru[i].ID_Piesa == vID_Piesa)
        {
            for (unsigned int j = 1; j <= NumarSpectatori; j++)
                if (spectatorPiesa[j].ID_Piesa == piesaTeatru[i].ID_Piesa)
                    v = v + biletPiesa[spectatorPiesa[j].ID_Bilet].Pret_Bilet;
            ok = 1;
        }
    cout << "Biletele cumparate pentru aceasta piesa alcatuiesc " << v << " lei."
         << "\n\n";
    cout << "Apasati enter pentru a va intoarce la meniul precedent..." << endl;
}

void Adaugare_Sali()
{
    system("CLS");
    copie_ID_Sala_Max++;
    NumarSali++;

    cout << "\n\n";
    cout << setw(4) << " " << "Introduceti datele noii sali:" << "\n\n";
    cout << setw(6) << " " << "ID-ul salii: " << copie_ID_Sala_Max << endl;
    salaTeatru[NumarSali].ID_Sala = copie_ID_Sala_Max;
    cout << setw(6) << " " << "Numar scaune: ";
    cin >> salaTeatru[NumarSali].Nr_Scaune;
    cout << setw(6) << " " << "Numar scaune loja: ";
    cin >> salaTeatru[NumarSali].Nr_Scaune_Loja;

    cout << '\n' << setw(4) << " " << "Apasati enter pentru a va intoarce la meniul precedent...";

    ofstream fisierSala;
    fisierSala.open("sala.txt", ios::out | ios::app);
    fisierSala << salaTeatru[NumarSali].ID_Sala << " " << salaTeatru[NumarSali].Nr_Scaune << " " << salaTeatru[NumarSali].Nr_Scaune_Loja << endl;
    fisierSala.close();
}

void Stergere_Sali()
{
    system("CLS");
    unsigned int vID;
    cout << "\n\n";
    cout << setw(5) << " " << "Introduceti ID-ul salii pe care doriti sa o stergeti din baza de date: ";
    cin >> vID;
    for (unsigned int i = vID; i <= NumarSali - 1; i++)
    {
        salaTeatru[i].ID_Sala = salaTeatru[i + 1].ID_Sala - 1;
        salaTeatru[i].Nr_Scaune = salaTeatru[i + 1].Nr_Scaune;
        salaTeatru[i].Nr_Scaune_Loja = salaTeatru[i + 1].Nr_Scaune_Loja;
    }
    NumarSali--;
    copie_ID_Sala_Max--;

    ofstream fiserSala("sala.txt");
    for (unsigned int i = 0; i <= NumarSali; i++)
        fiserSala << salaTeatru[i].ID_Sala << " " << salaTeatru[i].Nr_Scaune << " " << salaTeatru[i].Nr_Scaune_Loja << endl;
    fiserSala.close();
}

void Adaugare_Actori()
{
    bool valid = false;

    system("CLS");
    copie_ID_Actor_Max++;
    NumarActori++;
    cout << "\n\n";
    cout << setw(5) << " " << "Introduceti datele noului/noii actor/actrite: " << "\n\n";
    cout << setw(6) << " " << "ID-ul actorului: " << copie_ID_Actor_Max << endl;
    actorTeatru[NumarActori].ID_Actor = copie_ID_Actor_Max;
    cout << setw(6) << " " << "ID-ul piesei in care joaca actorul: ";

    while (!valid)
    {
        cin >> actorTeatru[NumarActori].ID_Piesa;;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << '\n';
            cerr << setw(6) << " " << "Valoarea introdusa in campul ID PIESA este invalida!" << endl;
            Sleep(1500);
            copie_ID_Actor_Max--;
            Adaugare_Actori();
        }
        else valid = true;
    }

    cout << setw(6) << " " << "Numele actorului: ";
    cin >> actorTeatru[NumarActori].Nume_Actor;
    cout << setw(6) << " " << "Prenumele actorului: ";
    cin >> actorTeatru[NumarActori].Prenume_Actor;
    cout << setw(6) << " " << "Varsta actorului: ";

    valid = false;
    while (!valid)
    {
        cin >> actorTeatru[NumarActori].Varsta_Actor;;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << '\n';
            cerr << setw(6) << " " << "Valoarea introdusa in campul VARSTA este invalida!" << endl;
            Sleep(1500);
            copie_ID_Actor_Max--;
            Adaugare_Actori();
        }
        else valid = true;
    }

    cout << setw(6) << " " << "Email-ul actorului: ";
    cin >> actorTeatru[NumarActori].Email_Actor;
    cout << setw(6) << " " << "CNP-ul actorului: ";

    valid = false;
    while (!valid)
    {
        cin >> actorTeatru[NumarActori].CNP_Actor;
        if (strlen(actorTeatru[NumarActori].CNP_Actor) != 13)
        {
            cin.clear();
            cin.ignore();
            cout << '\n';
            cerr << setw(6) << " " << "Valoarea introdusa in campul CNP este invalida!" << endl;
            Sleep(1500);
            copie_ID_Actor_Max--;
            Adaugare_Actori();
        }
        else valid = true;
    }

    cout << setw(6) << " " << "Sex-ul actorului (F/M): ";
    cin >> actorTeatru[NumarActori].Sex_Actor;

    ofstream fisierActor;
    fisierActor.open("actor.txt", ios::out | ios::app);
    fisierActor << actorTeatru[NumarActori].ID_Actor << " " << actorTeatru[NumarActori].ID_Piesa << " " << actorTeatru[NumarActori].Nume_Actor << " "
                << actorTeatru[NumarActori].Prenume_Actor << " " << actorTeatru[NumarActori].Varsta_Actor << " " << actorTeatru[NumarActori].Email_Actor << " "
                << actorTeatru[NumarActori].CNP_Actor << " " << actorTeatru[NumarActori].Sex_Actor << endl;
    fisierActor.close();
}

void Stergere_Actori()
{
    system("CLS");

    unsigned int vID;
    bool valid = false;

    cout << "\n\n";
    cout << setw(5) << " " << "APASA TASTA '0' PENTRU A ANULA";
    cout << "\n\n";
    cout << setw(5) << " " << "Introduceti ID-ul actorului pe care doriti sa il stergeti din baza de date: ";


    while (!valid)
    {
        cin >> vID;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << '\n';
            cerr << setw(6 - 1) << " " << "Valoarea introdusa in campul ID ACTOR este invalida!" << endl;
            Sleep(1500);
            Stergere_Actori();
        }
        else valid = true;
    }

    if (vID == 0)
        return;
    else
    {
        for (unsigned int i = vID; i <= NumarActori - 1; i++)
        {
            actorTeatru[i].ID_Actor = actorTeatru[i + 1].ID_Actor - 1;
            actorTeatru[i].ID_Piesa = actorTeatru[i + 1].ID_Piesa;
            strcpy(actorTeatru[i].Nume_Actor, actorTeatru[i + 1].Nume_Actor);
            strcpy(actorTeatru[i].Prenume_Actor, actorTeatru[i + 1].Prenume_Actor);
            actorTeatru[i].Varsta_Actor = actorTeatru[i + 1].Varsta_Actor;
            strcpy(actorTeatru[i].Email_Actor, actorTeatru[i + 1].Email_Actor);
            strcpy(actorTeatru[i].CNP_Actor, actorTeatru[i + 1].CNP_Actor);
            actorTeatru[i].Sex_Actor = actorTeatru[i + 1].Sex_Actor;
        }

        NumarActori--;
        copie_ID_Actor_Max--;

        ofstream fisierActor("actor.txt");
        for (unsigned int i = 1; i <= NumarActori; i++)
            fisierActor << actorTeatru[i].ID_Actor << " " << actorTeatru[i].ID_Piesa << " " << actorTeatru[i].Nume_Actor << " "
                        << actorTeatru[i].Prenume_Actor << " " << actorTeatru[i].Varsta_Actor << " " << actorTeatru[i].Email_Actor << " "
                        << actorTeatru[i].CNP_Actor << " " << actorTeatru[i].Sex_Actor << endl;
    }
}

void Adaugare_Piese()
{
    bool valid = false;

    system("CLS");
    copie_ID_Piesa_Max++;
    NumarPiese++;

    cout << "\n\n";
    cout << setw(4) << " " << "Introduceti datele noii piese:" << "\n\n";
    cout << setw(6) << " " << "ID-ul piesei: " << copie_ID_Piesa_Max << endl;
    piesaTeatru[NumarPiese].ID_Piesa = copie_ID_Piesa_Max;
    cout << setw(6) << " " << "ID-ul salii in care se va tine piesa de teatru: ";

    while (!valid)
    {
        cin >> piesaTeatru[NumarPiese].ID_Sala;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << '\n';
            cerr << setw(6 - 1) << " " << "Valoarea introdusa in campul ID PIESA este invalida!" << endl;
            Sleep(1500);
            Adaugare_Piese();
        }
        else valid = true;
    }

    if (piesaTeatru[NumarPiese].ID_Sala == 0)
        return;

    cout << setw(6) << " " << "Data: ";
    cin >> piesaTeatru[NumarPiese].Data_Piesa;

    if (piesaTeatru[NumarPiese].Data_Piesa == 0)
        return;

    cout << setw(6) << " " << "Ora: ";
    cin >> piesaTeatru[NumarPiese].Ora_Piesa;
    cout << setw(6) << " " << "Nume: ";
    cin >> piesaTeatru[NumarPiese].Nume_Piesa;

    cout << '\n' << setw(4) << " " << "Apasati enter pentru a va intoarce la meniul precedent...";

    ofstream fisierPiesa;
    fisierPiesa.open("piesa.txt", ios::out | ios::app);
    fisierPiesa << piesaTeatru[NumarPiese].ID_Piesa << " " << piesaTeatru[NumarPiese].ID_Sala << " " << piesaTeatru[NumarPiese].Data_Piesa << " "
                << piesaTeatru[NumarPiese].Ora_Piesa << " " << piesaTeatru[NumarPiese].Nume_Piesa << endl;
    fisierPiesa.close();
}

void Stergere_Piese()
{
    system("CLS");

    afisare_piese();

    unsigned int vID;
    bool valid = false;

    cout << "\n\n";
    cout << setw(5) << " " << "APASA TASTA '0' PENTRU A ANULA";
    cout << "\n\n";
    cout << setw(5) << " " << "Introduceti ID-ul piesei pe care doriti sa il stergeti din baza de date: ";

    while (!valid)
    {
        cin >> vID;
        if (cin.fail() || vID > copie_ID_Piesa_Max)
        {
            cin.clear();
            cin.ignore();
            cout << '\n';
            cerr << setw(6 - 1) << " " << "Valoarea introdusa in campul ID PIESA este invalida!" << endl;
            Sleep(1500);
            Stergere_Actori();
        }
        else valid = true;
    }

    if (vID == 0)
        return;
    {
        for (unsigned int i = vID; i <= NumarPiese - 1; i++)
        {
            piesaTeatru[i].ID_Sala = piesaTeatru[i + 1].ID_Sala - 1;
            piesaTeatru[i].ID_Sala = piesaTeatru[i + 1].ID_Sala;
            strcpy(piesaTeatru[i].Data_Piesa, piesaTeatru[i + 1].Data_Piesa);
            strcpy(piesaTeatru[i].Ora_Piesa, piesaTeatru[i + 1].Ora_Piesa);
            strcpy(piesaTeatru[i].Nume_Piesa, piesaTeatru[i + 1].Nume_Piesa);
        }
        NumarPiese--;
        copie_ID_Piesa_Max--;
    }

    ofstream fisierPiesa("piesa.txt");
    for (unsigned int i = 1; i <= NumarPiese; i++)
        fisierPiesa << piesaTeatru[i].ID_Piesa << " " << piesaTeatru[i].ID_Sala << " " << piesaTeatru[i].Data_Piesa << " "
                    << piesaTeatru[i].Ora_Piesa << " " << piesaTeatru[i].Nume_Piesa << endl;
    fisierPiesa.close();
}

int main()
{
    con.color(0x03);

    /// Citirea datelor din fisierele corespunzatoare
    citire_sali();
    citire_actori();
    citire_piese();
    citire_personaje_piese();
    citire_bilete();
    citire_personal();
    citire_spectatori();

    unsigned int Meniu_1;

    do
    {
        system("CLS");

        // Continutul meniului principal
        cout << "\n\n"
             << setw(35) << " "
             << "MENIU"
             << "\n";

        fillLinieConsola(70); // umple toate linia din consola cu '_'

        cout << setw(5 - 1) << " "
             << "1. Piesele ce urmeaza sa fie jucate in perioasa 10.07 - 17.07.2022" << endl;
        cout << setw(5 - 1) << " "
             << "2. Sali de teatru" << endl;
        cout << setw(5 - 1) << " "
             << "3. Tipurile de bilete disponibile la vanzare" << endl;
        cout << setw(5 - 1) << " "
             << "4. Actorii care joaca in piesele de teatru" << endl;
        cout << setw(5 - 1) << " "
             << "5. Personalul teatrului" << endl;
        cout << setw(5 - 1) << " "
             << "0. Iesire"
             << "\n\n";

        fillLinieConsola(70); // umple toate linia din consola cu  '_'

        cout << setw(5 - 1) << " "
             << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
        cin >> Meniu_1;

        switch (Meniu_1)
        {
        case 1:
        {
            unsigned int Meniu_2;

            do
            {
                system("CLS"); // sterge continut consola
                afisare_piese();
                cout << endl;

                // Continutul celui de al doilea meniu
                cout << setw(5 - 1) << " "
                     << "1. Detalii desre piesele de teatru" << endl;
                cout << setw(5 - 1) << " "
                     << "2. Personajele care joaca in piesele de teatru si actorii corespunzatori acestora" << endl;
                cout << setw(5 - 1) << " "
                     << "3. Profit si cheltuieli" << endl;
                cout << setw(5 - 1) << " "
                     << "4. Modificarea datelor" << endl;
                cout << setw(5 - 1) << " "
                     << "0. Inapoi"
                     << "\n\n";

                fillLinieConsola(85);

                cout << setw(5 - 1) << " "
                     << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
                cin >> Meniu_2;

                switch (Meniu_2)
                {

                case 1:
                {
                    cautare_piesa_nume();
                }
                _getch();
                break;

                case 2:
                {
                    cautare_Piesa_ID_Actori();
                }
                _getch();
                break;

                case 3:
                {
                    profituri_vanzare_bilete();
                }
                _getch();
                break;
                case 4:
                {
                    unsigned int Meniu_Mod_date;

                    do
                    {
                        system("CLS");
                        afisare_piese();
                        cout << '\n';
                        cout << setw(5 - 1) << " " << "MODIFICAREA DATELOR" << "\n\n";
                        cout << setw(6) << " " << "1. Adauga piese" << '\n';
                        cout << setw(6) << " " << "2. Sterge piese" << '\n';
                        cout << setw(6) << " " << "0. Inapoi" << "\n\n";

                        cout << setw(5 - 1) << " " << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
                        cin >> Meniu_Mod_date;

                        switch (Meniu_Mod_date)
                        {
                        case 1:
                            Adaugare_Piese();
                            break;
                        case 2:
                            Stergere_Piese();
                            break;
                        }
                    }
                    while (Meniu_Mod_date != 0);
                }
                _getch();
                break;
                }
            }
            while (Meniu_2 != 0);
        }
        break;
        case 2:
        {
            unsigned int Meniu_Sali;

            do
            {
                system("CLS");
                afisare_sali();
                cout << '\n';
                cout << setw(5 - 1) << " " << "MODIFICAREA DATELOR" << "\n\n";
                cout << setw(6) << " " << "1. Adauga sali" << '\n';
                cout << setw(6) << " " << "2. Sterge sali" << '\n';
                cout << setw(6) << " " << "0. Inapoi" << "\n\n";

                cout << setw(5 - 1) << " " << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
                cin >> Meniu_Sali;

                switch (Meniu_Sali)
                {
                case 1:
                    Adaugare_Sali();
                    _getch();
                    break;
                case 2:
                    Stergere_Sali();
                    break;
                }
            }
            while (Meniu_Sali != 0);
        }
        break;
        case 3:
        {
            afisare_bilete();
        }
        _getch();
        break;
        case 4:
        {
            unsigned int Meniu_Actori;

            do
            {
                system("CLS");
                afisare_actori();

                cout << '\n';
                cout << setw(5 - 1) << " " << "MODIFICAREA DATELOR" << "\n\n";
                cout << setw(6) << " " << "1. Adauga actori" << '\n';
                cout << setw(6) << " " << "2. Sterge actori" << '\n';
                cout << setw(6) << " " << "0. Inapoi" << "\n\n";

                cout << setw(5 - 1) << " " << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
                cin >> Meniu_Actori;

                switch (Meniu_Actori)
                {
                case 1:
                    Adaugare_Actori();
                    break;
                case 2:
                    Stergere_Actori();
                    break;
                }
            }
            while (Meniu_Actori != 0);
        }
        break;
        case 5:
        {
            afisare_personal();
        }
        _getch();
        break;
        }

    }
    while (Meniu_1 != 0);

    return 0;
}
