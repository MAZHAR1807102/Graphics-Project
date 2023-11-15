//
//  main.cpp
//  3D Object Drawing
//
//  Created by Nazirul Hasan on 4/9/23.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "pointLight.h"
#include "cube.h"
#include "stb_image.h"
#include "sphere.h"


#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);
void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);
void bed(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void Room1(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void Room2(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
//void table(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void Table(Cube& cube, Shader& lightingShader, glm::mat4 alTogether);
void Human(Sphere& sphere, Shader& lightingShader, glm::mat4 altogether);
long long nCr(int n, int r);
void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L);
unsigned int hollowBezier(GLfloat ctrlpoints[], int L);
void curve(Shader& lightingShader, glm::mat4 altogether);
void Fan(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);

vector <float> cntrlPoints;
vector <float> coordinates;
vector <float> normals;
vector <int> indices;
vector <float> vertices;
const double pi = 3.14159265389;
const int nt = 100;
const int ntheta = 20;
bool showControlPoints = true;
bool loadBezierCurvePoints = true;
bool showHollowBezier = false;
bool lineMode = false;
unsigned int bezierVAO;
glm::mat4 modelB = glm::mat4(1.0f);

bool humanMove = false;
float r = 0.0;
bool fanOn = false;
// settings
const unsigned int SCR_WIDTH = 1900;
const unsigned int SCR_HEIGHT = 1000;

// modelling transform
float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;




// camera
Camera camera(glm::vec3(0.0f, 3.1f, 35.2f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float eyeX = 0.0, eyeY = 1.0, eyeZ = 1.0;
float lookAtX = 0.0, lookAtY = 0.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);


// positions of the point lights
glm::vec3 pointLightPositions[] = {
    glm::vec3(10.0f,  5.0f,  -9.50f),
    glm::vec3(-4.50f,  5.0f,  -9.50f),
    glm::vec3(-4.50f,  5.0f,  9.50f),
    glm::vec3(-10.0f,  3.0f, 5.50f),
    glm::vec3(-15.0f,  15.0f, 25.50f)
};


//glm::vec3(-0.5, 1, -0.5)


PointLight pointlight1(

    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
    1.0f, 1.0f, 1.0f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    1       // light number
);
PointLight pointlight2(

    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,  // position
    0.5f, 0.5f, 0.5f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    2       // light number
);
PointLight pointlight3(

    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,  // position
    0.5f, 0.5f, 0.5f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    3       // light number
);
 PointLight pointlight4(

    pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z,  // position
    0.5f, 0.5f, 0.5f,     // ambient
    1.0f, 1.0f, 1.0f,     // diffuse
    1.0f, 1.0f, 1.0f,        // specular
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f, //k_q
    4       // light number
);
 PointLight pointlight5(
 pointLightPositions[4].x, pointLightPositions[4].y, pointLightPositions[4].z,  // position
     0.5f, 0.5f, 0.5f,     // ambient
     10.0f, 10.0f, 10.0f,     // diffuse
     1.0f, 1.0f, 1.0f,        // specular
     1.0f,   //k_c
     0.09f,  //k_l
     0.032f, //k_q
     5       // light number
     );


// light settings
bool onOffToggle = false;
bool onOffToggle1 = false;
bool donOffToggle = false;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;


// timing
float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Computer Graphics Laboratory", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    glClearColor(0.215f, 0.215f, 0.215f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapInterval(0);
    glfwSwapBuffers(window);


    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    //Shader lightingShader("vertexShaderForGouraudShading.vs", "fragmentShaderForGouraudShading.fs");
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");
    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");

    string diffuseMapPath = "table3.jpg";
    string specularMapPath = "table3.jpg";


    unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 5.0f, 1.0f);

    string diffuseMapPath4 = "bigtable.jpg";
    string specularMapPath4 = "bigtable.jpg";


    unsigned int diffMap4 = loadTexture(diffuseMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap4 = loadTexture(specularMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube5 = Cube(diffMap4, specMap4, 32.0f, 0.0f, 0.0f, 5.0f, 1.0f);

   string  diffuseMapPath1 = "grass2.png";
   string specularMapPath1 = "grass2.png";

    unsigned int diffMap1 = loadTexture(diffuseMapPath1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap1 = loadTexture(specularMapPath1.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube1 = Cube(diffMap1, specMap1, 40.0f, 0.0f, 0.0f, 10.0f, 10.0f); 


    string  diffuseMapPathConc = "bricksDif.jpg";
    string specularMapPathconc = "bricksSpec.jpg";

    unsigned int diffMap2 = loadTexture(diffuseMapPathConc.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap2 = loadTexture(specularMapPathconc.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube2 = Cube(diffMap2, specMap2, 40.0f, 0.0f, 0.0f, 1.50f, .750f);

    diffuseMapPathConc = "bricksDif.jpg";
     specularMapPathconc = "bricksSpec.jpg";

     diffMap2 = loadTexture(diffuseMapPathConc.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
     specMap2 = loadTexture(specularMapPathconc.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube3 = Cube(diffMap2, specMap2, 40.0f, 0.0f, 0.0f, 2.50f, 1.250f);


    string diffuseMapPathBan = "Banner.png";
    string specularMapPathBan = "Banner.png";

    unsigned int diffMapBan = loadTexture(diffuseMapPathBan.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMapBan = loadTexture(specularMapPathBan.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube6 = Cube(diffMapBan, specMapBan, 40.0f, 0.0f, 0.0f, 1.0f, 1.0f);
    
    string wood = "table2.jpg";
    unsigned int wood_tex = loadTexture(wood.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube cube4 = Cube(wood_tex, wood_tex, 40.0f, 0.0f, 0.0f, 2.0f, 1.0f);
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    float cube_vertices[] = {
        // positions      // normals
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };


     cntrlPoints = {
        
        -0.1417f, 2.1853f, 5.1000f,
        -0.6104f, 1.7675f, 5.1000f,
        -0.7438f, 1.2529f, 5.1000f,
        -0.7708f, 0.8412f, 5.1000f,
        -0.6938f, 0.4446f, 5.1000f,
        -0.5188f, 0.1237f, 5.1000f,
        -0.2771f, -0.0852f, 5.1000f,
        -0.1542f, -0.1669f, 5.1000f
    };

    unsigned int cubeVAO, cubeVBO, cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // vertex normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);

    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


    Sphere sphere = Sphere();

    //ourShader.use();
    //lightingShader.use();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.8f, 0.9f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // be sure to activate shader when setting uniforms/drawing objects
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);

        // point light 1
        pointlight1.setUpPointLight(lightingShader);
        // point light 2
        pointlight2.setUpPointLight(lightingShader);
        // point light 3
       pointlight3.setUpPointLight(lightingShader);
         //point light 4
       pointlight4.setUpPointLight(lightingShader);
       //point light 5
       pointlight5.setUpPointLight(lightingShader);

        lightingShader.setVec3("diectionalLight.directiaon", 2.5f, 3.0f, -0.50f);
        lightingShader.setVec3("diectionalLight.ambient", .2, .2, .2);
        lightingShader.setVec3("diectionalLight.diffuse", 1.0f, 1.0f, .8f);
        lightingShader.setVec3("diectionalLight.specular", 1.0f, 1.0f, 1.0f);



       
        lightingShader.setBool("dlighton", true);

       // donOffToggle = true;
        lightingShader.setVec3("spotlight.position", 2.5, 3.0, -0.5);
        lightingShader.setVec3("spotlight.direction", 0, -1, 0);
        lightingShader.setVec3("spotlight.ambient", .2, .2, .2);
        lightingShader.setVec3("spotlight.diffuse", .8f, .8f, .8f);
        lightingShader.setVec3("spotlight.specular", 1.0f, 1.0f, 1.0f);
        lightingShader.setFloat("spotlight.k_c", 1.0f);
        lightingShader.setFloat("spotlight.k_l", 0.09);
        lightingShader.setFloat("spotlight.k_q", 0.032);
        lightingShader.setFloat("cos_theta", glm::cos(glm::radians(5.5f)));
        lightingShader.setBool("spotlighton", donOffToggle);


        //pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,  // position
        //    1.0f, 1.0f, 1.0f,     // ambient
        //    1.0f, 1.0f, 1.0f,      // diffuse
        //    1.0f, 1.0f, 1.0f,        // specular
        //    1.0f,   //k_c
        //    0.09f,  //k_l
        //    0.032f, //k_q
        //    1,       // light number
        //    glm::cos(glm::radians(20.5f)),
        //    glm::cos(glm::radians(25.0f)),
        //    0, -1, 0
        // 
       

        // activate shader
        lightingShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShader.setMat4("projection", projection);

        // camera/view transformation
        glm::mat4 view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShader.setMat4("view", view);

        // Modelling Transformation
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
/*  
        ourShader.use();
        ourShader.setMat4("model", model);
        Cube genCube = Cube();
        genCube.drawCube(ourShader, model, 1.0, 1.0, 1.0);


        ourShader.use();
        ourShader.setMat4("model", model);
        Fan(cubeVAO, ourShader, model);
        */
        lightingShader.setMat4("model", model);

        //glBindVertexArray(cubeVAO);
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 36);



        //SPHERE
        glm::mat4 modelForSphere = glm::mat4(1.0f);
        translateMatrix = glm::translate(identityMatrix, glm::vec3(2.55, 2.50, 1.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0, 1.0, 1.0));
       // modelForSphere = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        lightingShader.setMat4("model", modelForSphere);
        modelForSphere = glm::translate(model, glm::vec3(-1.0f, 0.0f, 0.0f));
        modelForSphere = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
      //  sphere.drawSphere(lightingShader, modelForSphere);

        //Human(sphere, lightingShader, modelForSphere);




        lightingShader.setMat4("model", model);
        curve(lightingShader, model);
/* 
        //beziere curve
       float rotateAngle_ZB = pi / 2.0;
        identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrixB, rotateXMatrixB, rotateYMatrixB, rotateZMatrixB, scaleMatrixB;
        translateMatrixB = glm::translate(identityMatrix, glm::vec3(-10.0, 0.0, 0.0));
        rotateXMatrixB = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrixB = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrixB = glm::rotate(identityMatrix, glm::radians(rotateAngle_ZB), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrixB = glm::scale(identityMatrix, glm::vec3(3.0, 10.0, 2.0));
        modelB = translateMatrixB * rotateXMatrixB * rotateYMatrixB * rotateZMatrixB * scaleMatrixB;
       
        lightingShader.setMat4("model", modelB);

        if (loadBezierCurvePoints)
        {
            bezierVAO = hollowBezier(cntrlPoints.data(), ((unsigned int)cntrlPoints.size() / 3) - 1);
            loadBezierCurvePoints = false;
            showHollowBezier = true;
        }
        if (showHollowBezier)
        {
            lightingShader.use();
            lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.0f, 1.0f));
            lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.0f, 1.0f));
            lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
            lightingShader.setFloat("material.shininess", 32.0f);

            glBindVertexArray(bezierVAO);
            glDrawElements(GL_TRIANGLES,                    // primitive type
                (unsigned int)indices.size(),          // # of indices
                GL_UNSIGNED_INT,                 // data type
                (void*)0);                       // offset to indices

            // unbind VAO
            glBindVertexArray(0);
        }

        */

        //Room1(cubeVAO, lightingShader, model);

        glm::mat4 model1;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-15.5, translate_Y, translate_Z));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        model1 = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        lightingShader.setMat4("model", model1);
       // Room2(cubeVAO, lightingShader, model1);
        //table(cubeVAO, lightingShader, model);
        //bed(cubeVAO, lightingShader, model);

        //Texture

        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);

        // pass projection matrix to shader (note that in this case it could change every frame)
       // projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //glm::mat4 projection = glm::ortho(-2.0f, +2.0f, -1.5f, +1.5f, 0.1f, 100.0f);
        lightingShaderWithTexture.setMat4("projection", projection);

        // camera/view transformation
      //  view = camera.GetViewMatrix();
        //glm::mat4 view = basic_camera.createViewMatrix();
        lightingShaderWithTexture.setMat4("view", view);
/* 
        // Modelling Transformation
        identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
*/
        lightingShaderWithTexture.use();
        // point light 1
        pointlight1.setUpPointLight(lightingShaderWithTexture);
        // point light 2
        pointlight2.setUpPointLight(lightingShaderWithTexture);
        // point light 3
        pointlight3.setUpPointLight(lightingShaderWithTexture);
        // point light 4
        pointlight4.setUpPointLight(lightingShaderWithTexture);

         pointlight5.setUpPointLight(lightingShaderWithTexture);





        //BigTable
        glm::mat4 modelMatrixForContainer = glm::mat4(1.0f);
        glm::mat4 translateTexture = glm::mat4(1.0f);
        glm::mat4 scaleTexture = glm::mat4(1.0f);
        scaleTexture = glm::scale(model, glm::vec3(0.5f, 5.0f, 20.0f));
        translateTexture = glm::translate(model, glm::vec3(-5.0f, 0.90f, -2.8f));
        scaleTexture = glm::scale(model, glm::vec3(14.0f, 1.55f, 2.0f));
        modelMatrixForContainer = translateTexture * scaleTexture;
        cube.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

       
       translateTexture = glm::translate(model, glm::vec3(-5.0f, 2.4f, -2.8f));
       scaleTexture = glm::scale(model, glm::vec3(14.50f, .10f, 2.2f));
       modelMatrixForContainer = translateTexture * scaleTexture;
       cube5.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //Main surface

        //scaleTexture = glm::scale(model, glm::vec3(20.5f, 0.0f, 20.0f));
        translateTexture = glm::translate(model, glm::vec3(-50.0f, 0.0f, -15.8f));
        scaleTexture = glm::scale(model, glm::vec3(100.5f, 0.0f, 50.0f));
        modelMatrixForContainer = translateTexture * scaleTexture;
        cube1.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //frontwall

        scaleTexture = glm::scale(model, glm::vec3(0.5f, 5.0f, 20.0f));
        translateTexture = glm::translate(model, glm::vec3(-5.0f, 0.0f, 14.5f));
        scaleTexture = glm::scale(model, glm::vec3(5.5f, 5.0f, .50f));
        modelMatrixForContainer = translateTexture * scaleTexture;
        cube2.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleTexture = glm::scale(model, glm::vec3(0.5f, 5.0f, 20.0f));
        translateTexture = glm::translate(model, glm::vec3(5.0f, 0.0f, 14.5f));
        scaleTexture = glm::scale(model, glm::vec3(5.5f, 5.0f, .50f));
        modelMatrixForContainer = translateTexture * scaleTexture;
        cube2.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        scaleTexture = glm::scale(model, glm::vec3(0.5f, 5.0f, 20.0f));
        translateTexture = glm::translate(model, glm::vec3(-20.0f, 0.0f, 14.5f));
        scaleTexture = glm::scale(model, glm::vec3(20.5f, 5.0f, .50f));
        modelMatrixForContainer = translateTexture * scaleTexture;
        cube3.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //ROOFTOP

;        scaleTexture = glm::scale(model, glm::vec3(0.5f, 5.0f, 20.0f));
         translateTexture = glm::translate(model, glm::vec3(-20.0f, 5.1f, 14.5f));
         scaleTexture = glm::scale(model, glm::vec3(30.5f, 2.0f, .50f));
         modelMatrixForContainer = translateTexture * scaleTexture;
         cube6.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForContainer);

        //drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);


        //Table
        translateMatrix = glm::translate(identityMatrix, glm::vec3(5.0, 2.35, 4));
        cube4.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube4, lightingShaderWithTexture, translateMatrix);

        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.50, 2.35, 4));
        cube4.setTextureProperty(wood_tex, wood_tex, 32.0f);
        Table(cube4, lightingShaderWithTexture, translateMatrix);




        // also draw the lamp object(s)
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);

        // we now draw as many light bulbs as we have point lights.
        glBindVertexArray(lightCubeVAO);
        for (unsigned int i = 0; i < 5; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            cube.drawCube(ourShader, model, 0.8f, 0.8f, 0.8f);
            //glDrawArrays(GL_TRIANGLES, 0, 36);
        }

       /*  grassShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_POINTS, 0, positions.size());
        */

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &cubeEBO);
   // glDeleteVertexArrays(1, &VAO);
   // glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}




void drawCube1(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();

    lightingShader.setVec3("material.ambient", glm::vec3(0.3f, 0.0, 0.1));
    lightingShader.setVec3("material.diffuse", glm::vec3(0.3f, 0.0, 0.1));
    lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
    lightingShader.setFloat("material.shininess", 32.0f);

    lightingShader.setMat4("model", model);

    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}


// CURVE

void curve(Shader &lightingShader, glm::mat4 altogether)
{
    
    float rotateAngle_XB = 0.0, rotateAngle_YB = 0.0 , rotateAngle_ZB = 30.0;
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrixB, rotateXMatrixB, rotateYMatrixB, rotateZMatrixB, scaleMatrixB, modelForCurve;
    translateMatrixB = glm::translate(identityMatrix, glm::vec3(-20.0, 0.0, 0.0));
    rotateXMatrixB = glm::rotate(identityMatrix, glm::radians(rotateAngle_XB), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrixB = glm::rotate(identityMatrix, glm::radians(rotateAngle_YB), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrixB = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z*rotateAngle_ZB), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrixB = glm::scale(identityMatrix, glm::vec3(3.0, 10.0, 2.0));
    modelForCurve =altogether * translateMatrixB * rotateXMatrixB * rotateYMatrixB * rotateZMatrixB * scaleMatrixB;

    lightingShader.setMat4("model", modelForCurve);

    if (loadBezierCurvePoints)
    {
        bezierVAO = hollowBezier(cntrlPoints.data(), ((unsigned int)cntrlPoints.size() / 3) - 1);
        loadBezierCurvePoints = false;
        showHollowBezier = true;
    }
    if (showHollowBezier)
    {
        lightingShader.use();
        lightingShader.setVec3("material.ambient", glm::vec3(1.0f, 0.0f, 1.0f));
        lightingShader.setVec3("material.diffuse", glm::vec3(1.0f, 0.0f, 1.0f));
        lightingShader.setVec3("material.specular", glm::vec3(1.0f, 1.0f, 1.0f));
        lightingShader.setFloat("material.shininess", 32.0f);

        glBindVertexArray(bezierVAO);
        glDrawElements(GL_TRIANGLES,                    // primitive type
            (unsigned int)indices.size(),          // # of indices
            GL_UNSIGNED_INT,                 // data type
            (void*)0);                       // offset to indices

        // unbind VAO
        glBindVertexArray(0);
    }


}





//HUMAN
/*  
void Human(Sphere& sphere, Shader& lightingShader, glm::mat4 altogether)
{
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix;
    glm::mat4 modelForSphere = glm::mat4(1.0f);
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.50, 0.0, 1.0));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.25, 0.35, 0.3));
    // modelForSphere = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    
    modelForSphere = altogether * translateMatrix * scaleMatrix;
    sphere.drawSphere(lightingShader, modelForSphere);

    float ch_z = ball_z - 1.95f;
    glm::mat4 modelForSphere = glm::mat4(1.0f);
    modelForSphere = glm::translate(model, glm::vec3(char_x, 0.90f, ch_z));
    sphere.drawSphere(lightingShader, modelForSphere);

    float obj_z = ball_z - 2.0f;
    // character
    translateMatrix = glm::translate(identityMatrix, glm::vec3(char_x - 0.03f, 0.82f, obj_z));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.06f, 0.06f, 0.1f));
    model = alTogether * translateMatrix * scaleMatrix;
    lightingShader.setMat4("model", model);
    drawCube(cubeVAO, lightingShader, model, 0.3529, 0.3843, 0.5294);

    if (inc)
    {
        hand_angle += 0.5;
        hand_angle2 -= 0.5;
        if (hand_angle >= 100.0)
        {
            inc = false;
        }

    }
    else
    {
        hand_angle -= 0.5;
        hand_angle2 += 0.5;
        if (hand_angle <= 0.0)
            inc = true;
    }

    //hand
    float hand_z = obj_z + 0.05;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(char_x + 0.025f, 0.87f, hand_z));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.01f, 0.06f, 0.01f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(-20.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-230.0f + hand_angle), glm::vec3(1.0f, 0.0f, 0.0f));
    model = alTogether * translateMatrix * rotateXMatrix * rotateZMatrix * scaleMatrix;
    lightingShader.setMat4("model", model);
    drawCube(cubeVAO, lightingShader, model, 0.9176, 0.7725, 0.6627);


    translateMatrix = glm::translate(identityMatrix, glm::vec3(char_x - 0.035f, 0.87f, hand_z));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.01f, 0.06f, 0.01f));
    rotateZMatrix = glm::rotate(identityMatrix, glm::radians(20.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(110.0f + hand_angle2), glm::vec3(1.0f, 0.0f, 0.0f));
    model = alTogether * translateMatrix * rotateXMatrix * rotateZMatrix * scaleMatrix;
    lightingShader.setMat4("model", model);
    drawCube(cubeVAO, lightingShader, model, 0.9176, 0.7725, 0.6627);


    translateMatrix = glm::translate(identityMatrix, glm::vec3(char_x - 0.025f, 0.84f, hand_z));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.01f, 0.06f, 0.01f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(-230.0f + hand_angle), glm::vec3(1.0f, 0.0f, 0.0f));
    model = alTogether * translateMatrix * rotateXMatrix * scaleMatrix;
    lightingShader.setMat4("model", model);
    drawCube(cubeVAO, lightingShader, model, 0.9176, 0.7725, 0.6627);


    translateMatrix = glm::translate(identityMatrix, glm::vec3(char_x + 0.015f, 0.84f, hand_z));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.01f, 0.06f, 0.01f));
    rotateXMatrix = glm::rotate(identityMatrix, glm::radians(110.0f + hand_angle2), glm::vec3(1.0f, 0.0f, 0.0f));
    model = alTogether * translateMatrix * rotateXMatrix * scaleMatrix;
    lightingShader.setMat4("model", model);
    drawCube(cubeVAO, lightingShader, model, 0.9176, 0.7725, 0.6627);





}
*/
//Table_reception
void Table(Cube& cube, Shader& lightingShader, glm::mat4 alTogether)
{
    //cube.setMaterialisticProperty(glm::vec3(0.862f, 0.46f, 0.321f));
    glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix, scaleMatrix, model5;
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-0.5f, -0.8f, -0.3));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(4.0f, 0.2f, 3.0f));
    model5 = scaleMatrix * translateMatrix;
    cube.drawCubeWithTexture(lightingShader, alTogether * model5);


    glm::mat4 translateMatrix1, rotateXMatrix1, rotateYMatrix1, rotateZMatrix1, scaleMatrix1, model1;
    translateMatrix1 = glm::translate(identityMatrix, glm::vec3(-0.6f, 0.0f, -0.1f));
    rotateXMatrix1 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix1 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix1 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix1 = glm::scale(identityMatrix, glm::vec3(0.2f, 1.7f, 0.2f));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model1 = rotateXMatrix1 * translateMatrix1 * scaleMatrix1;
    cube.drawCubeWithTexture(lightingShader, alTogether * model1);

    glm::mat4 identityMatrix2 = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 translateMatrix2, rotateXMatrix2, rotateYMatrix2, rotateZMatrix2, scaleMatrix2, model2;
    translateMatrix2 = glm::translate(identityMatrix, glm::vec3(0.9f, 0.0f, -0.1f));
    rotateXMatrix2 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix2 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix2 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix2 = glm::scale(identityMatrix, glm::vec3(0.2f, 1.7f, 0.2f));
    model2 = rotateXMatrix2 * translateMatrix2 * scaleMatrix2;
    cube.drawCubeWithTexture(lightingShader, alTogether * model2);

    glm::mat4 translateMatrix3, rotateXMatrix3, rotateYMatrix3, rotateZMatrix3, scaleMatrix3, model3;
    translateMatrix3 = glm::translate(identityMatrix, glm::vec3(0.8f, 0.0f, -1.49f));
    rotateXMatrix3 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix3 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix3 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix3 = glm::scale(identityMatrix, glm::vec3(0.2f, 1.7f, 0.2f));
    //model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
    model3 = rotateXMatrix3 * translateMatrix3 * scaleMatrix3;
    cube.drawCubeWithTexture(lightingShader, alTogether * model3);

    // Modelling Transformation
    glm::mat4 translateMatrix4, rotateXMatrix4, rotateYMatrix4, rotateZMatrix4, scaleMatrix4, model4;
    translateMatrix4 = glm::translate(identityMatrix, glm::vec3(-0.6f, 0.0f, -1.49f));
    rotateXMatrix4 = glm::rotate(identityMatrix, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    rotateYMatrix4 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    rotateZMatrix4 = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scaleMatrix4 = glm::scale(identityMatrix, glm::vec3(0.2f, 1.7f, 0.2f));
    model4 = rotateXMatrix4 * translateMatrix4 * scaleMatrix4;
    cube.drawCubeWithTexture(lightingShader, alTogether * model4);
}

void Room1(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    //Left wall
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 5.0f, 20.0f));
    translate = glm::translate(model, glm::vec3(-10.5, 0, -0.5));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    scale = glm::scale(model, glm::vec3(2.0f, 0.20f, 0.005f));
    translate = glm::translate(model, glm::vec3(10.5, 0, 12.0));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    //Front wall
     model = glm::mat4(1.0f);
     translate = glm::mat4(1.0f);
     translate2 = glm::mat4(1.0f);
     scale = glm::mat4(1.0f);
     scale = glm::scale(model, glm::vec3(15.5f, 5.0f, 0.50f));
     translate = glm::translate(model, glm::vec3(-0.33, 0, -20.5));
     model = alTogether * scale * translate;
     drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

     //floor
     model = glm::mat4(1.0f);
     translate = glm::mat4(1.0f);
     translate2 = glm::mat4(1.0f);
     scale = glm::mat4(1.0f);
     scale = glm::scale(model, glm::vec3(18.5f, .85f, 30.50f));
     translate = glm::translate(model, glm::vec3(-0.33, 0, -0.5));
     model = alTogether * scale * translate;
     drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

     //top
     model = glm::mat4(1.0f);
     translate = glm::mat4(1.0f);
     translate2 = glm::mat4(1.0f);
     scale = glm::mat4(1.0f);
     scale = glm::scale(model, glm::vec3(15.5f, .05f, 30.50f));
     translate = glm::translate(model, glm::vec3(-0.33, 10.0, -0.5));
     scale = glm::scale(model, glm::vec3(15.5f, 0.5f, 30.50f));
     model = alTogether * scale * translate;
     drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

     //right wall

     model = glm::mat4(1.0f);
     translate = glm::mat4(1.0f);
    // translate2 = glm::mat4(1.0f);
     scale = glm::mat4(1.0f);
     scale = glm::scale(model, glm::vec3(0.5f, 5.0f, 23.85f));
     translate = glm::translate(model, glm::vec3(20.5f, 0, -0.385));
     model = alTogether * scale * translate;
     drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);
