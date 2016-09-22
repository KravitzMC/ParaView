/*=========================================================================

  Program:   ParaView
  Module:    $RCSfile$

  Copyright (c) Kitware, Inc.
  All rights reserved.
  See Copyright.txt or http://www.paraview.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#include "vtkPVStreamingPiecesInformation.h"

#include "vtkClientServerStream.h"
#include "vtkObjectFactory.h"
#include "vtkPVDataDeliveryManager.h"
#include "vtkPVRenderView.h"

#include <algorithm>
#include <set>
#include <vector>

class vtkPVStreamingPiecesInformation::vtkInternals :
  public std::set<unsigned int>
{
};

vtkStandardNewMacro(vtkPVStreamingPiecesInformation);
//----------------------------------------------------------------------------
vtkPVStreamingPiecesInformation::vtkPVStreamingPiecesInformation()
  : Internals (new vtkInternals())
{
}

//----------------------------------------------------------------------------
vtkPVStreamingPiecesInformation::~vtkPVStreamingPiecesInformation()
{
  delete this->Internals;
  this->Internals = NULL;
}

//----------------------------------------------------------------------------
void vtkPVStreamingPiecesInformation::CopyFromObject(vtkObject* object)
{
  vtkPVRenderView* view = vtkPVRenderView::SafeDownCast(object);
  if (!view)
    {
    vtkErrorMacro("Incorrect object: " <<
      (object? object->GetClassName() : "(null)"));
    return;
    }

  this->Internals->clear();

  vtkPVDataDeliveryManager* mgr = view->GetDeliveryManager();
  std::vector<unsigned int> keys;
  mgr->GetRepresentationsReadyToStreamPieces(keys);
  this->Internals->insert(keys.begin(), keys.end());
}

//----------------------------------------------------------------------------
void vtkPVStreamingPiecesInformation::AddInformation(vtkPVInformation* info)
{
  vtkPVStreamingPiecesInformation* other =
    vtkPVStreamingPiecesInformation::SafeDownCast(info);
  if (!other)
    {
    return;
    }

  this->Internals->insert(
    other->Internals->begin(), other->Internals->end());
}

//----------------------------------------------------------------------------
void vtkPVStreamingPiecesInformation::CopyToStream(vtkClientServerStream* css)
{
  css->Reset();
  *css << vtkClientServerStream::Reply
       << static_cast<int>(this->Internals->size());
  for (vtkInternals::iterator iter = this->Internals->begin();
    iter != this->Internals->end(); ++iter)
    {
    *css << (*iter);
    }
  *css << vtkClientServerStream::End;
}

//----------------------------------------------------------------------------
void vtkPVStreamingPiecesInformation::CopyFromStream(
  const vtkClientServerStream* css)
{
  this->Internals->clear();

  int num_items=0;
  css->GetArgument(0, 0, &num_items);
  for (int cc=0; cc < num_items; cc++)
    {
    unsigned int value;
    css->GetArgument(0, 1 + cc, &value);
    this->Internals->insert(value);
    }
}

//----------------------------------------------------------------------------
void vtkPVStreamingPiecesInformation::GetKeys(
  std::vector<unsigned int>& keys) const
{
  keys.insert(keys.end(), this->Internals->begin(), this->Internals->end());
}

//----------------------------------------------------------------------------
void vtkPVStreamingPiecesInformation::PrintSelf(ostream& os, vtkIndent indent)
{
  this->Superclass::PrintSelf(os, indent);
  os << indent << "Keys (" << this->Internals->size()  << "): " << endl;
  for (vtkInternals::iterator iter = this->Internals->begin();
    iter != this->Internals->end(); ++iter)
    {
    os << indent.GetNextIndent()  << (*iter) << endl;
    }
}
