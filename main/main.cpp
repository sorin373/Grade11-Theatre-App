#include <iostream> // cin / cout
#include <fstream>  // input din fisier
#include <cstring>  // string-uri
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

using namespace std;

struct sala
{
    /*int id;
    int Nr_Scaune;
    int Nr_Scaune_Loja;*/
    unsigned int ID_Sala;
    unsigned int Nr_Scaune;
    unsigned int Nr_Scaune_Loja;
} salaTeatru[11];

struct actor
{
    /*int id;
    char nume[21];
    char prenume[21];
    int varsta;
    char email[31];
    int cnp;*/
    unsigned int ID_Actor;
    char Nume_Actor[101];
    char Prenume_Actor[101];
    unsigned int Varsta_Actor;
    char Email_Actor[101];
    long long unsigned int CNP_Actor;
} actorTeatru[35];

struct piesa
{
    /*int id;
    int id_sala;
    char nume[41];
    char data[11];
    char ora[6];*/
    unsigned int ID_Piesa;
    unsigned int ID_Sala;
    char Nume_Piesa[101];
    char Data_Piesa[11];
    char Ora_Piesa[6];
} piesaTeatru[201];

struct personaj_piesa
{
    /*char nume[100];
    int id_piesa;
    int id_actor;*/
    unsigned int ID_Piesa;
    unsigned int ID_Actor;
    char Nume_Personaj[101];
} personajPiesa[401];

struct bilet
{
    /*int id;
    float pret;
    char tip[41];*/
    unsigned int ID_Bilet;
    float Pret_Bilet;
    char Tip_Bilet[41];
} biletPiesa[6];

struct personal
{
    /*int id;
    char nume[21];
    char prenume[21];
    char cnp[15];
    int varsta;
    char functie[31];*/
    unsigned int ID_PersonalTeatru;
    char Nume_PersonalTeatru[101];
    char Prenume_PersonalTeatru[101];
    char CNP_PersonalTeatru[15];
    unsigned int Varsta_PersonalTeatru;
    char Functie_PersonalTeatru[101];

} personalTeatru[101];

struct spectator
{
    /*int id;
    int id_bilet;
    int id_piesa*/
    unsigned int ID_Spectator;
    unsigned int ID_Bilet;
    unsigned int ID_Piesa;
} spectatorPiesa[401];

unsigned int nra = 1, nrp = 1, nrb = 1, nrsl = 1, nrpr = 1, nrsp = 1, nrprs = 1;

//Citire date din fisierele corespunzatoare
void citire_sali()
{
    ifstream fisierSala("sala.txt");               // fisier sali teatru
    while (fisierSala >> salaTeatru[nrsl].ID_Sala >> salaTeatru[nrsl].Nr_Scaune >> salaTeatru[nrsl].Nr_Scaune_Loja)
        nrsl++;
    nrsl--;
    fisierSala.close();
}

void citire_actori()
{
    ifstream fisierActor("actor.txt");             // fisier actori care joaca in piesele de teatru
    while (fisierActor >> actorTeatru[nra].ID_Actor >> actorTeatru[nra].Nume_Actor >> actorTeatru[nra].Prenume_Actor
        >> actorTeatru[nra].Varsta_Actor >> actorTeatru[nra].Email_Actor >> actorTeatru[nra].CNP_Actor)
        nra++;
    nra--;
    fisierActor.close();
}

void citire_piese()
{
    ifstream fisierPiesa("piesa.txt");             // fisier cu piesele care urmeaza sa fie jucate in urmatoarea saptamana
    while (fisierPiesa >> piesaTeatru[nrp].ID_Piesa >> piesaTeatru[nrp].Nume_Piesa >> piesaTeatru[nrp].ID_Sala >> piesaTeatru[nrp].Data_Piesa >> piesaTeatru[nrp].Ora_Piesa)
        nrp++;
    nrp--;
    fisierPiesa.close();
}

void citire_personaje_piese()
{
    ifstream fisierPersonaj("personaj.txt");       // fisier cu personajele din fiecare piesa de teatru
    while (fisierPersonaj >> personajPiesa[nrprs].ID_Piesa >> personajPiesa[nrprs].ID_Actor >> personajPiesa[nrprs].Nume_Personaj)
        nrprs++;
    nrprs--;
    fisierPersonaj.close();
}

void citire_bilete()
{
    ifstream fisierBilet("bilet.txt");             // fisier cu tipurile de bilete disponibile la teatru
    while (fisierBilet >> biletPiesa[nrb].ID_Bilet >> biletPiesa[nrb].Tip_Bilet >> biletPiesa[nrb].Pret_Bilet)
        nrb++;
    nrb--;
    fisierBilet.close();
}

void citire_personal()
{
    ifstream fisierPersonalTeatru("personal.txt"); // fisier cu personalul care lucreaza in incinta teatrului
    while (fisierPersonalTeatru >> personalTeatru[nrpr].ID_PersonalTeatru >> personalTeatru[nrpr].Functie_PersonalTeatru >> personalTeatru[nrpr].Nume_PersonalTeatru
            >> personalTeatru[nrpr].Prenume_PersonalTeatru >> personalTeatru[nrpr].CNP_PersonalTeatru >> personalTeatru[nrpr].Varsta_PersonalTeatru)
        nrpr++;
    nrpr--;
    fisierPersonalTeatru.close();
}

void citire_spectatori()
{
    ifstream fisierSpectator("spectator.txt");     // fisier cu spectatorii care si-au rezervat loc la fiecare piesa de teatru
    while (fisierSpectator >> spectatorPiesa[nrsp].ID_Spectator >> spectatorPiesa[nrsp].ID_Bilet >> spectatorPiesa[nrsp].ID_Piesa)
        nrsp++;
    nrsp--;
    fisierSpectator.close();
}

