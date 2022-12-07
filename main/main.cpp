#include <iostream> // cin / cout
#include <fstream>  // input din fisier
#include <cstring>  // string-uri
#include <iomanip>  // manipularea output-ului
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include <windows.h>
#include <wincon.h>

using namespace std;

/// Declarare structuri de date
struct sala
{
    unsigned int ID_Sala;
    unsigned int Nr_Scaune;
    unsigned int Nr_Scaune_Loja;
} salaTeatru[11];

struct actor
{
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
    unsigned int ID_Piesa;
    unsigned int ID_Sala;
    char Nume_Piesa[101];
    char Data_Piesa[11];
    char Ora_Piesa[6];
} piesaTeatru[201];

struct personaj_piesa
{
    unsigned int ID_Piesa;
    unsigned int ID_Actor;
    char Nume_Personaj[101];
} personajPiesa[401];

struct bilet
{
    unsigned int ID_Bilet;
    float Pret_Bilet;
    char Tip_Bilet[41];
} biletPiesa[6];

struct personal
{
    unsigned int ID_PersonalTeatru;
    char Nume_PersonalTeatru[101];
    char Prenume_PersonalTeatru[101];
    char CNP_PersonalTeatru[15];
    unsigned int Varsta_PersonalTeatru;
    char Functie_PersonalTeatru[101];

} personalTeatru[101];

struct spectator
{
    unsigned int ID_Spectator;
    unsigned int ID_Bilet;
    unsigned int ID_Piesa;
} spectatorPiesa[401];

// Declarare contoarelor
unsigned int NumarActori = 1, NumarPiese = 1, NumarBilete = 1, NumarSali = 1, NumarPersonalTeatru = 1, NumarSpectatori = 1, NumarPersonaje = 1;

/// Functii ajutatoare (daca exista erori comenteaza toate subprogramele din functii ajutatoare)
void fillLinieConsola(unsigned int vWidth)
{
    cout << setw(5 - 2) << " ";

    char fillLine;
    fillLine = cout.fill('_');
    cout.width(vWidth);
    cout << '_' << endl;
    cout.fill(fillLine);
    cout << endl;
}

void SetCursorSize(const int iSize = 0)
{
    HANDLE cxHandle;
    cxHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = iSize;
    cci.bVisible = true;
    SetConsoleCursorInfo(cxHandle, &cci);
}

//CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX
typedef struct _CONSOLE_FONT_INFOEX
{
    ULONG cbSize;
    DWORD nFont;
    COORD dwFontSize;
    UINT  FontFamily;
    UINT  FontWeight;
    WCHAR FaceName[LF_FACESIZE];
} CONSOLE_FONT_INFOEX, *PCONSOLE_FONT_INFOEX;

//the function declaration begins
#ifdef __cplusplus
extern "C" {
#endif
BOOL WINAPI SetCurrentConsoleFontEx(HANDLE hConsoleOutput, BOOL bMaximumWindow, PCONSOLE_FONT_INFOEX
                                    lpConsoleCurrentFontEx);
#ifdef __cplusplus
}
#endif
//the function declaration ends

/// Citire date din fisierele corespunzatoare
void citire_sali()
{
    ifstream fisierSala("sala.txt");             // fisier sali teatru
    while (fisierSala >> salaTeatru[NumarSali].ID_Sala >> salaTeatru[NumarSali].Nr_Scaune >> salaTeatru[NumarSali].Nr_Scaune_Loja)
        NumarSali++;
    NumarSali--;
    fisierSala.close();
}

void citire_actori()
{
    ifstream fisierActor("actor.txt");           // fisier actori care joaca in piesele de teatru
    while (fisierActor >> actorTeatru[NumarActori].ID_Actor >> actorTeatru[NumarActori].ID_Piesa >> actorTeatru[NumarActori].Nume_Actor
        >> actorTeatru[NumarActori].Prenume_Actor >> actorTeatru[NumarActori].Varsta_Actor >> actorTeatru[NumarActori].Email_Actor
        >> actorTeatru[NumarActori].CNP_Actor >> actorTeatru[NumarActori].Sex_Actor)
        NumarActori++;
    NumarActori--;
    fisierActor.close();
}

