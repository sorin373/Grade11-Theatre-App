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
#include <cmath>

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
unsigned int copie_ID_Sala_Max = 0, copie_ID_Actor_Max = 0, copie_ID_Piesa_Max = 0, copie_ID_Bilet_Max = 0, copie_ID_Personal_Max = 0;

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
    unsigned int ID_PersonalTeatru;
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
    char Functie_PersonalTeatru[1001];

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
    while (fisierPiesa >> piesaTeatru[NumarPiese].ID_Piesa >> piesaTeatru[NumarPiese].ID_Sala >> piesaTeatru[NumarPiese].ID_PersonalTeatru >> piesaTeatru[NumarPiese].Data_Piesa >> piesaTeatru[NumarPiese].Ora_Piesa)
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
    {
        copie_ID_Bilet_Max = biletPiesa[NumarBilete].ID_Bilet;
        NumarBilete++;
    }

    NumarBilete--;
    fisierBilet.close();
}

void citire_personal()
{
    ifstream fisierPersonalTeatru("personal.txt"); // fisier cu personalul care lucreaza in incinta teatrului
    while (fisierPersonalTeatru >> personalTeatru[NumarPersonalTeatru].ID_PersonalTeatru >> personalTeatru[NumarPersonalTeatru].Functie_PersonalTeatru
            >> personalTeatru[NumarPersonalTeatru].Nume_PersonalTeatru >> personalTeatru[NumarPersonalTeatru].Prenume_PersonalTeatru
            >> personalTeatru[NumarPersonalTeatru].CNP_PersonalTeatru >> personalTeatru[NumarPersonalTeatru].Varsta_PersonalTeatru)
    {
        copie_ID_Personal_Max = personalTeatru[NumarPersonalTeatru].ID_PersonalTeatru;
        NumarPersonalTeatru++;
    }

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
         << setw(5) << " "
         << "ID" << setw(5 + 1) << " "
         << "Nume" << setw(NumarMaxCaractere + 1) << " "
         << "Data" << setw(5 + 2) << " "
         << "Ora" << setw(5 + 3) << " " << "Regizor" << endl;
    fillLinieConsola(85); // umple toate linia din consola cu  '_'

    for (unsigned int i = 1; i <= NumarPiese; i++)
    {
        cout << setw(5) << " " << piesaTeatru[i].ID_Piesa << setw(5) << " " << piesaTeatru[i].Nume_Piesa
             << setw(NumarMaxCaractere - strlen(piesaTeatru[i].Nume_Piesa) + 5) << " " << piesaTeatru[i].Data_Piesa << " "
             << setw(5) << " " << piesaTeatru[i].Ora_Piesa << setw(5) << " ";

        for (unsigned int j = 0; j <= NumarPersonalTeatru; j++)
            if (personalTeatru[j].ID_PersonalTeatru == piesaTeatru[i].ID_PersonalTeatru)
                cout << personalTeatru[j].Nume_PersonalTeatru << " " << personalTeatru[j].Prenume_PersonalTeatru << endl;
    }
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
    unsigned int NumarMaxCaractere = 0;

    for (unsigned int i = 1; i <= NumarBilete; i++)
        if (strlen(biletPiesa[i].Tip_Bilet) > NumarMaxCaractere)
            NumarMaxCaractere = strlen(biletPiesa[i].Tip_Bilet);

    cout << "\n\n";
    cout << setw(5) << " " << "ID bilet";
    cout << setw(10) << " " << "Tip bilet";
    cout << setw(10 + 10) << " " << "Pret bilet";
    cout << "\n";

    fillLinieConsola(85);

    for (unsigned int i = 1; i <= NumarBilete; i++)
    {
        cout << setprecision(3) << fixed;
        cout << setw(8) << " " << biletPiesa[i].ID_Bilet << setw(10) << " ";

        char tipBiletAux[101];
        strcpy(tipBiletAux, biletPiesa[i].Tip_Bilet);

        for (unsigned int i = 0; i < strlen(tipBiletAux); i++)
            if (tipBiletAux[i] == '_')
                tipBiletAux[i] = ' ';

        cout << tipBiletAux << setw(NumarMaxCaractere - strlen(biletPiesa[i].Tip_Bilet) + 6) << " " << biletPiesa[i].Pret_Bilet << endl;
    }

    fillLinieConsola(85);
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
         << "ID Actor"
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
    unsigned int nrMaxCaractereFunctie = 0;
    for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
        if (strlen(personalTeatru[i].Functie_PersonalTeatru) > nrMaxCaractereFunctie)
            nrMaxCaractereFunctie = strlen(personalTeatru[i].Functie_PersonalTeatru);

    unsigned int nrMaxCaractereNumePersonal = 0;
    for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
        if (strlen(personalTeatru[i].Nume_PersonalTeatru) > nrMaxCaractereNumePersonal)
            nrMaxCaractereNumePersonal = strlen(personalTeatru[i].Nume_PersonalTeatru);

    unsigned int nrMaxCaracterePreumePersonal = 0;
    for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
        if (strlen(personalTeatru[i].Prenume_PersonalTeatru) > nrMaxCaracterePreumePersonal)
            nrMaxCaracterePreumePersonal = strlen(personalTeatru[i].Prenume_PersonalTeatru);

    cout << "\n\n"
         << setw(5) << " "
         << "ID Staff" << setw(10) << " "
         << "Functie" << setw(nrMaxCaractereFunctie - 10) << " "
         << "Nume staff"
         << setw(nrMaxCaractereNumePersonal - 5) << " "
         << "Prenume staff" << setw(nrMaxCaracterePreumePersonal - 5) << " "
         << "CNP staff" << setw(5) << " "
         << "Varsta staff"
         << "\n";
    fillLinieConsola(110);

    for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
    {
        cout << setw(5 + 2) << " " << personalTeatru[i].ID_PersonalTeatru << setw(10 - 1) << " ";

        char vFunctiePersonalAux[1001];
        strcpy(vFunctiePersonalAux, personalTeatru[i].Functie_PersonalTeatru);
        for (unsigned int j = 0; j < strlen(vFunctiePersonalAux); j++)
            if (vFunctiePersonalAux[j] == '_')
                vFunctiePersonalAux[j] = ' ';

        cout << vFunctiePersonalAux << setw(nrMaxCaractereFunctie + 5 - strlen(personalTeatru[i].Functie_PersonalTeatru)) << " "
             << personalTeatru[i].Nume_PersonalTeatru << " " << setw(nrMaxCaractereNumePersonal + 5 - strlen(personalTeatru[i].Nume_PersonalTeatru)) << " "
             << personalTeatru[i].Prenume_PersonalTeatru << setw(nrMaxCaracterePreumePersonal + 5 - strlen(personalTeatru[i].Prenume_PersonalTeatru)) << " "
             << personalTeatru[i].CNP_PersonalTeatru << setw(5) << " "
             << personalTeatru[i].Varsta_PersonalTeatru << endl;
    }

    fillLinieConsola(110);
}

