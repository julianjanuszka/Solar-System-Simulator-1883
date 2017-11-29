#include "Model.h"



Model::Model()
{
	vertArr = 0;
	vertCount = 0;

}


Model::~Model()
{
}

bool Model::Buffer(std::string objfile)
{
	//variables declared
	std::vector<glm::vec3> locations, normals;
	std::vector<glm::vec2> uvs;
	std::vector<VertInd> vertInds;

	//open obj file
	std::ifstream input;
	input.open(objfile);

	if (!input.is_open()) {
		std::cout << "File Failed to open";
		return false;
	}
	
	std::string line;
	//WHile looking over each line
	while (std::getline(input, line)) {
		std::istringstream a(line);
		//read label
		std::string label;
		a >> label;
		if (label == "v") {
			//read 3 floats from line
			float b, c, d;
			a >> b >> c >> d;
			glm::vec3 loc(b, c, d);
			locations.push_back(loc);

		}
		else if (label == "vt") {
			//read 2 floats from line
			float b, c;
			a >> b >> c;
			glm::vec2 uv(b, c);
			uvs.push_back(uv);
		}
		else if (label == "vn") {
			//read 3 floats from line
			float b, c, d;
			a >> b >> c >> d;
			glm::vec3 norm(b, c, d);
			normals.push_back(norm);
		}
		else if (label == "f") {
			//read 3 float from line
			unsigned int b, c, d;
			char slash;
			for (int i = 0; i < 3; i++) {
				a >> b >> slash >> c >> slash >> d;
				b--;
				c--;
				d--;

				VertInd thing;
				thing.locInd = b;
				thing.uvInd= c;
				thing.normInd = d;
				//push it back
				vertInds.push_back(thing);
			}


		}


	}
	//close file
	input.close();

	std::cout << "size of Location " << sizeof(locations) << std::endl;
	std::cout << "size of Uv " << sizeof(uvs) << std::endl;
	std::cout << "size of normals " << sizeof(normals) << std::endl;
	//for each vertInd, fill the vertbuffer with verts
	vertCount = vertInds.size();
	std::vector<Vertex> vertBufData(vertCount);
	for (unsigned int i = 0; i < vertCount; i++)
	{
		vertBufData[i] = { locations[vertInds[i].locInd],
						  uvs[vertInds[i].uvInd],
						normals[vertInds[i].normInd]
							};
	}
	
	//finding the furtherest radius
	for (glm::vec3& var : locations)
	{	
		float currentrad = pow(pow(var.x, 2) + pow(var.y, 2) + pow(var.z, 2), .5);
		if (currentrad > maxradius) {
			maxradius = currentrad;
		}
		if (var.x > maxx) {
			maxx = var.x;
		}
		if (var.y > maxy) {
			maxy = var.y;
		}
		if (var.z > maxz) {
			maxz = var.z;
		}
		if (var.x < minx) {
			minx = var.x;
		}
		if (var.y > miny) {
			miny = var.y;
		}
		if (var.z > minz) {
			minz = var.z;
		}
	}


	//generate buffers
	GLuint vertBuf;
	
	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertCount, &vertBufData[0], GL_STATIC_DRAW);


	//(attribute index, number of components, data type, normalized, stride(bytes per vertex), offset)
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	//(attribute index, number of components, data type, normalized, stride(bytes per vertex), offset)
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),(void*) sizeof(glm::vec3));

	//(attribute index, number of components, data type, normalized, stride(bytes per vertex), offset)
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(float)*5));
	//unbind to finish
	glBindVertexArray(0);
	

	//nicely tell the person they did good 
	std::cout << "finished";
	return true;
}

void Model::render()
{

	glBindVertexArray(vertArr);
	glDrawArrays(GL_TRIANGLES, 0, vertCount);
	glBindVertexArray(0);

}
