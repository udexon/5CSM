Stack Machine Parser Generator

```
190 38 START_BLOCK IN_IF 0 int main(int argc, const char** argv) {
203 28 START_BLOCK IN_IF 1 if (ciErrNum != CL_SUCCESS) {
206 7 START_BLOCK IN_IF 2 } else {
206 0 B_206_7_206_0 END_BLOCK IN_IF 3 } else {
207 24 START_BLOCK IN_IF 2 if (num_platforms == 0) {
210 7 START_BLOCK IN_IF 3 } else {
210 0 B_210_7_210_0 END_BLOCK IN_IF 4 } else {
212 95 START_BLOCK IN_IF 3 if ((clPlatformIDs = (cl_platform_id*)malloc(num_platforms * sizeof(cl_platform_id))) == NULL) {
215 0 B_212_95_215_0 END_BLOCK IN_IF 4 }
220 43 START_BLOCK IN_IF 3 for(cl_uint i = 0; i < num_platforms; ++i) {
222 27 START_BLOCK IN_IF 4 if(ciErrNum == CL_SUCCESS) {
226 28 START_BLOCK IN_IF 5 if (ciErrNum == CL_SUCCESS) {
229 7 START_BLOCK IN_IF 6 } else {
229 0 B_229_7_229_0 END_BLOCK IN_IF 7 } else {
232 0 B_226_28_232_0 END_BLOCK IN_IF 6 }
236 28 START_BLOCK IN_IF 5 if (ciErrNum == CL_SUCCESS) {
239 7 START_BLOCK IN_IF 6 } else {
239 0 B_239_7_239_0 END_BLOCK IN_IF 7 } else {
242 0 B_236_28_242_0 END_BLOCK IN_IF 6 }
254 24 START_BLOCK IN_IF 5 if (ciDeviceCount == 0) {
258 35 START_BLOCK IN_IF 6 } else if (ciErrNum != CL_SUCCESS) {
258 0 B_258_35_258_0 END_BLOCK IN_IF 7 } else if (ciErrNum != CL_SUCCESS) {
261 7 START_BLOCK IN_IF 6 } else {
261 0 B_261_7_261_0 END_BLOCK IN_IF 7 } else {
268 85 START_BLOCK IN_IF 6 if ((devices = (cl_device_id*)malloc(sizeof(cl_device_id) * ciDeviceCount)) == NULL) {
271 0 B_268_85_271_0 END_BLOCK IN_IF 7 }
273 28 START_BLOCK IN_IF 6 if (ciErrNum == CL_SUCCESS) {
274 50 START_BLOCK IN_IF 7 for(unsigned int i = 0; i < ciDeviceCount; ++i )  {
282 0 B_274_50_282_0 END_BLOCK IN_IF 8 }
283 7 START_BLOCK IN_IF 7 } else {
283 0 B_283_7_283_0 END_BLOCK IN_IF 8 } else {
286 0 B_273_28_286_0 END_BLOCK IN_IF 7 }
287 0 B_254_24_287_0 END_BLOCK IN_IF 6 }
292 0 B_222_27_292_0 END_BLOCK IN_IF 5 }
294 0 B_220_43_294_0 END_BLOCK IN_IF 4 }
295 0 B_207_24_295_0 END_BLOCK IN_IF 3 }
296 0 B_203_28_296_0 END_BLOCK IN_IF 2 }
317 3 START_BLOCK IN_IF 1 do {
323 20 START_BLOCK IN_IF 2 if( tmp == "name" ) {
327 3 START_BLOCK IN_IF 3 do {
329 36 START_BLOCK IN_IF 4 if (tmp != std::string("stepping")) {
331 0 B_329_36_331_0 END_BLOCK IN_IF 5 }
333 0 B_327_3_333_0 END_BLOCK IN_IF 4 }
337 0 B_323_20_337_0 END_BLOCK IN_IF 3 }
338 0 B_317_3_338_0 END_BLOCK IN_IF 2 }
352 0 B_190_38_352_0 END_BLOCK IN_IF 1 }
```
