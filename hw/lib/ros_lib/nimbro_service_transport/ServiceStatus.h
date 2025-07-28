#ifndef _ROS_nimbro_service_transport_ServiceStatus_h
#define _ROS_nimbro_service_transport_ServiceStatus_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace nimbro_service_transport
{

  class ServiceStatus : public ros::Msg
  {
    public:
      typedef const char* _host_type;
      _host_type host;
      typedef const char* _remote_type;
      _remote_type remote;
      typedef uint16_t _remote_port_type;
      _remote_port_type remote_port;
      typedef uint32_t _call_id_type;
      _call_id_type call_id;
      typedef const char* _service_type;
      _service_type service;
      typedef uint8_t _status_type;
      _status_type status;
      enum { STATUS_FINISHED_SUCCESS =  1 };
      enum { STATUS_FINISHED_ERROR =  2 };
      enum { STATUS_IN_PROGRESS =  3 };
      enum { STATUS_TIMEOUT =  4 };
      enum { STATUS_CONNECTION_ERROR =  5 };

    ServiceStatus():
      host(""),
      remote(""),
      remote_port(0),
      call_id(0),
      service(""),
      status(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      uint32_t length_host = strlen(this->host);
      varToArr(outbuffer + offset, length_host);
      offset += 4;
      memcpy(outbuffer + offset, this->host, length_host);
      offset += length_host;
      uint32_t length_remote = strlen(this->remote);
      varToArr(outbuffer + offset, length_remote);
      offset += 4;
      memcpy(outbuffer + offset, this->remote, length_remote);
      offset += length_remote;
      *(outbuffer + offset + 0) = (this->remote_port >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->remote_port >> (8 * 1)) & 0xFF;
      offset += sizeof(this->remote_port);
      *(outbuffer + offset + 0) = (this->call_id >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->call_id >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->call_id >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->call_id >> (8 * 3)) & 0xFF;
      offset += sizeof(this->call_id);
      uint32_t length_service = strlen(this->service);
      varToArr(outbuffer + offset, length_service);
      offset += 4;
      memcpy(outbuffer + offset, this->service, length_service);
      offset += length_service;
      *(outbuffer + offset + 0) = (this->status >> (8 * 0)) & 0xFF;
      offset += sizeof(this->status);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      uint32_t length_host;
      arrToVar(length_host, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_host; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_host-1]=0;
      this->host = (char *)(inbuffer + offset-1);
      offset += length_host;
      uint32_t length_remote;
      arrToVar(length_remote, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_remote; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_remote-1]=0;
      this->remote = (char *)(inbuffer + offset-1);
      offset += length_remote;
      this->remote_port =  ((uint16_t) (*(inbuffer + offset)));
      this->remote_port |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      offset += sizeof(this->remote_port);
      this->call_id =  ((uint32_t) (*(inbuffer + offset)));
      this->call_id |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->call_id |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      this->call_id |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      offset += sizeof(this->call_id);
      uint32_t length_service;
      arrToVar(length_service, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_service; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_service-1]=0;
      this->service = (char *)(inbuffer + offset-1);
      offset += length_service;
      this->status =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->status);
     return offset;
    }

    virtual const char * getType() override { return "nimbro_service_transport/ServiceStatus"; };
    virtual const char * getMD5() override { return "2afd58b569abd78a2992e01ed942edaa"; };

  };

}
#endif
