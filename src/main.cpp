#include <iostream>
#include <set>
#include <mxnet-cpp/MxNetCpp.h>
#include <leptonica/allheaders.h>
#include "opencv2/opencv.hpp"

using namespace mxnet::cpp;
using namespace std::chrono;

int iterators_mxnet();

/*The global context, change them if necessary*/
static mxnet::cpp::Context global_ctx(mxnet::cpp::kCPU, 0);
// static Context global_ctx(mxnet::cpp::kCPU,0);

int main(int argc, char const *argv[]) {
    int version;
    MXGetVersion(&version);

    LG << "MxNet     version : " << version;
    LG << "Leptonica version : " << getLeptonicaVersion();
    LG << "OpenCV    version : " << CV_VERSION;
    LG << "MxNet Base";
    iterators_mxnet();

    return 0;
}

/*!
 * Dump existing data iterators
 * @return
 */
int iterators_mxnet() {
    mx_uint num_data_iter_creators;
    DataIterCreator *data_iter_creators = nullptr;

    int r = MXListDataIters(&num_data_iter_creators, &data_iter_creators);
    CHECK_EQ(r, 0);
    LG << "num_data_iter_creators = " << num_data_iter_creators;
    //output: num_data_iter_creators = 8

    const char *name;
    const char *description;
    mx_uint num_args;
    const char **arg_names;
    const char **arg_type_infos;
    const char **arg_descriptions;

    for (mx_uint i = 0; i < num_data_iter_creators; i++) {
        r = MXDataIterGetIterInfo(data_iter_creators[i], &name, &description,
                                  &num_args, &arg_names, &arg_type_infos,
                                  &arg_descriptions);
        CHECK_EQ(r, 0);
        LG << " i: " << i << ", name: " << name;
    }

    MXNotifyShutdown();
    return 0;
}