void citire_piese()
{
    ifstream fisierPiesa("piesa.txt");          // fisier cu piesele care urmeaza sa fie jucate in urmatoarea saptamana
    while (fisierPiesa >> piesaTeatru[NumarPiese].ID_Piesa >> piesaTeatru[NumarPiese].ID_Sala
        >> piesaTeatru[NumarPiese].Data_Piesa >> piesaTeatru[NumarPiese].Ora_Piesa)
        {
            fisierPiesa.get();
            fisierPiesa.get(piesaTeatru[NumarPiese].Nume_Piesa,101);
            NumarPiese++;
        }
    NumarPiese--;
    fisierPiesa.close();
}

void citire_personaje_piese()
{
    ifstream fisierPersonaj("personaj.txt");    // fisier cu personajele din fiecare piesa de teatru
    while (fisierPersonaj >> personajPiesa[NumarPersonaje].ID_Piesa >> personajPiesa[NumarPersonaje].ID_Actor
           >> personajPiesa[NumarPersonaje].Nume_Personaj)
        NumarPersonaje++;
    NumarPersonaje--;
    fisierPersonaj.close();
}

void citire_bilete()
{
    ifstream fisierBilet("bilet.txt");          // fisier cu tipurile de bilete disponibile la teatru
    while (fisierBilet >> biletPiesa[NumarBilete].ID_Bilet >> biletPiesa[NumarBilete].Tip_Bilet >> biletPiesa[NumarBilete].Pret_Bilet)
        NumarBilete++;
    NumarBilete--;
    fisierBilet.close();
}

void citire_personal()
{
    ifstream fisierPersonalTeatru("personal.txt"); // fisier cu personalul care lucreaza in incinta teatrului
    while (fisierPersonalTeatru >> personalTeatru[NumarPersonalTeatru].ID_PersonalTeatru
        >> personalTeatru[NumarPersonalTeatru].Functie_PersonalTeatru >> personalTeatru[NumarPersonalTeatru].Nume_PersonalTeatru
        >> personalTeatru[NumarPersonalTeatru].Prenume_PersonalTeatru >> personalTeatru[NumarPersonalTeatru].CNP_PersonalTeatru
        >> personalTeatru[NumarPersonalTeatru].Varsta_PersonalTeatru)
        NumarPersonalTeatru++;
    NumarPersonalTeatru--;
    fisierPersonalTeatru.close();
}

void citire_spectatori()
{
    ifstream fisierSpectator("spectator.txt"); // fisier cu spectatorii care si-au rezervat loc la fiecare piesa de teatru
    while (fisierSpectator >> spectatorPiesa[NumarSpectatori].ID_Spectator >> spectatorPiesa[NumarSpectatori].ID_Bilet
           >> spectatorPiesa[NumarSpectatori].ID_Piesa)
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
        if (strlen(piesaTeatru[i].Nume_Piesa) > NumarMaxCaractere) NumarMaxCaractere = strlen(piesaTeatru[i].Nume_Piesa);

    // Afisarea pieselor de teatru (ID, NUME, DATA)
    cout << "\n\n" << setw(5 - 1) << " " << "ID" << setw(5 + 1) << " " << "Nume"<< setw(NumarMaxCaractere + 1) << " " << "Data" << endl;
    fillLinieConsola(85); // umple toate linia din consola cu  '_'

    for (unsigned int i = 1; i <= NumarPiese; i++)
        cout << setw(5) << " " << piesaTeatru[i].ID_Piesa << setw(5) << " " << piesaTeatru[i].Nume_Piesa
        << setw(NumarMaxCaractere - strlen(piesaTeatru[i].Nume_Piesa) + 5) << " " << piesaTeatru[i].Data_Piesa << endl;
}

