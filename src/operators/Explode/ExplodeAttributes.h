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

#ifndef EXPLODEATTRIBUTES_H
#define EXPLODEATTRIBUTES_H
#include <string>
#include <AttributeSubject.h>

class ExplodeAttributes;
#include <MapNode.h>

// ****************************************************************************
// Class: ExplodeAttributes
//
// Purpose:
//    This class contains attributes for the explode operator. 
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

class ExplodeAttributes : public AttributeSubject
{
public:
    enum ExplodeType
    {
        Point,
        Plane,
        Cylinder
    };
    enum ExplosionPattern
    {
        Impact,
        Scatter
    };
    enum SubsetType
    {
        Material,
        Domain,
        Group,
        EnumScalar,
        Unknown
    };

    // These constructors are for objects of this class
    ExplodeAttributes();
    ExplodeAttributes(const ExplodeAttributes &obj);
protected:
    // These constructors are for objects derived from this class
    ExplodeAttributes(private_tmfs_t tmfs);
    ExplodeAttributes(const ExplodeAttributes &obj, private_tmfs_t tmfs);
public:
    virtual ~ExplodeAttributes();

    virtual ExplodeAttributes& operator = (const ExplodeAttributes &obj);
    virtual bool operator == (const ExplodeAttributes &obj) const;
    virtual bool operator != (const ExplodeAttributes &obj) const;
private:
    void Init();
    void Copy(const ExplodeAttributes &obj);
public:

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;
    virtual AttributeSubject *NewInstance(bool) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectExplosionPoint();
    void SelectPlanePoint();
    void SelectPlaneNorm();
    void SelectCylinderPoint1();
    void SelectCylinderPoint2();
    void SelectMaterial();
    void SelectBoundaryNames();
    void SelectExplosions();
    void SetExplosionType(ExplodeType explosionType_);
    void SetExplosionPoint(const double *explosionPoint_);
    void SetPlanePoint(const double *planePoint_);
    void SetPlaneNorm(const double *planeNorm_);
    void SetCylinderPoint1(const double *cylinderPoint1_);
    void SetCylinderPoint2(const double *cylinderPoint2_);
    void SetMaterialExplosionFactor(double materialExplosionFactor_);
    void SetMaterial(const std::string &material_);
    void SetCylinderRadius(double cylinderRadius_);
    void SetExplodeMaterialCells(bool explodeMaterialCells_);
    void SetCellExplosionFactor(double cellExplosionFactor_);
    void SetExplosionPattern(ExplosionPattern explosionPattern_);
    void SetExplodeAllCells(bool explodeAllCells_);
    void SetBoundaryNames(const stringVector &boundaryNames_);
    void SetSubsetType(SubsetType subsetType_);
    ExplodeType        GetExplosionType() const;
    const double       *GetExplosionPoint() const;
          double       *GetExplosionPoint();
    const double       *GetPlanePoint() const;
          double       *GetPlanePoint();
    const double       *GetPlaneNorm() const;
          double       *GetPlaneNorm();
    const double       *GetCylinderPoint1() const;
          double       *GetCylinderPoint1();
    const double       *GetCylinderPoint2() const;
          double       *GetCylinderPoint2();
    double             GetMaterialExplosionFactor() const;
    const std::string  &GetMaterial() const;
          std::string  &GetMaterial();
    double             GetCylinderRadius() const;
    bool               GetExplodeMaterialCells() const;
    double             GetCellExplosionFactor() const;
    ExplosionPattern   GetExplosionPattern() const;
    bool               GetExplodeAllCells() const;
    const stringVector &GetBoundaryNames() const;
          stringVector &GetBoundaryNames();
    const AttributeGroupVector &GetExplosions() const;
          AttributeGroupVector &GetExplosions();
    SubsetType         GetSubsetType() const;

    // Persistence methods
    virtual bool CreateNode(DataNode *node, bool completeSave, bool forceAdd);
    virtual void SetFromNode(DataNode *node);


    // Attributegroup convenience methods
    void AddExplosions(const ExplodeAttributes &);
    void ClearExplosions();
    void RemoveExplosions(int i);
    int  GetNumExplosions() const;
    ExplodeAttributes &GetExplosions(int i);
    const ExplodeAttributes &GetExplosions(int i) const;

    ExplodeAttributes &operator [] (int i);
    const ExplodeAttributes &operator [] (int i) const;

    // Enum conversion functions
    static std::string ExplodeType_ToString(ExplodeType);
    static bool ExplodeType_FromString(const std::string &, ExplodeType &);
protected:
    static std::string ExplodeType_ToString(int);
public:
    static std::string ExplosionPattern_ToString(ExplosionPattern);
    static bool ExplosionPattern_FromString(const std::string &, ExplosionPattern &);
protected:
    static std::string ExplosionPattern_ToString(int);
public:
    static std::string SubsetType_ToString(SubsetType);
    static bool SubsetType_FromString(const std::string &, SubsetType &);
protected:
    static std::string SubsetType_ToString(int);
public:

    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;

    // User-defined methods
    bool AttributesMatch (const ExplodeAttributes &obj) const;

    // IDs that can be used to identify fields in case statements
    enum {
        ID_explosionType = 0,
        ID_explosionPoint,
        ID_planePoint,
        ID_planeNorm,
        ID_cylinderPoint1,
        ID_cylinderPoint2,
        ID_materialExplosionFactor,
        ID_material,
        ID_cylinderRadius,
        ID_explodeMaterialCells,
        ID_cellExplosionFactor,
        ID_explosionPattern,
        ID_explodeAllCells,
        ID_boundaryNames,
        ID_explosions,
        ID_subsetType,
        ID__LAST
    };

protected:
    AttributeGroup *CreateSubAttributeGroup(int index);
protected:
    int                  explosionType;
    double               explosionPoint[3];
    double               planePoint[3];
    double               planeNorm[3];
    double               cylinderPoint1[3];
    double               cylinderPoint2[3];
    double               materialExplosionFactor;
    std::string          material;
    double               cylinderRadius;
    bool                 explodeMaterialCells;
    double               cellExplosionFactor;
    int                  explosionPattern;
    bool                 explodeAllCells;
    stringVector         boundaryNames;
    AttributeGroupVector explosions;
    int                  subsetType;

private:
    // Static class format string for type map.
    static const char *TypeMapFormatString;
    static const private_tmfs_t TmfsStruct;
};
#define EXPLODEATTRIBUTES_TMFS "iDDDDDdsdbdibs*a*i"

#endif
