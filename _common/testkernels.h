/* testkernels.h  -- header for interface functions to the kernels
 defined in testkernels.cl, the corresponding binaries are in binfiles/testkernels.bin
 THIS IS AN AUTO-GENERATED FILE, DO NOT EDIT */

#ifndef HHtestkernels_GPUHH
#define HHtestkernels_GPUHH


#include"Stream.h"
#include"DeviceInterface.h"


namespace testkernels_GPU{

	 int prepare_kernels(const DeviceInterface * dev);

	 extern cl::Kernel * k_testmul2;
	 extern cl::Kernel * k_testmul;
	 int testmul2(const DeviceInterface * dev, Stream<float> * vec, Stream<float> * scal, Stream<float> * result);

	 int testmul(const DeviceInterface * dev, Stream<float> * result);

}
#endif
