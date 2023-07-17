#include "defines.h"
#include "TesterDebug.h"
using namespace std;
using namespace head;
using namespace defs;
clock_t clockStart;
//real functions
	void creator(void) {//you know...
		cls();
		cout << "creator: Lunar\nher bilibili: https://space.bilibili.com/3493110147451127?spm_id_from=333.1007.0.0";
		wait(3);
		cls();
	}

	bool canCraft(craftingRecipe r) {
		Item tempBackPack[backPackSize];
		for (int i = 0; i < backPackSize; i++) {
			tempBackPack[i] = backPack[i];
		}
		vector<Item> mat;
		mat = r.recipe;
		for (int i = 0; i < mat.size(); i++) {
			bool fnd = 0;
			for (int j = 0; j < backPackSize; j++) {
				if (tempBackPack[j] == mat[i]) {
					mat[i] = air;
					tempBackPack[j] = air;
					fnd = 1;
					break;
				}
			}
			if (fnd == 0) {
				return 0;
			}
		}
		return 1;
	}
//printing functions
	//print data
		void printDimensionData(Dimension d) {
			cout << d.name << ": " << d.description;
		}

		void printItemData(Item i) {
			if (i.category == "armorslot" || i.category == "weaponslot" || i == air) {
				cout << "nothing";
				return;
			}
			cout << i.name;
			if (i.category == "weapon") {
				cout << "    attack damage: " << i.attack;
			}
		}

		void printRecipe(craftingRecipe r) {
			cout << "needs: ";
			for (int i = 0; i < r.recipe.size(); i++) {
				cout << r.recipe[i].name << ' ';
			}
			enter();
			cout << "result: ";
			cout << r.result.name;
		}

		void printEntityInfo(Entity entity) {
			cout << entity.name << ": ";
			enter();
			cout << entity.description;
			enter();
		}

	//print menus
		int printMainMenu(void) {
			cls();
			int option;
			cout << "player: " << player.name;
			enter();
			cout << "your current dimension: " << currentDimension.name;
			enter();
			printLine();
			enter();
			cout << "your current health: " << player.health;
			enter();
			cout << "attack damage:" << player.attack;
			enter();
			printLine();
			enter();
			cout << "you can have several options to do";
			enter();
			cout << "1: go to dimension";
			enter();
			cout << "2: open inventory";
			enter();
			cout << "3: pick up dropped items";
			enter();
			cout << "4: drop items";
			enter();
			cout << "5: quit game";
			enter();
			cin >> option;
			return option;
		}

		string printDimensions(void) {
			cls();
			string option;
			printDimensionData(overworld);
			enter();
			printDimensionData(deepDark);
			enter();
			printDimensionData(nether);
			enter();
			printDimensionData(defs::end);
			enter();
			cin >> option;
			return option;
		}

		int printCraftingMenu() {
			cls();
			int option;
			if (recipes.size() != 0) {
				cout << "you can have several recipes to choose from:";
				enter();
			}
			for (int i = 1; i <= recipes.size(); i++) {
				cout << i << ": ";
				enter();
				printRecipe(recipes[i-1]);
				enter(2);
			}
			cout << recipes.size()+1<<": return to main menu";
			enter();
			printLine();
			enter();
			cout << "your inventory:";
			for (int i = 0; i < backPackSize; i++) {
				enter();
				printItemData(backPack[i]);
			}
			enter();
			cin >> option;
			return option;
		}

		int printInventory(void) {
			cls();
			int option;
			sort(backPack, backPack + backPackSize);
			cout << "your inventory:";
			for (int i = 0; i < backPackSize; i++) {
				enter();
				printItemData(backPack[i]);
			}
			enter();
			cout << "your armor:";
			for (int i = 0; i < 3; i++) {
				enter();
				printItemData(armorSlot[i]);
			}
			enter(2);
			cout << "your weapon: ";
			enter();
			printItemData(weapon);
			enter(2);
			cout << "selected item: ";
			printItemData(backPack[selectedItem]);
			enter();
			printLine();
			enter();
			cout << "you have several options to do";
			enter();
			cout << "1: open crafting menu";
			enter();
			cout << "2: use selected item";
			enter();
			cout << "3: select item";
			enter();
			cout << "4: return to main menu";
			enter();
			cin >> option;
			return option;
		}

		int printSlectItem(void) {
			int option;
			cls();
			for (int i = 0; i < backPackSize; i++) {
				cout << (i + 1) << ": " << backPack[i].name;
				enter();
			}
			cout << (backPackSize+1) << ": return to main menu";
			enter();
			cin >> option;
			return option;
		}

		int printUnderAttackMenu(void) {
			int option;
			cls();
			cout << "You are under attack!";
			enter();
			cout << "the monster you are facing:";
			enter();
			cout << playerFacingEntity.name;
			enter();
			cout << "your health:"<<player.health;
			enter();
			printLine();
			enter();
			cout << "you have several options to do";
			enter();
			cout << "1: get info about the monster";
			enter();
			cout << "2: try to run away";
			enter();
			cout << "3: attack options";
			enter();
			cout << "4: select item";
			enter();
			cout << "5: quit game";
			enter();
			cin >> option;
			return option;
		}

		int printBeforePlayMenu(void){
			int option;
			cls();
			printString_wait("You are playing Console Minecraft!",35,0.05);
			enter();
			printLine();
			enter();
			cout << "you can:";
			enter();
			cout << "1: start game directly";
			enter();
			cout << "2: or, you can enter a seed!";
			enter();
			cout << "3: How do I play Console Minecraft?";
			enter();
			cin >> option;
			return option;
		}

		int printAttackMenu(void) {
			int option;
			cls();
			cout << "Attacking: " << playerFacingEntity.name;
			enter();
			cout << "attack damage: " << player.attack;
			enter();
			printLine();
			enter();
			cout << "Attacking options:";
			enter();
			cout << "1: attack directly";
			enter();
			cout << "2: use selected item";
			enter();
			cout << "3: return to main menu";
			enter();
			cin >> option;
			return option;
		}

		int printDeathMenu(int Death, Entity entity = air_entity) {
			cls();
			int option;
			cout << "You died!";
			enter();
			switch (Death) {
				case DEATH_ATTACK_ENTITY: {
					cout << player.name << " was slain by " << playerFacingEntity.name;
					enter();
				}
			}
			printLine();
			enter();
			cout << "1: respawn";
			enter();
			cout << "2: quit game";
			enter();
			cin >> option;
			return option;
		}

		vector<int> printDroppedItemsMenu(void) {
			vector<int> options;
			cls();
			if (droppedItems.empty()) {
				cout << "There aren't any dropped items to pick up!";
				wait(2);
				cls();
				options.push_back(0);
				return options;
			}
			cout << "Dropped items:";
			enter();
			for (int i = 0; i < droppedItems.size(); i++) {
				cout << i + 1 << ": " << droppedItems[i].name;
				enter();
			}
			cout << "The count of items you want to pick up:";
			int count;
			cin >> count;
			enter();
			cout << "Which are: ";
			for (int i = 0; i < count; i++) {
				int t;
				cin >> t;
				options.push_back(t);
			}
			return options;
		}

		vector<int> printDiscardStuffMenu(void){
			vector<int> options;
			cls();
			if (checkBackPackIsEmpty()) {
				cout << "There aren\'t any stuff to drop!(Your backpack is empty)";
				options.push_back(0);
				wait(3);
				return options;
			}
			cout << "Your backpack:";
			enter();
			for (int i = 0; i < backPackSize; i++) {
				cout << (i + 1) << ": " << backPack[i].name;
				enter();
			}
			enter();
			cout << "The count of items you want to drop:";
			int count;
			cin >> count;
			enter();
			cout << "Which are: ";
			for (int i = 0; i < count; i++) {
				int t;
				cin >> t;
				options.push_back(t);
			}
			return options;
		}


