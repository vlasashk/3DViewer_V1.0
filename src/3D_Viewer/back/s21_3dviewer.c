/**
 * @file s21_3dviewer.c
 * @brief Implementation of 3d model processing
 */
#include "./s21_3dviewer.h"

int open_obj_file(char *f_name, FILE **f) {
  *f = fopen(f_name, "r");
  if (!*f)
    fprintf(stderr, "s21_3dviewer: %s: no such file\n", f_name);
  else
    printf("file: %s is open ptr:%p\n", f_name, (void *)(*f));
  return (*f) ? SUCCESS : FAIL;
}

void initObj3d(obj3d *res) {
  res->vtx_count = 0;
  res->fct_count = 0;
  res->total_indices = 0;
  res->bounds.x_max = 0;
  res->bounds.x_min = 0;
  res->bounds.y_max = 0;
  res->bounds.y_min = 0;
  res->bounds.z_max = 0;
  res->bounds.z_min = 0;
  res->centers.x_center = 0;
  res->centers.y_center = 0;
  res->centers.z_center = 0;
  res->vet_arr = NULL;
  res->fct_vtx = NULL;
  res->polygons = NULL;
}

int read_obj(FILE *f, obj3d *res) {
  initObj3d(res);
  int status = FAIL;
  char buffer[BUFF_SIZE] = {0};
  while (fgets(buffer, BUFF_SIZE, f))
    if (buffer[0] == 'v' && buffer[1] == ' ')
      ++res->vtx_count;
    else if (buffer[0] == 'f' && buffer[1] == ' ')
      ++res->fct_count;
  if (res->fct_count && res->vtx_count) status = s21_alloc_mem(res);
  if (!status) {
    status = fill_obj3d(f, res);
    centerObj(res);
  }
  return (!status) ? SUCCESS : FAIL;
}

int s21_alloc_mem(obj3d *res) {
  res->vet_arr = (double *)calloc(res->vtx_count * DIMEN, sizeof(double));
  if (res->vet_arr)
    res->fct_vtx = (unsigned int *)calloc(res->fct_count, sizeof(unsigned int));
  if (res->fct_vtx)
    res->polygons = (polygon_t *)calloc(res->fct_count, sizeof(polygon_t));
  int status = (res->polygons) ? SUCCESS : FAIL;
  if (status) free_obj3d(&res);
  return status;
}

void free_obj3d(obj3d **res) {
  if ((*res)->polygons)
    for (unsigned int i = 0; i < (*res)->fct_count; ++i)
      if ((*res)->polygons[i].vertexes) free((*res)->polygons[i].vertexes);
  if ((*res)->vet_arr) {
    free((*res)->vet_arr);
    (*res)->vet_arr = NULL;
  }
  if ((*res)->fct_vtx) {
    free((*res)->fct_vtx);
    (*res)->fct_vtx = NULL;
  }
  if ((*res)->polygons) {
    free((*res)->polygons);
    (*res)->polygons = NULL;
  }
  if (*res) {
    free((*res));
    (*res) = NULL;
  }
}

int fill_obj3d(FILE *f, obj3d *res) {
  char buffer[BUFF_SIZE] = {0};
  int first_line = 0;
  fseek(f, 0, SEEK_SET); /* to begin of file*/
  unsigned int i = 0, j = 0, status = FAIL;
  double *arr = res->vet_arr;
  while (fgets(buffer, BUFF_SIZE, f)) {
    if (buffer[0] == 'v' && buffer[1] == ' ') {
      sscanf(buffer + 2, "%lf%lf%lf", &arr[i], &arr[i + 1], &arr[i + 2]);
      parseMaxMin(res, arr[i], arr[i + 1], arr[i + 2], first_line);
      first_line = 1;
      i += 3;
    } else if (buffer[0] == 'f' && buffer[1] == ' ') {
      status = fill_facets(buffer, res, j++);
    }
  }
  return (!status) ? SUCCESS : FAIL;
}

int fill_facets(char *buffer, obj3d *obj, unsigned int index) {
  unsigned int count = count_vtx_of_facet(buffer);
  obj->total_indices += count;
  obj->fct_vtx[index] = count;
  if (count > 0) {
    obj->polygons[index].vertexes =
        (unsigned int *)calloc(count, sizeof(unsigned int));
  }
  if (obj->polygons[index].vertexes) parse_vertices(buffer, index, obj);
  // if (count > 200) printf("idx=%d, vtx=%d\n", index, count);
  return (obj->polygons[index].vertexes) ? SUCCESS : FAIL;
}

unsigned int count_vtx_of_facet(char *buffer) {
  char str[255] = {0};
  unsigned int count = 0;
  buffer += 2; /* skip first f_ */
  while (*buffer && sscanf(buffer, "%s", str)) {
    unsigned int length = 0;
    length = strlen(str) + 1;
    buffer += length;
    if (length > 1) ++count; /*skip spaces*/
    strcpy(str, "");
  }
  return count;
}

unsigned int parse_vertices(char *buffer, unsigned int index, obj3d *obj) {
  char str[255] = {0};
  unsigned int count = 0;
  buffer += 2; /* skip first f_ */
  while (*buffer) {
    unsigned int length = 0;
    sscanf(buffer, "%s", str);
    length = strlen(str) + 1;
    buffer += length;
    if (length > 1) { /*skip spaces*/
      sscanf(str, "%u", &obj->polygons[index].vertexes[count]);
      ++count;
    }
    strcpy(str, "");
  }
  return count;
}

void parseMaxMin(obj3d *res, double x, double y, double z, int first_line) {
  if (first_line) {
    compareNums(&res->bounds.x_min, &res->bounds.x_max, x);
    compareNums(&res->bounds.y_min, &res->bounds.y_max, y);
    compareNums(&res->bounds.z_min, &res->bounds.z_max, z);
  } else {
    res->bounds.x_max = x;
    res->bounds.x_min = x;
    res->bounds.y_max = y;
    res->bounds.y_min = y;
    res->bounds.z_max = z;
    res->bounds.z_min = z;
  }
}

void compareNums(double *have_min, double *have_max, double comparable) {
  if (*have_max < comparable) {
    *have_max = comparable;
  }
  if (*have_min > comparable) {
    *have_min = comparable;
  }
}

void centerObj(obj3d *res) {
  res->centers.x_center =
      centersFormula(&res->bounds.x_min, &res->bounds.x_max);
  res->centers.y_center =
      centersFormula(&res->bounds.y_min, &res->bounds.y_max);
  res->centers.z_center =
      centersFormula(&res->bounds.z_min, &res->bounds.z_max);
  for (unsigned int i = 0; i < res->vtx_count * 3; i += 3) {
    res->vet_arr[i] -= res->centers.x_center;
    res->vet_arr[i + 1] -= res->centers.y_center;
    res->vet_arr[i + 2] -= res->centers.z_center;
  }
}

double centersFormula(double *minVal, double *maxVal) {
  double center = *minVal + (*maxVal - *minVal) / 2;
  *minVal -= center;
  *maxVal -= center;
  return center;
}
