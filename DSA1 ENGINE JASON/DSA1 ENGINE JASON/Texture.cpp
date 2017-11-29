#include "Texture.h"



Texture::Texture()
{

}


Texture::~Texture()
{
}

void Texture::use()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void Texture::load(std::string textureloc)
{
	

	FIBITMAP* image = FreeImage_Load(FreeImage_GetFileType(textureloc.c_str(), 0), textureloc.c_str());//(get type in cstring, filepath in cstring)
	if (image == nullptr) {
		//load failed 
		std::cout << "\n texture load failed " << std::endl;
		return;
	}
	FIBITMAP* image32Bit = FreeImage_ConvertTo32Bits(image);//change image to 32bit bitmap

															//unloadimage since it is no longer needed
	FreeImage_Unload(image);

	//genandbind new texture
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//Upload textureBytes
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, (FreeImage_GetWidth(image32Bit)),
		(FreeImage_GetHeight(image32Bit)), 0, GL_BGRA, GL_UNSIGNED_BYTE,
		(void*)(FreeImage_GetBits(image32Bit)));
	//filters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);//set filtertolinear insteadof mipmap linear
																	 //unload image32 since it's no longer needed
	FreeImage_Unload(image32Bit);
	
	glBindTexture(GL_TEXTURE_2D, 0);//unbind when finished

}

