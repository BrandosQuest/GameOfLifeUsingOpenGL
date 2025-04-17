#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shader_s.h>

#include <iostream>
#include <vector>
#include <array>
//#include "../thirdparty/SDL3-3.2.10/include/SDL3/SDL_events.h"
//#include "../thirdparty/SDL3-3.2.10/include/SDL3/SDL.h"

using namespace std;

void parametersInput(int* rows, int* coloums) {
    std::cout << "ciaooo, insert the number of rows and coloums for the game" << std::endl;

    cin >> *rows;
    cin >> *coloums;
}
struct bQuad {
    float vertices[12];//4 points of x y z
    bool alive = false;
    array<float, 3> colours;//rgb
};

void setVetixesOfQuadsInMatrix(std::vector<std::vector<bQuad>>& matrix, int rows, int coloums) {
    float cellWidth = 2.0 / coloums;
    float cellHight = 2.0 / rows;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < coloums; j++)
        {
            float verticess[12] = {
                (j * cellWidth) - 1.0            , 1.0 - (i * cellHight)                , 0.0f,  // top left
                (j * cellWidth) - 1.0 + cellWidth, 1.0 - (i * cellHight)                , 0.0f,  // top right
                (j * cellWidth) - 1.0            , 1.0 - ((i * cellHight) + cellHight)  , 0.0f,  // bottom left 
                (j * cellWidth) - 1.0 + cellWidth, 1.0 - ((i * cellHight) + cellHight)  , 0.0f,  // bottom right 
            };
            for (int v = 0; v < 12; ++v) {
                matrix[i][j].vertices[v] = verticess[v];
            }

            array<float, 3> colourss;
            if ((i + j) % 2 == 0) {
                colourss = { 0.5f, 0.5f, 0.0f };
            }
            else {
                colourss = { 0.1f, 0.1f, 0.1f };
            }
            matrix[i][j].colours = colourss;
        }
    }
}
void setVetixesAndIndexes(int sizeVertixes, int sizeIndexes, float* vertixesAndColour, unsigned int* indexes, std::vector<std::vector<bQuad>>& matrix, int rows, int coloums) {
    int quadCounter = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < coloums; j++)
        {
            //firstQuad
            vertixesAndColour[(quadCounter * 24) + 0] = matrix[i][j].vertices[0];
            vertixesAndColour[(quadCounter * 24) + 1] = matrix[i][j].vertices[1];
            vertixesAndColour[(quadCounter * 24) + 2] = matrix[i][j].vertices[2];
            vertixesAndColour[(quadCounter * 24) + 3] = matrix[i][j].colours[0];
            vertixesAndColour[(quadCounter * 24) + 4] = matrix[i][j].colours[1];
            vertixesAndColour[(quadCounter * 24) + 5] = matrix[i][j].colours[2];
            //firstQuad
            vertixesAndColour[(quadCounter * 24) + 6] = matrix[i][j].vertices[3];
            vertixesAndColour[(quadCounter * 24) + 7] = matrix[i][j].vertices[4];
            vertixesAndColour[(quadCounter * 24) + 8] = matrix[i][j].vertices[5];
            vertixesAndColour[(quadCounter * 24) + 9] = matrix[i][j].colours[0];
            vertixesAndColour[(quadCounter * 24) + 10] = matrix[i][j].colours[1];
            vertixesAndColour[(quadCounter * 24) + 11] = matrix[i][j].colours[2];
            //firstQuad
            vertixesAndColour[(quadCounter * 24) + 12] = matrix[i][j].vertices[6];
            vertixesAndColour[(quadCounter * 24) + 13] = matrix[i][j].vertices[7];
            vertixesAndColour[(quadCounter * 24) + 14] = matrix[i][j].vertices[8];
            vertixesAndColour[(quadCounter * 24) + 15] = matrix[i][j].colours[0];
            vertixesAndColour[(quadCounter * 24) + 16] = matrix[i][j].colours[1];
            vertixesAndColour[(quadCounter * 24) + 17] = matrix[i][j].colours[2];
            //firstQuad
            vertixesAndColour[(quadCounter * 24) + 18] = matrix[i][j].vertices[9];
            vertixesAndColour[(quadCounter * 24) + 19] = matrix[i][j].vertices[10];
            vertixesAndColour[(quadCounter * 24) + 20] = matrix[i][j].vertices[11];
            vertixesAndColour[(quadCounter * 24) + 21] = matrix[i][j].colours[0];
            vertixesAndColour[(quadCounter * 24) + 22] = matrix[i][j].colours[1];
            vertixesAndColour[(quadCounter * 24) + 23] = matrix[i][j].colours[2];

            indexes[(quadCounter * 6) + 0] = (quadCounter * 4) + 0;//0
            indexes[(quadCounter * 6) + 1] = (quadCounter * 4) + 2;//2
            indexes[(quadCounter * 6) + 2] = (quadCounter * 4) + 1;//1
            indexes[(quadCounter * 6) + 3] = (quadCounter * 4) + 2;//2
            indexes[(quadCounter * 6) + 4] = (quadCounter * 4) + 3;//3
            indexes[(quadCounter * 6) + 5] = (quadCounter * 4) + 1;//1

            quadCounter++;
        }
    }
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    int coloums = 0;
    int rows = 0;
    parametersInput(&rows, &coloums);
    std::vector<std::vector<bQuad>> matrix(rows, std::vector<bQuad>(coloums));
    setVetixesOfQuadsInMatrix(matrix, rows, coloums);



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
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("C:/BrandoOnPc/programmazione/OpenGL/GameOfLifeUsingOpenGL/src/newVertShader.vert", "C:/BrandoOnPc/programmazione/OpenGL/GameOfLifeUsingOpenGL/src/newFragShader.frag"); // you can name your shader files however you like

    //This will synchronize your frame rate with your monitor's refresh rate (typically 60Hz), 
    // preventing unnecessary rendering.
    // Add this after creating the OpenGL context (after glfwMakeContextCurrent)
    //glfwSwapInterval(1); // Enable vsync

    
    float* verticesAndColour = new float[4 * rows * coloums * 6];
    unsigned int* indices = new unsigned int[6 * rows * coloums];
    setVetixesAndIndexes(4 * rows * coloums * 6, 6 * rows * coloums, verticesAndColour, indices, matrix, rows, coloums);



    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    unsigned int EBO;
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(verticesAndColour), verticesAndColour, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, (4 * rows * coloums * 6) * sizeof(float), verticesAndColour, GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (6 * rows * coloums) * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);

    //ourShader.use();
    //float offset = 0.5f;
    //ourShader.setFloat("xOffset", offset);

    // uncomment this call to draw in wireframe polygons.
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    //while (!glfwWindowShouldClose(window) && SDL_PollEvent(&event))
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render the triangle
        ourShader.use();

        int width;
        int height;
        glfwGetWindowSize(window, &width, &height);

        float timeValue = glfwGetTime();
        ourShader.setFloat("timeFormInit", timeValue);
        ourShader.setFloat("width", width);
        ourShader.setFloat("hight", height);


        glBindVertexArray(VAO);
        int numOfVert = 6 * rows * coloums;
        glDrawElements(GL_TRIANGLES, numOfVert, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, 3);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    delete[] verticesAndColour;
    delete[] indices;
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}