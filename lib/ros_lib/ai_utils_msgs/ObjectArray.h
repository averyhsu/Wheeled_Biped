#ifndef _ROS_ai_utils_msgs_ObjectArray_h
#define _ROS_ai_utils_msgs_ObjectArray_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Header.h"
#include "ai_utils_msgs/Object.h"

namespace ai_utils_msgs
{

  class ObjectArray : public ros::Msg
  {
    public:
      typedef std_msgs::Header _header_type;
      _header_type header;
      uint32_t array_length;
      typedef ai_utils_msgs::Object _array_type;
      _array_type st_array;
      _array_type * array;

    ObjectArray():
      header(),
      array_length(0), st_array(), array(nullptr)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += this->header.serialize(outbuffer + offset);
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
      offset += this->header.deserialize(inbuffer + offset);
      uint32_t array_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      array_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      array_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      array_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->array_length);
      if(array_lengthT > array_length)
        this->array = (ai_utils_msgs::Object*)realloc(this->array, array_lengthT * sizeof(ai_utils_msgs::Object));
      array_length = array_lengthT;
      for( uint32_t i = 0; i < array_length; i++){
      offset += this->st_array.deserialize(inbuffer + offset);
        memcpy( &(this->array[i]), &(this->st_array), sizeof(ai_utils_msgs::Object));
      }
     return offset;
    }

    virtual const char * getType() override { return "ai_utils_msgs/ObjectArray"; };
    virtual const char * getMD5() override { return "2cf1828a504da30cc232588cfb50fde1"; };

  };

}
#endif
