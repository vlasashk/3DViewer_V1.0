#include <stdio.h>

#include "../3D_Viewer/back/s21_3dviewer.h"
#include "./s21_3dviewer_tests.h"

/*----------------------------------file manipulate-------------------*/
START_TEST(file_open_fail) {
  char *file_name = "sadflasdf";              // Arrange
  FILE *f = NULL;                             // Arrange
  int status = open_obj_file(file_name, &f);  // Act
  ck_assert_int_eq(FAIL, status);             // Accert
  ck_assert_ptr_eq(f, NULL);                  // Accert
}
END_TEST

START_TEST(file_open_ok) {
  char *file_name = "data-samples/cube.obj";  // Arrange
  FILE *f = NULL;                             // Arrange
  int status = open_obj_file(file_name, &f);  // Act
  ck_assert_int_eq(SUCCESS, status);          // Accert
  ck_assert_ptr_ne(f, NULL);                  // Accert
  fclose(f);
}
END_TEST

START_TEST(count_vtx_fct) {
  char *file_name = "data-samples/cube.obj";  // Arrange
  FILE *f = NULL;                             // Arrange
  obj3d *res = calloc(1, sizeof(obj3d));      // Arrange
  int status = open_obj_file(file_name, &f);  // Act
  if (!status) status = read_obj(f, res);     // Act
  ck_assert_int_eq(SUCCESS, status);          // Accert
  ck_assert_int_eq(res->vtx_count, 8);        // Accert
  ck_assert_int_eq(res->fct_count, 12);       // Accert
  ck_assert_ptr_ne(f, NULL);                  // Accert
  fclose(f);
  free_obj3d(&res);
  // ck_assert_ptr_eq(f, NULL);  // Accert
}
END_TEST

START_TEST(read_vertexes) {
  char *file_name = "data-samples/cube.obj";           // Arrange
  FILE *f = NULL;                                      // Arrange
  obj3d *res = calloc(1, sizeof(obj3d));               // Arrange
  int status = open_obj_file(file_name, &f);           // Act
  if (!status) status = read_obj(f, res);              // Act
  ck_assert_int_eq(SUCCESS, status);                   // Accert
  ck_assert_int_eq((int)(res->vet_arr[0] * 10), 5);    // Accert
  ck_assert_int_eq((int)(res->vet_arr[1] * 10), -5);   // Accert
  ck_assert_int_eq((int)(res->vet_arr[2] * 10), -5);   // Accert
  ck_assert_int_eq((int)(res->vet_arr[3] * 10), 5);    // Accert
  ck_assert_int_eq((int)(res->vet_arr[4] * 10), -5);   // Accert
  ck_assert_int_eq((int)(res->vet_arr[5] * 10), 5);    // Accert
  ck_assert_int_eq((int)(res->vet_arr[6] * 10), -5);   // Accert
  ck_assert_int_eq((int)(res->vet_arr[7] * 10), -5);   // Accert
  ck_assert_int_eq((int)(res->vet_arr[8] * 10), 5);    // Accert
  ck_assert_int_eq((int)(res->vet_arr[9] * 10), -5);   // Accert
  ck_assert_int_eq((int)(res->vet_arr[10] * 10), -5);  // Accert
  ck_assert_int_eq((int)(res->vet_arr[11] * 10), -5);  // Accert
  ck_assert_int_eq((int)(res->vet_arr[12] * 10), 5);   // Accert
  ck_assert_int_eq((int)(res->vet_arr[13] * 10), 5);   // Accert
  ck_assert_int_eq((int)(res->vet_arr[14] * 10), -5);  // Accert
  ck_assert_int_eq((int)(res->vet_arr[15] * 10), 5);   // Accert
  ck_assert_int_eq((int)(res->vet_arr[16] * 10), 5);   // Accert
  ck_assert_int_eq((int)(res->vet_arr[17] * 10), 5);   // Accert
  ck_assert_int_eq((int)(res->vet_arr[18] * 10), -5);  // Accert
  ck_assert_int_eq((int)(res->vet_arr[19] * 10), 5);   // Accert
  ck_assert_int_eq((int)(res->vet_arr[20] * 10), 5);   // Accert
  ck_assert_int_eq((int)(res->vet_arr[21] * 10), -5);  // Accert
  ck_assert_int_eq((int)(res->vet_arr[22] * 10), 5);   // Accert
  ck_assert_int_eq((int)(res->vet_arr[23] * 10), -5);  // Accert
  ck_assert_int_eq(res->fct_vtx[3], 3);                // Accert
  ck_assert_int_eq(res->polygons[3].vertexes[0], 6);   // Accert
  ck_assert_int_eq(res->polygons[3].vertexes[1], 7);   // Accert
  ck_assert_int_eq(res->polygons[3].vertexes[2], 3);   // Accert
  fclose(f);
  free_obj3d(&res);
}
END_TEST

