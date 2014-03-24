/***********************************************************
     Starter code for Assignment 3

     This code was originally written by Jack Wang for
		    CSC418, SPRING 2005

		implements light_source.h

***********************************************************/

#include <cmath>
#include "light_source.h"

void PointLight::shade( Ray3D& ray ) {
	// TODO: implement this function to fill in values for ray.col 
	// using phong shading.  Make sure your vectors are normalized, and
	// clamp colour values to 1.0.
	//
	// It is assumed at this point that the intersection information in ray 
	// is available.  So be sure that traverseScene() is called on the ray 
	// before this function.
    
    // Normalized vectors needed for phong shading
    Vector3D N = ray.intersection.normal;
    N.normalize();
    Vector3D L = _pos-ray.intersection.point;
    L.normalize();
    Vector3D V = -ray.dir;
    V.normalize();
    Vector3D R = 2.*(L.dot(N)*N)-L;
    R.normalize();

    //intensity due to ambient light
    Colour Ia = (*ray.intersection.mat).ambient*_col_ambient;

    //intensity due to diffuse light
    Colour Id = (*ray.intersection.mat).diffuse*(std::max(0.0,N.dot(L))*_col_diffuse);

    //intensity due to specular light
    Colour Is = (*ray.intersection.mat).specular*(std::max(0.0,pow(V.dot(R),(*ray.intersection.mat).specular_exp))*_col_specular);

    //Phone shading
    //ray.col = Ia + Id + Is;
    //Only diffuse and ambient
    //ray.col = Ia + Id;
    //Scene signature
    ray.col = (*ray.intersection.mat).diffuse;
    ray.col.clamp();
}

