#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

using namespace std;

/// Declarare contoarelor
unsigned int NumarActori = 1, NumarPiese = 1, NumarBilete = 1, NumarSali = 1, NumarPersonalTeatru = 1, NumarSpectatori = 1, NumarPersonaje = 1, NumarPieseVechi = 1, NumarSpectatoriVechi = 1;
unsigned int copie_ID_Sala_Max = 0, copie_ID_Actor_Max = 0, copie_ID_Piesa_Max = 0, copie_ID_Bilet_Max = 0, copie_ID_Personal_Max = 0, copie_ID_Piesa_Veche_Max = 0;
unsigned int contorVenit = 1;

/// Declarare structuri de date
struct sala
{
public:
    unsigned int ID_Sala;
    unsigned int Nr_Scaune;
    unsigned int Nr_Scaune_Loja;
} salaTeatru[1001];

struct actor
{
public:
    unsigned int ID_Actor;
    unsigned int ID_Piesa;
    char Nume_Actor[1001];
    char Prenume_Actor[1001];
    unsigned int Varsta_Actor;
    char Email_Actor[1001];
    char CNP_Actor[15];
    char Sex_Actor;
} actorTeatru[1001];

struct piesa
{
public:
    unsigned int ID_Piesa;
    unsigned int ID_Sala;
    char Nume_Piesa[1001];
    char Data_Piesa[1001];
    char Ora_Piesa[6];
    unsigned int ID_PersonalTeatru;
} piesaTeatru[1001];

struct personaj_piesa
{
public:
    unsigned int ID_Piesa;
    unsigned int ID_Actor;
    char Nume_Personaj[201];
} personajPiesa[1001];

struct bilet
{
public:
    unsigned int ID_Bilet;
    float Pret_Bilet;
    char Tip_Bilet[1001];
} biletPiesa[6];

struct personal
{
public:
    unsigned int ID_PersonalTeatru;
    char Nume_PersonalTeatru[1001];
    char Prenume_PersonalTeatru[1001];
    char CNP_PersonalTeatru[15];
    unsigned int Varsta_PersonalTeatru;
    char Functie_PersonalTeatru[1001];

} personalTeatru[1001];

struct spectator
{
public:
    unsigned int ID_Spectator;
    unsigned int ID_Bilet;
    unsigned int ID_Piesa;
    unsigned int loja;
} spectatorPiesa[1001], spectator_vechi[1001];

struct piesa_v
{
public:
    unsigned int ID_Piesa;
    unsigned int ID_Sala;
    char Nume_Piesa[101];
    char Data_Piesa[11];
    unsigned int ID_PersonalTeatru;
} piesa_veche[1001];

struct venit
{
public:
    unsigned int ID_Piesa;
    char Data_Piesa[1001];
    float suma;
} venitPiesa[1001];

/// Functii ajutatoare
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
    while (fisierActor >> actorTeatru[NumarActori].ID_Actor >> actorTeatru[NumarActori].ID_Piesa >> actorTeatru[NumarActori].Nume_Actor >> actorTeatru[NumarActori].Prenume_Actor >> actorTeatru[NumarActori].Varsta_Actor >> actorTeatru[NumarActori].Email_Actor >> actorTeatru[NumarActori].CNP_Actor >> actorTeatru[NumarActori].Sex_Actor)
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
    while (fisierPersonalTeatru >> personalTeatru[NumarPersonalTeatru].ID_PersonalTeatru >> personalTeatru[NumarPersonalTeatru].Functie_PersonalTeatru >> personalTeatru[NumarPersonalTeatru].Nume_PersonalTeatru >> personalTeatru[NumarPersonalTeatru].Prenume_PersonalTeatru >> personalTeatru[NumarPersonalTeatru].CNP_PersonalTeatru >> personalTeatru[NumarPersonalTeatru].Varsta_PersonalTeatru)
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
    while (fisierSpectator >> spectatorPiesa[NumarSpectatori].ID_Spectator >> spectatorPiesa[NumarSpectatori].ID_Bilet >> spectatorPiesa[NumarSpectatori].ID_Piesa >> spectatorPiesa[NumarSpectatori].loja)
        NumarSpectatori++;
    NumarSpectatori--;
    fisierSpectator.close();
}

void citire_piese_vechi()
{
    ifstream fisierPiesaVeche("piesa_veche.txt");
    while (fisierPiesaVeche >> piesa_veche[NumarPieseVechi].ID_Piesa >> piesa_veche[NumarPieseVechi].ID_Sala >> piesa_veche[NumarPieseVechi].ID_PersonalTeatru >> piesa_veche[NumarPieseVechi].Data_Piesa)
    {
        copie_ID_Piesa_Veche_Max = piesa_veche[NumarPieseVechi].ID_Piesa;
        fisierPiesaVeche.get();
        fisierPiesaVeche.get(piesa_veche[NumarPieseVechi].Nume_Piesa, 101);
        NumarPieseVechi++;
    }
    NumarPieseVechi--;
    fisierPiesaVeche.close();
}

void citire_spectatori_vechi()
{
    ifstream fisierSpectatorVechi("spectator_vechi.txt");
    while (fisierSpectatorVechi >> spectator_vechi[NumarSpectatoriVechi].ID_Spectator >> spectator_vechi[NumarSpectatoriVechi].ID_Bilet >> spectator_vechi[NumarSpectatoriVechi].ID_Piesa >> spectator_vechi[NumarSpectatoriVechi].loja)
        NumarSpectatoriVechi++;
    NumarSpectatoriVechi--;
    fisierSpectatorVechi.close();
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
         << "Nume" << setw(NumarMaxCaractere + 4) << " "
         << "Data" << setw(10) << " "
         << "Ora" << setw(5 + 3) << " "
         << "Regizor" << endl;
    fillLinieConsola(90); // umple toate linia din consola cu  '_'

    for (unsigned int i = 1; i <= NumarPiese; i++)
    {
        cout << setw(5) << " " << piesaTeatru[i].ID_Piesa << setw(5) << " " << piesaTeatru[i].Nume_Piesa
             << setw(NumarMaxCaractere - strlen(piesaTeatru[i].Nume_Piesa) + 5) << " " << piesaTeatru[i].Data_Piesa << " "
             << setw(5) << " " << piesaTeatru[i].Ora_Piesa << setw(5) << " ";

        for (unsigned int j = 0; j <= NumarPersonalTeatru; j++)
            if (personalTeatru[j].ID_PersonalTeatru == piesaTeatru[i].ID_PersonalTeatru)
                cout << personalTeatru[j].Nume_PersonalTeatru << " " << personalTeatru[j].Prenume_PersonalTeatru << endl;
    }
    fillLinieConsola(90); // umple toate linia din consola cu  '_'
}

void afisare_istoric_piese()
{
    // Determinarea piesei cu numar maxim de caractere
    unsigned int NumarMaxCaractere = 0;

    for (unsigned int i = 1; i <= NumarPieseVechi; i++)
        if (strlen(piesa_veche[i].Nume_Piesa) > NumarMaxCaractere)
            NumarMaxCaractere = strlen(piesa_veche[i].Nume_Piesa);

    // Afisarea pieselor de teatru (ID, NUME, DATA)
    cout << "\n\n"
         << setw(5) << " "
         << "ID" << setw(10) << " "
         << "Nume" << setw(NumarMaxCaractere - 2) << " "
         << "Data" << setw(10) << " "
         << "Regizor" << endl;
    fillLinieConsola(85); // umple toate linia din consola cu  '_'

    for (unsigned int i = 1; i <= NumarPieseVechi; i++)
    {
        cout << setw(5) << " " << piesa_veche[i].ID_Piesa << setw(5) << " " << piesa_veche[i].Nume_Piesa
             << setw(NumarMaxCaractere - strlen(piesa_veche[i].Nume_Piesa) + 5) << " " << piesa_veche[i].Data_Piesa << " " << setw(5) << " ";

        for (unsigned int j = 0; j <= NumarPersonalTeatru; j++)
            if (personalTeatru[j].ID_PersonalTeatru == piesa_veche[i].ID_PersonalTeatru)
                cout << personalTeatru[j].Nume_PersonalTeatru << " " << personalTeatru[j].Prenume_PersonalTeatru << endl;
    }
    fillLinieConsola(85); // umple toate linia din consola cu  '_'
}

