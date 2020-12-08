//
// Created by jongsik on 20. 12. 2..
//

#ifndef POST_DATA_PROCESSING_CONFIG_H
#define POST_DATA_PROCESSING_CONFIG_H

#include <yaml-cpp/yaml.h>

struct Extrinsic
{
  float delX;
  float delY;
  float delZ;

  float delRoll;
  float delPitch;
  float delYaw;

  float minX;
  float maxX;

  std::string path;
};

class Config{
public:
  Config();

  float delX;
  float delY;
  float delZ;

  float delRoll;
  float delPitch;
  float delYaw;

  float minX;
  float maxX;

  std::string path;


  Extrinsic extrinsic;

  void ReadEveryParameter(YAML::Node yamlFile);
};

#endif //POST_DATA_PROCESSING_CONFIG_H
