#ifndef _ROS_nimbro_topic_transport_CompressedMsg_h
#define _ROS_nimbro_topic_transport_CompressedMsg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace nimbro_topic_transport
{

  class CompressedMsg : public ros::Msg
  {
    public:
      typedef const char* _type_type;
      _type_type type;
      typedef uint32_t _flags_type;
      _flags_type flags;
      uint32_t md5[4];
      uint32_t data_length;
      typedef uint8_t _data_type;
      _data_type st_data;
      _data_type * data;

    CompressedMsg():
      type(""),
      flags(0),
      md5(),
      data_length(0), st_data(), data(nullptr)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      uint32_t length_type = strlen(this->type);
      varToArr(outbuffer + offset, length_type);
      offset += 4;
      memcpy(outbuffer + offset, this->type, length_type);
      offset += length_type;
      *(outbuffer + offset + 0) = (this->flags >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->flags >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->flags >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->flags >> (8 * 3)) & 0xFF;
      offset += sizeof(this->flags);
      for( uint32_t i = 0; i < 4; i++){
      *(outbuffer + offset + 0) = (this->md5[i] >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->md5[i] >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->md5[i] >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->md5[i] >> (8 * 3)) & 0xFF;
      offset += sizeof(this->md5[i]);
      }
      *(outbuffer + offset + 0) = (this->data_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->data_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->data_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->data_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->data_length);
      for( uint32_t i = 0; i < data_length; i++){
      *(outbuffer + offset + 0) = (this->data[i] >> (8 * 0)) & 0xFF;
      offset += sizeof(this->data[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      uint32_t length_type;
      arrToVar(length_type, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_type; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_type-1]=0;
      this->type = (char *)(inbuffer + offset-1);
      offset += length_type;
      this->flags =  ((uint32_t) (*(inbuffer + offset)));
      this->flags |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->flags |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->flags |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->flags);
      for( uint32_t i = 0; i < 4; i++){
      this->md5[i] =  ((uint32_t) (*(inbuffer + offset)));
      this->md5[i] |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->md5[i] |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->md5[i] |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->md5[i]);
      }
      uint32_t data_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      data_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      data_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      data_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->data_length);
      if(data_lengthT > data_length)
        this->data = (uint8_t*)realloc(this->data, data_lengthT * sizeof(uint8_t));
      data_length = data_lengthT;
      for( uint32_t i = 0; i < data_length; i++){
      this->st_data =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->st_data);
        memcpy( &(this->data[i]), &(this->st_data), sizeof(uint8_t));
      }
     return offset;
    }

    virtual const char * getType() override { return "nimbro_topic_transport/CompressedMsg"; };
    virtual const char * getMD5() override { return "4027f3e662023a280cf442508fa56b96"; };

  };

}
#endif
