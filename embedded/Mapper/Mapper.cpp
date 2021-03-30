//
//
//

#include "Mapper.h"

//
//
//
BasicRaster::BasicRaster()
    : m_width(0)
    , m_height(0)
    , m_id{}
{
}

BasicRaster::BasicRaster(int w, int h, std::string const& id)
    : m_width(w)
    , m_height(h)
    , m_id(id)
{
}

BasicRaster::~BasicRaster()
{
}

std::string BasicRaster::id() const
{
    return std::string();
}

int BasicRaster::width() const
{
    return 0;
}

int BasicRaster::height() const
{
    return 0;
}

#if MAPPER_BUILD_TEST
#include <gtest/gtest.h>

class MapperTestF : public ::testing::Test
{
};

TEST_F(MapperTestF, t1)
{

}
#endif

// end of file
