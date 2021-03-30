//
//
//

#ifndef MAPPER_H
#define MAPPER_H

#include <string>

class BasicRaster 
{
    int m_width;
    int m_height;
    std::string m_id;

public:
    BasicRaster();
    BasicRaster(int w, int h, std::string const &id);

    virtual ~BasicRaster();

public:
    std::string id() const;
    int width() const;
    int height() const;

};

#endif

// end of file Mapper.h