void afisare_sali()
{
    cout << "\n\n";
    cout << setw(5) << " "
         << "ID Sala";
    cout << setw(2) << " "
         << "Numar scaune";
    cout << setw(2) << " "
         << "Numar scaune loja";
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
    cout << setw(5) << " "
         << "ID bilet";
    cout << setw(10) << " "
         << "Tip bilet";
    cout << setw(10 + 10) << " "
         << "Pret bilet";
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

void afisare_piese_vechi()
{
    unsigned int NumarMaxCaractere = 0;

    for (unsigned int i = 1; i <= NumarPieseVechi; i++)
        if (strlen(piesa_veche[i].Nume_Piesa) > NumarMaxCaractere)
            NumarMaxCaractere = strlen(piesa_veche[i].Nume_Piesa);

    cout << "\n\n"
         << setw(5) << " "
         << "ID" << setw(5 + 1) << " "
         << "Nume" << setw(NumarMaxCaractere + 1) << " "
         << "Data" << setw(5 + 3) << " "
         << "Regizor" << endl;
    fillLinieConsola(90);

    for (unsigned int i = 1; i <= NumarPieseVechi; i++)
    {
        cout << setw(5) << " " << piesa_veche[i].ID_Piesa << setw(5) << " " << piesa_veche[i].Nume_Piesa
             << setw(NumarMaxCaractere - strlen(piesa_veche[i].Nume_Piesa) + 5) << " " << piesa_veche[i].Data_Piesa << " "
             << setw(5) << " ";

        for (unsigned int j = 0; j <= NumarPersonalTeatru; j++)
            if (personalTeatru[j].ID_PersonalTeatru == piesa_veche[i].ID_PersonalTeatru)
                cout << personalTeatru[j].Nume_PersonalTeatru << " " << personalTeatru[j].Prenume_PersonalTeatru << endl;
    }
    fillLinieConsola(90);
}

void afisare_venituri()
{
    cout << "\n\n";
    cout << setw(5) << " " << "ID Piesa" << setw(5) << " " << "Data piesei" << setw(5) << " " << "Venit" << '\n';
    fillLinieConsola(85);

    for (unsigned int i = 1; i <= contorVenit; i++)
        cout << setw(10 - 2) << " " << venitPiesa[i].ID_Piesa << setw(10 - 1) << " " << venitPiesa[i].Data_Piesa << setw(10 - 6) << " "
             << venitPiesa[i].suma << " RON" << endl;
    fillLinieConsola(85);
}

/// Sortari
void sort_piese_ID_crescator()
{
    bool vSort = true;
    do
    {
        vSort = true;
        for (unsigned int i = 1; i <= NumarPiese - 1; i++)
            if (piesaTeatru[i].ID_Piesa > piesaTeatru[i + 1].ID_Piesa)
            {
                unsigned int aux;

                aux = piesaTeatru[i].ID_Piesa;
                piesaTeatru[i].ID_Piesa = piesaTeatru[i + 1].ID_Piesa;
                piesaTeatru[i + 1].ID_Piesa = aux;

                aux = piesaTeatru[i].ID_Sala;
                piesaTeatru[i].ID_Sala = piesaTeatru[i + 1].ID_Piesa;
                piesaTeatru[i + 1].ID_Piesa = aux;

                aux = piesaTeatru[i].ID_PersonalTeatru;
                piesaTeatru[i].ID_PersonalTeatru = piesaTeatru[i + 1].ID_PersonalTeatru;
                piesaTeatru[i + 1].ID_PersonalTeatru = aux;

                char charAux[1001];

                strcpy(charAux, piesaTeatru[i].Data_Piesa);
                strcpy(piesaTeatru[i].Data_Piesa, piesaTeatru[i + 1].Data_Piesa);
                strcpy(piesaTeatru[i + 1].Data_Piesa, charAux);

                strcpy(charAux, piesaTeatru[i].Ora_Piesa);
                strcpy(piesaTeatru[i].Ora_Piesa, piesaTeatru[i + 1].Ora_Piesa);
                strcpy(piesaTeatru[i + 1].Ora_Piesa, charAux);

                strcpy(charAux, piesaTeatru[i].Nume_Piesa);
                strcpy(piesaTeatru[i].Nume_Piesa, piesaTeatru[i + 1].Nume_Piesa);
                strcpy(piesaTeatru[i + 1].Nume_Piesa, charAux);

                vSort = false;
            }
    }
    while (!vSort);
}

void sort_venituri_ID_crescator()
{
    bool vSort = true;

    do
    {
        vSort = true;
        for (unsigned int i = 1; i <= contorVenit - 1; i++)
            if (venitPiesa[i].ID_Piesa > venitPiesa[i + 1].ID_Piesa)
            {
                unsigned int aux;
                aux = venitPiesa[i].ID_Piesa;
                venitPiesa[i].ID_Piesa = venitPiesa[i + 1].ID_Piesa;
                venitPiesa[i + 1].ID_Piesa = aux;

                char dataAux[11];
                strcpy(dataAux, venitPiesa[i].Data_Piesa);
                strcpy(venitPiesa[i].Data_Piesa, venitPiesa[i + 1].Data_Piesa);
                strcpy(venitPiesa[i + 1].Data_Piesa, dataAux);

                float sumaAux;
                sumaAux = venitPiesa[i].suma;
                venitPiesa[i].suma = venitPiesa[i + 1].suma;
                venitPiesa[i + 1].suma = sumaAux;

                vSort = false;
            }
    }
    while (!vSort);
}

void sortari_piese()
{
    unsigned int Meniu_sortari;
    do
    {
        system("CLS");
        cout << endl;
        cout << setw(5 - 1) << " "
             << "1. Sortare alfabetica." << endl;
        cout << setw(5 - 1) << " "
             << "2. Sortare dupa data." << endl;
        cout << setw(5 - 1) << " "
             << "3. Sortare dupa ora." << endl;
        cout << setw(5 - 1) << " "
             << "0. Inapoi"
             << "\n\n";

        cout << setw(5 - 1) << " "
             << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
        cin >> Meniu_sortari;
        switch (Meniu_sortari)
        {
        case 1:
        {
            unsigned int ok;
            piesa s_piesaTeatru[201];
            for (unsigned int i = 1; i <= NumarPiese; i++)
                s_piesaTeatru[i] = piesaTeatru[i];
            do
            {
                ok = 1;
                for (unsigned int i = 1; i < NumarPiese; i++)
                    if (stricmp(s_piesaTeatru[i].Nume_Piesa, s_piesaTeatru[i + 1].Nume_Piesa) > 0)
                    {
                        swap(s_piesaTeatru[i], s_piesaTeatru[i + 1]);
                        ok = 0;
                    }
            }
            while (ok == 0);

            unsigned int NumarMaxCaractere = 0;
            for (unsigned int i = 1; i <= NumarPiese; i++)
                if (strlen(s_piesaTeatru[i].Nume_Piesa) > NumarMaxCaractere)
                    NumarMaxCaractere = strlen(s_piesaTeatru[i].Nume_Piesa);

            cout << "\n\n"
                 << setw(5) << " "
                 << "ID" << setw(5 + 1) << " "
                 << "Nume" << setw(NumarMaxCaractere + 1) << " "
                 << "Data" << setw(5 + 2) << " "
                 << "Ora" << setw(5 + 3) << " "
                 << "Regizor" << endl;
            fillLinieConsola(85);
            for (unsigned int i = 1; i <= NumarPiese; i++)
            {
                cout << setw(5) << " " << s_piesaTeatru[i].ID_Piesa << setw(5) << " " << s_piesaTeatru[i].Nume_Piesa
                     << setw(NumarMaxCaractere - strlen(s_piesaTeatru[i].Nume_Piesa) + 5) << " " << s_piesaTeatru[i].Data_Piesa << " "
                     << setw(5) << " " << s_piesaTeatru[i].Ora_Piesa << setw(5) << " ";

                for (unsigned int j = 0; j <= NumarPersonalTeatru; j++)
                    if (personalTeatru[j].ID_PersonalTeatru == s_piesaTeatru[i].ID_PersonalTeatru)
                        cout << personalTeatru[j].Nume_PersonalTeatru << " " << personalTeatru[j].Prenume_PersonalTeatru << endl;
            }
            fillLinieConsola(85);
        }
        _getch();
        break;

        case 2:
        {
            unsigned int ok;
            piesa s_piesaTeatru[201];
            for (unsigned int i = 1; i <= NumarPiese; i++)
                s_piesaTeatru[i] = piesaTeatru[i];
            do
            {
                ok = 1;
                for (unsigned int i = 1; i < NumarPiese; i++)
                    if ((s_piesaTeatru[i].Data_Piesa[4] > s_piesaTeatru[i + 1].Data_Piesa[4] ||
                            (s_piesaTeatru[i].Data_Piesa[4] == s_piesaTeatru[i + 1].Data_Piesa[4] && s_piesaTeatru[i].Data_Piesa[5] > s_piesaTeatru[i + 1].Data_Piesa[5]) ||
                            ((s_piesaTeatru[i].Data_Piesa[4] == s_piesaTeatru[i + 1].Data_Piesa[4] && s_piesaTeatru[i].Data_Piesa[5] == s_piesaTeatru[i + 1].Data_Piesa[5]) &&
                             s_piesaTeatru[i].Data_Piesa[0] > s_piesaTeatru[i + 1].Data_Piesa[0])) ||
                            (((s_piesaTeatru[i].Data_Piesa[4] == s_piesaTeatru[i + 1].Data_Piesa[4] && s_piesaTeatru[i].Data_Piesa[5] == s_piesaTeatru[i + 1].Data_Piesa[5]) &&
                              s_piesaTeatru[i].Data_Piesa[0] == s_piesaTeatru[i + 1].Data_Piesa[0]) &&
                             s_piesaTeatru[i].Data_Piesa[1] > s_piesaTeatru[i + 1].Data_Piesa[1]))
                    {
                        swap(s_piesaTeatru[i], s_piesaTeatru[i + 1]);
                        ok = 0;
                    }
            }
            while (ok == 0);

            unsigned int NumarMaxCaractere = 0;
            for (unsigned int i = 1; i <= NumarPiese; i++)
                if (strlen(s_piesaTeatru[i].Nume_Piesa) > NumarMaxCaractere)
                    NumarMaxCaractere = strlen(s_piesaTeatru[i].Nume_Piesa);

            cout << "\n\n"
                 << setw(5) << " "
                 << "ID" << setw(5 + 1) << " "
                 << "Nume" << setw(NumarMaxCaractere + 1) << " "
                 << "Data" << setw(5 + 2) << " "
                 << "Ora" << setw(5 + 3) << " "
                 << "Regizor" << endl;
            fillLinieConsola(85);
            for (unsigned int i = 1; i <= NumarPiese; i++)
            {
                cout << setw(5) << " " << s_piesaTeatru[i].ID_Piesa << setw(5) << " " << s_piesaTeatru[i].Nume_Piesa
                     << setw(NumarMaxCaractere - strlen(s_piesaTeatru[i].Nume_Piesa) + 5) << " " << s_piesaTeatru[i].Data_Piesa << " "
                     << setw(5) << " " << s_piesaTeatru[i].Ora_Piesa << setw(5) << " ";

                for (unsigned int j = 0; j <= NumarPersonalTeatru; j++)
                    if (personalTeatru[j].ID_PersonalTeatru == s_piesaTeatru[i].ID_PersonalTeatru)
                        cout << personalTeatru[j].Nume_PersonalTeatru << " " << personalTeatru[j].Prenume_PersonalTeatru << endl;
            }
            fillLinieConsola(85);
        }
        _getch();
        break;

        case 3:
        {
            unsigned int ok;
            piesa s_piesaTeatru[201];
            for (unsigned int i = 1; i <= NumarPiese; i++)
                s_piesaTeatru[i] = piesaTeatru[i];
            do
            {
                ok = 1;
                for (unsigned int i = 1; i < NumarPiese; i++)
                    if (strcmp(s_piesaTeatru[i].Ora_Piesa, s_piesaTeatru[i + 1].Ora_Piesa) > 0)
                    {
                        swap(s_piesaTeatru[i], s_piesaTeatru[i + 1]);
                        ok = 0;
                    }
            }
            while (ok == 0);

            unsigned int NumarMaxCaractere = 0;
            for (unsigned int i = 1; i <= NumarPiese; i++)
                if (strlen(s_piesaTeatru[i].Nume_Piesa) > NumarMaxCaractere)
                    NumarMaxCaractere = strlen(s_piesaTeatru[i].Nume_Piesa);

            cout << "\n\n"
                 << setw(5) << " "
                 << "ID" << setw(5 + 1) << " "
                 << "Nume" << setw(NumarMaxCaractere + 1) << " "
                 << "Data" << setw(5 + 2) << " "
                 << "Ora" << setw(5 + 3) << " "
                 << "Regizor" << endl;
            fillLinieConsola(85);
            for (unsigned int i = 1; i <= NumarPiese; i++)
            {
                cout << setw(5) << " " << s_piesaTeatru[i].ID_Piesa << setw(5) << " " << s_piesaTeatru[i].Nume_Piesa
                     << setw(NumarMaxCaractere - strlen(s_piesaTeatru[i].Nume_Piesa) + 5) << " " << s_piesaTeatru[i].Data_Piesa << " "
                     << setw(5) << " " << s_piesaTeatru[i].Ora_Piesa << setw(5) << " ";

                for (unsigned int j = 0; j <= NumarPersonalTeatru; j++)
                    if (personalTeatru[j].ID_PersonalTeatru == s_piesaTeatru[i].ID_PersonalTeatru)
                        cout << personalTeatru[j].Nume_PersonalTeatru << " " << personalTeatru[j].Prenume_PersonalTeatru << endl;
            }
            fillLinieConsola(85);
        }
        _getch();
        break;
        }
    }
    while (Meniu_sortari != 0);
}

void sortari_actori()
{
    unsigned int Meniu_sortari;
    do
    {
        system("CLS");
        cout << endl;

        cout << setw(5 - 1) << " "
             << "1. Sortare alfabetica dupa numele de familie." << endl;
        cout << setw(5 - 1) << " "
             << "2. Sortare alfabetica dupa prenume." << endl;
        cout << setw(5 - 1) << " "
             << "3. Sortare dupa varsta." << endl;
        cout << setw(5 - 1) << " "
             << "0. Inapoi"
             << "\n\n";

        cout << setw(5 - 1) << " "
             << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
        cin >> Meniu_sortari;
        switch (Meniu_sortari)
        {
        case 1:
        {
            unsigned int ok;
            actor c_actor[201];
            for (unsigned int i = 1; i <= NumarActori; i++)
                c_actor[i] = actorTeatru[i];
            do
            {
                ok = 1;
                for (unsigned int i = 1; i < NumarActori; i++)
                    if (stricmp(c_actor[i].Nume_Actor, c_actor[i + 1].Nume_Actor) > 0)
                    {
                        swap(c_actor[i], c_actor[i + 1]);
                        ok = 0;
                    }
            }
            while (ok == 0);

            unsigned int NumarMaxCaractereNume = 0;

            for (unsigned int i = 1; i <= NumarActori; i++)
                if (strlen(c_actor[i].Nume_Actor) > NumarMaxCaractereNume)
                    NumarMaxCaractereNume = strlen(c_actor[i].Nume_Actor);

            unsigned int NumarMaxCaracterePrenume = 0;

            for (unsigned int i = 0; i <= NumarActori; i++)
                if (strlen(c_actor[i].Prenume_Actor) > NumarMaxCaracterePrenume)
                    NumarMaxCaracterePrenume = strlen(c_actor[i].Prenume_Actor);

            unsigned int NumarMaxCaractereEmail = 0;

            for (unsigned int i = 0; i < NumarActori; i++)
                if (strlen(c_actor[i].Email_Actor) > NumarMaxCaractereEmail)
                    NumarMaxCaractereEmail = strlen(c_actor[i].Email_Actor);

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

            fillLinieConsola(115);

            for (unsigned int i = 1; i <= NumarActori; i++)
                cout << setw(5) << " " << c_actor[i].ID_Actor << setw(10 - 1) << " " << c_actor[i].ID_Piesa << setw(10 - 1) << " " << c_actor[i].Nume_Actor
                     << setw(NumarMaxCaractereNume - strlen(c_actor[i].Nume_Actor) + 10) << " " << c_actor[i].Prenume_Actor
                     << setw(NumarMaxCaracterePrenume - strlen(c_actor[i].Prenume_Actor) + 10) << " " << c_actor[i].Varsta_Actor << " ani"
                     << setw(10) << " " << c_actor[i].Email_Actor << setw(NumarMaxCaractereEmail - strlen(c_actor[i].Email_Actor) + 10) << "\n";

            fillLinieConsola(115);
        }
        _getch();
        break;

        case 2:
        {
            unsigned int ok;
            actor c_actor[201];
            for (unsigned int i = 1; i <= NumarActori; i++)
                c_actor[i] = actorTeatru[i];
            do
            {
                ok = 1;
                for (unsigned int i = 1; i < NumarActori; i++)
                    if (stricmp(c_actor[i].Prenume_Actor, c_actor[i + 1].Prenume_Actor) > 0)
                    {
                        swap(c_actor[i], c_actor[i + 1]);
                        ok = 0;
                    }
            }
            while (ok == 0);

            unsigned int NumarMaxCaractereNume = 0;

            for (unsigned int i = 1; i <= NumarActori; i++)
                if (strlen(c_actor[i].Nume_Actor) > NumarMaxCaractereNume)
                    NumarMaxCaractereNume = strlen(c_actor[i].Nume_Actor);

            unsigned int NumarMaxCaracterePrenume = 0;

            for (unsigned int i = 0; i <= NumarActori; i++)
                if (strlen(c_actor[i].Prenume_Actor) > NumarMaxCaracterePrenume)
                    NumarMaxCaracterePrenume = strlen(c_actor[i].Prenume_Actor);

            unsigned int NumarMaxCaractereEmail = 0;

            for (unsigned int i = 0; i < NumarActori; i++)
                if (strlen(c_actor[i].Email_Actor) > NumarMaxCaractereEmail)
                    NumarMaxCaractereEmail = strlen(c_actor[i].Email_Actor);

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

            fillLinieConsola(115);

            for (unsigned int i = 1; i <= NumarActori; i++)
                cout << setw(5) << " " << c_actor[i].ID_Actor << setw(10 - 1) << " " << c_actor[i].ID_Piesa << setw(10 - 1) << " " << c_actor[i].Nume_Actor
                     << setw(NumarMaxCaractereNume - strlen(c_actor[i].Nume_Actor) + 10) << " " << c_actor[i].Prenume_Actor
                     << setw(NumarMaxCaracterePrenume - strlen(c_actor[i].Prenume_Actor) + 10) << " " << c_actor[i].Varsta_Actor << " ani"
                     << setw(10) << " " << c_actor[i].Email_Actor << setw(NumarMaxCaractereEmail - strlen(c_actor[i].Email_Actor) + 10) << "\n";

            fillLinieConsola(115);
        }
        _getch();
        break;

        case 3:
        {
            unsigned int ok;
            actor c_actor[201];
            for (unsigned int i = 1; i <= NumarActori; i++)
                c_actor[i] = actorTeatru[i];
            do
            {
                ok = 1;
                for (unsigned int i = 1; i < NumarActori; i++)
                    if (c_actor[i].Varsta_Actor > c_actor[i + 1].Varsta_Actor)
                    {
                        swap(c_actor[i], c_actor[i + 1]);
                        ok = 0;
                    }
            }
            while (ok == 0);

            unsigned int NumarMaxCaractereNume = 0;

            for (unsigned int i = 1; i <= NumarActori; i++)
                if (strlen(c_actor[i].Nume_Actor) > NumarMaxCaractereNume)
                    NumarMaxCaractereNume = strlen(c_actor[i].Nume_Actor);

            unsigned int NumarMaxCaracterePrenume = 0;

            for (unsigned int i = 0; i <= NumarActori; i++)
                if (strlen(c_actor[i].Prenume_Actor) > NumarMaxCaracterePrenume)
                    NumarMaxCaracterePrenume = strlen(c_actor[i].Prenume_Actor);

            unsigned int NumarMaxCaractereEmail = 0;

            for (unsigned int i = 0; i < NumarActori; i++)
                if (strlen(c_actor[i].Email_Actor) > NumarMaxCaractereEmail)
                    NumarMaxCaractereEmail = strlen(c_actor[i].Email_Actor);

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

            fillLinieConsola(115);

            for (unsigned int i = 1; i <= NumarActori; i++)
                cout << setw(5) << " " << c_actor[i].ID_Actor << setw(10 - 1) << " " << c_actor[i].ID_Piesa << setw(10 - 1) << " " << c_actor[i].Nume_Actor
                     << setw(NumarMaxCaractereNume - strlen(c_actor[i].Nume_Actor) + 10) << " " << c_actor[i].Prenume_Actor
                     << setw(NumarMaxCaracterePrenume - strlen(c_actor[i].Prenume_Actor) + 10) << " " << c_actor[i].Varsta_Actor << " ani"
                     << setw(10) << " " << c_actor[i].Email_Actor << setw(NumarMaxCaractereEmail - strlen(c_actor[i].Email_Actor) + 10) << "\n";

            fillLinieConsola(115);
        }
        _getch();
        break;
        }
    }
    while (Meniu_sortari != 0);
}

void sortari_personal()
{
    unsigned int Meniu_sortari;
    do
    {
        system("CLS");
        cout << endl;

        cout << setw(5 - 1) << " "
             << "1. Sortare alfabetica dupa numele de familie." << endl;
        cout << setw(5 - 1) << " "
             << "2. Sortare alfabetica dupa prenume." << endl;
        cout << setw(5 - 1) << " "
             << "3. Sortare dupa varsta." << endl;
        cout << setw(5 - 1) << " "
             << "4. Sortare dupa ocupatie." << endl;
        cout << setw(5 - 1) << " "
             << "0. Inapoi"
             << "\n\n";

        cout << setw(5 - 1) << " "
             << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
        cin >> Meniu_sortari;
        switch (Meniu_sortari)
        {
        case 1:
        {
            unsigned int ok;
            personal c_personal[201];
            for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
                c_personal[i] = personalTeatru[i];
            do
            {
                ok = 1;
                for (unsigned int i = 1; i < NumarPersonalTeatru; i++)
                    if (stricmp(c_personal[i].Nume_PersonalTeatru, c_personal[i + 1].Nume_PersonalTeatru) > 0)
                    {
                        swap(c_personal[i], c_personal[i + 1]);
                        ok = 0;
                    }
            }
            while (ok == 0);

            unsigned int nrMaxCaractereFunctie = 0;
            for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
                if (strlen(c_personal[i].Functie_PersonalTeatru) > nrMaxCaractereFunctie)
                    nrMaxCaractereFunctie = strlen(c_personal[i].Functie_PersonalTeatru);

            unsigned int nrMaxCaractereNumePersonal = 0;
            for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
                if (strlen(c_personal[i].Nume_PersonalTeatru) > nrMaxCaractereNumePersonal)
                    nrMaxCaractereNumePersonal = strlen(c_personal[i].Nume_PersonalTeatru);

            unsigned int nrMaxCaracterePreumePersonal = 0;
            for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
                if (strlen(c_personal[i].Prenume_PersonalTeatru) > nrMaxCaracterePreumePersonal)
                    nrMaxCaracterePreumePersonal = strlen(c_personal[i].Prenume_PersonalTeatru);

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
                cout << setw(5 + 2) << " " << c_personal[i].ID_PersonalTeatru << setw(10 - 1) << " ";

                char vFunctiePersonalAux[1001];
                strcpy(vFunctiePersonalAux, c_personal[i].Functie_PersonalTeatru);
                for (unsigned int j = 0; j < strlen(vFunctiePersonalAux); j++)
                    if (vFunctiePersonalAux[j] == '_')
                        vFunctiePersonalAux[j] = ' ';

                cout << vFunctiePersonalAux << setw(nrMaxCaractereFunctie + 5 - strlen(c_personal[i].Functie_PersonalTeatru)) << " "
                     << c_personal[i].Nume_PersonalTeatru << " " << setw(nrMaxCaractereNumePersonal + 5 - strlen(c_personal[i].Nume_PersonalTeatru)) << " "
                     << c_personal[i].Prenume_PersonalTeatru << setw(nrMaxCaracterePreumePersonal + 5 - strlen(c_personal[i].Prenume_PersonalTeatru)) << " "
                     << c_personal[i].CNP_PersonalTeatru << setw(5) << " "
                     << c_personal[i].Varsta_PersonalTeatru << endl;
            }

            fillLinieConsola(110);
        }
        _getch();
        break;

        case 2:
        {
            unsigned int ok;
            personal c_personal[201];
            for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
                c_personal[i] = personalTeatru[i];
            do
            {
                ok = 1;
                for (unsigned int i = 1; i < NumarPersonalTeatru; i++)
                    if (stricmp(c_personal[i].Prenume_PersonalTeatru, c_personal[i + 1].Prenume_PersonalTeatru) > 0)
                    {
                        swap(c_personal[i], c_personal[i + 1]);
                        ok = 0;
                    }
            }
            while (ok == 0);

            unsigned int nrMaxCaractereFunctie = 0;
            for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
                if (strlen(c_personal[i].Functie_PersonalTeatru) > nrMaxCaractereFunctie)
                    nrMaxCaractereFunctie = strlen(c_personal[i].Functie_PersonalTeatru);

            unsigned int nrMaxCaractereNumePersonal = 0;
            for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
                if (strlen(c_personal[i].Nume_PersonalTeatru) > nrMaxCaractereNumePersonal)
                    nrMaxCaractereNumePersonal = strlen(c_personal[i].Nume_PersonalTeatru);

            unsigned int nrMaxCaracterePreumePersonal = 0;
            for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
                if (strlen(c_personal[i].Prenume_PersonalTeatru) > nrMaxCaracterePreumePersonal)
                    nrMaxCaracterePreumePersonal = strlen(c_personal[i].Prenume_PersonalTeatru);

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
                cout << setw(5 + 2) << " " << c_personal[i].ID_PersonalTeatru << setw(10 - 1) << " ";

                char vFunctiePersonalAux[1001];
                strcpy(vFunctiePersonalAux, c_personal[i].Functie_PersonalTeatru);
                for (unsigned int j = 0; j < strlen(vFunctiePersonalAux); j++)
                    if (vFunctiePersonalAux[j] == '_')
                        vFunctiePersonalAux[j] = ' ';

                cout << vFunctiePersonalAux << setw(nrMaxCaractereFunctie + 5 - strlen(c_personal[i].Functie_PersonalTeatru)) << " "
                     << c_personal[i].Nume_PersonalTeatru << " " << setw(nrMaxCaractereNumePersonal + 5 - strlen(c_personal[i].Nume_PersonalTeatru)) << " "
                     << c_personal[i].Prenume_PersonalTeatru << setw(nrMaxCaracterePreumePersonal + 5 - strlen(c_personal[i].Prenume_PersonalTeatru)) << " "
                     << c_personal[i].CNP_PersonalTeatru << setw(5) << " "
                     << c_personal[i].Varsta_PersonalTeatru << endl;
            }

            fillLinieConsola(110);
        }
        _getch();
        break;

        case 3:
        {
            unsigned int ok;
            personal c_personal[201];
            for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
                c_personal[i] = personalTeatru[i];
            do
            {
                ok = 1;
                for (unsigned int i = 1; i < NumarPersonalTeatru; i++)
                    if (c_personal[i].Varsta_PersonalTeatru > c_personal[i + 1].Varsta_PersonalTeatru)
                    {
                        swap(c_personal[i], c_personal[i + 1]);
                        ok = 0;
                    }
            }
            while (ok == 0);

            unsigned int nrMaxCaractereFunctie = 0;
            for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
                if (strlen(c_personal[i].Functie_PersonalTeatru) > nrMaxCaractereFunctie)
                    nrMaxCaractereFunctie = strlen(c_personal[i].Functie_PersonalTeatru);

            unsigned int nrMaxCaractereNumePersonal = 0;
            for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
                if (strlen(c_personal[i].Nume_PersonalTeatru) > nrMaxCaractereNumePersonal)
                    nrMaxCaractereNumePersonal = strlen(c_personal[i].Nume_PersonalTeatru);

            unsigned int nrMaxCaracterePreumePersonal = 0;
            for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
                if (strlen(c_personal[i].Prenume_PersonalTeatru) > nrMaxCaracterePreumePersonal)
                    nrMaxCaracterePreumePersonal = strlen(c_personal[i].Prenume_PersonalTeatru);

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
                cout << setw(5 + 2) << " " << c_personal[i].ID_PersonalTeatru << setw(10 - 1) << " ";

                char vFunctiePersonalAux[1001];
                strcpy(vFunctiePersonalAux, c_personal[i].Functie_PersonalTeatru);
                for (unsigned int j = 0; j < strlen(vFunctiePersonalAux); j++)
                    if (vFunctiePersonalAux[j] == '_')
                        vFunctiePersonalAux[j] = ' ';

                cout << vFunctiePersonalAux << setw(nrMaxCaractereFunctie + 5 - strlen(c_personal[i].Functie_PersonalTeatru)) << " "
                     << c_personal[i].Nume_PersonalTeatru << " " << setw(nrMaxCaractereNumePersonal + 5 - strlen(c_personal[i].Nume_PersonalTeatru)) << " "
                     << c_personal[i].Prenume_PersonalTeatru << setw(nrMaxCaracterePreumePersonal + 5 - strlen(c_personal[i].Prenume_PersonalTeatru)) << " "
                     << c_personal[i].CNP_PersonalTeatru << setw(5) << " "
                     << c_personal[i].Varsta_PersonalTeatru << endl;
            }

            fillLinieConsola(110);
        }
        _getch();
        break;

        case 4:
        {
            unsigned int ok;
            personal c_personal[201];
            for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
                c_personal[i] = personalTeatru[i];
            do
            {
                ok = 1;
                for (unsigned int i = 1; i < NumarPersonalTeatru; i++)
                    if (stricmp(c_personal[i].Functie_PersonalTeatru, c_personal[i + 1].Functie_PersonalTeatru) > 0)
                    {
                        swap(c_personal[i], c_personal[i + 1]);
                        ok = 0;
                    }
            }
            while (ok == 0);

            unsigned int nrMaxCaractereFunctie = 0;
            for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
                if (strlen(c_personal[i].Functie_PersonalTeatru) > nrMaxCaractereFunctie)
                    nrMaxCaractereFunctie = strlen(c_personal[i].Functie_PersonalTeatru);

            unsigned int nrMaxCaractereNumePersonal = 0;
            for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
                if (strlen(c_personal[i].Nume_PersonalTeatru) > nrMaxCaractereNumePersonal)
                    nrMaxCaractereNumePersonal = strlen(c_personal[i].Nume_PersonalTeatru);

            unsigned int nrMaxCaracterePreumePersonal = 0;
            for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
                if (strlen(c_personal[i].Prenume_PersonalTeatru) > nrMaxCaracterePreumePersonal)
                    nrMaxCaracterePreumePersonal = strlen(c_personal[i].Prenume_PersonalTeatru);

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
                cout << setw(5 + 2) << " " << c_personal[i].ID_PersonalTeatru << setw(10 - 1) << " ";

                char vFunctiePersonalAux[1001];
                strcpy(vFunctiePersonalAux, c_personal[i].Functie_PersonalTeatru);
                for (unsigned int j = 0; j < strlen(vFunctiePersonalAux); j++)
                    if (vFunctiePersonalAux[j] == '_')
                        vFunctiePersonalAux[j] = ' ';

                cout << vFunctiePersonalAux << setw(nrMaxCaractereFunctie + 5 - strlen(c_personal[i].Functie_PersonalTeatru)) << " "
                     << c_personal[i].Nume_PersonalTeatru << " " << setw(nrMaxCaractereNumePersonal + 5 - strlen(c_personal[i].Nume_PersonalTeatru)) << " "
                     << c_personal[i].Prenume_PersonalTeatru << setw(nrMaxCaracterePreumePersonal + 5 - strlen(c_personal[i].Prenume_PersonalTeatru)) << " "
                     << c_personal[i].CNP_PersonalTeatru << setw(5) << " "
                     << c_personal[i].Varsta_PersonalTeatru << endl;
            }

            fillLinieConsola(110);
        }
        _getch();
        break;
        }
    }
    while (Meniu_sortari != 0);
}

