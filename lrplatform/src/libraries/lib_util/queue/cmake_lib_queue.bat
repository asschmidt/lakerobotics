SET BUILD_OUTPUT="../../../build_output/%1/obj/lib_queue"
mkdir %BUILD_OUTPUT%

cmake -E chdir %BUILD_OUTPUT% cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=%1 -DPLATFORM_ROOT="%2" -DAPPLICATION_ROOT="%3"  ../../../../src/libraries/queue
