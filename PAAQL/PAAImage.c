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

#include "PAAImage.h"

#include "paa2img.h"

static const size_t kComponentsPerPixel = 4;
static const size_t kBitsPerComponent = sizeof(unsigned char) * 8;

CGImageRef CreateCGImageFromPAA(const char* path) {
    Image image;
    int result = paa2img(path, &image);
    
    if (result > 0) {
        return NULL;
    }
    
    CFDataRef data = CFDataCreate(kCFAllocatorDefault, image.data, image.size);
    free(image.data);
    
    CGDataProviderRef dataProvider = CGDataProviderCreateWithCFData(data);
    CGColorSpaceRef rgb = CGColorSpaceCreateDeviceRGB();
    
    CGImageRef imageRef = CGImageCreate(image.width, image.height, kBitsPerComponent, kBitsPerComponent * kComponentsPerPixel, kComponentsPerPixel * image.width, rgb, kCGImageAlphaLast, dataProvider, NULL, false, kCGRenderingIntentDefault);
    
    CGColorSpaceRelease(rgb);
    CGDataProviderRelease(dataProvider);
    CFRelease(data);

    return imageRef;
}
