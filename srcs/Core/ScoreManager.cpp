/*
** EPITECH PROJECT, 2025
** B-OOP-400-COT-4-1-arcade-james.gbetchedji [WSL: Ubuntu]
** File description:
** ScoreManager
*/

#include "../../includes/Core/ScoreManager.hpp"

std::string ScoreManager::getScoreFileName(const std::string& gameName) const
{
    return scoresDir + "Score_" + gameName + ".txt";
}

std::vector<ScoreManager::Score> ScoreManager::loadScoresFromFile(const std::string &filename)
{
    std::vector<Score> scores;
    std::ifstream file(filename);
    
    if (!file.is_open())
        return scores;
    
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream stream(line);
        std::string name;
        int value;
        std::time_t time;
    
        std::string label;
        std::getline(stream, label, ':');
        if (label != "Player")
            continue;
        
        stream >> name >> value >> time;
        scores.push_back(Score(name, value, time));
    }
    return scores;
}

void ScoreManager::loadScores(const std::string& gameName)
{
    std::string filename = getScoreFileName(gameName);
    gameScores[gameName] = loadScoresFromFile(filename);
}

void ScoreManager::loadAllScores(const std::vector<std::string>& gamePaths)
{
    for (const auto& path : gamePaths) {
        std::filesystem::path p(path);
        std::string filename = p.filename().string();
        size_t pos = filename.find("arcade_");
        if (pos != std::string::npos)
            filename = filename.substr(pos + std::string("arcade_").size());
        pos = filename.find(".so");
        if (pos != std::string::npos)
            filename = filename.substr(0, pos);
        
        if (filename != "ncurses" && filename != "sdl2" && filename != "sfml")
            loadScores(filename);
    }
}

void ScoreManager::saveScoresToFile(const std::vector<Score> &scores, const std::string &filename)
{
    std::filesystem::path filePath(filename);
    std::filesystem::create_directories(filePath.parent_path());
    
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open score file for writing: " << filename << std::endl;
        return;
    }
    
    for (const auto& score : scores)
        file << "Player: " << score.playerName << " " << score.value << " " << score.timestamp << "\n";
}

void ScoreManager::saveScores(const std::string& gameName)
{
    auto it = gameScores.find(gameName);
    if (it != gameScores.end()) {
        saveScoresToFile(it->second, getScoreFileName(gameName));
    }
}

void ScoreManager::addScore(const std::string& gameName, const std::string& playerName, int score)
{
    loadScores(gameName);
    
    Score newScore(playerName, score, std::time(nullptr));
    gameScores[gameName].push_back(newScore);
    
    std::sort(gameScores[gameName].begin(), gameScores[gameName].end(), 
        [](const Score &a, const Score &b) { return a.value > b.value; });
    
    saveScores(gameName);
}

std::pair<std::string, int> ScoreManager::getHighScore(const std::string& gameName)
{
    if (gameScores.find(gameName) == gameScores.end())
        loadScores(gameName);
    
    if (!gameScores[gameName].empty()) {
        const auto& topScore = gameScores[gameName][0];
        return {topScore.playerName, topScore.value};
    }
    
    return {"None", 0};
}

void ScoreManager::displayScores() const
{
    for (const auto& [game, scores] : gameScores) {
        std::cout << "Game: " << game << std::endl;
        for (const auto &score : scores) {
            std::cout << "Player: " << score.playerName << " - " << score.value 
                      << " (" << std::ctime(&score.timestamp) << ")";
        }
        std::cout << "------------------------" << std::endl;
    }
}
