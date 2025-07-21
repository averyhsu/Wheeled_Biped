#ifndef _ROS_SERVICE_ComputeInference_h
#define _ROS_SERVICE_ComputeInference_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace ai_utils_msgs
{

static const char COMPUTEINFERENCE[] = "ai_utils_msgs/ComputeInference";

  class ComputeInferenceRequest : public ros::Msg
  {
    public:
      typedef bool _start_type;
      _start_type start;

    ComputeInferenceRequest():
      start(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_start;
      u_start.real = this->start;
      *(outbuffer + offset + 0) = (u_start.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->start);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_start;
      u_start.base = 0;
      u_start.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->start = u_start.real;
      offset += sizeof(this->start);
     return offset;
    }

    virtual const char * getType() override { return COMPUTEINFERENCE; };
    virtual const char * getMD5() override { return "676aa7bfb3ec2071e814f2368dfd5fb5"; };

  };

  class ComputeInferenceResponse : public ros::Msg
  {
    public:

    ComputeInferenceResponse()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
     return offset;
    }

    virtual const char * getType() override { return COMPUTEINFERENCE; };
    virtual const char * getMD5() override { return "d41d8cd98f00b204e9800998ecf8427e"; };

  };

  class ComputeInference {
    public:
    typedef ComputeInferenceRequest Request;
    typedef ComputeInferenceResponse Response;
  };

}
#endif
