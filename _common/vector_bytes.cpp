/* vector_bytes.h  -- source for interface functions to the kernels
 defined in vector_bytes.cl, the corresponding binaries are in binfiles/vector_bytes.bin
 THIS IS AN AUTO-GENERATED FILE, DO NOT EDIT */

#include"vector_bytes.h"
#include"KernelFile.h"
#include<vector>
#include<iostream>
#include<cassert>


namespace vector_bytes_GPU{

	 cl::Kernel * k_vector_bytes = 0;
	 int prepare_kernels(const DeviceInterface * dev){
		 FILE * input = fopen("binfiles/vector_bytes.bin","rb");
		 if(!input){
			 	std::cerr << "Loading binary file binfiles/vector_bytes.bin failed \n";
			 	return FAILURE;
		 }
		 fseek(input, 0L, SEEK_END);
		 size_t size = ftell(input);
		 rewind(input);
		 cl_int err;
		 char * binary = new char[size];
		 fread(binary, sizeof(char), size, input);
		 fclose(input);
		 cl::Program::Binaries binaries;
		 std::vector<int> binstatus;
		 for(unsigned int d=0; d < (*(dev->GetDevices())).size(); d++){
			 binstatus.push_back(0);
			 binaries.push_back(std::make_pair(binary, size));
		 }
		 cl::Program * bProgram = new cl::Program(*(dev->GetContext()),
		 						   *(dev->GetDevices()),
		 						   binaries,
		 						   &binstatus,
		 						   &err);
		 if (err != CL_SUCCESS) {
			 	std::cerr << "Loading binaries failed (" << err << ")\n";
			 	return FAILURE;
		 }
		 err = bProgram->build(*(dev->GetDevices()));
		 if (err != CL_SUCCESS) {
		 	std::cerr << "Program::build() failed (" << err << ")\n";
		 	return FAILURE;
		 }

		 k_vector_bytes = new cl::Kernel(*bProgram, "vector_bytes", &err);
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel::Kernel() failed (" << err << ") for kernel vector_bytes\n";
			 return FAILURE;
		 }

	 return 0;
	 }



	 int vector_bytes(const DeviceInterface * dev, Stream<uchar16> * test){

		 cl_int err;
		 std::vector<cl::Event> *evvec = new std::vector<cl::Event>();
		 cl::Event event = cl::Event();

		 evvec->push_back((test->GetEvent()));
		 err = k_vector_bytes->setArg(0, *(*test)());
		 if (err != CL_SUCCESS) {
			 std::cerr << "Kernel.SetArg() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 err = dev->GetQueue()->enqueueNDRangeKernel(*k_vector_bytes, cl::NullRange, cl::NDRange(test->GetD1(),test->GetD2()), cl::NullRange, evvec, &event );
		 if (err != CL_SUCCESS) {
			 std::cerr << "CommandQueue::enqueueNDRangeKernel() failed (" << err << ")\n";
			 assert(0);
			 return FAILURE;
		 }

		 delete evvec;
	 return 0;
	 }

}
