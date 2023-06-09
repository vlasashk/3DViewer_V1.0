/**
 * @file s21_3dviewer.h
 * @author Team (TL: nidorina@student.21-school.ru)
 * nidorina@student.21-school.ru
 * karynkas@student.21-school.ru
 * @brief s21 3dvewer header
 * @version 0.1
 * @date 2023-05-17
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef SRC_3DVIEWER_BACK_3DVIEWER_H_
#define SRC_3DVIEWER_BACK_3DVIEWER_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE (16 * 4096)  //!< 64KB buffer
#define DIMEN 3                //!< dimension of space

/**
 * @enum
 * @brief useful state
 */
enum st {
  FALSE,        //!< logical false=0
  TRUE,         //!< logical true=1
  SUCCESS = 0,  //!< process status success=0
  FAIL,         //!< process status fail=1
};

/**
 * @typedef
 * @brief structure that contain one facet
 */
typedef struct {
  unsigned int *vertexes; /*<! array of vtx needed to connect*/
} polygon_t;

/**
 * @typedef
 * @brief structure that contain axis min/max info
 */
typedef struct {
  double x_min;
  double x_max;
  double y_min;
  double y_max;
  double z_min;
  double z_max;
} axis_t;

/**
 * @typedef
 * @brief structure that contain axis center info
 */
typedef struct {
  double x_center;
  double y_center;
  double z_center;
} centers_t;

/**
 * @typedef
 * @brief struct that contain 3d object
 */
typedef struct {
  unsigned int vtx_count;     /*!< count of vertexes*/
  unsigned int fct_count;     /*!< count of facets*/
  unsigned int *fct_vtx;      /*!< connected vtx for poligon*/
  unsigned int total_indices; /*!< total amount of all facets indices*/
  polygon_t *polygons;        /*!< array of facets*/
  double *vet_arr;            /*!< array of vertexes x1,y1,z1,x2..*/

  centers_t centers;
  axis_t bounds;
} obj3d;

/*---------------------------file operations-----------------*/

/**
 * @brief intializing obj3d struct with NULL and 0
 * @param[out] res ptr to allocated memory #obj3d struct
 * @sa used in read_obj()
 */
void initObj3d(obj3d *res);

/**
 * @brief parses main/max values for each axis (x, y, z)
 * @param[in] x x value of a point
 * @param[in] y y value of a point
 * @param[in] z z value of a point
 * @param[in] first_line flag to indicate first line for initializing values in
 * first iteration
 * @param[out] res ptr to allocated memory #obj3d struct
 * @sa used in fill_obj3d()
 */
void parseMaxMin(obj3d *res, double x, double y, double z, int first_line);

/**
 * @brief compares min and max axis values to passed comparable
 * @param[in] comparable the value with which the min and max values of the axes
 * are compared
 * @param[out] have_min min value of chosen axis
 * @param[out] have_max max value of chosen axis
 * @sa used in parseMaxMin()
 */
void compareNums(double *have_min, double *have_max, double comparable);

/**
 * @brief centers object in a window
 * @param[out] res ptr to allocated memory #obj3d struct
 * @sa used in read_obj()
 */
void centerObj(obj3d *res);

/**
 * @brief calculates the center of an axis
 * @param[out] minVal axis minimal value
 * @param[out] maxVal axis maximal value
 * @return double value a axis center
 * @sa used in centerObj()
 */
double centersFormula(double *minVal, double *maxVal);

/**
 * @brief try to open obj file to read and read it
 * @warning opened file doesn't close, don't forget to close it
 * @param[in] f_name file name string
 * @param[out] f ptr to opened file
 * @return int status #st enum
 * @sa next step is read_obj()
 */
