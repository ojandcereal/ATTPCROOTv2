#include "AtTabBase.h"

#include "AtTabInfo.h"

#include <TEveBrowser.h>
#include <TEveManager.h>
#include <TEveWindow.h>
ClassImp(AtTabBase);
int AtTabBase::fNumTabs = 0;

AtTabBase::AtTabBase() : fTabId(fNumTabs)
{
   fNumTabs++;
}
/// Init both the tab (InitTab()) and then init the AtTabInfo class
void AtTabBase::Init()
{
   InitTab();
   fTabInfo->Init();
   MakeTab(TEveWindow::CreateWindowInTab(gEve->GetBrowser()->GetTabRight()));
}