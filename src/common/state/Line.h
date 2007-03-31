#ifndef LINE_H
#define LINE_H
#include <state_exports.h>
#include <string>
#include <AttributeSubject.h>
#include <ColorAttribute.h>

// ****************************************************************************
// Class: Line
//
// Purpose:
//    Attributes for a line
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   Thu Dec 18 11:24:14 PDT 2003
//
// Modifications:
//   
// ****************************************************************************

class STATE_API Line : public AttributeSubject
{
public:
    Line();
    Line(const Line &obj);
    virtual ~Line();

    virtual void operator = (const Line &obj);
    virtual bool operator == (const Line &obj) const;
    virtual bool operator != (const Line &obj) const;

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;
    virtual AttributeSubject *NewInstance(bool) const;

    // Property selection methods
    virtual void SelectAll();
    void SelectPoint1();
    void SelectPoint2();
    void SelectDesignator();
    void SelectColor();
    void SelectVarName();

    // Property setting methods
    void SetPoint1(const double *point1_);
    void SetPoint2(const double *point2_);
    void SetDesignator(const std::string &designator_);
    void SetColor(const ColorAttribute &color_);
    void SetLineStyle(int lineStyle_);
    void SetLineWidth(int lineWidth_);
    void SetInteractive(bool interactive_);
    void SetReflineLabels(bool reflineLabels_);
    void SetVarName(const std::string &varName_);
    void SetNumSamples(int numSamples_);

    // Property getting methods
    const double         *GetPoint1() const;
          double         *GetPoint1();
    const double         *GetPoint2() const;
          double         *GetPoint2();
    const std::string    &GetDesignator() const;
          std::string    &GetDesignator();
    const ColorAttribute &GetColor() const;
          ColorAttribute &GetColor();
    int                  GetLineStyle() const;
    int                  GetLineWidth() const;
    bool                 GetInteractive() const;
    bool                 GetReflineLabels() const;
    const std::string    &GetVarName() const;
          std::string    &GetVarName();
    int                  GetNumSamples() const;

    // Persistence methods
    virtual bool CreateNode(DataNode *node, bool completeSave, bool forceAdd);
    virtual void SetFromNode(DataNode *node);


    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;

    // User-defined methods
    void SetPoint1(double,double,double);
    void SetPoint2(double,double,double);
private:
    double         point1[3];
    double         point2[3];
    std::string    designator;
    ColorAttribute color;
    int            lineStyle;
    int            lineWidth;
    bool           interactive;
    bool           reflineLabels;
    std::string    varName;
    int            numSamples;
};

#endif
