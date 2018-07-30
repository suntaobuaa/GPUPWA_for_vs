/* vector_bytes.h  -- header for interface functions to the kernels
 defined in vector_bytes.cl, the corresponding binaries are in binfiles/vector_bytes.bin
 THIS IS AN AUTO-GENERATED FILE, DO NOT EDIT */

#ifndef HHvector_bytes_GPUHH
#define HHvector_bytes_GPUHH


#include"Stream.h"
#include"DeviceInterface.h"


namespace vector_bytes_GPU{

	 int prepare_kernels(const DeviceInterface * dev);

	 extern cl::Kernel * k_vector_bytes;
	 int vector_bytes(const DeviceInterface * dev, Stream<uchar16> * test);

}
#endif
