struct Tile{
    glm::vec3 colorsRGB;
    bool isVisible;

    Tile() {
        float r = (rand()%255)/255.0f;
        float g = (rand()%255)/255.0f;
        float b = (rand()%255)/255.0f;
        colorsRGB = glm::vec3(r,g,b);
        isVisible = true;
    }
};

class ColorTiles{
public:

    float tileWidth, tileHeight;

    glm::mat4 modelMatrix;

    VerticesObject* vertices;

    Tile matrixColors[ROWS][COLS] = {};

    ColorTiles(float totalWidth, float totalHeight)
    {
        this->tileWidth = totalWidth / (float)COLS;
        this->tileHeight = totalHeight / (float)ROWS;

        this->modelMatrix = glm::mat4(1);

        this->setupVertices(tileWidth, tileHeight);

        this-> createMatrixColors();
    }

    void setupVertices(float width, float height) {
        /*
            Comeca centralizado no zero
        */
        float verticesCoordinates[] = {
                // positions
                -width / 2.0f, -height / 2.0f, 0.0f,	// top left
                -width / 2.0f, height / 2.0f,  0.0f,	// bottom left
                width  / 2.0f, height / 2.0f,  0.0f, // bottom right
                width  / 2.0f, -height / 2.0f, 0.0f	// top right
        };

        vertices = new VerticesObject(verticesCoordinates, 12);
    }

    void createMatrixColors(){
        srand((unsigned) time(NULL)) ;
        for (int row = 0; row < ROWS; row++) {
              for (int col = 0; col < COLS; col++) {
                    Tile t = Tile();
                    matrixColors[row][col] = t;
                  }
            }
    }

    int testCliqueMouse(float xPos,float yPos) {
        int counter = 0;
        int columnClick = (int) (xPos / tileWidth);
        int rowClick = (int) (yPos / tileHeight);

        if (matrixColors[rowClick][columnClick].isVisible) {
            matrixColors[rowClick][columnClick].isVisible = false;
            counter = counter+1;
            Tile tileActual = matrixColors[rowClick][columnClick];
            for (int row = 0; row < ROWS; row++) {
                for (int col = 0; col < COLS; col++) {
                    Tile tileAnother = matrixColors[row][col];
                    if(tileAnother.isVisible) {
                        bool notMatched = caculateDMax(tileActual.colorsRGB,tileAnother.colorsRGB);
                        matrixColors[row][col].isVisible = notMatched;
                        if(false == notMatched){
                            counter = counter+1;
                        }
                    }
                }
            }
        }

        return counter;
    }

    bool caculateDMax(glm::vec3 actual, glm::vec3 another){

        int actualR = actual.x*255;
        int actualG = actual.y*255;
        int actualB = actual.z*255;

        int anotherR = another.x*255;
        int anotherG = another.y*255;
        int anotherB = another.z*255;

        double distanceOfRed = actualR - anotherR;
        double distanceOfGreen = actualG - anotherG;
        double distanceOfBlue = actualB - anotherB;

        double distance = sqrt(pow(distanceOfRed, 2) + pow(distanceOfGreen, 2) + pow(distanceOfBlue, 2));
        double distanceMax = sqrt(pow((0-255), 2) + pow((0-255), 2) + pow((0-255), 2));

        if(distance / distanceMax <= 0.15){
            return false;
        }else{
            return true;
        }
    }

    void draw(Shader *shaderProgram) {

        // Define shaderProgram como o shader a ser utilizado
        shaderProgram->UseProgramShaders();

        // Define em quais vertices sera desenhado pelo shader
        vertices->bind(shaderProgram);

        for (int row = 0; row < ROWS; row++) {
            for (int col = 0; col < COLS; col++) {

                float xi = col*tileWidth  + tileWidth/2;
                float yi = row*tileHeight + tileHeight/2;

                modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(xi, yi, 0.0));

                //define aonde desenhar
                glUniformMatrix4fv(
                        glGetUniformLocation(shaderProgram->Program, "matrix_OBJ"), 1,
                        GL_FALSE, glm::value_ptr(modelMatrix));



                //seleciona o tile a ser desenhado
                Tile tile = matrixColors[row][col];


                if(tile.isVisible){
                    glUniform3fv(
                            glGetUniformLocation(shaderProgram->Program, "colorValues"), 1,
                            glm::value_ptr(tile.colorsRGB));
                } else {

                    glUniform3fv(
                            glGetUniformLocation(shaderProgram->Program, "colorValues"), 1,
                            glm::value_ptr(glm::vec3(0,0,0)));
                }


                // Define em quais vertices sera desenhado pelo shader
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
        }

    }

};