//game function
	string error;
	bool startGame(void) {
		//creator();
		while (1) {
			if (clock()-clockStart == 6 || bg_f) {
				bg_f = 0;
				clockStart = clock();
				PlaySound(TEXT("bg.wav"), 0, SND_ASYNC);//background music
			}
			player.attack = weapon.attack + playerAttackConstValue;
			if(!underAttack){
				int op_m = printMainMenu();
				switch (op_m) {
					case 1: {
						string op_dim = printDimensions();
						if (op_dim == overworld.name) {
							currentDimension = overworld;
							//nothing to do; the overworld is a safe place.
						}
						else if (op_dim == nether.name) {
							currentDimension = nether;
							if (rand_(0, 5) == 0) {
								playerFacingEntity = wither;
							}
							else {
								playerFacingEntity = piglin;
							}
							underAttack = 1;
							//the nether is a dangerous place. 1/5 chance: a wither.
						}
						else if (op_dim == deepDark.name) {
							currentDimension = deepDark;
							if (rand_(0, 2) == 0) {
								activatedShriekerTimes++;
								if (activatedShriekerTimes >= shreikerActivateTimeCanSpawnWarden) {
									playerFacingEntity = warden;
									isBlind = true;
									underAttack = true;
								}
							}
							//the deep dark is definetly awful. But the chance of spawning a warden is 1/15.
						}
						else if (op_dim == defs::end.name) {
							currentDimension = defs::end;
							if (!enderDragonIsSlain) {
								playerFacingEntity = enderDragon;
							}
							else {
								playerFacingEntity = enderman;
							}
							//the end has a chance of 1 spawning the ender dragon, but it will be endermen if the dragon is already slain.
							underAttack = true;
						}
						break;
					}
					case 2: {
						int op_inventory = printInventory();
						switch (op_inventory) {
							case 1: {
								int craft_op = printCraftingMenu();
								cls();
								if (craft_op <= 0 || craft_op > recipes.size() + 1) {
									error = "The input is wrong!";
									return 0;
								}
								if (craft_op == recipes.size() + 1) {
									break;
								}
								if (canCraft(recipes[craft_op - 1])) {
									int Air_ = 0;
									for (int i = 0; i < recipes[craft_op - 1].recipe.size(); i++) {
										for (int j = 0; j < backPackSize; j++) {
											if (backPack[j] == recipes[craft_op - 1].recipe[i]) {
												backPack[j].setAir();
												Air_ = j;
												break;
											}
										}
									}
									backPack[Air_] = recipes[craft_op - 1].result;
									sort(backPack, backPack + backPackSize);
								}
								else {
									cls();
									cout << "You don\'t have enough materials, can\'t craft the item!\n";
									wait(2);
									break;
								}
								cls();
								break;
							}
							case 2: {
								if (backPack[selectedItem].category == "armorHead" && armorSlot[0]==slotHead) {
									Item t = backPack[selectedItem];
									backPack[selectedItem].setAir();
									armorSlot[0] = t;
								}
								if (backPack[selectedItem].category == "armorChest" && armorSlot[1] == slotChest) {
									Item t = backPack[selectedItem];
									backPack[selectedItem].setAir();
									armorSlot[1] = t;
								}
								if (backPack[selectedItem].category == "armorFeet" && armorSlot[2] == slotFeet) {
									Item t = backPack[selectedItem];
									backPack[selectedItem].setAir();
									armorSlot[2] = t;
								}
								if (backPack[selectedItem].category == "weapon" && weapon == slotWeapon) {
									Item t = backPack[selectedItem];
									backPack[selectedItem].setAir();
									weapon = t;
								}
								break;
							}
							case 3: {
								int op_sel = printSlectItem();
								if (op_sel != (backPackSize+1)) {
									selectedItem = (op_sel-1);
								}
								break;
							}
							default: {
								continue;
							}
						}
						break;
					}
					case 3: {
						vector<int> op_i = printDroppedItemsMenu();
						if (op_i == vector<int>{0}) {
							break;
						}
						for (int i = 0; i < op_i.size(); i++) {
							if (checkBackPackIsFull()) {
								cls();
								cout << "Your backpack is full! You tried to get too many items into it!";
								wait(2);
								cls();
							}
							else {
								int last = getBackPackLastAir();
								backPack[last] = droppedItems[op_i[i]-1];
							}
						}
						break;
					}
					case 4: {
						vector<int> op_i = printDiscardStuffMenu();
						if (op_i == vector<int>{0}) {
							break;
						}
						for (int i = 0; i < op_i.size(); i++) {
							if (checkBackPackIsEmpty()) {
								break;
							}
							droppedItems.push_back(backPack[op_i[i]-1]);
							backPack[op_i[i]-1].setAir();
						}
						break;
					}
					case 5: {
						return true;
						break;
					}
					default: {
						error = "The input is wrong!";
						return false;
					}
				}
				cls();
			}
			else {
				int option = printUnderAttackMenu();
				switch (option) {
					case 1: {
						cls();
						printEntityInfo(playerFacingEntity);
						wait(4);
						cls();
						if (rand_(0, 2) == 0) {
							player.health -= (playerFacingEntity.attack+rand_(0,1));
						}
						break;
					}
					case 2: {
						if (rand_(0, 7) < 2) {
							playerFacingEntity = air_entity;
							underAttack = 0;
							cls();
							cout << "You escaped successfully!";
							wait(2);
							cls();
						}
						else {
							cls();
							cout << "The " << playerFacingEntity.name << " stopped you from escaping!";
							wait(2);
							cls();
							if (rand_(0, 2) == 0) {
								player.health -= (playerFacingEntity.attack + rand_(0, 1));
							}
						}
						break;
					}
					case 3: {
						int attack_op = printAttackMenu();
						switch (attack_op) {
							case 1: {
								playerFacingEntity.health -= ((player.attack + rand_(0, 1)) + (isBlind == 0 ? 1 : 0) * (rand_(0, 2)));
								player.health -= (playerFacingEntity.attack + rand_(0, 1) - (isBlind == 0 ? 1 : 0) * rand_(0, 5));
								if (playerFacingEntity.health <= 0 && player.health > 0) {
									for (int i = 0; i < playerFacingEntity.drop.size(); i++) {
										droppedItems.push_back(playerFacingEntity.drop[i]);
									}
									if (playerFacingEntity == warden) {
										isBlind = false;
									}
									playerFacingEntity = air_entity;
									underAttack = 0;
								}
								break;
							}
							case 2: {
								if (backPack[selectedItem].category == "armorHead" && armorSlot[0] == slotHead) {
									Item t = backPack[selectedItem];
									backPack[selectedItem].setAir();
									armorSlot[0] = t;
								}
								if (backPack[selectedItem].category == "armorChest" && armorSlot[1] == slotChest) {
									Item t = backPack[selectedItem];
									backPack[selectedItem].setAir();
									armorSlot[1] = t;
								}
								if (backPack[selectedItem].category == "armorFeet" && armorSlot[2] == slotFeet) {
									Item t = backPack[selectedItem];
									backPack[selectedItem].setAir();
									armorSlot[2] = t;
								}
								if (backPack[selectedItem].category == "weapon" && weapon == slotWeapon) {
									Item t = backPack[selectedItem];
									backPack[selectedItem].setAir();
									weapon = t;
								}
								break;
							}
							case 3: {
								break;
							}
						}
						break;
					}
					case 4: {
						int op_sel = printSlectItem();
						if (op_sel != (backPackSize + 1)) {
							selectedItem = (op_sel - 1);
						}
						break;
					}
					case 5: {
						return true;
						break;
					}
					default: {
						error = "The input is wrong!";
						return false;
					}
				}
				if (player.health <= 0) {
					int option = printDeathMenu(DEATH_ATTACK_ENTITY,playerFacingEntity);
					switch (option) {
						case 1: {
							cls();
							weapon.setAir();
							armorSlot[0] = slotHead;
							armorSlot[1] = slotChest;
							armorSlot[2] = slotFeet;//armor slots
							weapon = slotWeapon;
							for (int i = 0; i < backPackSize; i++) {
								backPack[i].setAir();
							}//backpack
							player.health = player.maximumHealth;
							underAttack = 0;
							currentDimension = overworld;
							startGame();
						}
						case 2: {
							return true;
						}
					}
				}
			}
		}
		return 1;
	}

