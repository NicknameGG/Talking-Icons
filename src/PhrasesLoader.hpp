#pragma once

#include <vector>
#include <string>
#include <Geode/utils/web.hpp>
#include <Geode/loader/Event.hpp>

using namespace geode::prelude;

class PhrasesLoader {
public:
    static std::vector<std::string> phrases;
    static std::vector<std::string> deathPhrases;
    static EventListener<web::WebTask> phraseListener;
    static EventListener<web::WebTask> deathPhraseListener;
public:
    static std::vector<std::string> split(const std::string& str, char delim) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(str);
        while (std::getline(tokenStream, token, delim)) {
            tokens.push_back(token);
        }
        return tokens;
    }
    static void loadPhrases();
    static std::string getRandomPhrase();
    static std::string getRandomDeathPhrase();
};