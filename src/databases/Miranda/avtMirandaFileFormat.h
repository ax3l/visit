/*****************************************************************************
*
* Copyright (c) 2000 - 2007, The Regents of the University of California
* Produced at the Lawrence Livermore National Laboratory
* All rights reserved.
*
* This file is part of VisIt. For details, see http://www.llnl.gov/visit/. The
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
*    documentation and/or materials provided with the distribution.
*  - Neither the name of the UC/LLNL nor  the names of its contributors may be
*    used to  endorse or  promote products derived from  this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED.  IN  NO  EVENT  SHALL  THE  REGENTS  OF  THE  UNIVERSITY OF
* CALIFORNIA, THE U.S.  DEPARTMENT  OF  ENERGY OR CONTRIBUTORS BE  LIABLE  FOR
* ANY  DIRECT,  INDIRECT,  INCIDENTAL,  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

// ************************************************************************* //
//                            avtMirandaFileFormat.h                           //
// ************************************************************************* //

#ifndef AVT_Miranda_FILE_FORMAT_H
#define AVT_Miranda_FILE_FORMAT_H

#include <avtMTMDFileFormat.h>

#include <string>
#include <vector>

using std::string;
using std::vector;
class DBOptionsAttributes;


// ****************************************************************************
//  Class: avtMirandaFileFormat
//
//  Purpose:
//      Reads in Miranda files as a plugin to VisIt.
//
//  Programmer: dbremer -- generated by xml2avt
//  Creation:   Tue Jan 23 17:00:13 PST 2007
//
// ****************************************************************************

class avtMirandaFileFormat : public avtMTMDFileFormat
{
  public:
                           avtMirandaFileFormat(const char *, DBOptionsAttributes *);
    virtual               ~avtMirandaFileFormat() {;};

    virtual void          *GetAuxiliaryData(const char *var, int timestate, 
                                            int domain, const char *type, 
                                            void *args, DestructorFunction &);
    
    virtual void           GetCycles(std::vector<int> &c)    {c = aCycles;}
    virtual void           GetTimes(std::vector<double> &t)  {t = aSimTimes;}

    virtual int            GetNTimesteps(void)  {return aCycles.size();}

    virtual const char    *GetType(void)   { return "Miranda"; }
    virtual void           FreeUpResources(void); 

    virtual vtkDataSet    *GetMesh(int, int, const char *);
    virtual vtkDataArray  *GetVar(int, int, const char *);
    virtual vtkDataArray  *GetVectorVar(int, int, const char *);

  protected:
    int                    dim;           // dimensionality.  2 or 3
    int                    flatDim;       // if dim==2, flatDim == 0,1,or 2
    
    double                 fOrigin[3];    // sample 0,0,0 is centered on fOrigin
    double                 fStride[3];    // spacing between samples
    
    int                    iBlockSize[3];
    int                    iNumBlocks[3];
    
    vector<string>         aVarNames;
    vector<int>            aVarNumComps;
    vector<vector<float> > aVarMinMax;    // Current Miranda dumps write min/max
                                          // of last timestep, so for now this 
                                          // is almost unused.

    vector<string>         aMatNames;     // Material names. Size is 0 if there
                                          // is no material set. If present, the
                                          // material set comes after all vars.
    vector<int>            aCycles;
    vector<double>         aSimTimes;
    
    string                 fileTemplate;
    string                 gridTemplate;

    vector<int>            domainMap;     // has 3-int tuple for each block--
                                          // domain index to i,j,k block.
    
    virtual void           PopulateDatabaseMetaData(avtDatabaseMetaData *, int);
    virtual void           DomainToIJK(int domain, int &i, int &j, int &k);

    static  void           SkipToEndOfLine( ifstream &f, bool bCheckForBadTokens = true );
    static  double         GetFortranDouble( ifstream &f );
};


#endif