void sortari_istoricPiese_alfabeti_A_Z()
{
    system("CLS");

    unsigned int ok;
    piesa_v c_piesa_veche[401];
    for (unsigned int i = 1; i <= NumarPieseVechi; i++)
        c_piesa_veche[i] = piesa_veche[i];
    do
    {
        ok = 1;
        for (unsigned int i = 1; i < NumarPieseVechi; i++)
            if (stricmp(c_piesa_veche[i].Nume_Piesa, c_piesa_veche[i + 1].Nume_Piesa) > 0)
            {
                swap(c_piesa_veche[i], c_piesa_veche[i + 1]);
                ok = 0;
            }
    }
    while (ok == 0);

    unsigned int NumarMaxCaractere = 0;

    for (unsigned int i = 1; i <= NumarPieseVechi; i++)
        if (strlen(c_piesa_veche[i].Nume_Piesa) > NumarMaxCaractere)
            NumarMaxCaractere = strlen(c_piesa_veche[i].Nume_Piesa);

    cout << "\n\n"
         << setw(5) << " "
         << "ID" << setw(5 + 1) << " "
         << "Nume" << setw(NumarMaxCaractere + 1) << " "
         << "Data" << setw(5 + 3) << " "
         << "Regizor" << endl;
    fillLinieConsola(90);

    for (unsigned int i = 1; i <= NumarPieseVechi; i++)
    {
        cout << setw(5) << " " << c_piesa_veche[i].ID_Piesa << setw(5) << " " << c_piesa_veche[i].Nume_Piesa
             << setw(NumarMaxCaractere - strlen(c_piesa_veche[i].Nume_Piesa) + 5) << " " << c_piesa_veche[i].Data_Piesa << " "
             << setw(5) << " ";

        for (unsigned int j = 0; j <= NumarPersonalTeatru; j++)
            if (personalTeatru[j].ID_PersonalTeatru == piesa_veche[i].ID_PersonalTeatru)
                cout << personalTeatru[j].Nume_PersonalTeatru << " " << personalTeatru[j].Prenume_PersonalTeatru << endl;
    }
    fillLinieConsola(90);

    cout << '\n'
         << setw(4) << " "
         << "Apasati enter pentru a va intoarce la meniul precedent...";
}

void sortari_istoricPiese_alfabeti_Z_A()
{
    system("CLS");

    unsigned int ok;
    piesa_v c_piesa_veche[401];
    for (unsigned int i = 1; i <= NumarPieseVechi; i++)
        c_piesa_veche[i] = piesa_veche[i];
    do
    {
        ok = 1;
        for (unsigned int i = 1; i < NumarPieseVechi; i++)
            if (stricmp(c_piesa_veche[i].Nume_Piesa, c_piesa_veche[i + 1].Nume_Piesa) < 0)
            {
                swap(c_piesa_veche[i], c_piesa_veche[i + 1]);
                ok = 0;
            }
    }
    while (ok == 0);

    unsigned int NumarMaxCaractere = 0;

    for (unsigned int i = 1; i <= NumarPieseVechi; i++)
        if (strlen(c_piesa_veche[i].Nume_Piesa) > NumarMaxCaractere)
            NumarMaxCaractere = strlen(c_piesa_veche[i].Nume_Piesa);

    cout << "\n\n"
         << setw(5) << " "
         << "ID" << setw(5 + 1) << " "
         << "Nume" << setw(NumarMaxCaractere + 1) << " "
         << "Data" << setw(5 + 3) << " "
         << "Regizor" << endl;
    fillLinieConsola(90);

    for (unsigned int i = 1; i <= NumarPieseVechi; i++)
    {
        cout << setw(5) << " " << c_piesa_veche[i].ID_Piesa << setw(5) << " " << c_piesa_veche[i].Nume_Piesa
             << setw(NumarMaxCaractere - strlen(c_piesa_veche[i].Nume_Piesa) + 5) << " " << c_piesa_veche[i].Data_Piesa << " "
             << setw(5) << " ";

        for (unsigned int j = 0; j <= NumarPersonalTeatru; j++)
            if (personalTeatru[j].ID_PersonalTeatru == piesa_veche[i].ID_PersonalTeatru)
                cout << personalTeatru[j].Nume_PersonalTeatru << " " << personalTeatru[j].Prenume_PersonalTeatru << endl;
    }
    fillLinieConsola(90);

    cout << '\n'
         << setw(4) << " "
         << "Apasati enter pentru a va intoarce la meniul precedent...";
}

void sortari_istoricPiese_data()
{
    system("CLS");

    unsigned int ok;
    piesa_v c_piesa_veche[401];
    for (unsigned int i = 1; i <= NumarPieseVechi; i++)
        c_piesa_veche[i] = piesa_veche[i];
    do
    {
        ok = 1;
        for (unsigned int i = 1; i < NumarPieseVechi; i++)
            if ((c_piesa_veche[i].Data_Piesa[4] > c_piesa_veche[i + 1].Data_Piesa[4] ||
                    (c_piesa_veche[i].Data_Piesa[4] == c_piesa_veche[i + 1].Data_Piesa[4] && c_piesa_veche[i].Data_Piesa[5] > c_piesa_veche[i + 1].Data_Piesa[5]) ||
                    ((c_piesa_veche[i].Data_Piesa[4] == c_piesa_veche[i + 1].Data_Piesa[4] && c_piesa_veche[i].Data_Piesa[5] == c_piesa_veche[i + 1].Data_Piesa[5]) &&
                     c_piesa_veche[i].Data_Piesa[0] > c_piesa_veche[i + 1].Data_Piesa[0])) ||
                    (((c_piesa_veche[i].Data_Piesa[4] == c_piesa_veche[i + 1].Data_Piesa[4] && c_piesa_veche[i].Data_Piesa[5] == c_piesa_veche[i + 1].Data_Piesa[5]) &&
                      c_piesa_veche[i].Data_Piesa[0] == c_piesa_veche[i + 1].Data_Piesa[0]) &&
                     c_piesa_veche[i].Data_Piesa[1] > c_piesa_veche[i + 1].Data_Piesa[1]))
            {
                swap(c_piesa_veche[i], c_piesa_veche[i + 1]);
                ok = 0;
            }
    }
    while (ok == 0);

    unsigned int NumarMaxCaractere = 0;

    for (unsigned int i = 1; i <= NumarPieseVechi; i++)
        if (strlen(c_piesa_veche[i].Nume_Piesa) > NumarMaxCaractere)
            NumarMaxCaractere = strlen(c_piesa_veche[i].Nume_Piesa);

    cout << "\n\n"
         << setw(5) << " "
         << "ID" << setw(5 + 1) << " "
         << "Nume" << setw(NumarMaxCaractere + 1) << " "
         << "Data" << setw(5 + 3) << " "
         << "Regizor" << endl;
    fillLinieConsola(75);

    for (unsigned int i = 1; i <= NumarPieseVechi; i++)
    {
        cout << setw(5) << " " << c_piesa_veche[i].ID_Piesa << setw(5) << " " << c_piesa_veche[i].Nume_Piesa
             << setw(NumarMaxCaractere - strlen(c_piesa_veche[i].Nume_Piesa) + 5) << " " << c_piesa_veche[i].Data_Piesa << " "
             << setw(5) << " ";

        for (unsigned int j = 0; j <= NumarPersonalTeatru; j++)
            if (personalTeatru[j].ID_PersonalTeatru == piesa_veche[i].ID_PersonalTeatru)
                cout << personalTeatru[j].Nume_PersonalTeatru << " " << personalTeatru[j].Prenume_PersonalTeatru << endl;
    }
    fillLinieConsola(75);

    cout << '\n'
         << setw(4) << " "
         << "Apasati enter pentru a va intoarce la meniul precedent...";
}

/// Componente main
void cautare_piesa_nume()
{
    system("CLS");
    afisare_piese();

    char vNume_Piesa[101];

    cout << '\n';
    cout << setw(5 - 1) << " "
         << "APASA TASTA '0' PENTRU A ANULA";

    cout << "\n\n"
         << setw(5 - 1) << " "
         << "Tasteaza numele piesei: ";
    cin.get();
    cin.get(vNume_Piesa, 101);

    if (strcmp(vNume_Piesa, "0") == 0)
        return;
    else
    {
        for (unsigned int i = 1; i <= NumarPiese; i++)
            if (stricmp(piesaTeatru[i].Nume_Piesa, vNume_Piesa) == 0)
            {
                cout << '\n';

                cout << setw(5 - 1) << " "
                     << "ID: " << piesaTeatru[i].ID_Piesa << endl;
                cout << setw(5 - 1) << " "
                     << "Nume: " << piesaTeatru[i].Nume_Piesa << endl;
                cout << setw(5 - 1) << " "
                     << "Sala: " << piesaTeatru[i].ID_Sala << endl;
                cout << setw(5 - 1) << " "
                     << "Data: " << piesaTeatru[i].Data_Piesa << endl;
                cout << setw(5 - 1) << " "
                     << "Ora: " << piesaTeatru[i].Ora_Piesa << '\n';
            }
        cout << '\n';
        cout << setw(5 - 1) << " "
             << "Apasa enter pentru a te intoarce la meniul precedent...";
        _getch();
        cautare_piesa_nume();
    }
}

