/**
 ** This file is part of the atkv project.
 ** Copyright 2016 Anderson Tavares <nocturne.pe@gmail.com>.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/
#include <at/core/array.h>
#include <at/core/macro.h>
/*=============================================================================
 PRIVATE API
 ============================================================================*/
/*=============================================================================
 PUBLIC API
 ============================================================================*/

void
at_array_header_init(AtArrayHeader* header){
  memset(header,0,sizeof(AtArrayHeader));
  header->owns_data = 1;
}

void
at_array_header_set(AtArrayHeader* header, uint8_t dim, uint64_t* shape){
  size_t   num_bytes = dim*sizeof(uint64_t);
  uint64_t tmp = 1;
  uint8_t  i;
  header->dim      = dim;
  header->shape    = (uint64_t*) realloc(header->shape,num_bytes << 1);
  header->step     = &header->shape[dim];
  memcpy(header->shape, shape, dim*sizeof(uint64_t));
  for(i = dim-1; i < dim; i--){
    header->step[i] = tmp;
    tmp *= header->shape[i];
  }
  header->num_elements = header->step[0] * header->shape[0];
}

AtArray_uint8_t*
at_array_uint8_t_create(){
  AtArray_uint8_t* array = malloc(sizeof(AtArray_uint8_t));
  at_array_header_init(&array->h);
  array->data = NULL;
  return array;
}
AtArray_uint64_t*
at_array_uint64_t_create(){
  AtArray_uint64_t* array = malloc(sizeof(AtArray_uint64_t));
  at_array_header_init(&array->h);
  array->data = NULL;
  return array;
}

AtArray_uint8_t*
at_array_uint8_t_new(uint8_t dim, uint64_t* shape){
  AtArray_uint8_t* array = at_array_uint8_t_create();
  at_array_header_set(&array->h, dim, shape);
  array->data = malloc(array->h.num_elements * sizeof(uint8_t));
  return array;
}

AtArray_uint8_t*
at_array_uint8_t_new_with_data(uint8_t dim, uint64_t* shape, uint8_t* data, bool copy){
  AtArray_uint8_t* array = at_array_uint8_t_create();
  uint64_t num_bytes;
  at_array_header_set(&array->h, dim, shape);

  if(!copy)
    array->data = data;
  else{
    num_bytes   = array->h.num_elements * sizeof(uint8_t);
    array->data = malloc(num_bytes);
    memcpy(array->data, data, num_bytes);
  }
  return array;
}

AtArray_uint64_t*
at_array_uint64_t_new_with_data(uint8_t dim, uint64_t* shape, uint64_t* data, bool copy){
  AtArray_uint64_t* array = at_array_uint64_t_create();
  uint64_t num_bytes;
  at_array_header_set(&array->h, dim, shape);

  if(!copy)
    array->data = data;
  else{
    num_bytes   = array->h.num_elements * sizeof(uint64_t);
    array->data = malloc(num_bytes);
    memcpy(array->data, data, num_bytes);
  }
  return array;
}

void
at_array_uint8_t_fill(AtArray_uint8_t* array, uint8_t value){
  memset(array->data,value,array->h.num_elements * sizeof(uint8_t));
}

uint8_t
at_array_uint8_t_max(AtArray_uint8_t* array){
  uint64_t i;
  uint8_t  value = 0;
  for(i = 0; i < array->h.num_elements; i++)
    value = max(value, array->data[i]);
  return value;
}

void
at_array_uint64_t_fill(AtArray_uint64_t* array, uint64_t value){
  uint64_t i;
  if(value == 0) memset(array->data, 0, array->h.num_elements * sizeof(uint64_t));
  else
    for(i = 0; i < array->h.num_elements; i++)
      array->data[i] = value;
}

AtArray_uint8_t*
at_array_uint8_t_zeros(uint8_t dim, uint64_t *shape){
  AtArray_uint8_t* array = at_array_uint8_t_new(dim, shape);
  at_array_uint8_t_fill(array,0);
  return array;
}
AtArray_uint8_t*
at_array_uint8_t_ones(uint8_t dim, uint64_t *shape){
  AtArray_uint8_t* array = at_array_uint8_t_new(dim, shape);
  at_array_uint8_t_fill(array,1);
  return array;
}


void
at_array_uint8_t_destroy(AtArray_uint8_t** array_ptr){
  if(array_ptr){
    AtArray_uint8_t* array = *array_ptr;
    if(array){
      if(array->h.owns_data)
        free(array->data);
      at_array_header_dispose(&array->h);
      free(array);
    }
    *array_ptr = NULL;
  }
}

void
at_index_to_nd(uint8_t dim, uint64_t* step, uint64_t s, uint64_t* s_nd){
  uint8_t i;
  for(i = 0; i < dim; i++){
    s_nd[i]  = s/step[i];
    s       %= step[i];
  }
}

void
at_index_to_1d(uint8_t dim, uint64_t* step, int64_t* s_nd, uint64_t* s){
  uint8_t i;
  *s = 0;
  for(i = 0; i < dim; i++)
    *s += s_nd[i] * step[i];
}

#define at_array_index_to_nd(array, s, s_nd) at_index_to_nd(array->h.dim, array->h.step,s,s_nd)
#define at_array_index_to_1d(array, s_nd, s) at_index_to_1d(array->h.dim, array->h.step,s_nd,s)

AtArray_uint16_t*
at_array_uint16_t_create(){
  AtArray_uint16_t* array = malloc(sizeof(AtArray_uint16_t));
  at_array_header_init(&array->h);
  array->data = NULL;
  return array;
}
AtArray_uint16_t*
at_array_uint16_t_new(uint8_t dim, uint64_t* shape){
  AtArray_uint16_t* array = at_array_uint16_t_create();
  at_array_header_set(&array->h, dim, shape);
  array->data = malloc(array->h.num_elements * sizeof(uint16_t));
  return array;
}

void
at_array_uint16_t_destroy(AtArray_uint16_t** arp){
  if(arp){
    AtArray_uint16_t* ar = *arp;
    if(ar){
      if(ar->h.owns_data)
        free(ar->data);
      at_array_header_dispose(&ar->h);
      free(ar);
    }
    *arp = NULL;
  }
}


void
at_array_uint64_t_destroy(AtArray_uint64_t** array_ptr){
  if(array_ptr){
    AtArray_uint64_t* array = *array_ptr;
    if(array){
      if(array->h.owns_data)
        free(array->data);
      at_array_header_dispose(&array->h);
      free(array);
    }
    *array_ptr = NULL;
  }
}

void
at_array_header_dispose(AtArrayHeader* header){
  free(header->shape);
}