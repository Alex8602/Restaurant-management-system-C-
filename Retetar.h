#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include "Exceptie.h"
#include "MateriePrima.h"
#include "Serializable.h"

using namespace std;

class Retetar final : public Serializable {
private:
	vector<MateriePrima> materii;
	int nrMaterii;
	char* instructiuni;
	const int MAX_SIZE;

public:
	Retetar() : MAX_SIZE(50) {

	}

	Retetar(int max_size, int nrMaterii, const char* instructiuni, vector<MateriePrima> materii) : MAX_SIZE(max_size) {
		this->instructiuni = new char[MAX_SIZE + 1];
		strcpy(this->instructiuni, instructiuni);
		for (int i = 0; i < nrMaterii; i++) {
			this->materii.push_back(materii[i]);
		}
		this->nrMaterii = nrMaterii;
	}

	Retetar(const Retetar& rt) : MAX_SIZE(rt.MAX_SIZE) {
		this->instructiuni = new char[MAX_SIZE + 1];
		strcpy(this->instructiuni, rt.instructiuni);
		for (int i = 0; i < rt.materii.size(); i++) {
			this->materii.push_back(rt.materii[i]);
		}
		this->nrMaterii = rt.nrMaterii;
	}

	void setNrMaterii(int nr) {
		try {
			if (nr < 0)
			{
				throw Exceptie("Nr de materii nu poate fi <= 0");
			}
			this->nrMaterii = nr;
		}
		catch (Exceptie ex) {
			cerr << ex.what();
			return;
		}
	}

	void setInstructiuni(char* instructiuni) {
		try {
			if (strlen(instructiuni) > MAX_SIZE)
			{
				throw Exceptie("Numarul de caractere din denumire este mai mare decat nr de caractere maxim");
			}
			this->instructiuni = new char[MAX_SIZE + 1];
			strcpy(this->instructiuni, instructiuni);
		}
		catch (Exceptie ex) {
			cerr << ex.what();
			return;
		}
	}

	void setMaterii(vector<MateriePrima> materii) {
		materii.clear();
		for (int i = 0; i < nrMaterii; i++) {
			this->materii.push_back(materii[i]);
		}
	}

	int getMaxSize() {
		return MAX_SIZE;
	}

	char* getIntructiuni() {
		char* copie = new char[MAX_SIZE + 1];
		strcpy(copie, instructiuni);
		return copie;
	}

	int getNrMaterii() {
		return nrMaterii;
	}

	vector<MateriePrima>& getMaterii() {
		return materii;
	}

	Retetar& operator=(Retetar& rt) {
		this->instructiuni = new char[MAX_SIZE + 1];
		strcpy(this->instructiuni, rt.getIntructiuni());
		this->materii.clear();
		for (int i = 0; i < rt.materii.size(); i++) {
			materii.push_back(rt.materii[i]);
		}
		return *this;
	}

	friend ostream& operator<<(ostream& os, Retetar& rt) {
		os << "Materii utilizate: \n";
		for (int i = 0; i < rt.nrMaterii; i++) {
			os << "\t" << rt.materii[i];
		}
		os << "Instructiuni: " << rt.getIntructiuni();
		return os;
	}

	friend istream& operator>>(istream& is, Retetar& rt) {
		string denumire;
		is >> denumire;
		rt.setInstructiuni(const_cast<char*>(denumire.c_str()));

		vector<MateriePrima> materii;
		int nr;
		is >> nr;
		for (int i = 0; i < nr; i++)
		{
			MateriePrima mp;
			is >> mp;
			materii.push_back(mp);
		}
		rt.setMaterii(materii);
		return is;
	}

	MateriePrima& operator[](int index) {
		try {
			if (index >= materii.size() || index < 0)
			{
				throw Exceptie("Indexul dat este eronat");
			}
			return materii[index];
		}
		catch (Exceptie ex) {
			cerr << ex.what();
			return materii[0];
		}
	}

	Retetar& operator+(MateriePrima mp) {
		nrMaterii++;
		materii.push_back(mp);
		return *this;
	}

	friend bool operator>(Retetar& r1, Retetar& r2) {
		return r1.getNrMaterii() > r2.getNrMaterii();
	}

	friend bool operator<(Retetar& r1, Retetar& r2) {
		return r1.getNrMaterii() < r2.getNrMaterii();
	}

	friend bool operator>=(Retetar& r1, Retetar& r2) {
		return r1.getNrMaterii() >= r2.getNrMaterii();
	}

	friend bool operator<=(Retetar& r1, Retetar& r2) {
		return r1.getNrMaterii() <= r2.getNrMaterii();
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
		char buffer[255];
		ifs.read(buffer, sizeof(buffer));
		instructiuni = buffer;

		int numMaterii;
		ifs.read(reinterpret_cast<char*>(&numMaterii), sizeof(numMaterii));

		materii.resize(numMaterii);
		for (int i = 0; i < numMaterii; ++i) {
			materii[i].read(ifs);
		}
	}

	void write(ofstream& ofs) const override {
		ofs.write(instructiuni, strlen(instructiuni) + 1);

		int numMaterii = static_cast<int>(materii.size());
		ofs.write(reinterpret_cast<const char*>(&numMaterii), sizeof(numMaterii));

		for (const auto& materie : materii) {
			materie.write(ofs);
		}
	}

	~Retetar() {
		delete[] instructiuni;
	}
};
