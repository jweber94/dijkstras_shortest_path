#ifndef GRAPHVERTEX
#define GRAPHVERTEX

#include <stddef.h>

class GraphVertex {
public:
  GraphVertex() = default;

private:
  size_t vertex_idx_;
};

#endif /* GRAPHVERTEX */