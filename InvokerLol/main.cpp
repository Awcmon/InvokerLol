#include <iostream>
#define WINVER 0x0500
#include <windows.h>
#include <vector>
#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

class Key {
public:
	Key(short _keyIn, vector<short> _keyOutSeq);
	void HandleEvents();
private:
	bool keyDown;
	short keyIn;
	vector<short> keyOutSeq;
};

Key::Key(short _keyIn, vector<short> _keyOutSeq)
{
	keyIn = _keyIn;
	keyOutSeq = _keyOutSeq;
	keyDown = false;
}

void Key::HandleEvents()
{
	if (GetAsyncKeyState(keyIn) && !keyDown)
	{
		for (int i = 0; i < (int)keyOutSeq.size(); i++)
		{
			//Structure for the keyboard event
			INPUT ip;

			//Set up the INPUT structure
			ip.type = INPUT_KEYBOARD;
			ip.ki.time = 0;
			ip.ki.wVk = 0; //We're doing scan codes instead
			ip.ki.dwExtraInfo = 0;

			//This let's you do a hardware scan instead of a virtual keypress
			ip.ki.dwFlags = KEYEVENTF_SCANCODE;
			ip.ki.wScan = keyOutSeq[i];  //Set a unicode character to use (A)

			/*
			Sleep(300 + (rand() % 100));
			keybd_event((unsigned char)keyOutSeq[i], 0, 0, 0);
			Sleep(10 + (rand() % 100));
			keybd_event((unsigned char)keyOutSeq[i], 0, KEYEVENTF_KEYUP, 0);
			Sleep(300 + (rand() % 100));
			*/

			Sleep(10 + (rand() % 10));

			//Send the press
			SendInput(1, &ip, sizeof(INPUT));

			Sleep(10 + (rand() % 10));

			//Prepare a keyup event
			ip.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
			SendInput(1, &ip, sizeof(INPUT));

			Sleep(20 + (rand() % 25));
		}
		keyDown = true;
	}
	if (!GetAsyncKeyState(keyIn) && keyDown)
	{
		keyDown = false;
	}
}

int main()
{
	srand(time(NULL));

	std::vector<short> KeyVec;
	std::vector<Key> Keys;

	//cold snap qqqr
	Keys.push_back(Key(VK_NUMPAD7, { 0x10, 0x10, 0x10, 0x13 } ));
	//ghost walk qqwr
	Keys.push_back(Key(VK_NUMPAD4, { 0x10, 0x10, 0x11, 0x13 }));
	//icewall qqer
	Keys.push_back(Key(VK_NUMPAD1, { 0x10, 0x10, 0x12, 0x13 }));
	//emp wwwr
	Keys.push_back(Key(VK_NUMPAD8, { 0x11, 0x11, 0x11, 0x13 }));
	//tornado wwqr
	Keys.push_back(Key(VK_NUMPAD5, { 0x11, 0x11, 0x10, 0x13 }));
	//alacrity wwwer
	Keys.push_back(Key(VK_NUMPAD2, { 0x11, 0x11, 0x12, 0x13 }));
	//sunstrike eeer
	Keys.push_back(Key(VK_NUMPAD9, { 0x12, 0x12, 0x12, 0x13 }));
	//forge spirit eeqr
	Keys.push_back(Key(VK_NUMPAD6, { 0x12, 0x12, 0x10, 0x13 }));
	//chaos meteor eewr
	Keys.push_back(Key(VK_NUMPAD3, { 0x12, 0x12, 0x11, 0x13 }));
	//deafening blast qwer
	Keys.push_back(Key(VK_NUMPAD0, { 0x10, 0x11, 0x12, 0x13 }));

	while (1)
	{
		for (int i = 0; i < (int)Keys.size(); i++)
		{
			Keys[i].HandleEvents();
		}
	}

	return 0;
}