/*----------------------------------memory manipulate-------------------*/
START_TEST(alloc_mem_ok) {
  obj3d *obj = calloc(1, sizeof(obj3d));
  obj->vtx_count = 10;
  obj->fct_count = 20;                   // Arrange
  int status = s21_alloc_mem(obj);       // Act
  ck_assert_int_eq(SUCCESS, status);     // Accert
  ck_assert_ptr_ne((void *)&obj, NULL);  // Accert
  free_obj3d(&obj);
}
END_TEST

START_TEST(free_mem) {
  obj3d *obj = NULL;                     // Arrange
  obj = (obj3d *)malloc(sizeof(obj3d));  // Arrange
  obj->vtx_count = 100;
  obj->fct_count = 200;               // Arrange
  int status = s21_alloc_mem(obj);    // Act
  free_obj3d(&obj);                   // Act
  ck_assert_int_eq(SUCCESS, status);  // Accert
}
END_TEST

/*-----------------------------parse functions------------------*/
START_TEST(fill_obj3d_verteces) {
  // char *buffer = "v -426.750397 4550.81408 2637.903854 ";  // Arrange
  char *file_name = "data-samples/deer.obj";                       // Arrange
  FILE *f = NULL;                                                  // Arrange
  obj3d *obj = NULL;                                               // Arrange
  obj = (obj3d *)malloc(sizeof(obj3d));                            // Arrange
  *obj = (obj3d){.vtx_count = 772, .fct_count = 1508};             // Arrange
  int status = open_obj_file(file_name, &f);                       // Act
  if (!status) status = s21_alloc_mem(obj);                        // Act
  if (!status) status = fill_obj3d(f, obj);                        // Act
  ck_assert_int_eq(SUCCESS, status);                               // Accert
  ck_assert_int_eq((int)(obj->vet_arr[0] * 1000000), -295424526);  // Accert
  ck_assert_int_eq((int)(obj->vet_arr[1] * 1000000), 482015262);   // Accert
  ck_assert_int_eq((int)(obj->vet_arr[2] * 1000000), 10099);       // Accert
  free_obj3d(&obj);                                                // Act
}
END_TEST

START_TEST(fill_facet_ok) {
  char *bf = "f 5/4/ 562/7/10 123/25/25 5 58//86 12/ 74// ";  // Arrange
  obj3d *obj = NULL;                                          // Arrange
  obj = (obj3d *)malloc(sizeof(obj3d));                       // Arrange
  *obj = (obj3d){.vtx_count = 1, .fct_count = 1};             // Arrange
  int status = s21_alloc_mem(obj);                            // Act
  if (!status) status = fill_facets(bf, obj, 0);              // Act
  ck_assert_int_eq(SUCCESS, status);                          // Accert
  ck_assert_int_eq(7, obj->fct_vtx[0]);                       // Accert
  ck_assert_int_eq(obj->polygons[0].vertexes[0], 5);          // Accert
  ck_assert_int_eq(obj->polygons[0].vertexes[1], 562);        // Accert
  ck_assert_int_eq(obj->polygons[0].vertexes[2], 123);        // Accert
  ck_assert_int_eq(obj->polygons[0].vertexes[3], 5);          // Accert
  ck_assert_int_eq(obj->polygons[0].vertexes[4], 58);         // Accert
  ck_assert_int_eq(obj->polygons[0].vertexes[5], 12);         // Accert
  ck_assert_int_eq(obj->polygons[0].vertexes[6], 74);         // Accert
  free_obj3d(&obj);                                           // Act
}
END_TEST

START_TEST(count_vtx_of_facet_ok) {
  char *bf = "f 5/4 562/7/10 123/25/25 5 58//86 12/ 74// ";  // Arrange
  obj3d *obj = NULL;                                         // Arrange
  obj = (obj3d *)malloc(sizeof(obj3d));                      // Arrange
  *obj = (obj3d){.vtx_count = 2, .fct_count = 1};            // Arrange
  int status = s21_alloc_mem(obj);                           // Act
  if (!status) status = count_vtx_of_facet(bf);              // Act
  ck_assert_int_eq(7, status);                               // Accert
  free_obj3d(&obj);                                          // Act
}
END_TEST

