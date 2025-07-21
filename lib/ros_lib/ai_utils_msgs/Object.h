#ifndef _ROS_ai_utils_msgs_Object_h
#define _ROS_ai_utils_msgs_Object_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace ai_utils_msgs
{

  class Object : public ros::Msg
  {
    public:
      typedef int32_t _id_type;
      _id_type id;
      typedef const char* _type_type;
      _type_type type;
      typedef float _score_type;
      _score_type score;
      float centroid[2];
      float size[2];

    Object():
      id(0),
      type(""),
      score(0),
      centroid(),
      size()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const override
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_id;
      u_id.real = this->id;
      *(outbuffer + offset + 0) = (u_id.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_id.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_id.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_id.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->id);
      uint32_t length_type = strlen(this->type);
      varToArr(outbuffer + offset, length_type);
      offset += 4;
      memcpy(outbuffer + offset, this->type, length_type);
      offset += length_type;
      union {
        float real;
        uint32_t base;
      } u_score;
      u_score.real = this->score;
      *(outbuffer + offset + 0) = (u_score.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_score.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_score.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_score.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->score);
      for( uint32_t i = 0; i < 2; i++){
      union {
        float real;
        uint32_t base;
      } u_centroidi;
      u_centroidi.real = this->centroid[i];
      *(outbuffer + offset + 0) = (u_centroidi.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_centroidi.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_centroidi.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_centroidi.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->centroid[i]);
      }
      for( uint32_t i = 0; i < 2; i++){
      union {
        float real;
        uint32_t base;
      } u_sizei;
      u_sizei.real = this->size[i];
      *(outbuffer + offset + 0) = (u_sizei.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_sizei.base >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (u_sizei.base >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (u_sizei.base >> (8 * 3)) & 0xFF;
      offset += sizeof(this->size[i]);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer) override
    {
      int offset = 0;
      union {
        int32_t real;
        uint32_t base;
      } u_id;
      u_id.base = 0;
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_id.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->id = u_id.real;
      offset += sizeof(this->id);
      uint32_t length_type;
      arrToVar(length_type, (inbuffer + offset));
      offset += 4;
      for(unsigned int k= offset; k< offset+length_type; ++k){
          inbuffer[k-1]=inbuffer[k];
      }
      inbuffer[offset+length_type-1]=0;
      this->type = (char *)(inbuffer + offset-1);
      offset += length_type;
      union {
        float real;
        uint32_t base;
      } u_score;
      u_score.base = 0;
      u_score.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_score.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_score.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_score.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->score = u_score.real;
      offset += sizeof(this->score);
      for( uint32_t i = 0; i < 2; i++){
      union {
        float real;
        uint32_t base;
      } u_centroidi;
      u_centroidi.base = 0;
      u_centroidi.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_centroidi.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_centroidi.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_centroidi.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->centroid[i] = u_centroidi.real;
      offset += sizeof(this->centroid[i]);
      }
      for( uint32_t i = 0; i < 2; i++){
      union {
        float real;
        uint32_t base;
      } u_sizei;
      u_sizei.base = 0;
      u_sizei.base |= ((uint32_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_sizei.base |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1);
      u_sizei.base |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2);
      u_sizei.base |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3);
      this->size[i] = u_sizei.real;
      offset += sizeof(this->size[i]);
      }
     return offset;
    }

    virtual const char * getType() override { return "ai_utils_msgs/Object"; };
    virtual const char * getMD5() override { return "6060d584035957549c3a4a222ea21276"; };

  };

}
#endif