/* 
     scale = glm::scale(model, glm::vec3(22.0f, 0.20f, 0.004f));
     translate = glm::translate(model, glm::vec3(-23.30, 0, 15.5));
     model = alTogether * scale * translate;
     drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);
     */
}

void Room2(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    //Left wall
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 5.0f, 23.85f));
    translate = glm::translate(model, glm::vec3(-10.5, 0, -0.385));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

   /*  scale = glm::scale(model, glm::vec3(2.0f, 0.20f, 0.005f));
    translate = glm::translate(model, glm::vec3(10.5, 0, 12.0));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);
    */
    //Front wall
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(15.5f, 5.0f, 0.50f));
    translate = glm::translate(model, glm::vec3(-0.33, 0, -20.5));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    //floor
    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(18.5f, .85f, 30.50f));
    translate = glm::translate(model, glm::vec3(-0.33, 0, -0.5));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    //top

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(15.5f, 0.5f, 30.50f));
    translate = glm::translate(model, glm::vec3(-0.33, 10.0, -0.5));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    //right wall

    model = glm::mat4(1.0f);
    translate = glm::mat4(1.0f);
    translate2 = glm::mat4(1.0f);
    scale = glm::mat4(1.0f);
    scale = glm::scale(model, glm::vec3(0.5f, 5.0f, 20.0f));
    translate = glm::translate(model, glm::vec3(20.5f, 0, -0.5));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);

    scale = glm::scale(model, glm::vec3(22.0f, 0.20f, 0.004f));
    translate = glm::translate(model, glm::vec3(-23.30, 0, 15.5));
    model = alTogether * scale * translate;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);
}


