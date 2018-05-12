#ifndef IMAGE_H
#define IMAGE_H

extern bool ios_convertToPNG(const wchar_t* cFilename, uint8_t* data, u32 size);
extern bool convertToPNG(const wchar_t* cFilename, uint8_t* data, u32 size);

#endif
