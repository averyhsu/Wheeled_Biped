#ifndef _ROS_SERVICE_reset_h
#define _ROS_SERVICE_reset_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ocs2_msgs/mpc_target_trajectories.h"

namespace ocs2_msgs
{

static const char RESET[] = "ocs2_msgs/reset";

  class resetRequest : public ros::Msg
  {
    public:
      typedef bool _reset_type;
      _reset_type reset;
      typedef ocs2_msgs::mpc_target_trajectories _targetTrajectories_type;
      _targetTrajectories_type targetTrajectories;

    resetRequest():
      reset(0),
      targetTrajectories()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_reset;
      u_reset.real = this->reset;
      *(outbuffer + offset + 0) = (u_reset.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->reset);
      offset += this->targetTrajectories.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_reset;
      u_reset.base = 0;
      u_reset.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->reset = u_reset.real;
      offset += sizeof(this->reset);
      offset += this->targetTrajectories.deserialize(inbuffer + offset);
     return offset;
    }

    virtual const char * getType() override { return RESET; };
    virtual const char * getMD5() override { return "7759e1cea687346062f2674a13fe14ee"; };

  };

  class resetResponse : public ros::Msg
  {
    public:
      typedef bool _done_type;
      _done_type done;

    resetResponse():
      done(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_done;
      u_done.real = this->done;
      *(outbuffer + offset + 0) = (u_done.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->done);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_done;
      u_done.base = 0;
      u_done.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->done = u_done.real;
      offset += sizeof(this->done);
     return offset;
    }

    virtual const char * getType() override { return RESET; };
    virtual const char * getMD5() override { return "89bb254424e4cffedbf494e7b0ddbfea"; };

  };

  class reset {
    public:
    typedef resetRequest Request;
    typedef resetResponse Response;
  };

}
#endif
