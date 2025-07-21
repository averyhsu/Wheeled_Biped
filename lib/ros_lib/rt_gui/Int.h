#ifndef _ROS_SERVICE_Int_h
#define _ROS_SERVICE_Int_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rt_gui
{

static const char INT[] = "rt_gui/Int";

  class IntRequest : public ros::Msg
  {
    public:
      typedef int64_t _min_type;
      _min_type min;
      typedef int64_t _max_type;
      _max_type max;
      typedef int64_t _value_type;
      _value_type value;
      typedef const char* _client_name_type;
      _client_name_type client_name;
      typedef const char* _group_name_type;
      _group_name_type group_name;
      typedef const char* _data_name_type;
      _data_name_type data_name;

    IntRequest():
      min(0),
      max(0),
      value(0),
      client_name(""),
      group_name(""),
      data_name("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        int64_t real;
        uint64_t base;
      } u_min;
      u_min.real = this->min;
      *(outbuffer + offset + 0) = (u_min.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_min.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_min.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_min.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_min.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_min.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_min.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_min.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->min);
      union {
        int64_t real;
        uint64_t base;
      } u_max;
      u_max.real = this->max;
      *(outbuffer + offset + 0) = (u_max.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_max.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_max.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_max.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_max.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_max.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_max.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_max.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->max);
      union {
        int64_t real;
        uint64_t base;
      } u_value;
      u_value.real = this->value;
      *(outbuffer + offset + 0) = (u_value.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_value.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_value.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_value.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_value.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_value.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_value.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_value.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->value);
      uint32_t length_client_name = strlen(this->client_name);
      varToArr(outbuffer + offset, length_client_name);
      offset += 4;
      memcpy(outbuffer + offset, this->client_name, length_client_name);
      offset += length_client_name;
      uint32_t length_group_name = strlen(this->group_name);
      varToArr(outbuffer + offset, length_group_name);
      offset += 4;
      memcpy(outbuffer + offset, this->group_name, length_group_name);
      offset += length_group_name;
      uint32_t length_data_name = strlen(this->data_name);
      varToArr(outbuffer + offset, length_data_name);
      offset += 4;
      memcpy(outbuffer + offset, this->data_name, length_data_name);
      offset += length_data_name;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        int64_t real;
        uint64_t base;
      } u_min;
      u_min.base = 0;
      u_min.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_min.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_min.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_min.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_min.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_min.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_min.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_min.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->min = u_min.real;
      offset += sizeof(this->min);
      union {
        int64_t real;
        uint64_t base;
      } u_max;
      u_max.base = 0;
      u_max.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_max.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_max.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_max.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_max.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_max.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_max.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_max.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->max = u_max.real;
      offset += sizeof(this->max);
      union {
        int64_t real;
        uint64_t base;
      } u_value;
      u_value.base = 0;
      u_value.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_value.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_value.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_value.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_value.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_value.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_value.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_value.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->value = u_value.real;
      offset += sizeof(this->value);
      uint32_t length_client_name;
      arrToVar(length_client_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_client_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_client_name-1]=0;
      this->client_name = (char *)(inbuffer + offset-1);
      offset += length_client_name;
      uint32_t length_group_name;
      arrToVar(length_group_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_group_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_group_name-1]=0;
      this->group_name = (char *)(inbuffer + offset-1);
      offset += length_group_name;
      uint32_t length_data_name;
      arrToVar(length_data_name, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_data_name; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_data_name-1]=0;
      this->data_name = (char *)(inbuffer + offset-1);
      offset += length_data_name;
     return offset;
    }

    virtual const char * getType() override { return INT; };
    virtual const char * getMD5() override { return "d06aaca1be915d4432a24f59ccd418dd"; };

  };

  class IntResponse : public ros::Msg
  {
    public:
      typedef int64_t _resp_type;
      _resp_type resp;

    IntResponse():
      resp(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        int64_t real;
        uint64_t base;
      } u_resp;
      u_resp.real = this->resp;
      *(outbuffer + offset + 0) = (u_resp.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_resp.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_resp.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_resp.base >> (8 * 3)) & 0xFF;
      *(outbuffer + offset + 4) = (u_resp.base >> (8 * 4)) & 0xFF;
      *(outbuffer + offset + 5) = (u_resp.base >> (8 * 5)) & 0xFF;
      *(outbuffer + offset + 6) = (u_resp.base >> (8 * 6)) & 0xFF;
      *(outbuffer + offset + 7) = (u_resp.base >> (8 * 7)) & 0xFF;
      offset += sizeof(this->resp);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        int64_t real;
        uint64_t base;
      } u_resp;
      u_resp.base = 0;
      u_resp.base |= ((uint64_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_resp.base |= ((uint64_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_resp.base |= ((uint64_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_resp.base |= ((uint64_t) (*(inbuffer + offset + 3))) << (8 * 3);
      u_resp.base |= ((uint64_t) (*(inbuffer + offset + 4))) << (8 * 4);
      u_resp.base |= ((uint64_t) (*(inbuffer + offset + 5))) << (8 * 5);
      u_resp.base |= ((uint64_t) (*(inbuffer + offset + 6))) << (8 * 6);
      u_resp.base |= ((uint64_t) (*(inbuffer + offset + 7))) << (8 * 7);
      this->resp = u_resp.real;
      offset += sizeof(this->resp);
     return offset;
    }

    virtual const char * getType() override { return INT; };
    virtual const char * getMD5() override { return "15982c3a12e735514ac7ff5c21fc3ece"; };

  };

  class Int {
    public:
    typedef IntRequest Request;
    typedef IntResponse Response;
  };

}
#endif
