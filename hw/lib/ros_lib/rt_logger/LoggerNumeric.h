#ifndef _ROS_rt_logger_LoggerNumeric_h
#define _ROS_rt_logger_LoggerNumeric_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64MultiArray.h"

namespace rt_logger
{

  class LoggerNumeric : public ros::Msg
  {
    public:
      typedef std_msgs::String _name_type;
      _name_type name;
      typedef std_msgs::Float64MultiArray _array_type;
      _array_type array;

    LoggerNumeric():
      name(),
      array()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->name.serialize(outbuffer + offset);
      offset += this->array.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += this->name.deserialize(inbuffer + offset);
      offset += this->array.deserialize(inbuffer + offset);
     return offset;
    }

    virtual const char * getType() override { return "rt_logger/LoggerNumeric"; };
    virtual const char * getMD5() override { return "f23b3225a6fd33f53df40404120a5f86"; };

  };

}
#endif
