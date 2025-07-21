#ifndef _ROS_SERVICE_Double_h
#define _ROS_SERVICE_Double_h
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace rt_gui
{

static const char DOUBLE[] = "rt_gui/Double";

  class DoubleRequest : public ros::Msg
  {
    public:
      typedef float _min_type;
      _min_type min;
      typedef float _max_type;
      _max_type max;
      typedef float _value_type;
      _value_type value;
      typedef const char* _client_name_type;
      _client_name_type client_name;
      typedef const char* _group_name_type;
      _group_name_type group_name;
      typedef const char* _data_name_type;
      _data_name_type data_name;

    DoubleRequest():
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
      offset += serializeAvrFloat64(outbuffer + offset, this->min);
      offset += serializeAvrFloat64(outbuffer + offset, this->max);
      offset += serializeAvrFloat64(outbuffer + offset, this->value);
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
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->min));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->max));
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->value));
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

    virtual const char * getType() override { return DOUBLE; };
    virtual const char * getMD5() override { return "f9ed3a668836c250d7dba1a0de44cdde"; };

  };

  class DoubleResponse : public ros::Msg
  {
    public:
      typedef float _resp_type;
      _resp_type resp;

    DoubleResponse():
      resp(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      offset += serializeAvrFloat64(outbuffer + offset, this->resp);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      offset += deserializeAvrFloat64(inbuffer + offset, &(this->resp));
     return offset;
    }

    virtual const char * getType() override { return DOUBLE; };
    virtual const char * getMD5() override { return "5c0620fff294da63cdbb093bfc819662"; };

  };

  class Double {
    public:
    typedef DoubleRequest Request;
    typedef DoubleResponse Response;
  };

}
#endif
