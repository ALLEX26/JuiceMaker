#include<iostream>
#include<Windows.h>
#include<string>
#include<list>

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

	string get_nume()	
	{
		return this->nume;
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

void getSuc()
{
	list<Sucuri*>sucuri;
	string nume;
	cout << "Dati numele sucului pe care il doriti: "; cin >> nume;
	for (auto s : sucuri)
	{
		if (s->get_nume() == nume)
		{
			cout << "Sucul dumneavoastra este servit imediat --> " << nume;
		}
		else
		{
			cout << "Sucul dumnevoastra se prepara asteptati 10 secunde";
			sucMaker();
		}
	}
}


void DefinireUtilizator(list<Client*>&c)
{
	string nume, gmail, parola;
	cout << "Intruduceti numele dumnevoastra: "; cin >> nume;
	cout << "Introduceti adresa dumneavoastra de mail:"; cin >> gmail;
	cout << "Introduceti parola personala: "; cin >> parola;
	c.push_back(new Client(nume, parola, gmail));
}


int main()
{
	list <Client*>c;
	string p;
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

			break;
		case 4:

			break;
		case 5:
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

}