void cautare_piesa_ID()
{
    system("CLS");
    afisare_piese();

    unsigned int vID;
    bool exit = false, valid = false;

    cout << '\n';
    cout << setw(5 - 1) << " "
         << "APASA TASTA '0' PENTRU A ANULA";

    cout << "\n\n"
         << setw(5 - 1) << " "
         << "Tasteaza ID-ul piesei: ";

    while (!valid)
    {
        cin >> vID;
        if (cin.fail() || vID > copie_ID_Piesa_Max )
        {
            cin.clear();
            cin.ignore();
            cout << '\n';
            cerr << setw(5) << " "
                 << "Valoarea introdusa este invalida!" << endl;
            Sleep(1500);
            cautare_piesa_ID();
        }
        else
            valid = true;
    }

    if (vID == 0)
        return;
    else
    {
        for (unsigned int i = 1; i <= NumarPiese && !exit; i++)
            if (piesaTeatru[i].ID_Piesa == vID)
            {
                cout << '\n';

                cout << setw(5 - 1) << " "
                     << "ID: " << piesaTeatru[i].ID_Piesa << endl;
                cout << setw(5 - 1) << " "
                     << "Nume: " << piesaTeatru[i].Nume_Piesa << endl;
                cout << setw(5 - 1) << " "
                     << "Sala: " << piesaTeatru[i].ID_Sala << endl;
                cout << setw(5 - 1) << " "
                     << "Data: " << piesaTeatru[i].Data_Piesa << endl;
                cout << setw(5 - 1) << " "
                     << "Ora: " << piesaTeatru[i].Ora_Piesa << '\n';

                exit = true;
            }
        cout << '\n';
        cout << setw(5 - 1) << " "
             << "Apasa enter pentru a te intoarce la meniul precedent...";
        _getch();
        cautare_piesa_ID();
    }
}

void cautare_piesa_ora()
{
    system("CLS");
    afisare_piese();

    char vOraPiesa[6];
    bool valid = false, exist = false;

    cout << '\n';
    cout << setw(5 - 1) << " "
         << "APASA TASTA '0' PENTRU A ANULA";

    cout << "\n\n"
         << setw(5 - 1) << " "
         << "Tasteaza ora (FORMAT: 00:00): ";

    while (!valid)
    {
        cin.get();
        cin.get(vOraPiesa, 6);

        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << '\n';
            cerr << setw(5 - 1) << " "
                 << "Formatul orei introduse este invalid!" << endl;
            Sleep(1500);
            cautare_piesa_ora();
        }
        else
            valid = true;
    }

    if (strcmp(vOraPiesa, "0") == 0)
        return;
    else
    {
        for (unsigned int i = 1; i <= NumarPiese; i++)
            if (strcmp(piesaTeatru[i].Ora_Piesa, vOraPiesa) == 0)
            {
                cout << '\n';

                cout << setw(5 - 1) << " "
                     << "ID: " << piesaTeatru[i].ID_Piesa << endl;
                cout << setw(5 - 1) << " "
                     << "Nume: " << piesaTeatru[i].Nume_Piesa << endl;
                cout << setw(5 - 1) << " "
                     << "Sala: " << piesaTeatru[i].ID_Sala << endl;
                cout << setw(5 - 1) << " "
                     << "Data: " << piesaTeatru[i].Data_Piesa << endl;
                cout << setw(5 - 1) << " "
                     << "Ora: " << piesaTeatru[i].Ora_Piesa << '\n';

                exist = true;
            }

        if (!exist)
        {
            cout << '\n'
                 << setw(5 - 1) << " "
                 << "Nu exista piese la aceasta ora!";
            Sleep(1500);
            cautare_piesa_ora();
        }

        cout << '\n';
        cout << setw(5 - 1) << " "
             << "Apasa enter pentru a te intoarce la meniul precedent...";

        _getch();
        cautare_piesa_ora();
    }

}

void cautare_piesa_data()
{
    system("CLS");
    afisare_piese();

    char vDataPiesa[11];
    bool valid = false, exist = false;

    cout << '\n';
    cout << setw(5 - 1) << " "
         << "APASA TASTA '0' PENTRU A ANULA";

    cout << "\n\n"
         << setw(5 - 1) << " "
         << "Tasteaza data (FORMAT: DD.MM.YYYY): ";

    while (!valid)
    {
        cin.get();
        cin.get(vDataPiesa, 11);

        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << '\n';
            cerr << setw(5 - 1) << " "
                 << "Formatul datei introduse este invalid!" << endl;
            Sleep(1500);
            cautare_piesa_data();
        }
        else
            valid = true;
    }

    if (strcmp(vDataPiesa, "0") == 0)
        return;
    else
    {
        for (unsigned int i = 1; i <= NumarPiese; i++)
            if (strcmp(piesaTeatru[i].Data_Piesa, vDataPiesa) == 0)
            {
                cout << '\n';

                cout << setw(5 - 1) << " "
                     << "ID: " << piesaTeatru[i].ID_Piesa << endl;
                cout << setw(5 - 1) << " "
                     << "Nume: " << piesaTeatru[i].Nume_Piesa << endl;
                cout << setw(5 - 1) << " "
                     << "Sala: " << piesaTeatru[i].ID_Sala << endl;
                cout << setw(5 - 1) << " "
                     << "Data: " << piesaTeatru[i].Data_Piesa << endl;
                cout << setw(5 - 1) << " "
                     << "Ora: " << piesaTeatru[i].Ora_Piesa << '\n';

                exist = true;
            }

        if (!exist)
        {
            cout << '\n'
                 << setw(5 - 1) << " "
                 << "Nu exista piese in aceasta data!";
            Sleep(1500);
            cautare_piesa_data();
        }

        cout << '\n';
        cout << setw(5 - 1) << " "
             << "Apasa enter pentru a te intoarce la meniul precedent...";
        _getch();
        cautare_piesa_data();
    }

}

void cautare_piesa_regizor()
{
    system("CLS");
    afisare_piese();

    char vNumeRegizor[101], vPrenumeRegizor[101];
    bool exist = false;

    cout << '\n';
    cout << setw(5 - 1) << " "
         << "APASA TASTA '0' PENTRU A ANULA";

    cout << "\n\n"
         << setw(5 - 1) << " "
         << "Tasteaza numele regizorului: ";

    cin.get();
    cin.get(vNumeRegizor, 101);

    if (strcmp(vNumeRegizor, "0") == 0)
        return;
    else
    {
        cout << setw(5 - 1) << " "
             << "Tasteaza prenumele regizorului: ";

        cin.get();
        cin.get(vPrenumeRegizor, 101);

        if (strcmp(vPrenumeRegizor, "0") == 0)
            return;
        else
        {
            unsigned int copieID = 0;
            for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
                if (stricmp(vNumeRegizor, personalTeatru[i].Nume_PersonalTeatru) == 0 && stricmp(vPrenumeRegizor, personalTeatru[i].Prenume_PersonalTeatru) == 0)
                    copieID = personalTeatru[i].ID_PersonalTeatru;

            for (unsigned int j = 1; j <= NumarPiese; j++)
                if (copieID == piesaTeatru[j].ID_PersonalTeatru)
                {
                    cout << '\n';

                    cout << setw(5 - 1) << " "
                         << "ID: " << piesaTeatru[j].ID_Piesa << endl;
                    cout << setw(5 - 1) << " "
                         << "Nume: " << piesaTeatru[j].Nume_Piesa << endl;
                    cout << setw(5 - 1) << " "
                         << "Sala: " << piesaTeatru[j].ID_Sala << endl;
                    cout << setw(5 - 1) << " "
                         << "Data: " << piesaTeatru[j].Data_Piesa << endl;
                    cout << setw(5 - 1) << " "
                         << "Ora: " << piesaTeatru[j].Ora_Piesa << '\n';

                    exist = true;
                }

            if (!exist)
            {
                cout << '\n'
                     << setw(5 - 1) << " "
                     << "Nu exista piese puse in scena de regizorul respectiv!";
                Sleep(1500);
                cautare_piesa_regizor();
            }

            cout << '\n';
            cout << setw(5 - 1) << " "
                 << "Apasa enter pentru a te intoarce la meniul precedent...";

            _getch();
            cautare_piesa_regizor();
        }
    }

}

void cautare_piesa_actor()
{
    system("CLS");
    afisare_piese();

    char vNumeActor[101], vPrenumeActor[101];

    cout << '\n';
    cout << setw(5 - 1) << " "
         << "APASA TASTA '0' PENTRU A ANULA";

    cout << "\n\n"
         << setw(5 - 1) << " "
         << "Tasteaza numele actorului: ";

    cin.get();
    cin.get(vNumeActor, 101);

    if (strcmp(vNumeActor, "0") == 0)
        return;
    else
    {
        cout << setw(5 - 1) << " "
             << "Tasteaza prenumele actorului: ";

        cin.get();
        cin.get(vPrenumeActor, 101);

        if (strcmp(vPrenumeActor, "0") == 0)
            return;
        else
        {
            bool exist = false;

            for (unsigned int i = 1; i <= NumarActori; i++)
                if (strcmp(actorTeatru[i].Nume_Actor, vNumeActor) == 0 && strcmp(actorTeatru[i].Prenume_Actor, vPrenumeActor) == 0)
                    for (unsigned int j = 1; j <= NumarPiese; j++)
                        if (piesaTeatru[j].ID_Piesa == actorTeatru[i].ID_Piesa)
                        {
                            cout << '\n';

                            cout << setw(5 - 1) << " "
                                 << "ID: " << piesaTeatru[j].ID_Piesa << endl;
                            cout << setw(5 - 1) << " "
                                 << "Nume: " << piesaTeatru[j].Nume_Piesa << endl;
                            cout << setw(5 - 1) << " "
                                 << "Sala: " << piesaTeatru[j].ID_Sala << endl;
                            cout << setw(5 - 1) << " "
                                 << "Data: " << piesaTeatru[j].Data_Piesa << endl;
                            cout << setw(5 - 1) << " "
                                 << "Ora: " << piesaTeatru[j].Ora_Piesa << '\n';

                            exist = true;
                        }

            if (!exist)
            {
                cout << '\n'
                     << setw(5 - 1) << " "
                     << "Nu exista piese jucate de actorul respectiv!";
                Sleep(1500);
                cautare_piesa_actor();
            }

            cout << '\n';
            cout << setw(5 - 1) << " "
                 << "Apasa enter pentru a te intoarce la meniul precedent...";
        }
    }
    _getch();
}

void cautare_Piesa_ID_Actori()
{
    system("CLS");

    afisare_piese();

    unsigned int vID_Piesa;
    bool exit = false, valid = false;

    cout << setw(5 - 1) << " "
         << "APASA TASTA '0' PENTRU A TE INTOARCE LA MENIUL PRECEDENT"
         << "\n\n";
    cout << setw(5 - 1) << " "
         << "Introdu ID-ul corespunzator piesei cautate: ";

    while (!valid)
    {
        cin >> vID_Piesa;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << '\n';
            cerr << setw(5 - 1) << " "
                 << "Valoarea introdusa in campul ID PIESA este invalida!" << endl;
            Sleep(1500);
            cautare_Piesa_ID_Actori();
        }
        else
            valid = true;
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
        cout << setw(5 - 1) << " "
             << "Apasati enter pentru a va intoarce la meniul precedent...";

        _getch();
        cautare_Piesa_ID_Actori();
    }
}

void Adaugare_Sali()
{
    system("CLS");
    copie_ID_Sala_Max++;
    NumarSali++;

    cout << "\n\n";
    cout << setw(4) << " "
         << "Introduceti datele noii sali:"
         << "\n\n";
    cout << setw(6) << " "
         << "ID-ul salii: " << copie_ID_Sala_Max << endl;
    salaTeatru[NumarSali].ID_Sala = copie_ID_Sala_Max;
    cout << setw(6) << " "
         << "Numar scaune: ";
    cin >> salaTeatru[NumarSali].Nr_Scaune;
    cout << setw(6) << " "
         << "Numar scaune loja: ";
    cin >> salaTeatru[NumarSali].Nr_Scaune_Loja;

    cout << '\n'
         << setw(4) << " "
         << "Apasati enter pentru a va intoarce la meniul precedent...";

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
    cout << setw(5) << " "
         << "Introduceti ID-ul salii pe care doriti sa o stergeti din baza de date: ";
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
    for (unsigned int i = 1; i <= NumarSali; i++)
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
    cout << setw(5) << " "
         << "Introduceti datele noului/noii actor/actrite: "
         << "\n\n";
    cout << setw(6) << " "
         << "ID-ul actorului: " << copie_ID_Actor_Max << endl;
    actorTeatru[NumarActori].ID_Actor = copie_ID_Actor_Max;
    cout << setw(6) << " "
         << "ID-ul piesei in care joaca actorul: ";

    while (!valid)
    {
        cin >> actorTeatru[NumarActori].ID_Piesa;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << '\n';
            cerr << setw(6) << " "
                 << "Valoarea introdusa in campul ID PIESA este invalida!" << endl;
            Sleep(1500);
            copie_ID_Actor_Max--;
            Adaugare_Actori();
        }
        else
            valid = true;
    }

    cout << setw(6) << " "
         << "Numele actorului: ";
    cin >> actorTeatru[NumarActori].Nume_Actor;
    cout << setw(6) << " "
         << "Prenumele actorului: ";
    cin >> actorTeatru[NumarActori].Prenume_Actor;
    cout << setw(6) << " "
         << "Varsta actorului: ";

    valid = false;
    while (!valid)
    {
        cin >> actorTeatru[NumarActori].Varsta_Actor;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << '\n';
            cerr << setw(6) << " "
                 << "Valoarea introdusa in campul VARSTA este invalida!" << endl;
            Sleep(1500);
            copie_ID_Actor_Max--;
            Adaugare_Actori();
        }
        else
            valid = true;
    }

    cout << setw(6) << " "
         << "Email-ul actorului: ";
    cin >> actorTeatru[NumarActori].Email_Actor;
    cout << setw(6) << " "
         << "CNP-ul actorului: ";

    valid = false;
    while (!valid)
    {
        cin >> actorTeatru[NumarActori].CNP_Actor;
        if (strlen(actorTeatru[NumarActori].CNP_Actor) != 13)
        {
            cin.clear();
            cin.ignore();
            cout << '\n';
            cerr << setw(6) << " "
                 << "Valoarea introdusa in campul CNP este invalida!" << endl;
            Sleep(1500);
            copie_ID_Actor_Max--;
            Adaugare_Actori();
        }
        else
            valid = true;
    }

    cout << setw(6) << " "
         << "Sex-ul actorului (F/M): ";
    cin.get();
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
    afisare_actori();

    unsigned int vID;
    bool valid = false;

    cout << "\n\n";
    cout << setw(5) << " "
         << "APASA TASTA '0' PENTRU A ANULA";
    cout << "\n\n";
    cout << setw(5) << " "
         << "Introduceti ID-ul actorului pe care doriti sa il stergeti din baza de date: ";

    while (!valid)
    {
        cin >> vID;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << '\n';
            cerr << setw(6 - 1) << " "
                 << "Valoarea introdusa in campul ID ACTOR este invalida!" << endl;
            Sleep(1500);
            Stergere_Actori();
        }
        else
            valid = true;
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

void Adaugare_Personal()
{
    system("CLS");

    copie_ID_Personal_Max++;
    NumarPersonalTeatru++;

    cout << "\n\n";
    cout << setw(4) << " "
         << "Introduceti datele noului angajat (administratie teatru):"
         << "\n\n";
    cout << setw(6) << " "
         << "ID-ul angajatului: " << copie_ID_Personal_Max << endl;
    personalTeatru[NumarPersonalTeatru].ID_PersonalTeatru = copie_ID_Personal_Max;

    cout << setw(6) << " "
         << "Functie: ";
    char vFunctiePersonalTeatru[1001];
    cin.get();
    cin.get(vFunctiePersonalTeatru, 1001);

    for (unsigned int i = 0; i < strlen(vFunctiePersonalTeatru); i++)
        if (vFunctiePersonalTeatru[i] == ' ')
            vFunctiePersonalTeatru[i] = '_';
    strcpy(personalTeatru[NumarPersonalTeatru].Functie_PersonalTeatru, vFunctiePersonalTeatru);

    cout << setw(6) << " "
         << "Nume angajat: ";
    cin >> personalTeatru[NumarPersonalTeatru].Nume_PersonalTeatru;
    cout << setw(6) << " "
         << "Prenume angajat: ";
    cin >> personalTeatru[NumarPersonalTeatru].Prenume_PersonalTeatru;
    cout << setw(6) << " "
         << "CNP angajat: ";

    bool valid = false;
    while (!valid)
    {
        cin >> personalTeatru[NumarPersonalTeatru].CNP_PersonalTeatru;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << '\n';
            cerr << setw(6) << " "
                 << "Valoarea introdusa in campul CNP este invalida!" << endl;
            Sleep(1500);
            copie_ID_Personal_Max--;
            NumarPersonalTeatru--;
            Adaugare_Personal();
        }
        else
            valid = true;
    }

    cout << setw(6) << " "
         << "Varsta angajat: ";
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
    unsigned int vID;

    bool valid = false;

    cout << "\n\n";
    cout << setw(5) << " "
         << "APASA TASTA '0' PENTRU A ANULA";
    cout << "\n\n";
    cout << setw(5) << " "
         << "Introduceti ID-ul angajatului pe care doriti sa il stergeti din baza de date: ";

    while (!valid)
    {
        cin >> vID;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << '\n';
            cerr << setw(6 - 1) << " "
                 << "Valoarea introdusa in campul ID PIESA este invalida!" << endl;
            Sleep(1500);
            Stergere_Personal();
        }
        else
            valid = true;
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

