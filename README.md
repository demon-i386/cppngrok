# cppngrok
a cpp wrapper for ngrok

### basic usage
```cpp
#include <cppngrok.h> // or "cppngrok.h" if locally

void main(){
  Setup cppn_handler;
  cppn_handler.bind() // http tunnel on default port (8080)
  cppn_handler.bind("tcp", 1337) // tcp tunnel in port 1337
  
  // see documentation for full guide

}
```
### requeriments

```
https://ngrok.com/
```

### simple static build

```
make
g++ your_project.cpp build/cppngrok_lib.a
make clean
```

#### based in pyngrok
```
https://github.com/alexdlaird/pyngrok
```