/// Componente main
void cautare_piesa()
{
    system("CLS");
    afisare_piese();

    unsigned int Meniu_Cautare;
    bool valid = false;

    do
    {
        cout << setw(5 - 1) << " " << "Cum doriti sa cautati piesa dorita?" << "\n\n";

        cout << setw(5) << " " << "1. Dupa numele piesei" << endl;
        cout << setw(5) << " " << "2. Dupa ID-ul piesei" << endl;
        cout << setw(5) << " " << "3. Dupa ora la care are loc piesa" << endl;
        cout << setw(5) << " " << "4. Dupa data in care are loc piesa" << endl;
        cout << setw(5) << " " << "5. Dupa regizorul piesei" << endl;
        cout << setw(5) << " " << "6. Dupa un anumit actor " << endl;
        cout << setw(5) << " " << "0. Inapoi" << "\n\n";

        cout << setw(5 - 1) << " "
             << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";

        while (!valid)
        {
            cin >> Meniu_Cautare;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
                cout << '\n';
                cerr << setw(6 - 1) << " " << "Valoarea introdusa este invalida!" << endl;
                Sleep(1500);
                cautare_piesa();
            }
            else valid = true;
        }

        switch (Meniu_Cautare)
        {
        case 1:
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
                    cout << '\n';

                    cout << setw(5 - 1) << " " << "ID: " << piesaTeatru[i].ID_Piesa << endl;
                    cout << setw(5 - 1) << " " << "Nume: " << piesaTeatru[i].Nume_Piesa << endl;
                    cout << setw(5 - 1) << " " << "Sala: " << piesaTeatru[i].ID_Sala << endl;
                    cout << setw(5 - 1) << " " << "Data: " << piesaTeatru[i].Data_Piesa << endl;
                    cout << setw(5 - 1) << " " << "Ora: " << piesaTeatru[i].Ora_Piesa << '\n';
                }
            cout << '\n';
            cout << setw(5 - 1) << " " << "Apasa enter pentru a te intoarce la meniul precedent...";
            _getch();
            cautare_piesa();
        }
        _getch();
        break;
        case 2:
        {
            system("CLS");
            afisare_piese();

            unsigned int vID;
            bool exit = false, valid = false;

            cout << endl
                 << setw(5 - 1) << " "
                 << "Tasteaza ID-ul piesei: ";

            while (!valid)
            {
                cin >> vID;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore();
                    cout << '\n';
                    cerr << setw(6) << " " << "Valoarea introdusa este invalida!" << endl;
                    Sleep(1500);
                    cautare_piesa();
                }
                else valid = true;
            }

            for (unsigned int i = 1; i <= NumarPiese && !exit; i++)
                if (piesaTeatru[i].ID_Piesa == vID)
                {
                    cout << '\n';

                    cout << setw(5 - 1) << " " << "ID: " << piesaTeatru[i].ID_Piesa << endl;
                    cout << setw(5 - 1) << " " << "Nume: " << piesaTeatru[i].Nume_Piesa << endl;
                    cout << setw(5 - 1) << " " << "Sala: " << piesaTeatru[i].ID_Sala << endl;
                    cout << setw(5 - 1) << " " << "Data: " << piesaTeatru[i].Data_Piesa << endl;
                    cout << setw(5 - 1) << " " << "Ora: " << piesaTeatru[i].Ora_Piesa << '\n';

                    exit = true;
                }
            cout << '\n';
            cout << setw(5 - 1) << " " << "Apasa enter pentru a te intoarce la meniul precedent...";
            _getch();
            cautare_piesa();
        }
        _getch();
        break;
        case 3:
        {
            system("CLS");
            afisare_piese();

            char vOraPiesa[6];
            bool valid = false, exist = false;

            cout << endl
                 << setw(5 - 1) << " "
                 << "Tasteaza ora (FORMAT: 00:00): ";

            while (!valid)
            {
                cin.get();
                cin.get(vOraPiesa, 6);

                if (cin.fail() || strlen(vOraPiesa) != 5 || vOraPiesa[strlen(vOraPiesa) / 2] != ':')
                {
                    cin.clear();
                    cin.ignore();
                    cout << '\n';
                    cerr << setw(5 - 1) << " " << "Formatul orei introduse este invalid!" << endl;
                    Sleep(1500);
                    cautare_piesa();
                }
                else valid = true;
            }

            for (unsigned int i = 1; i <= NumarPiese; i++)
                if (strcmp(piesaTeatru[i].Ora_Piesa, vOraPiesa) == 0)
                {
                    cout << '\n';

                    cout << setw(5 - 1) << " " << "ID: " << piesaTeatru[i].ID_Piesa << endl;
                    cout << setw(5 - 1) << " " << "Nume: " << piesaTeatru[i].Nume_Piesa << endl;
                    cout << setw(5 - 1) << " " << "Sala: " << piesaTeatru[i].ID_Sala << endl;
                    cout << setw(5 - 1) << " " << "Data: " << piesaTeatru[i].Data_Piesa << endl;
                    cout << setw(5 - 1) << " " << "Ora: " << piesaTeatru[i].Ora_Piesa << '\n';

                    exist = true;
                }

            if (!exist)
            {
                cout << '\n' << setw(5 - 1) << " " << "Nu exista piese la aceasta ora!";
                Sleep(1500);
                cautare_piesa();
            }

            cout << '\n';
            cout << setw(5 - 1) << " " << "Apasa enter pentru a te intoarce la meniul precedent...";

            _getch();
            cautare_piesa();
        }
        _getch();
        break;
        case 4:
        {
            system("CLS");
            afisare_piese();

            char vDataPiesa[11];
            bool valid = false, exist = false;

            cout << endl
                 << setw(5 - 1) << " "
                 << "Tasteaza data (FORMAT: dd.mm): ";

            while (!valid)
            {
                cin.get();
                cin.get(vDataPiesa, 6);

                if (cin.fail() || strlen(vDataPiesa) != 5 || vDataPiesa[strlen(vDataPiesa) / 2] != '.')
                {
                    cin.clear();
                    cin.ignore();
                    cout << '\n';
                    cerr << setw(5 - 1) << " " << "Formatul datei introduse este invalid!" << endl;
                    Sleep(1500);
                    cautare_piesa();
                }
                else valid = true;
            }

            for (unsigned int i = 1; i <= NumarPiese; i++)
                if (strcmp(piesaTeatru[i].Data_Piesa, vDataPiesa) == 0)
                {
                    cout << '\n';

                    cout << setw(5 - 1) << " " << "ID: " << piesaTeatru[i].ID_Piesa << endl;
                    cout << setw(5 - 1) << " " << "Nume: " << piesaTeatru[i].Nume_Piesa << endl;
                    cout << setw(5 - 1) << " " << "Sala: " << piesaTeatru[i].ID_Sala << endl;
                    cout << setw(5 - 1) << " " << "Data: " << piesaTeatru[i].Data_Piesa << endl;
                    cout << setw(5 - 1) << " " << "Ora: " << piesaTeatru[i].Ora_Piesa << '\n';

                    exist = true;
                }

            if (!exist)
            {
                cout << '\n' << setw(5 - 1) << " " << "Nu exista piese in aceasta data!";
                Sleep(1500);
                cautare_piesa();
            }

            cout << '\n';
            cout << setw(5 - 1) << " " << "Apasa enter pentru a te intoarce la meniul precedent...";

            _getch();
            cautare_piesa();
        }
        _getch();
        break;
        case 5:
        {
            system("CLS");
            afisare_piese();

            char vNumeRegizor[101], vPrenumeRegizor[101];
            bool exist = false;

            cout << endl
                 << setw(5 - 1) << " "
                 << "Tasteaza numele regizorului: ";

            cin.get();
            cin.get(vNumeRegizor, 101);

            cout << setw(5 - 1) << " "
                 << "Tasteaza prenumele regizorului: ";

            cin.get();
            cin.get(vPrenumeRegizor, 101);

            unsigned int copieID = 0;
            for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
                if (stricmp(vNumeRegizor, personalTeatru[i].Nume_PersonalTeatru) == 0 && stricmp(vPrenumeRegizor, personalTeatru[i].Prenume_PersonalTeatru) == 0)
                    copieID = personalTeatru[i].ID_PersonalTeatru;

            for (unsigned int j = 1; j <= NumarPiese; j++)
                if (copieID == piesaTeatru[j].ID_PersonalTeatru)
                {
                    cout << '\n';

                    cout << setw(5 - 1) << " " << "ID: " << piesaTeatru[j].ID_Piesa << endl;
                    cout << setw(5 - 1) << " " << "Nume: " << piesaTeatru[j].Nume_Piesa << endl;
                    cout << setw(5 - 1) << " " << "Sala: " << piesaTeatru[j].ID_Sala << endl;
                    cout << setw(5 - 1) << " " << "Data: " << piesaTeatru[j].Data_Piesa << endl;
                    cout << setw(5 - 1) << " " << "Ora: " << piesaTeatru[j].Ora_Piesa << '\n';

                    exist = true;
                }

            if (!exist)
            {
                cout << '\n' << setw(5 - 1) << " " << "Nu exista piese puse in scena de regizorul respectiv!";
                Sleep(1500);
                cautare_piesa();
            }

            cout << '\n';
            cout << setw(5 - 1) << " " << "Apasa enter pentru a te intoarce la meniul precedent...";

            _getch();
            afisare_piese();
        }
        _getch();
        break;
        case 6:
        {
            system("CLS");
            afisare_piese();

            char vNumeActor[101], vPrenumeActor[101];

            cout << endl
                 << setw(5 - 1) << " "
                 << "Tasteaza numele actorului: ";

            cin.get();
            cin.get(vNumeActor, 101);

            cout << setw(5 - 1) << " "
                 << "Tasteaza prenumele actorului: ";

            cin.get();
            cin.get(vPrenumeActor, 101);

            bool exist = false;

            for (unsigned int i = 1; i <= NumarActori; i++)
                if (strcmp(actorTeatru[i].Nume_Actor, vNumeActor) == 0 && strcmp(actorTeatru[i].Prenume_Actor, vPrenumeActor) == 0)
                    for (unsigned int j = 1; j <= NumarPiese; j++)
                        if (piesaTeatru[j].ID_Piesa == actorTeatru[i].ID_Piesa)
                        {
                            cout << '\n';

                            cout << setw(5 - 1) << " " << "ID: " << piesaTeatru[j].ID_Piesa << endl;
                            cout << setw(5 - 1) << " " << "Nume: " << piesaTeatru[j].Nume_Piesa << endl;
                            cout << setw(5 - 1) << " " << "Sala: " << piesaTeatru[j].ID_Sala << endl;
                            cout << setw(5 - 1) << " " << "Data: " << piesaTeatru[j].Data_Piesa << endl;
                            cout << setw(5 - 1) << " " << "Ora: " << piesaTeatru[j].Ora_Piesa << '\n';

                            exist = true;
                        }

            if (!exist)
            {
                cout << '\n' << setw(5 - 1) << " " << "Nu exista piese jucate de actorul respectiv!";
                Sleep(1500);
                cautare_piesa();
            }

            cout << '\n';
            cout << setw(5 - 1) << " " << "Apasa enter pentru a te intoarce la meniul precedent...";

            _getch();
            cautare_piesa();
        }
        _getch();
        break;
        }
    }
    while (Meniu_Cautare != 0);
}

