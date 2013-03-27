#ifdef __APPLE__
#include <CoreFoundation/CFBundle.h>
#include <CoreFoundation/CFString.h>
// function provides some Mac OS X specific source code to load files from the resources of the application bundle.
char * resPath(char **argv, char* name, char* type ) 
{
	static char resource[1024];
	CFURLRef cfBundleURL = CFBundleCopyResourceURL( CFBundleGetMainBundle(),    
	CFStringCreateWithCString(kCFAllocatorDefault,name, kCFStringEncodingISOLatin1), 
	CFStringCreateWithCString(kCFAllocatorDefault,type,kCFStringEncodingISOLatin1), 
	NULL);
	CFStringGetCString( CFURLCopyPath(cfBundleURL),
		resource,1023,kCFStringEncodingISOLatin1);
   return resource;
}
#pragma comment(lib, "libMacOSX.a")
#endif