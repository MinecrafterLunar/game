#include <bits/stdc++.h>
#include <algorithm>
#include <Windows.h>
#include <mmsystem.h>
#include <fstream>
#pragma comment(lib,"winmm.lib")
using namespace std;
#ifndef HEAD_H
#define HEAD_H
#define backPackSize 10
#define playerAttackConstValue 5
#define shreikerActivateTimeCanSpawnWarden 3
#define ItemCount 23
//debugging stuff
#define toString(name) #name
#define debug(err) cout << "debug:" << toString(err) <<": "<< err << '\n'
#define debugger MessageBoxA(NULL,"This is the debugger","game",MB_OK)
namespace head{
	//definitions
		struct Item {
			int attack;
			string category;
			/*categories:
			**armorHead *
			**armorChest *
			**armorFeet *
			**armorSlotHead *
			**armorSlotChest *
			**armorSlotFeet *
			**weapon
			**air*/
			string name;
			void setAir(void) {
				attack = 10;
				category = "\0";
				name = "Air";
			}
			bool operator<(const Item& b)const {
				if (category < b.category) {
					return 1;
				}
				else if (category > b.category) {
					return 0;
				}
				else if (name < b.name) {
					return 1;
				}
				else {
					return 0;
				}
			}//this thing allows sorting
			bool operator==(const Item& b)const {
				if (b.name == name) {
					return 1;
				}
				else {
					return 0;
				}
			}
			bool operator!=(const Item& b)const {
				if (b.name != name) {
					return 1;
				}
				else {
					return 0;
				}
			}
		} slotHead = Item{ 0,"armorslot", "" }, slotChest = Item{ 0,"armorslot", "" }, slotFeet = Item{ 0,"armorslot", "" },
			slotWeapon = Item{ 0,"weaponslot", "" }, air = { 10,"\0", "Air" }, weapon = air, armorSlot[3], backPack[backPackSize];

		struct Entity {
			string category;
			string description;
			string name;
			int attack;
			int health;
			int maximumHealth;
			vector<Item> drop;
			bool operator==(const Entity& b)const {
				if (name == b.name) {
					return 1;
				}
				else {
					return 0;
				}
			}
		};

		struct Dimension {
			string description;
			string name;
			Entity spawn;
			/*dimensions:
			**Deep Dark
			**The Nether
			**The End*/
		};

		struct craftingRecipe {
			string category;
			vector<Item> recipe;
			Item result;
			bool operator<(const craftingRecipe& b)const {
				if (category < b.category) {
					return 1;
				}
				else {
					return 0;
				}
			}
			bool operator==(const craftingRecipe& b)const {
				if (category == b.category && recipe == b.recipe && result==b.result) {
					return 1;
				}
				else {
					return 0;
				}
			}
			bool operator<=(const craftingRecipe& b)const {
				if ((category == b.category && recipe == b.recipe && result == b.result) || (category < b.category)) {
					return 1;
				}
				else {
					return 0;
				}
			}
		};

		struct slot {
			Item item;
			int count;
			bool operator<(const slot& b)const {
				return ((count == b.count) ? (count < b.count) : (item < b.item));
			}
		};

	//functions
		bool ifFileExists_ifstream(string& name) {//if file exists->returns 1,else returns 0
			ifstream f(name.c_str());
			return f.good();
		}

		void enter(int t = 1) {//enter t times(if t undefined, t=1)
			for (int i = 0; i < t; i++) {
				cout << '\n';
			}
		}

		void printChar(char ch, int t) {//print ch t times
			for (int i = 0; i < t; i++) {
				cout << ch;
			}
		}

		void cls(void) {//clear screen
			system("cls");
		}

		void wait(double secs) {//wait secs seconds
			secs *= 1000;
			Sleep((int)secs);
		}

		int rand_(int low, int high) {//random number generator values from low to high
			int ret;
			ret = rand() % (high - low) + low;
			return ret;
		}

		void printLine(void) {//print a line...
			printChar('-', 47);
		}

		void printString_wait(const char a[], int n, double sec = 0.1) {
			for (int i = 0; i < n; i++) {
				cout << a[i];
				wait(sec);
			}
		}

		bool checkBackPackIsFull(void) {
			bool flag=true;
			for (int i = 0; i < backPackSize; i++) {
				if (backPack[i] == air) {
					flag = false;
					break;
				}
			}
			return flag;
		}

		int getBackPackLastAir(void) {
			if (checkBackPackIsFull()) {
				MessageBoxA(NULL, "Invalid use of getBackPackLastAir!", "Error", MB_OK);
				return INT_MAX;
			}
			for (int i = 0; i < backPackSize; i++) {
				if (backPack[i] == air) {
					return i;
				}
			}
			return INT_MAX;
		}

		bool checkBackPackIsEmpty(void) {
			for (int i = 0; i < backPackSize; i++) {
				if (backPack[i] != air) {
					return false;
				}
			}
			return true;
		}

		char charEncode(char c) {
			if (c > 'z' || c < 'A' || (c > 'Z' && c < 'a')) {
				return c;
			}
			else if (c > 'A' && c < 'Z') {
				if (c == 'Z') {
					return 'A';
				}
				else {
					return char(c + 1);
				}
			}
			else {
				if (c == 'z') {
					return 'a';
				}
				else {
					return char(c + 1);
				}
			}
		}
	//sorting......(I'm speeeeeechless.)
		//the sorting function sort(RAITER_,RAITER_,_comp_) doesn't work on vectors so I made one quicksort.(it must have operator< && operator<=)
		template <typename T> vector<T> quickSort(vector<T> s, int start, int end) {
			int i, j;
			i = start;
			j = end;
			s[0] = s[start];
			while (i < j) {
				while (i < j && s[0] < s[j]) {
					j--;
				}
				if (i < j) {
					s[i] = s[j];
					i++;
				}
				while (i < j && s[i] <= s[0]) {
					i++;
				}
				if (i < j) {
					s[j] = s[i];
					j--;
				}
			}
			s[i] = s[0];
			if (start < i) {
				quickSort(s, start, j - 1);
			}
			if (i < end) {
				quickSort(s, j + 1, end);
			}
			return s;
		}
}
#endif // HEADER_H
