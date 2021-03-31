//
//
//
#define _CRT_NONSTDC_NO_WARNINGS

#include "ControlCenter.h"
#include "Mapper.h"

#include <string.h>

template<class T>
void *duplicate_vector( T const *src, size_t s )
{
    T *dst = (T *)malloc( s * sizeof( T ) );
    memcpy( dst, src, s * sizeof( T ) );

    return dst;
}

ControlCenter::ControlCenter()
{
}

ControlCenter::~ControlCenter()
{
}

char *ControlCenter::CreateRaster(const char *filename)
{
    auto theRaster = new BasicRaster( 128, 64, filename );
    m_inventory.push_back( theRaster );

    return strdup( theRaster->id().c_str() );
} // end of function ControlCenter::CreateRaster

list_t *ControlCenter::ListRasters() const
{
    list_t *lst = new list_t( (int)m_inventory.size(), duplicate_vector( m_inventory.data(), m_inventory.size() ) );

    return lst;
}

list_t::list_t
    (
    int s, void *d
    )
    : m_size(s), m_data(d)
{
} // end of function list_t::list_t
