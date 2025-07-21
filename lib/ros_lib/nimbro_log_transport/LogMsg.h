#ifndef _ROS_nimbro_log_transport_LogMsg_h
#define _ROS_nimbro_log_transport_LogMsg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "rosgraph_msgs/Log.h"

namespace nimbro_log_transport
{

  class LogMsg : public ros::Msg
  {
    public:
      typedef uint32_t _id_type;
      _id_type id;
      typedef rosgraph_msgs::Log _msg_type;
      _msg_type msg;

    LogMsg():
      id(0),
      msg()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->id >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->id >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->id >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->id >> (8 * 3)) & 0xFF;
      offset += sizeof(this->id);
      offset += this->msg.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      this->id =  ((uint32_t) (*(inbuffer + offset)));
      this->id |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->id |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->id |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->id);
      offset += this->msg.deserialize(inbuffer + offset);
     return offset;
    }

    virtual const char * getType() override { return "nimbro_log_transport/LogMsg"; };
    virtual const char * getMD5() override { return "3bf1aa4ee5ce30014f8de11446314219"; };

  };

}
#endif
