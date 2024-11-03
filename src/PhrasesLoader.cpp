#include "PhrasesLoader.hpp"

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

EventListener<web::WebTask> PhrasesLoader::phraseListener;
EventListener<web::WebTask> PhrasesLoader::deathPhraseListener;

void PhrasesLoader::loadPhrases() {
    auto phraseRequest = web::WebRequest();

    phraseListener.bind([] (web::WebTask::Event* event) {
        if (auto res = event->getValue()) {
            PhrasesLoader::phrases = PhrasesLoader::split(res->string().unwrapOr("Error parsing"), '\n');
        }
    });

    phraseListener.setFilter(phraseRequest.get("https://raw.githubusercontent.com/NicknameGG/talking-icons-files/main/phrases.txt"));

    auto deathPhraseRequest = web::WebRequest();

    deathPhraseListener.bind([] (web::WebTask::Event* event) {
        if (auto res = event->getValue()) {
            PhrasesLoader::deathPhrases = PhrasesLoader::split(res->string().unwrapOr("Error parsing"), '\n');
        }
    });

    deathPhraseListener.setFilter(deathPhraseRequest.get("https://raw.githubusercontent.com/NicknameGG/talking-icons-files/main/death.txt"));
}

std::string PhrasesLoader::getRandomPhrase() {
  return phrases[rand() % phrases.size()];
}

std::string PhrasesLoader::getRandomDeathPhrase() {
  return deathPhrases[rand() % deathPhrases.size()];
}