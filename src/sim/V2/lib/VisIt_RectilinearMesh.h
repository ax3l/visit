/*****************************************************************************
*
* Copyright (c) 2000 - 2019, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-442911
* All rights reserved.
*
* This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or other materials provided with the distribution.
*  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
* LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
* DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

#ifndef VISIT_RECTILINEAR_MESH_H
#define VISIT_RECTILINEAR_MESH_H

#ifdef __cplusplus
extern "C"
{
#endif

int VisIt_RectilinearMesh_alloc(visit_handle *obj);
int VisIt_RectilinearMesh_free(visit_handle obj);
int VisIt_RectilinearMesh_setCoordsXY(visit_handle obj, visit_handle x, visit_handle y);
int VisIt_RectilinearMesh_setCoordsXYZ(visit_handle obj, visit_handle x, visit_handle y, visit_handle z);
int VisIt_RectilinearMesh_setRealIndices(visit_handle obj, int min[3], int max[3]);
int VisIt_RectilinearMesh_setBaseIndex(visit_handle obj, int base_index[3]);
int VisIt_RectilinearMesh_setGhostCells(visit_handle obj, visit_handle gz);
int VisIt_RectilinearMesh_setGhostNodes(visit_handle obj, visit_handle gn);

int VisIt_RectilinearMesh_getCoords(visit_handle obj, int *ndims, visit_handle *x, visit_handle *y, visit_handle *z);
int VisIt_RectilinearMesh_getRealIndices(visit_handle obj, int min[3], int max[3]);
int VisIt_RectilinearMesh_getBaseIndex(visit_handle obj, int base_index[3]);
int VisIt_RectilinearMesh_getGhostCells(visit_handle h, visit_handle *gz);
int VisIt_RectilinearMesh_getGhostNodes(visit_handle h, visit_handle *gn);

#ifdef __cplusplus
}
#endif

#endif
