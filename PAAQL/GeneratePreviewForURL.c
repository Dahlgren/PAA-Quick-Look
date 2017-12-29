/*
 * Copyright (C) 2017 Björn Dahlgren
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <CoreFoundation/CoreFoundation.h>
#include <CoreServices/CoreServices.h>
#include <QuickLook/QuickLook.h>

#include "PAAImage.h"

OSStatus GeneratePreviewForURL(void *thisInterface, QLPreviewRequestRef preview, CFURLRef url, CFStringRef contentTypeUTI, CFDictionaryRef options);
void CancelPreviewGeneration(void *thisInterface, QLPreviewRequestRef preview);

/* -----------------------------------------------------------------------------
   Generate a preview for file

   This function's job is to create preview for designated file
   ----------------------------------------------------------------------------- */

OSStatus GeneratePreviewForURL(void *thisInterface, QLPreviewRequestRef preview, CFURLRef url, CFStringRef contentTypeUTI, CFDictionaryRef options)
{
    CFStringRef urlPath = CFURLCopyPath(url);
    const char* path = CFStringGetCStringPtr(urlPath,kCFStringEncodingUTF8);
    CFRelease(urlPath);
    
    if (path) {
        CGImageRef image = CreateCGImageFromPAA(path);
        
        if (!image) {
            return 1;
        }
        
        CGFloat width = CGImageGetWidth(image);
        CGFloat height = CGImageGetHeight(image);
        CGSize size = CGSizeMake(width, height);
        CGRect rect = CGRectMake(0,0, width, height);
        
        CGContextRef ctx = QLPreviewRequestCreateContext(preview, size, true, NULL);
        CGContextDrawImage(ctx, rect, image);
        QLPreviewRequestFlushContext(preview, ctx);
        CGContextRelease(ctx);
        CGImageRelease(image);
    }
    
    return noErr;
}

void CancelPreviewGeneration(void *thisInterface, QLPreviewRequestRef preview)
{
    // Implement only if supported
}
