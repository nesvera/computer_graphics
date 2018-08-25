#ifndef EDGE_H
#define EDGE_H

#include "Vector3.h"

class Edge
{

public:
    Edge(Vector3 _v0, Vector3 _v1){
        v0 = new Vector3(_v0);
        v1 = new Vector3(_v1);
    }

    Vector3 *v0, *v1;

};

#endif // EDGE_H
