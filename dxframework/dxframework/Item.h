#pragma once
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <windows.h>
#include <iostream>
#include <string>

#pragma comment(lib, "Strmiids.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "xinput.lib")
#define SAFE_RELEASE(x) if(x){x->Release(); x = 0;}

using namespace std;

class Item
{

private:
	string	name; // name of the key
	bool		haveItem;	//							
	bool		renderKey;	// render key if player has it in the hud

 public:

	 // need to create item
	Item();
		
	// need to name the item

	//set name of item
	void setItem(string s);

	//return the item name
	string getItemName();

	// Check if player has possesition
	bool PlayerHaveItem(haveKey);

	//If item created add to array of items
	bool NeedNewItemArray(bool newItem);

	//have hud render if the player has item
	bool RenderKey(bool renderKey);


	~Item(void);
};

