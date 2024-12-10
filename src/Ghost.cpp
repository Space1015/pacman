
#include <Ghost.hpp>
Ghost::Ghost(sf::Texture &texture, Type type) { // Use member initializer list
    charSprite.setTexture(texture);
    charSprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
    speed = 99;
}
pair<int, int> Ghost::goToCoords(GameMap gameMap, double px, double py){
    px = (int)(px/16); py = (int)(py/16);
    int x = charSprite.getPosition().x/16;
    int y = charSprite.getPosition().y/16;
    queue<pair<int, int>> q;
    bool visited [36][28];
    pair<int, int> prev[36][28];
    for (int i = 0; i < 36; i++) {
        for (int j = 0; j < 28; j++) {
            visited[i][j] = false;
        }
    }
    visited[y][x] = true;
    prev[y][x] = {y,x};
    q.push({y,x});
    while(!q.empty()){
        pair<int, int> s = q.front(); q.pop();
        if(s.first == py && s.second == px){ //if at pacman
            while(prev[s.first][s.second] != prev[prev[s.first][s.second].first][prev[s.first][s.second].second]){
                s = prev[s.first][s.second];
            }
            return {s.first * 16, s.second * 16};
        }
        if(iempty(s.second, s.first - 1, gameMap) && !visited[s.first - 1][s.second]){
            visited[s.first - 1][s.second] = true;
            prev[s.first - 1][s.second] = s;
            q.push({s.first - 1, s.second});
        }
        if(iempty(s.second, s.first + 1, gameMap) && !visited[s.first + 1][s.second]){
            visited[s.first + 1][s.second] = true;
            prev[s.first + 1][s.second] = s;
            q.push({s.first + 1, s.second});
        }
        if(iempty((s.second + 27) % 28, s.first, gameMap) && !visited[s.first][(s.second + 27) % 28]){
            visited[s.first][(s.second + 27) % 28] = true;
            prev[s.first][(s.second + 27) % 28] = s;
            q.push({s.first,(s.second + 27) % 28});
        }
        if(iempty((s.second + 1) % 28, s.first, gameMap) && !visited[s.first][(s.second + 1) % 28]){
            visited[s.first][(s.second + 1) % 28] = true;
            prev[s.first][(s.second + 1) % 28] = s;
            q.push({s.first,(s.second + 1) % 28});
        }
    }
    return {0,0};
}
void Ghost::move(GameMap gameMap, pair<int, int> s, double deltaTime){
    if(charSprite.getPosition().x == s.second){
        if(charSprite.getPosition().y < s.first){
            charSprite.setPosition(charSprite.getPosition().x, min((double)s.first, charSprite.getPosition().y + deltaTime * speed));
        }else{
            charSprite.setPosition(charSprite.getPosition().x, max((double)s.first, charSprite.getPosition().y - deltaTime * speed));
        }
    }else if(charSprite.getPosition().x == s.second){
        if(charSprite.getPosition().x < s.second){
            charSprite.setPosition(min((double)s.second, charSprite.getPosition().x + deltaTime * speed), charSprite.getPosition().y);
        }else{
            charSprite.setPosition(max((double)s.second, charSprite.getPosition().x - deltaTime * speed), charSprite.getPosition().y);
        }
    }else if(abs(s.second - charSprite.getPosition().x) > abs(s.first - charSprite.getPosition().y)){
        if(charSprite.getPosition().x < s.second){
            charSprite.setPosition(min((double)s.second, charSprite.getPosition().x + deltaTime * speed), charSprite.getPosition().y);
        }else{
            charSprite.setPosition(max((double)s.second, charSprite.getPosition().x - deltaTime * speed), charSprite.getPosition().y);
        }
    }else{
        if(charSprite.getPosition().y < s.first){
            charSprite.setPosition(charSprite.getPosition().x, min((double)s.first, charSprite.getPosition().y + deltaTime * speed));
        }else{
            charSprite.setPosition(charSprite.getPosition().x, max((double)s.first, charSprite.getPosition().y - deltaTime * speed));
        }
    }
}