void Adaugare_Piese()
{
    bool valid = false;

    system("CLS");
    copie_ID_Piesa_Max++;
    NumarPiese++;

    cout << "\n\n";
    cout << setw(4) << " "
         << "Introduceti datele noii piese:"
         << "\n\n";
    cout << setw(6) << " "
         << "ID-ul piesei: " << copie_ID_Piesa_Max << endl;
    piesaTeatru[NumarPiese].ID_Piesa = copie_ID_Piesa_Max;
    cout << setw(6) << " "
         << "ID-ul salii in care se va tine piesa de teatru: ";

    while (!valid)
    {
        cin >> piesaTeatru[NumarPiese].ID_Sala;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << '\n';
            cerr << setw(6 - 1) << " "
                 << "Valoarea introdusa in campul ID SALA este invalida!" << endl;
            Sleep(1500);
            Adaugare_Piese();
        }
        else
            valid = true;
    }

    if (piesaTeatru[NumarPiese].ID_Sala == 0)
        return;

    char vNumeRegizor[101], vPrenumeRegizor[101];

    cout << setw(5 + 1) << " "
         << "Tasteaza numele regizorului: ";

    cin.get();
    cin.get(vNumeRegizor, 101);

    cout << setw(5 + 1) << " "
         << "Tasteaza prenumele regizorului: ";

    cin.get();
    cin.get(vPrenumeRegizor, 101);

    unsigned int copieID = 0, ID_Personal_Locala = 0;
    for (unsigned int i = 1; i <= NumarPersonalTeatru; i++)
    {
        if (stricmp(vNumeRegizor, personalTeatru[i].Nume_PersonalTeatru) == 0 && stricmp(vPrenumeRegizor, personalTeatru[i].Prenume_PersonalTeatru) == 0)
            copieID = personalTeatru[i].ID_PersonalTeatru;
        ID_Personal_Locala = personalTeatru[i].ID_PersonalTeatru;
    }

    if (copieID == 0)
    {
        cout << '\n';
        cerr << setw(5 + 1) << " " << "Regizorul respectiv nu exista in baza de date!" << endl;
        Sleep(1500);
        system("CLS");

        cout << "\n\n";
        cout << setw(5 + 1) << " " << "Doresti sa adaugi un nou angajat?" << "\n\n";
        cout << setw(5 + 1) << " " << "1. Adauga un nou angajat" << endl;
        cout << setw(5 + 1) << " " << "0. Inapoi" << "\n\n";

        unsigned int alegereUtilizator;
        cout << setw(5 + 1) << " "
             << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
        cin >> alegereUtilizator;

        if (alegereUtilizator == 1)
        {
            Adaugare_Personal();
            piesaTeatru[NumarPiese].ID_PersonalTeatru = ID_Personal_Locala + 1;
        }
        else
        {
            copie_ID_Piesa_Max--;
            NumarPiese--;
            return;
        }
    }
    else
        piesaTeatru[NumarPiese].ID_PersonalTeatru = copieID;

    cout << setw(6) << " "
         << "Data: ";
    cin >> piesaTeatru[NumarPiese].Data_Piesa;

    if (piesaTeatru[NumarPiese].Data_Piesa == 0)
        return;

    cout << setw(6) << " "
         << "Ora: ";
    cin >> piesaTeatru[NumarPiese].Ora_Piesa;
    cout << setw(6) << " "
         << "Nume: ";
    cin.get();
    cin.get(piesaTeatru[NumarPiese].Nume_Piesa, 101);

    cout << '\n'
         << setw(4) << " "
         << "Apasati enter pentru a va intoarce la meniul precedent...";

    _getch();

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
    cout << setw(5) << " "
         << "APASA TASTA '0' PENTRU A ANULA";
    cout << "\n\n";
    cout << setw(5) << " "
         << "Introduceti ID-ul piesei pe care doriti sa il stergeti din baza de date: ";

    while (!valid)
    {
        cin >> vID;
        if (cin.fail() || vID > copie_ID_Piesa_Max)
        {
            cin.clear();
            cin.ignore();
            cout << '\n';
            cerr << setw(6 - 1) << " "
                 << "Valoarea introdusa in campul ID PIESA este invalida!" << endl;
            Sleep(1500);
            Stergere_Actori();
        }
        else
            valid = true;
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
    cout << setw(4) << " "
         << "Introduceti datele noii sali:"
         << "\n\n";
    cout << setw(6) << " "
         << "ID-ul biletului: " << copie_ID_Bilet_Max << endl;
    biletPiesa[NumarBilete].ID_Bilet = copie_ID_Bilet_Max;
    cout << setw(6) << " "
         << "Descrierea tipului de bilet (maxim 100 de caractere): ";

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

        cout << setw(6) << " "
             << "Pret bilet: ";

        float pretBiletAux;

        while (!valid)
        {
            cin >> pretBiletAux;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
                cout << '\n';
                cerr << setw(6) << " "
                     << "Valoarea introdusa in campul PRET BILET este invalida!" << endl;
                Sleep(1500);
                copie_ID_Bilet_Max--;
                Adaugare_Bilet();
            }
            else
                valid = true;
        }

        biletPiesa[NumarBilete].Pret_Bilet = pretBiletAux + 0.00;

        cout << '\n'
             << setw(4) << " "
             << "Apasati enter pentru a va intoarce la meniul precedent...";

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
    cout << setw(5) << " "
         << "APASA TASTA '0' PENTRU A ANULA";
    cout << "\n\n";
    cout << setw(5) << " "
         << "Introduceti ID-ul piesei pe care doriti sa il stergeti din baza de date: ";

    while (!valid)
    {
        cin >> vID;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << '\n';
            cerr << setw(6 - 1) << " "
                 << "Valoarea introdusa in campul ID PIESA este invalida!" << endl;
            Sleep(1500);
            Stergere_Actori();
        }
        else
            valid = true;
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

void Venituri()
{
    contorVenit = 0;
    sort_piese_ID_crescator();

    float sumaTotalaPiesa = 0.00;

    for (unsigned int i = 1; i <= NumarPieseVechi; i++)
    {
        sumaTotalaPiesa = 0.00;

        for (unsigned int j = 1; j <= NumarSpectatoriVechi; j++)
            if (piesa_veche[i].ID_Piesa == spectator_vechi[j].ID_Piesa)
                for (unsigned int k = 1; k <= NumarBilete; k++)
                    if (biletPiesa[k].ID_Bilet == spectator_vechi[j].ID_Bilet)
                        sumaTotalaPiesa += biletPiesa[k].Pret_Bilet;

        venitPiesa[contorVenit].ID_Piesa = piesa_veche[i].ID_Piesa;
        strcpy(venitPiesa[contorVenit].Data_Piesa, piesa_veche[i].Data_Piesa);
        venitPiesa[contorVenit].suma = sumaTotalaPiesa;
        contorVenit++;
    }

    contorVenit--;

    for (unsigned int i = 1; i <= NumarPiese; i++)
    {
        sumaTotalaPiesa = 0.00;

        for (unsigned int j = 1; j <= NumarSpectatori; j++)
            if (piesaTeatru[i].ID_Piesa == spectatorPiesa[j].ID_Piesa)
                for (unsigned int k = 1; k <= NumarBilete; k++)
                    if (biletPiesa[k].ID_Bilet == spectatorPiesa[j].ID_Bilet)
                        sumaTotalaPiesa += biletPiesa[k].Pret_Bilet;

        venitPiesa[contorVenit].ID_Piesa = piesaTeatru[i].ID_Piesa;
        strcpy(venitPiesa[contorVenit].Data_Piesa, piesaTeatru[i].Data_Piesa);
        venitPiesa[contorVenit].suma = sumaTotalaPiesa;
        contorVenit++;
    }

    contorVenit--;
}

void sortare_venituri_crescator_sumaAcumulata()
{
    bool vSort = true;

    do
    {
        vSort = true;
        for (unsigned int i = 1; i <= contorVenit - 1; i++)
            if (venitPiesa[i].suma > venitPiesa[i + 1].suma)
            {
                unsigned int aux;
                aux = venitPiesa[i].ID_Piesa;
                venitPiesa[i].ID_Piesa = venitPiesa[i + 1].ID_Piesa;
                venitPiesa[i + 1].ID_Piesa = aux;

                char DataAux[11];
                strcpy(DataAux, venitPiesa[i].Data_Piesa);
                strcpy(venitPiesa[i].Data_Piesa, venitPiesa[i + 1].Data_Piesa);
                strcpy(venitPiesa[i + 1].Data_Piesa, DataAux);

                float SumaAux;
                SumaAux = venitPiesa[i].suma;
                venitPiesa[i].suma = venitPiesa[i + 1].suma;
                venitPiesa[i + 1].suma = SumaAux;

                vSort = false;
            }
    }
    while (!vSort);
}

void sortare_venituri_descrescator_sumaAcumulata()
{
    bool vSort = true;

    do
    {
        vSort = true;
        for (unsigned int i = 1; i <= contorVenit - 1; i++)
            if (venitPiesa[i].suma < venitPiesa[i + 1].suma)
            {
                unsigned int aux;
                aux = venitPiesa[i].ID_Piesa;
                venitPiesa[i].ID_Piesa = venitPiesa[i + 1].ID_Piesa;
                venitPiesa[i + 1].ID_Piesa = aux;

                char DataAux[11];
                strcpy(DataAux, venitPiesa[i].Data_Piesa);
                strcpy(venitPiesa[i].Data_Piesa, venitPiesa[i + 1].Data_Piesa);
                strcpy(venitPiesa[i + 1].Data_Piesa, DataAux);

                float SumaAux;
                SumaAux = venitPiesa[i].suma;
                venitPiesa[i].suma = venitPiesa[i + 1].suma;
                venitPiesa[i + 1].suma = SumaAux;

                vSort = false;
            }
    }
    while (!vSort);
}

void sortare_venituri_data()
{
    system("CLS");

    struct dataPiesa
    {
        unsigned int ID_Piesa;
        unsigned int zi;
        unsigned int luna;
        unsigned int an;
    } dataLoc[1001], dataIntrodusa;

    unsigned int contorData = 0, contor = 1;
    unsigned int vectorZi[2], vectorLuna[2], vectorAn[4];
    unsigned int ziFinala = 0, lunaFinala = 0, anFinal = 0;

    char matrix[3][11];

    cout << "\n\n";
    cout << setw(5) << " " << "Introduceti data (FORMAT: DD.MM.YYYY): " << "\n\n";
    cout << setw(5) << " " << "Ziua (DD): ";
    cin >> dataIntrodusa.zi;
    cout << setw(5) << " " << "Luna (MM): ";
    cin >> dataIntrodusa.luna;
    cout << setw(5) << " " << "An (YYYY): ";
    cin >> dataIntrodusa.an;

    for (unsigned int i = 1; i <= contorVenit; i++)
    {
        ziFinala = 0;
        lunaFinala = 0;
        anFinal = 0;

        for (unsigned int j = 0; j < strlen(venitPiesa[i].Data_Piesa); j++)
            if (venitPiesa[i].Data_Piesa[j] == '.')
                venitPiesa[i].Data_Piesa[j] = ' ';

        char copieData[11];
        strcpy(copieData, venitPiesa[i].Data_Piesa);

        for (unsigned int j = 0; j < strlen(venitPiesa[i].Data_Piesa); j++)
            if (venitPiesa[i].Data_Piesa[j] == ' ')
                venitPiesa[i].Data_Piesa[j] = '.';

        char *p = strtok(copieData, " ");

        contorData = 0;

        while (p != NULL)
        {
            strcpy(matrix[contorData], p);
            contorData++;
            p = strtok(NULL, " ");
        }

        if (matrix[0][0] == '0')
        {
            matrix[0][0] = matrix[0][1];
            matrix[0][1] = NULL;
        }

        if (matrix[1][0] == '0')
        {
            matrix[1][0] = matrix[1][1];
            matrix[1][1] = NULL;
        }

        if (strlen(matrix[0]) == 2)
        {
            vectorZi[0] = (unsigned int)(matrix[0][0]) - 48;
            vectorZi[1] = (unsigned int)(matrix[0][1]) - 48;

            for (unsigned int i = 0; i < 2; i++)
                ziFinala = ziFinala * 10 + vectorZi[i];
        }
        else
            ziFinala = (unsigned int)(matrix[0][0]) - 48;

        if (strlen(matrix[1]) == 2)
        {
            vectorLuna[0] = (unsigned int)(matrix[1][0]) - 48;
            vectorLuna[1] = (unsigned int)(matrix[1][1]) - 48;

            for (unsigned int i = 0; i < 2; i++)
                lunaFinala = lunaFinala * 10 + vectorLuna[i];
        }
        else
            lunaFinala = (unsigned int)(matrix[1][0]) - 48;


        vectorAn[0] = (unsigned int)(matrix[2][0]) - 48;
        vectorAn[1] = (unsigned int)(matrix[2][1]) - 48;
        vectorAn[2] = (unsigned int)(matrix[2][2]) - 48;
        vectorAn[3] = (unsigned int)(matrix[2][3]) - 48;

        for (unsigned int i = 0; i < 4; i++)
            anFinal = anFinal * 10 + vectorAn[i];

        dataLoc[contor].ID_Piesa = venitPiesa[i].ID_Piesa;
        dataLoc[contor].zi = ziFinala;
        dataLoc[contor].luna = lunaFinala;
        dataLoc[contor].an = anFinal;

        contor++;
    }

    contor--;

    sort_venituri_ID_crescator();

    system("CLS");

    cout << "\n\n";
    cout << setw(5) << " " << "ID Piesa" << setw(5) << " " << "Data piesei" << setw(6) << " " << "Venit" << '\n';

    fillLinieConsola(50);

    for (unsigned int i = 1; i <= contorVenit; i++)
        for (unsigned int j = 1; j <= contor; j++)
        {
            if (venitPiesa[i].ID_Piesa == dataLoc[j].ID_Piesa)
            {
                if (dataLoc[j].an > dataIntrodusa.an)
                    cout << setw(10 - 2) << " " << venitPiesa[i].ID_Piesa << setw(10 - 1) << " " << venitPiesa[i].Data_Piesa << setw(10 - 6) << " "
                         << venitPiesa[i].suma << " RON" << endl;
                else if (dataLoc[j].an == dataIntrodusa.an)
                {
                    if (dataLoc[j].luna > dataIntrodusa.luna)
                        cout << setw(10 - 2) << " " << venitPiesa[i].ID_Piesa << setw(10 - 1) << " " << venitPiesa[i].Data_Piesa << setw(10 - 6) << " "
                             << venitPiesa[i].suma << " RON" << endl;
                    else if (dataLoc[j].luna == dataIntrodusa.luna)
                        if (dataLoc[j].zi > dataIntrodusa.zi)
                            cout << setw(10 - 2) << " " << venitPiesa[i].ID_Piesa << setw(10 - 1) << " " << venitPiesa[i].Data_Piesa << setw(10 - 6) << " "
                                 << venitPiesa[i].suma << " RON" << endl;
                }
            }
        }

    fillLinieConsola(50);

    cout << '\n'
         << setw(4) << " "
         << "Apasati enter pentru a va intoarce la meniul precedent...";
}

void resetare_afisare_venituri()
{
    sort_venituri_ID_crescator();
}

/// MATEI
void piese_dupa_data()
{
    cout << endl
         << "Tasteaza data (FORMAT: DD.MM.YYYY): ";
    char date[11];
    cin.get();
    cin.get(date, 11);
    unsigned int NumarMaxCaractere = 0;

    for (unsigned int i = 1; i <= NumarPiese; i++)
        if (strcmp(date, piesaTeatru[i].Data_Piesa) < 0)
            if (strlen(piesaTeatru[i].Nume_Piesa) > NumarMaxCaractere)
                NumarMaxCaractere = strlen(piesaTeatru[i].Nume_Piesa);

    cout << "\n\n"
         << setw(5 - 1) << " "
         << "ID" << setw(5 + 1) << " "
         << "Nume" << setw(NumarMaxCaractere + 1) << " "
         << "Data" << endl;
    fillLinieConsola(85);

    for (unsigned int i = 1; i <= NumarPiese; i++)
        if (strcmp(date, piesaTeatru[i].Data_Piesa) < 0)
            cout << setw(5) << " " << piesaTeatru[i].ID_Piesa << setw(5) << " " << piesaTeatru[i].Nume_Piesa
                 << setw(NumarMaxCaractere - strlen(piesaTeatru[i].Nume_Piesa) + 5) << " " << piesaTeatru[i].Data_Piesa << endl;
}

