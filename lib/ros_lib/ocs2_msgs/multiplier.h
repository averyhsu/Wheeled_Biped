#ifndef _ROS_ocs2_msgs_multiplier_h
#define _ROS_ocs2_msgs_multiplier_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace ocs2_msgs
{

  class multiplier : public ros::Msg
  {
    public:
      typedef float _time_type;
      _time_type time;
      typedef float _penalty_type;
      _penalty_type penalty;
      uint32_t lagrangian_length;
      typedef float _lagrangian_type;
      _lagrangian_type st_lagrangian;
      _lagrangian_type * lagrangian;

    multiplier():
      time(0),
      penalty(0),
      lagrangian_length(0), st_lagrangian(), lagrangian(nullptr)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_time;
      u_time.real = this->time;
      *(outbuffer + offset + 0) = (u_time.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_time.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_time.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_time.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->time);
      union {
        float real;
        uint32_t base;
      } u_penalty;
      u_penalty.real = this->penalty;
      *(outbuffer + offset + 0) = (u_penalty.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_penalty.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_penalty.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_penalty.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->penalty);
      *(outbuffer + offset + 0) = (this->lagrangian_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->lagrangian_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->lagrangian_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->lagrangian_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->lagrangian_length);
      for( uint32_t i = 0; i < lagrangian_length; i++){
      union {
        float real;
        uint32_t base;
      } u_lagrangiani;
      u_lagrangiani.real = this->lagrangian[i];
      *(outbuffer + offset + 0) = (u_lagrangiani.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_lagrangiani.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_lagrangiani.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_lagrangiani.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->lagrangian[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_time;
      u_time.base = 0;
      u_time.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_time.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_time.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_time.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->time = u_time.real;
      offset += sizeof(this->time);
      union {
        float real;
        uint32_t base;
      } u_penalty;
      u_penalty.base = 0;
      u_penalty.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_penalty.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_penalty.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_penalty.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->penalty = u_penalty.real;
      offset += sizeof(this->penalty);
      uint32_t lagrangian_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      lagrangian_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      lagrangian_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      lagrangian_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->lagrangian_length);
      if(lagrangian_lengthT > lagrangian_length)
        this->lagrangian = (float*)realloc(this->lagrangian, lagrangian_lengthT * sizeof(float));
      lagrangian_length = lagrangian_lengthT;
      for( uint32_t i = 0; i < lagrangian_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_lagrangian;
      u_st_lagrangian.base = 0;
      u_st_lagrangian.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_lagrangian.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_lagrangian.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_lagrangian.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_lagrangian = u_st_lagrangian.real;
      offset += sizeof(this->st_lagrangian);
        memcpy( &(this->lagrangian[i]), &(this->st_lagrangian), sizeof(float));
      }
     return offset;
    }

    virtual const char * getType() override { return "ocs2_msgs/multiplier"; };
    virtual const char * getMD5() override { return "8284394e15f2038e54705abd91aee001"; };

  };

}
#endif