START_TEST(parse_vertices_ok) {
  char *bf = "f 551/25 562/70 547/84 123/25/25 5 58//86 12/ 74// ";  // Arrange
  obj3d *obj = NULL;                                                 // Arrange
  obj = (obj3d *)malloc(sizeof(obj3d));                              // Arrange
  *obj = (obj3d){.vtx_count = 2, .fct_count = 8};                    // Arrange
  int status = s21_alloc_mem(obj);                                   // Act
  obj->polygons[0].vertexes =
      (unsigned int *)calloc(8, sizeof(unsigned int));  // Act
  if (!status) status = parse_vertices(bf, 0, obj);     // Act
  ck_assert_int_eq(8, status);                          // Accert
  ck_assert_int_eq(obj->polygons[0].vertexes[0], 551);  // Accert
  ck_assert_int_eq(obj->polygons[0].vertexes[1], 562);  // Accert
  ck_assert_int_eq(obj->polygons[0].vertexes[2], 547);  // Accert
  ck_assert_int_eq(obj->polygons[0].vertexes[3], 123);  // Accert
  ck_assert_int_eq(obj->polygons[0].vertexes[4], 5);    // Accert
  ck_assert_int_eq(obj->polygons[0].vertexes[5], 58);   // Accert
  ck_assert_int_eq(obj->polygons[0].vertexes[6], 12);   // Accert
  ck_assert_int_eq(obj->polygons[0].vertexes[7], 74);   // Accert
  free_obj3d(&obj);                                     // Act
}
END_TEST

START_TEST(move) {
  char *file_name = "data-samples/cube.obj";  // Arrange
  FILE *f = NULL;                             // Arrange
  obj3d *res = calloc(1, sizeof(obj3d));      // Arrange
  int status = open_obj_file(file_name, &f);  // Act
  if (!status) status = read_obj(f, res);     // Act

  double x = 1.32;
  double y = 1.4563;
  double z = 1.134;
  moveX(x, res);
  moveY(y, res);
  moveZ(z, res);
  ck_assert_int_eq(SUCCESS, status);                  // Accert
  ck_assert_double_eq((res->vet_arr[0]), 0.5 + x);    // Accert
  ck_assert_double_eq((res->vet_arr[1]), -0.5 + y);   // Accert
  ck_assert_double_eq((res->vet_arr[2]), -0.5 + z);   // Accert
  ck_assert_double_eq((res->vet_arr[3]), 0.5 + x);    // Accert
  ck_assert_double_eq((res->vet_arr[4]), -0.5 + y);   // Accert
  ck_assert_double_eq((res->vet_arr[5]), 0.5 + z);    // Accert
  ck_assert_double_eq((res->vet_arr[6]), -0.5 + x);   // Accert
  ck_assert_double_eq((res->vet_arr[7]), -0.5 + y);   // Accert
  ck_assert_double_eq((res->vet_arr[8]), 0.5 + z);    // Accert
  ck_assert_double_eq((res->vet_arr[9]), -0.5 + x);   // Accert
  ck_assert_double_eq((res->vet_arr[10]), -0.5 + y);  // Accert
  ck_assert_double_eq((res->vet_arr[11]), -0.5 + z);  // Accert
  ck_assert_double_eq((res->vet_arr[12]), 0.5 + x);   // Accert
  ck_assert_double_eq((res->vet_arr[13]), 0.5 + y);   // Accert
  ck_assert_double_eq((res->vet_arr[14]), -0.5 + z);  // Accert
  ck_assert_double_eq((res->vet_arr[15]), 0.5 + x);   // Accert
  ck_assert_double_eq((res->vet_arr[16]), 0.5 + y);   // Accert
  ck_assert_double_eq((res->vet_arr[17]), 0.5 + z);   // Accert
  ck_assert_double_eq((res->vet_arr[18]), -0.5 + x);  // Accert
  ck_assert_double_eq((res->vet_arr[19]), 0.5 + y);   // Accert
  ck_assert_double_eq((res->vet_arr[20]), 0.5 + z);   // Accert
  ck_assert_double_eq((res->vet_arr[21]), -0.5 + x);  // Accert
  ck_assert_double_eq((res->vet_arr[22]), 0.5 + y);   // Accert
  ck_assert_double_eq((res->vet_arr[23]), -0.5 + z);  // Accert
  ck_assert_int_eq(res->fct_vtx[3], 3);               // Accert
  ck_assert_int_eq(res->polygons[3].vertexes[0], 6);  // Accert
  ck_assert_int_eq(res->polygons[3].vertexes[1], 7);  // Accert
  ck_assert_int_eq(res->polygons[3].vertexes[2], 3);  // Accert
  fclose(f);
  free_obj3d(&res);
}
END_TEST

