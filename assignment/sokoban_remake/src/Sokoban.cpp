#include "Sokoban.hpp"


SB::Sokoban::Sokoban() {
    auto wallTexture = sf::Texture{};
    auto boxTexture = sf::Texture{};
    auto groundTexture = sf::Texture{};
    auto groundStorageTexture = sf::Texture{};
    wallTexture.loadFromFile(TILESET_DIR + "block_06.png");
    boxTexture.loadFromFile(TILESET_DIR + "crate_03.png");
    groundTexture.loadFromFile(TILESET_DIR + "ground_01.png");
    groundStorageTexture.loadFromFile(TILESET_DIR + "ground_04.png");

    tile_textures_[TileChar::Player] = groundTexture;
    tile_textures_[TileChar::EmptySpace] = groundTexture;
    tile_textures_[TileChar::Wall] = wallTexture;
    tile_textures_[TileChar::Box] = boxTexture;
    tile_textures_[TileChar::Storage] = groundStorageTexture;
    tile_textures_[TileChar::BoxStorage] = boxTexture;

    auto playerUpTexture = sf::Texture{};
    auto playerDownTexture = sf::Texture{};
    auto playerLeftTexture = sf::Texture{};
    auto playerRightTexture = sf::Texture{};
    playerUpTexture.loadFromFile(TILESET_DIR + "player_08.png");
    playerDownTexture.loadFromFile(TILESET_DIR + "player_05.png");
    playerLeftTexture.loadFromFile(TILESET_DIR + "player_20.png");
    playerRightTexture.loadFromFile(TILESET_DIR + "player_17.png");

    player_textures_[Direction::Up] = playerUpTexture;
    player_textures_[Direction::Down] = playerDownTexture;
    player_textures_[Direction::Left] = playerLeftTexture;
    player_textures_[Direction::Right] = playerRightTexture;

    text_font_.loadFromFile(FONT_DIR + "roboto-regular.ttf");
}

void SB::Sokoban::movePlayer(const Direction dir) {
    if (isWon()) {
        return;
    }

    // Change player's orientation
    player_dir_ = dir;

    // auto& currTileChar = tileAt(player_loc_);
    switch (const auto nextCoord = Sokoban::nextCoord(player_loc_, dir); tileAt(nextCoord)) {
        case TileChar::EmptySpace:
            player_loc_ = nextCoord;
            break;
        case TileChar::BoxStorage:
        case TileChar::Box: {
            const auto [movable, boxNextCoord] = testBoxNextCoord(nextCoord, dir);
            if (!movable) {
                break;
            }
            player_loc_ = nextCoord;
            moveBox(nextCoord, boxNextCoord);
            break;
        }
        default:
            break;
    }
}

bool SB::Sokoban::isWon() const {
    return num_boxes_storage == num_boxes || num_boxes_storage == num_storages;
}

void SB::Sokoban::reset() {
    num_boxes_storage = initial_num_boxes_storage;
    player_loc_ = initial_player_loc_;
    player_dir_ = Direction::Down;
    map_ = initial_map_;
}

void SB::Sokoban::draw(sf::RenderTarget& target, const sf::RenderStates states) const {
    // Draw the map
    for (unsigned row = 0; row < size_.y; row++) {
        for (unsigned col = 0; col < size_.x; col++) {
            auto tile_char = map_.at(col).at(row);
            auto texture = tile_textures_.at(tile_char);
            auto sprite = sf::Sprite(texture);
            sprite.setPosition(
                static_cast<float>(col * TILE_SIZE), static_cast<float>(row * TILE_SIZE));
            target.draw(sprite, states);
        }
    }

    // Draw the player
    const auto texture = player_textures_.at(player_dir_);
    auto sprite = sf::Sprite(texture);
    sprite.setPosition(
        static_cast<float>(player_loc_.x * TILE_SIZE),
        static_cast<float>(player_loc_.y * TILE_SIZE));
    target.draw(sprite, states);

    // If the player wins, display the "YOU WIN!" text in the middle of the window
    if (isWon()) {
        auto winText = sf::Text{};
        winText.setFont(text_font_);
        winText.setString("YOU WIN!");
        winText.setFillColor(sf::Color::Black);
        winText.setCharacterSize(100);

        auto targetSize = sf::Vector2f{ target.getSize() };
        auto textBounds = winText.getGlobalBounds();
        winText.setPosition(
            targetSize.x / 2 - textBounds.width / 2, targetSize.y / 2 - textBounds.height / 2);

        target.draw(winText, states);
    }
}

