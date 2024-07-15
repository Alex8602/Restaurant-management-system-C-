#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <fstream>
#include "MateriePrima.h"
#include "Retetar.h"
#include "Preparat.h"
#include "Comanda.h"
#include <map>
#include <sstream>
#include <list>

using namespace std;

int MateriePrima::nrMateriiPrimeUtilizate = 0;

#define MAX_CHR 150

int main(int argc, const char* argv[]) {
    if (argc == 3)
    {
        fstream file_materiePrima(argv[1]);
        fstream file_preparat(argv[2]);

        vector<MateriePrima> mp_file;
        MateriePrima mp;
        while (file_materiePrima>>mp && !file_materiePrima.eof())
        {
            mp_file.push_back(mp);
        }
        file_materiePrima.close();

        Retetar rt(MAX_CHR, mp_file.size(), "...", mp_file);
        
        Preparat pr;
        file_preparat >> pr;

        file_preparat.close();

        vector<Preparat> meniu = {pr };

        vector<Preparat> preparate_pt_comenzi;
        vector<Comanda> comenzi;

        bool exit = false;
        while (exit == false)
        {

            cout << "Meniu: ";
            for (int i = 0; i < meniu.size(); i++)
            {
                cout << "[" << i + 1 << "]";
                cout << " Denumire: " << meniu[i].getDenumire();
                cout << " Gramaj: " << meniu[i].getGramaj();
                cout << endl << endl;
            }

            do {
                int nr;
                cout << "Selectati un produs (nr acestuia): ";
                do {
                    cin >> nr;
                    --nr;
                    if (nr >= meniu.size() || nr < 0)
                    {
                        cout << "\n\tNr incorect, reselectati: ";
                    }
                } while (nr >= meniu.size() || nr < 0);

                bool materii_disponibile = true;
                for (int i = 0; i < meniu[nr].getReteta().getMaterii().size(); i++)
                {
                    if (meniu[nr].getReteta()[i].getCantitate() <= 0)
                    {
                        materii_disponibile = false;
                        cout << "Din pacate nu se poate prelua comanda pentru " << meniu[nr].getDenumire() << " intrucat nu exista o materie diponibila: " << meniu[nr].getReteta().getMaterii()[i] << endl;
                        break;
                    }
                }
                if (materii_disponibile)
                {
                    preparate_pt_comenzi.push_back(meniu[nr]);
                    for (int i = 0; i < meniu[nr].getReteta().getMaterii().size(); i++)
                        meniu[nr].getReteta().getMaterii()[i]--;

                }
                cout << "\nDoriti sa mai comandati un produs? (1/0): ";
                cin >> exit;

                if (exit == false)
                {
                    comenzi.push_back(Comanda("2023-11-24 12:00:00", preparate_pt_comenzi));
                    preparate_pt_comenzi.clear();
                }

            } while (exit == true);
            cout << "Se doreste crearea unei noi comenzi? (1/0): ";
            cin >> exit;

            if (exit == false)
            {
                cout << "\nComenzile sunt: ";
                for (int i = 0; i < comenzi.size(); i++)
                {
                    cout << "\t" << comenzi[i];
                }
                cout << endl;
            }

            exit = !exit;
        }
        return 0;
      
    }

    list<MateriePrima> lista_mp;

    cout << "Incarca CSV? (1/0): ";
    int optiune = 0;
    cin >> optiune;

    if (optiune == 1)
    {
        cout << "Calea catre fisierul CSV: ";
        string path;
        cin >> path;
        
        ifstream file(path);
        if (!file.is_open())
        {
            cerr << "Eroare la deschiderea fisierului CSV\n";
        }
        else {
            string line;
            getline(file, line);

            while (getline(file, line))
            {
                istringstream ss(line);
                string denumire;
                int cantitate;
                if (getline(ss, denumire, ',') && (ss >> cantitate))
                {
                    MateriePrima mp(denumire.c_str(), cantitate, MAX_CHR);
                    lista_mp.push_back(mp);
                }
                else {
                    cerr << "Eroare la citirea din CSV\n";
                    break;
                }
            }
            file.close();
        }
    }

    MateriePrima tagliatelle("tagliatelle", 5, MAX_CHR);
    MateriePrima smantana_lichida("smantana lichida", 20, MAX_CHR);
    MateriePrima mozzarella("mozzarela", 15, MAX_CHR);
    MateriePrima parmezan("parmezan", 4, MAX_CHR);
    MateriePrima faina("faina", 13, MAX_CHR);
    MateriePrima drojdie("drojdie", 7, MAX_CHR);
    MateriePrima ulei("ulei", 10, MAX_CHR);
    MateriePrima sos_rosii("sos de rosii", 4, MAX_CHR);

    tagliatelle.salvareBinar("out");


    vector<MateriePrima> mp_tagliatelle = { tagliatelle, smantana_lichida, mozzarella, parmezan };
    vector<MateriePrima> mp_pizza = { faina, drojdie, ulei, sos_rosii, mozzarella };


    Retetar rt_tagliatelle(MAX_CHR, mp_tagliatelle.size(), "intr. de preparare...", mp_tagliatelle);
    Retetar rt_pizza_margherita(MAX_CHR, mp_pizza.size(), "instr. de preparare...", mp_pizza);


    Preparat pr_tagliatelle(MAX_CHR, "Tagliatelle", 450, rt_tagliatelle, true);
    Preparat pr_pizza(MAX_CHR, "Pizza Margherita", 500, rt_pizza_margherita, true);

    vector<Preparat> meniu = { pr_tagliatelle, pr_pizza };

    vector<Preparat> preparate_pt_comenzi;
    vector<Comanda> comenzi;

    bool exit = false;
    while (exit == false)
    {
        
        cout << "Meniu: ";
        for (int i = 0; i < meniu.size(); i++)
        {
            cout << "[" << i + 1 << "]";
            cout << " Denumire: " << meniu[i].getDenumire();
            cout << " Gramaj: " << meniu[i].getGramaj();
            cout << endl << endl;
        }
        
        do {
            int nr;
            cout << "Selectati un produs (nr acestuia): ";
            do {
                cin >> nr;
                --nr;
                if (nr >= meniu.size() || nr < 0)
                {
                    cout << "\n\tNr incorect, reselectati: ";
                }
            } while (nr >= meniu.size() || nr < 0);
           
            bool materii_disponibile = true;
            for (int i = 0; i < meniu[nr].getReteta().getMaterii().size(); i++)
            {
                if (meniu[nr].getReteta()[i].getCantitate() <= 0)
                {
                    materii_disponibile = false;
                    cout << "Din pacate nu se poate prelua comanda pentru " << meniu[nr].getDenumire() << " intrucat nu exista o materie diponibila: " << meniu[nr].getReteta().getMaterii()[i] << endl;
                    break;
                }
            }
            if (materii_disponibile)
            {
                preparate_pt_comenzi.push_back(meniu[nr]);
                for (int i = 0; i < meniu[nr].getReteta().getMaterii().size(); i++)
                    meniu[nr].getReteta().getMaterii()[i]--;

            }
            cout << "\nDoriti sa mai comandati un produs? (1/0): ";
            cin >> exit;

            if (exit == false)
            {
                comenzi.push_back(Comanda("2023-11-24 12:00:00", preparate_pt_comenzi));
                preparate_pt_comenzi.clear();
            }
            
        } while (exit == true);
        cout << "Se doreste crearea unei noi comenzi? (1/0): ";
        cin >> exit;

        if (exit == false)
        {
            cout << "\nComenzile sunt: ";
            for (int i = 0; i < comenzi.size(); i++)
            {
                cout << "\t" << comenzi[i];
            }
            cout << endl;
        }

        exit = !exit;
    }

    map<string, int> statistici;
    for (Comanda comanda : comenzi) {
        for (Preparat preparat : comanda.getPreparate()) {
            
            statistici[preparat.getDenumire()]++;
        }
    }

    cout << "Raport nr de preparate per comenzi: \n";
    for (auto index : statistici) {
        cout << "Preparatul: " << index.first << " a fost comandat de: " << index.second << " ori\n";
    }


    return 0;
}
