#include "functions.hpp"
#include <memory>

class Texture
{
private:
    const char* _path;
    int _colorType;
    int _nrChannels;

public:
    GLuint* object; 
    bool linearFiltering;
    int _width, _height;

    Texture(const char* filePath, bool linFiltering, int rgbType, GLuint* obj) : _path(filePath), linearFiltering(linFiltering), 
    _colorType(rgbType), object(obj)
    {   
        ReloadTexture(linFiltering);
    } 

    void ReloadTexture(bool);
};