void sali_cu_piesa()
{
    system("CLS");
    afisare_sali();

    cout << setw(5 - 1) << " "
         << "APASA TASTA '0' PENTRU A ANULA";
    cout << "\n\n";

    cout << endl << setw(5 - 1) << " "
         << "Tasteaza ID-ul salii: ";
    unsigned int vID_Sala;

    cin >> vID_Sala;

    if (vID_Sala == 0)
        return;
    else
    {
        for (unsigned int i = 1; i <= NumarPiese; i++)
            if (piesaTeatru[i].ID_Sala == vID_Sala)
            {
                cout << '\n';

                cout << setw(5 - 1) << " "
                     << "ID: " << piesaTeatru[i].ID_Piesa << endl;
                cout << setw(5 - 1) << " "
                     << "Nume: " << piesaTeatru[i].Nume_Piesa << endl;
                cout << setw(5 - 1) << " "
                     << "Sala: " << piesaTeatru[i].ID_Sala << endl;
                cout << setw(5 - 1) << " "
                     << "Data: " << piesaTeatru[i].Data_Piesa << endl;
                cout << setw(5 - 1) << " "
                     << "Ora: " << piesaTeatru[i].Ora_Piesa << '\n';
            }

        cout << '\n'
             << setw(4) << " "
             << "Apasati enter pentru a va intoarce la meniul precedent...";

        _getch();
        sali_cu_piesa();
    }
}

void cautare_actori_nume()
{
    system("CLS");

    unsigned int Meniu_subprogram;

    cout << endl;
    cout << setw(5 - 1) << " "
         << "1. Cautare dupa prenume." << endl;
    cout << setw(5 - 1) << " "
         << "2. Cautare dupa nume de familie." << endl;
    cout << setw(5 - 1) << " "
         << "0. Inapoi"
         << "\n\n";

    cout << setw(5 - 1) << " "
         << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
    cin >> Meniu_subprogram;
    if (Meniu_subprogram == 1)
    {
        system("CLS");

        cout << endl;
        cout << setw(5 - 1) << " "
             << "Tasteaza prenumele actorului: ";
        char vPrenume_Actor[101];
        cin.get();
        cin.get(vPrenume_Actor, 101);

        unsigned int NumarMaxCaractereNume = 0;
        unsigned int NumarMaxCaracterePrenume = 0;
        unsigned int NumarMaxCaractereEmail = 0;

        for (unsigned int i = 1; i <= NumarActori; i++)
            if (stricmp(vPrenume_Actor, actorTeatru[i].Prenume_Actor) == 0)
            {
                if (strlen(actorTeatru[i].Nume_Actor) > NumarMaxCaractereNume)
                    NumarMaxCaractereNume = strlen(actorTeatru[i].Nume_Actor);
                if (strlen(actorTeatru[i].Prenume_Actor) > NumarMaxCaracterePrenume)
                    NumarMaxCaracterePrenume = strlen(actorTeatru[i].Prenume_Actor);
                if (strlen(actorTeatru[i].Email_Actor) > NumarMaxCaractereEmail)
                    NumarMaxCaractereEmail = strlen(actorTeatru[i].Email_Actor);
            }
        cout << "\n\n"
             << setw(5 - 1) << " "
             << "ID_Actor"
             << " "
             << "ID_Piesa" << setw(5) << " "
             << "Nume_Actor"
             << setw(NumarMaxCaractereNume) << " "
             << "Prenume_Actor" << setw(NumarMaxCaracterePrenume) << " "
             << "Varsta_Actor" << setw(10) << " "
             << "Email_Actor" << setw(NumarMaxCaractereEmail - 1) << " "
             << "CNP" << setw(14) << " "
             << "Sex"
             << "\n";

        fillLinieConsola(150);

        for (unsigned int i = 1; i <= NumarActori; i++)
            if (stricmp(vPrenume_Actor, actorTeatru[i].Prenume_Actor) == 0)
                cout << setw(5) << " " << actorTeatru[i].ID_Actor << setw(10 - 1) << " " << actorTeatru[i].ID_Piesa << setw(10 - 1) << " " << actorTeatru[i].Nume_Actor
                     << setw(NumarMaxCaractereNume - strlen(actorTeatru[i].Nume_Actor) + 10) << " " << actorTeatru[i].Prenume_Actor
                     << setw(NumarMaxCaracterePrenume - strlen(actorTeatru[i].Prenume_Actor) + 15) << " " << actorTeatru[i].Varsta_Actor << " ani"
                     << setw(10) << " " << actorTeatru[i].Email_Actor << setw(NumarMaxCaractereEmail - strlen(actorTeatru[i].Email_Actor) + 10)
                     << " " << actorTeatru[i].CNP_Actor << setw(8) << " " << actorTeatru[i].Sex_Actor << setw(10) << "\n";

        fillLinieConsola(150);

        cout << '\n'
             << setw(4) << " "
             << "Apasati enter pentru a va intoarce la meniul precedent...";
    }
    else if (Meniu_subprogram == 0)
        return;
    else
    {
        system("CLS");

        cout << endl;
        cout << setw(5 - 1) << " "
             << "Tasteaza numele de familie al actorului: ";
        char vNume_Actor[101];
        cin.get();
        cin.get(vNume_Actor, 101);

        unsigned int NumarMaxCaractereNume = 0;
        unsigned int NumarMaxCaracterePrenume = 0;
        unsigned int NumarMaxCaractereEmail = 0;

        for (unsigned int i = 1; i <= NumarActori; i++)
            if (stricmp(vNume_Actor, actorTeatru[i].Nume_Actor) == 0)
            {
                if (strlen(actorTeatru[i].Nume_Actor) > NumarMaxCaractereNume)
                    NumarMaxCaractereNume = strlen(actorTeatru[i].Nume_Actor);
                if (strlen(actorTeatru[i].Prenume_Actor) > NumarMaxCaracterePrenume)
                    NumarMaxCaracterePrenume = strlen(actorTeatru[i].Prenume_Actor);
                if (strlen(actorTeatru[i].Email_Actor) > NumarMaxCaractereEmail)
                    NumarMaxCaractereEmail = strlen(actorTeatru[i].Email_Actor);
            }
        cout << "\n\n"
             << setw(5 - 1) << " "
             << "ID_Actor"
             << " "
             << "ID_Piesa" << setw(5) << " "
             << "Nume_Actor"
             << setw(NumarMaxCaractereNume) << " "
             << "Prenume_Actor" << setw(NumarMaxCaracterePrenume) << " "
             << "Varsta_Actor" << setw(10) << " "
             << "Email_Actor" << setw(NumarMaxCaractereEmail - 1) << " "
             << "CNP" << setw(14) << " "
             << "Sex"
             << "\n";

        fillLinieConsola(150);

        for (unsigned int i = 1; i <= NumarActori; i++)
            if (stricmp(vNume_Actor, actorTeatru[i].Nume_Actor) == 0)
                cout << setw(5) << " " << actorTeatru[i].ID_Actor << setw(10 - 1) << " " << actorTeatru[i].ID_Piesa << setw(10 - 1) << " " << actorTeatru[i].Nume_Actor
                     << setw(NumarMaxCaractereNume - strlen(actorTeatru[i].Nume_Actor) + 10) << " " << actorTeatru[i].Prenume_Actor
                     << setw(NumarMaxCaracterePrenume - strlen(actorTeatru[i].Prenume_Actor) + 15) << " " << actorTeatru[i].Varsta_Actor << " ani"
                     << setw(10) << " " << actorTeatru[i].Email_Actor << setw(NumarMaxCaractereEmail - strlen(actorTeatru[i].Email_Actor) + 10)
                     << " " << actorTeatru[i].CNP_Actor << setw(8) << " " << actorTeatru[i].Sex_Actor << setw(10) << "\n";

        fillLinieConsola(150);

        cout << '\n'
             << setw(4) << " "
             << "Apasati enter pentru a va intoarce la meniul precedent...";
    }
    _getch();
    cautare_actori_nume();
}

void bilete_ieftine()
{
    system("CLS");
    afisare_bilete();

    float vPret;

    cout << setw(5 - 1) << " "
         << "APASA TASTA '0' PENTRU A ANULA";

    cout << "\n\n";
    cout << setw(5 - 1) << " "
         << "Tasteaza pretul: ";
    cin >> vPret;

    if (vPret == 0)
        return;
    else
    {
        cout << '\n';
        for (unsigned int i = 1; i <= NumarBilete; i++)
            if (biletPiesa[i].Pret_Bilet < vPret)
                cout << setw(5 - 1) << " " << biletPiesa[i].ID_Bilet << ": " << biletPiesa[i].Tip_Bilet << ", " << biletPiesa[i].Pret_Bilet << endl;

        cout << '\n'
             << setw(4) << " "
             << "Apasati enter pentru a va intoarce la meniul precedent...";

        _getch();
        bilete_ieftine();
    }
}

void bilete_pe_piesa()
{
    system("CLS");
    afisare_bilete();

    unsigned int vID_Piesa;
    unsigned int ok = 0, bilete = 0, bilete_loja = 0;

    bool piesaVeche = false;

    cout << '\n';
    cout << setw(5 - 1) << " "
         << "APASA TASTA '0' PENTRU A ANULA";
    cout << "\n\n";
    cout << setw(5 - 1) << " "
         << "Tasteaza ID-ul piesei cautate: ";

    bool valid = false;
    while (!valid)
    {
        cin >> vID_Piesa;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore();
            cout << '\n';
            cerr << setw(4) << " "
                 << "Valoarea introdusa este invalida!" << endl;
            Sleep(1500);
            bilete_pe_piesa();
        }
        else
            valid = true;
    }

    if (vID_Piesa == 0)
        return;
    else
    {
        system("CLS");
        afisare_bilete();

        for (unsigned int i = 1; i <= NumarPieseVechi && ok == 0; i++)
            if (piesa_veche[i].ID_Piesa == vID_Piesa)
            {
                piesaVeche = true;

                for (unsigned int j = 1; j <= NumarSpectatori; j++)
                    if (spectatorPiesa[j].ID_Piesa == piesaTeatru[i].ID_Piesa)
                    {
                        bilete++;
                        if (spectatorPiesa[j].loja == 1)
                            bilete_loja++;
                    }
                ok = 1;
            }

        for (unsigned int i = 1; i <= NumarPiese && ok == 0; i++)
            if (piesaTeatru[i].ID_Piesa == vID_Piesa)
            {
                for (unsigned int j = 1; j <= NumarSpectatori; j++)
                    if (spectatorPiesa[j].ID_Piesa == piesaTeatru[i].ID_Piesa)
                    {
                        bilete++;
                        if (spectatorPiesa[j].loja == 1)
                            bilete_loja++;
                    }
                ok = 1;
            }

        cout << '\n';
        if (piesaVeche == true)
        {
            cout << setw(5 - 1) << " " << "Pentru piesa '" << piesa_veche[vID_Piesa].Nume_Piesa << "' s-au vandut " << bilete
                 << " bilete, dintre care " << bilete_loja << " pentru loja " << "(" << piesa_veche[vID_Piesa].Data_Piesa << ")." << '\n';

            cout << "\n\n"
                 << setw(4) << " "
                 << "Apasati enter pentru a va intoarce la meniul precedent...";
        }

        else
        {
            char dataPiesaLocala[11], numePiesaLocal[101];

            for (unsigned int i = 1; i <= NumarPiese; i++)
                if (piesaTeatru[i].ID_Piesa == vID_Piesa)
                {
                    strcpy(dataPiesaLocala, piesaTeatru[i].Data_Piesa);
                    strcpy(numePiesaLocal, piesaTeatru[i].Nume_Piesa);
                }

            cout << setw(5 - 1) << " " << "Pentru piesa '" << numePiesaLocal << "' s-au vandut " << bilete
                 << " bilete, dintre care " << bilete_loja << " pentru loja " << "(" << dataPiesaLocala << ")." << '\n';

            cout << "\n\n"
                 << setw(4) << " "
                 << "Apasati enter pentru a va intoarce la meniul precedent...";
        }
    }
    _getch();
    bilete_pe_piesa();
}

void bilete_nevandute()
{
    system("CLS");
    afisare_bilete();

    cout << endl;
    unsigned int bilete_vandute[201] = {0};
    for (unsigned int i = 1; i <= NumarSpectatoriVechi; i++)
        bilete_vandute[spectator_vechi[i].ID_Piesa]++;
    unsigned int meniu_subprogram;

    cout << setw(5) << " " << "1. Numarul de bilete nevandute intr-o piesa." << endl
         << setw(5) << " " << "2. Numarul de bilete nevandute in total." << endl
         << setw(5) << " " << "0. Inapoi"
         << "\n\n";
    cout << setw(5 - 1) << " " << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
    cin >> meniu_subprogram;

    if (meniu_subprogram == 1)
    {
        system("CLS");
        afisare_bilete();

        cout << endl
             << setw(5 - 1) << " " << "Tastati numele piesei: ";
        char vPiesaVeche[101];
        cin >> vPiesaVeche;
        unsigned int v = 0;
        for (unsigned int i = 1; i <= NumarPieseVechi; i++)
            if (strcmp(piesa_veche[i].Nume_Piesa, vPiesaVeche) == 0)
                v = v + (salaTeatru[piesa_veche[i].ID_Sala].Nr_Scaune + salaTeatru[piesa_veche[i].ID_Sala].Nr_Scaune_Loja - bilete_vandute[piesa_veche[i].ID_Piesa]);
        cout << '\n' << setw(5 - 1) << " " << "In total, aceasta piesa a avut " << v << " bilete nevandute." << endl;

        cout << "\n\n"
             << setw(4) << " "
             << "Apasati enter pentru a va intoarce la meniul precedent...";

    }
    else if (meniu_subprogram == 0)
        return;
    else
    {
        system("CLS");
        afisare_bilete();

        unsigned int v = 0;
        for (unsigned int i = 1; i <= NumarPieseVechi; i++)
            v = v + (salaTeatru[piesa_veche[i].ID_Sala].Nr_Scaune + salaTeatru[piesa_veche[i].ID_Sala].Nr_Scaune_Loja - bilete_vandute[piesa_veche[i].ID_Piesa]);

        cout << setw(5 - 1) << " " << "In total, " << v << " bilete au ramas nevandute.";

        cout << "\n\n"
             << setw(4) << " "
             << "Apasati enter pentru a va intoarce la meniul precedent...";
    }
    _getch();
    bilete_nevandute();
}

void top5_piese()
{
    system("CLS");

    cout << "\n\n";

    piesa_v c_piesa_veche[201];
    for (unsigned int i = 1; i <= NumarPieseVechi; i++)
        c_piesa_veche[i] = piesa_veche[i];
    unsigned int c_NumarPieseVechi;
    c_NumarPieseVechi = NumarPieseVechi;
    for (unsigned int i = 1; i < c_NumarPieseVechi; i++)
        for (unsigned int j = i + 1; j <= c_NumarPieseVechi; j++)
            if (strcmp(c_piesa_veche[i].Nume_Piesa, c_piesa_veche[j].Nume_Piesa) == 0)
            {
                for (unsigned int k = j; k < c_NumarPieseVechi; k++)
                    c_piesa_veche[k] = c_piesa_veche[k + 1];
                c_NumarPieseVechi--;
                j--;
            }

    unsigned int max1 = 0, max2 = 0, max3 = 0, max4 = 0, max5 = 0, v;
    char max1_p[101] = "", max2_p[101] = "", max3_p[101] = "", max4_p[101] = "", max5_p[101] = "";
    for (unsigned int i = 1; i <= c_NumarPieseVechi; i++)
    {
        v = 0;
        for (unsigned int j = 1; j <= NumarPieseVechi; j++)
            if (strcmp(c_piesa_veche[i].Nume_Piesa, piesa_veche[j].Nume_Piesa) == 0)
                for (unsigned int k = 1; k <= NumarSpectatoriVechi; k++)
                    if (piesa_veche[j].ID_Piesa == spectator_vechi[k].ID_Piesa)
                        v++;
        if (v > max1)
        {
            max1 = v;
            strcpy(max1_p, c_piesa_veche[i].Nume_Piesa);
        }
        else if (v > max2)
        {
            max2 = v;
            strcpy(max2_p, c_piesa_veche[i].Nume_Piesa);
        }
        else if (v > max3)
        {
            max3 = v;
            strcpy(max3_p, c_piesa_veche[i].Nume_Piesa);
        }
        else if (v > max4)
        {
            max4 = v;
            strcpy(max4_p, c_piesa_veche[i].Nume_Piesa);
        }
        else if (v > max5)
        {
            max5 = v;
            strcpy(max5_p, c_piesa_veche[i].Nume_Piesa);
        }
    }

    cout << setw(5) << " "
         << "1. " << max1_p << ", cu " << max1 << " bilete vandute in total" << endl
         << setw(5) << " "
         << "2. " << max2_p << ", cu " << max2 << " bilete vandute in total" << endl
         << setw(5) << " "
         << "3. " << max3_p << ", cu " << max3 << " bilete vandute in total" << endl
         << setw(5) << " "
         << "4. " << max4_p << ", cu " << max4 << " bilete vandute in total" << endl
         << setw(5) << " "
         << "5. " << max5_p << ", cu " << max5 << " bilete vandute in total" << endl;

    cout << '\n'
         << setw(4) << " "
         << "Apasati enter pentru a va intoarce la meniul precedent...";
}

