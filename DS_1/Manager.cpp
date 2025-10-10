#include "Manager.h"
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "ArtistBSTNode.h"
#include "TitleBSTNode.h"

using namespace std;

// 공백과 CRLF(\r)를 양쪽에서 제거하는 도우미
static inline std::string trim_copy(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r");
    return s.substr(start, end - start + 1);
}

Manager::Manager() {
    flog.open("log.txt", std::ios::out | std::ios::trunc); // 기존 로그 파일이 있으면 덮어쓰기
}

Manager::~Manager() {
    if (fcmd.is_open()) {
        fcmd.close();
    }
    if (flog.is_open()) {
        flog.close();
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
            params = trim_copy(params);
            ADD(params);
        } else if (cmd == "QPOP") {
            QPOP();
        } else if (cmd == "SEARCH") {
            std::string params;
            std::getline(ss, params);
            params = trim_copy(params);
            SEARCH(params);
        } else if (cmd == "MAKEPL") {
            std::string params;
            std::getline(ss, params);
            params = trim_copy(params);
            MAKEPL(params);
        } else if (cmd == "PRINT") {
            std::string params;
            std::getline(ss, params);
            params = trim_copy(params);
            PRINT(params);
        } else if (cmd == "DELETE") {
            std::string params;
            std::getline(ss, params);
            params = trim_copy(params);
            DELETE(params);
        }
        // 다른 명령어들은 이곳에 추가될 수 있습니다.
    }
    fcmd.close();
}

void Manager::LOAD() {
	//Music_List.txt를 읽어서 MusicQueue에 push

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

    flog << "========LOAD========" << std::endl;
    std::string line;
    while (std::getline(musicList, line)) {
        std::stringstream ss(line);
        std::string artist, title, runtime;
        
        std::getline(ss, artist, '|');
        std::getline(ss, title, '|');
        std::getline(ss, runtime, '|');
        artist = trim_copy(artist);
        title = trim_copy(title);
        runtime = trim_copy(runtime);
        
        q.push(artist, title, runtime);
        flog << artist << "/" << title << "/" << runtime << std::endl;
    }
    
    flog << "====================" << std::endl;
    musicList.close();
    
}

void Manager::ADD(const std::string& params) {
	//MusicQueue에 data 추가 <가수이름> | <노래제목> | <재생시간>
    
    std::stringstream ss(params);
    std::string artist, title, runtime;

    if (!std::getline(ss, artist, '|') || !std::getline(ss, title, '|') || !std::getline(ss, runtime, '|')) {
        // 정보 누락 시 에러 처리
        flog << "========ERROR========" << std::endl;
        flog << 200 << std::endl;
        flog << "====================" << std::endl;
        return;
    }
    artist = trim_copy(artist);
    title = trim_copy(title);
    runtime = trim_copy(runtime);

    if (q.exist(artist, title)) {
        // 이미 곡이 존재할 경우 에러 처리
        flog << "========ERROR========" << std::endl;
        flog << 200 << std::endl;
        flog << "====================" << std::endl;
        return;
    }

    flog << "========ADD========" << std::endl;
    q.push(artist, title, runtime);
    flog << artist << "/" << title << "/" << runtime << std::endl;
    flog << "====================" << std::endl;
}

void Manager::QPOP() {
    
    if (q.empty()) {
        flog << "========ERROR========" << std::endl;
        flog << 300 << std::endl;
        flog << "====================" << std::endl;
        return;
    }
    flog << "========QPOP========" << std::endl;
    // 모든 큐 요소를 POP하여 BST 구성
    while (!q.empty()) {
        MusicQueueNode* node = q.pop();
        // parse runtime mm:ss -> seconds
        std::string rt = trim_copy(node->getRuntime());
        int mm = 0, ss = 0;
        size_t pos = rt.find(':');
        if (pos != std::string::npos) {
            mm = std::stoi(rt.substr(0, pos));
            ss = std::stoi(rt.substr(pos + 1));
        }
        int sec = mm * 60 + ss;

        // ArtistBST: 아티스트 기준 삽입 (중복 제목은 add_song에서 무시)
        ab.insert(node->getArtist(), node->getTitle(), sec);
        // TitleBST: 제목 기준 삽입 (동일 제목 내 동일 가수 중복은 addSong에서 무시)
        tb.insert(node->getTitle(), node->getArtist(), sec);
        delete node; // 큐에서 pop된 노드 해제
    }
    
    flog << "Success" << std::endl;
    flog << "====================" << std::endl;
}

