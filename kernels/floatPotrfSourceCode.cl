

//TODO: put in actual source code -.-
kernel void float_potrf(global float* inout){
	const int globalid = get_global_id(0);
	inout[globalid] = inout[globalid] + 7;
}
