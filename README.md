# cppngrok
a cpp wrapper for ngrok


### requirements
```
https://github.com/whoshuu/cpr
```

### basic usage
```cpp
#include <cppngrok.h> // or "cppngrok.h" if locally

void main(){
  Setup cppn_handler;
  cppn_handler.connect() // http tunnel on default port (8080)
  cppn_handler.connect("tcp", 1337) // tcp tunnel in port 1337
  
  // see documentation for full guide

}
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
