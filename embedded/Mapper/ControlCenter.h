//
//
//

#ifndef CONTROLCENTER_H
#define CONTROLCENTER_H

#include <string>
#include <vector>

class BasicRaster;
class ControlCenter
{
    std::vector<BasicRaster*> m_inventory;

public:
    ControlCenter();

    virtual ~ControlCenter();

    std::string CreateRaster(std::string const &filename);
    std::vector<BasicRaster*> const& ListRasters() const;
};

#endif