void cautare_Piesa_ID_Actori()
{
    system("CLS");

    afisare_piese();

    unsigned int vID_Piesa;
    bool exit = false, valid = false;

    cout << setw(5 - 1) << " " << "APASA TASTA '0' PENTRU A TE INTOARCE LA MENIUL PRECEDENT" << "\n\n";
    cout << setw(5 - 1) << " " << "Introdu ID-ul corespunzator piesei cautate: ";

    while (!valid)
    {
        cin >> vID_Piesa;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << '\n';
            cerr << setw(5 - 1) << " " << "Valoarea introdusa in campul ID PIESA este invalida!" << endl;
            Sleep(1500);
            cautare_Piesa_ID_Actori();
        }
        else valid = true;
    }

    if (vID_Piesa == 0)
        return;
    else
    {
        system("CLS");

        char copieNumePiesa[101];

        cout << "\n\n";
        for (unsigned int i = 1; i <= NumarPiese && !exit; i++)
            if (piesaTeatru[i].ID_Piesa)
            {
                strcpy(copieNumePiesa, piesaTeatru[i].Nume_Piesa);
                exit = true;
            }

        exit = false;
        for (unsigned int i = 1; i <= NumarPiese && !exit; i++)
            if (piesaTeatru[i].ID_Piesa == vID_Piesa)
            {
                for (unsigned int j = 1; j <= NumarPersonaje; j++)
                    if (personajPiesa[j].ID_Piesa == piesaTeatru[i].ID_Piesa)
                    {
                        cout << setw(5 - 1) << " " << personajPiesa[j].Nume_Personaj << " ";

                        unsigned int k = 1;
                        while (actorTeatru[k].ID_Actor != personajPiesa[j].ID_Actor)
                            k++;

                        cout << "- jucat de " << actorTeatru[k].Nume_Actor << " " << actorTeatru[k].Prenume_Actor << "\n\n";
                    }
                exit = true;
            }

        fillLinieConsola(60);

        cout << "\n";
        cout << setw(5 - 1) << " " << "Apasati enter pentru a va intoarce la meniul precedent...";

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
        cin >> actorTeatru[NumarActori].ID_Piesa;
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
            cerr << setw(6 - 1) << " " << "Valoarea introdusa in campul ID SALA este invalida!" << endl;
            Sleep(1500);
            Adaugare_Piese();
        }
        else valid = true;
    }

    if (piesaTeatru[NumarPiese].ID_Sala == 0)
        return;

    char vNumeRegizor[101], vPrenumeRegizor[101];

    cout << endl
         << setw(5 + 1) << " "
         << "Tasteaza numele regizorului: ";

    cin.get();
    cin.get(vNumeRegizor, 101);

    cout << setw(5 + 1) << " "
         << "Tasteaza prenumele regizorului: ";

    cin.get();
    cin.get(vPrenumeRegizor, 101);

    unsigned int copieID = 0;
    for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
        if (stricmp(vNumeRegizor, personalTeatru[i].Nume_PersonalTeatru) == 0 && stricmp(vPrenumeRegizor, personalTeatru[i].Prenume_PersonalTeatru) == 0)
            copieID = personalTeatru[i].ID_PersonalTeatru;

    if (copieID == 0)
    {
        cerr << "Regizorul respectiv nu exista in baza de date!" << endl;
    }
    else
        piesaTeatru[NumarPiese].ID_PersonalTeatru = copieID;


    cout << setw(6) << " " << "Data: ";
    cin >> piesaTeatru[NumarPiese].Data_Piesa;

    if (piesaTeatru[NumarPiese].Data_Piesa == 0)
        return;

    cout << setw(6) << " " << "Ora: ";
    cin >> piesaTeatru[NumarPiese].Ora_Piesa;
    cout << setw(6) << " " << "Nume: ";
    cin.get();
    cin.get(piesaTeatru[NumarPiese].Nume_Piesa, 101);

    cout << '\n' << setw(4) << " " << "Apasati enter pentru a va intoarce la meniul precedent...";

    ofstream fisierPiesa;
    fisierPiesa.open("piesa.txt", ios::out | ios::app);
    fisierPiesa << piesaTeatru[NumarPiese].ID_Piesa << " " << piesaTeatru[NumarPiese].ID_Sala << " "
                << piesaTeatru[NumarPiese].ID_PersonalTeatru << " " << piesaTeatru[NumarPiese].Data_Piesa << " "
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
            piesaTeatru[i].ID_PersonalTeatru = piesaTeatru[i + 1].ID_PersonalTeatru;
            strcpy(piesaTeatru[i].Data_Piesa, piesaTeatru[i + 1].Data_Piesa);
            strcpy(piesaTeatru[i].Ora_Piesa, piesaTeatru[i + 1].Ora_Piesa);
            strcpy(piesaTeatru[i].Nume_Piesa, piesaTeatru[i + 1].Nume_Piesa);
        }
        NumarPiese--;
        copie_ID_Piesa_Max--;
    }

    ofstream fisierPiesa("piesa.txt");
    for (unsigned int i = 1; i <= NumarPiese; i++)
        fisierPiesa << piesaTeatru[i].ID_Piesa << " " << piesaTeatru[i].ID_Sala << " " << piesaTeatru[i].ID_PersonalTeatru << " " << piesaTeatru[i].Data_Piesa << " "
                    << piesaTeatru[i].Ora_Piesa << " " << piesaTeatru[i].Nume_Piesa << endl;
    fisierPiesa.close();
}