void Manager::SEARCH(const std::string& params) {
    std::stringstream ss(params);
    std::string opt; ss >> opt;
    if (opt == "ARTIST") {
        std::string artist; std::getline(ss, artist);
        artist = trim_copy(artist);
        auto* node = ab.search(artist);
        if (!node) { flog << "========ERROR========\n400\n====================" << std::endl; return; }
        flog << "========SEARCH========" << std::endl;
        const auto& titles = node->get_title();
        const auto& times = node->get_rt();
        for (size_t i=0;i<titles.size();++i){ int s=times[i]; flog << artist << "/" << titles[i] << "/" << s/60 << ":" << std::setw(2) << std::setfill('0') << s%60 << "\n"; }
        flog << "====================" << std::endl; return;
    } else if (opt == "TITLE") {
        std::string title; std::getline(ss, title);
        title = trim_copy(title);
        auto* node = tb.search(title);
        if (!node) { flog << "========ERROR========\n400\n====================" << std::endl; return; }
        flog << "========SEARCH========" << std::endl;
        const auto& artists = node->getArtists();
        const auto& times = node->getRuntimes();
        for (size_t i=0;i<artists.size();++i){ int s=times[i]; flog << artists[i] << "/" << title << "/" << s/60 << ":" << std::setw(2) << std::setfill('0') << s%60 << "\n"; }
        flog << "====================" << std::endl; return;
    } else if (opt == "SONG") {
        std::string rest; std::getline(ss, rest);
        rest = trim_copy(rest);
        size_t bar = rest.find('|');
        if (bar==std::string::npos){ flog << "========ERROR========\n400\n====================" << std::endl; return; }
        std::string artist = trim_copy(rest.substr(0, bar));
        std::string title = trim_copy(rest.substr(bar+1));
        auto* node = ab.search(artist);
        if (!node) { flog << "========ERROR========\n400\n====================" << std::endl; return; }
        const auto& titles = node->get_title();
        const auto& times = node->get_rt();
        for (size_t i=0;i<titles.size();++i){ if (titles[i]==title){ flog << "========SEARCH========" << std::endl; int s=times[i]; flog<<artist<<"/"<<title<<"/"<<s/60<<":"<<std::setw(2)<<std::setfill('0')<<s%60<<"\n"; flog << "====================" << std::endl; return; } }
        flog << "========ERROR========\n400\n====================" << std::endl; return;
    }
    flog << "========ERROR========\n400\n====================" << std::endl;
}

void Manager::MAKEPL(const std::string& params) {
    std::stringstream ss(params); std::string opt; ss>>opt;
    auto print_tail = [&](){ flog << "Count : "<< pl.get_count() << " / 10\n"; int t=pl.run_time(); flog<<"Time : "<<t/60<<"min "<<t%60<<"sec\n"; flog << "====================" << std::endl; };
    if (opt=="ARTIST"){
        std::string artist; std::getline(ss, artist); artist = trim_copy(artist);
        auto* node = ab.search(artist); if(!node){ flog<<"========ERROR========\n500\n===================="<<std::endl; return; }
        const auto& titles=node->get_title(); const auto& times=node->get_rt();
        if (pl.get_count() + (int)titles.size() > 10){ flog<<"========ERROR========\n500\n===================="<<std::endl; return; }
        for(size_t i=0;i<titles.size();++i){ if(!pl.find_song(artist, titles[i])){ pl.insert_node(artist, titles[i], times[i]); } else { flog<<"========ERROR========\n500\n===================="<<std::endl; return; } }
        flog << "========MAKEPL========" << std::endl;
        flog << pl.print();
        print_tail(); return;
    } else if (opt=="TITLE"){
        std::string title; std::getline(ss,title); title = trim_copy(title);
        auto* node = tb.search(title); if(!node){ flog<<"========ERROR========\n500\n===================="<<std::endl; return; }
        const auto& artists=node->getArtists(); const auto& times=node->getRuntimes();
        if (pl.get_count() + (int)artists.size() > 10){ flog<<"========ERROR========\n500\n===================="<<std::endl; return; }
        for(size_t i=0;i<artists.size();++i){ if(!pl.find_song(artists[i], title)){ pl.insert_node(artists[i], title, times[i]); } else { flog<<"========ERROR========\n500\n===================="<<std::endl; return; } }
        flog << "========MAKEPL========" << std::endl;
        flog << pl.print();
        print_tail(); return;
    } else if (opt=="SONG"){
        std::string rest; std::getline(ss, rest); rest = trim_copy(rest);
        size_t bar=rest.find('|'); if(bar==std::string::npos){ flog<<"========ERROR========\n500\n===================="<<std::endl; return; }
        std::string artist=trim_copy(rest.substr(0,bar)), title=trim_copy(rest.substr(bar+1));
        auto* aNode = ab.search(artist); if(!aNode){ flog<<"========ERROR========\n500\n===================="<<std::endl; return; }
        const auto& titles=aNode->get_title(); const auto& times=aNode->get_rt();
        for(size_t i=0;i<titles.size();++i){ if(titles[i]==title){ if(pl.get_count()>=10 || pl.find_song(artist,title)){ flog<<"========ERROR========\n500\n===================="<<std::endl; return;} pl.insert_node(artist,title,times[i]); flog << "========MAKEPL========" << std::endl; flog << pl.print(); print_tail(); return; } }
        flog<<"========ERROR========\n500\n===================="<<std::endl; return;
    }
    flog<<"========ERROR========\n500\n===================="<<std::endl;
}

