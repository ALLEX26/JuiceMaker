#include <iostream>
#include <Windows.h>
#include<string>
#include <list>

using namespace std;

class Client
{
public:
	string nume;
	string parola;
	string mail;
	Client(string _nume, string _parola, string _mail)
	{
		this->nume = _nume;
		this->parola = _parola;
		this->mail = _mail;
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

class Cake
{
public:
	Cake();
	Cake(string n);
	string getName();
private:
	string name;
};
Cake::Cake()
{
	name = "name";
}
Cake::Cake(string n)
{
	this->name = n;
}
string Cake::getName()
{
	return this->name;
}
class RecipeCake
{
public:
	RecipeCake();
	RecipeCake(string name, int time);
	string getName();
	int getTime();
private:
	string name;
	int time;
};
RecipeCake::RecipeCake()
{
	name = "n/a";
	time = 1;
}

RecipeCake::RecipeCake(string n, int t)
{
	this->name = n;
	this->time = t;
}
string RecipeCake::getName()
{
	return this->name;
}
int RecipeCake::getTime()
{
	return this->time;
}
class CakeMaker
{
public:
	CakeMaker();
	Cake takeCommand(RecipeCake recipe);
private:
};
CakeMaker::CakeMaker()
{}

Cake CakeMaker::takeCommand(RecipeCake recipe)
{
	string name = recipe.getName();
	int time = recipe.getTime();
	Cake alt = Cake(name);
	cout << "\nPrajitura se pregateste, asteptati 5 secunde!\n";
	for (int i = 5; i >= 1; i--)
	{
		Sleep(1000);
		cout << "Au ramas " << i << " secunde\n";
	}
	cout << "\nPrajitura este gata!\n\n";
	Sleep(100);
	return alt;
}
class CarouselOfCakes
{
public:
	CarouselOfCakes();
	bool addCake(Cake cn);
	Cake getCake(string cn);
	int getCurentCapacity();
	void getCakesFromCarousel();
private:
	Cake* storage[10];
	unsigned int maxCapacity = 10;
	unsigned int lowLimit = 3;

};
CarouselOfCakes::CarouselOfCakes()
{
	for (int i = 0; i < maxCapacity; i++)
	{
		storage[i] = nullptr;
	}
}

bool CarouselOfCakes::addCake(Cake n)
{
	for (int b = 0; b < maxCapacity; b++)
	{
		if (storage[b] != nullptr)
		{

		}
		else
		{
			storage[b] = new Cake(n.getName());
			return 1;
		}
	}
	return 0;
}

Cake CarouselOfCakes::getCake(string cn)
{
	for (int i = 0; i < maxCapacity; i++)
	{
		if (storage[i] != nullptr)
		{
			if ((*storage[i]).getName().compare(cn) != 1)
			{
				Cake tkc = *storage[i];
				delete storage[i];
				storage[i] = nullptr;
				return tkc;
			}
		}
	}
	return Cake("");
}

int CarouselOfCakes::getCurentCapacity()
{
	unsigned int size = 0;
	for (int h = 0; h < maxCapacity; h++)
	{
		if (storage[h] != nullptr)
		{
			size++;
		}
	}
	return size;
}

void CarouselOfCakes::getCakesFromCarousel()
{
	unsigned int i = 0;
	for (i = 0; i < getCurentCapacity(); i++)
		cout << storage[i]->getName() << " ";
	cout << '\n';
}
class CommandTaker
{
public:
	CommandTaker();
	CommandTaker(RecipeCake recipe);
	Cake takeCommand(RecipeCake recipe);
	Cake* takeCommand(RecipeCake recipe, int nrC);
	Cake takeCommand(string noc);
	void getCakesFromCarousel();
	bool checkCarouselOfCakes();
	bool refillCarousel();

private:
	RecipeCake carouselRecipe;
	CakeMaker cakeMaker;
	CarouselOfCakes carousel;
};
CommandTaker::CommandTaker()
{
}
CommandTaker::CommandTaker(RecipeCake recipe)
{
	carouselRecipe = recipe;
}
Cake CommandTaker::takeCommand(RecipeCake recipe)
{
	Cake ct = carousel.getCake(recipe.getName());
	if (ct.getName() != "")
		return ct;
	else
		ct = cakeMaker.takeCommand(recipe);
	return ct;
}

Cake* CommandTaker::takeCommand(RecipeCake recipe, int nrC)
{
	int i = 0;
	Cake r[20];

	while (nrC)
	{
		cout << "Pregatim prajitura: " << recipe.getName() << " cu numarul -> " << i + 1 << ".\n";
		cout << "Prajituri ramase -> " << nrC - 1 << "\n";
		r[i] = cakeMaker.takeCommand(recipe);
		nrC--;
		i++;
	}
	return r;
}

Cake CommandTaker::takeCommand(string noc)
{
	RecipeCake rc = RecipeCake(noc, 5);
	Cake a = carousel.getCake(rc.getName());
	if (a.getName() != "")
		return a;
	else
		a = cakeMaker.takeCommand(rc);
	return a;
}

void CommandTaker::getCakesFromCarousel()//  ???
{
	carousel.getCakesFromCarousel();
}

bool CommandTaker::checkCarouselOfCakes()
{
	if (carousel.getCurentCapacity() < 3)
	{
		return 0;
	}
	return 1;
}

bool CommandTaker::refillCarousel()
{
	int size = carousel.getCurentCapacity();
	bool check;
	Cake cn = Cake(carouselRecipe.getName());
	while (size < 10)
	{
		check = carousel.addCake(cn);
		size++;
	}

	return check;
}
class CommandPanel
{
public:
	CommandPanel();
	void showProducts();
	void selectProduct(string p);
	void selectProduct(string p, int nrp);
	void showProductInCarousel();
private:
	list<RecipeCake> menu;
	CommandTaker commandTaker;

};
CommandPanel::CommandPanel()
{
	RecipeCake c0 = RecipeCake("Amandina", 5);
	RecipeCake c1 = RecipeCake("Cheesecake", 5);
	RecipeCake c2 = RecipeCake("Ecler", 5);
	RecipeCake c3 = RecipeCake("Savarina", 5);
	menu.push_back(c0);
	menu.push_back(c1);
	menu.push_back(c2);
	menu.push_back(c3);

	if (commandTaker.checkCarouselOfCakes() == 0)
		commandTaker.refillCarousel();
}

void CommandPanel::showProducts()
{
	list<RecipeCake>::iterator rc;
	for (rc = menu.begin(); rc != menu.end(); ++rc)
		cout << rc->getName() << "\n";
}

void CommandPanel::selectProduct(string p)
{
	bool ok = 0;
	list<RecipeCake>::iterator rc;
	for (rc = menu.begin(); rc != menu.end(); rc++)
		if (rc->getName() == p)
			ok = 1;
	if (ok == 0)
		cout << "\nNe pare rau, aceasta prajitura nu face parte din meniul nostru!\n";
	else
		commandTaker.takeCommand(p);
}

void CommandPanel::selectProduct(string p, int nrp)
{
	bool ok = 0;
	list<RecipeCake>::iterator rc;
	for (rc = menu.begin(); rc != menu.end(); rc++)
		if (rc->getName() == p)
		{
			ok = 1;
		}

	if (ok == 0)
	{
		cout << "Ne pare rau, aceasta prajitura nu face parte din meniul nostru!\n";
	}

	else if (1 <= nrp && nrp <= 20)
	{

		RecipeCake rc = RecipeCake(p, 5);
		commandTaker.takeCommand(rc, nrp);
	}
	else
		cout << "Ne pare rau, aparatul poate produce doar 20 de bucati.\n";
}

void CommandPanel::showProductInCarousel()
{
	commandTaker.getCakesFromCarousel();
}

int main()
{
	CommandPanel CP = CommandPanel();
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
			system("cls");
			cout << "Ce prajitura doriti sa comandati? -> ";
			cin >> p;
			CP.selectProduct(p);
			cout << "\n\n";
			system("pause");
			system("cls");
			break;
		case 3:
			system("cls");
			cout << "Ce prajitura doriti sa comandati? -> ";
			cin >> p;
			cout << "\nCate bucati doriti sa comandati? -> ";
			cin >> n;
			cout << "\n";
			CP.selectProduct(p, n);
			cout << "\n\n";
			system("pause");
			system("cls");
			break;
		case 4:
			system("cls");
			CP.showProductInCarousel();
			cout << "In acest moment nu sunt produse disponibile insa daca alegeti un produs din meniul nostru, el va fi gata in doar 5 secunde! \n\n";
			system("pause");
			system("cls");
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
	} while (opt != 5);

}