#include <stdio.h>
#include "nsVoidArray.h"
#include "nsIWebShell.h"
#include "nsString.h"
#include "nsIComponentManager.h"
#include "nsParserCIID.h"

#ifdef XP_PC
#define PARSER_DLL "gkparser.dll"
#elif defined(XP_UNIX) || defined(XP_BEOS)
#define PARSER_DLL "libhtmlpars"MOZ_DLL_SUFFIX
#else
#define PARSER_DLL "libraptorhtmlpars"MOZ_DLL_SUFFIX
#endif

extern "C" NS_EXPORT int DebugRobot(nsVoidArray * workList, nsIWebShell * ww);

int main(int argc, char **argv)
{
  nsVoidArray * gWorkList = new nsVoidArray();
  if(gWorkList) {
    int i;
    for (i = 1; i < argc; i++) {
      nsString *tempString = new nsString;
      tempString->AssignWithConversion(argv[i]);
      gWorkList->AppendElement(tempString);
    }
  }

  static NS_DEFINE_CID(kCParserCID, NS_PARSER_CID);
  nsComponentManager::RegisterComponent(kCParserCID, NULL, NULL, PARSER_DLL, PR_FALSE, PR_FALSE);

  return DebugRobot(gWorkList, nsnull);
}

