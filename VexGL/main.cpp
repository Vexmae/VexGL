#include "main.h"

int main() {
    Run();
    return 0;
}

int WinMain() {
    main();
    return 0;
}

void Run() {
    Initialize();
    vglCreateWindow(START_WIDTH, START_HEIGHT, START_TITLE, false);
    vglAssignCallbacks();
    Load();
    while (!glfwWindowShouldClose(window)) {
        Render();
        vglTimeUpdate();
        glfwPollEvents();
        Update();
    }

    std::cout << "Closing Window." << std::endl;
    glfwTerminate();
}

void Initialize() {
}

void Load() {
    glEnable(GL_DEPTH_TEST);
    vglShader shader = vglShader(VGL_VERTEX_DEFAULT, VGL_FRAGMENT_DEFAULT);
    shader.vglGetShaderID(&ShaderProgram);
    shader.Use();

    cube.vglInitCube();
    cube2.vglInitCube();

    cube2.vglRotate(glm::vec3(-45.0f, 0.0f, 45.0f));
    cube.vglRotate(glm::vec3(45.0f, 0.0f, 45.0f));

    cube.vglScale(glm::vec3(0.5f));
    cube2.vglScale(glm::vec3(0.5f));

    cube.vglSetPosition(glm::vec3(-1.0f, 0.0f, 0.0f));
    cube2.vglSetPosition(glm::vec3(1.0f, 0.0f, 0.0f));
}

void Render() {
    glClearColor(0.0f, 0.5f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 600.0f / 600.0f, 0.1f, 100.0f);
        
    glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "view"), 1, false, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "projection"), 1, false, glm::value_ptr(projection));


    glUseProgram(ShaderProgram);
    cube.vglRotate(glm::vec3(0.0f, 1.0f, 0.0f));
    cube.vglDraw(ShaderProgram);

    cube2.vglRotate(glm::vec3(0.0f, 1.0f, 0.0f));
    cube2.vglDraw(ShaderProgram);

    glfwSwapBuffers(window);
}

void Update() {
    if (vglGetFrameSinceStart() % 60 == 0) {
        std::string title;
        title += std::to_string(1.0f / vglDeltaTime());
        title += " FPS";
        std::cout << title << std::endl;
        glfwSetWindowTitle(window, title.c_str());
    }
}

void vglAssignCallbacks() {
    glfwSetFramebufferSizeCallback(window, vglViewportSizeCallback);
    glfwSetKeyCallback(window, vglKeyCallback);
}

void vglViewportSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void vglKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {

    if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {
        switch (iswireframe) {
            case 0:
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                break;
            case 1:
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                break;
        }
        iswireframe = !iswireframe;
    }
}

void vglCreateWindow(int width, int height, char title[], bool fullscreen) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, true);
    glfwWindowHint(GLFW_FOCUSED, true);

    GLFWmonitor* monitor = NULL;
    if (fullscreen) { monitor = glfwGetPrimaryMonitor(); };

    GLFWwindow* _window = glfwCreateWindow(width, height, title, monitor, NULL);

    if (!_window) { std::cout << "Window Creation Failed" << std::endl; };

    window = _window;
    glfwMakeContextCurrent(_window);

    gladLoadGL();
    glViewport(0, 0, width, height);
    glfwSwapInterval(1); //V-sync on with 1 and off with 0;
}
