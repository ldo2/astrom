#ifndef __SamplesMatrix_HPP__
#define __SamplesMatrix_HPP__

#include <stdexcept>
#include <iostream>

  template <typename ContentType>
  class SamplesMatrix {
    public:
      typedef ContentType Sample;

      int width, height;
      Sample *data;

      class Row {
        public:
        SamplesMatrix *matrix;
        Sample *row;

        Row() : matrix(0), row(0) {}
        Row(SamplesMatrix *matrix, Sample *row) 
         : matrix(matrix), row(row) {}

        Sample &operator [](int index) {
          if (index < 0 || index >= matrix->width) {
            std::cerr << "SamplesMatrix::Row: index out of bounds " << index << std::endl << std::flush;
            throw std::runtime_error("SamplesMatrix::Row: index out of bounds");
          }
          return row[index];
        }
      } *rows;
      
      SamplesMatrix(int width, int height)
        : width(width), height(height) {
        data = new Sample [width * height];
        rows = new Row [height];

        for (int i = 0; i < height; ++i) {
          rows[i].matrix = this;
          rows[i].row = data + i * width;
        }
      }

      ~SamplesMatrix() {
        delete[] data; 
        delete[] rows; 
      }

      Sample &sample(int row, int column) {
        if (row < 0 || row >= height) {
          throw std::runtime_error("SamplesMatrix: index out of bounds");
        }
        return rows[row][column];
      }

      Row &operator [](int index) {
        if (index < 0 || index >= height) {
          throw std::runtime_error("SamplesMatrix: index out of bounds");
        }
        return rows[index];
      }
  };

#endif /* __SamplesMatrix_HPP__ */