long long nCr(int n, int r)
{
    if (r > n / 2)
        r = n - r; // because C(n, r) == C(n, n - r)
    long long ans = 1;
    int i;

    for (i = 1; i <= r; i++)
    {
        ans *= n - r + i;
        ans /= i;
    }

    return ans;
}

void BezierCurve(double t, float xy[2], GLfloat ctrlpoints[], int L)
{
    double y = 0;
    double x = 0;
    t = t > 1.0 ? 1.0 : t;
    for (int i = 0; i < L + 1; i++)
    {
        long long ncr = nCr(L, i);
        double oneMinusTpow = pow(1 - t, double(L - i));
        double tPow = pow(t, double(i));
        double coef = oneMinusTpow * tPow * ncr;
        x += coef * ctrlpoints[i * 3];
        y += coef * ctrlpoints[(i * 3) + 1];

    }
    xy[0] = float(x);
    xy[1] = float(y);
}


unsigned int hollowBezier(GLfloat ctrlpoints[], int L)
{
    int i, j;
    float x, y, z, r;                //current coordinates
    float theta;
    float nx, ny, nz, lengthInv;    // vertex normal


    const float dtheta = (pi/2.0) / ntheta;        //angular step size

    float t = 0;
    float dt = 1.0 / nt;
    float xy[2];

    for (i = 0; i <= nt; ++i)              //step through y
    {
        BezierCurve(t, xy, ctrlpoints, L);
        r = xy[0];
        y = xy[1];
        theta = 0;
        t += dt;
        lengthInv = 1.0 / r;

        for (j = 0; j <= ntheta; ++j)
        {
            double cosa = cos(theta);
            double sina = sin(theta);
            z = r * cosa;
            x = r * sina;

            coordinates.push_back(x);
            coordinates.push_back(y);
            coordinates.push_back(z);

            // normalized vertex normal (nx, ny, nz)
            // center point of the circle (0,y,0)
            nx = (x - 0) * lengthInv;
            ny = (y - y) * lengthInv;
            nz = (z - 0) * lengthInv;

            normals.push_back(nx);
            normals.push_back(ny);
            normals.push_back(nz);

            theta += dtheta;
        }
    }

    // generate index list of triangles
    // k1--k1+1
    // |  / |
    // | /  |
    // k2--k2+1

    int k1, k2;
    for (int i = 0; i < nt; ++i)
    {
        k1 = i * (ntheta + 1);     // beginning of current stack
        k2 = k1 + ntheta + 1;      // beginning of next stack

        for (int j = 0; j < ntheta; ++j, ++k1, ++k2)
        {
            // k1 => k2 => k1+1
            indices.push_back(k1);
            indices.push_back(k2);
            indices.push_back(k1 + 1);

            // k1+1 => k2 => k2+1
            indices.push_back(k1 + 1);
            indices.push_back(k2);
            indices.push_back(k2 + 1);
        }
    }

    size_t count = coordinates.size();
    for (int i = 0; i < count; i += 3)
    {
        vertices.push_back(coordinates[i]);
        vertices.push_back(coordinates[i + 1]);
        vertices.push_back(coordinates[i + 2]);

        vertices.push_back(normals[i]);
        vertices.push_back(normals[i + 1]);
        vertices.push_back(normals[i + 2]);
    }

    unsigned int bezierVAO;
    glGenVertexArrays(1, &bezierVAO);
    glBindVertexArray(bezierVAO);

    // create VBO to copy vertex data to VBO
    unsigned int bezierVBO;
    glGenBuffers(1, &bezierVBO);
    glBindBuffer(GL_ARRAY_BUFFER, bezierVBO);           // for vertex data
    glBufferData(GL_ARRAY_BUFFER,                   // target
        (unsigned int)vertices.size() * sizeof(float), // data size, # of bytes
        vertices.data(),   // ptr to vertex data
        GL_STATIC_DRAW);                   // usage

    // create EBO to copy index data
    unsigned int bezierEBO;
    glGenBuffers(1, &bezierEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bezierEBO);   // for index data
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,           // target
        (unsigned int)indices.size() * sizeof(unsigned int),             // data size, # of bytes
        indices.data(),               // ptr to index data
        GL_STATIC_DRAW);                   // usage

    // activate attrib arrays
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    // set attrib arrays with stride and offset
    int stride = 24;     // should be 24 bytes
    glVertexAttribPointer(0, 3, GL_FLOAT, false, stride, (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, stride, (void*)(sizeof(float) * 3));

    // unbind VAO, VBO and EBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return bezierVAO;
}