int open_obj_file(char *f_name, FILE **f);
/**
 * @brief read 3d object file and count vertexes and facets
 * and set them to res->vtx_count and res->fct_count
 * and allocated memory for object and fill memory
 * @warning opened file doesn't close, don't forget to close it
 * @warning also don't forget to freeing an allocated memory after use it
 * @param[in] f ptr to obj file
 * @param[out] res ptr to obj3d sturcture in memory
 * @return int status of operation #st enum
 * @sa used after open_obj_file()
 * @sa contain s21_alloc_mem(), fill_obj3d()
 */
int read_obj(FILE *f, obj3d *res);

/**
 * @brief reading the file a second time and
 * parse vertexes and faces from the
 * file and fill it to memory structure
 * @param[in] f ptr to obj file
 * @param[out] res ptr to obj3d sturcture
 * @return int status of operation #st enum
 * @warning Don't forget to free memory free_obj3d()
 * @sa contain fill_facets()
 */
int fill_obj3d(FILE *f, obj3d *res);

/**
 * @brief allocating memory for obj3d sturcture
 * @param[out] res ptr to allocated memory #obj3d struct
 * @return int status of allocation 0-success 1-fail
 * @warning Don't forget to freeing an allocated memory after use it.
 * If allocate is fail, then isn't necessary to free_obj3d()
 * @warning if memory allocation fail then it free_obj3d()
 * @sa used in read_obj()
 */
int s21_alloc_mem(obj3d *res);

/**
 * @brief freeing allocated memory
 * @param[in] res ptr to ptr to allocated memory #obj3d struct
 * @sa used in s21_alloc_mem() and used by yourself
 */
void free_obj3d(obj3d **res);

/**
 * @brief count vertexes of facets, then
 * allocate memory for it and fill it
 * @param[in] buffer ptr to sting with property of facet
 * @param[out] obj ptr to 3d object #obj3d structure
 * @param[in] index index of current handled facet
 * @return int status of operation #st enum
 * @sa free_obj3d(), fill_obj3d()
 * @sa contain count_vtx_of_facet(), parse_vertices()
 */
int fill_facets(char *buffer, obj3d *obj, unsigned int index);

/**
 * @brief counts how many vertices are registered for the polygon
 * @param[in] buffer ptr to string of facet beginnig 'f' and separated by space
 * like "f 5 3 1"
 * @return int amount vertices
 * @sa used in fill_facets()
 */
unsigned int count_vtx_of_facet(char *buffer);

/**
 * @brief parse vertices from buffer and put it to obj3d
 * structure according their index and sequence number
 * @param[in] buffer string with facet property like "f 3/4/5 34//3 564"
 * @param[in] index index of facet in a row
 * @param[out] obj obj3d stucture that contain all the object
 * @return int count of vetices of the facet
 * @sa used in fill_facets()
 */
unsigned int parse_vertices(char *buffer, unsigned int index, obj3d *obj);

/*---------------------------affine operations-----------------*/

/**
 * @brief rescales object to fit in chosen scale factor
 * @param[in] scaleApply scale factor
 * @param[out] res ptr to allocated memory #obj3d struct
 * @sa used gui part for initial rescaling
 */
void rescaleObj(double scaleApply, obj3d *res);

/**
 * @brief rescales initial object to fit in chosen scale factor
 * @param[in] scaleVal scale factor
 * @param[out] res ptr to allocated memory #obj3d struct
 * @sa used gui part for initial rescaling
 */
void initialRescaleObj(double scaleVal, obj3d *res);

/**
 * @brief calculates the max distance between max and min of an axis amoung all
 * axes
 * @param[out] res ptr to allocated memory #obj3d struct
 * @return double value of a max distance between max and min of an axis
 * @sa used in rescaleObj()
 */
double findMaxAxisDistance(obj3d *res);

void moveX(double xVal, obj3d *res);
void moveY(double yVal, obj3d *res);
void moveZ(double zVal, obj3d *res);
void rotateX(double rotate, obj3d *res);
void rotateY(double rotate, obj3d *res);
void rotateZ(double rotate, obj3d *res);

#endif  // SRC_3DVIEWER_BACK_3DVIEWER_H_