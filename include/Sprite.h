#include <glm/glm.hpp>
#include "Shader.h"
#include "Texture.h"
#include "Render.h"

class Sprite {

    public:
        Sprite(Texture *texture, Shader *shader, Render* renderer);
        ~Sprite();

        glm::vec2 position;
        glm::vec2 size;
        
        void draw(int windowWidth, int windowHeight, glm::vec2 position, glm::vec2 size, glm::vec2 rotation) const;


    private:
        Texture texture;
        Shader shader;
        Render renderer;
};