///Ioana
///Afisati toate piesele care incep cu litera � (litera va fi introdus de la tastatura)
void afisare_prima_litera()
{
    system("CLS");

    cout << "\n\n";
    cout << setw(5 - 1) << " "
         << "APASA TASTA '0' PENTRU A ANULA";

    cout << "\n\n";
    cout<< setw(5 - 1) << " "
        <<"Introduceti litera: ";
    char l;
    cin>>l;

    if (l == '0')
        return;
    else
    {
        if(l>='a'&&l<='z')
            l=l-32;

        cout << endl;
        for (unsigned int i = 1; i <= NumarPiese; i++)
            if(piesaTeatru[i].Nume_Piesa[0]==l)
                cout << setw(5 - 1) << " " << piesaTeatru[i].ID_Piesa << setw(5 - 1) << " " << piesaTeatru[i].Nume_Piesa
                     << setw(5 - 1) << " " << piesaTeatru[i].Data_Piesa << " "
                     << setw(5 - 1) << " " << piesaTeatru[i].Ora_Piesa << setw(5 - 1) << endl;
        cout << '\n'
             << setw(4) << " "
             << "Apasati enter pentru a va intoarce la meniul precedent...";

        _getch();
        afisare_prima_litera();
    }
}

/// Afisati toate piesele care se tin dupa ora�(ora va fi introdusa de la tastatura)
void piese_dupa_ora()
{
    system("CLS");

    cout << "\n\n";
    cout << setw(5 - 1) << " "
         << "APASA TASTA '0' PENTRU A ANULA";
    cout << "\n\n";

    cout<< setw(5 - 1) << " "
        <<"Introduceti ora dorita: ";

    char ora[6];
    cin.get();
    cin.get(ora, 6);

    system("CLS");
    cout << "\n\n";

    if (strcmp(ora, "0") == 0)
        return;
    else
    {
        for (unsigned int i = 1; i <= NumarPiese; i++)
            if (strcmp(ora, piesaTeatru[i].Ora_Piesa) <= 0)
                cout << setw(5 - 1) << " " << piesaTeatru[i].Nume_Piesa << " "
                     << "- ora " << piesaTeatru[i].Ora_Piesa << " "
                     << "- data " << piesaTeatru[i].Data_Piesa << "\n\n";

        cout << '\n'
             << setw(4) << " "
             << "Apasati enter pentru a va intoarce la meniul precedent...";

        _getch();
        piese_dupa_ora();
    }
}

/// Afisarea primelor 3 cele mai incapatoare sali din teatru
void cele_mai_mari_3_sali()
{
    system("CLS");

    cout << "\n\n";
    cout << setw(5 - 1) << " "
         << "Primele 3 cele mai incapatoare sali din teatru: "
         << "\n\n";

    unsigned int i, aux, j;
    unsigned int v_locuri[1000], v_sala[1000];

    for (i = 1; i <= NumarSali - 1; i++)
    {
        v_locuri[i] = salaTeatru[i].Nr_Scaune + salaTeatru[i].Nr_Scaune_Loja;
        v_sala[i] = salaTeatru[i].ID_Sala;
    }
    for (i = 1; i <= NumarSali - 2; i++)
        for (j = i + 1; j <= NumarSali - 1; j++)
            if (v_locuri[i] < v_locuri[j])
            {
                aux = v_locuri[i];
                v_locuri[i] = v_locuri[j];
                v_locuri[j] = aux;
                aux = v_sala[i];
                v_sala[i] = v_sala[j];
                v_sala[j] = aux;
            }
    for (i = 1; i <= 3; i++)
        cout << setw(5) << " "
             << "Sala: " << v_sala[i] << " cu " << v_locuri[i] << " locuri" << endl;

    cout << '\n'
         << setw(4) << " "
         << "Apasati enter pentru a va intoarce la meniul precedent...";
    _getch();
}

/// Afisarea tuturor actorilor a caror varsta este mai mare sau egala cu � ani.
void varsta_mai_mare_actori()
{
    system("CLS");

    unsigned int nrMaxCaractereNume = 0;
    for (unsigned int i = 1; i <= NumarActori; i++)
        if (strlen(actorTeatru[i].Nume_Actor) > nrMaxCaractereNume)
            nrMaxCaractereNume = strlen(actorTeatru[i].Nume_Actor);

    unsigned int nrMaxCaracterePrenume = 0;
    for (unsigned int i = 1; i <= NumarActori; i++)
        if (strlen(actorTeatru[i].Prenume_Actor) > nrMaxCaracterePrenume)
            nrMaxCaracterePrenume = strlen(actorTeatru[i].Prenume_Actor);

    cout << '\n';
    cout << setw(5 - 1) << " "
         << "APASA TASTA '0' PENTRU A ANULA";
    cout << "\n\n";

    unsigned int varsta = 0, i;
    cout << setw(4) << " "
         << "Introduceti varsta: ";
    cin >> varsta;

    if (varsta == 0)
        return;
    else
    {
        system("CLS");
        cout << "\n\n";

        cout << setw(5) << " "
             << "Nume" << setw(nrMaxCaractereNume) << " "
             << "Prenume" << setw(7) << " "
             << "Varsta" << '\n';
        fillLinieConsola(60);

        for (i = 1; i <= NumarActori; i++)
            if (actorTeatru[i].Varsta_Actor >= varsta)
                cout << setw(4) << " " << actorTeatru[i].Nume_Actor << setw(nrMaxCaractereNume + 5 - strlen(actorTeatru[i].Nume_Actor))
                     << " " << actorTeatru[i].Prenume_Actor << setw(nrMaxCaracterePrenume + 5 - strlen(actorTeatru[i].Prenume_Actor)) << " "
                     << actorTeatru[i].Varsta_Actor << endl;

        fillLinieConsola(60);

        cout << '\n'
             << setw(4) << " "
             << "Apasati enter pentru a va intoarce la meniul precedent...";
        _getch();
        varsta_mai_mare_actori();
    }
}

/// Afisarea tuturor actorilor a caror varsta este mai mica sau egala cu � ani
void varsta_mai_mica_actori()
{
    system("CLS");

    unsigned int nrMaxCaractereNume = 0;
    for (unsigned int i = 1; i <= NumarActori; i++)
        if (strlen(actorTeatru[i].Nume_Actor) > nrMaxCaractereNume)
            nrMaxCaractereNume = strlen(actorTeatru[i].Nume_Actor);

    unsigned int nrMaxCaracterePrenume = 0;
    for (unsigned int i = 1; i <= NumarActori; i++)
        if (strlen(actorTeatru[i].Prenume_Actor) > nrMaxCaracterePrenume)
            nrMaxCaracterePrenume = strlen(actorTeatru[i].Prenume_Actor);

    cout << '\n';
    cout << setw(5 - 1) << " "
         << "APASA TASTA '0' PENTRU A ANULA";
    cout << "\n\n";

    unsigned int varsta = 0, i;
    cout << setw(4) << " "
         << "Introduceti varsta: ";
    cin >> varsta;

    if (varsta == 0)
        return;
    else
    {
        system("CLS");

        cout << "\n\n";
        cout << setw(5) << " "
             << "Nume" << setw(nrMaxCaractereNume) << " "
             << "Prenume" << setw(7) << " "
             << "Varsta" << '\n';

        fillLinieConsola(60);
        for (i = 1; i <= NumarActori; i++)
            if (actorTeatru[i].Varsta_Actor <= varsta)
                cout << setw(4) << " " << actorTeatru[i].Nume_Actor << setw(nrMaxCaractereNume + 5 - strlen(actorTeatru[i].Nume_Actor))
                     << " " << actorTeatru[i].Prenume_Actor << setw(nrMaxCaracterePrenume + 5 - strlen(actorTeatru[i].Prenume_Actor)) << " "
                     << actorTeatru[i].Varsta_Actor << endl;
        fillLinieConsola(60);

        cout << '\n'
             << setw(4) << " "
             << "Apasati enter pentru a va intoarce la meniul precedent...";
        _getch();
        varsta_mai_mica_actori();
    }
}

///Afisati toti actorii cu genul� (genul va fi introdus de la tastatura)
void gen_actori()
{
    system("CLS");

    unsigned int NumarMaxCaractereNume = 0;

    for (unsigned int i = 1; i <= NumarActori; i++)
        if (strlen(actorTeatru[i].Nume_Actor) > NumarMaxCaractereNume)
            NumarMaxCaractereNume = strlen(actorTeatru[i].Nume_Actor);

    unsigned int NumarMaxCaracterePrenume = 0;

    for (unsigned int i = 0; i <= NumarActori; i++)
        if (strlen(actorTeatru[i].Prenume_Actor) > NumarMaxCaracterePrenume)
            NumarMaxCaracterePrenume = strlen(actorTeatru[i].Prenume_Actor);

    unsigned int NumarMaxCaractereEmail = 0;

    for (unsigned int i = 0; i < NumarActori; i++)
        if (strlen(actorTeatru[i].Email_Actor) > NumarMaxCaractereEmail)
            NumarMaxCaractereEmail = strlen(actorTeatru[i].Email_Actor);

    char gen;

    cout << "\n\n";

    cout << setw(5 - 1) << " "
         << "APASA TASTA '0' PENTRU A ANULA";
    cout << "\n\n";

    cout << setw(5 - 1) << " " << "Introduceti genul (M / F): ";
    cin>>gen;

    if (gen == '0')
        return;
    else
    {
        system("CLS");

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

        if(gen>='a'&&gen<='z')
            gen=gen-32;
        for(unsigned int i=0; i<NumarActori; i++)
            if(actorTeatru[i].Sex_Actor==gen)
                cout << setw(5) << " " << actorTeatru[i].ID_Actor << setw(10 - 1) << " " << actorTeatru[i].ID_Piesa << setw(10 - 1) << " " << actorTeatru[i].Nume_Actor
                     << setw(NumarMaxCaractereNume - strlen(actorTeatru[i].Nume_Actor) + 10) << " " << actorTeatru[i].Prenume_Actor
                     << setw(NumarMaxCaracterePrenume - strlen(actorTeatru[i].Prenume_Actor) + 10) << " " << actorTeatru[i].Varsta_Actor << " ani"
                     << setw(10) << " " << actorTeatru[i].Email_Actor << setw(NumarMaxCaractereEmail - strlen(actorTeatru[i].Email_Actor) + 10) << "\n";
        fillLinieConsola(115);

        cout << '\n'
             << setw(4) << " "
             << "Apasati enter pentru a va intoarce la meniul precedent...";

        _getch();
        gen_actori();
    }
}

///Afisati tot personalul cu ocupatia� (numele ocupatiei va fi introdus de la tastatura)
void ocupatie_personal()
{
    system("CLS");

    unsigned int NumarMaxCaractereNume = 0;

    for (unsigned int i = 1; i <= NumarActori; i++)
        if (strlen(actorTeatru[i].Nume_Actor) > NumarMaxCaractereNume)
            NumarMaxCaractereNume = strlen(actorTeatru[i].Nume_Actor);

    unsigned int NumarMaxCaracterePrenume = 0;

    for (unsigned int i = 0; i <= NumarActori; i++)
        if (strlen(actorTeatru[i].Prenume_Actor) > NumarMaxCaracterePrenume)
            NumarMaxCaracterePrenume = strlen(actorTeatru[i].Prenume_Actor);

    unsigned int NumarMaxCaractereEmail = 0;

    for (unsigned int i = 0; i < NumarActori; i++)
        if (strlen(actorTeatru[i].Email_Actor) > NumarMaxCaractereEmail)
            NumarMaxCaractereEmail = strlen(actorTeatru[i].Email_Actor);

    char ocupatie[1001];

    cout << '\n';
    cout << setw(5 - 1) << " "
         << "APASA TASTA '0' PENTRU A ANULA";
    cout << "\n\n";

    cout << setw(5 - 1) << " " << "Introduceti ocupatia cautata: ";
    cin.get();
    cin.get(ocupatie,1001);

    if (strcmp(ocupatie, "0") == 0)
        return;
    else
    {
        unsigned int i;
        for(i=0; i<strlen(ocupatie); i++)
            if(ocupatie[i]>='A'&&ocupatie[i]<='Z')
                ocupatie[i]=ocupatie[i]-32;

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

        fillLinieConsola(115);

        for(i=1; i<=NumarPersonalTeatru; i++)
            if(stricmp(personalTeatru[i].Functie_PersonalTeatru,ocupatie)==0)
                cout << setw(5) << " " << actorTeatru[i].ID_Actor << setw(10 - 1) << " " << actorTeatru[i].ID_Piesa << setw(10 - 1) << " " << actorTeatru[i].Nume_Actor
                     << setw(NumarMaxCaractereNume - strlen(actorTeatru[i].Nume_Actor) + 10) << " " << actorTeatru[i].Prenume_Actor
                     << setw(NumarMaxCaracterePrenume - strlen(actorTeatru[i].Prenume_Actor) + 10) << " " << actorTeatru[i].Varsta_Actor << " ani"
                     << setw(10) << " " << actorTeatru[i].Email_Actor << setw(NumarMaxCaractereEmail - strlen(actorTeatru[i].Email_Actor) + 10) << "\n";
        fillLinieConsola(115);

        cout << '\n'
             << setw(4) << " "
             << "Apasati enter pentru a va intoarce la meniul precedent...";

        _getch();
        ocupatie_personal();
    }
}

///Afisarea personalului cu varsta mai mare sau egala cu � ani.
void varsta_mai_mare_personal()
{
    system("CLS");

    unsigned int NumarMaxCaractereNume = 0;

    for (unsigned int i = 1; i <= NumarActori; i++)
        if (strlen(actorTeatru[i].Nume_Actor) > NumarMaxCaractereNume)
            NumarMaxCaractereNume = strlen(actorTeatru[i].Nume_Actor);

    unsigned int NumarMaxCaracterePrenume = 0;

    for (unsigned int i = 0; i <= NumarActori; i++)
        if (strlen(actorTeatru[i].Prenume_Actor) > NumarMaxCaracterePrenume)
            NumarMaxCaracterePrenume = strlen(actorTeatru[i].Prenume_Actor);

    unsigned int NumarMaxCaractereEmail = 0;

    for (unsigned int i = 0; i < NumarActori; i++)
        if (strlen(actorTeatru[i].Email_Actor) > NumarMaxCaractereEmail)
            NumarMaxCaractereEmail = strlen(actorTeatru[i].Email_Actor);

    unsigned int varsta,i;

    cout << '\n';
    cout << setw(5 - 1) << " "
         << "APASA TASTA '0' PENTRU A ANULA";
    cout << "\n\n";

    cout << setw(5 - 1) << " " << "Introduceti varsta: ";
    cin>>varsta;

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

    if (varsta == 0)
        return;
    else
    {
        fillLinieConsola(115);

        for(i=1; i<=NumarPersonalTeatru; i++)
            if(personalTeatru[i].Varsta_PersonalTeatru>=varsta)
                cout << setw(5) << " " << actorTeatru[i].ID_Actor << setw(10 - 1) << " " << actorTeatru[i].ID_Piesa << setw(10 - 1) << " " << actorTeatru[i].Nume_Actor
                     << setw(NumarMaxCaractereNume - strlen(actorTeatru[i].Nume_Actor) + 10) << " " << actorTeatru[i].Prenume_Actor
                     << setw(NumarMaxCaracterePrenume - strlen(actorTeatru[i].Prenume_Actor) + 10) << " " << actorTeatru[i].Varsta_Actor << " ani"
                     << setw(10) << " " << actorTeatru[i].Email_Actor << setw(NumarMaxCaractereEmail - strlen(actorTeatru[i].Email_Actor) + 10) << "\n";
        fillLinieConsola(115);

        cout << '\n'
             << setw(4) << " "
             << "Apasati enter pentru a va intoarce la meniul precedent...";

        _getch();
        varsta_mai_mare_personal();
    }
}