START_TEST(rescale) {
  char *file_name = "data-samples/cube.obj";  // Arrange
  FILE *f = NULL;                             // Arrange
  obj3d *res = calloc(1, sizeof(obj3d));      // Arrange
  int status = open_obj_file(file_name, &f);  // Act
  if (!status) status = read_obj(f, res);     // Act
  double scale = 0.6;
  initialRescaleObj(scale, res);
  ck_assert_int_eq(SUCCESS, status);                                   // Accert
  ck_assert_double_eq((res->vet_arr[0]), 0.5 * (scale - scale * -1));  // Accert
  ck_assert_double_eq((res->vet_arr[1]),
                      -0.5 * (scale - scale * -1));  // Accert
  ck_assert_double_eq((res->vet_arr[2]),
                      -0.5 * (scale - scale * -1));                    // Accert
  ck_assert_double_eq((res->vet_arr[3]), 0.5 * (scale - scale * -1));  // Accert
  ck_assert_double_eq((res->vet_arr[4]),
                      -0.5 * (scale - scale * -1));                    // Accert
  ck_assert_double_eq((res->vet_arr[5]), 0.5 * (scale - scale * -1));  // Accert
  ck_assert_double_eq((res->vet_arr[6]),
                      -0.5 * (scale - scale * -1));  // Accert
  ck_assert_double_eq((res->vet_arr[7]),
                      -0.5 * (scale - scale * -1));                    // Accert
  ck_assert_double_eq((res->vet_arr[8]), 0.5 * (scale - scale * -1));  // Accert
  ck_assert_double_eq((res->vet_arr[9]),
                      -0.5 * (scale - scale * -1));  // Accert
  ck_assert_double_eq((res->vet_arr[10]),
                      -0.5 * (scale - scale * -1));  // Accert
  ck_assert_double_eq((res->vet_arr[11]),
                      -0.5 * (scale - scale * -1));  // Accert
  ck_assert_double_eq((res->vet_arr[12]),
                      0.5 * (scale - scale * -1));  // Accert
  ck_assert_double_eq((res->vet_arr[13]),
                      0.5 * (scale - scale * -1));  // Accert
  ck_assert_double_eq((res->vet_arr[14]),
                      -0.5 * (scale - scale * -1));  // Accert
  ck_assert_double_eq((res->vet_arr[15]),
                      0.5 * (scale - scale * -1));  // Accert
  ck_assert_double_eq((res->vet_arr[16]),
                      0.5 * (scale - scale * -1));  // Accert
  ck_assert_double_eq((res->vet_arr[17]),
                      0.5 * (scale - scale * -1));  // Accert
  ck_assert_double_eq((res->vet_arr[18]),
                      -0.5 * (scale - scale * -1));  // Accert
  ck_assert_double_eq((res->vet_arr[19]),
                      0.5 * (scale - scale * -1));  // Accert
  ck_assert_double_eq((res->vet_arr[20]),
                      0.5 * (scale - scale * -1));  // Accert
  ck_assert_double_eq((res->vet_arr[21]),
                      -0.5 * (scale - scale * -1));  // Accert
  ck_assert_double_eq((res->vet_arr[22]),
                      0.5 * (scale - scale * -1));  // Accert
  ck_assert_double_eq((res->vet_arr[23]),
                      -0.5 * (scale - scale * -1));   // Accert
  ck_assert_int_eq(res->fct_vtx[3], 3);               // Accert
  ck_assert_int_eq(res->polygons[3].vertexes[0], 6);  // Accert
  ck_assert_int_eq(res->polygons[3].vertexes[1], 7);  // Accert
  ck_assert_int_eq(res->polygons[3].vertexes[2], 3);  // Accert
  fclose(f);
  free_obj3d(&res);
}
END_TEST

