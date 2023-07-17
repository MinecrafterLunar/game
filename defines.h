#include "head.h"
using namespace head;
#pragma once
#ifndef DEFINES_H
#define DEFINES_H
#define DEATH_NORESULT -1
#define DEATH_ATTACK_ENTITY 0
namespace defs {
	string playerName = "";
	string itemNames[ItemCount];
	bool underAttack = false;
	bool bg_f = true;
	bool isBlind = false;
	bool enderDragonIsSlain = false;
	int selectedItem = 0;
	int activatedShriekerTimes = 0;
	//in main() how to play
	void howToPlay(void) {
		cout << "This is a console half replica of Minecraft";
		enter();
		cout << "This game is developed using Visual Studio";
		enter();
		cout << "Many of the game rules you can find in Minecraft(I mean, not /gamerule command)";
		enter();
		cout << "";
		enter();
		system("pause");
	}
	//items
		//materials
			Item iron_ingot = Item{ 0,"materials","Iron Ingot" }, gold_ingot = Item{0,"materials","Gold Ingot"}, diamond = Item{ 0,"materials","Diamond" };
		//misc
			Item stick = Item{ 0,"misc","Stick" };
			Item enderPearl = Item{ 0,"misc","Ender Pearl" };
		//armor
			/*
			template:
			Item _helmet = Item{ 0,"armorHead"," Helmet" }, _chestplate = Item{ 0,"armorChest"," Chestplate" }, _boots = Item{ 0,"armorFeet"," Boots" };
			*/
			Item iron_helmet = Item{ 0,"armorHead","Iron Helmet" }, iron_chestplate = Item{ 0,"armorChest","Iron Chestplate" }, iron_boots = Item{ 0,"armorFeet","Iron Boots" };
			Item gold_helmet = Item{ 0,"armorHead","Golden Helmet" }, gold_chestplate = Item{ 0,"armorChest","Golden Chestplate" }, gold_boots = Item{ 0,"armorFeet","Golden Boots" };
			Item diamond_helmet = Item{ 0,"armorHead","Diamond Helmet" }, diamond_chestplate = Item{ 0,"armorChest","Diamond Chestplate" }, diamond_boots = Item{ 0,"armorFeet","Diamond Boots" };
		//weapons
			Item iron_sword = Item{ 10,"weapon","Iron Sword" }, gold_sword = Item{ 7,"weapon","Gold Sword" }, diamond_sword = Item{ 20,"weapon","Diamond Sword" };
	
	//entities
		//normal
			/*
			template:
			Entity  = Entity{ "monster","Attack damage:  points of blood\nHealth:  points of blood","",,,,vector<Item>{} };
			*/
			Entity zombie = Entity{ "monster","Attack damage: 2 points of blood\nHealth: 10 points of blood","Zombie",2,10,10,vector<Item>{air} };
			Entity piglin = Entity{ "monster","Attack damage: 4 points of blood\nHealth: 20 points of blood","Piglin",4,20,20,vector<Item>{gold_ingot} };
			Entity enderman = Entity{ "monster","Attack damage: 5 points of blood\nHealth: 20 points of blood","Enderman",5,20,20,vector<Item>{enderPearl} };
		//special
			Entity player = Entity{ "player","","",0,50,50,vector<Item>{air} };
			Entity warden = Entity{ "monster","Attack damage: 10 points of blood\nHealth: 100 points of blood","Warden",10,100,100,vector<Item>{air} };
			Entity wither = Entity{ "monster","Attack damage: 25 points of blood\nHealth: 300 points of blood","Wither",25,300,300,vector<Item>{air} };
			Entity enderDragon = Entity{ "monster","Attack damage: 40 points of blood\nHealth: 200 points of blood","Ender Dragon",40,200,200,vector<Item>{air} };
			Entity air_entity = Entity{ "","","",0,0,0,vector<Item>{air} };
			Entity playerFacingEntity;

			//dimensions
			Dimension deepDark = Dimension{ "Spawns Wardens","Deep_Dark",warden };
			Dimension nether = Dimension{ "Spawns Withers","Nether",wither };
			Dimension	end = Dimension{ "Spawns Ender Dragons","End",enderDragon };
			Dimension overworld = Dimension{ "A place to rest","Overworld",air_entity };
			Dimension currentDimension = overworld;
	//crafting recipes
		//armor
			/*
			template:
			craftingRecipe Helmet = { "armorHead",vector<Item>{ ,,,, },_helmet };
			craftingRecipe Chestplate = { "armorChest",vector<Item>{ ,,,,,,, },_chestplate };
			craftingRecipe Boots = { "armorFeet",vector<Item>{ ,,, },_boots };
			*/
			craftingRecipe ironHelmet = craftingRecipe{ "armorHead",vector<Item>{ iron_ingot,iron_ingot,iron_ingot,iron_ingot,iron_ingot },iron_helmet };
			craftingRecipe ironChestplate = craftingRecipe{ "armorChest",vector<Item>{ iron_ingot,iron_ingot,iron_ingot,iron_ingot,iron_ingot,iron_ingot,iron_ingot,iron_ingot },iron_chestplate };
			craftingRecipe ironBoots = craftingRecipe{ "armorFeet",vector<Item>{ iron_ingot,iron_ingot,iron_ingot,iron_ingot },iron_boots };
	
			craftingRecipe goldHelmet = craftingRecipe{ "armorHead",vector<Item>{ gold_ingot,gold_ingot,gold_ingot,gold_ingot,gold_ingot },gold_helmet };
			craftingRecipe goldChestplate = craftingRecipe{ "armorChest",vector<Item>{ gold_ingot,gold_ingot,gold_ingot,gold_ingot,gold_ingot,gold_ingot,gold_ingot,gold_ingot },gold_chestplate };
			craftingRecipe goldBoots = craftingRecipe{ "armorFeet",vector<Item>{ gold_ingot,gold_ingot,gold_ingot, },gold_boots };

			craftingRecipe diamondHelmet = craftingRecipe{ "armorHead",vector<Item>{ diamond,diamond,diamond,diamond,diamond },diamond_helmet };
			craftingRecipe diamondChestplate = craftingRecipe{ "armorChest",vector<Item>{ diamond,diamond,diamond,diamond,diamond,diamond,diamond,diamond },diamond_chestplate };
			craftingRecipe diamondBoots = craftingRecipe{ "armorFeet",vector<Item>{ diamond,diamond,diamond,diamond },diamond_boots };
		//weapons
			craftingRecipe ironSword = craftingRecipe{ "weapon",vector<Item>{stick,iron_ingot,iron_ingot},iron_sword };
			craftingRecipe goldSword = craftingRecipe{ "weapon",vector<Item>{stick,gold_ingot,gold_ingot},gold_sword };
			craftingRecipe diamondSword = craftingRecipe{ "weapon",vector<Item>{stick,diamond,diamond},diamond_sword };

	//vector of recipes
		vector<craftingRecipe> recipes = vector<craftingRecipe>{
			ironHelmet,ironChestplate,ironBoots,
			goldHelmet,goldChestplate,goldBoots,
			diamondHelmet,diamondChestplate,diamondBoots,
			ironSword,goldSword,diamondSword
		};
	//vector of dropped items
		vector<Item> droppedItems;

}
#endif // DEFINES_H