//Walking Human
/* 
void planeAnimation(unsigned int& cubeVAO, Shader ourShader, glm::mat4 comMatrix)
{
    if (humanMove)
    {
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        identityMatrix = glm::mat4(1.0f);

        float x_init = -8.0;
        float y_init = -1.0;


        // Plane
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 2.0f, 2.0f));
        if (r >= 8.0)
        {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(r + x_init, r + x_init + y_init, -2.0f));
           // x_pilot_eye = r + x_init;
           // y_pilot_eye = r + x_init + y_init;
           // z_pilot_eye = -2.0f;
        }
        else
        {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(r + x_init, y_init, -2.0f));
        }


        model = comMatrix * translateMatrix * scaleMatrix;


        string diffuseMapPath = "wall.jpg";
        string specularMapPath = "wall.jpg";

        unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
        unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);


        glm::mat4 modelMatrixForContainer = model;
        Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
        cube.drawCubeWithTexture(ourShader, model);

        r = (r + 1);

    }
    else
    {
        glm::mat4 identityMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        identityMatrix = glm::mat4(1.0f);

        // Plane
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 2.0f, 2.0f));
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-8.0f, -1.0f, -2.0f));
        model = comMatrix * translateMatrix * scaleMatrix;


        string diffuseMapPath = "wall.jpg";
        string specularMapPath = "wall.jpg";

        unsigned int diffMap = loadTexture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
        unsigned int specMap = loadTexture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);


        glm::mat4 modelMatrixForContainer = model;
        Cube cube = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);
        cube.drawCubeWithTexture(ourShader, model);



    }
}
 */

