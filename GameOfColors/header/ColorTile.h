//
// Created by Gian Boschetti on 2019-05-13.
//

#ifndef GAMEOFCOLORS_COLORTILE_H
#define GAMEOFCOLORS_COLORTILE_H

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

#define numRows 40
#define numCols 20
class ColorTiles{
public:

    float tileWidth, tileHeight;

    glm::mat4 modelMatrix;

    VerticesObject* vertices;

    Tile matrixColors[numRows][numCols] = {};

    ColorTiles(float totalWidth, float totalHeight)
    {
        this->tileWidth = totalWidth / (float)numCols;
        this->tileHeight = totalHeight / (float)numRows;

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
          for (int row = 0; row < numRows; row++) {
              for (int col = 0; col < numCols; col++) {
                    Tile t = Tile();
                    matrixColors[row][col] = t;
                  }
            }
    }

    void testCliqueMouse(float xPos,float yPos) {
        int columnClick = (int) (xPos / tileWidth);
        int rowClick = (int) (yPos / tileHeight);

        if (matrixColors[rowClick][columnClick].isVisible) {
            //matrixColors[rowClick][columnClick].isVisible = false;
            Tile tileActual = matrixColors[rowClick][columnClick];
            for (int row = 0; row < numRows; row++) {
                for (int col = 0; col < numCols; col++) {
                    Tile tileAnother = matrixColors[row][col];
                    if(tileAnother.isVisible) {
                        matrixColors[row][col].isVisible = caculateDMax(tileActual.colorsRGB,tileAnother.colorsRGB);
                    }
                }
            }
        }
    }

    bool caculateDMax(glm::vec3 actual, glm::vec3 another){

        int actualR = actual.x*255;
        int actualG = actual.y*255;
        int actualB = actual.z*255;

        int anotherR = another.x*255;
        int anotherG = another.y*255;
        int anotherB = another.z*255;


        float dActual = ( (0-actualR)^2 + (0-actualG)^2 + (0-actualB)^2 )^(1/2);

        float dAnother = ( (0-anotherR)^2 + (0-anotherG)^2 + (0-anotherB)^2 )^(1/2);


        float limiteMin = dActual * 0.7f;
        float limiteMax = dActual * 1.3f;

        if(dAnother>limiteMin&&dAnother<limiteMax){
            return false;
        }else{
            if(actualR==anotherR&&actualG==anotherG&&actualB==anotherB){
                return false;
            }
            return true;
        }
    }

    void draw(Shader *shaderProgram) {

        // Define shaderProgram como o shader a ser utilizado
        shaderProgram->UseProgramShaders();

        // Define em quais vertices sera desenhado pelo shader
        vertices->bind(shaderProgram);

        for (int row = 0; row < numRows; row++) {
            for (int col = 0; col < numCols; col++) {

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

#endif //GAMEOFCOLORS_COLORTILE_H
