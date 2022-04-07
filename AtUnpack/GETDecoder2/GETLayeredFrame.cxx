#include "GETLayeredFrame.h"

#include <TClonesArray.h>
#include <cstddef>

#include "GETBasicFrame.h"

GETLayeredFrame::GETLayeredFrame()
{
   fFrames = nullptr;

   Clear();
}

Int_t GETLayeredFrame::GetNumFrames()
{
   return GetNItems();
}
TClonesArray *GETLayeredFrame::GetFrames()
{
   return fFrames;
}
GETBasicFrame *GETLayeredFrame::GetFrame(Int_t index)
{
   return (GETBasicFrame *)fFrames->At(index);
}

void GETLayeredFrame::Clear(Option_t *)
{
   if (fFrames == nullptr)
      fFrames = new TClonesArray("GETBasicFrame", 48);

   GETLayerHeader::Clear();
   fFrames->Clear("C");
}

void GETLayeredFrame::Read(ifstream &stream)
{
   Clear();

   GETLayerHeader::Read(stream);

   for (Int_t iFrame = 0; iFrame < GetNItems(); iFrame++) {
      auto *frame = (GETBasicFrame *)fFrames->ConstructedAt(iFrame);
      frame->Read(stream);
   }
}