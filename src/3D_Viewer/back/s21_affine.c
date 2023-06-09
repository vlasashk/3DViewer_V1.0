/**
 * @file s21_affine.c
 * @brief Implementation of affine transformations
 */
#include "./s21_3dviewer.h"

double findMaxAxisDistance(obj3d* res) {
  double result = 0.0;
  double xDistance = res->bounds.x_max - res->bounds.x_min;
  double yDistance = res->bounds.y_max - res->bounds.y_min;
  double zDistance = res->bounds.z_max - res->bounds.z_min;
  if (xDistance > yDistance) {
    if (xDistance > zDistance) {
      result = xDistance;
    } else {
      result = zDistance;
    }
  } else {
    if (yDistance > zDistance) {
      result = yDistance;
    } else {
      result = zDistance;
    }
  }
  return result;
}

void rescaleObj(double scaleApply, obj3d* res) {
  res->bounds.x_max *= scaleApply;
  res->bounds.x_min *= scaleApply;
  res->bounds.y_max *= scaleApply;
  res->bounds.y_min *= scaleApply;
  res->bounds.z_max *= scaleApply;
  res->bounds.z_min *= scaleApply;
  for (unsigned int i = 0; i < res->vtx_count * 3; i += 3) {
    res->vet_arr[i] *= scaleApply;
    res->vet_arr[i + 1] *= scaleApply;
    res->vet_arr[i + 2] *= scaleApply;
  }
}

void initialRescaleObj(double scaleVal, obj3d* res) {
  double scaleApply = (scaleVal - (scaleVal * (-1))) / findMaxAxisDistance(res);
  rescaleObj(scaleApply, res);
}

void moveX(double xVal, obj3d* res) {
  res->bounds.x_max += xVal;
  res->bounds.x_min += xVal;
  for (unsigned int i = 0; i < res->vtx_count * 3; i += 3) {
    res->vet_arr[i] += xVal;
  }
}

void moveY(double yVal, obj3d* res) {
  res->bounds.y_max += yVal;
  res->bounds.y_min += yVal;
  for (unsigned int i = 0; i < res->vtx_count * 3; i += 3) {
    res->vet_arr[i + 1] += yVal;
  }
}

void moveZ(double zVal, obj3d* res) {
  res->bounds.z_max += zVal;
  res->bounds.z_min += zVal;
  for (unsigned int i = 0; i < res->vtx_count * 3; i += 3) {
    res->vet_arr[i + 2] += zVal;
  }
}

void rotateX(double rotate, obj3d* res) {
  double sin_x = sin(rotate);
  double cos_x = cos(rotate);
  double temp_y_max = res->bounds.y_max;
  double temp_y_min = res->bounds.y_min;
  double temp_z_max = res->bounds.z_max;
  double temp_z_min = res->bounds.z_min;
  res->bounds.y_max = cos_x * temp_y_max - sin_x * temp_z_max;
  res->bounds.y_min = cos_x * temp_y_min - sin_x * temp_z_min;
  res->bounds.z_max = sin_x * temp_y_max + cos_x * temp_z_max;
  res->bounds.z_min = sin_x * temp_y_min + cos_x * temp_z_min;
  for (unsigned int i = 0; i < res->vtx_count * 3; i += 3) {
    double temp_y = res->vet_arr[i + 1];
    double temp_z = res->vet_arr[i + 2];
    res->vet_arr[i + 1] = cos_x * temp_y - sin_x * temp_z;
    res->vet_arr[i + 2] = sin_x * temp_y + cos_x * temp_z;
  }
}

void rotateY(double rotate, obj3d* res) {
  double sin_y = sin(rotate);
  double cos_y = cos(rotate);
  double temp_x_max = res->bounds.x_max;
  double temp_x_min = res->bounds.x_min;
  double temp_z_max = res->bounds.z_max;
  double temp_z_min = res->bounds.z_min;
  res->bounds.x_max = cos_y * temp_x_max + sin_y * temp_z_max;
  res->bounds.x_min = cos_y * temp_x_min + sin_y * temp_z_min;
  res->bounds.z_max = sin_y * (-temp_x_max) + cos_y * temp_z_max;
  res->bounds.z_min = sin_y * (-temp_x_min) + cos_y * temp_z_min;
  for (unsigned int i = 0; i < res->vtx_count * 3; i += 3) {
    double temp_x = res->vet_arr[i + 0];
    double temp_z = res->vet_arr[i + 2];
    res->vet_arr[i + 0] = cos_y * temp_x + sin_y * temp_z;
    res->vet_arr[i + 2] = sin_y * (-temp_x) + cos_y * temp_z;
  }
}

void rotateZ(double rotate, obj3d* res) {
  double sin_z = sin(rotate);
  double cos_z = cos(rotate);
  double temp_x_max = res->bounds.x_max;
  double temp_x_min = res->bounds.x_min;
  double temp_y_max = res->bounds.y_max;
  double temp_y_min = res->bounds.y_min;
  res->bounds.x_max = cos_z * temp_x_max - sin_z * temp_y_max;
  res->bounds.x_min = cos_z * temp_x_min - sin_z * temp_y_min;
  res->bounds.y_max = sin_z * temp_x_max + cos_z * temp_y_max;
  res->bounds.y_min = sin_z * temp_x_min + cos_z * temp_y_min;
  for (unsigned int i = 0; i < res->vtx_count * 3; i += 3) {
    double temp_x = res->vet_arr[i + 0];
    double temp_y = res->vet_arr[i + 1];
    res->vet_arr[i + 0] = cos_z * temp_x - sin_z * temp_y;
    res->vet_arr[i + 1] = sin_z * temp_x + cos_z * temp_y;
  }
}