sf::Vector2u SB::Sokoban::nextCoord(const sf::Vector2u& coord, const Direction dir) {
    switch (dir) {
        case Direction::Up:
            return { coord.x, coord.y - 1 };
        case Direction::Down:
            return { coord.x, coord.y + 1 };
        case Direction::Left:
            return { coord.x - 1, coord.y };
        case Direction::Right:
            return { coord.x + 1, coord.y };
        default:
            return coord;
    }
}

std::pair<bool, sf::Vector2u>
SB::Sokoban::testBoxNextCoord(const sf::Vector2u& boxCoord, const Direction dir) const {
    const auto nextCoord = Sokoban::nextCoord(boxCoord, dir);
    if (nextCoord.x >= size_.x || nextCoord.y >= size_.y) {
        return { false, boxCoord };
    }
    if (tileAtConst(nextCoord) == TileChar::Box || tileAtConst(nextCoord) == TileChar::Wall) {
        return { false, boxCoord };
    }

    return { true, nextCoord };
}

void SB::Sokoban::moveBox(const sf::Vector2u& boxCoord, const sf::Vector2u& boxNextCoord) {
    auto& boxTileChar = tileAt(boxCoord);
    auto& boxNextTileChar = tileAt(boxNextCoord);
    if (boxTileChar == TileChar::Box) {
        boxTileChar = TileChar::EmptySpace;
    } else if (boxTileChar == TileChar::BoxStorage) {
        boxTileChar = TileChar::Storage;
        num_boxes_storage--;
    }

    if (boxNextTileChar == TileChar::EmptySpace) {
        boxNextTileChar = TileChar::Box;
    } else if (boxNextTileChar == TileChar::Storage) {
        boxNextTileChar = TileChar::BoxStorage;
        num_boxes_storage++;
    }
}

std::ostream& SB::operator<<(std::ostream& os, const Sokoban& sokoban) {
    os << sokoban.size_.y << " " << sokoban.size_.x << std::endl;
    for (unsigned row = 0; row < sokoban.size_.y; row++) {
        for (unsigned col = 0; col < sokoban.size_.x; col++) {
            os << static_cast<char>(sokoban.map_[col][row]);
        }
        os << std::endl;
    }

    return os;
}

std::istream& SB::operator>>(std::istream& is, Sokoban& sokoban) {
    is >> sokoban.size_.y >> sokoban.size_.x;

    for (unsigned col = 0; col < sokoban.size_.x; col++) {
        sokoban.initial_map_.emplace_back(sokoban.size_.y);
    }

    for (unsigned row = 0; row < sokoban.size_.y; row++) {
        for (unsigned col = 0; col < sokoban.size_.x; col++) {
            char c;
            is >> c;
            const auto tileChar = static_cast<TileChar>(c);
            sokoban.initial_map_[col][row] = tileChar;

            if (tileChar == TileChar::Player) {
                sokoban.initial_player_loc_ = { col, row };
                sokoban.initial_map_[col][row] = TileChar::EmptySpace;
            }

            if (tileChar == TileChar::Box) {
                sokoban.num_boxes++;
            }

            if (tileChar == TileChar::Storage) {
                sokoban.num_storages++;
            }

            if (tileChar == TileChar::BoxStorage) {
                sokoban.num_boxes++;
                sokoban.num_storages++;
                sokoban.initial_num_boxes_storage++;
            }
        }
    }

    sokoban.reset();

    return is;
}
