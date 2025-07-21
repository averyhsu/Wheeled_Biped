#ifndef _ROS_ocs2_msgs_mpc_flattened_controller_h
#define _ROS_ocs2_msgs_mpc_flattened_controller_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "ocs2_msgs/mpc_observation.h"
#include "ocs2_msgs/mpc_target_trajectories.h"
#include "ocs2_msgs/mpc_state.h"
#include "ocs2_msgs/mpc_input.h"
#include "ocs2_msgs/mode_schedule.h"
#include "ocs2_msgs/controller_data.h"
#include "ocs2_msgs/mpc_performance_indices.h"

namespace ocs2_msgs
{

  class mpc_flattened_controller : public ros::Msg
  {
    public:
      typedef uint8_t _controllerType_type;
      _controllerType_type controllerType;
      typedef ocs2_msgs::mpc_observation _initObservation_type;
      _initObservation_type initObservation;
      typedef ocs2_msgs::mpc_target_trajectories _planTargetTrajectories_type;
      _planTargetTrajectories_type planTargetTrajectories;
      uint32_t stateTrajectory_length;
      typedef ocs2_msgs::mpc_state _stateTrajectory_type;
      _stateTrajectory_type st_stateTrajectory;
      _stateTrajectory_type * stateTrajectory;
      uint32_t inputTrajectory_length;
      typedef ocs2_msgs::mpc_input _inputTrajectory_type;
      _inputTrajectory_type st_inputTrajectory;
      _inputTrajectory_type * inputTrajectory;
      uint32_t timeTrajectory_length;
      typedef float _timeTrajectory_type;
      _timeTrajectory_type st_timeTrajectory;
      _timeTrajectory_type * timeTrajectory;
      uint32_t postEventIndices_length;
      typedef uint16_t _postEventIndices_type;
      _postEventIndices_type st_postEventIndices;
      _postEventIndices_type * postEventIndices;
      typedef ocs2_msgs::mode_schedule _modeSchedule_type;
      _modeSchedule_type modeSchedule;
      uint32_t data_length;
      typedef ocs2_msgs::controller_data _data_type;
      _data_type st_data;
      _data_type * data;
      typedef ocs2_msgs::mpc_performance_indices _performanceIndices_type;
      _performanceIndices_type performanceIndices;
      enum { CONTROLLER_UNKNOWN = 0  };
      enum { CONTROLLER_FEEDFORWARD = 1 };
      enum { CONTROLLER_LINEAR = 2 };

    mpc_flattened_controller():
      controllerType(0),
      initObservation(),
      planTargetTrajectories(),
      stateTrajectory_length(0), st_stateTrajectory(), stateTrajectory(nullptr),
      inputTrajectory_length(0), st_inputTrajectory(), inputTrajectory(nullptr),
      timeTrajectory_length(0), st_timeTrajectory(), timeTrajectory(nullptr),
      postEventIndices_length(0), st_postEventIndices(), postEventIndices(nullptr),
      modeSchedule(),
      data_length(0), st_data(), data(nullptr),
      performanceIndices()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->controllerType >> (8 * 0)) & 0xFF;
      offset += sizeof(this->controllerType);
      offset += this->initObservation.serialize(outbuffer + offset);
      offset += this->planTargetTrajectories.serialize(outbuffer + offset);
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
      *(outbuffer + offset + 0) = (this->timeTrajectory_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->timeTrajectory_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->timeTrajectory_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->timeTrajectory_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->timeTrajectory_length);
      for( uint32_t i = 0; i < timeTrajectory_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->timeTrajectory[i]);
      }
      *(outbuffer + offset + 0) = (this->postEventIndices_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->postEventIndices_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->postEventIndices_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->postEventIndices_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->postEventIndices_length);
      for( uint32_t i = 0; i < postEventIndices_length; i++){
      *(outbuffer + offset + 0) = (this->postEventIndices[i] >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->postEventIndices[i] >> (8 * 1)) & 0xFF;
      offset += sizeof(this->postEventIndices[i]);
      }
      offset += this->modeSchedule.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->data_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->data_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->data_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->data_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->data_length);
      for( uint32_t i = 0; i < data_length; i++){
      offset += this->data[i].serialize(outbuffer + offset);
      }
      offset += this->performanceIndices.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      this->controllerType =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->controllerType);
      offset += this->initObservation.deserialize(inbuffer + offset);
      offset += this->planTargetTrajectories.deserialize(inbuffer + offset);
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
      uint32_t postEventIndices_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      postEventIndices_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      postEventIndices_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      postEventIndices_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->postEventIndices_length);
      if(postEventIndices_lengthT > postEventIndices_length)
        this->postEventIndices = (uint16_t*)realloc(this->postEventIndices, postEventIndices_lengthT * sizeof(uint16_t));
      postEventIndices_length = postEventIndices_lengthT;
      for( uint32_t i = 0; i < postEventIndices_length; i++){
      this->st_postEventIndices =  ((uint16_t) (*(inbuffer + offset)));
      this->st_postEventIndices |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->st_postEventIndices);
        memcpy( &(this->postEventIndices[i]), &(this->st_postEventIndices), sizeof(uint16_t));
      }
      offset += this->modeSchedule.deserialize(inbuffer + offset);
      uint32_t data_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      data_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      data_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      data_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->data_length);
      if(data_lengthT > data_length)
        this->data = (ocs2_msgs::controller_data*)realloc(this->data, data_lengthT * sizeof(ocs2_msgs::controller_data));
      data_length = data_lengthT;
      for( uint32_t i = 0; i < data_length; i++){
      offset += this->st_data.deserialize(inbuffer + offset);
        memcpy( &(this->data[i]), &(this->st_data), sizeof(ocs2_msgs::controller_data));
      }
      offset += this->performanceIndices.deserialize(inbuffer + offset);
     return offset;
    }

    virtual const char * getType() override { return "ocs2_msgs/mpc_flattened_controller"; };
    virtual const char * getMD5() override { return "9355aadb2928f436a41799dd737c0f53"; };

  };

}
#endif
