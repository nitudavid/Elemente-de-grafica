#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;

    spawnX = rand() % 700 + 300;
    direction = rand() % 2;
    speed = 300 * speedMultiplier;
    time = 0;

    if (direction == 1) {
        angle = M_PI / 6 * (1.0 + (std::rand() % 2));
    }
    else if (direction == 0) {
        direction = -1;
        angle = M_PI / 6 * (4.0 + (std::rand() % 2));
    }
    

    // TODO(student): Compute coordinates of a square's center, and store
    // then in the `cx` and `cy` class variables (see the header). Use
    // `corner` and `squareSide`. These two class variables will be used
    // in the `Update()` function. Think about it, why do you need them?
    cx = 300;
    cy = 300;
    // Initialize tx and ty (the translation steps)
    translateX = spawnX;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // Initialize angularStep
    angularStep = 0;

    Mesh* cer = object2D::CreateRectangle("cer", glm::vec3(0, 0, -6), 2000, 2000, glm::vec3(0, 0.1, 0.2));
    AddMeshToList(cer);

    Mesh* iarba = object2D::CreateRectangle("iarba", glm::vec3(0, 0, 30), 2000, 200, glm::vec3(0, 0.15, 0));
    AddMeshToList(iarba);

    Mesh* luna1 = object2D::CreateCircle("luna1", glm::vec3(0, 720, -5), 170, glm::vec3(0.89, 0.89, 0.89));
    AddMeshToList(luna1);

    Mesh* luna2 = object2D::CreateCircle("luna2", glm::vec3(0, 720, -4), 150, glm::vec3(0.86, 0.86, 0.86));
    AddMeshToList(luna2);

    Mesh* corpRata = object2D::CreateTriangle("corpRata", glm::vec3(0, 0, 0), glm::vec3(0, 140, 0), glm::vec3(290, 70, 0), glm::vec3(0.2, 0.1, 0));
    AddMeshToList(corpRata);

    Mesh* aripaSusRata = object2D::CreateTriangle("aripaSusRata", glm::vec3(70, 70, 0), glm::vec3(160, 70, 0), glm::vec3(115, 230, 0), glm::vec3(0.2, 0.1, 0));
    AddMeshToList(aripaSusRata);

    Mesh* aripaJosRata = object2D::CreateTriangle("aripaJosRata", glm::vec3(70, 70, 0), glm::vec3(160, 70, 0), glm::vec3(115, -90, 0), glm::vec3(0.2, 0.1, 0));
    AddMeshToList(aripaJosRata);

    Mesh* capRata = object2D::CreateCircle("capRata", glm::vec3(290, 70, 1), 50, glm::vec3(0, 0.2, 0));
    AddMeshToList(capRata);

    Mesh* ciocRata = object2D::CreateTriangle("ciocRata", glm::vec3(290, 78, -1), glm::vec3(290, 35, -1), glm::vec3(365, 47, -1), glm::vec3(0.9, 0.7, 0.2));
    AddMeshToList(ciocRata);

    Mesh* ochiAlbRata = object2D::CreateCircle("ochiAlbRata", glm::vec3(308, 77, 10), 13, glm::vec3(1, 1, 1));
    AddMeshToList(ochiAlbRata);

    Mesh* ochiNegruRata = object2D::CreateCircle("ochiNegruRata", glm::vec3(308, 77, 15), 11, glm::vec3(0, 0, 0));
    AddMeshToList(ochiNegruRata);

    Mesh* corpGlont = object2D::CreateRectangle("corpGlont", glm::vec3(1230, 630, 3), 20, 40, glm::vec3(0.25, 0.25, 0.25));
    AddMeshToList(corpGlont);

    Mesh* capGlont = object2D::CreateTriangle("capGlont", glm::vec3(1230, 670, 3), glm::vec3(1250, 670, 3), glm::vec3(1240, 690, 3), glm::vec3(0.25, 0.25, 0.25));
    AddMeshToList(capGlont);

    Mesh* corpGlontNegru = object2D::CreateRectangle("corpGlontNegru", glm::vec3(1230, 630, 5), 20, 40, glm::vec3(0, 0, 0));
    AddMeshToList(corpGlontNegru);

    Mesh* capGlontNegru = object2D::CreateTriangle("capGlontNegru", glm::vec3(1230, 670, 5), glm::vec3(1250, 670, 5), glm::vec3(1240, 690, 5), glm::vec3(0, 0, 0));
    AddMeshToList(capGlontNegru);

    Mesh* inima1 = object2D::CreateTriangle("inima1", glm::vec3(1250, 660, 3), glm::vec3(1190, 660, 3), glm::vec3(1220, 630, 3), glm::vec3(0.4, 0, 0.1));
    AddMeshToList(inima1);

    Mesh* inima2 = object2D::CreateTriangle("inima2", glm::vec3(1250, 660, 3), glm::vec3(1250, 690, 3), glm::vec3(1190, 660, 3), glm::vec3(0.4, 0, 0.1));
    AddMeshToList(inima2);

    Mesh* inima3 = object2D::CreateTriangle("inima3", glm::vec3(1190, 660, 3), glm::vec3(1190, 690, 3), glm::vec3(1250, 660, 3), glm::vec3(0.4, 0, 0.1));
    AddMeshToList(inima3);

    Mesh* inima1Neagra = object2D::CreateTriangle("inima1Neagra", glm::vec3(1250, 660, 5), glm::vec3(1190, 660, 5), glm::vec3(1220, 630, 5), glm::vec3(0, 0, 0));
    AddMeshToList(inima1Neagra);

    Mesh* inima2Neagra = object2D::CreateTriangle("inima2Neagra", glm::vec3(1250, 660, 5), glm::vec3(1250, 690, 5), glm::vec3(1190, 660, 5), glm::vec3(0, 0, 0));
    AddMeshToList(inima2Neagra);

    Mesh* inima3Neagra = object2D::CreateTriangle("inima3Neagra", glm::vec3(1190, 660, 5), glm::vec3(1190, 690, 5), glm::vec3(1250, 660, 5), glm::vec3(0, 0, 0));
    AddMeshToList(inima3Neagra);

    Mesh* scorWire = object2D::CreateRectangle("scorWire", glm::vec3(870, 630, 3), 380, 60, glm::vec3(0.6, 0, 0.6), false);
    AddMeshToList(scorWire);

    Mesh* scor = object2D::CreateRectangle("scor", glm::vec3(870, 630, 3), 23.75, 60, glm::vec3(0.3, 0, 0.3));
    AddMeshToList(scor);

    Mesh* endCredits = object2D::CreateRectangle("endCredits", glm::vec3(0, 0, 10), 1280, 720, glm::vec3(0, 0, 0.1));
    AddMeshToList(endCredits);

    Mesh* coroana1 = object2D::CreateRectangle("coroana1", glm::vec3(480, 260, 20), 320, 100, glm::vec3(1, 0.7, 0));
    AddMeshToList(coroana1);

    Mesh* coroana2 = object2D::CreateTriangle("coroana2", glm::vec3(480, 360, 20), glm::vec3(480, 500, 20), glm::vec3(640, 360, 20), glm::vec3(1, 0.7, 0));
    AddMeshToList(coroana2);

    Mesh* coroana3 = object2D::CreateTriangle("coroana3", glm::vec3(480, 360, 20), glm::vec3(640, 500, 20), glm::vec3(800, 360, 20), glm::vec3(1, 0.7, 0));
    AddMeshToList(coroana3);

    Mesh* coroana4 = object2D::CreateTriangle("coroana4", glm::vec3(800, 360, 20), glm::vec3(800, 500, 20), glm::vec3(640, 360, 20), glm::vec3(1, 0.7, 0));
    AddMeshToList(coroana4);

    Mesh* fataTrista1 = object2D::CreateCircle("fataTrista1", glm::vec3(640, 150, 15), 500, glm::vec3(0.7, 0.1, 0.1));
    AddMeshToList(fataTrista1);

    Mesh* fataTrista2 = object2D::CreateCircle("fataTrista2", glm::vec3(640, 100, 20), 400, glm::vec3(0, 0, 0.1));
    AddMeshToList(fataTrista2);

    Mesh* ochiTrist1 = object2D::CreateCircle("ochiTrist1", glm::vec3(530, 450, 20), 100, glm::vec3(0.7, 0.1, 0.1));
    AddMeshToList(ochiTrist1);

    Mesh* ochiTrist2 = object2D::CreateCircle("ochiTrist2", glm::vec3(750, 450, 20), 100, glm::vec3(0.7, 0.1, 0.1));
    AddMeshToList(ochiTrist2);
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    // TODO(student): Update steps for translation, rotation and scale,
    // in order to create animations. Use the class variables in the
    // class header, and if you need more of them to complete the task,
    // add them over there!
    
    time += 0.1;
    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["cer"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["iarba"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["luna1"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["luna2"], shaders["VertexColor"], modelMatrix);

    RenderMesh2D(meshes["corpGlont"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["capGlont"], shaders["VertexColor"], modelMatrix);
    if (glontFolosit >= 3) {
        RenderMesh2D(meshes["corpGlontNegru"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["capGlontNegru"], shaders["VertexColor"], modelMatrix);
    }

    modelMatrix *= transform2D::Translate(-40, 0);
    RenderMesh2D(meshes["corpGlont"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["capGlont"], shaders["VertexColor"], modelMatrix);
    if (glontFolosit >= 2) {
        RenderMesh2D(meshes["corpGlontNegru"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["capGlontNegru"], shaders["VertexColor"], modelMatrix);
    }

    modelMatrix *= transform2D::Translate(-40, 0);
    RenderMesh2D(meshes["corpGlont"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["capGlont"], shaders["VertexColor"], modelMatrix);
    if (glontFolosit >= 1) {
        RenderMesh2D(meshes["corpGlontNegru"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["capGlontNegru"], shaders["VertexColor"], modelMatrix);
    }

    modelMatrix *= transform2D::Translate(-80, 0);
    RenderMesh2D(meshes["inima1"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["inima2"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["inima3"], shaders["VertexColor"], modelMatrix);
    if (vietipierdute == 3) {
        RenderMesh2D(meshes["inima1Neagra"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["inima2Neagra"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["inima3Neagra"], shaders["VertexColor"], modelMatrix);
    }

    modelMatrix *= transform2D::Translate(-80, 0);
    RenderMesh2D(meshes["inima1"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["inima2"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["inima3"], shaders["VertexColor"], modelMatrix);
    if (vietipierdute == 2 || vietipierdute == 3) {
        RenderMesh2D(meshes["inima1Neagra"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["inima2Neagra"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["inima3Neagra"], shaders["VertexColor"], modelMatrix);
    }

    modelMatrix *= transform2D::Translate(-80, 0);
    RenderMesh2D(meshes["inima1"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["inima2"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["inima3"], shaders["VertexColor"], modelMatrix);
    if (vietipierdute == 1 || vietipierdute == 2 || vietipierdute == 3) {
        RenderMesh2D(meshes["inima1Neagra"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["inima2Neagra"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["inima3Neagra"], shaders["VertexColor"], modelMatrix);
    }

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(0, -75);
    RenderMesh2D(meshes["scorWire"], shaders["VertexColor"], modelMatrix);
    if (scor >= 1) {
        RenderMesh2D(meshes["scor"], shaders["VertexColor"], modelMatrix);
    }
    if (scor >= 2) {
        modelMatrix *= transform2D::Translate(23.75, 0);
        RenderMesh2D(meshes["scor"], shaders["VertexColor"], modelMatrix);
    }
    if (scor >= 3) {
        modelMatrix *= transform2D::Translate(23.75, 0);
        RenderMesh2D(meshes["scor"], shaders["VertexColor"], modelMatrix);
    }
    if (scor >= 4) {
        modelMatrix *= transform2D::Translate(23.75, 0);
        RenderMesh2D(meshes["scor"], shaders["VertexColor"], modelMatrix);
    }
    if (scor >= 5) {
        modelMatrix *= transform2D::Translate(23.75, 0);
        RenderMesh2D(meshes["scor"], shaders["VertexColor"], modelMatrix);
    }
    if (scor >= 6) {
        modelMatrix *= transform2D::Translate(23.75, 0);
        RenderMesh2D(meshes["scor"], shaders["VertexColor"], modelMatrix);
    }
    if (scor >= 7) {
        modelMatrix *= transform2D::Translate(23.75, 0);
        RenderMesh2D(meshes["scor"], shaders["VertexColor"], modelMatrix);
    }
    if (scor >= 8) {
        modelMatrix *= transform2D::Translate(23.75, 0);
        RenderMesh2D(meshes["scor"], shaders["VertexColor"], modelMatrix);
    }
    if (scor >= 9) {
        modelMatrix *= transform2D::Translate(23.75, 0);
        RenderMesh2D(meshes["scor"], shaders["VertexColor"], modelMatrix);
    }
    if (scor >= 10) {
        modelMatrix *= transform2D::Translate(23.75, 0);
        RenderMesh2D(meshes["scor"], shaders["VertexColor"], modelMatrix);
    }
    if (scor >= 11) {
        modelMatrix *= transform2D::Translate(23.75, 0);
        RenderMesh2D(meshes["scor"], shaders["VertexColor"], modelMatrix);
    }
    if (scor >= 12) {
        modelMatrix *= transform2D::Translate(23.75, 0);
        RenderMesh2D(meshes["scor"], shaders["VertexColor"], modelMatrix);
    }
    if (scor >= 13) {
        modelMatrix *= transform2D::Translate(23.75, 0);
        RenderMesh2D(meshes["scor"], shaders["VertexColor"], modelMatrix);
    }
    if (scor >= 14) {
        modelMatrix *= transform2D::Translate(23.75, 0);
        RenderMesh2D(meshes["scor"], shaders["VertexColor"], modelMatrix);
    }
    if (scor >= 15) {
        modelMatrix *= transform2D::Translate(23.75, 0);
        RenderMesh2D(meshes["scor"], shaders["VertexColor"], modelMatrix);
    }
    if (scor >= 16) {
        modelMatrix *= transform2D::Translate(23.75, 0);
        RenderMesh2D(meshes["scor"], shaders["VertexColor"], modelMatrix);
    }

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Rotate(angle);
    modelMatrix *= glm::mat3(1, 0, 0, 0, direction, 0, 0, 0, 1);
    modelMatrix *= transform2D::Scale(0.6, 0.6);

    RenderMesh2D(meshes["corpRata"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["capRata"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["ochiAlbRata"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["ochiNegruRata"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["ciocRata"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Rotate(angle);
    modelMatrix *= glm::mat3(1, 0, 0, 0, direction, 0, 0, 0, 1);
    modelMatrix *= transform2D::Translate(70 * 0.6, 70 * 0.6);
    modelMatrix *= transform2D::Rotate(angularStep);
    modelMatrix *= transform2D::Translate(-70 * 0.6, -70 * 0.6);
    modelMatrix *= transform2D::Scale(0.6, 0.6);
    
    static bool fata = true;
    if (fata)
        angularStep += deltaTimeSeconds * 1.5;
    else
        angularStep -= deltaTimeSeconds * 1.5;
    if (angularStep >= 0.5) {
        fata = false;
    }
    if (angularStep < 0)
        fata = true;

    RenderMesh2D(meshes["aripaSusRata"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Rotate(angle);
    modelMatrix *= glm::mat3(1, 0, 0, 0, direction, 0, 0, 0, 1);
    modelMatrix *= transform2D::Translate(70 * 0.6, 70 * 0.6);
    modelMatrix *= transform2D::Rotate(-angularStep);
    modelMatrix *= transform2D::Translate(-70 * 0.6, -70 * 0.6);
    modelMatrix *= transform2D::Scale(0.6, 0.6);
    RenderMesh2D(meshes["aripaJosRata"], shaders["VertexColor"], modelMatrix);

    if (scor == 16) {
        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["endCredits"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["coroana1"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["coroana2"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["coroana3"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["coroana4"], shaders["VertexColor"], modelMatrix);
    }

    if (vietipierdute == 3) {
        modelMatrix = glm::mat3(1);
        RenderMesh2D(meshes["endCredits"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["fataTrista1"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["fataTrista2"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["ochiTrist1"], shaders["VertexColor"], modelMatrix);
        RenderMesh2D(meshes["ochiTrist2"], shaders["VertexColor"], modelMatrix);
    }

    if (time < 80 && lovita == false) {

        translateX += deltaTimeSeconds * cos(angle) * speed;
        translateY += deltaTimeSeconds * sin(angle) * speed;
        if (translateX > 1280) {
            angle = M_PI - angle;
            translateX = 1199;
            direction = -1;
        }
        if (translateX < 0) {
            angle = M_PI - angle;
            translateX = 0;
            direction = 1;
        }
        if (translateY > 720) {
            angle = -angle;
            translateY = 719;
        }
        if (translateY < 0) {
            angle = -angle;
            translateY = 0;
        }
    }
    else if (time < 80 && lovita == true) {
        
        time = 0;
        translateY -= deltaTimeSeconds * speed;
        angle = M_PI / 2;
        if (translateY <= -300) {
            speedMultiplierCalc++;
            scor++;
            if (speedMultiplierCalc % 5 == 0) {
                speedMultiplier += 1;
            }
            glontFolosit = 0;
            speed = 300 * speedMultiplier;
            lovita = false;
            spawnX = rand() % 700 + 300;
            translateX = spawnX;
            translateY = 0;
            direction = rand() % 2;
            time = 0;

            if (direction == 1) {
                angle = M_PI / 6 * (1.0 + (std::rand() % 2));
            }
            else if (direction == 0) {
                direction = -1;
                angle = M_PI / 6 * (4.0 + (std::rand() % 2));
            }
        }
    }
    else if(time >= 80 && lovita == false) {
        
        translateY += deltaTimeSeconds * speed;
        angle = M_PI / 2;
        if (translateY >= 1000) {
            vietipierdute++;
            speedMultiplierCalc++;
            if (speedMultiplierCalc % 5 == 0) {
                speedMultiplier += 1;
            }
            glontFolosit = 0;
            speed = 300 * speedMultiplier;
            spawnX = rand() % 700 + 300;
            translateX = spawnX;
            translateY = 0;
            direction = rand() % 2;
            time = 0;

            if (direction == 1) {
                angle = M_PI / 6 * (1.0 + (std::rand() % 2));
            }
            else if (direction == 0) {
                direction = -1;
                angle = M_PI / 6 * (4.0 + (std::rand() % 2));
            }
        }
    }
    
}

void Tema1::resetSpawn(float deltaTimeSeconds){

}

void rataEvadeaza(float deltaTimeSeconds) {

}



void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (button == 1) {
        if (mouseX > translateX && mouseX < translateX + 200) {
            if (mouseY > 720 - translateY -200 && mouseY < 720 - translateY + 100) {
                if (glontFolosit < 3) {
                    lovita = true;
                    glontFolosit++;
                }
            }
        }
        else glontFolosit++;
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}