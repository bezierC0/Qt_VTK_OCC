# Qt VTK OpenCASCADE 集成项目

这是一个演示 OpenCASCADE Technology (OCC)、Visualization Toolkit (VTK) 和 Qt 集成的简单项目。

## 依赖项

*   Qt 5
*   OpenCASCADE Technology (OCC)
*   Visualization Toolkit (VTK)

## 编译方法

本项目使用 CMake 作为构建系统。

1.  **配置项目:**
    创建一个构建目录并运行 CMake。如果依赖项不在标准位置，您可能需要提供它们的路径。

    ```bash
    mkdir build
    cd build
    cmake ..
    ```
    *注意: 您可能需要指定您的生成器 (例如, "Visual Studio 16 2019") 以及 Qt, VTK, 和 OpenCASCADE 的路径。*

2.  **构建项目:**
    使用 CMake 生成的构建系统编译源代码。

    ```bash
    cmake --build .
    ```
    或者，您可以在您的 IDE 中打开生成的项目文件 (例如, Visual Studio 的 `.sln` 文件) 并从那里构建。
