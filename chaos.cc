#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>				// srand
#include <time.h>				// setting srand seed
#include <unistd.h>				// usleep
#include <SFML/Graphics.hpp>	// drawing graphics

// window settings
static const int SIZE_X = 800;
static const int SIZE_Y = 600;
static const int BORDER = 50;

int random(int s) { return (rand() % s); }

class chaosworld {
    public:
        chaosworld(int v, int f);
        void draw();
    private:
        std::vector<sf::CircleShape> vertices_create(int v);
        sf::CircleShape tracer_create();
        void tracer_update();
    private:
        int FRAME;
        int FRAME_STOP;
        std::vector<sf::CircleShape> vertices;
        std::vector<sf::CircleShape> tracer_history;
        sf::CircleShape tracer;
};

chaosworld::chaosworld(int v, int f) {
    FRAME = 0;
    FRAME_STOP = f;
    srand (time(NULL));
    vertices = vertices_create(v);
    tracer = tracer_create();
}

// returns a randomly positioned point
sf::CircleShape chaosworld::tracer_create() {
    sf::CircleShape t(1);
    t.setFillColor(sf::Color(255, 255, 255));
    t.setPosition(random(SIZE_X-BORDER), random(SIZE_Y-BORDER));
    return t;
}

// returns vector containing v randomly positioned vertices
std::vector<sf::CircleShape> chaosworld::vertices_create(int v) {
    std::vector<sf::CircleShape> output;
    for (; v > 0; --v) {
        sf::CircleShape shape(5);
        shape.setFillColor(sf::Color(255, 0, 255)); // white
        shape.setPosition(random(SIZE_X-BORDER), random(SIZE_Y-BORDER));
        output.push_back(shape);
    }
    return output;
}

// calculates and updates new tracer position
void chaosworld::tracer_update() {
    sf::Vector2f origin = tracer.getPosition();
    sf::Vector2f target = vertices.at(random(vertices.size())).getPosition();
    // calculate new tracer
    int x = ( target.x + origin.x ) / 2;
    int y = ( target.y + origin.y ) / 2;

    tracer_history.push_back(tracer);   // save old tracer
    tracer.setPosition(x, y);
}

// creates window and starts game
void chaosworld::draw() {
    // draw frame counter
    sf::Text frametxt;
    sf::Font font;
    font.loadFromFile("Ubuntu-C.ttf");
    frametxt.setFont(font);
    frametxt.setCharacterSize(20);
    frametxt.setPosition(760, 10);

    // draw window
    sf::RenderWindow window(sf::VideoMode(SIZE_X, SIZE_Y), "Chaos Game");
    while (window.isOpen()) {
    /* close window request check */
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
    /* draw objects in window */
        window.clear(sf::Color::Black);
        for (auto i : vertices) window.draw(i);
        for (auto i : tracer_history) window.draw(i);
        window.draw(frametxt);
    /* update world */
        if (FRAME < FRAME_STOP) {
            window.draw(tracer);
            tracer_update();
            frametxt.setString(std::to_string(++FRAME));
        }
        window.display();
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Use: " << argv[0] << " <#vertices> <#frames>" << std::endl;
        return 1;  
    }

    std::istringstream ss1(argv[1]);
    std::istringstream ss2(argv[2]);

    int v, f;
    if ( !(ss1 >> v) || v < 0 ) {
        std::cout << "Invalid #vertices." << '\n';
        return 1;
    }
    if ( !(ss2 >> f) || f < 0 ) {
    	std::cout << "Invalid #frames. " << '\n';
        return 1;
    }

    chaosworld c(v, f);
    c.draw();

    return 0;
}