/*!
 * Canvas class implementation.
 * @file canvas.cpp
 */

#include "canvas.h"

namespace life {

  /*!
  * Default constructor.
  */
  Canvas::Canvas(size_t w, size_t h, int bs)
    : m_width(w), m_height(h), m_r_width(w * bs), m_r_height(h * bs), m_block_size(bs) {
    m_pixels.resize(m_r_width * m_r_height * image_depth, 0);
  }

  /*!
  * Default destructor.
  */
  Canvas::~Canvas() { /*empty*/ }

  /*!
  * Deep copy of the canvas.
  * @param clone The object we are copying from.
  */
  Canvas::Canvas(const Canvas& clone)
  : m_width(clone.m_width), m_height(clone.m_height),
    m_r_width(clone.m_r_width), m_r_height(clone.m_r_height),
    m_block_size(clone.m_block_size), m_pixels(clone.m_pixels) {}

  /*!
  * @param source The object we are copying information from.
  * @return A reference to the `this` object.
  */
  Canvas& Canvas::operator=(const Canvas& source) {
    if (this != &source) {
      m_width = source.m_width;
      m_height = source.m_height;
      m_r_width = source.m_r_width;
      m_r_height = source.m_r_height;
      m_block_size = source.m_block_size;
      m_pixels = source.m_pixels;
    }
    return *this;
  }

  /*!
  * @param color The color of pixels.
  */
  void Canvas::clear(const Color& color) {

    /// Reset all pixel of image with the informed color.
    for (size_t i = 0; i < m_pixels.size(); i += image_depth) {
      m_pixels[i] = color.channels[Color::R];
      m_pixels[i + 1] = color.channels[Color::G];
      m_pixels[i + 2] = color.channels[Color::B];
      m_pixels[i + 3] = 255;
    }
  }

    /*!
  * @throw `std::invalid_argument()` it the pixel coordinate is located outside the canvas.
  * @param x The (virtual) X coordinate of the pixel we want to know the color of.
  * @param y The (virtual) Y coordinate of the pixel we want to know the color of.
  * @return The pixel color.
  */
  Color Canvas::pixel(coord_t x, coord_t y) const {
      
    /// Check if coords is valids.
    if (x >= m_width || y >= m_height) {
      throw std::invalid_argument("Pixel coordinate is outside the canvas.");
    }

    size_t index = ((y * m_r_width) + x) * image_depth; //!<- Pixel index in the array based on coordinates.

    Color pixel_color;
    pixel_color.channels[Color::R] = m_pixels[index];
    pixel_color.channels[Color::G] = m_pixels[index + 1];
    pixel_color.channels[Color::B] = m_pixels[index + 2];

    return pixel_color;
  }

  /*!
  * Draw a pixel on the virtual image at the requested coordinate.
  *
  * @note Nothing is done if the  pixel coordinate is located outside the canvas.
  * @param x The (virtual) X coordinate of the pixel we want to draw.
  * @param y The (virtual) Y coordinate of the pixel we want to draw.
  * @param color The color.
  */
  void Canvas::pixel(coord_t x, coord_t y, const Color& color) {

    /// Check if coords is valids.
    if (x >= m_width || y >= m_height) {
      throw std::invalid_argument("Pixel coordinate is outside the canvas.");
    }

    size_t start_x = x * m_block_size;  //!<- X coordinate converted to the new size.
    size_t start_y = y * m_block_size;  //!<- Y coordinate converted to the new size.

    for (short i = 0; i < m_block_size; ++i) {
      for (short j = 0; j < m_block_size; ++j) {
        size_t index = (((start_y + i) * m_r_width) + (start_x + j)) * image_depth;   //!<- Initial index of each pixel.
        
        m_pixels[index] = color.channels[Color::R];
        m_pixels[index + 1] = color.channels[Color::G];
        m_pixels[index + 2] = color.channels[Color::B];
        m_pixels[index + 3] = 255;
      }
    }
  }
}  // namespace life

//================================[ canvas.cpp ]================================//