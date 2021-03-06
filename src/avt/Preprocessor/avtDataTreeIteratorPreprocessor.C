// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                           avtDataTreeIteratorPreprocessor.C                       //
// ************************************************************************* //

#include <avtDataTreeIteratorPreprocessor.h>

#include <vtkDataSet.h>

#include <avtDataTree.h>

#include <DebugStream.h>


// ****************************************************************************
//  Method: avtDataTreeIteratorPreprocessor constructor
//
//  Programmer: Hank Childs
//  Creation:   September 9, 2001
//
// ****************************************************************************

avtDataTreeIteratorPreprocessor::avtDataTreeIteratorPreprocessor()
{
    ;
}


// ****************************************************************************
//  Method: avtDataTreeIteratorPreprocessor destructor
//
//  Programmer: Hank Childs
//  Creation:   September 9, 2001
//
// ****************************************************************************

avtDataTreeIteratorPreprocessor::~avtDataTreeIteratorPreprocessor()
{
    ;
}


// ****************************************************************************
//  Method: avtDataTreeIteratorPreprocessor::Preprocess
//
//  Purpose:
//      Does the actual preprocessing work.  Since most derived types do not
//      want to code up how to unwrap a data tree, this does it for them.  It
//      then calls ProcessDomain for each data tree, which the derived types
//      must define.
//
//  Programmer: Hank Childs
//  Creation:   September 9, 2001
//
// ****************************************************************************

void
avtDataTreeIteratorPreprocessor::Preprocess(void)
{
    avtDataTree_p tree = GetInputDataTree();
    int totalNodes = tree->GetNumberOfLeaves();

    debug3 << "Preprocessing with " << totalNodes << " nodes." << endl;
    Initialize(totalNodes);

    debug3 << "Preprocessing the top level tree" << endl;
    PreprocessTree(tree);

    debug3 << "Allowing preprocessing module to finalize." << endl;
    Finalize();
}


// ****************************************************************************
//  Method: avtDataTreeIteratorPreprocessor::PreprocessTree
//
//  Purpose:
//      Unwraps a data tree and calls ProcessDomain on each leaf. 
//
//  Programmer: Hank Childs
//  Creation:   September 9, 2001
//
//  Modifications:
//    Kathleen Bonnell, Wed May 17 15:15:24 PDT 2006
//    Remove call to SetSource(NULL) as it now removes information necessary
//    for the dataset.
//
// ****************************************************************************

void
avtDataTreeIteratorPreprocessor::PreprocessTree(avtDataTree_p tree)
{
    if (*tree == NULL)
    {
        return;
    }

    int numChildren = tree->GetNChildren();

    if ( (numChildren <= 0) && (!(tree->HasData())) )
    {
        return;
    }

    if (numChildren == 0)
    {
        //
        // There is only one dataset to process (the leaf).
        //
        vtkDataSet *in_ds = tree->GetDataRepresentation().GetDataVTK();
        int dom = tree->GetDataRepresentation().GetDomain();

        //
        // Ensure that there is no funny business when we do an Update.
        //
        // NO LONGER A GOOD IDEA
        //in_ds->SetSource(NULL);

        ProcessDomain(in_ds, dom);
    }
    else
    {
        for (int i = 0 ; i < numChildren ; i++)
        {
            if (tree->ChildIsPresent(i))
            {
                PreprocessTree(tree->GetChild(i));
            }
        }
    }
}


// ****************************************************************************
//  Method: avtDataTreeIteratorPreprocessor::Initialize
//
//  Purpose:
//      Gives the preprocessor module a chance to initialize itself.  This
//      implementation does nothing, but is defined so derived types can
//      initalize themselves if appropriate.
//
//  Programmer: Hank Childs
//  Creation:   September 9, 2001
//
// ****************************************************************************

void
avtDataTreeIteratorPreprocessor::Initialize(int)
{
    ;
}


// ****************************************************************************
//  Method: avtDataTreeIteratorPreprocessor::Finalize
//
//  Purpose:
//      Gives the preprocessor module a chance to finalize itself.  This
//      implementation does nothing, but is defined so derived types can
//      finalize themselves if appropriate.
//
//  Programmer: Hank Childs
//  Creation:   September 9, 2001
//
// ****************************************************************************

void
avtDataTreeIteratorPreprocessor::Finalize(void)
{
    ;
}


