#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "Exceptie.h"
#include "Retetar.h"

using namespace std;

class Preparat final {
private:
	char* denumire;
	int gramaj;
	Retetar reteta;
	bool disponibil;
	const int MAX_SIZE;

public:
	Preparat() : MAX_SIZE(50) {

	}

	Preparat(int max_size, const char* denumire, int gramaj, const Retetar reteta, bool disponibil) : MAX_SIZE(max_size), reteta(reteta) {
		this->denumire = new char[MAX_SIZE + 1];
		strcpy(this->denumire, denumire);
		this->gramaj = gramaj;
		this->disponibil =  disponibil;
	}

	Preparat(const Preparat& p) : MAX_SIZE(p.MAX_SIZE), reteta(p.reteta) {
		this->denumire = new char[MAX_SIZE + 1];
		strcpy(this->denumire, p.denumire);
		this->gramaj = p.gramaj;
		this->disponibil = p.disponibil;
	}

	void setDenumire(char* denumire) {
		try {
			if (strlen(denumire) > MAX_SIZE)
			{
				throw Exceptie("Denumirea produsului nu poate fi mai mare decat maximul sirului de caractere specificat");
			}
			this->denumire = new char[MAX_SIZE + 1];
			strcpy(this->denumire, denumire);
		}
		catch (Exceptie ex) {
			cerr << ex.what();
			return;
		}
	}

	void setGramaj(int gramaj) {
		try {
			if (gramaj < 0)
			{
				throw Exceptie("Gramajul nu poate fi < 0");
			}this->gramaj = gramaj;
		}
		catch(Exceptie ex) {
			cerr << ex.what();
			return;
		}
	}

	void setReteta(Retetar& reteta) {
		this->reteta = reteta;
	}

	void setDisponibil(bool disponibil) {
		this->disponibil = disponibil;
	}

	char* getDenumire() {
		char* copie = new char[MAX_SIZE + 1];
		strcpy(copie, denumire);
		return copie;
	}

	int getGramaj() {
		return gramaj;
	}

	Retetar& getReteta() {
		return reteta;
	}

	bool getDisponibil() {
		return disponibil;
	}

	Preparat& operator=(Preparat& p) {
		this->denumire = new char[MAX_SIZE + 1];
		strcpy(this->denumire, p.getDenumire());
		this->gramaj = p.getGramaj();
		this->reteta = p.getReteta();
		this->disponibil = p.getDisponibil();
		return *this;
	}

	friend ostream& operator<<(ostream& os, Preparat& p) {
		os << "Denumire preparat: " << p.getDenumire();
		os << "\nGramaj: " << p.getGramaj();
		os << "\nEste disponibil: " << p.getDisponibil() ? "Da" : "Nu";
		os << "\nReteta: \n\t" << p.reteta;
		return os;
	}

	friend istream& operator>>(istream& is, Preparat& p) {
		string denumire;
		is >> denumire;
		p.setDenumire(const_cast<char*>(denumire.c_str()));

		int gramaj;
		is >> gramaj;
		p.setGramaj(gramaj);

		bool disp;
		is >> disp;
		p.setDisponibil(disp);

		Retetar r(p.getReteta());
		is >> r;
		p.setReteta(r);

		return is;
	}

	friend bool operator!(Preparat& p) {
		return !p.getDisponibil();
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

	~Preparat() {
		delete[] denumire;
	}
};
