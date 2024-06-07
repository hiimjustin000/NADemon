#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/LevelInfoLayer.hpp>
class $modify(NDLevelInfoLayer, LevelInfoLayer) {
    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge)) return false;

        if (level->m_stars.value() == 0 && level->m_starsRequested == 10) m_difficultySprite->updateDifficultyFrame(6, GJDifficultyName::Short);

        return true;
    }

    void levelDownloadFinished(GJGameLevel* level) {
        LevelInfoLayer::levelDownloadFinished(level);

        if (level->m_stars.value() == 0 && level->m_starsRequested == 10) m_difficultySprite->updateDifficultyFrame(6, GJDifficultyName::Short);
    }

    void levelUpdateFinished(GJGameLevel* level, UpdateResponse response) {
        LevelInfoLayer::levelUpdateFinished(level, response);

        if (level->m_stars.value() == 0 && level->m_starsRequested == 10) m_difficultySprite->updateDifficultyFrame(6, GJDifficultyName::Short);
    }

    void likedItem(LikeItemType type, int id, bool liked) {
        LevelInfoLayer::likedItem(type, id, liked);

        if (m_level->m_stars.value() == 0 && m_level->m_starsRequested == 10) m_difficultySprite->updateDifficultyFrame(6, GJDifficultyName::Short);
    }
};

#include <Geode/modify/LevelCell.hpp>
class $modify(NDLevelCell, LevelCell) {
    void loadFromLevel(GJGameLevel* level) {
        LevelCell::loadFromLevel(level);

        if (auto difficultyContainer = m_mainLayer->getChildByID("difficulty-container")) {
            if (level->m_stars.value() == 0 && level->m_starsRequested == 10)
                static_cast<GJDifficultySprite*>(difficultyContainer->getChildByID("difficulty-sprite"))->updateDifficultyFrame(6, GJDifficultyName::Short);
        }
    }
};
