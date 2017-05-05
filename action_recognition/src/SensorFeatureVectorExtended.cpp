#include <tf2/LinearMath/Quaternion.h>
#include <fstream>
#include <iostream> 
#include "action_recognition/SensorFeatureVectorExtended.hpp"
#include "action_recognition/SensorFeatureVector.hpp"
#include "action_recognition/common.hpp"

SensorFeatureVectorExtended::SensorFeatureVectorExtended(Vector3D vector3D, tf2::Quaternion quaternion):SensorFeatureVector(vector3D), quaternion_(quaternion){}

SensorFeatureVectorExtended::SensorFeatureVectorExtended(float x, float y, float z, tf2::Quaternion quaternion):
  SensorFeatureVector(x,y,z), quaternion_(quaternion){}

SensorFeatureVectorExtended::SensorFeatureVectorExtended(std::vector<float> values_vector):SensorFeatureVector(values_vector){
  if(values_vector.size() != SENSOR_FEATURE_VECTOR_EXTENDED_SIZE)
    std::cerr << "The vector size for a Sensorfeaturevectorextended initialization should be " << SENSOR_FEATURE_VECTOR_EXTENDED_SIZE << std::endl;
  else{
    int i = 3;
    quaternion_ = tf2::Quaternion(values_vector[i++],values_vector[i++],values_vector[i++], values_vector[i++]);
  }
}

SensorFeatureVectorExtended::SensorFeatureVectorExtended(float x, float y, float z, float x_q, float y_q, float z_q, float w):
  SensorFeatureVector(x,y,z),quaternion_(x_q, y_q, z_q, w){}

tf2::Quaternion SensorFeatureVectorExtended::get_quaternion(void){return quaternion_;}

SensorFeatureVectorExtended SensorFeatureVectorExtended::normalize(void){
    return SensorFeatureVectorExtended(vector3D_.normalize(), quaternion_.normalize());
}

void SensorFeatureVectorExtended::write_to_file(std::ofstream &os){  
  std::vector<float> values_vector(SENSOR_FEATURE_VECTOR_EXTENDED_SIZE);
  values_vector[VectorElements::X]=vector3D_.get_x();
  values_vector[VectorElements::Y]=vector3D_.get_y();
  values_vector[VectorElements::Z]=vector3D_.get_z();
  values_vector[VectorElements::X_Q]=quaternion_.getX();
  values_vector[VectorElements::Y_Q]=quaternion_.getY();
  values_vector[VectorElements::Z_Q]=quaternion_.getZ();
  values_vector[VectorElements::W]=quaternion_.getW();
  tools::swap_endian(values_vector.begin(),values_vector.end());
  os.write((char *)&values_vector[0], values_vector.size()*sizeof(float));
}


void SensorFeatureVectorExtended::print_vector(void){
  std::cout << "[ "<< vector3D_.get_x() << ", " << vector3D_.get_y() << ", " << vector3D_.get_z() << ", " << quaternion_.getX() << ", " << quaternion_.getY() << ", " << quaternion_.getZ() << ", " <<quaternion_.getW()<< " ]" << std::endl; 

}

int SensorFeatureVectorExtended::get_size(void){return SENSOR_FEATURE_VECTOR_EXTENDED_SIZE;}
