//
// Created by dcr on 2022/6/19.
// This is intended to load all the input images
// also provide functions to delete certain image
//

#ifndef SFM_PROJECT_IMGLOADER_H
#define SFM_PROJECT_IMGLOADER_H
#include <iostream>
#include <vector>
#include <string>
#include <io.h>
#include <cstring>

#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"

namespace sfmProject{
class ImgLoader {
 public:
  ImgLoader(){};

  ~ImgLoader();

  bool LoadImages(const std::string &path);

  unsigned int image_number_{};

  std::vector<cv::Mat> images_;
};
}

#endif  // SFM_PROJECT_IMGLOADER_H
