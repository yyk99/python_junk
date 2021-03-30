//
//
//

#ifndef CONTROLCENTER_H
#define CONTROLCENTER_H

#include <vector>

class BasicRaster;

struct list_t
{
    list_t( int s, void *d );
    int m_size;
    void *m_data;
};


class ControlCenter
{
    std::vector<BasicRaster*> m_inventory;

public:
    ControlCenter();

    virtual ~ControlCenter();

    char *CreateRaster(const char *filename);
    list_t *ListRasters() const;
};

#endif