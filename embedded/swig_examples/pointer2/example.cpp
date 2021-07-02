//
//
//

#if _WIN32
#   define _CRT_SECURE_NO_DEPRECATE
#   define _CRT_NONSTDC_NO_WARNINGS
#endif

#include "example.h"

#include <stdio.h>
#include <string.h>

#define MAX_LAYER 16

static layer_handle_t all_layers[MAX_LAYER];
static layer_info_t all_layer_info[MAX_LAYER];
static size_t all_layer_count = 0;

layer_handle_t* LoadedLayerList(size_t* listSize)
{
    if (listSize == 0)
        return NULL;

    *listSize = all_layer_count;
    return all_layers;
}

// returns NULL if error
layer_handle_t LoadLayer(const char* filename)
{
    if (filename == NULL)
        return NULL;
    if (strcmp(filename, "error.tif") == 0)
        return NULL;
    if (all_layer_count < MAX_LAYER) {
        all_layer_info[all_layer_count].description = strdup(filename);
        all_layers[all_layer_count] = &all_layer_info[all_layer_count];
        ++all_layer_count;

        return all_layers[all_layer_count - 1];
    }
    return NULL;
}

layer_info_t const* GetLayerInfo(layer_handle_t h)
{
    layer_info_t* pos = (layer_info_t*)h;

    return pos;
}

const char *RunInfoQuery(layer_info_query_t const* query)
{
    if (query == NULL)
        return NULL;

    static char buffer[1024];
    buffer[0] = 0;

    sprintf(buffer, "Flags: 0x%08x, Total: %ld items", query->m_flags, (long)query->m_list_size);

    for (int i = 0; i != query->m_point_list_size; ++i)
    {
        printf("%i -> (%f, %f)\n", i, query->m_point_list[i].x, query->m_point_list[i].y);
    }

    return buffer;
}

