/*! \brief Bitmap
 *
 * Implementation of a component
 *
 * File:   Bitmap.cpp
 * Author: Dieter Steuten
 *
 */

/* --- Includes --- */
#include "Bitmap.hpp"

#include <algorithm>
#include <iostream>

/* --- CPP regular --- */
Bitmap::Bitmap() {}
Bitmap::~Bitmap() {}

/* --- protected functionalities --- */
bool Bitmap::P(bool lauf) {
    return (inner.eingabeWechsel && lauf);
    /*if (inner.eingabeWechsel && lauf) {
        return true;
    } else {
        return false;
    }*/
}

const T_Bitmap &Bitmap::O() {
/*    std::vector<positionABS> onlyone;
    onlyone.reserve(inner.data.size() / 3);
    auto iter = inner.data.begin() + inner.color_chanel;

    for (iter = inner.data.begin() + inner.color_chanel; iter < inner.data.end(); iter += 3) {
        onlyone.push_back(*iter);
    }
    inner.data = onlyone;
    //   std::reverse(inner.data.begin(), inner.data.end());
    //   std::rotate(inner.data.begin(), inner.data.begin() + inner.data.size()/3, inner.data.end());
*/
    return inner;
}

void Bitmap::I(const T_Bitmap &irgendwas) {
    if (inner != irgendwas) {
        std::vector<uint8_t> pre_data;

        inner.eingabeWechsel = true;
        inner.bmp_filename = irgendwas.bmp_filename;

        std::ifstream inp;  //{inner.bmp_filename, std::ios_base::binary};
        inp.open(inner.bmp_filename);
        if (inp) {
            inp.read((char *)&file_header, sizeof(file_header));
            if (file_header.file_type != 0x4D42) {
                throw std::runtime_error("Error! Unrecognized file format.");
            }
            inp.read((char *)&bmp_info_header, sizeof(bmp_info_header));

            // The BMPColorHeader is used only for transparent images
            if (bmp_info_header.bit_count == 32) {
                // Check if the file has bit mask color information
                if (bmp_info_header.size >= (sizeof(BMPInfoHeader) + sizeof(BMPColorHeader))) {
                    inp.read((char *)&bmp_color_header, sizeof(bmp_color_header));
                    // Check if the pixel data is stored as BGRA and if the color space type is sRGB
                    check_color_header(bmp_color_header);
                } else {
                    std::cerr << "Warning! The file \"" << irgendwas.bmp_filename << "\" does not seem to contain bit mask information\n";
                    throw std::runtime_error("Error! Unrecognized file format.");
                }
            }

            // Jump to the pixel data location
            inp.seekg(file_header.offset_data, inp.beg);

            // Adjust the header fields for output.
            // Some editors will put extra info in the image file, we only save the headers and the data.
            if (bmp_info_header.bit_count == 32) {
                bmp_info_header.size = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
                file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
            } else {
                bmp_info_header.size = sizeof(BMPInfoHeader);
                file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
            }
            file_header.file_size = file_header.offset_data;

            if (bmp_info_header.height < 0) {
                throw std::runtime_error("The program can treat only BMP images with the origin in the bottom left corner!");
            }

            pre_data.resize(bmp_info_header.width * bmp_info_header.height * bmp_info_header.bit_count / 8);
            inner.collumn = bmp_info_header.width;
            inner.row = bmp_info_header.height;
            inner.bitcount = bmp_info_header.bit_count / 8;
            // Here we check if we need to take into account row padding
            if (bmp_info_header.width % 4 == 0) {
                inp.read((char *)pre_data.data(), pre_data.size());
                file_header.file_size += pre_data.size();
            } else {
                row_stride = bmp_info_header.width * bmp_info_header.bit_count / 8;
                uint32_t new_stride = make_stride_aligned(4);
                std::vector<uint8_t> padding_row(new_stride - row_stride);

                for (int y = 0; y < bmp_info_header.height; ++y) {
                    inp.read((char *)(pre_data.data() + row_stride * y), row_stride);
                    inp.read((char *)padding_row.data(), padding_row.size());
                }
                file_header.file_size += pre_data.size() + bmp_info_header.height * padding_row.size();
            }

            auto iter = pre_data.begin();
            int x = 0;
            int y = bmp_info_header.height; int poos =0;
            while (iter != pre_data.end()) {
                if ((*iter) < 255) {
                    inner.data.push_back({x, y});
                }
                x = poos % (bmp_info_header.width);// * bmp_info_header.bit_count / 8);
                if(x==0){y--;}
                iter+=( 3);
                poos++;
            }
        } else {
            inner.eingabeWechsel = false;
            throw std::runtime_error("Unable to open the input image file.");
        }
    }
}

void Bitmap::check_color_header(BMPColorHeader &bmp_color_header) {
    BMPColorHeader expected_color_header;
    if (expected_color_header.red_mask != bmp_color_header.red_mask ||
        expected_color_header.blue_mask != bmp_color_header.blue_mask ||
        expected_color_header.green_mask != bmp_color_header.green_mask ||
        expected_color_header.alpha_mask != bmp_color_header.alpha_mask) {
        throw std::runtime_error("Unexpected color mask format! The program expects the pixel data to be in the BGRA format");
    }
    if (expected_color_header.color_space_type != bmp_color_header.color_space_type) {
        throw std::runtime_error("Unexpected color space type! The program expects sRGB values");
    }
}

uint32_t Bitmap::make_stride_aligned(uint32_t align_stride) {
    uint32_t new_stride = row_stride;
    while (new_stride % align_stride != 0) {
        new_stride++;
    }
    return new_stride;
}