void afisare_sali()
{
    for (unsigned int i = 1; i <= NumarSali; i++)
        cout << "Sala " << salaTeatru[i].ID_Sala << ": " << salaTeatru[i].Nr_Scaune << " scaune normale "
        << salaTeatru[i].Nr_Scaune_Loja << " scaune in loja" << endl;
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
        if (strlen(actorTeatru[i].Nume_Actor) > NumarMaxCaractereNume) NumarMaxCaractereNume = strlen(actorTeatru[i].Nume_Actor);

    // Determinarea prenumelui cu numar maxim de caractere
    unsigned int NumarMaxCaracterePrenume = 0;

    for (unsigned int i = 0; i <= NumarActori; i++)
        if (strlen(actorTeatru[i].Prenume_Actor) > NumarMaxCaracterePrenume) NumarMaxCaracterePrenume = strlen(actorTeatru[i].Prenume_Actor);

    // Determinarea Email-ului cu numar maxim de caractere
    unsigned int NumarMaxCaractereEmail = 0;

    for (unsigned int i = 0; i < NumarActori; i++)
        if (strlen(actorTeatru[i].Email_Actor) > NumarMaxCaractereEmail) NumarMaxCaractereEmail = strlen(actorTeatru[i].Email_Actor);

    // Afisare Actori
    cout << "\n\n" << setw(5 - 1) << " " << "ID_Actor" << " " << "ID_Piesa" << setw(5) << " " << "Nume_Actor" << setw(NumarMaxCaractereNume) <<" " << "Prenume_Actor" << setw(NumarMaxCaracterePrenume - 5) << " "
    << "Varsta_Actor" << setw(10) << " " << "Email_Actor" << "\n";

    fillLinieConsola(115); // umple toate linia din consola cu  '_'

    for (unsigned int i = 1; i <= NumarActori; i++)
        cout << setw(5) << " " << actorTeatru[i].ID_Actor << setw(10 - 1) << " " << actorTeatru[i].ID_Piesa << setw(10 - 1) << " " << actorTeatru[i].Nume_Actor
        << setw(NumarMaxCaractereNume - strlen(actorTeatru[i].Nume_Actor) + 10) << " " << actorTeatru[i].Prenume_Actor
        << setw(NumarMaxCaracterePrenume - strlen(actorTeatru[i].Prenume_Actor) + 10) << " " << actorTeatru[i].Varsta_Actor << " ani"
        << setw(10) << " " << actorTeatru[i].Email_Actor << setw(NumarMaxCaractereEmail - strlen(actorTeatru[i].Email_Actor) + 10) << "\n";

}

void afisare_personal()
{
    for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
        cout << personalTeatru[i].Nume_PersonalTeatru << endl;
}

