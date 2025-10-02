#pragma once
#include "MusicQueue.h"
#include "TitleBST.h"
#include "ArtistBST.h"
#include "PlayList.h"
#include <fstream>

using namespace std;

class Manager {
private:
	MusicQueue q;
	ArtistBST ab;
	TitleBST tb;
	PlayList pl;
	ifstream fcmd;
	ofstream flog;
public:
	Manager();
	~Manager();

	void run(const char* command);

	void LOAD();
	void ADD(const std::string& Line);
	void QPOP();
	void SEARCH(const std::string& params);
	void MAKEPL(const std::string& params);
	void PRINT(const std::string& params);
	void DELETE(const std::string& params);
	void EXIT();

};