/// Afisarea personalului cu varsta mai mica sau egala cu � ani
void varsta_mai_mica_personal()
{
    system("CLS");

    unsigned int NumarMaxCaractereNume = 0;

    for (unsigned int i = 1; i <= NumarActori; i++)
        if (strlen(actorTeatru[i].Nume_Actor) > NumarMaxCaractereNume)
            NumarMaxCaractereNume = strlen(actorTeatru[i].Nume_Actor);

    unsigned int NumarMaxCaracterePrenume = 0;

    for (unsigned int i = 0; i <= NumarActori; i++)
        if (strlen(actorTeatru[i].Prenume_Actor) > NumarMaxCaracterePrenume)
            NumarMaxCaracterePrenume = strlen(actorTeatru[i].Prenume_Actor);

    unsigned int NumarMaxCaractereEmail = 0;

    for (unsigned int i = 0; i < NumarActori; i++)
        if (strlen(actorTeatru[i].Email_Actor) > NumarMaxCaractereEmail)
            NumarMaxCaractereEmail = strlen(actorTeatru[i].Email_Actor);

    unsigned int varsta,i;

    cout << '\n';
    cout << setw(5 - 1) << " "
         << "APASA TASTA '0' PENTRU A ANULA";
    cout << "\n\n";

    cout << setw(5 - 1) << " " << "Introduceti varsta: ";
    cin>>varsta;

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


    if (varsta == 0)
        return;
    else
    {
        fillLinieConsola(115);
        for(i=0; i<NumarPersonalTeatru; i++)
            if(personalTeatru[i].Varsta_PersonalTeatru<=varsta)
                cout << setw(5) << " " << actorTeatru[i].ID_Actor << setw(10 - 1) << " " << actorTeatru[i].ID_Piesa << setw(10 - 1) << " " << actorTeatru[i].Nume_Actor
                     << setw(NumarMaxCaractereNume - strlen(actorTeatru[i].Nume_Actor) + 10) << " " << actorTeatru[i].Prenume_Actor
                     << setw(NumarMaxCaracterePrenume - strlen(actorTeatru[i].Prenume_Actor) + 10) << " " << actorTeatru[i].Varsta_Actor << " ani"
                     << setw(10) << " " << actorTeatru[i].Email_Actor << setw(NumarMaxCaractereEmail - strlen(actorTeatru[i].Email_Actor) + 10) << "\n";
        fillLinieConsola(115);
        cout << '\n'
             << setw(4) << " "
             << "Apasati enter pentru a va intoarce la meniul precedent...";

        _getch();
        varsta_mai_mica_personal();
    }

}

int main()
{

    /// Citirea datelor din fisierele corespunzatoare
    citire_sali();
    citire_actori();
    citire_piese();
    citire_personaje_piese();
    citire_bilete();
    citire_personal();
    citire_spectatori();
    citire_piese_vechi();
    citire_spectatori_vechi();

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
             << "6. Istoricul pieselor de teatru" << endl;
        cout << setw(5 - 1) << " "
             << "7. Venituri" << endl;
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
                     << "1. Detalii despre piesele de teatru" << endl;
                cout << setw(5 - 1) << " "
                     << "2. Personajele care joaca in piesele de teatru si actorii corespunzatori acestora" << endl;
                cout << setw(5 - 1) << " "
                     << "3. Afisati toate pisele care incep cu o anumita litera" << endl;
                cout << setw(5 - 1) << " "
                     << "4. Afisati toate piesele care au loc dupa o anumita ora" << endl;
                cout << setw(5 - 1) << " "
                     << "5. Modificarea datelor" << endl;
                cout << setw(5 - 1) << " "
                     << "0. Inapoi"
                     << "\n\n";

                fillLinieConsola(90);

                cout << setw(5 - 1) << " "
                     << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
                cin >> Meniu_2;

                switch (Meniu_2)
                {

                case 1:
                {
                    unsigned int Meniu_Cautare;

                    do
                    {
                        system("CLS");
                        afisare_piese();
                        bool valid = false;
                        cout << setw(5 - 1) << " "
                             << "Cum doriti sa cautati piesa dorita?"
                             << "\n\n";

                        cout << setw(5) << " "
                             << "1. Dupa numele piesei" << endl;
                        cout << setw(5) << " "
                             << "2. Dupa ID-ul piesei" << endl;
                        cout << setw(5) << " "
                             << "3. Dupa ora la care are loc piesa" << endl;
                        cout << setw(5) << " "
                             << "4. Dupa data in care are loc piesa" << endl;
                        cout << setw(5) << " "
                             << "5. Dupa regizorul piesei" << endl;
                        cout << setw(5) << " "
                             << "6. Dupa un anumit actor " << endl;
                        cout << setw(5) << " "
                             << "0. Inapoi"
                             << "\n\n";

                        cout << setw(5 - 1) << " "
                             << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
                        cin >> Meniu_Cautare;

                        switch (Meniu_Cautare)
                        {
                        case 1:
                        {
                            cautare_piesa_nume();
                        }
                        break;
                        case 2:
                        {
                            cautare_piesa_ID();
                        }
                        break;
                        case 3:
                        {
                            cautare_piesa_ora();
                        }
                        break;
                        case 4:
                        {
                            cautare_piesa_data();
                        }
                        break;
                        case 5:
                        {
                            cautare_piesa_regizor();
                        }
                        break;
                        case 6:
                        {
                            cautare_piesa_actor();
                        }
                        break;
                        }
                    }
                    while (Meniu_Cautare != 0);
                    system("CLS");
                }
                break;

                case 2:
                {
                    cautare_Piesa_ID_Actori();
                }
                break;

                _getch();
                break;

                case 3:
                {
                    afisare_prima_litera();
                }
                break;

                case 4:
                {
                    piese_dupa_ora();
                }
                break;

                case 5:
                {
                    unsigned int Meniu_Mod_Date_Piesa;

                    do
                    {
                        system("CLS");
                        afisare_piese();
                        cout << '\n';
                        cout << setw(5 - 1) << " "
                             << "MODIFICAREA DATELOR"
                             << "\n\n";
                        cout << setw(6) << " "
                             << "1. Adauga piese" << '\n';
                        cout << setw(6) << " "
                             << "2. Sterge piese" << '\n';
                        cout << setw(6) << " "
                             << "0. Inapoi"
                             << "\n\n";

                        cout << setw(5 - 1) << " "
                             << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
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
            unsigned int Meniu_Sali;

            do
            {
                system("CLS");
                afisare_sali();
                cout << '\n';
                cout << setw(6) << " "
                     << "1. Afisarea pieselor ca se joaca intr-o anumita sala" << '\n';
                cout << setw(6) << " "
                     << "2. Afisarea primelor 3 cele mai incapatoare sali din teatru" << '\n';
                cout << setw(6) << " "
                     << "3. Modificare date" << '\n';
                cout << setw(6) << " "
                     << "0. Inapoi"
                     << "\n\n";

                cout << setw(5 - 1) << " "
                     << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
                cin >> Meniu_Sali;

                switch (Meniu_Sali)
                {
                case 1:
                    sali_cu_piesa();
                    break;
                case 2:
                    cele_mai_mari_3_sali();
                    break;
                case 3:
                {
                    unsigned int Meniu_Mod_Sali;

                    do
                    {
                        system("CLS");
                        afisare_sali();
                        cout << '\n';
                        cout << setw(5 - 1) << " "
                             << "MODIFICAREA DATELOR"
                             << "\n\n";
                        cout << setw(6) << " "
                             << "1. Adauga sali" << '\n';
                        cout << setw(6) << " "
                             << "2. Sterge sali" << '\n';
                        cout << setw(6) << " "
                             << "0. Inapoi"
                             << "\n\n";

                        cout << setw(5 - 1) << " "
                             << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
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
                }
            }
            while (Meniu_Sali != 0);
        }
        break;
        case 3:
        {
            unsigned int Meniu_Bilet;

            do
            {
                system("CLS");
                afisare_bilete();

                cout << '\n';
                cout << setw(6) << " "
                     << "1. Afisarea biletelor in functie de pret" << '\n';
                cout << setw(6) << " "
                     << "2. Numarul biletelor vandute pentru fiecare piesa" << '\n';
                cout << setw(6) << " "
                     << "3. Numarul biletelor nevandute pentru piesele din trecut" << '\n';
                cout << setw(6) << " "
                     << "4. Modificarea datelor" << '\n';
                cout << setw(6) << " "
                     << "0. Inapoi"
                     << "\n\n";

                cout << setw(5 - 1) << " "
                     << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
                cin >> Meniu_Bilet;

                switch (Meniu_Bilet)
                {
                case 1:
                    bilete_ieftine();
                    break;
                case 2:
                    bilete_pe_piesa();
                    break;
                case 3:
                    bilete_nevandute();
                    break;
                case 4:
                {
                    unsigned int Meniu_Mod_Bilet;

                    do
                    {
                        system("CLS");
                        afisare_bilete();

                        cout << '\n';
                        cout << setw(5 - 1) << " "
                             << "MODIFICAREA DATELOR"
                             << "\n\n";
                        cout << setw(6) << " "
                             << "1. Adauga tip de bilet" << '\n';
                        cout << setw(6) << " "
                             << "2. Sterge tip de bilet" << '\n';
                        cout << setw(6) << " "
                             << "0. Inapoi"
                             << "\n\n";

                        cout << setw(5 - 1) << " "
                             << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
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
                _getch();
                break;
                }
            }
            while (Meniu_Bilet != 0);
        }
        break;
        case 4:
        {
            unsigned int Meniu_Actori;

            do
            {
                system("CLS");
                afisare_actori();

                cout << '\n';
                cout << setw(6) << " "
                     << "1. Cautare actori" << '\n';
                cout << setw(6) << " "
                     << "2. Modificarea datelor" << '\n';
                cout << setw(6) << " "
                     << "0. Inapoi"
                     << "\n\n";

                cout << setw(5 - 1) << " "
                     << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
                cin >> Meniu_Actori;

                switch (Meniu_Actori)
                {
                case 1:
                {
                    unsigned int Meniu_Cautare_Actori;

                    do
                    {
                        system("CLS");

                        cout << '\n';
                        cout << setw(6) << " "
                             << "1. Cautare actori" << '\n';
                        cout << setw(6) << " "
                             << "2. Afisarea tuturor actorilor dupa o anumita varsta" << '\n';
                        cout << setw(6) << " "
                             << "3. Afisarea tuturor actorilor inainte de o anumita varsta" << '\n';
                        cout << setw(6) << " "
                             << "4. Sortarea actorilor dupa sex" << '\n';
                        cout << setw(6) << " "
                             << "0. Inapoi"
                             << "\n\n";

                        cout << setw(5 - 1) << " "
                             << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
                        cin >> Meniu_Cautare_Actori;

                        switch (Meniu_Cautare_Actori)
                        {
                        case 1:
                            cautare_actori_nume();
                            break;
                        case 2:
                            varsta_mai_mare_actori();
                            break;
                        case 3:
                            varsta_mai_mica_actori();
                            break;
                        case 4:
                            gen_actori();
                            break;
                        }
                    }
                    while (Meniu_Cautare_Actori != 0);
                }
                break;
                case 2:
                {
                    unsigned int Meniu_Mod_Actori;

                    do
                    {
                        system("CLS");

                        cout << '\n';
                        cout << setw(5 - 1) << " "
                             << "MODIFICAREA DATELOR"
                             << "\n\n";
                        cout << setw(6) << " "
                             << "1. Adauga actori" << '\n';
                        cout << setw(6) << " "
                             << "2. Sterge actori" << '\n';
                        cout << setw(6) << " "
                             << "0. Inapoi"
                             << "\n\n";

                        cout << setw(5 - 1) << " "
                             << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
                        cin >> Meniu_Mod_Actori;

                        switch (Meniu_Mod_Actori)
                        {
                        case 1:
                            Adaugare_Actori();
                            break;
                        case 2:
                            Stergere_Actori();
                            break;
                        }
                    }
                    while (Meniu_Mod_Actori != 0);
                }
                break;
                }
            }
            while (Meniu_Actori != 0);
        }
        break;
        case 5:
        {
            unsigned int Meniu_Personal;

            do
            {
                system("CLS");
                afisare_personal();

                cout << '\n';
                cout << setw(6) << " "
                     << "1. Sortare personal teatru" << '\n';
                cout << setw(6) << " "
                     << "2. Modificare date" << '\n';
                cout << setw(6) << " "
                     << "0. Inapoi"
                     << "\n\n";

                cout << setw(5 - 1) << " "
                     << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
                cin >> Meniu_Personal;

                switch (Meniu_Personal)
                {
                case 1:
                {

                    unsigned int Meniu_Cautare_Personal;

                    do
                    {

                        system("CLS");
                        afisare_personal();

                        cout << '\n';
                        cout << setw(6) << " "
                             << "1. Afisarea personalului teatrului dupa functie" << '\n';
                        cout << setw(6) << " "
                             << "2. Afisarea tuturor actorilor dupa o anumita varsta" << '\n';
                        cout << setw(6) << " "
                             << "3. Afisarea tuturor actorilor inainte de o anumita varsta" << '\n';
                        cout << setw(6) << " "
                             << "0. Inapoi"
                             << "\n\n";

                        cout << setw(5 - 1) << " "
                             << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
                        cin >> Meniu_Cautare_Personal;

                        switch (Meniu_Cautare_Personal)
                        {
                        case 1:
                            ocupatie_personal();
                            break;
                        case 2:
                            varsta_mai_mare_personal();
                            break;
                        case 3:
                            varsta_mai_mica_personal();
                            break;
                        }
                    }
                    while (Meniu_Cautare_Personal != 0);
                }
                break;
                case 2:
                {
                    unsigned int Meniu_Mod_Personal;

                    do
                    {
                        system("CLS");
                        afisare_personal();

                        cout << '\n';
                        cout << setw(5 - 1) << " "
                             << "MODIFICAREA DATELOR"
                             << "\n\n";
                        cout << setw(6) << " "
                             << "1. Adauga personal teatru" << '\n';
                        cout << setw(6) << " "
                             << "2. Sterge personal teatru" << '\n';
                        cout << setw(6) << " "
                             << "0. Inapoi"
                             << "\n\n";

                        cout << setw(5 - 1) << " "
                             << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
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
            while (Meniu_Personal != 0);


        }
        break;
        case 6:
        {
            unsigned int Meniu_sortari;

            do
            {
                system("CLS");
                afisare_piese_vechi();

                cout << setw(5 - 1) << " " << "1. Sorteaza piesele vechi alfabetic A-Z" << endl;
                cout << setw(5 - 1) << " " << "2. Sorteaza piesele vechi alfabetic Z-A" << endl;
                cout << setw(5 - 1) << " " << "3. Sorteaza piesele vechi in functie de data in care au fost jucate" << endl;
                cout << setw(5 - 1) << " "
                     << "4. Top 5 cele mai frecventate piese din trecut" << endl;
                cout << setw(5 - 1) << " " << "0. Inapoi" << "\n\n";

                cout << setw(5 - 1) << " "
                     << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
                cin >> Meniu_sortari;
                switch (Meniu_sortari)
                {
                case 1:
                {
                    sortari_istoricPiese_alfabeti_A_Z();
                }
                _getch();
                break;

                case 2:
                {
                    sortari_istoricPiese_alfabeti_Z_A();
                }
                _getch();
                break;

                case 3:
                {
                    sortari_istoricPiese_data();
                }
                _getch();
                break;

                case 4:
                    top5_piese();
                    _getch();
                    break;
                }
            }
            while (Meniu_sortari != 0);
        }
        break;
        case 7:
        {
            Venituri();

            unsigned int Meniu_Venituri;

            do
            {
                bool valid = false;
                system("CLS");
                afisare_venituri();

                cout << setw(5 - 1) << " " << "1. Sorteaza veniturile in ordine crescatoare in functie de suma acumulata" << endl;
                cout << setw(5 - 1) << " " << "2. Sorteaza veniturile in ordine descrescatoare in functie de suma acumulata" << endl;
                cout << setw(5 - 1) << " " << "3. Afiseaza veniturile pieselor dupa o anumita data" << endl;
                cout << setw(5 - 1) << " " << "4. Reseteaza afisarea veniturilor" << endl;
                cout << setw(5 - 1) << " " << "0. Inapoi" << "\n\n";

                cout << setw(5 - 1) << " "
                     << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";

                valid = false;
                while (!valid)
                {
                    cin >> Meniu_Venituri;
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore();
                        cout << '\n';
                        cerr << setw(5 - 1) << " "
                             << "Valoarea introdusa este invalida!" << endl;
                        Sleep(1500);
                        break;
                    }
                    else
                        valid = true;
                }

                switch (Meniu_Venituri)
                {
                case 1:
                {
                    sortare_venituri_crescator_sumaAcumulata();
                }
                break;
                case 2:
                {
                    sortare_venituri_descrescator_sumaAcumulata();
                }
                break;
                case 3:
                {
                    sortare_venituri_data();
                }
                _getch();
                break;
                case 4:
                {
                    resetare_afisare_venituri();
                }
                break;
                }
            }
            while (Meniu_Venituri != 0);
        }
        break;
        }
    }
    while (Meniu_1 != 0);

    return 0;
}
