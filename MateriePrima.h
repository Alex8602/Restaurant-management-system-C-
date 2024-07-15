#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include "Exceptie.h"
#include "Serializable.h"

using namespace std;

class MateriePrima final : public Serializable {
private:
    static int nrMateriiPrimeUtilizate;
    const int MAX_SIZE;
    char* denumire;
    int cantitate;

public:
    MateriePrima() : MAX_SIZE(50) {
        denumire = nullptr;
        nrMateriiPrimeUtilizate++;
        cantitate = 0;
    }

    MateriePrima(int MAX_SIZE) : MAX_SIZE(MAX_SIZE) {
        nrMateriiPrimeUtilizate++;
        denumire = nullptr;
        cantitate = 0;
    }

    MateriePrima(const char* denumire, int cantitate, int MAX_SIZE) : MAX_SIZE(MAX_SIZE) {
        this->cantitate = cantitate;
        this->denumire = new char[MAX_SIZE + 1];
        strcpy(this->denumire, denumire);
        nrMateriiPrimeUtilizate++;
    }

    MateriePrima(const MateriePrima& mp) : MAX_SIZE(mp.MAX_SIZE) {
        this->cantitate = mp.cantitate;
        this->denumire = new char[MAX_SIZE + 1];
        strcpy(this->denumire, mp.denumire);
    }

    static void setNrMateriiPrimeUtilizate(int nr) {
        try {
            if (nr < 0)
            {
                throw Exceptie("Nr de materii prime nu poate fi mai mic decat 0");
            }
            nrMateriiPrimeUtilizate = nr;
        }
        catch (Exceptie ex) {
            cerr << ex.what();
            return;
        }
    }

    void setDenumire(char* denumire) {
        try {
            if (strlen(denumire) > MAX_SIZE) {
                throw Exceptie("Sirur de caractere nu poate fi mai mare decat marimea setata!");
            }
            this->denumire = new char[MAX_SIZE + 1];
            strcpy(this->denumire, denumire);
        }
        catch (Exceptie ex) {
            cerr << ex.what();
            return;
        }
    }

    void setCantitate(int cantitate) {
        try {
            if (cantitate < 0)
            {
                throw Exceptie("Cantiatea nu poate fi mai mica decat 0");
            }
            this->cantitate = cantitate;
        }
        catch (Exceptie ex) {
            cerr << ex.what();
            return;
        }
        
    }

    static int getNrMateriiPrimeUtilizate() {
        return nrMateriiPrimeUtilizate;
    }

    char* getDenumire() {
        char* copie = new char[MAX_SIZE];
        strcpy(copie, denumire);
        return copie;
    }

    int getCantitate() {
        return cantitate;
    }

    int getMaxSize() {
        return MAX_SIZE;
    }

    MateriePrima& operator=(MateriePrima& mp) {
        delete[] denumire;
        denumire = new char[MAX_SIZE + 1];
        strcpy(denumire, mp.getDenumire());
        cantitate = mp.cantitate;
        return *this;
    }

    friend ostream& operator<<(ostream& os, const MateriePrima& mp) {
        os << mp.denumire;
        os << mp.cantitate;
        os << endl;
        return os;
    }

    friend istream& operator>>(istream& is, MateriePrima& mp) {
        string denumire;
        int cantitate;
        is >> denumire;
        is >> cantitate;

        mp.setDenumire(const_cast<char*>(denumire.c_str()));
        mp.setCantitate(cantitate);
        return is;
    }

    operator string() const {
        return string(denumire);
    }

    MateriePrima& operator++() {
        cantitate++;
        return *this;
    }

    MateriePrima operator++(int) {
        MateriePrima copie = *this;
        cantitate++;
        return copie;
    }

    MateriePrima& operator--() {
        cantitate--;
        return *this;
    }

    MateriePrima operator--(int) {
        MateriePrima copie = *this;
        cantitate--;
        return copie;
    }

    friend bool operator==(MateriePrima& mp1, MateriePrima& mp2) {
        if (mp1.getMaxSize() == mp2.getMaxSize())
        {
            if (mp1.getCantitate() == mp2.getCantitate())
            {
                if (strcmp(mp1.getDenumire(), mp2.getDenumire()) == 0)
                {
                    return true;
                }
            }
        }
        return false;
    }

    void salvareBinar(const char* file) {
        ofstream output(file, ios::binary | ios::app | ios::out);
        if (!output) {
            cerr << "Eroare la scrierea fisierului binar" << endl;
            return;
        }
        output << this;
        output.close();
    }

    void read(ifstream& ifs) override {
        ifs.read(reinterpret_cast<char*>(&cantitate), sizeof(cantitate));
        char buffer[255];
        ifs.read(buffer, sizeof(buffer));
        denumire = buffer;
    }

    void write(ofstream& ofs) const override {
        ofs.write(reinterpret_cast<const char*>(&cantitate), sizeof(cantitate));
        ofs.write(denumire, strlen(denumire) + 1); 
    }

    ~MateriePrima() {
        delete[] denumire;
    }

};