//main
	int main() {
		clockStart = clock();
		quickSort(recipes, 0, int(recipes.size() - 1));
		string filename = "bg.wav";
		if (!ifFileExists_ifstream(filename)) {
			MessageBoxA(NULL, "bg.wav is not existing! This is an error!", "game", MB_OK | MB_ICONEXCLAMATION);
			return -1;
		}
		filename = "pigstep.wav";
		if (!ifFileExists_ifstream(filename)) {
			MessageBoxA(NULL, "pigstep.wav is not existing! This is an error!", "game", MB_OK | MB_ICONEXCLAMATION);
			return -1;
		}
		cout << "Initializing game...";
		srand(unsigned int(time(0)));
		cout << "¨x";
		weapon.setAir();
		cout << "¨y";
		armorSlot[0] = slotHead;
		cout << "¨z";
		armorSlot[1] = slotChest;
		cout << "¨{";
		armorSlot[2] = slotFeet;//armor slots
		cout << "¨|";
		weapon = slotWeapon;
		for (int i = 0; i < backPackSize; i++) {
			backPack[i].setAir();
		}//backpack
		cout << "¨} Initialzing done!";
		wait(1);
		cls();
//		weapon = iron_sword;

		///*
		creator();
		unsigned long seed;
		int op = printBeforePlayMenu();
		if (op == 2) {
			cls();
			cout << "please enter the seed: ";
			cin >> seed;
			srand(seed);
		}
		else if (op == 3) {
			cls();
			howToPlay();
			cls();
		}
		cls();
		cout << "Please enter the player name:";//playername
		string playerName;
		cin >> playerName;
		player.name = playerName;//*/
//		player.name = "test";//only for testing!
		if (startGame() == false) {//the game has something wrong going on...
			cls();
			cout << "\nSomething's wrong with the game, error: " << error;
		}
		else {//the game is good!
			cls();
			cout << "The game ended succesfully!";
		}
		enter();
		system("pause");
		return 0;
	}
