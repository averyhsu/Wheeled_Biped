#ifndef _ROS_SERVICE_Bool_h
#define _ROS_SERVICE_Bool_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rt_gui
{

static const char BOOL[] = "rt_gui/Bool";

  class BoolRequest : public ros::Msg
  {
    public:
      typedef bool _value_type;
      _value_type value;
      typedef const char* _client_name_type;
      _client_name_type client_name;
      typedef const char* _group_name_type;
      _group_name_type group_name;
      typedef const char* _data_name_type;
      _data_name_type data_name;

    BoolRequest():
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
        bool real;
        uint8_t base;
      } u_value;
      u_value.real = this->value;
      *(outbuffer + offset + 0) = (u_value.base >> (8 * 0)) & 0xFF;
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
        bool real;
        uint8_t base;
      } u_value;
      u_value.base = 0;
      u_value.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
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

    virtual const char * getType() override { return BOOL; };
    virtual const char * getMD5() override { return "e0efcc4e2bd8ba4b0e41a678faca6af8"; };

  };

  class BoolResponse : public ros::Msg
  {
    public:
      typedef bool _resp_type;
      _resp_type resp;

    BoolResponse():
      resp(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_resp;
      u_resp.real = this->resp;
      *(outbuffer + offset + 0) = (u_resp.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->resp);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        bool real;
        uint8_t base;
      } u_resp;
      u_resp.base = 0;
      u_resp.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->resp = u_resp.real;
      offset += sizeof(this->resp);
     return offset;
    }

    virtual const char * getType() override { return BOOL; };
    virtual const char * getMD5() override { return "e3a98d806e1c4fee01a17d597e27ea8e"; };

  };

  class Bool {
    public:
    typedef BoolRequest Request;
    typedef BoolResponse Response;
  };

}
#endif
