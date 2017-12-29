/*
 * Copyright (C)  2016  Felix "KoffeinFlummi" Wiegand
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

#pragma once


#define DXT1     0xFF01
#define DXT3     0xFF03
#define DXT5     0xFF05
#define ARGB4444 0x4444
#define ARGB1555 0x1555
#define AI88     0x8080

#define COMP_NONE 0
#define COMP_LZSS 1
#define COMP_LZO  2


typedef struct PAAImage {
    uint16_t width;
    uint16_t height;
    size_t size;
    unsigned char *data;
} Image;

int dxt12img(unsigned char *input, unsigned char *output, int width, int height);

int dxt52img(unsigned char *input, unsigned char *output, int width, int height);

int paa2img(char *source, Image *output);
