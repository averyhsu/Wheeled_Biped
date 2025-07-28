#ifndef _ROS_ocs2_msgs_lagrangian_metrics_h
#define _ROS_ocs2_msgs_lagrangian_metrics_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace ocs2_msgs
{

  class lagrangian_metrics : public ros::Msg
  {
    public:
      typedef float _time_type;
      _time_type time;
      typedef float _penalty_type;
      _penalty_type penalty;
      uint32_t constraint_length;
      typedef float _constraint_type;
      _constraint_type st_constraint;
      _constraint_type * constraint;

    lagrangian_metrics():
      time(0),
      penalty(0),
      constraint_length(0), st_constraint(), constraint(nullptr)
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
      *(outbuffer + offset + 0) = (this->constraint_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->constraint_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->constraint_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->constraint_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->constraint_length);
      for( uint32_t i = 0; i < constraint_length; i++){
      union {
        float real;
        uint32_t base;
      } u_constrainti;
      u_constrainti.real = this->constraint[i];
      *(outbuffer + offset + 0) = (u_constrainti.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_constrainti.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_constrainti.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_constrainti.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->constraint[i]);
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
      uint32_t constraint_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      constraint_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      constraint_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      constraint_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->constraint_length);
      if(constraint_lengthT > constraint_length)
        this->constraint = (float*)realloc(this->constraint, constraint_lengthT * sizeof(float));
      constraint_length = constraint_lengthT;
      for( uint32_t i = 0; i < constraint_length; i++){
      union {
        float real;
        uint32_t base;
      } u_st_constraint;
      u_st_constraint.base = 0;
      u_st_constraint.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_st_constraint.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_st_constraint.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_st_constraint.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->st_constraint = u_st_constraint.real;
      offset += sizeof(this->st_constraint);
        memcpy( &(this->constraint[i]), &(this->st_constraint), sizeof(float));
      }
     return offset;
    }

    virtual const char * getType() override { return "ocs2_msgs/lagrangian_metrics"; };
    virtual const char * getMD5() override { return "1734f3665afb7d38e9db59de18711863"; };

  };

}
#endif
