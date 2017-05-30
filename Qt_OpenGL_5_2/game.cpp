#include "game.h"

Game::Game()
{
    lastFrameTime = QDateTime::currentMSecsSinceEpoch();
}

void Game::draw(QOpenGLShaderProgram &shader)
{
    for (int i = 0; i < DrawableObjects.size();i++)
    {
        //ImmovableObjects[i].Draw();
    }
}

void Game::step()
{

}

void Game::move()
{
    for (int i = 0; i < DrawableObjects.size();i++)
    {
        //MovableObjects[i].Position += MovableObjects[i].Motion;
    }
}

void Game::initializeGame(QOpenGLShaderProgram* shader, KeyboardManager* keyboardManager)
{
    this->keyboardManager = keyboardManager;

    loadModels();
    loadTextures();
    createEnviroment(shader);
    createPlayer(shader);

    //TEST
    player.getPosition().setX(20);
}

void Game::render(Camera& camera, Light& light, QMatrix4x4 pMatrix)
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glDisable(GL_CULL_FACE);
    skybox.draw(camera, light, pMatrix);
    f->glEnable(GL_CULL_FACE);

    envGenerator.draw(camera, light, pMatrix);
    star.draw(camera, light, pMatrix);
    player.draw(camera, light, pMatrix);
}

void Game::logic(Camera& camera)
{
    input();

    int deltaTime = QDateTime::currentMSecsSinceEpoch() - lastFrameTime;
    lastFrameTime = QDateTime::currentMSecsSinceEpoch();

    envGenerator.removeObjects(physics.checkCollisions(&star, envGenerator.GetObjects()));
    skybox.setPosition(player.getPosition());

    envGenerator.logic(player.getPosition(), deltaTime);
    star.logic(deltaTime);
    player.logic(deltaTime);
    updateCamera(camera);
}

void Game::loadModels()
{
    QVector<QString> modelsToLoad;
    modelsToLoad.push_back(":/Objects/skybox");
    modelsToLoad.push_back(":/Objects/planetoid");
    modelsToLoad.push_back(":/Objects/star");
    modelsToLoad.push_back(":/Objects/drone");
    objManager.loadAll(modelsToLoad);
}

void Game::loadTextures()
{
    QVector<QString> texturesToLoad;
    texturesToLoad.push_back(":/Textures/skybox");
    texturesToLoad.push_back(":/Textures/planetoid");
    texturesToLoad.push_back(":/Textures/star");
    texturesToLoad.push_back(":/Textures/drone");
    texturesManager.loadAll(texturesToLoad);
}

void Game::createEnviroment(QOpenGLShaderProgram* shader)
{
    envGenerator.init(&objManager, &texturesManager, shader);

    skybox.init(shader, objManager.getModel(":/Objects/skybox"),
                        texturesManager.getTexture(":/Textures/skybox"));
    skybox.getLightProperties().setAmbientColor(255,255,255,0);
    skybox.getLightProperties().setSpecularReflection(0);

    star.init(shader, objManager.getModel(":/Objects/star"),
                      texturesManager.getTexture(":/Textures/star"));
    star.getLightProperties().setAmbientColor(255,255,255,0);
    star.getLightProperties().setAmbientReflection(2);
    star.getRotationSpeed().setY(0.007f);
}

void Game::createPlayer(QOpenGLShaderProgram* shader)
{
    player.init(shader, &objManager, &texturesManager);
}

void Game::updateCamera(Camera& camera)
{
    camera.setPosition(player.getPosition());
    camera.setRotation(player.getRotation());
}

void Game::input()
{
    if(keyboardManager->isKeyPressed(Qt::Key::Key_W))
    {
        float dir = player.direction.y() + 0.02;
        if (dir >M_PI * 2) dir -= M_PI * 2;
        else if (dir < -M_PI * 2) dir += M_PI * 2;
        player.direction.setY(dir);
    }

    if(keyboardManager->isKeyPressed(Qt::Key::Key_S))
    {
        float dir = player.direction.y() - 0.02;
        if (dir > M_PI * 2) dir -= M_PI * 2;
        else if (dir < -M_PI * 2) dir += M_PI * 2;
        player.direction.setY(dir);
    }


    if(keyboardManager->isKeyPressed(Qt::Key::Key_A))
    {
        float dir = player.direction.x() + 0.05;
        if (dir >M_PI * 2) dir -= M_PI * 2;
        else if (dir < -M_PI * 2) dir += M_PI * 2;
        player.direction.setX(dir);
    }

    if (keyboardManager->isKeyPressed(Qt::Key::Key_D))
    {
        float dir = player.direction.x() - 0.05;
        if (dir > M_PI * 2) dir -= M_PI * 2;
        else if (dir < -M_PI * 2) dir += M_PI * 2;
        player.direction.setX(dir);
    }


    if(keyboardManager->isKeyPressed(Qt::Key::Key_Q))
    {

    }

    if(keyboardManager->isKeyPressed(Qt::Key::Key_E))
    {

    }

    if(keyboardManager->isKeyPressed(Qt::Key::Key_Space))
    {
        player.speed = player.maxspeed;
    }
}

void Game::pause()
{

}

void Game::resume()
{
    lastFrameTime = QDateTime::currentMSecsSinceEpoch();
}
