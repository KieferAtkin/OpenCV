# **OpenCV**

This project has be setup to use the OpenCV PreBuilt Binaries with the use of 
the C++ language and Microsoft Visual Studio.
 
 https://opencv.org/releases/
 
 
### **IGCV**
 
 IGCV will be the main IrisGuard OpenCV core of the application.
 
 - [ ] Make into a .dll or static?

### **UI Application**

UI Application Project will be a lite User Interface to interact with IGCVcore whilst
performing all testing and development until the requirements have been successfully completed.

- [ ] Setup OpenGL with DearImGUI with additional libraries. (RealTime Rendering).
      Additional libraries would be Glew, GLFW, GLM etc.
- [ ] CVUI.h library? 
       - https://learnopencv.com/cvui-gui-lib-built-on-top-of-opencv-drawing-primitives/
       - https://dovyski.github.io/cvui/

### **OpenCV Test**

This is the testing project area for testing different concepts using OpenCV's Calls.

- [ ] Exclude all uneccessary file from the project when building. 
- [ ] Change MedianBlur to GauusianBlur in the main testing .cpp file.
- [ ] Refactor code from main into reuseable functions.
- [ ] Eyelid Detection.
- [ ] Gaussian Noise detection for countermeasure. Spoofing etc.