void Adaugare_Bilet()
{
    system("CLS");
    afisare_bilete();

    bool valid = false;

    copie_ID_Bilet_Max++;
    NumarBilete++;

    cout << "\n\n";
    cout << setw(4) << " " << "Introduceti datele noii sali:" << "\n\n";
    cout << setw(6) << " " << "ID-ul biletului: " << copie_ID_Bilet_Max << endl;
    biletPiesa[NumarBilete].ID_Bilet = copie_ID_Bilet_Max;
    cout << setw(6) << " " << "Descrierea tipului de bilet (maxim 100 de caractere): ";

    char descriereBilet[101];
    cin.get();
    cin.get(descriereBilet, 101);

    if (strlen(descriereBilet) > 100)
    {
        cerr << "Prea multe caractere in descrierea biletului!";
        Sleep(1500);
        Adaugare_Bilet();
    }
    else
    {
        for (unsigned int i = 0; i < strlen(descriereBilet); i++)
            if (descriereBilet[i] == ' ')
                descriereBilet[i] = '_';
        strcpy(biletPiesa[NumarBilete].Tip_Bilet, descriereBilet);

        cout << setw(6) << " " << "Pret bilet: ";

        float pretBiletAux;

        while (!valid)
        {
            cin >> pretBiletAux;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
                cout << '\n';
                cerr << setw(6) << " " << "Valoarea introdusa in campul PRET BILET este invalida!" << endl;
                Sleep(1500);
                copie_ID_Bilet_Max--;
                Adaugare_Bilet();
            }
            else valid = true;
        }

        biletPiesa[NumarBilete].Pret_Bilet = pretBiletAux + 0.00;

        cout << '\n' << setw(4) << " " << "Apasati enter pentru a va intoarce la meniul precedent...";

        ofstream fisierBilet;
        fisierBilet.open("bilet.txt", ios::out | ios::app);
        fisierBilet << biletPiesa[NumarBilete].ID_Bilet << " " << biletPiesa[NumarBilete].Tip_Bilet << " " << biletPiesa[NumarBilete].Pret_Bilet << '\n';
        fisierBilet.close();
    }
}

