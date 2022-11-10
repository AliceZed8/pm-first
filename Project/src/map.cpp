#include "../inc/map.hpp"


Map::Map(sf::RenderWindow& render_window): r_window(render_window)
{
    vec_map = {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    xSize = vec_map[0].size();
    ySize = vec_map.size();

    for (unsigned int i = 0; i < ySize; i++) {
        for (unsigned int j = 0; j < xSize; j++) {
            sf::RectangleShape block({blockSize, blockSize});
            block.setPosition({(float) blockSize*j , (float) blockSize*i});

            if (vec_map[i][j]) block.setFillColor(sf::Color::White);
            else block.setFillColor(sf::Color::Black);

            vec_blocks.push_back(block);
        }
    }
}

void Map::draw() {
    for (unsigned int i = 0; i < vec_blocks.size(); i++) {
        r_window.draw(vec_blocks[i]);
    }
}

bool Map::checkMapCase(int x , int y) {
    if (vec_map[y][x]) return true;
    else return false;
}