//Afisare date
void afisare_piese()
{
    cout << "ID "
         << " Nume "
         << " Data " << endl;
    for (int i = 1; i <= nrp; i++)
        cout << piesaTeatru[i].ID_Piesa << " " << piesaTeatru[i].Nume_Piesa << " " << piesaTeatru[i].Data_Piesa << endl;
}

void afisare_sali()
{
    for (int i = 1; i <= nrsl; i++)
        cout << "Sala " << salaTeatru[i].ID_Sala << ": " << salaTeatru[i].Nr_Scaune << " scaune normale " << salaTeatru[i].Nr_Scaune_Loja << " scaune in loja" << endl;
}

void afisare_bilete()
{
    for (int i = 1; i <= nrb; i++)
        cout << biletPiesa[i].ID_Bilet << ": " << biletPiesa[i].Tip_Bilet << ", " << biletPiesa[i].Pret_Bilet << endl;
}

void afisare_actori()
{
    for (int i = 1; i <= nra; i++)
        cout << actorTeatru[i].Nume_Actor << endl;
}

void afisare_personal()
{
    for (int i = 1; i <= nrpr; i++)
        cout << personalTeatru[i].Nume_PersonalTeatru << endl;
}

int main()
{
    int t1;
    citire_sali();
    citire_actori();
    citire_piese();
    citire_personaje_piese();
    citire_bilete();
    citire_personal();
    citire_spectatori();
    do
    {
        system("CLS");
        cout << "MENIU" << endl;
        cout << "1. Piesele ce urmeaza sa fie jucate in perioasa 10.07 - 17.07.2022." << endl;
        cout << "2. Sali de teatru." << endl;
        cout << "3. Tipurile de bilete disponibile la vanzare." << endl;
        cout << "4. Actorii care joaca in piesele de teatru." << endl;
        cout << "5. Personalul teatrului." << endl;
        cout << "0. Iesire" << endl
             << endl;
        cout << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
        cin >> t1;
        switch (t1)
        {
        case 1:
        {
            int t2;
            do
            {
                system("CLS");
                afisare_piese(); cout << endl;
                cout << "1. Detalii desre piesele de teatru." << endl;
                cout << "2. Personajele care joaca in piesele de teatru si actorii corespunzatori acestora." << endl;
                cout << "3. Profit si cheltuieli." << endl;
                cout << "0. Inapoi." << endl
                     << endl;
                cout << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
                cin >> t2;
                switch (t2)
                {
                case 1:
                {
                    int idp;
                    cout << endl
                         << "Tasteaza ID-ul piesei: ";
                    cin >> idp;
                    cout << endl;
                    int ok = 0;
                    for (int i = 1; i <= nrp && ok == 0; i++)
                        if (piesaTeatru[i].ID_Piesa == idp)
                        {
                            cout << "ID: " << piesaTeatru[i].ID_Piesa << endl;
                            cout << "Nume: " << piesaTeatru[i].Nume_Piesa << endl;
                            cout << "Sala: " << piesaTeatru[i].ID_Sala << endl;
                            cout << "Data: " << piesaTeatru[i].Data_Piesa << endl;
                            cout << "Ora: " << piesaTeatru[i].Ora_Piesa << endl;
                            ok = 1;
                        }
                }
                    _getch();
                    break;
                case 2:
                {
                    int idp;
                    cout << endl
                         << "Tasteaza ID-ul piesei: ";
                    cin >> idp;
                    cout << endl;
                    int ok = 0;
                    for (int i = 1; i <= nrp && ok == 0; i++)
                        if (piesaTeatru[i].ID_Piesa == idp)
                        {
                            for (int j = 1; j <= nrprs; j++)
                                if (personajPiesa[j].ID_Piesa == piesaTeatru[i].ID_Piesa)
                                {
                                    cout << personajPiesa[j].Nume_Personaj;
                                    int k = 1;
                                    while (actorTeatru[k].ID_Actor != personajPiesa[j].ID_Actor)
                                        k++;
                                    cout << " (jucat de " << actorTeatru[k].Nume_Actor << ")" << endl;
                                }
                            ok = 1;
                        }
                }
                    _getch();
                    break;
                case 3:
                {
                    int idp;
                    cout << endl
                         << "Tasteaza ID-ul piesei: ";
                    cin >> idp;
                    cout << endl;
                    int ok = 0, v = 0;
                    for (int i = 1; i <= nrp && ok == 0; i++)
                        if (piesaTeatru[i].ID_Piesa == idp)
                        {
                            for (int j = 1; j <= nrsp; j++)
                                if (spectatorPiesa[j].ID_Piesa == piesaTeatru[i].ID_Piesa)
                                    v = v + biletPiesa[piesaTeatru[i].ID_Piesa].Pret_Bilet;
                            ok = 1;
                        }
                    cout << "Biletele cumparate pentru aceasta piesa alcatuiesc " << v << " lei" << endl;
                }
                    _getch();
                    break;
                }
            } while (t2 != 0);
        }
        break;
        case 2:
        {
            //  afisare_sali();
            /*int t2;
            do
            {
                system("CLS");
                cout<<"1. "<<endl;
                cout<<"0. Inapoi"<<endl<<endl;
                cout<<"Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
                cin>>t2;
                switch(t2)
                {
                    case 1:{
                           } _getch(); break;
                }
            }while(t2!=0);*/
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
    } while (t1 != 0);

    return 0;
}
