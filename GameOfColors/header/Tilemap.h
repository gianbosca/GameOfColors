#pragma once
class Tilemap
{
public:
	int numRows, numCols;
    float tileWidth, tileHeight;

    glm::mat4 modelMatrix;

	SpriteSheet* tileset;
	VerticesObject* vertices;

    Tilemap(float totalWidth, float totalHeight, int numRows, int numCols);
	void draw(Shader *shaderProgram);
	void setupVertices(float width, float height);
	~Tilemap();
	
};

Tilemap::Tilemap(float totalWidth, float totalHeight, int numRows, int numCols)
{
	this->tileset = new SpriteSheet("../resource/tileset.png",true, 64, 48, -0.10f);
    //this->tileset = new SpriteSheet("resource/warrior.png",true, 8, 2, -0.10f);
    //this->tileset = new SpriteSheet("resource/Terrain_Tileset.png",true, 6, 1, -0.10f);
	this->numRows = numRows;
	this->numCols = numCols;

	this->tileWidth = totalWidth / (float)numCols;
	this->tileHeight = totalHeight / (float)numRows;

	this->modelMatrix = glm::mat4(1);

	this->setupVertices(tileWidth, tileHeight);
}

void Tilemap::setupVertices(float width, float height) {
	/*
		Comeca centralizado no zero
	*/
	float verticesCoordinates[] = {
		// positions						// texture coords
		-width / 2.0f, -height / 2.0f, 0.0f,		0.0f,						1.0f,									// top left
		-width / 2.0f, height / 2.0f,  0.0f,		0.0f,						1.00f - (1.00f / (float)tileset->rows),	// bottom left
		width  / 2.0f, height / 2.0f,  0.0f,		1.00f / (float)tileset->columns, 1.00f - (1.00f / (float)tileset->rows),	// bottom right
		width  / 2.0f, -height / 2.0f, 0.0f,		1.00f / (float)tileset->columns, 1.0f,									// top right
	};

	vertices = new VerticesObject(verticesCoordinates, 20);

}


