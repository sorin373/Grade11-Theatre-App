#include <iostream> // cin / cout
#include <fstream>  // input din fisier
#include <cstring>  // string-uri
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

using namespace std;

struct sala
{
    int id;
    int nr_sc;
    int nr_scloja;
} sl[6];

struct actor
{
    int id;
    char nume[21];
    char prenume[21];
    int varsta;
    char email[31];
    int cnp;
} a[35];

struct piesa
{
    int id;
    int id_sala;
    char nume[21];
    char data[11];
    char ora[6];
} p[22];

struct personaj_piesa
{
    char nume[31];
    int id_piesa;
    int id_actor;
} prs[100];

struct bilet
{
    int id;
    float pret;
    char tip[41];
} b[6];

struct personal
{
    int id;
    int id_sala;
    char nume[21];
    char prenume[21];
    int cnp;
    int varsta;
    char functie[31];
} pr[100];

struct spectator
{
    int id;
    int id_bilet;
    int id_piesa;
} sp[207];

int nra = 1, nrp = 1, nrb = 1, nrsl = 1, nrpr = 1, nrsp = 1, nrprs = 1;

ifstream fisierSala("sala.txt");                //fisier sali teatru
ifstream fisierActor("actor.txt");              //fisier actori care joaca in piesele de teatru
ifstream fisierPiesa("piesa.txt");              //fisier cu piesele care urmeaza sa fie jucate in urmatoarea saptamana
ifstream fisierPersonaj("personaj.txt");        //fisier cu personajele din fiecare piesa de teatru
ifstream fisierBilet("bilet.txt");              //fisier cu tipurile de bilete disponibile la teatru
ifstream fisierPersonalTeatru("personal.txt");  //fisier cu personalul care lucreaza in incinta teatrului
ifstream fisierSpectator("spectator.txt");      //fisier cu spectatorii care si-au rezervat loc la fiecare piesa de teatru

