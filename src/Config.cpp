//
// Created by jongsik on 20. 12. 2..
//

//
// Created by jongsik on 20. 10. 28..
//

#include "Config.h"
#include <iostream>

Config::Config()
{
  YAML::Node yamlFile = YAML::LoadFile("/home/jongsik/indoor-mapping_ws/src/post_data_processing/param/default.yaml");
  ReadEveryParameter(yamlFile);
}


void Config::ReadEveryParameter(const YAML::Node yamlFile)
{
  YAML::Node extrinsicYaml = yamlFile["Extrinsic"];

  delX = extrinsicYaml["delX"].as<float>();
  delY = extrinsicYaml["delY"].as<float>();
  delZ = extrinsicYaml["delZ"].as<float>();

  delRoll = extrinsicYaml["delRoll"].as<float>();
  delPitch = extrinsicYaml["delPitch"].as<float>();
  delYaw = extrinsicYaml["delYaw"].as<float>();

  minX = extrinsicYaml["minX"].as<float>();
  maxX = extrinsicYaml["maxX"].as<float>();

  path = extrinsicYaml["path"].as<std::string>();
}