#define ROWS 40
#define COLS 20
#define ROUNDS 4

#ifdef __APPLE__
    #include "header/Includes.h";
    #include "header/Shader.h";
    #include "header/VerticesObject.h";
    #include "header/ColorTile.h";
#elif _WIN64
	#include "../header/Includes.h";
	#include "../header/Shader.h";
	#include "../header/VerticesObject.h";
	#include "../header/ColorTile.h";
#endif

Shader *shaderProgram;
GLFWwindow *window;
ColorTiles *colorsTiles;

int ROUND = 0;
int POINTS = 0;

//Atributos janela
int WIDTH = 800;
int HEIGHT = 600;
int RESIZED_WIDTH = 800;
int RESIZED_HEIGHT = 600;

//teclas pressionadas
int keys[1024];

//Define acoes do redimensionamento da tela
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    RESIZED_WIDTH = width;
    RESIZED_HEIGHT = height;
}

/*
	Controla que teclas estão pressionadas em um dado momento
*/
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if(action == GLFW_PRESS) keys[key] = 1;
	if(action == GLFW_RELEASE) keys[key] = 0;
}

int calculateChances(){
    return ROUNDS-ROUND;
}

int calculePoints(int manyMatcheds){
    switch ( ROUND )
    {
        case 1:
            return manyMatcheds * 10;
            break;
        case 2:
            return manyMatcheds * 5;
            break;
        case 3:
            return manyMatcheds * 2;
            break;
        case 4:
            return manyMatcheds * 1;
            break;
        default:
            return manyMatcheds;
    }


}

/*
Define acoes do mouse
*/
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (action == GLFW_PRESS && button == GLFW_MOUSE_BUTTON_LEFT) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        //Realiza a proporcao do clique para projecao original
        xpos = WIDTH * xpos / RESIZED_WIDTH;
        ypos = HEIGHT * ypos / RESIZED_HEIGHT;

        int manyMatcheds = colorsTiles->testCliqueMouse((float)xpos,(float)ypos);
        if(manyMatcheds>0){
            printf("Você acertou %d.\n",manyMatcheds);
            ROUND++;
            POINTS = POINTS + calculePoints(manyMatcheds);


            if(ROUND==ROUNDS){
                printf("\nO jogo acabou, você fez %d pontos.\n",POINTS);
                glfwSetWindowShouldClose(window, true);
            } else{
                printf("você está com %d pontos.\n",POINTS);
                printf("Você tem %d chances.\n\n",calculateChances());
            }
        }

    }
}


GLFWwindow* createWindow() {
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Jogo das Cores!", NULL, NULL);
    if (window == NULL) {
        printf("%s", "Houve uma falha ao criar a janela GLFW");
        glfwTerminate();
        return NULL;
    }
    glfwMakeContextCurrent(window);
    return window;
}

int main() {
	if (!glfwInit()) {
		fprintf(stderr, "ERRO: não é possivel iniciar GLFW3\n");
		return 1;
	}

	/* needs for Apple OS X */
    #ifdef __APPLE__
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #endif // !APPLE

	window = createWindow();

	// inicia manipulador da extensao GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	//criacao do shader
	shaderProgram = new Shader("shader/vertexShader.txt", "shader/fragmentShader.txt");

	// define shader para uso
	shaderProgram->UseProgramShaders();

	// habilita funcao de profundidade
	glEnable(GL_DEPTH_TEST);

	//Create SO callbacks
	// esta para quando redimensionar a tela
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // esta para quando clicar com o mouse
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    colorsTiles = new ColorTiles(WIDTH, HEIGHT);

    printf("Você tem %d chances.\n\n",calculateChances());

    // looping do main
	while (!glfwWindowShouldClose(window)) {

	    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// glm projecao
		glm::mat4 projection = glm::ortho(0.0f, (float)WIDTH, (float)HEIGHT, 0.0f, -1.0f, 1.0f);
		
		glUniformMatrix4fv(
			glGetUniformLocation(shaderProgram->Program, "proj"), 1, GL_FALSE, glm::value_ptr(projection));

		//desenha
        colorsTiles->draw(shaderProgram);

        //fila eventos 
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
    // encerra contexto GL e outros recursos da GLFW
    glfwTerminate();

    return 0;


    delete colorsTiles;
    delete shaderProgram;
}

