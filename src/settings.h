

#ifdef _DEBUG 
#define MODE "DEBUG"
#include <iostream>
#define LOG(x) std::cout << x << "\n"
#endif

#ifdef _RELEASE 
#define MODE "RELEASE"
#define LOG(x) 
#endif

#define DEFAULT_VERTEX_SHADER "shaders/vertexShader.vs"