void Tilemap::draw(Shader *shaderProgram) {
//    int mapa[10][10] ={
//            {836, 837, 838, 836, 837, 838, 836, 837, 838, 836},
//            {832, 833, 834, 832, 833, 834, 832, 833, 834, 832},
//            {836, 837, 838, 836, 837, 838, 836, 837, 838, 836},
//            {832, 833, 834, 832, 833, 834, 832, 833, 834, 832},
//            {836, 837, 838, 836, 837, 838, 836, 837, 838, 836},
//            {832, 833, 834, 832, 833, 834, 832, 833, 834, 832},
//            {836, 837, 838, 836, 837, 838, 836, 837, 838, 836},
//            {832, 833, 834, 832, 833, 834, 832, 833, 834, 832},
//            {836, 837, 838, 836, 837, 838, 836, 837, 838, 836},
//            {832, 833, 834, 832, 833, 834, 832, 833, 834, 832}
//    };

//    int gr = tileset->getIDSomeTile(54,15);
//
//    int mapa[10][10] ={
//            {gr, gr, gr, gr, gr, tileset->getIDSomeTile(20,6), gr, gr, gr, gr},
//            {gr, gr, gr, gr, gr, gr, gr, gr, gr, gr},
//            {gr, gr, gr, gr, gr, gr, gr, gr, gr, gr},
//            {gr, gr, gr, gr, gr, gr, gr, gr, gr, gr},
//            {gr, gr, gr, gr, gr, 199, gr, gr, gr, gr},
//            {gr, gr, gr, gr, gr, gr, gr, gr, gr, gr},
//            {gr, gr, gr, gr, gr, gr, gr, gr, gr, gr},
//            {gr, gr, gr, gr, gr, gr, gr, gr, gr, gr},
//            {gr, gr, gr, gr, gr, gr, gr, gr, gr, gr},
//            {gr, gr, gr, gr, gr, gr, gr, gr, gr, gr}
//    };

    int mapa[20][25] = {
   {962,963,963,963,963,963,963,963,963,963,963,963,963,970,969,963,963,963,963,963,963,963,963,963,963},
   {962,963,963,963,963,963,963,963,963,963,963,963,963,974,957,963,963,963,963,963,963,963,963,963,963},
   {970,968,968,968,968,969,963,963,963,970,969,963,963,974,957,963,963,963,963,963,963,963,963,963,963},
   {973,971,971,971,971,972,963,963,963,974,957,963,963,974,957,963,963,970,968,968,968,968,969,963,963},
   {962,963,963,963,963,963,963,963,963,974,957,963,963,974,957,963,963,973,971,971,971,971,972,963,963},
   {962,963,963,963,963,963,963,963,963,974,957,963,963,974,957,963,963,970,969,963,963,963,970,969,963},
   {962,963,963,970,968,968,968,968,969,974,957,963,963,974,957,963,963,967,967,963,963,963,974,957,963},
   {962,963,963,973,971,971,971,971,972,973,972,963,963,974,957,963,963,967,967,963,963,963,974,957,963},
   {963,963,963,963,963,963,963,963,963,963,963,961,961,974,957,963,963,973,972,963,963,963,974,957,963},
   {963,963,963,963,963,963,963,963,963,963,963,961,961,974,957,963,963,963,963,963,963,963,974,957,963},
   {968,968,968,968,968,969,963,963,963,970,969,961,961,974,957,963,963,963,963,963,963,963,973,972,963},
   {971,971,971,971,967,957,963,963,963,974,957,961,961,973,972,963,963,967,967,967,967,967,967,967,967},
   {962,963,963,963,974,957,963,963,963,974,957,961,961,961,961,963,963,967,967,967,967,967,967,967,967},
   {962,963,963,963,973,972,963,963,963,974,957,961,963,961,961,963,963,963,963,963,963,963,963,963,963},
   {962,963,963,963,963,963,963,963,963,974,957,961,961,961,961,963,963,963,963,963,963,963,963,963,963},
   {962,963,963,963,963,963,963,963,963,973,972,961,961,961,961,963,967,967,963,963,970,969,963,963,963},
   {970,968,968,968,968,969,963,963,970,968,968,968,968,969,961,963,967,967,963,963,967,967,963,963,963},
   {973,971,971,971,971,972,963,963,973,971,971,971,971,972,961,963,967,967,963,963,973,972,963,963,963},
   {966,966,966,963,963,963,963,963,963,963,963,961,961,961,961,963,967,967,963,963,963,963,963,963,963},
   {966,966,966,963,963,963,963,963,963,963,963,961,961,961,961,963,967,967,963,963,963,963,963,963,963}
    };

    // Define shaderProgram como o shader a ser utilizado
    shaderProgram->UseProgramShaders();

    // Define qual textura sera desenhada pelo shader
    tileset->texture->bind(shaderProgram);

    // Define em quais vertices sera desenhado pelo shader
    vertices->bind(shaderProgram);

    for (int col = 0; col < numCols; col++) {
        for (int row = 0; row < numRows; row++) {


            float xi = col*tileWidth  + tileWidth/2;
            float yi = row*tileHeight + tileHeight/2;

            modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(xi, yi, 0.0));

            //define aonde desenhar
            glUniformMatrix4fv(
               glGetUniformLocation(shaderProgram->Program, "matrix_OBJ"), 1,
                  GL_FALSE, glm::value_ptr(modelMatrix));

            //seleciona o tileset a ser desenhado
            int id_tile = mapa[row][col];
            tileset->setColumn((int)(id_tile % tileset->columns));
            tileset->setRow((int)(id_tile / tileset->columns));

            //passa o tileset selecionado para o shader
            tileset->passUniformsToShader(shaderProgram);

            // Define em quais vertices sera desenhado pelo shader
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
    }
}

Tilemap::~Tilemap()
{
	delete tileset;
}
