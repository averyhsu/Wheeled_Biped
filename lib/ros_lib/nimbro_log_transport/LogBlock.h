#ifndef _ROS_nimbro_log_transport_LogBlock_h
#define _ROS_nimbro_log_transport_LogBlock_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "nimbro_log_transport/LogMsg.h"

namespace nimbro_log_transport
{

  class LogBlock : public ros::Msg
  {
    public:
      typedef uint64_t _key_type;
      _key_type key;
      uint32_t msgs_length;
      typedef nimbro_log_transport::LogMsg _msgs_type;
      _msgs_type st_msgs;
      _msgs_type * msgs;

    LogBlock():
      key(0),
      msgs_length(0), st_msgs(), msgs(nullptr)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->key >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->key >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->key >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->key >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (this->key >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (this->key >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (this->key >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (this->key >> (8 * 7)) & 0xFF;
      offset += sizeof(this->key);
      *(outbuffer + offset + 0) = (this->msgs_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->msgs_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->msgs_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->msgs_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->msgs_length);
      for( uint32_t i = 0; i < msgs_length; i++){
      offset += this->msgs[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      this->key =  ((uint64_t) (*(inbuffer + offset)));
      this->key |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->key |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->key |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->key |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      this->key |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      this->key |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      this->key |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      offset += sizeof(this->key);
      uint32_t msgs_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      msgs_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      msgs_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      msgs_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->msgs_length);
      if(msgs_lengthT > msgs_length)
        this->msgs = (nimbro_log_transport::LogMsg*)realloc(this->msgs, msgs_lengthT * sizeof(nimbro_log_transport::LogMsg));
      msgs_length = msgs_lengthT;
      for( uint32_t i = 0; i < msgs_length; i++){
      offset += this->st_msgs.deserialize(inbuffer + offset);
        memcpy( &(this->msgs[i]), &(this->st_msgs), sizeof(nimbro_log_transport::LogMsg));
      }
     return offset;
    }

    virtual const char * getType() override { return "nimbro_log_transport/LogBlock"; };
    virtual const char * getMD5() override { return "cbc45b9d793ed6ba153682121adafa6b"; };

  };

}
#endif
