#ifndef PROJETO_PG_GA_SPRITESHEET_H
#define PROJETO_PG_GA_SPRITESHEET_H

#pragma once
class SpriteSheet
{
public:
	Texture* texture;
	int rows;
	int columns;
	int currentRow;
	int currentColumn;
	float z;

	SpriteSheet(string filename, bool useAlpha, int columns, int rows, float z) {
        this->texture = new Texture(filename, useAlpha);
		this->rows = rows;
        this->columns = columns;
        this->currentRow = 0;
        this->currentColumn = 0;
        this->z = z;

	};

	~SpriteSheet();

	void passUniformsToShader(Shader* shaderProgram) {
		texture->passUniformsToShader(shaderProgram, getOffsetX(), getOffsetY(), z );
	}

	float getOffsetX() {
		return (float)1 / columns * (currentColumn % columns);
	}

	float getOffsetY() {
		return 1.00f - (1.00f / rows * (currentRow % rows));
	}

	void nextColumn() {
		currentColumn++;
	}

    void setRow(int a) {
        currentRow = a;
    }

    void setColumn(int a) {
        currentColumn = a;
    }

    int getIDSomeTile(int which_col, int which_row){
        return which_col + (columns * which_row);
	}
};

SpriteSheet::~SpriteSheet()
{
	delete texture;
}
#endif
