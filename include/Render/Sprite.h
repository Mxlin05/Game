#include <glm/glm.hpp>
#include "Shader.h"
#include "Texture.h"
#include "Render.h"

enum class SpriteType {
    Generic,
    Enemy,
    Player,
    UI
};


class Sprite {

    public:
        Sprite(Texture *texture, Shader *shader, Render* renderer, SpriteType type = SpriteType::Generic);
        ~Sprite();

        SpriteType type = SpriteType::Generic;
        glm::vec2 position;
        glm::vec2 size;

        bool isSelected = false;
        bool isHovered = false;
        glm::vec3 colorTint;

        void draw(int windowWidth, int windowHeight, glm::vec2 position, glm::vec2 size, glm::vec2 rotation) const;
        void draw_battle(int windowWidth, int windowHeight, glm::vec2 position, glm::vec2 size, glm::vec2 rotation, bool isPlayer) const;


    private:
        Texture texture;
        Shader shader;
        Render renderer;
};