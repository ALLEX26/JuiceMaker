﻿#include <iostream>
#include <Windows.h>
#include<string>
#include <list>
#include <fstream>
#include <sstream>

using namespace std;

class Client
{
private:
	string nume;
	string parola;
	string mail;
public:
	Client(string _nume, string _parola, string _mail)
	{
		this->nume = _nume;
		this->parola = _parola;
		this->mail = _mail;
	}
	string get_nume()
	{
		return this->nume;
	}

};

class Sucuri
{
private:
	string nume;
	string fruct;
	bool zahar;
public:
	Sucuri(string _nume, string _fructe, bool _zahar)
	{
		this->nume = _nume;
		this->fruct = _fructe;
		this->zahar = _zahar;
	}
	string getNume() const {
		return nume;
	}
	void afiseazaDetalii() const
	{
		cout << "Nume: " << nume << ", Fruct: " << fruct << ", Zahar: " << (zahar ? "Da" : "Nu") << endl;
	}
};

class Depozit
{
private:
	list<Sucuri*>s;
	int capacitate;
public:
	Depozit(int capacitate, list<Sucuri*>s)
	{
		this->capacitate = capacitate;
	}

};


void DefinireUtilizator(list<Client*>&c)
{
	string nume, gmail, parola;
	cout << "Intruduceti numele dumnevoastra: "; cin >> nume;
	cout << "Introduceti adresa dumneavoastra de mail:"; cin >> gmail;
	cout << "Introduceti parola personala: "; cin >> parola;
	c.push_back(new Client(nume, parola, gmail));
}

void afiseazaSucuriDinFisier(const string& numeFisier) {
	ifstream fisier(numeFisier);
	string linie;

	while (getline(fisier, linie)) {
		stringstream ss(linie);
		string nume, fruct, strZahar;
		bool zahar;

		getline(ss, nume, ',');
		getline(ss, fruct, ',');
		getline(ss, strZahar, ',');

		zahar = (strZahar == "true");

		Sucuri suc(nume, fruct, zahar);
		suc.afiseazaDetalii();
	}

	fisier.close();
}
void citesteSucuriDinFisier(const string& numeFisier, list<Sucuri*>& listaSucuri) {
	ifstream fisier(numeFisier);
	string linie;
	while (getline(fisier, linie)) {
		stringstream ss(linie);
		string nume, fruct, strZahar;
		bool zahar;

		getline(ss, nume, ',');
		getline(ss, fruct, ',');
		getline(ss, strZahar, ',');

		zahar = (strZahar == "true");

		// Verifică dacă sucul deja există în listă înainte de a-l adăuga
		bool existaDeja = false;
		for (auto& suc : listaSucuri) {
			if (suc->getNume() == nume) {
				existaDeja = true;
				break;
			}
		}
		if (!existaDeja) {
			listaSucuri.push_back(new Sucuri(nume, fruct, zahar));
		}
	}

	fisier.close();
}



void afiseazaSucurile(const list<Sucuri*>& listaSucuri) {
	for (const auto& suc : listaSucuri) {
		suc->afiseazaDetalii();
	}
}

void stergeSucDupaNume(list<Sucuri*>& listaSucuri, const string& numeSuc, unique_ptr<Sucuri>& ultimulSucSters) {
	bool sucGasit = false;
	for (auto it = listaSucuri.begin(); it != listaSucuri.end(); ) {
		if ((*it)->getNume() == numeSuc) {
			ultimulSucSters = make_unique<Sucuri>(**it);
			delete *it;
			it = listaSucuri.erase(it);
			sucGasit = true;
			cout << "Sucul " << numeSuc << " a fost sters." << endl;
			break;
		}
		else {
			++it;
		}
	}

	if (!sucGasit) {
		cout << "Sucul " << numeSuc << " nu a fost gasit in lista." << endl;
	}

	if (listaSucuri.empty()) {
		cout << "Toate sucurile au fost epuizate. Vom adauga inapoi ultimul suc sters." << endl;
		if (ultimulSucSters != nullptr) {
			listaSucuri.push_back(new Sucuri(*ultimulSucSters));
		}
	}
}







int main()
{
	list <Sucuri*>s;
	list <Client*>c;

	unique_ptr<Sucuri> ultimulSucSters;
	citesteSucuriDinFisier("sucuri.txt", s);
	string p, nume_suc;
	int opt, n;
	do
	{
		cout << "0. Iesire\n";
		cout << "1. Inregistrare client nou\n";
		cout << "2. Autentificare client existent\n";
		cout << "3. Afisare sucuri disponibile\n";
		cout << "4. Afisare sucuri existente in depozit\n";
		cout << "5. Comanda suc\n";
		cout << "6. Afisare istoric comenzi\n";
		cout << "\n-------------------------------------------------\n";
		cout << "Optiunea dumneavoastra este: ";
		cin >> opt;
		switch (opt)
		{
		case 1:
			system("cls");
			DefinireUtilizator(c);
			cout << "\n\n";
			system("pause");
			system("cls");
			break;
		case 2:

			break;
		case 3:



			afiseazaSucurile(s);

			break;
		case 4:

			afiseazaSucuriDinFisier("sucuri.txt");
			break;
		case 5:
			cout << "introduceti sucul dorit" << endl;
			cin >> nume_suc;
			stergeSucDupaNume(s, nume_suc, ultimulSucSters);
			break;
		case 6:
			break;
		case 0:
			exit(0);
		default: cout << "\nAti ales optiunea gresita!\n";
			system("pause");
			system("cls");
		}
	} while (opt != 0);
	for (auto suc : s) {
		delete suc;
	}
}