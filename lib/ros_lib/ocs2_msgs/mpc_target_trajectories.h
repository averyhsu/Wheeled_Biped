#ifndef _ROS_ocs2_msgs_mpc_target_trajectories_h
#define _ROS_ocs2_msgs_mpc_target_trajectories_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ocs2_msgs/mpc_state.h"
#include "ocs2_msgs/mpc_input.h"

namespace ocs2_msgs
{

  class mpc_target_trajectories : public ros::Msg
  {
    public:
      uint32_t timeTrajectory_length;
      typedef float _timeTrajectory_type;
      _timeTrajectory_type st_timeTrajectory;
      _timeTrajectory_type * timeTrajectory;
      uint32_t stateTrajectory_length;
      typedef ocs2_msgs::mpc_state _stateTrajectory_type;
      _stateTrajectory_type st_stateTrajectory;
      _stateTrajectory_type * stateTrajectory;
      uint32_t inputTrajectory_length;
      typedef ocs2_msgs::mpc_input _inputTrajectory_type;
      _inputTrajectory_type st_inputTrajectory;
      _inputTrajectory_type * inputTrajectory;

    mpc_target_trajectories():
      timeTrajectory_length(0), st_timeTrajectory(), timeTrajectory(nullptr),
      stateTrajectory_length(0), st_stateTrajectory(), stateTrajectory(nullptr),
      inputTrajectory_length(0), st_inputTrajectory(), inputTrajectory(nullptr)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->timeTrajectory_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->timeTrajectory_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->timeTrajectory_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->timeTrajectory_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->timeTrajectory_length);
      for( uint32_t i = 0; i < timeTrajectory_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->timeTrajectory[i]);
      }
      *(outbuffer + offset + 0) = (this->stateTrajectory_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->stateTrajectory_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->stateTrajectory_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->stateTrajectory_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->stateTrajectory_length);
      for( uint32_t i = 0; i < stateTrajectory_length; i++){
      offset += this->stateTrajectory[i].serialize(outbuffer + offset);
      }
      *(outbuffer + offset + 0) = (this->inputTrajectory_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->inputTrajectory_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->inputTrajectory_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->inputTrajectory_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->inputTrajectory_length);
      for( uint32_t i = 0; i < inputTrajectory_length; i++){
      offset += this->inputTrajectory[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      uint32_t timeTrajectory_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      timeTrajectory_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      timeTrajectory_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      timeTrajectory_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->timeTrajectory_length);
      if(timeTrajectory_lengthT > timeTrajectory_length)
        this->timeTrajectory = (float*)realloc(this->timeTrajectory, timeTrajectory_lengthT * sizeof(float));
      timeTrajectory_length = timeTrajectory_lengthT;
      for( uint32_t i = 0; i < timeTrajectory_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_timeTrajectory));
        memcpy( &(this->timeTrajectory[i]), &(this->st_timeTrajectory), sizeof(float));
      }
      uint32_t stateTrajectory_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      stateTrajectory_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      stateTrajectory_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      stateTrajectory_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->stateTrajectory_length);
      if(stateTrajectory_lengthT > stateTrajectory_length)
        this->stateTrajectory = (ocs2_msgs::mpc_state*)realloc(this->stateTrajectory, stateTrajectory_lengthT * sizeof(ocs2_msgs::mpc_state));
      stateTrajectory_length = stateTrajectory_lengthT;
      for( uint32_t i = 0; i < stateTrajectory_length; i++){
      offset += this->st_stateTrajectory.deserialize(inbuffer + offset);
        memcpy( &(this->stateTrajectory[i]), &(this->st_stateTrajectory), sizeof(ocs2_msgs::mpc_state));
      }
      uint32_t inputTrajectory_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      inputTrajectory_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      inputTrajectory_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      inputTrajectory_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->inputTrajectory_length);
      if(inputTrajectory_lengthT > inputTrajectory_length)
        this->inputTrajectory = (ocs2_msgs::mpc_input*)realloc(this->inputTrajectory, inputTrajectory_lengthT * sizeof(ocs2_msgs::mpc_input));
      inputTrajectory_length = inputTrajectory_lengthT;
      for( uint32_t i = 0; i < inputTrajectory_length; i++){
      offset += this->st_inputTrajectory.deserialize(inbuffer + offset);
        memcpy( &(this->inputTrajectory[i]), &(this->st_inputTrajectory), sizeof(ocs2_msgs::mpc_input));
      }
     return offset;
    }

    virtual const char * getType() override { return "ocs2_msgs/mpc_target_trajectories"; };
    virtual const char * getMD5() override { return "2d8da69ddfcd018a998edad053f8c7b6"; };

  };

}
#endif