void citire_sali()
{
    while (fisierSala >> sl[nrsl].id >> sl[nrsl].nr_sc >> sl[nrsl].nr_scloja)
        nrsl++;
    nrsl--;
}
void citire_actori()
{
    while (fisierActor >> a[nra].id >> a[nra].nume >> a[nra].prenume >> a[nra].varsta >> a[nra].email >> a[nra].cnp)
        nra++;
    nra--;
}
void citire_piese()
{
    while (fisierPiesa >> p[nrp].id >> p[nrp].id_sala >> p[nrp].nume >> p[nrp].data >> p[nrp].ora)
        nrp++;
    nrp--;
}
void citire_personaje_piese()
{
    while (fisierPersonaj >> prs[nrprs].nume >> prs[nrprs].id_piesa >> prs[nrprs].id_actor)
        nrprs++;
    nrprs--;
}
void citire_bilete()
{
    while (fisierBilet >> b[nrb].id >> b[nrb].pret >> b[nrb].tip)
        nrb++;
    nrb--;
}
void citire_personal()
{
    while (fisierPersonalTeatru >> pr[nrpr].id >> pr[nrpr].id_sala >> pr[nrpr].nume >> pr[nrpr].prenume >> pr[nrpr].cnp >> pr[nrpr].varsta >> pr[nrpr].functie)
        nrpr++;
    nrpr--;
}
void citire_spectatori()
{
    while (fisierSpectator >> sp[nrsp].id >> sp[nrsp].id_bilet >> sp[nrsp].id_piesa)
        nrsp++;
    nrsp--;
}
void afisare_piese()
{
    for (int i = 1; i <= nrp; i++)
        cout << p[i].nume << endl;
}
void afisare_sali()
{
    for (int i = 1; i <= nrsl; i++)
        cout << "Sala " << sl[i].id << ": " << sl[i].nr_sc << " scaune normale " << sl[i].nr_scloja << " scaune in loja" << endl;
}
void afisare_bilete()
{
    for (int i = 1; i <= nrb; i++)
        cout << b[i].id << ": " << b[i].tip << ", " << b[i].pret << endl;
}
void afisare_actori()
{
    for (int i = 1; i <= nra; i++)
        cout << a[i].nume << endl;
}
void afisare_personal()
{
    for (int i = 1; i <= nrpr; i++)
        cout << pr[i].nume << endl;
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
        cout << "1. Piesele viitoare" << endl;
        cout << "2. Sali" << endl;
        cout << "3. Bilete" << endl;
        cout << "4. Actori" << endl;
        cout << "5. Personal" << endl;
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
                afisare_piese();
                cout << "1. Detalii piesa" << endl;
                cout << "2. Personaje piesa" << endl;
                cout << "3. Bani" << endl;
                cout << "0. Intoarcere" << endl
                     << endl;
                cout << "Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
                cin >> t2;
                switch (t2)
                {
                case 1:
                {
                    char numep[21];
                    cout << endl
                         << "Tasteaza numele piesei: ";
                    cin.get();
                    cin.get(numep, 21);
                    cout << endl;
                    int ok = 0;
                    for (int i = 1; i <= nrp && ok == 0; i++)
                        if (strcmp(p[i].nume, numep) == 0)
                        {
                            cout << p[i].id << endl;
                            cout << p[i].nume << endl;
                            cout << p[i].id_sala << endl;
                            cout << p[i].data << endl;
                            cout << p[i].ora << endl;
                            ok = 1;
                        }
                }
                    _getch();
                    break;
                case 2:
                {
                    char numep[21];
                    cout << endl
                         << "Tasteaza numele piesei: ";
                    cin.get();
                    cin.get(numep, 21);
                    cout << endl;
                    int ok = 0;
                    for (int i = 1; i <= nrp && ok == 0; i++)
                        if (strcmp(p[i].nume, numep) == 0)
                        {
                            for (int j = 1; j <= nrprs; j++)
                                if (prs[j].id_piesa == p[i].id)
                                {
                                    cout << prs[j].nume;
                                    int k = 1;
                                    while (a[k].id != prs[j].id_actor)
                                        k++;
                                    cout << " (jucat de " << a[k].nume << ")" << endl;
                                }
                            ok = 1;
                        }
                }
                    _getch();
                    break;
                case 3:
                {
                    char numep[21];
                    cout << endl
                         << "Tasteaza numele piesei: ";
                    cin.get();
                    cin.get(numep, 21);
                    cout << endl;
                    int ok = 0, v = 0;
                    for (int i = 1; i <= nrp && ok == 0; i++)
                        if (strcmp(p[i].nume, numep) == 0)
                        {
                            for (int j = 1; j <= nrsp; j++)
                                if (sp[j].id_piesa == p[i].id)
                                    v = v + b[p[i].id].pret;
                            ok = 1;
                        }
                    cout << "Biletele cumparate pentru aceasta piesa alcatuiesc " << v << " lei" << endl;
                }
                    getch();
                    break;
                }
            } while (t2 != 0);
        }
        case 2:
        {
            afisare_sali();
            /*int t2;
            do
            {
                system("CLS");
                cout<<"1. "<<endl;
                cout<<"0. Intoarcere"<<endl<<endl;
                cout<<"Tastati numarul respectiv sectiunii pe care doriti sa o accesati: ";
                cin>>t2;
                switch(t2)
                {
                    case 1:{
                           } _getch(); break;
                }
            }while(t2!=0);*/
        }
            getch();
            break;
        case 3:
        {
            afisare_bilete();
        }
            getch();
            break;
        case 4:
        {
            afisare_actori();
        }
            getch();
            break;
        case 5:
        {
            afisare_personal();
        }
            getch();
            break;
        }
    } while (t1 != 0);

    fisierSala.close();
    fisierActor.close();
    fisierPiesa.close();
    fisierPersonaj.close();
    fisierBilet.close();
    fisierPersonalTeatru.close();
    fisierSpectator.close();

    return 0;
}