START_TEST(rotateX_test) {
  char *file_name = "data-samples/cube.obj";  // Arrange
  FILE *f = NULL;                             // Arrange
  obj3d *res = calloc(1, sizeof(obj3d));      // Arrange
  int status = open_obj_file(file_name, &f);  // Act
  if (!status) status = read_obj(f, res);     // Act

  double x = 90;
  double sin_x = sin(x);
  double cos_x = cos(x);
  rotateX(x, res);

  ck_assert_int_eq(SUCCESS, status);            // Accert
  ck_assert_double_eq((res->vet_arr[0]), 0.5);  // Accert
  ck_assert_double_eq((res->vet_arr[1]),
                      cos_x * -0.5 - sin_x * -0.5);                    // Accert
  ck_assert_double_eq((res->vet_arr[3]), 0.5);                         // Accert
  ck_assert_double_eq((res->vet_arr[4]), cos_x * -0.5 - sin_x * 0.5);  // Accert

  ck_assert_double_eq((res->vet_arr[6]), -0.5);                        // Accert
  ck_assert_double_eq((res->vet_arr[7]), cos_x * -0.5 - sin_x * 0.5);  // Accert
  ck_assert_double_eq((res->vet_arr[9]), -0.5);                        // Accert
  ck_assert_double_eq((res->vet_arr[10]),
                      cos_x * -0.5 - sin_x * -0.5);  // Accert
  ck_assert_double_eq((res->vet_arr[12]), 0.5);      // Accert
  ck_assert_double_eq((res->vet_arr[13]),
                      cos_x * 0.5 - sin_x * -0.5);                     // Accert
  ck_assert_double_eq((res->vet_arr[15]), 0.5);                        // Accert
  ck_assert_double_eq((res->vet_arr[16]), cos_x * 0.5 - sin_x * 0.5);  // Accert
  ck_assert_double_eq((res->vet_arr[18]), -0.5);                       // Accert
  ck_assert_double_eq((res->vet_arr[19]), cos_x * 0.5 - sin_x * 0.5);  // Accert
  ck_assert_double_eq((res->vet_arr[21]), -0.5);                       // Accert
  ck_assert_double_eq((res->vet_arr[22]),
                      cos_x * 0.5 - sin_x * -0.5);    // Accert
  ck_assert_int_eq(res->fct_vtx[3], 3);               // Accert
  ck_assert_int_eq(res->polygons[3].vertexes[0], 6);  // Accert
  ck_assert_int_eq(res->polygons[3].vertexes[1], 7);  // Accert
  ck_assert_int_eq(res->polygons[3].vertexes[2], 3);  // Accert
  fclose(f);
  free_obj3d(&res);
}
END_TEST

START_TEST(rotateZ_test) {
  char *file_name = "data-samples/cube.obj";  // Arrange
  FILE *f = NULL;                             // Arrange
  obj3d *res = calloc(1, sizeof(obj3d));      // Arrange
  int status = open_obj_file(file_name, &f);  // Act
  if (!status) status = read_obj(f, res);     // Act

  double x = 90;
  double sin_x = sin(x);
  double cos_x = cos(x);
  rotateZ(x, res);
  ck_assert_int_eq(SUCCESS, status);             // Accert
  ck_assert_double_eq((res->vet_arr[2]), -0.5);  // Accert
  ck_assert_double_eq((res->vet_arr[1]),
                      cos_x * -0.5 + sin_x * 0.5);                     // Accert
  ck_assert_double_eq((res->vet_arr[5]), 0.5);                         // Accert
  ck_assert_double_eq((res->vet_arr[4]), cos_x * -0.5 + sin_x * 0.5);  // Accert

  ck_assert_double_eq((res->vet_arr[8]), 0.5);  // Accert
  ck_assert_double_eq((res->vet_arr[7]),
                      cos_x * -0.5 + sin_x * -0.5);  // Accert
  ck_assert_double_eq((res->vet_arr[11]), -0.5);     // Accert
  ck_assert_double_eq((res->vet_arr[10]),
                      cos_x * -0.5 + sin_x * -0.5);  // Accert
  ck_assert_double_eq((res->vet_arr[14]), -0.5);     // Accert
  ck_assert_double_eq((res->vet_arr[13]),
                      cos_x * 0.5 + sin_x * 0.5);                      // Accert
  ck_assert_double_eq((res->vet_arr[17]), 0.5);                        // Accert
  ck_assert_double_eq((res->vet_arr[16]), cos_x * 0.5 + sin_x * 0.5);  // Accert
  ck_assert_double_eq((res->vet_arr[20]), 0.5);                        // Accert
  ck_assert_double_eq((res->vet_arr[19]),
                      cos_x * 0.5 + sin_x * -0.5);  // Accert
  ck_assert_double_eq((res->vet_arr[23]), -0.5);    // Accert
  ck_assert_double_eq((res->vet_arr[22]),
                      cos_x * 0.5 + sin_x * -0.5);    // Accert
  ck_assert_int_eq(res->fct_vtx[3], 3);               // Accert
  ck_assert_int_eq(res->polygons[3].vertexes[0], 6);  // Accert
  ck_assert_int_eq(res->polygons[3].vertexes[1], 7);  // Accert
  ck_assert_int_eq(res->polygons[3].vertexes[2], 3);  // Accert
  fclose(f);
  free_obj3d(&res);
}
END_TEST

