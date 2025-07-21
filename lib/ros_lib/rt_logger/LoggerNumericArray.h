#ifndef _ROS_rt_logger_LoggerNumericArray_h
#define _ROS_rt_logger_LoggerNumericArray_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Time.h"
#include "rt_logger/LoggerNumeric.h"

namespace rt_logger
{

  class LoggerNumericArray : public ros::Msg
  {
    public:
      typedef std_msgs::Time _time_type;
      _time_type time;
      uint32_t array_length;
      typedef rt_logger::LoggerNumeric _array_type;
      _array_type st_array;
      _array_type * array;

    LoggerNumericArray():
      time(),
      array_length(0), st_array(), array(nullptr)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->time.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->array_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->array_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->array_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->array_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->array_length);
      for( uint32_t i = 0; i < array_length; i++){
      offset += this->array[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += this->time.deserialize(inbuffer + offset);
      uint32_t array_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      array_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      array_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      array_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->array_length);
      if(array_lengthT > array_length)
        this->array = (rt_logger::LoggerNumeric*)realloc(this->array, array_lengthT * sizeof(rt_logger::LoggerNumeric));
      array_length = array_lengthT;
      for( uint32_t i = 0; i < array_length; i++){
      offset += this->st_array.deserialize(inbuffer + offset);
        memcpy( &(this->array[i]), &(this->st_array), sizeof(rt_logger::LoggerNumeric));
      }
     return offset;
    }

    virtual const char * getType() override { return "rt_logger/LoggerNumericArray"; };
    virtual const char * getMD5() override { return "b85aac77b4d19409ef377444a6069ae1"; };

  };

}
#endif
