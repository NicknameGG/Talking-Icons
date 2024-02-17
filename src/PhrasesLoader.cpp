#include "PhrasesLoader.hpp"
#include <Geode/utils/web.hpp>

using namespace geode::prelude;

std::vector<std::string> PhrasesLoader::phrases = {
	"Hello!",
	"Im here so you don't get division by 0"
};

std::vector<std::string> PhrasesLoader::deathPhrases = {
	"wow, mean.",
	"you're so mean",
	"I knew that you hated me, but I subestimated how much.",
	"you're a bad person",
	":(",
    "I'm not mad, I'm just disappointed",
    "Everytime you kill me, I die a little inside",
    "Are you happy now?",
    "Go ahead, kill me again. I have nothing left to live for.",
    "I'm not even mad, I'm impressed.",
    "Look at what you've done.",
    "Very funny.",
    "Stop it.",
    
};

void PhrasesLoader::loadPhrases() {
  web::AsyncWebRequest()
      .fetch("https://raw.githubusercontent.com/NicknameGG/talking-icons-files/"
             "main/phrases.txt")
      .text()
      .then([](std::string text) {
        phrases = PhrasesLoader::split(text, '\n');
      });

    web::AsyncWebRequest()
      .fetch("https://raw.githubusercontent.com/NicknameGG/talking-icons-files/"
             "main/death.txt")
      .text()
      .then([](std::string text) {
        deathPhrases = PhrasesLoader::split(text, '\n');
      });
}

std::string PhrasesLoader::getRandomPhrase() {
  return phrases[rand() % phrases.size()];
}

std::string PhrasesLoader::getRandomDeathPhrase() {
  return deathPhrases[rand() % deathPhrases.size()];
}