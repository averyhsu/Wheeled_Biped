#ifndef _ROS_SERVICE_List_h
#define _ROS_SERVICE_List_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rt_gui
{

static const char LIST[] = "rt_gui/List";

  class ListRequest : public ros::Msg
  {
    public:
      typedef const char* _value_type;
      _value_type value;
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

    ListRequest():
      value(""),
      list_length(0), st_list(), list(nullptr),
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
      uint32_t length_value;
      arrToVar(length_value, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_value; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_value-1]=0;
      this->value = (char *)(inbuffer + offset-1);
      offset += length_value;
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

    virtual const char * getType() override { return LIST; };
    virtual const char * getMD5() override { return "0edbbd1b6710b0c8f2864dc248abd418"; };

  };

  class ListResponse : public ros::Msg
  {
    public:
      typedef const char* _resp_type;
      _resp_type resp;

    ListResponse():
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

    virtual const char * getType() override { return LIST; };
    virtual const char * getMD5() override { return "b791c1a4a4f0cee32b54dd1a73706a59"; };

  };

  class List {
    public:
    typedef ListRequest Request;
    typedef ListResponse Response;
  };

}
#endif
