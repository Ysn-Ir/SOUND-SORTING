#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <ctime>
#include <algorithm>
const int w = 600, l = 600;
const float width = 2.f;

void sort(std::vector<float>& wpos) {
    for (int i = 0; i < wpos.size(); i++) {
        for (int j = 0; j < wpos.size() - i + 1; j++) {
            if (wpos[j] < wpos[j + 1]) {
                float temp = wpos[j];
                wpos[j] = wpos[j + 1];
                wpos[j + 1] = temp;
            }
        }
    }
}

void shuffle(std::vector<float>& wpos, std::vector<float>& lpos, float width, int w) {
    for (int i = 0; i < w / width; i++) {
        wpos.push_back(width * i);
        lpos.push_back(l / (i+2) * width);
    }
    std::random_shuffle(wpos.begin(), wpos.end());
}

void setter(std::vector<sf::RectangleShape>* rec, std::vector<float>& wpos, std::vector<float>& lpos) {
    //temp rectangle
    sf::RectangleShape r;
    r.setFillColor(sf::Color::White);
    for (int i = 0; i < (w / (int)width); i++) {
        rec->push_back(r);
    }
    for (int i = 0; i < rec->size(); i++) {
       rec->at(i).setSize(sf::Vector2f(width, lpos[i]));
       rec->at(i).setPosition(sf::Vector2f(wpos[i], l));
    }
}

void update(std::vector<sf::RectangleShape>& rec, std::vector<float>& wpos) {
    for (int i = 0; i < rec.size(); i++)
        rec[i].setPosition(sf::Vector2f(wpos[i], l));
    sort(wpos);
}

void draw(sf::RenderWindow& window, const std::vector<sf::RectangleShape>& rec) {
    window.clear();
    for (const auto& i : rec) {
        window.draw(i);
    }
    window.display();
}

int main() {
    sf::RenderWindow window(sf::VideoMode(w, l), "window", sf::Style::Default);
    srand(time(nullptr));
    std::vector<float> wpos, lpos;
    std::vector<sf::RectangleShape> rec;
  setter(&rec, wpos, lpos);
    shuffle(wpos, lpos, width, w);
  

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
       /* update(rec, wpos);*/
        draw(window, rec);
    }

    return 0;
}
