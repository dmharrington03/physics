#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <cmath>
#include "headers.hpp"
#include "funcs.cpp"

const int width = 1200;

#define N 150
const int boxWidth = width / N;
#define IX(i, j) ((i) + (N + 2) * (j))
const int size = (N + 2) * (N + 2);

float u[size], v[size], u_prev[size], v_prev[size];
float dens[size], dens_prev[size];

// Sources:
float s[size];

const float visc = .001;
const float dt = 0.01;
float diff = .001;

sf::Vector2i pMousePos(0, 0);
sf::Vector2i mousePos(0, 0);
sf::Vector2i change(0, 0);
sf::Vector2i box(0, 0);


int main()
{
    sf::RenderWindow window(sf::VideoMode(width, width), "Fluid Sim");
    sf::RectangleShape rectGrid[N][N];

    // Populate Rectangle Array
    // Loop through x positions
    for (int i = 0; i < N; i++) {
        // Loop through y positions
        for (int j = 0; j < N; j++) {
            rectGrid[i][j].setSize(sf::Vector2f(boxWidth, boxWidth));
            rectGrid[i][j].setPosition(sf::Vector2f(i * boxWidth, j * boxWidth));
            rectGrid[i][j].setFillColor(sf::Color::Black);
        }
    }

    init_zero(size, s);
    init_zero(size, u);
    init_zero(size, v);
    init_zero(size, u_prev);
    init_zero(size, v_prev);
    init_zero(size, dens);
    init_zero(size, dens_prev);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Clear screen on space
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space)
                    init_zero(size, u);
                    init_zero(size, v);
                    init_zero(size, u_prev);
                    init_zero(size, v_prev);
                    init_zero(size, dens);
                    init_zero(size, dens_prev);
            }
        }

        window.clear();
        
        // Get user mouse input
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            mousePos = sf::Mouse::getPosition(window);
            change = mousePos - pMousePos;
            box = sf::Vector2i(floor(mousePos.x / boxWidth), floor(mousePos.y / boxWidth));
            box.x = constrain(box.x, 0, N);
            box.y = constrain(box.y, 0, N);
            dens[IX(box.x, box.y)] = 0.5f;
            u[IX(box.x, box.y)] = -change.x * 5;
            v[IX(box.x, box.y)] = -change.y * 5;
        }
        pMousePos = mousePos;

        vel_step(N, u, v, u_prev, v_prev, visc, dt);
        dens_step(N, dens, dens_prev, u, v, diff, dt);

        fade_dens(N, dens, 0.99f);

        // Loop through x positions
        for (int i = 0; i < N; i++) {
            // Loop through y positions
            for (int j = 0; j < N; j++) {
                float boxDens = constrain(dens[IX(i, j)] * 2000, 0, 255);
                rectGrid[i][j].setFillColor(sf::Color(boxDens, boxDens, boxDens));
                window.draw(rectGrid[i][j]);
            }
        }

        window.display();
    }

    return 0;
}
