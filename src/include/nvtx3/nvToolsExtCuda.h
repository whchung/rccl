/*
* Copyright 2009-2020  NVIDIA Corporation.  All rights reserved.
*
* Licensed under the Apache License v2.0 with LLVM Exceptions.
* See https://llvm.org/LICENSE.txt for license information.
* SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
*/

#include "nvToolsExt.h"

#include "hip/hip_runtime.h"

#ifndef NVTOOLSEXT_CUDA_V3
#define NVTOOLSEXT_CUDA_V3

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* ========================================================================= */
/** \name Functions for CUDA Resource Naming
*/
/** \addtogroup RESOURCE_NAMING
 * \section RESOURCE_NAMING_CUDA CUDA Resource Naming
 *
 * This section covers the API functions that allow to annotate CUDA resources
 * with user-provided names.
 *
 * @{
 */

/*  ------------------------------------------------------------------------- */
/* \cond SHOW_HIDDEN 
* \brief Used to build a non-colliding value for resource types separated class
* \version \NVTX_VERSION_2
*/
#define NVTX_RESOURCE_CLASS_CUDA  4
/** \endcond */

/*  ------------------------------------------------------------------------- */
/** \brief Resource types for CUDA
*/
typedef enum nvtxResourceCUDAType_t
{
    NVTX_RESOURCE_TYPE_CUDA_DEVICE = NVTX_RESOURCE_MAKE_TYPE(CUDA, 1), /* hipDevice_t */
    NVTX_RESOURCE_TYPE_CUDA_CONTEXT = NVTX_RESOURCE_MAKE_TYPE(CUDA, 2), /* hipCtx_t */
    NVTX_RESOURCE_TYPE_CUDA_STREAM = NVTX_RESOURCE_MAKE_TYPE(CUDA, 3), /* hipStream_t */
    NVTX_RESOURCE_TYPE_CUDA_EVENT = NVTX_RESOURCE_MAKE_TYPE(CUDA, 4), /* hipEvent_t */
} nvtxResourceCUDAType_t;


/* ------------------------------------------------------------------------- */
/** \brief Annotates a CUDA device.
 *
 * Allows the user to associate a CUDA device with a user-provided name.
 *
 * \param device - The handle of the CUDA device to name.
 * \param name   - The name of the CUDA device.
 *
 * \version \NVTX_VERSION_1
 * @{ */
NVTX_DECLSPEC void NVTX_API nvtxNameCuDeviceA(hipDevice_t device, const char* name);
NVTX_DECLSPEC void NVTX_API nvtxNameCuDeviceW(hipDevice_t device, const wchar_t* name);
/** @} */

/* ------------------------------------------------------------------------- */
/** \brief Annotates a CUDA context.
 *
 * Allows the user to associate a CUDA context with a user-provided name.
 *
 * \param context - The handle of the CUDA context to name.
 * \param name    - The name of the CUDA context.
 *
 * \par Example:
 * \code
 * hipError_t status = hipCtxCreate( &cuContext, 0, cuDevice );
 * if ( hipSuccess != status )
 *     goto Error;
 * nvtxNameCuContext(cuContext, "CTX_NAME");
 * \endcode
 *
 * \version \NVTX_VERSION_1
 * @{ */
NVTX_DECLSPEC void NVTX_API nvtxNameCuContextA(hipCtx_t context, const char* name);
NVTX_DECLSPEC void NVTX_API nvtxNameCuContextW(hipCtx_t context, const wchar_t* name);
/** @} */

/* ------------------------------------------------------------------------- */
/** \brief Annotates a CUDA stream.
 *
 * Allows the user to associate a CUDA stream with a user-provided name.
 *
 * \param stream - The handle of the CUDA stream to name.
 * \param name   - The name of the CUDA stream.
 *
 * \version \NVTX_VERSION_1
 * @{ */
NVTX_DECLSPEC void NVTX_API nvtxNameCuStreamA(hipStream_t stream, const char* name);
NVTX_DECLSPEC void NVTX_API nvtxNameCuStreamW(hipStream_t stream, const wchar_t* name);
/** @} */

/* ------------------------------------------------------------------------- */
/** \brief Annotates a CUDA event.
 *
 * Allows the user to associate a CUDA event with a user-provided name.
 *
 * \param event - The handle of the CUDA event to name.
 * \param name  - The name of the CUDA event.
 *
 * \version \NVTX_VERSION_1
 * @{ */
NVTX_DECLSPEC void NVTX_API nvtxNameCuEventA(hipEvent_t event, const char* name);
NVTX_DECLSPEC void NVTX_API nvtxNameCuEventW(hipEvent_t event, const wchar_t* name);
/** @} */

/** @} */ /* END RESOURCE_NAMING */

/* ========================================================================= */
#ifdef UNICODE
  #define nvtxNameCuDevice   nvtxNameCuDeviceW
  #define nvtxNameCuContext  nvtxNameCuContextW
  #define nvtxNameCuStream   nvtxNameCuStreamW
  #define nvtxNameCuEvent    nvtxNameCuEventW
#else
  #define nvtxNameCuDevice   nvtxNameCuDeviceA
  #define nvtxNameCuContext  nvtxNameCuContextA
  #define nvtxNameCuStream   nvtxNameCuStreamA
  #define nvtxNameCuEvent    nvtxNameCuEventA
#endif

#ifdef __cplusplus
}
#endif /* __cplusplus */

#ifndef NVTX_NO_IMPL
#define NVTX_IMPL_GUARD_CUDA /* Ensure other headers cannot included directly */
#include "nvtxDetail/nvtxImplCuda_v3.h"
#undef NVTX_IMPL_GUARD_CUDA
#endif /*NVTX_NO_IMPL*/

#endif /* NVTOOLSEXT_CUDA_V3 */
