#ifndef _ROS_SERVICE_Check_h
#define _ROS_SERVICE_Check_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rt_gui
{

static const char CHECK[] = "rt_gui/Check";

  class CheckRequest : public ros::Msg
  {
    public:
      uint32_t value_length;
      typedef bool _value_type;
      _value_type st_value;
      _value_type * value;
      uint32_t list_length;
      typedef char* _list_type;
      _list_type st_list;
      _list_type * list;
      typedef const char* _client_name_type;
      _client_name_type client_name;
      typedef const char* _group_name_type;
      _group_name_type group_name;
      typedef const char* _data_name_type;
      _data_name_type data_name;

    CheckRequest():
      value_length(0), st_value(), value(nullptr),
      list_length(0), st_list(), list(nullptr),
      client_name(""),
      group_name(""),
      data_name("")
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->value_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->value_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->value_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->value_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->value_length);
      for( uint32_t i = 0; i < value_length; i++){
      union {
        bool real;
        uint8_t base;
      } u_valuei;
      u_valuei.real = this->value[i];
      *(outbuffer + offset + 0) = (u_valuei.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->value[i]);
      }
      *(outbuffer + offset + 0) = (this->list_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->list_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->list_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->list_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->list_length);
      for( uint32_t i = 0; i < list_length; i++){
      uint32_t length_listi = strlen(this->list[i]);
      varToArr(outbuffer + offset, length_listi);
      offset += 4;
      memcpy(outbuffer + offset, this->list[i], length_listi);
      offset += length_listi;
      }
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
      uint32_t value_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      value_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      value_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      value_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->value_length);
      if(value_lengthT > value_length)
        this->value = (bool*)realloc(this->value, value_lengthT * sizeof(bool));
      value_length = value_lengthT;
      for( uint32_t i = 0; i < value_length; i++){
      union {
        bool real;
        uint8_t base;
      } u_st_value;
      u_st_value.base = 0;
      u_st_value.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->st_value = u_st_value.real;
      offset += sizeof(this->st_value);
        memcpy( &(this->value[i]), &(this->st_value), sizeof(bool));
      }
      uint32_t list_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      list_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      list_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      list_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->list_length);
      if(list_lengthT > list_length)
        this->list = (char**)realloc(this->list, list_lengthT * sizeof(char*));
      list_length = list_lengthT;
      for( uint32_t i = 0; i < list_length; i++){
      uint32_t length_st_list;
      arrToVar(length_st_list, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_st_list; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_st_list-1]=0;
      this->st_list = (char *)(inbuffer + offset-1);
      offset += length_st_list;
        memcpy( &(this->list[i]), &(this->st_list), sizeof(char*));
      }
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

    virtual const char * getType() override { return CHECK; };
    virtual const char * getMD5() override { return "a874a12531b63dba24dbc0a8ee774cca"; };

  };

  class CheckResponse : public ros::Msg
  {
    public:
      typedef bool _resp_type;
      _resp_type resp;

    CheckResponse():
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

    virtual const char * getType() override { return CHECK; };
    virtual const char * getMD5() override { return "e3a98d806e1c4fee01a17d597e27ea8e"; };

  };

  class Check {
    public:
    typedef CheckRequest Request;
    typedef CheckResponse Response;
  };

}
#endif
