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
#ifndef AT_ARRAY_H
#define AT_ARRAY_H
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <at/core/macro.h>
AT_BEGIN_DECLS
/*=============================================================================
 STRUCTURE
 ============================================================================*/
/**
 * @brief @~Brazilian Cabeçalho do Vetor Multidimensional
 *
 *
 * Multidimensional Array (
 */
typedef struct AtArrayHeader{
  uint64_t* shape;       // 00-07: size of each dimension
  uint64_t* step;        // 08-15: offset between consecutive elements
                         //              of each dimension
  uint64_t  num_elements;// 16-23: total number of elements
  uint8_t   dim;         // 24-24: dimension
  uint8_t   owns_data;   // 25-25: true if they can delete its own data
  uint8_t   alignment[6];// 26-31: explicit padding
}AtArrayHeader;          // Total: 32B

#define AtArray(type) AtArray_##type

/**
 * @brief @~Brazilian Vetor Multidimensional
 *
 * Para criar um vetor, é necessário saber a dimensão (`dim`) e o tamanho
 * (`shape`) de cada uma. Por exemplo, podemos criar uma matriz bidimensional
 * 5x4: dim = 2 e `shape={5,4}`. Note-se que o tamanho é {Y,X} e não {X,Y}, e
 * dimensões adicionais devem ser colocadas primeiro ({Z,Y,X} por exemplo).
 * dimensão é uint8 e shape é um array de uint64.
 */
typedef struct AtArray_uint8_t{
  AtArrayHeader h;  // 00-31
  uint8_t      *data;    // 32-39
}AtArray_uint8_t;        // Total: 40B
typedef struct AtArray_uint16_t{
  AtArrayHeader h;
  uint16_t     *data;
}AtArray_uint16_t;
typedef struct AtArray_uint32_t{
  AtArrayHeader h;
  uint32_t     *data;
}AtArray_uint32_t;
typedef struct AtArray_uint64_t{
  AtArrayHeader h;
  uint64_t     *data;
}AtArray_uint64_t;
typedef struct AtArray_int8_t{
  AtArrayHeader h;
  int8_t       *data;
}AtArray_int8_t;
typedef struct AtArray_int16_t{
  AtArrayHeader h;
  int16_t      *data;
}AtArray_int16_t;
typedef struct AtArray_int32_t{
  AtArrayHeader h;
  int32_t      *data;
}AtArray_int32_t;
typedef struct AtArray_int64_t{
  AtArrayHeader h;
  int64_t      *data;
}AtArray_int64_t;
typedef struct AtArray_float{
  AtArrayHeader h;
  float        *data;
}AtArray_float;
typedef struct AtArray_double{
  AtArrayHeader h;
  double       *data;
}AtArray_double;

/*=============================================================================
 FUNCTIONS
 ============================================================================*/

void
at_index_to_nd(uint8_t dim, uint64_t* step, uint64_t s, uint64_t* s_nd);

void
at_index_to_1d(uint8_t dim, uint64_t* step, int64_t* s_nd, uint64_t* s);
#define at_array_index_to_nd(array, s, s_nd) at_index_to_nd(array->h.dim, array->h.step,s,s_nd)
#define at_array_index_to_1d(array, s_nd, s) at_index_to_1d(array->h.dim, array->h.step,s_nd,s)

#define at_array_max(array) _Generic((array), \
  AtArray_uint8_t*:at_array_uint8_t_max)(array)

void
at_array_header_init(AtArrayHeader* header);

void
at_array_header_set(AtArrayHeader* header, uint8_t dim, uint64_t* shape);

void
at_array_header_dispose(AtArrayHeader* header);


#define at_array_destroy(array_ptr) _Generic((array_ptr), \
  AtArray_uint8_t**: at_array_uint8_t_destroy             \
)(array_ptr)

// uint8_t
// --------
AtArray_uint8_t*
at_array_uint8_t_create();

AtArray_uint8_t*
at_array_uint8_t_new(uint8_t dim, uint64_t* shape);

AtArray_uint8_t*
at_array_uint8_t_new_with_data(uint8_t dim, uint64_t* shape, uint8_t* data, bool copy);

AtArray_uint8_t*
at_array_uint8_t_zeros(uint8_t dim, uint64_t* shape);

AtArray_uint8_t*
at_array_uint8_t_ones(uint8_t dim, uint64_t* shape);

void
at_array_uint8_t_fill(AtArray_uint8_t* array, uint8_t value);

uint8_t
at_array_uint8_t_max(AtArray_uint8_t* array);

void
at_array_uint8_t_destroy(AtArray_uint8_t** array);

// uint16_t
// --------
AtArray_uint16_t*
at_array_uint16_t_new(uint8_t dim, uint64_t* shape);

void
at_array_uint16_t_destroy(AtArray_uint16_t** arp);

// uint64_t
// --------

AtArray_uint64_t*
at_array_uint64_t_create();

AtArray_uint64_t*
at_array_uint64_t_new_with_data(uint8_t dim, uint64_t* shape, uint64_t* data, bool copy);

void
at_array_uint64_t_fill(AtArray_uint64_t* array, uint64_t value);

void
at_array_uint64_t_destroy(AtArray_uint64_t** array);
AT_END_DECLS
#endif