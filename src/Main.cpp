#include <GL/glut.h>
#include "Game.h"
#include "Character.h"
#include <iostream>

Character character;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    Game::getInstance().render();
    glutSwapBuffers();
}

void passiveMotion(int x, int y)
{
    Game::getInstance().handleMouseMotion(x, y);
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    Game::getInstance().handleMouseClick(button, state, x, y);
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    std::cout << "Key pressed: " << key << std::endl;
    float distance = 7.0f; // Distance the character will move
    auto& character = Game::getInstance().getCharacter();
    auto& map = Game::getInstance().getMap();

    switch (key)
    {
    case 27: // ESC key
        Game::getInstance().togglePause();
        break;
    case 'w':
    case 'W':
        character.moveUp(distance, map);
        break;
    case 's':
    case 'S':
        character.moveDown(distance, map);
        break;
    case 'a':
    case 'A':
        character.moveLeft(distance, map);
        break;
    case 'd':
    case 'D':
        character.moveRight(distance, map);
        break;
    case 'g':
    case 'G':
        character.getPoints(map);
        break;
    case 'j':
    case 'J':
        character.shoot();
        break;
    }
    glutPostRedisplay();
}

void handleSpecialKeyPress(int key, int x, int y) {
    float distance = 7.0f; // Distance the character will move
    auto& character = Game::getInstance().getCharacter();
    auto& map = Game::getInstance().getMap();

    switch (key) {
        case GLUT_KEY_UP:
            character.moveUp(distance, map);
            break;
        case GLUT_KEY_DOWN:
            character.moveDown(distance, map);
            break;
        case GLUT_KEY_LEFT:
            character.moveLeft(distance, map);
            break;
        case GLUT_KEY_RIGHT:
            character.moveRight(distance, map);
            break;
    }
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 812, 0, 588);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(1.0, 1.0, 1.0, 1.0); // Fundo branco

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void timer(int value)
{
    Game &game = Game::getInstance();
    if (game.getState() == GameState::PLAY)
    {
        game.getMosquito().movimentacao(); // Atualiza a posição do mosquito
    }
    glutPostRedisplay();          // Redispara a renderização
    glutTimerFunc(100, timer, 0); // Redefine o temporizador para 100ms
}

void update(int value) {
    Game::getInstance().update();
    character.updateProjectiles();
    glutTimerFunc(16, update, 0); // Chamar update a cada 16ms (~60fps)
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(812, 588);
    glutCreateWindow("Aedes Combat: Viagem pelas estacoes.");

    init();

    glutDisplayFunc(display);
    glutPassiveMotionFunc(passiveMotion);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);   // Adicionar manipulador de teclado
    glutTimerFunc(100, timer, 0); // Inicializa o temporizador para movimentação do mosquito
    glutSpecialFunc(handleSpecialKeyPress); 
    glutTimerFunc(16, update, 0); // Iniciar o loop de atualização

    glutMainLoop();
    return 0;
}

