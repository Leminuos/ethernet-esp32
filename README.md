# Example of Component Requirements

Ví dụ một cây thư mục như sau:

```
- autoProject/
             - CMakeLists.txt
             - components/ - car/ - CMakeLists.txt
                                     - car.c
                                     - car.h
                           - engine/ - CMakeLists.txt
                                     - engine.c
                                     - include/ - engine.h
                           - spark_plug/  - CMakeLists.txt
                                          - spark_plug.c
                                          - spark_plug.h
```

### Car component

Nội dung của file header như sau:

```h
/* car.h */
#include "engine.h"

#ifdef ENGINE_IS_HYBRID
#define CAR_MODEL "Hybrid"
#endif
```

Nội dung của file source như sau:

```c
/* car.c */
#include "car.h"
```

Nội dung của file CMakeLists.txt như sau:

```make
idf_component_register(SRCS "car.c"
                  INCLUDE_DIRS "."
                  REQUIRES engine)
```

- `SRCS`: khai báo các file source của component.
- `INCLUDE_DIRS`:khai báo các file header mà component cung cấp.
- `REQUIRES`: khai báo các component cần thiết để có thể build component này.
- `idf_component_register` là một macro đặc biệt của ESP-IDF dùng để:
  - Khai báo 1 component (tức là thư viện con, module,...)
  - Cho biết file source
  - Chỉ định các thư mục chứa header
  - Khai báo dependency tới các component khác