void Stergere_Bilet()
{
    system("CLS");
    afisare_bilete();

    unsigned int vID;

    bool valid = false;

    cout << "\n\n";
    cout << setw(5) << " " << "APASA TASTA '0' PENTRU A ANULA";
    cout << "\n\n";
    cout << setw(5) << " " << "Introduceti ID-ul piesei pe care doriti sa il stergeti din baza de date: ";

    while (!valid)
    {
        cin >> vID;
        if (cin.fail())
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
    else
    {
        for (unsigned int i = vID; i <= NumarBilete - 1; i++)
        {
            biletPiesa[i].ID_Bilet = biletPiesa[i + 1].ID_Bilet - 1;
            strcpy(biletPiesa[i].Tip_Bilet, biletPiesa[i + 1].Tip_Bilet);
            biletPiesa[i].Pret_Bilet = biletPiesa[i + 1].Pret_Bilet;
        }
        NumarBilete--;
        copie_ID_Bilet_Max--;
    }

    ofstream fisierBilet("bilet.txt");
    for (unsigned int i = 1; i <= NumarBilete; i++)
        fisierBilet << biletPiesa[i].ID_Bilet << " " << biletPiesa[i].Tip_Bilet << " " << biletPiesa[i].Pret_Bilet << endl;
    fisierBilet.close();
}

void Adaugare_Personal()
{
    system("CLS");
    afisare_personal();

    copie_ID_Personal_Max++;
    NumarPersonalTeatru++;

    cout << "\n\n";
    cout << setw(4) << " " << "Introduceti datele noului angajat (administratie teatru):" << "\n\n";
    cout << setw(6) << " " << "ID-ul angajatului: " << copie_ID_Personal_Max << endl;
    personalTeatru[NumarPersonalTeatru].ID_PersonalTeatru = copie_ID_Personal_Max;

    cout << setw(6) << " " << "Functie: ";
    char vFunctiePersonalTeatru[1001];
    cin.get();
    cin.get(vFunctiePersonalTeatru, 1001);

    for (unsigned int i = 0; i < strlen(vFunctiePersonalTeatru); i++)
        if (vFunctiePersonalTeatru[i] == ' ')
            vFunctiePersonalTeatru[i] = '_';
    strcpy(personalTeatru[NumarPersonalTeatru].Functie_PersonalTeatru,vFunctiePersonalTeatru);

    cout << setw(6) << " " << "Nume angajat: ";
    cin >> personalTeatru[NumarPersonalTeatru].Nume_PersonalTeatru;
    cout << setw(6) << " " << "Prenume angajat: ";
    cin >> personalTeatru[NumarPersonalTeatru].Prenume_PersonalTeatru;
    cout << setw(6) << " " << "CNP angajat: ";

    bool valid = false;
    while (!valid)
    {
        cin >> personalTeatru[NumarPersonalTeatru].CNP_PersonalTeatru;
        if (cin.fail() || strlen(personalTeatru[NumarPersonalTeatru].CNP_PersonalTeatru) != 13)
        {
            cin.clear();
            cin.ignore();
            cout << '\n';
            cerr << setw(6) << " " << "Valoarea introdusa in campul PRET BILET este invalida!" << endl;
            Sleep(1500);
            copie_ID_Personal_Max--;
            Adaugare_Personal();
        }
        else valid = true;
    }

    cout << setw(6) << " " << "Varsta angajat: ";
    cin >> personalTeatru[NumarPersonalTeatru].Varsta_PersonalTeatru;

    ofstream fisierPersonalTeatru;
    fisierPersonalTeatru.open("personal.txt", ios::out | ios::app);
    fisierPersonalTeatru << personalTeatru[NumarPersonalTeatru].ID_PersonalTeatru << " "
                         << personalTeatru[NumarPersonalTeatru].Functie_PersonalTeatru << " "
                         << personalTeatru[NumarPersonalTeatru].Nume_PersonalTeatru << " "
                         << personalTeatru[NumarPersonalTeatru].Prenume_PersonalTeatru << " "
                         << personalTeatru[NumarPersonalTeatru].CNP_PersonalTeatru << " "
                         << personalTeatru[NumarPersonalTeatru].Varsta_PersonalTeatru << endl;
    fisierPersonalTeatru.close();
}

void Stergere_Personal()
{
    system("CLS");
    afisare_personal();

    unsigned int vID;

    bool valid = false;

    cout << "\n\n";
    cout << setw(5) << " " << "APASA TASTA '0' PENTRU A ANULA";
    cout << "\n\n";
    cout << setw(5) << " " << "Introduceti ID-ul angajatului pe care doriti sa il stergeti din baza de date: ";

    while (!valid)
    {
        cin >> vID;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << '\n';
            cerr << setw(6 - 1) << " " << "Valoarea introdusa in campul ID PIESA este invalida!" << endl;
            Sleep(1500);
            Stergere_Personal();
        }
        else valid = true;
    }

    if (vID == 0)
        return;
    else
    {
        for (unsigned int i = vID; i <= NumarPersonalTeatru; i++)
        {
            personalTeatru[i].ID_PersonalTeatru = personalTeatru[i + 1].ID_PersonalTeatru - 1;
            strcpy(personalTeatru[i].Functie_PersonalTeatru, personalTeatru[i + 1].Functie_PersonalTeatru);
            strcpy(personalTeatru[i].Nume_PersonalTeatru, personalTeatru[i + 1].Nume_PersonalTeatru);
            strcpy(personalTeatru[i].Prenume_PersonalTeatru, personalTeatru[i + 1].Prenume_PersonalTeatru);
            strcpy(personalTeatru[i].CNP_PersonalTeatru, personalTeatru[i + 1].CNP_PersonalTeatru);
            personalTeatru[i].Varsta_PersonalTeatru = personalTeatru[i + 1].Varsta_PersonalTeatru;
        }
        NumarPersonalTeatru--;
        copie_ID_Personal_Max--;
    }

    ofstream fisierPersonalTeatru("personal.txt");
    for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
        fisierPersonalTeatru << personalTeatru[i].ID_PersonalTeatru << " "
                             << personalTeatru[i].Functie_PersonalTeatru << " "
                             << personalTeatru[i].Nume_PersonalTeatru << " "
                             << personalTeatru[i].Prenume_PersonalTeatru << " "
                             << personalTeatru[i].CNP_PersonalTeatru << " "
                             << personalTeatru[i].Varsta_PersonalTeatru << endl;
    fisierPersonalTeatru.close();
}

