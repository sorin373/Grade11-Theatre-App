#include <iostream> // cin / cout
#include <fstream>  // input din fisier
#include <cstring>  // string-uri
#include <iomanip>  // manipularea output-ului
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

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
    char Nume_Actor[101];
    char Prenume_Actor[101];
    unsigned int Varsta_Actor;
    char Email_Actor[101];
    long long unsigned int CNP_Actor;
} actorTeatru[35];

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
    while (fisierActor >> actorTeatru[NumarActori].ID_Actor >> actorTeatru[NumarActori].Nume_Actor >> actorTeatru[NumarActori].Prenume_Actor
        >> actorTeatru[NumarActori].Varsta_Actor >> actorTeatru[NumarActori].Email_Actor >> actorTeatru[NumarActori].CNP_Actor)
        NumarActori++;
    NumarActori--;
    fisierActor.close();
}

void citire_piese()
{
    ifstream fisierPiesa("piesa.txt");          // fisier cu piesele care urmeaza sa fie jucate in urmatoarea saptamana
    while (fisierPiesa >> piesaTeatru[NumarPiese].ID_Piesa >> piesaTeatru[NumarPiese].Nume_Piesa >> piesaTeatru[NumarPiese].ID_Sala
        >> piesaTeatru[NumarPiese].Data_Piesa >> piesaTeatru[NumarPiese].Ora_Piesa)
        NumarPiese++;
    NumarPiese--;
    fisierPiesa.close();
}

void citire_personaje_piese()
{
    ifstream fisierPersonaj("personaj.txt");    // fisier cu personajele din fiecare piesa de teatru
    while (fisierPersonaj >> personajPiesa[NumarPersonaje].ID_Piesa >> personajPiesa[NumarPersonaje].ID_Actor >> personajPiesa[NumarPersonaje].Nume_Personaj)
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
        if (strlen(piesaTeatru[i].Nume_Piesa) > NumarMaxCaractere) NumarMaxCaractere = strlen(piesaTeatru[i].Nume_Piesa);

    // Afisarea pieselor de teatru (ID, NUME, DATA)
    cout << "ID" << setw(5 + 1) << " " << "Nume"<< setw(NumarMaxCaractere + 1) << " " << "Data" << "\n\n";

    for (unsigned int i = 1; i <= NumarPiese; i++)
        cout << piesaTeatru[i].ID_Piesa << setw(5) << " " << piesaTeatru[i].Nume_Piesa
        << setw(NumarMaxCaractere - strlen(piesaTeatru[i].Nume_Piesa) + 5) << " " << piesaTeatru[i].Data_Piesa << endl;
}

void afisare_sali()
{
    for (unsigned int i = 1; i <= NumarSali; i++)
        cout << "Sala " << salaTeatru[i].ID_Sala << ": " << salaTeatru[i].Nr_Scaune << " scaune normale " << salaTeatru[i].Nr_Scaune_Loja << " scaune in loja" << endl;
}

void afisare_bilete()
{
    for (unsigned int i = 1; i <= NumarBilete; i++)
        cout << biletPiesa[i].ID_Bilet << ": " << biletPiesa[i].Tip_Bilet << ", " << biletPiesa[i].Pret_Bilet << endl;
}

void afisare_actori()
{
    for (unsigned int i = 1; i <= NumarActori; i++)
        cout << actorTeatru[i].Nume_Actor << endl;
}

void afisare_personal()
{
    for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
        cout << personalTeatru[i].Nume_PersonalTeatru << endl;
}

int main()
{
    // Citirea datelor din fisierele corespunzatoare
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
        cout << "MENIU" << "\n\n";

        cout << "1. Piesele ce urmeaza sa fie jucate in perioasa 10.07 - 17.07.2022." << endl;
        cout << "2. Sali de teatru." << endl;
        cout << "3. Tipurile de bilete disponibile la vanzare." << endl;
        cout << "4. Actorii care joaca in piesele de teatru." << endl;
        cout << "5. Personalul teatrului." << endl;
        cout << "0. Iesire" << "\n\n";

        cout << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: "; cin >> Meniu_1;

        switch (Meniu_1)
        {
        case 1:
        {
            unsigned int Meniu_2;

            do
            {
                system("CLS"); // sterge continut consola
                afisare_piese(); cout << endl;

                // Continutul celui de al doilea meniu
                cout << "1. Detalii desre piesele de teatru." << endl;
                cout << "2. Personajele care joaca in piesele de teatru si actorii corespunzatori acestora." << endl;
                cout << "3. Profit si cheltuieli." << endl;
                cout << "0. Inapoi." << "\n\n";

                cout << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: "; cin >> Meniu_2;

                switch (Meniu_2)
                {

                case 1: // Cautarea pieselor in baza de date dupa ID-ul lor (vID_Piesa), introdus de la tastatura
                {
                    char vNume_Piesa[101];
                    unsigned int ok = 0;

                    cout << endl << "Tasteaza numele piesei: "; cin.get(); cin.get(vNume_Piesa, 101);

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
                    system("CLS"); // sterge continut consola
                    cout << "Profit si Cheltuieli" << "\n";

                    unsigned int vID_Piesa;
                    unsigned int ok = 0, v = 0;

                    cout << endl << "Tasteaza ID-ul piesei cautate: "; cin >> vID_Piesa;

                    for (unsigned int i = 1; i <= NumarPiese && ok == 0; i++)
                        if (piesaTeatru[i].ID_Piesa == vID_Piesa)
                        {
                            for (int j = 1; j <= NumarSpectatori; j++)
                                if (spectatorPiesa[j].ID_Piesa == piesaTeatru[i].ID_Piesa)
                                    v = v + biletPiesa[piesaTeatru[i].ID_Piesa].Pret_Bilet;
                            ok = 1;
                        }
                    cout << "Biletele cumparate pentru aceasta piesa alcatuiesc " << v << " lei" << "\n\n";
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
            afisare_actori();
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
