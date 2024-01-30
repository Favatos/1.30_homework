#include <iostream>
#include <list>
#include <ctime>
#include <random>
using namespace std;

class Weapon
{
protected:
	int damage;
	int shootCount;
	int maxAmmo;
public:

	Weapon(int damage, int shootCount, int maxAmmo) : damage(damage), shootCount(shootCount), maxAmmo(maxAmmo) {}
	virtual int shoot() = 0;
	int getShootcount() { return shootCount; }
};

class Blaster : public Weapon {
public:
	Blaster() : Weapon(10, -1, -1) {}
	int shoot() {
		return damage;
	}
};

class Pistol : public Weapon {
public:
	Pistol() : Weapon(20, 6, 6) {}
	int shoot(){
		if (shootCount > 0) {
			shootCount--;
			return damage;
		}
	}
};

class MachineGun : public Weapon {
public:
	MachineGun() : Weapon(5, 100, 100) {}
	int shoot() {
		if (shootCount > 0) {
			shootCount--;
			return damage;
		}
	}
};

class Monster {
	string name;
	list<Weapon*>weapons;
public:
	int hp;
	Monster(string n, int h) : name { n }, hp{ h } {}
	void getWeapon(Weapon* weapon) {
		weapons.push_back(weapon);
	}

	string getName() { return name; }

	int checkWeapons() {
		int check = 0;
		for (Weapon* weapon : weapons) {
			if (weapon->getShootcount() == 0) {
				check++;
			}
		}
		return check;
	}

	void shoot(Monster* m2) {
		for (Weapon* weapon : weapons) {
			if (weapon->getShootcount() != 0) {
				int d = weapon->shoot();
				cout << "Урон по "<<m2->getName()<<" от "<<name<<": " << d << endl;
				m2->hp -= d;
			}
			else {
				cout << "Патроны закончились у " << name << endl;
			}
		}
	}
};

Weapon* get(list<Weapon*> l, int k) {
	list<Weapon*>::iterator it = l.begin();
	for (int i = 0; i < k; i++) {
		++it;
	}

	return *it;
}

void game(Monster* m1, Monster* m2) {
	while (m1->hp != 0 || m2->hp != 0 && (m1->checkWeapons()!=2 && m2->checkWeapons() != 2)) {
		m1->shoot(m2);
		m2->shoot(m1);
		cout << endl;
	}
	if (m1->hp == 0) {
		cout << "Победил монстр " << m1->getName() << endl;
	}
	else if (m2->hp == 0) {
		cout << "Победил монстр " << m2->getName() << endl;
	}
	else {
		cout << "Патроны закончились у всех. Победила дружба." << endl;
	}
}

void randWeapon(list<Weapon*> l, Monster* p) {
	srand(time(NULL));
	p->getWeapon(get(l, rand() % 3));
	p->getWeapon(get(l, rand() % 3));
}

int main(){
	setlocale(LC_ALL, "RU");
	list<Weapon*> weapons;
	Blaster* blaster = new Blaster();
	Pistol* pistol = new Pistol();
	MachineGun* machineGun = new MachineGun();
	
	weapons.push_back(blaster);
	weapons.push_back(pistol);
	weapons.push_back(machineGun);

	Monster m1("Петя", 100);
	Monster m2("Миша", 100);
	randWeapon(weapons, &m1);
	randWeapon(weapons, &m2);
	game(&m1, &m2);

	for (Weapon* weapon : weapons) {
		delete weapon;
	}

	return 0;
}