/*
 * Configuration.h
 *
 *  Created on: Mar 8, 2017
 *      Author: ysun3
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include "Renderer.h"
#include "Camera.h"
#include "Image.h"
#include "Light.h"
#include "LightSet.h"
#include "AABB.h"
#include "Stamp.h"

# include <unistd.h>
# include <stdio.h>

#include <iostream>

using namespace std;
using namespace lux;
using namespace openvdb;

//Set resolution
int height = 1080; //1080;
int width = 1920; //1920

//Configuration for wedges usage
////Set delta_s of renderer
//float delta_s = 0.01;      //0.003
//
////K of volume
//float K=13;
//
////Initialize camera
//Vector c0(20,18,30);
//Vector c(-20,-18,-25);
//Vector up0(0,1,0);
//float near = 25.0;
//float far = 55.0;

//Configuration for cumulo usage
//Set delta_s of renderer
float delta_s = 0.01;      //0.003

//K of volume
float K=10;

//Initialize camera
Vector c0(0,0,3);
Vector c(0,0,-3);
Vector up0(0,1,0);
float near = 0.0;
float far = 6.0;

#endif /* CONFIGURATION_H_ */
