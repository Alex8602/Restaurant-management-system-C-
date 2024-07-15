#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "Exceptie.h"
#include "Preparat.h"

using namespace std;


class Comanda final {
private:
	char* dataora;  // ca YYYY-mm-dd hh:mm:ss (max 21 char)
	vector<Preparat> preparate;

public:
	Comanda(const char* dataora, vector<Preparat> preparate) {
		this->dataora = new char[21];
		strcpy(this->dataora, dataora);
		for (int i = 0; i < preparate.size(); i++)
		{
			this->preparate.push_back(preparate[i]);
		}
	}

	Comanda(const Comanda& c) {
		this->dataora = new char[21];
		strcpy(this->dataora, c.dataora);
		for (int i = 0; i < c.preparate.size(); i++)
		{
			this->preparate.push_back(c.preparate[i]);
		}
	}

	void setDataora(char* dataora) {
		try {
			if (strlen(dataora) > 20)
			{
				throw Exceptie("Sirul de caractere de data-ora nu tb sa fie mai mare de 20");
			}
			this->dataora = new char[21];
			strcpy(this->dataora, dataora);
		}
		catch (Exceptie ex) {
			cerr << ex.what();
			return;
		}
	}

	void setPreparate(vector<Preparat> preparate) {
		preparate.clear();
		for (int i = 0; i < preparate.size(); i++)
		{
			this->preparate.push_back(preparate[i]);
		}
	}

	char* getDataora() {
		char* copie = new char[21];
		strcpy(copie, dataora);
		return copie;
	}

	vector<Preparat> getPreparate() {
		vector<Preparat> copie;
		for (int i = 0; i < preparate.size(); i++)
		{
			copie.push_back(preparate[i]);
		}
		return copie;
	}

	Comanda& operator=(Comanda& c) {
		this->dataora = new char[21];
		strcpy(this->dataora, c.dataora);
		this->preparate.clear();
		for (int i = 0; i < c.preparate.size(); i++)
		{
			this->preparate.push_back(c.preparate[i]);
		}
		return *this;
	}

	friend ostream& operator<<(ostream& os, Comanda& c) {
		os << "Data si ora comenzii: " << c.getDataora();
		os << "\nProdusele comandate: ";
		for (int i = 0; i < c.getPreparate().size(); i++)
		{
			os << "\n\t" << c.getPreparate()[i].getDenumire();
		}
		return os;
	}

	friend istream& operator>>(istream& is, Comanda& c) {
		string dataora;
		is >> dataora;
		c.setDataora(const_cast<char*>(dataora.c_str()));

		int size;
		is >> size;
		vector<Preparat> preparate(size, c.getPreparate()[0]);
		for (int i = 0; i < size; i++) {
			is >> preparate[i];
		}
		return is;
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

	~Comanda() {
		delete[] dataora;
	}

};