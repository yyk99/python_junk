//
//
//

#include "ControlCenter.h"
#include "Mapper.h"

ControlCenter::ControlCenter()
{
}

ControlCenter::~ControlCenter()
{
}

std::string ControlCenter::CreateRaster(std::string const& filename)
{
    auto theRaster = new BasicRaster(128, 64, filename);
    m_inventory.push_back(theRaster);

    return theRaster->id();
}

std::vector<BasicRaster*> const& ControlCenter::ListRasters() const
{
    return m_inventory;
}
