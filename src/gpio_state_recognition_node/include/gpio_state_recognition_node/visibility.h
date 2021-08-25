// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef ROS2RASP_LECTURE_GPIOSTATERECOGNITIONNODE__VISIBILITY_H_
#define ROS2RASP_LECTURE_GPIOSTATERECOGNITIONNODE__VISIBILITY_H_

#ifdef __cplusplus
extern "C"
{
#endif

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__

  #ifdef __GNUC__
    #define ROS2RASP_LECTURE_GPIOSTATERECOGNITIONNODE_EXPORT __attribute__ ((dllexport))
    #define ROS2RASP_LECTURE_GPIOSTATERECOGNITIONNODE_IMPORT __attribute__ ((dllimport))
  #else
    #define ROS2RASP_LECTURE_GPIOSTATERECOGNITIONNODE_EXPORT __declspec(dllexport)
    #define ROS2RASP_LECTURE_GPIOSTATERECOGNITIONNODE_IMPORT __declspec(dllimport)
  #endif

  #ifdef ROS2RASP_LECTURE_GPIOSTATERECOGNITIONNODE_DLL
    #define ROS2RASP_LECTURE_GPIOSTATERECOGNITIONNODE_PUBLIC ROS2RASP_LECTURE_GPIOSTATERECOGNITIONNODE_EXPORT
  #else
    #define ROS2RASP_LECTURE_GPIOSTATERECOGNITIONNODE_PUBLIC ROS2RASP_LECTURE_GPIOSTATERECOGNITIONNODE_IMPORT
  #endif

  #define ROS2RASP_LECTURE_GPIOSTATERECOGNITIONNODE_PUBLIC_TYPE ROS2RASP_LECTURE_GPIOSTATERECOGNITIONNODE_PUBLIC

  #define ROS2RASP_LECTURE_GPIOSTATERECOGNITIONNODE_LOCAL

#else

  #define ROS2RASP_LECTURE_GPIOSTATERECOGNITIONNODE_EXPORT __attribute__ ((visibility("default")))
  #define ROS2RASP_LECTURE_GPIOSTATERECOGNITIONNODE_IMPORT

  #if __GNUC__ >= 4
    #define ROS2RASP_LECTURE_GPIOSTATERECOGNITIONNODE_PUBLIC __attribute__ ((visibility("default")))
    #define ROS2RASP_LECTURE_GPIOSTATERECOGNITIONNODE_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define ROS2RASP_LECTURE_GPIOSTATERECOGNITIONNODE_PUBLIC
    #define ROS2RASP_LECTURE_GPIOSTATERECOGNITIONNODE_LOCAL
  #endif

  #define ROS2RASP_LECTURE_GPIOSTATERECOGNITIONNODE_PUBLIC_TYPE
#endif

#ifdef __cplusplus
}
#endif

#endif  // ROS2RASP_LECTURE_GPIOSTATERECOGNITIONNODE__VISIBILITY_H_
