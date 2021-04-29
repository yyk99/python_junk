//
//
//

#ifndef POINTER2_EXAMPLE_H
#define POINTER2_EXAMPLE_H

typedef void* layer_handle_t;

typedef struct {
    char* description;
} layer_info_t;


// returns NULL if error
// listSize == 0 if list is empty
layer_handle_t* LoadedLayerList(size_t* listSize);

layer_handle_t LoadLayer(const char* filename);

layer_info_t const *GetLayerInfo(layer_handle_t h);


#endif