int main()
{
    /// _______TERMINAL_______

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Latimea caracterului
    cfi.dwFontSize.Y = 20;                  // Inaltimea
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = 700;

    std::wcscpy(cfi.FaceName, L"Consolas"); // Font
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

    ::SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);  //Full screen
    system(""); /// Add color
    SetCursorSize(25);

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
        cout << "\n\n" << setw(35) << " " << "MENIU" << "\n";

        fillLinieConsola(70); // umple toate linia din consola cu  '_'

        cout << setw(5 - 1) << " " << "1. Piesele ce urmeaza sa fie jucate in perioasa 10.07 - 17.07.2022." << endl;
        cout << setw(5 - 1) << " " << "2. Sali de teatru." << endl;
        cout << setw(5 - 1) << " " << "3. Tipurile de bilete disponibile la vanzare." << endl;
        cout << setw(5 - 1) << " " << "4. Actorii care joaca in piesele de teatru." << endl;
        cout << setw(5 - 1) << " " << "5. Personalul teatrului." << endl;
        cout << setw(5 - 1) << " " << "0. Iesire" << "\n\n";

        fillLinieConsola(70); // umple toate linia din consola cu  '_'

        cout << setw(5 - 1) << " " << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: "; cin >> Meniu_1;

        switch (Meniu_1)
        {
        case 1:
        {
            unsigned int Meniu_2;

            do
            {
                system("CLS"); // sterge continut consola
                afisare_piese(); cout << endl;
                fillLinieConsola(85); // umple toate linia din consola cu  '_'

                // Continutul celui de al doilea meniu
                cout << setw(5 - 1) << " " << "1. Detalii desre piesele de teatru." << endl;
                cout << setw(5 - 1) << " " << "2. Personajele care joaca in piesele de teatru si actorii corespunzatori acestora." << endl;
                cout << setw(5 - 1) << " " << "3. Profit si cheltuieli." << endl;
                cout << setw(5 - 1) << " " << "0. Inapoi." << "\n\n";

                fillLinieConsola(85);

                cout << setw(5 - 1) << " " << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: "; cin >> Meniu_2;

                switch (Meniu_2)
                {

                case 1: // Cautarea pieselor in baza de date dupa numele lor (vNume_Piesa), introdus de la tastatura
                        // Modificat din ID => Nume !!!!!!!!!!!!!!!
                        // De lucrat la afisare piese dupa cautarea
                        // implementare cautarii dupa data, ID si nume
                {
                    char vNume_Piesa[101];
                    unsigned int ok = 0;

                    cout << endl << setw(5 - 1) << " " << "Tasteaza numele piesei: "; cin.get(); cin.get(vNume_Piesa, 101);

                    for (unsigned int i = 1; i <= NumarPiese && ok == 0; i++)
                        if (stricmp(piesaTeatru[i].Nume_Piesa, vNume_Piesa) == 0)
                        {
                            system("CLS"); // sterge continut consola

                            cout << "ID: " << piesaTeatru[i].ID_Piesa << endl;
                            cout << "Nume: " << piesaTeatru[i].Nume_Piesa << endl;
                            cout << "Sala: " << piesaTeatru[i].ID_Sala << endl;
                            cout << "Data: " << piesaTeatru[i].Data_Piesa << endl;
                            cout << "Ora: " << piesaTeatru[i].Ora_Piesa << "\n\n";

                            cout << "Apasa enter pentru a te intoarce la meniul precedent..." << endl;

                            ok = 1;
                        }
                }
                    _getch();
                    break;

                case 2:
                {
                    unsigned int vID_Piesa;
                    unsigned int ok = 0;

                    cout << endl << "Tasteaza ID-ul piesei cautate: "; cin >> vID_Piesa; cout << "\n\n";

                    for (unsigned int i = 1; i <= NumarPiese && ok == 0; i++)
                        if (piesaTeatru[i].ID_Piesa == vID_Piesa)
                        {
                            for (unsigned int j = 1; j <= NumarPersonaje; j++)
                                if (personajPiesa[j].ID_Piesa == piesaTeatru[i].ID_Piesa)
                                {
                                    cout << personajPiesa[j].Nume_Personaj;

                                    unsigned int k = 1;
                                    while (actorTeatru[k].ID_Actor != personajPiesa[j].ID_Actor) k++;

                                    cout << " (jucat de " << actorTeatru[k].Nume_Actor << ")" << endl;
                                }

                            ok = 1; // iese din 'for'
                        }

                }
                    _getch();
                    break;

                case 3:
                {
                    unsigned int vID_Piesa;
                    unsigned int ok = 0, v = 0;

                    cout << endl << "Tasteaza ID-ul piesei cautate: "; cin >> vID_Piesa;

                    for (unsigned int i = 1; i <= NumarPiese && ok == 0; i++)
                        if (piesaTeatru[i].ID_Piesa == vID_Piesa)
                        {
                            for (unsigned int j = 1; j <= NumarSpectatori; j++)
                                if (spectatorPiesa[j].ID_Piesa == piesaTeatru[i].ID_Piesa)
                                    v = v + biletPiesa[spectatorPiesa[j].ID_Bilet].Pret_Bilet;
                            ok = 1;
                        }
                    cout << "Biletele cumparate pentru aceasta piesa alcatuiesc " << v << " lei." << "\n\n";
                    cout << "Apasa enter pentru a te intoarce la meniul precedent..." << endl;

                }
                    _getch();
                    break;
                }
            } while (Meniu_2 != 0);
        }
        break;
        case 2:
        {
            afisare_sali();
        }
            _getch();
            break;
        case 3:
        {
            afisare_bilete();
        }
            _getch();
            break;
        case 4:
        {
            system("CLS");

            afisare_actori();
            fillLinieConsola(115); // umple toate linia din consola cu  '_'

            cout << setw(5 - 1) << " " << "1. Cauta dupa numele personajului." << endl;
            cout << setw(5 - 1) << " " << "2. Cauta dupa ID-ul piesei." << "\n\n";

            /// TODO
            unsigned int Meniu_3;

            //cout << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: "; cin >> Meniu_3;

        }
            _getch();
            break;
        case 5:
        {
            afisare_personal();
        }
            _getch();
            break;
        }

    } while (Meniu_1 != 0);

    return 0;
}
