#ifndef _ROS_SERVICE_Text_h
#define _ROS_SERVICE_Text_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rt_gui
{

static const char TEXT[] = "rt_gui/Text";

  class TextRequest : public ros::Msg
  {
    public:
      typedef const char* _value_type;
      _value_type value;
      typedef const char* _client_name_type;
      _client_name_type client_name;
      typedef const char* _group_name_type;
      _group_name_type group_name;
      typedef const char* _data_name_type;
      _data_name_type data_name;

    TextRequest():
      value(""),
      client_name(""),
      group_name(""),
      data_name("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      uint32_t length_value = strlen(this->value);
      varToArr(outbuffer + offset, length_value);
      offset += 4;
      memcpy(outbuffer + offset, this->value, length_value);
      offset += length_value;
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
      uint32_t length_value;
      arrToVar(length_value, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_value; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_value-1]=0;
      this->value = (char *)(inbuffer + offset-1);
      offset += length_value;
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

    virtual const char * getType() override { return TEXT; };
    virtual const char * getMD5() override { return "eda7c33a2457f9e06463723b58123da8"; };

  };

  class TextResponse : public ros::Msg
  {
    public:
      typedef const char* _resp_type;
      _resp_type resp;

    TextResponse():
      resp("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      uint32_t length_resp = strlen(this->resp);
      varToArr(outbuffer + offset, length_resp);
      offset += 4;
      memcpy(outbuffer + offset, this->resp, length_resp);
      offset += length_resp;
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      uint32_t length_resp;
      arrToVar(length_resp, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_resp; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_resp-1]=0;
      this->resp = (char *)(inbuffer + offset-1);
      offset += length_resp;
     return offset;
    }

    virtual const char * getType() override { return TEXT; };
    virtual const char * getMD5() override { return "b791c1a4a4f0cee32b54dd1a73706a59"; };

  };

  class Text {
    public:
    typedef TextRequest Request;
    typedef TextResponse Response;
  };

}
#endif