///Ioana
///Afisati toate piesele care se tin dupa ora…(ora va fi introdusa de la tastatura)

///Afisati toate piesele care se tin dupa ora…(ora va fi introdusa de la tastatura)
void piese_dupa_ora()
{
    char ora[6];
    cin.get(ora,6);
    for (unsigned int i = 1; i <= NumarPiese; i++)
    {
        if(strcmp(ora,piesaTeatru[i].Ora_Piesa)<=0)
            cout<<piesaTeatru[i].Nume_Piesa<<" "<<piesaTeatru[i].Ora_Piesa<<endl;
    }
}

///Afisarea primelor 3 cele mai incapatoare sali din teatru
void cele_mai_mari_3_sali ()
{
    system("CLS");

    cout << "\n\n";
    cout << setw(5) << " " << "Primele 3 cele mai incapatoare sali din teatru: " << "\n\n";
    unsigned int i,aux,j;
    unsigned int v_locuri[1000], v_sala[1000];

    for(i=1; i<=NumarSali-1; i++)
    {
        v_locuri[i]=salaTeatru[i].Nr_Scaune+salaTeatru[i].Nr_Scaune_Loja;
        v_sala[i]=salaTeatru[i].ID_Sala;
    }
    for(i=1; i<=NumarSali-2; i++)
        for(j=i+1; j<=NumarSali-1; j++)
            if(v_locuri[i]<v_locuri[j])
            {
                aux=v_locuri[i];
                v_locuri[i]=v_locuri[j];
                v_locuri[j]=aux;
                aux=v_sala[i];
                v_sala[i]=v_sala[j];
                v_sala[j]=aux;
            }
    for(i=1; i<=3; i++)
        cout << setw(5) << " " <<"Sala: " << v_sala[i]<< " cu " << v_locuri[i] << " locuri" << endl;

    cout << '\n' << setw(4) << " " << "Apasati enter pentru a va intoarce la meniul precedent...";
    _getch();
}

