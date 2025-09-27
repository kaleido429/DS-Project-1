#include "Manager.h"
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>

using namespace std;

Manager::Manager() {
    flog.open("log.txt", std::ios::app);
}

Manager::~Manager() {
    if (fcmd.is_open()) {
        fcmd.close();
    }
}

void Manager::run(const char* command) {
	// command.txt 파일 읽어서 명령 수행
    fcmd.open(command);
    if (!fcmd.is_open()) {
        flog << "Error: command file not found" << std::endl;
        return;
    }
    std::string line;
    while (std::getline(fcmd, line)) {
        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "LOAD") {
            LOAD();
        } else if (cmd == "ADD") {
            // "ADD" 명령어 뒤의 모든 문자열을 ADD 함수에 전달
            std::string params;
            std::getline(ss, params);
            // 앞쪽 공백 제거
            if (!params.empty() && params[0] == ' ') {
                params = params.substr(1);
            }
            ADD(params);
        }
        // 다른 명령어들은 이곳에 추가될 수 있습니다.
    }
    fcmd.close();
}

void Manager::LOAD() {
	//Music_List.txt를 읽어서 MusicQueue에 push
    flog << "========LOAD========" << std::endl;

    if (!q.empty()) {
        flog << "========ERROR========" << std::endl;
        flog << 100 << std::endl;
        flog << "====================" << std::endl;
        return;
    }

    std::ifstream musicList("Music_List.txt");
    if (!musicList.is_open()) {
        flog << "========ERROR========" << std::endl;
        flog << 100 << std::endl;
        flog << "====================" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(musicList, line)) {
        std::stringstream ss(line);
        std::string artist, title, runtime;
        
        std::getline(ss, artist, '|');
        std::getline(ss, title, '|');
        std::getline(ss, runtime, '|');
        
        q.push(artist, title, runtime);
        flog << artist << "/" << title << "/" << runtime << std::endl;
    }
    
    flog << "====================" << std::endl;
    musicList.close();
    
}

void Manager::ADD(const std::string& params) {
	//MusicQueue에 data 추가 <가수이름> | <노래제목> | <재생시간>
    flog << "========ADD========" << std::endl;
    
    std::stringstream ss(params);
    std::string artist, title, runtime;

    if (!std::getline(ss, artist, '|') || !std::getline(ss, title, '|') || !std::getline(ss, runtime, '|')) {
        // 정보 누락 시 에러 처리
        flog << "========ERROR========" << std::endl;
        flog << 200 << std::endl;
        flog << "====================" << std::endl;
        return;
    }

    if (q.exist(artist, title)) {
        // 이미 곡이 존재할 경우 에러 처리
        flog << "========ERROR========" << std::endl;
        flog << 200 << std::endl;
        flog << "====================" << std::endl;
        return;
    }

    q.push(artist, title, runtime);
    flog << artist << "/" << title << "/" << runtime << std::endl;
    flog << "====================" << std::endl;
}

void Manager::QPOP() {
	
}

void Manager::SEARCH() {
	
}

void Manager::MAKEPL() {
	
}

void Manager::PRINT() {
	
}

void Manager::DELETE() {
	
}

void Manager::EXIT() {

}