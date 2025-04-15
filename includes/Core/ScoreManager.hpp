
/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji
** File description:
** prototyped
*/

#ifndef SCORE_HPP
#define SCORE_HPP
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <filesystem>
#include <map>
#include <algorithm>

class ScoreManager {
    struct Score {
        std::string playerName;
        int value;
        std::time_t timestamp;
        Score() : playerName(""), value(0), timestamp(std::time(nullptr)) {}
        Score(const std::string& name, int val, std::time_t time) 
            : playerName(name), value(val), timestamp(time) {}
    };

    private:
        std::string scoresDir;
        std::map<std::string, std::vector<Score>> gameScores;

    public:
        ScoreManager() : scoresDir("/tmp/arcade/scores/") {
            std::filesystem::create_directories(scoresDir);
        }

        std::vector<Score> loadScoresFromFile(const std::string& filename);
        void loadScores(const std::string& gameName);
        void saveScoresToFile(const std::vector<Score>& scores, const std::string& filename);
        void saveScores(const std::string& gameName);
        void addScore(const std::string& gameName, const std::string& playerName, int score);
        
        std::pair<std::string, int> getHighScore(const std::string& gameName);
        
        void loadAllScores(const std::vector<std::string>& gamePaths);
        
        std::string getScoreFileName(const std::string& gameName) const;
        
        void displayScores() const;
    };

#endif