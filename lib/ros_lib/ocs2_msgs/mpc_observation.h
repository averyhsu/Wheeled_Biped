#ifndef _ROS_ocs2_msgs_mpc_observation_h
#define _ROS_ocs2_msgs_mpc_observation_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ocs2_msgs/mpc_state.h"
#include "ocs2_msgs/mpc_input.h"

namespace ocs2_msgs
{

  class mpc_observation : public ros::Msg
  {
    public:
      typedef float _time_type;
      _time_type time;
      typedef ocs2_msgs::mpc_state _state_type;
      _state_type state;
      typedef ocs2_msgs::mpc_input _input_type;
      _input_type input;
      typedef int8_t _mode_type;
      _mode_type mode;

    mpc_observation():
      time(0),
      state(),
      input(),
      mode(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->time);
      offset += this->state.serialize(outbuffer + offset);
      offset += this->input.serialize(outbuffer + offset);
      union {
        int8_t real;
        uint8_t base;
      } u_mode;
      u_mode.real = this->mode;
      *(outbuffer + offset + 0) = (u_mode.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->mode);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->time));
      offset += this->state.deserialize(inbuffer + offset);
      offset += this->input.deserialize(inbuffer + offset);
      union {
        int8_t real;
        uint8_t base;
      } u_mode;
      u_mode.base = 0;
      u_mode.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->mode = u_mode.real;
      offset += sizeof(this->mode);
     return offset;
    }

    virtual const char * getType() override { return "ocs2_msgs/mpc_observation"; };
    virtual const char * getMD5() override { return "c4075a25799f2a89c6d62b26e93cb66f"; };

  };

}
#endif
