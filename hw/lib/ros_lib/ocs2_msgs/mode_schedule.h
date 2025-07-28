#ifndef _ROS_ocs2_msgs_mode_schedule_h
#define _ROS_ocs2_msgs_mode_schedule_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace ocs2_msgs
{

  class mode_schedule : public ros::Msg
  {
    public:
      uint32_t eventTimes_length;
      typedef float _eventTimes_type;
      _eventTimes_type st_eventTimes;
      _eventTimes_type * eventTimes;
      uint32_t modeSequence_length;
      typedef int8_t _modeSequence_type;
      _modeSequence_type st_modeSequence;
      _modeSequence_type * modeSequence;

    mode_schedule():
      eventTimes_length(0), st_eventTimes(), eventTimes(nullptr),
      modeSequence_length(0), st_modeSequence(), modeSequence(nullptr)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->eventTimes_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->eventTimes_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->eventTimes_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->eventTimes_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->eventTimes_length);
      for( uint32_t i = 0; i < eventTimes_length; i++){
      offset += serializeAvrFloat64(outbuffer + offset, this->eventTimes[i]);
      }
      *(outbuffer + offset + 0) = (this->modeSequence_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->modeSequence_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->modeSequence_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->modeSequence_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->modeSequence_length);
      for( uint32_t i = 0; i < modeSequence_length; i++){
      union {
        int8_t real;
        uint8_t base;
      } u_modeSequencei;
      u_modeSequencei.real = this->modeSequence[i];
      *(outbuffer + offset + 0) = (u_modeSequencei.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->modeSequence[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      uint32_t eventTimes_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      eventTimes_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      eventTimes_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      eventTimes_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->eventTimes_length);
      if(eventTimes_lengthT > eventTimes_length)
        this->eventTimes = (float*)realloc(this->eventTimes, eventTimes_lengthT * sizeof(float));
      eventTimes_length = eventTimes_lengthT;
      for( uint32_t i = 0; i < eventTimes_length; i++){
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->st_eventTimes));
        memcpy( &(this->eventTimes[i]), &(this->st_eventTimes), sizeof(float));
      }
      uint32_t modeSequence_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      modeSequence_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      modeSequence_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      modeSequence_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->modeSequence_length);
      if(modeSequence_lengthT > modeSequence_length)
        this->modeSequence = (int8_t*)realloc(this->modeSequence, modeSequence_lengthT * sizeof(int8_t));
      modeSequence_length = modeSequence_lengthT;
      for( uint32_t i = 0; i < modeSequence_length; i++){
      union {
        int8_t real;
        uint8_t base;
      } u_st_modeSequence;
      u_st_modeSequence.base = 0;
      u_st_modeSequence.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->st_modeSequence = u_st_modeSequence.real;
      offset += sizeof(this->st_modeSequence);
        memcpy( &(this->modeSequence[i]), &(this->st_modeSequence), sizeof(int8_t));
      }
     return offset;
    }

    virtual const char * getType() override { return "ocs2_msgs/mode_schedule"; };
    virtual const char * getMD5() override { return "9aa75d28b36c292b797e36e87614038a"; };

  };

}
#endif
