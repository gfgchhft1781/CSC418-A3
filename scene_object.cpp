/***********************************************************
     Starter code for Assignment 3

     This code was originally written by Jack Wang for
		    CSC418, SPRING 2005

		implements scene_object.h

***********************************************************/

#include <cmath>
#include <iostream>
#include "scene_object.h"

bool UnitSquare::intersect( Ray3D& ray, const Matrix4x4& worldToModel,
		const Matrix4x4& modelToWorld ) {
	// TODO: implement intersection code for UnitSquare, which is
	// defined on the xy-plane, with vertices (0.5, 0.5, 0), 
	// (-0.5, 0.5, 0), (-0.5, -0.5, 0), (0.5, -0.5, 0), and normal
	// (0, 0, 1).
	//
	// Your goal here is to fill ray.intersection with correct values
	// should an intersection occur.  This includes intersection.point, 
	// intersection.normal, intersection.none, intersection.t_value.   
	//
	// HINT: Remember to first transform the ray into object space  
	// to simplify the intersection test.

    Ray3D ro;
    ro.origin = worldToModel*ray.origin;
    ro.dir = worldToModel*ray.dir;
    float t = -(ro.origin[2]/ro.dir[2]);
    if (t <= 0) {
        return false;
    }
    
    //calculate x and y
    float x_check = ro.origin[0] + t*ro.dir[0];
    float y_check = ro.origin[1] + t*ro.dir[1];
    Point3D io(x_check, y_check, 0.0);
    Vector3D norm(0.0,0.0,1.0);
    
    //x and y should fall on unit square
    if ( (x_check <= 0.5 && x_check >= -0.5) && (y_check <= 0.5 && y_check >= -0.5) ) {
        //an intersection has occured. Check if should update
        if (ray.intersection.none || t < ray.intersection.t_value) {
            //should update
            ray.intersection.t_value = t;
            ray.intersection.point = modelToWorld*io;
            ray.intersection.normal = worldToModel.transpose()*norm;
            ray.intersection.normal.normalize();
            ray.intersection.none = false;
            return true;
        }
    }
	return false;
}

bool UnitSphere::intersect( Ray3D& ray, const Matrix4x4& worldToModel,
		const Matrix4x4& modelToWorld ) {
	// TODO: implement intersection code for UnitSphere, which is centred 
	// on the origin.  
	//
	// Your goal here is to fill ray.intersection with correct values
	// should an intersection occur.  This includes intersection.point, 
	// intersection.normal, intersection.none, intersection.t_value.   
	//
	// HINT: Remember to first transform the ray into object space  
	// to simplify the intersection test.

    Ray3D ro;
    ro.origin = worldToModel*ray.origin;
    ro.dir = worldToModel*ray.dir;

    Point3D c(0,0,0);
    float t, t0, t1;
    float r = 1;

    //Use quadratic formula to find intersection
    float A = ro.dir.dot(ro.dir);
    float B = 2*(ro.dir.dot(ro.origin-c));
    float C = (ro.origin-c).dot(ro.origin-c) - 1;

    //Find discriminant
    float d = B*B-4*A*C;

    //If the discriminant is negative there is no intersection
    if ( d < 0 )
        return false;
    
    // calculate solutions
    t0 = (-B + sqrt(d))/(2.0 * A);
    t1 = (-B - sqrt(d))/(2.0 * A);
    
    if ( t0 < 0 && t1 < 0 )
        return false;
    else if ( t0 < 0 )
        t = t1;
    else if ( t1 < 0)
        t = t0;
    else
        t = fmin(t1,t0);

    //calculate intersection point
    float x_check = ro.origin[0] + t*ro.dir[0];
    float y_check = ro.origin[1] + t*ro.dir[1];
    float z_check = ro.origin[2] + t*ro.dir[2];
    Point3D io(x_check, y_check, z_check);
    Vector3D norm(x_check,y_check,z_check);
    norm.normalize();

    //update ray values
    if (ray.intersection.none || t < ray.intersection.t_value) {
        ray.intersection.t_value = t;
        ray.intersection.point = modelToWorld*io;
        ray.intersection.normal = worldToModel.transpose()*norm;
        ray.intersection.normal.normalize();
        ray.intersection.none = false;
        return true;
    }

	return false;
}

