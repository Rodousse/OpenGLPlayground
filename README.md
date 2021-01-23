# OpenGLPlayground


## Dependencies

This project uses different dependencies:

- [Assimp](https://github.com/assimp/assimp): Used to load model files to render 
- [Eigen](http://eigen.tuxfamily.org/index.php?title=Main_Page): Matrice and vector manipulation
- [Stbipp](https://github.com/Rodousse/stbipp): Image I/O
- [glfw](https://github.com/glfw/glfw.git): Window and context provider
- [Flix01/imgui](https://github.com/Flix01/imgui.git): Imgui fork with an additionnal file browser 
- [glew-cmake](https://github.com/Perlmint/glew-cmake.git): OpenGL extension wrangler
- [spdlog](https://github.com/gabime/spdlog.git): Log system

---


## Install

Whole install instructions:
```
git clone https://github.com/Rodousse/OpenGLPlayground.git
cd OpenGLPlayground
# Third party install 
cd third_party
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX="Wherever/you/want" .. 
make
# Project build
cd ../../project
mkdir build
cd build
cmake -DCMAKE_PREFIX_PATH="thirdParty/install/path/" ..
make
```