void Fan(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether){
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 translate = glm::mat4(1.0f);
    glm::mat4 translate2 = glm::mat4(1.0f);
    glm::mat4 translatematrix = glm::mat4(1.0f);
    glm::mat4 scale = glm::mat4(1.0f);
    glm::mat4 scaleMatrix = glm::mat4(1.0f);
    glm::mat4 translateMatrix = glm::mat4(1.0f);
if (fanOn)
{
    //plate 1
    scale = glm::scale(identityMatrix, glm::vec3(0.5f, 5.0f, 23.85f));
    translate = glm::translate(identityMatrix, glm::vec3(-10.5, 0, -0.385));
   
    glm::mat4 translateMatrix2 = glm::translate(identityMatrix, glm::vec3(-0.5f, 0.5f, -0.125f));
    glm::mat4 translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-1.5f, 0.0f, -1.7f));

    model = translateMatrix3 * translate * glm::rotate(model, glm::radians(r), glm::vec3(0.0f, 1.0f, 0.0f)) * translateMatrix2 * scale;
    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);
;

    //plate 2
   
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.2f, 0.5f, 1.325f));

    translateMatrix2 = glm::translate(identityMatrix, glm::vec3(-0.5f, 0.5f, -0.125f));

    model = translateMatrix3 * translateMatrix * glm::rotate(identityMatrix, glm::radians(r + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * translateMatrix2 * scaleMatrix;
    lightingShader.setMat4("model", model);
    lightingShader.setVec4("color", glm::vec4(0.0, 0.8157f, 0.2f, 1.0f));

    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);




    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, .6f, .1f));
    translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-01.32f, 1.0f, -0.48f));

    model = translateMatrix3 * scaleMatrix;
    lightingShader.setMat4("model", model);
    lightingShader.setVec4("color", glm::vec4(0.0, 0.0f, 0.0f, 1.0f));

    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);




    r = (r + 5.0);

}
else
{
    //Fan plate 1
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.2f, 0.5f, 1.325f));

    glm::mat4 translateMatrix2 = glm::translate(identityMatrix, glm::vec3(-0.5f, 0.5f, -0.125f));


    glm::mat4 translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-1.5f, 0.0f, -1.7f));

    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 0.1f, .5f));

    model = translateMatrix3 * translateMatrix * glm::rotate(identityMatrix, glm::radians(r), glm::vec3(0.0f, 1.0f, 0.0f)) * translateMatrix2 * scaleMatrix;
    lightingShader.setMat4("model", model);
    lightingShader.setVec4("color", glm::vec4(0.0, 0.8157f, 0.2f, 1.0f));

    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);


    //Fan plate 2
    translateMatrix = glm::translate(identityMatrix, glm::vec3(0.2f, 0.5f, 1.325f));

    translateMatrix2 = glm::translate(identityMatrix, glm::vec3(-0.5f, 0.5f, -0.125f));

    model = translateMatrix3 * translateMatrix * glm::rotate(identityMatrix, glm::radians(r + 90.0f), glm::vec3(0.0f, 1.0f, 0.0f)) * translateMatrix2 * scaleMatrix;
    lightingShader.setMat4("model", model);
    lightingShader.setVec4("color", glm::vec4(0.0, 0.8157f, 0.2f, 1.0f));

    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);


    //Fan handle
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(.1f, .6f, .1f));
    translateMatrix3 = glm::translate(identityMatrix, glm::vec3(-01.32f, 1.0f, -0.48f));

    model = translateMatrix3 * scaleMatrix;
    lightingShader.setMat4("model", model);
    lightingShader.setVec4("color", glm::vec4(0.0, 0.0f, 0.0f, 1.0f));

    drawCube(cubeVAO, lightingShader, model, 0.545, 0.271, 0.075);


}
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        if (rotateAxis_X) rotateAngle_X -= 0.1;
        else if (rotateAxis_Y) rotateAngle_Y -= 0.1;
        else rotateAngle_Z -= 0.1;
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) translate_Y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) translate_Y -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) translate_X += 0.001;
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) translate_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) translate_Z += 0.001;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) translate_Z -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) scale_X += 0.001;
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) scale_X -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) scale_Y += 0.001;
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) scale_Y -= 0.001;
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS) scale_Z += 0.001;
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) scale_Z -= 0.001;

    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        rotateAngle_X += 0.1;
        rotateAxis_X = 1.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
    {
        rotateAngle_Y += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 1.0;
        rotateAxis_Z = 0.0;
    }
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        rotateAngle_Z += 0.1;
        rotateAxis_X = 0.0;
        rotateAxis_Y = 0.0;
        rotateAxis_Z = 1.0;
    }

    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
    {
        eyeX += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
    {
        eyeX -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        eyeZ += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
    {
        eyeZ -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        eyeY += 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        eyeY -= 2.5 * deltaTime;
        basic_camera.changeEye(eyeX, eyeY, eyeZ);
    }
    pointlight3.turnOn();
    pointlight4.turnOn();
    pointlight5.turnOn();

    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        onOffToggle = !onOffToggle;
        if (onOffToggle) {
            pointlight1.turnOff();
            pointlight3.turnOff();

        }
        else{
            pointlight1.turnOn();
        pointlight3.turnOn();

    }
    }

    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        onOffToggle1 = !onOffToggle1;
        if (onOffToggle1) {
            pointlight2.turnOff();
            pointlight4.turnOff();

        }
        else{  
            pointlight2.turnOn();
        pointlight3.turnOn();
        }

    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        donOffToggle = !donOffToggle;
        
    }



    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        if (specularToggle)
        {

            pointlight1.turnAmbientOff();
            pointlight2.turnAmbientOff();
            pointlight3.turnAmbientOff();
            pointlight4.turnAmbientOff();
            specularToggle = !specularToggle;
        }
        else
        {

            pointlight1.turnAmbientOn();
            pointlight2.turnAmbientOn();
            pointlight3.turnAmbientOn();
            pointlight4.turnAmbientOn();
            specularToggle = !specularToggle;
        }



    }


    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        if (diffuseToggle)
        {

            pointlight1.turnDiffuseOff();
            pointlight2.turnDiffuseOff();
            pointlight3.turnDiffuseOff();
            pointlight4.turnDiffuseOff();
            diffuseToggle = !diffuseToggle;
        }
        else
        {

            pointlight1.turnDiffuseOn();
            pointlight2.turnDiffuseOn();
            pointlight3.turnDiffuseOn();
            pointlight4.turnDiffuseOn();
            diffuseToggle = !diffuseToggle;
        }

    }
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
    {
        if (specularToggle)
        {

            pointlight1.turnSpecularOff();
            pointlight2.turnSpecularOff();
            pointlight3.turnSpecularOff();
            pointlight4.turnSpecularOff();
            specularToggle = !specularToggle;
        }
        else
        {

            pointlight1.turnSpecularOn();
            pointlight2.turnSpecularOn();
            pointlight3.turnSpecularOn();
            pointlight4.turnSpecularOn();
            specularToggle = !specularToggle;
        }



    }
   /* if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        pointlight1.turnAmbientOn();
        pointlight2.turnAmbientOn();
        pointlight3.turnAmbientOn();
        pointlight4.turnAmbientOn();
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        pointlight1.turnDiffuseOn();
        pointlight2.turnDiffuseOn();
        pointlight3.turnDiffuseOn();
        pointlight4.turnDiffuseOn();
    }
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
    {
        pointlight1.turnSpecularOn();
        pointlight2.turnSpecularOn();
        pointlight3.turnSpecularOn();
        pointlight4.turnSpecularOn();
    }

    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
    {
        pointlight1.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight1.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight1.specular = glm::vec3(0.0, 1.0, 0.0);


        pointlight2.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight2.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight2.specular = glm::vec3(0.0, 1.0, 0.0);


        pointlight3.ambient = glm::vec3(0.0, 1.0, 0.0);
        pointlight3.diffuse = glm::vec3(0.0, 1.0, 0.0);
        pointlight3.specular = glm::vec3(0.0, 1.0, 0.0);


        pointlight4.ambient = glm::vec3(0.0, 1.0, 0.0);
       pointlight4.diffuse = glm::vec3(0.0, 1.0, 0.0);
       pointlight4.specular = glm::vec3(0.0, 1.0, 0.0);

    }*/


}

unsigned int loadTexture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// ------------------------------------------------------- 
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}