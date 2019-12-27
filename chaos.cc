#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>				// srand
#include <time.h>				// setting srand seed
#include <SFML/Graphics.hpp>	// drawing graphics

typedef sf::CircleShape Vertex;
typedef std::vector<Vertex> Vertices;

unsigned random(unsigned s) { return (rand() % s); }

class chaosworld {
    public:
        chaosworld(unsigned v, unsigned f) : FRAME(0), FRAME_STOP(f) {
            srand(time(NULL));
            vertices = vertices_new(v);
            tracer = vertex_new(1, sf::Color::White);
        }
        void run() {
            // draw frame counter
            sf::Text frametxt; sf::Font font;
            font.loadFromFile("Ubuntu-C.ttf");
            frametxt.setFont(font);
            frametxt.setCharacterSize(20);
            frametxt.setPosition(SIZE_X-BORDER, 10);

            // draw window
            sf::RenderWindow window(sf::VideoMode(SIZE_X, SIZE_Y), "Chaos Game");
            while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed ||
                        (event.type == sf::Event::KeyPressed
                            && (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Q) ))
                        window.close();
                }
            /* draw objects in window */
                window.clear(sf::Color::Black);
                for (auto i : vertices) window.draw(i);
                for (auto i : tracer_history) window.draw(i);
                window.draw(frametxt);
            /* update world */
                if (FRAME_STOP == 0 || FRAME < FRAME_STOP) {
                    window.draw(tracer);
                    tracer_update();
                    frametxt.setString(std::to_string(++FRAME));
                }
                window.display();
            }
        }
    private:
        const Vertex vertex_new(unsigned size, const sf::Color& color) const {
            Vertex v(size);
            v.setFillColor(color);
            v.setPosition(random(SIZE_X-BORDER), random(SIZE_Y-BORDER));
            return v;
        }
        const Vertices vertices_new(unsigned v) const {
            Vertices output;
            for (; v > 0; --v)
                output.push_back(vertex_new(5, sf::Color(255, 0, 255))); // purple

            return output;
        }
        void tracer_update() {
            sf::Vector2f origin = tracer.getPosition();
            sf::Vector2f target = vertices.at(random(vertices.size())).getPosition();
            // calculate new tracer
            int x = ( target.x + origin.x ) / 2;
            int y = ( target.y + origin.y ) / 2;

            tracer_history.push_back(tracer);
            tracer.setPosition(x, y);
        }
    private:
        unsigned FRAME, FRAME_STOP;
        Vertex tracer;
        Vertices vertices, tracer_history;
        static const unsigned SIZE_X = 800, SIZE_Y = 600, BORDER = 50; // window settings
};

int main(int argc, char* argv[]) {
    unsigned v = 3, f = 0;

    switch(argc) {
        case 1: break;
        case 3: {
            if ( !(std::istringstream(argv[2]) >> f) || f < 0 ) {
                std::cout << "Invalid #frames. " << '\n';
                return 1;
            }
        }
        case 2: {
            if ( !(std::istringstream(argv[2]) >> v) || v < 0 ) {
                std::cout << "Invalid #vertices." << '\n';
                return 1;
            }
        }
        break;
        default:
            std::cout << "Use: " << argv[0] << " <#vertices> <#frames>" << std::endl;
            return 1;  
    }

    chaosworld c(v, f);
    c.run();

    return 0;
}