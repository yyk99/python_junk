//
//
//

#ifndef POINTER2_EXAMPLE_H
#define POINTER2_EXAMPLE_H

//
// A group of samples to issustrate void * handling
//

#include <stdint.h>

typedef void *layer_handle_t;
typedef void *entity_handle_t;

typedef struct {
    char* description;
} layer_info_t;


// returns NULL if error
// listSize == 0 if list is empty
layer_handle_t* LoadedLayerList(size_t* listSize);

layer_handle_t LoadLayer(const char* filename);

layer_info_t const *GetLayerInfo(layer_handle_t h);

typedef struct {
    uint32_t m_flags; // The flag field
    entity_handle_t* m_list;
    size_t m_list_size;
} layer_info_query_t ;

const char* RunInfoQuery(layer_info_query_t const* query);
#endif
