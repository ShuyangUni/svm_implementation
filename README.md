# svm_implementation
This is a simple implementation of Support Vector Machine (SVM)

# matlab
* The matlab version code is in **/matlab**.
  * **/matlab/data** 
    * Some test data
    * The code to generate test data
  * **/matlab/svm** 
    * The core implementation of svm
    * Using '*quadprog*' in training process.
  * **/matlab/demo_linear_test.m**
    * a linear example
  * **demo_nonlinear_test.m**
    * a non-linear example
  
* The input parameters are set in the struct '*svm*'.
* The output results are also stored in the same struct '*svm*'.

# cpp 
* The cpp version code is in **/cpp**.
  * **/cpp/data** 
    * Some test data in txt format
    * The last column is *label* while the rest are *data*
  * **/cpp/common** 
    * Common modules, including data loading module
  * **/cpp/support_vector_machine**
    * The core implementation of svm
    * In order to avoid external optimization library, using SMO in training process.
    * The implementation is following the paper in 1998.
    * *Sequential Minimal Optimization: A Fast Algorithm for Training Support Vector Machines*
  * **/cpp/demo_svm_smo_linear.cc**
    * a linear implementation
  * **/cpp/demo_svm_smo_nonlinear.cc**
    * a non-linear implementation

* The required libraries 
  * Eigen3 (tested in version 3.3.4)
  * cmake (tested in version 3.19.2)
  * g++/gcc (tested in version 7.5.0)

* To run the demo
```
cd cpp/
mkdir build
cd build
cmake .
make -j4
./demo_svm_smo_linear         # to run the linear svm demo
./demo_svm_smo_nonlinear      # to run the nonlinear svm demo
```