//
// Created by dcr on 2022/6/19.
//

#include "img_loader.h"

namespace sfmProject {
ImgLoader::~ImgLoader() = default;

bool ImgLoader::LoadImages(const std::string &path) {
  /** windows edition **/

  intptr_t file_handle = 0;
  _finddata32_t file_info{};
  cv::Mat temp_image;
  char *file_path = new char[path.length() + 1];

  strcpy_s(file_path, path.length() + 1, path.c_str());
  std::string target_file(path, 0, path.length() - 5);
  file_handle = _findfirst32(file_path, &file_info);

  if (file_handle == -1) {
    std::cerr << "error occurred unable to find the target file" << std::endl;
    return false;
  } else {
    temp_image = cv::imread(target_file + file_info.name);
    images_.push_back(temp_image);
  }
  _findclose(file_handle);
  this->image_number_ = images_.size();
  return true;

  /** Linux edition This is still incomplete **/
  /*DIR *pDir;
  struct dirent *ptr;

  if (!(pDir = opendir(location.c_str()))) {
    std::cerr << "the root is " << location << std::endl;
    std::cerr << "can not get the file ptr , check the dir location";
    return false;
  }

  while ((ptr = readdir(pDir)) != nullptr) {
    // 这里我理解他的指针应该是自动会指向到下一个文件，所以不用写指针的移动
    std::string sub_file =
        location + "/" + ptr->d_name;  // 当前指针指向的文件名
    if (ptr->d_type != 8 &&
        ptr->d_type !=
            4) {  // 递归出口，当不是普通文件（8）和文件夹（4）时退出递归
      return;
    }
    cv::Mat temp;

    // 普通文件直接加入到files
    if (ptr->d_type == 8) {
      // 相当于将命令下使用ls展示出来的文件中除了. 和 ..全部保存在files中
      // 当然下面可以写各种字符串的筛选逻辑，比如只要后缀有.jpg图片
      if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0) {
        if (strstr(ptr->d_name, ".png")) {
          temp = cv::imread(location + ptr->d_name);
          orb->detect(temp, temp_key_points);
          if (temp_key_points.size() >= 8) {
            std::cout << ptr->d_name << " ";
            images.push_back(temp);
            key_points.push_back(temp_key_points);
            orb->compute(images[images.size() - 1],
                         key_points[key_points.size() - 1], temp_descriptors);
            descriptors_.push_back(temp_descriptors);
          }
        }
      }
    }
  }
  begin_image = images[0].clone();
  orb->detect(begin_image, begin_image_key_points);
  orb->compute(begin_image, begin_image_key_points, begin_image_descriptors);
  std::cout << std::endl;
  image_number = images.size();
  key_points.resize(image_number);
  descriptors_.resize(image_number);
  matches_.resize(image_number);
  good_matches.resize(image_number);
  std::cout << "have successfully read " << images.size() << " images"
            << std::endl;
  // 关闭根目录
  std::cout << "test: " << images[0].size << std::endl;
  closedir(pDir);*/
}

}  // namespace sfmProject