START_TEST(rotateY_test) {
  char *file_name = "data-samples/cube.obj";  // Arrange
  FILE *f = NULL;                             // Arrange
  obj3d *res = calloc(1, sizeof(obj3d));      // Arrange
  int status = open_obj_file(file_name, &f);  // Act
  if (!status) status = read_obj(f, res);     // Act

  double y = 90;
  double sin_y = sin(y);
  double cos_y = cos(y);
  rotateY(y, res);
  ck_assert_int_eq(SUCCESS, status);                                   // Accert
  ck_assert_double_eq((res->vet_arr[0]), cos_y * 0.5 + sin_y * -0.5);  // Accert
  ck_assert_double_eq((res->vet_arr[3]), cos_y * 0.5 + sin_y * 0.5);   // Accert
  ck_assert_double_eq((res->vet_arr[6]), cos_y * -0.5 + sin_y * 0.5);  // Accert
  ck_assert_double_eq((res->vet_arr[9]),
                      cos_y * -0.5 + sin_y * -0.5);  // Accert
  ck_assert_double_eq((res->vet_arr[12]),
                      cos_y * 0.5 + sin_y * -0.5);                     // Accert
  ck_assert_double_eq((res->vet_arr[15]), cos_y * 0.5 + sin_y * 0.5);  // Accert
  ck_assert_double_eq((res->vet_arr[18]),
                      cos_y * -0.5 + sin_y * 0.5);  // Accert
  ck_assert_double_eq((res->vet_arr[21]),
                      cos_y * -0.5 + sin_y * -0.5);   // Accert
  ck_assert_int_eq(res->fct_vtx[3], 3);               // Accert
  ck_assert_int_eq(res->polygons[3].vertexes[0], 6);  // Accert
  ck_assert_int_eq(res->polygons[3].vertexes[1], 7);  // Accert
  ck_assert_int_eq(res->polygons[3].vertexes[2], 3);  // Accert
  fclose(f);
  free_obj3d(&res);
}
END_TEST

Suite *s21_common_suite() {
  Suite *s_3dObj;
  TCase *tc_file_operations, *tc_memory, *tc_parse, *tc_affine;

  s_3dObj = suite_create("file manipulation suite");

  tc_file_operations = tcase_create("opening file");
  tcase_add_test(tc_file_operations, file_open_fail);
  tcase_add_test(tc_file_operations, file_open_ok);
  tcase_add_test(tc_file_operations, count_vtx_fct);
  tcase_add_test(tc_file_operations, read_vertexes);
  suite_add_tcase(s_3dObj, tc_file_operations);

  tc_memory = tcase_create("memory manipul");
  tcase_add_test(tc_memory, alloc_mem_ok);
  tcase_add_test(tc_memory, free_mem);
  suite_add_tcase(s_3dObj, tc_memory);

  tc_parse = tcase_create("parse func");
  tcase_add_test(tc_parse, fill_obj3d_verteces);
  tcase_add_test(tc_parse, fill_facet_ok);
  tcase_add_test(tc_parse, count_vtx_of_facet_ok);
  tcase_add_test(tc_parse, parse_vertices_ok);
  suite_add_tcase(s_3dObj, tc_parse);

  tc_affine = tcase_create("affine func");
  tcase_add_test(tc_affine, move);
  tcase_add_test(tc_affine, rescale);
  tcase_add_test(tc_affine, rotateX_test);
  tcase_add_test(tc_affine, rotateZ_test);
  tcase_add_test(tc_affine, rotateY_test);

  suite_add_tcase(s_3dObj, tc_affine);

  return s_3dObj;
}
