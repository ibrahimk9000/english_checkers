
#include "texture.h"
std::string texture::cwd(const std::string &res)
{
	char currwd[FILENAME_MAX];
	std::string resu;

	if (getcwd(currwd, sizeof(currwd)) != NULL)
	{
		resu = currwd;
		resu += DEFSL + res;
	}
	return resu;
}
void texture::init(const std::string &path)
{

	try
	{

		if (!textu.loadFromFile(cwd(path))) //load texture if path not found throw error
			throw 1;
	}
	catch (int)
	{
#ifdef _WIN32
		std::string err = cwd(path);
		err += " not found";
		MessageBoxA(NULL, err.c_str(), "Error!", MB_ICONEXCLAMATION | MB_OK);

#elif __linux__
		std::cerr << cwd(path) << " not found";

#endif
		throw;
	}
}
sf::Texture *texture::map()
{

	return &textu;
}
