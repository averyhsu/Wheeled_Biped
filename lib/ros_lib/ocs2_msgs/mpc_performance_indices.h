#ifndef _ROS_ocs2_msgs_mpc_performance_indices_h
#define _ROS_ocs2_msgs_mpc_performance_indices_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace ocs2_msgs
{

  class mpc_performance_indices : public ros::Msg
  {
    public:
      typedef float _initTime_type;
      _initTime_type initTime;
      typedef float _merit_type;
      _merit_type merit;
      typedef float _cost_type;
      _cost_type cost;
      typedef float _dynamicsViolationSSE_type;
      _dynamicsViolationSSE_type dynamicsViolationSSE;
      typedef float _equalityConstraintsSSE_type;
      _equalityConstraintsSSE_type equalityConstraintsSSE;
      typedef float _equalityLagrangian_type;
      _equalityLagrangian_type equalityLagrangian;
      typedef float _inequalityLagrangian_type;
      _inequalityLagrangian_type inequalityLagrangian;

    mpc_performance_indices():
      initTime(0),
      merit(0),
      cost(0),
      dynamicsViolationSSE(0),
      equalityConstraintsSSE(0),
      equalityLagrangian(0),
      inequalityLagrangian(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_initTime;
      u_initTime.real = this->initTime;
      *(outbuffer + offset + 0) = (u_initTime.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_initTime.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_initTime.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_initTime.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->initTime);
      union {
        float real;
        uint32_t base;
      } u_merit;
      u_merit.real = this->merit;
      *(outbuffer + offset + 0) = (u_merit.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_merit.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_merit.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_merit.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->merit);
      union {
        float real;
        uint32_t base;
      } u_cost;
      u_cost.real = this->cost;
      *(outbuffer + offset + 0) = (u_cost.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_cost.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_cost.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_cost.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->cost);
      union {
        float real;
        uint32_t base;
      } u_dynamicsViolationSSE;
      u_dynamicsViolationSSE.real = this->dynamicsViolationSSE;
      *(outbuffer + offset + 0) = (u_dynamicsViolationSSE.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_dynamicsViolationSSE.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_dynamicsViolationSSE.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_dynamicsViolationSSE.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->dynamicsViolationSSE);
      union {
        float real;
        uint32_t base;
      } u_equalityConstraintsSSE;
      u_equalityConstraintsSSE.real = this->equalityConstraintsSSE;
      *(outbuffer + offset + 0) = (u_equalityConstraintsSSE.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_equalityConstraintsSSE.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_equalityConstraintsSSE.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_equalityConstraintsSSE.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->equalityConstraintsSSE);
      union {
        float real;
        uint32_t base;
      } u_equalityLagrangian;
      u_equalityLagrangian.real = this->equalityLagrangian;
      *(outbuffer + offset + 0) = (u_equalityLagrangian.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_equalityLagrangian.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_equalityLagrangian.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_equalityLagrangian.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->equalityLagrangian);
      union {
        float real;
        uint32_t base;
      } u_inequalityLagrangian;
      u_inequalityLagrangian.real = this->inequalityLagrangian;
      *(outbuffer + offset + 0) = (u_inequalityLagrangian.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_inequalityLagrangian.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_inequalityLagrangian.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_inequalityLagrangian.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->inequalityLagrangian);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        float real;
        uint32_t base;
      } u_initTime;
      u_initTime.base = 0;
      u_initTime.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_initTime.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_initTime.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_initTime.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->initTime = u_initTime.real;
      offset += sizeof(this->initTime);
      union {
        float real;
        uint32_t base;
      } u_merit;
      u_merit.base = 0;
      u_merit.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_merit.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_merit.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_merit.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->merit = u_merit.real;
      offset += sizeof(this->merit);
      union {
        float real;
        uint32_t base;
      } u_cost;
      u_cost.base = 0;
      u_cost.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_cost.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_cost.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_cost.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->cost = u_cost.real;
      offset += sizeof(this->cost);
      union {
        float real;
        uint32_t base;
      } u_dynamicsViolationSSE;
      u_dynamicsViolationSSE.base = 0;
      u_dynamicsViolationSSE.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_dynamicsViolationSSE.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_dynamicsViolationSSE.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_dynamicsViolationSSE.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->dynamicsViolationSSE = u_dynamicsViolationSSE.real;
      offset += sizeof(this->dynamicsViolationSSE);
      union {
        float real;
        uint32_t base;
      } u_equalityConstraintsSSE;
      u_equalityConstraintsSSE.base = 0;
      u_equalityConstraintsSSE.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_equalityConstraintsSSE.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_equalityConstraintsSSE.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_equalityConstraintsSSE.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->equalityConstraintsSSE = u_equalityConstraintsSSE.real;
      offset += sizeof(this->equalityConstraintsSSE);
      union {
        float real;
        uint32_t base;
      } u_equalityLagrangian;
      u_equalityLagrangian.base = 0;
      u_equalityLagrangian.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_equalityLagrangian.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_equalityLagrangian.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_equalityLagrangian.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->equalityLagrangian = u_equalityLagrangian.real;
      offset += sizeof(this->equalityLagrangian);
      union {
        float real;
        uint32_t base;
      } u_inequalityLagrangian;
      u_inequalityLagrangian.base = 0;
      u_inequalityLagrangian.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_inequalityLagrangian.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_inequalityLagrangian.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_inequalityLagrangian.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->inequalityLagrangian = u_inequalityLagrangian.real;
      offset += sizeof(this->inequalityLagrangian);
     return offset;
    }

    virtual const char * getType() override { return "ocs2_msgs/mpc_performance_indices"; };
    virtual const char * getMD5() override { return "d3efdce4c946e170e65e642157f48398"; };

  };

}
#endif
