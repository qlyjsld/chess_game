#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <thread>
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Chess.h"

static GLFWwindow* window;
static Chess chess(window);

int main()
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(800, 800, "Chess", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "error" << std::endl;
    }

    float map_vertices[] = {
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f
    };

    float pawn_vertices[] = {
        -0.75f, -0.75f, 1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, -0.75f, 1.0f, 0.0f, 1.0f,

        -0.75f, -0.75f, 1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
        -0.75f, -1.0f, 1.0f, 1.0f, 0.0f
    };

    VertexArray map_va;
    VertexBuffer map_vb(map_vertices, sizeof(map_vertices));

    map_va.attrib<float>(3);
    map_va.attrib<float>(2);
    map_va.EnableAttrib();

    map_vb.Unbind();
    map_va.Unbind();

    VertexArray pawn_va;
    VertexBuffer pawn_vb(pawn_vertices, sizeof(pawn_vertices));

    pawn_va.attrib<float>(3);
    pawn_va.attrib<float>(2);
    pawn_va.EnableAttrib();

    pawn_vb.Unbind();
    pawn_va.Unbind();

    Shader shader("./res/shader/tri.shader");
    shader.Unbind();

    Texture map("./res/texture/chessmap.png");
    Texture outline("./res/texture/outline.png");
    Texture knockout("./res/texture/ko.png");

    // sprite sheet is better (load once instead of one by one) but there is no optimization problem so I leave it like this
    Texture player_pawn("./res/texture/chess_set/player/pawn.png");
    Texture bot_pawn("./res/texture/chess_set/bot/pawn.png");

    Texture player_king("./res/texture/chess_set/player/king.png");
    Texture bot_king("./res/texture/chess_set/bot/king.png");

    Texture player_queen("./res/texture/chess_set/player/queen.png");
    Texture bot_queen("./res/texture/chess_set/bot/queen.png");

    Texture player_rook("./res/texture/chess_set/player/rook.png");
    Texture bot_rook("./res/texture/chess_set/bot/rook.png");

    Texture player_knight("./res/texture/chess_set/player/knight.png");
    Texture bot_knight("./res/texture/chess_set/bot/knight.png");

    Texture player_bishop("./res/texture/chess_set/player/bishop.png");
    Texture bot_bishop("./res/texture/chess_set/bot/bishop.png");

    Texture step("./res/texture/chess_set/step.png");

    std::thread worker(&Chess::play, &chess);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        if (chess.end == true) {
            std::cout << "Press enter twice to close the window!" << std::endl;
            std::cin.get();
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        map_va.Bind();
        shader.Bind();
        map.Bind();
        glm::vec2 tmp(0.0f);
        shader.updateOffset("offset", tmp);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        map_va.Unbind();
        map.Unbind();

        pawn_va.Bind();
        for (auto& i : chess.chess_sets) {
            tmp.x = 0.25f * i.x;
            tmp.y = 0.25f * i.y;
            shader.updateOffset("offset", tmp);
            switch (i.type) {
            case (pawn_type::bot_bishop):
                bot_bishop.Bind();
                break;
            case (pawn_type::player_bishop):
                player_bishop.Bind();
                break;
            case (pawn_type::bot_king):
                bot_king.Bind();
                break;
            case (pawn_type::player_king):
                player_king.Bind();
                break;
            case (pawn_type::bot_rook):
                bot_rook.Bind();
                break;
            case (pawn_type::player_rook):
                player_rook.Bind();
                break;
            case (pawn_type::bot_queen):
                bot_queen.Bind();
                break;
            case (pawn_type::player_queen):
                player_queen.Bind();
                break;
            case (pawn_type::bot_knight):
                bot_knight.Bind();
                break;
            case (pawn_type::player_knight):
                player_knight.Bind();
                break;
            case (pawn_type::bot_pawn):
                bot_pawn.Bind();
                break;
            case (pawn_type::player_pawn):
                player_pawn.Bind();
                break;
            case (pawn_type::step):
                step.Bind();
                break;
            }
            glDrawArrays(GL_TRIANGLES, 0, 6);
            if (i.outline == true) {
                outline.Bind();
                glDrawArrays(GL_TRIANGLES, 0, 6);
            }
            if (i.knockout == true) {
                knockout.Bind();
                glDrawArrays(GL_TRIANGLES, 0, 6);
            }
        }
        pawn_va.Unbind();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
    worker.join();

    glfwTerminate();
    return 0;
}