void Manager::PRINT(const std::string& params) {
    std::string p = trim_copy(params);
    if (p == "ARTIST") {
        if (ab.empty()) {
            flog << "========ERROR========" << std::endl;
            flog << 600 << std::endl;
            flog << "====================" << std::endl;
            return;
        }
        flog << "========PRINT========" << std::endl;
        flog << "ArtistBST" << std::endl;
        ab.print(flog);
    } else if (p == "TITLE") {
        if (tb.empty()) {
            flog << "========ERROR========" << std::endl;
            flog << 600 << std::endl;
            flog << "====================" << std::endl;
            return;
        }
        flog << "========PRINT========" << std::endl;
        flog << "TitleBST" << std::endl;
        tb.print(flog);
    } else if (p == "LIST") {
        if (!pl.exist()) { flog << "========ERROR========\n600\n====================" << std::endl; return; }
        flog << "========PRINT========" << std::endl;
        flog << pl.print();
        flog << "Count : "<< pl.get_count() << " / 10\n";
        int t = pl.run_time(); flog << "Time : "<< t/60 << "min "<< t%60 << "sec\n";
    } else {
        flog << "========ERROR========" << std::endl;
        flog << 600 << std::endl;
        flog << "====================" << std::endl;
        return;
    }
    flog << "====================" << std::endl;
}

void Manager::DELETE(const std::string& params) {
    std::stringstream ss(params); std::string opt; ss>>opt;
    auto success=[&](){ flog<<"========DELETE========"<<std::endl<<"Success\n===================="<<std::endl; };
    auto error=[&](){ flog<<"========ERROR========\n700\n===================="<<std::endl; };
    if (opt=="ARTIST"){
        std::string artist; std::getline(ss,artist); artist = trim_copy(artist);
        auto* node = ab.search(artist); if(!node){ error(); return; }
        // TitleBST와 PlayList에서도 해당 아티스트의 모든 곡 제거
        const auto& titles=node->get_title();
        for(const auto& t : titles){ tb.remove_song(t, artist); pl.delete_song(artist, t); }
        ab.delete_node(artist);
        success(); return;
    } else if (opt=="TITLE"){
        std::string title; std::getline(ss,title); title = trim_copy(title);
        auto* node = tb.search(title); if(!node){ error(); return; }
        const auto& artists=node->getArtists();
        for(const auto& a: artists){ ab.remove_song(a, title); pl.delete_song(a, title); }
        tb.delete_node(title);
        success(); return;
    } else if (opt=="LIST"){
        std::string rest; std::getline(ss,rest); rest = trim_copy(rest);
        size_t bar=rest.find('|'); if(bar==std::string::npos){ error(); return; }
        std::string artist=trim_copy(rest.substr(0,bar)), title=trim_copy(rest.substr(bar+1));
        if (!pl.delete_song(artist,title)) { error(); return; }
        success(); return;
    } else if (opt=="SONG"){
        std::string rest; std::getline(ss,rest); rest = trim_copy(rest);
        size_t bar=rest.find('|'); if(bar==std::string::npos){ error(); return; }
        std::string artist=trim_copy(rest.substr(0,bar)), title=trim_copy(rest.substr(bar+1));
        bool ok1 = ab.remove_song(artist,title);
        bool ok2 = tb.remove_song(title,artist);
        bool ok3 = pl.delete_song(artist,title);
        if (!(ok1||ok2||ok3)) { error(); return; }
        success(); return;
    }
    error();
}

void Manager::EXIT() {
    flog << "=======EXIT========" << std::endl;
    flog << "Success" << std::endl;
    flog << "===================" << std::endl;
}