///Afisarea tuturor actorilor a caror varsta este mai mare sau egala cu … ani.
void varsta_mai_mare_actori()
{
    unsigned int nrMaxCaractereNume = 0;
    for (unsigned int i = 1; i <= NumarActori; i++)
        if (strlen(actorTeatru[i].Nume_Actor) > nrMaxCaractereNume)
            nrMaxCaractereNume = strlen(actorTeatru[i].Nume_Actor);

    unsigned int nrMaxCaracterePrenume = 0;
    for (unsigned int i = 1; i <= NumarActori; i++)
        if (strlen(actorTeatru[i].Prenume_Actor) > nrMaxCaracterePrenume)
            nrMaxCaracterePrenume = strlen(actorTeatru[i].Prenume_Actor);

    cout << "\n\n";
    unsigned int varsta = 0,i;
    cout << setw(4) << " " << "Afisarea tuturor actorilor dupa o anumita varsta" << "\n\n";
    cout << setw(4) << " " << "Introduceti varsta: ";
    cin>>varsta;
    system("CLS");
    cout << setw(4) << " " << "\n\n";
    cout << setw(4) << " " << "Actorii a caror varsta este mai mare sau egala cu " << varsta << " ani" << '\n';
    fillLinieConsola(60);

    cout << setw(5) << " " << "Nume" << setw(nrMaxCaractereNume) << " " << "Prenume" << setw(7) << " " << "Varsta" << '\n';
    fillLinieConsola(60);

    for(i=0; i<NumarActori; i++)
        if(actorTeatru[i].Varsta_Actor>=varsta)
            cout<< setw(4) << " " <<actorTeatru[i].Nume_Actor << setw(nrMaxCaractereNume + 5 - strlen(actorTeatru[i].Nume_Actor))
                <<" "<<actorTeatru[i].Prenume_Actor << setw(nrMaxCaracterePrenume + 5 - strlen(actorTeatru[i].Prenume_Actor)) << " "
                << actorTeatru[i].Varsta_Actor <<endl;

    fillLinieConsola(60);

    cout << '\n' << setw(4) << " " << "Apasati enter pentru a va intoarce la meniul precedent...";
    _getch();
}
///Afisarea tuturor actorilor a caror varsta este mai mica sau egala cu … ani
void varsta_mai_mica_actori()
{

    unsigned int nrMaxCaractereNume = 0;
    for (unsigned int i = 1; i <= NumarActori; i++)
        if (strlen(actorTeatru[i].Nume_Actor) > nrMaxCaractereNume)
            nrMaxCaractereNume = strlen(actorTeatru[i].Nume_Actor);

    unsigned int nrMaxCaracterePrenume = 0;
    for (unsigned int i = 1; i <= NumarActori; i++)
        if (strlen(actorTeatru[i].Prenume_Actor) > nrMaxCaracterePrenume)
            nrMaxCaracterePrenume = strlen(actorTeatru[i].Prenume_Actor);

    cout << "\n\n";
    unsigned int varsta = 0,i;
    cout << setw(4) << " " << "Afisarea tuturor actorilor inainte o anumita varsta" << "\n\n";
    cout << setw(4) << " " << "Introduceti varsta: ";
    cin>>varsta;

    cout << setw(4) << " " << "\n\n";
    cout << setw(4) << " " << "Actorii a caror varsta este mai mica sau egala cu " << varsta << " ani" << '\n';
    fillLinieConsola(60);

    cout << setw(5) << " " << "Nume" << setw(nrMaxCaractereNume) << " " << "Prenume" << setw(7) << " " << "Varsta" << '\n';
    fillLinieConsola(60);
     for(i=0;i<NumarActori;i++)
        if(actorTeatru[i].Varsta_Actor<=varsta)
           cout<< setw(4) << " " <<actorTeatru[i].Nume_Actor << setw(nrMaxCaractereNume + 5 - strlen(actorTeatru[i].Nume_Actor))
                <<" "<<actorTeatru[i].Prenume_Actor << setw(nrMaxCaracterePrenume + 5 - strlen(actorTeatru[i].Prenume_Actor)) << " "
                << actorTeatru[i].Varsta_Actor <<endl;
     fillLinieConsola(60);

    cout << '\n' << setw(4) << " " << "Apasati enter pentru a va intoarce la meniul precedent...";
    _getch();
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
             << '\n';

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
                    cautare_piesa();
                }
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
                    unsigned int Meniu_Mod_Date_Piesa;

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
                        cin >> Meniu_Mod_Date_Piesa;

                        switch (Meniu_Mod_Date_Piesa)
                        {
                        case 1:
                            Adaugare_Piese();
                            break;
                        case 2:
                            Stergere_Piese();
                            break;
                        }
                    }
                    while (Meniu_Mod_Date_Piesa != 0);
                }
                break;
                }
            }
            while (Meniu_2 != 0);
        }
        break;
        case 2:
        {
            unsigned int Meniu_Mod_Sali;

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
                cin >> Meniu_Mod_Sali;

                switch (Meniu_Mod_Sali)
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
            while (Meniu_Mod_Sali != 0);
        }
        break;
        case 3:
        {
            unsigned int Meniu_Mod_Bilet;

            do
            {
                system("CLS");
                afisare_bilete();

                cout << '\n';
                cout << setw(5 - 1) << " " << "MODIFICAREA DATELOR" << "\n\n";
                cout << setw(6) << " " << "1. Adauga tip de bilet" << '\n';
                cout << setw(6) << " " << "2. Sterge tip de bilet" << '\n';
                cout << setw(6) << " " << "0. Inapoi" << "\n\n";

                cout << setw(5 - 1) << " " << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
                cin >> Meniu_Mod_Bilet;

                switch (Meniu_Mod_Bilet)
                {
                case 1:
                    Adaugare_Bilet();
                    _getch();
                    break;
                case 2:
                    Stergere_Bilet();
                    break;
                }
            }
            while (Meniu_Mod_Bilet != 0);
        }
        break;
        case 4:
        {
            unsigned int Meniu_Mod_Actori;

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
                cin >> Meniu_Mod_Actori;

                switch (Meniu_Mod_Actori)
                {
                case 1:
                    Adaugare_Actori();
                    _getch();
                    break;
                case 2:
                    Stergere_Actori();
                    break;
                }
            }
            while (Meniu_Mod_Actori != 0);
        }
        break;
        case 5:
        {
            unsigned int Meniu_Mod_Personal;

            do
            {
                system("CLS");
                afisare_personal();

                cout << '\n';
                cout << setw(5 - 1) << " " << "MODIFICAREA DATELOR" << "\n\n";
                cout << setw(6) << " " << "1. Adauga personal teatru" << '\n';
                cout << setw(6) << " " << "2. Sterge personal teatru" << '\n';
                cout << setw(6) << " " << "0. Inapoi" << "\n\n";

                cout << setw(5 - 1) << " " << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
                cin >> Meniu_Mod_Personal;

                switch (Meniu_Mod_Personal)
                {
                case 1:
                    Adaugare_Personal();
                    break;
                case 2:
                    Stergere_Personal();
                    break;
                }
            }
            while (Meniu_Mod_Personal != 0);
        }
        break;
        }
    }
    while (Meniu_1 != 0);

    return 0;
}
