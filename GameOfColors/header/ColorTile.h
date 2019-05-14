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


                ///TEM ERRO
                glUniform3fv(
                        glGetUniformLocation(shaderProgram->Program, "colorValues"), 1,
                        glm::value_ptr(tile.colorsRGB));


                // Define em quais vertices sera desenhado pelo shader
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            }
        }

    }

};

#endif //GAMEOFCOLORS_COLORTILE_H
