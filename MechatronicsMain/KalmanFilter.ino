#import <BasicLinearAlgebra.h> using namespace BLA;
float kalmanFilter(float z,float R){
  static BLA::Matrix<2,1> x = {0,0};
  static BLA::Matrix<2,2> P = {0.01,0,0,0.01};
  static const float dt = 0.01f;
   //static const float R = 0.6;
  static BLA::Matrix<2,2> Qk = {0.005,0,0,0.004};
  static BLA::Matrix<2,2> F = {1,dt,0,1};
  static BLA::Matrix<1,2> H = {1,0};
  static BLA::Matrix<2,1> B = {0,dt};
  static BLA::Matrix<2,2> I = {1,0,0,1};
  float u = 0.5;

  x = F * x + B * u;
  P = F * P * (~F) + Qk;

  // Update
  float S = (H * P * (~H))(0,0) + R;
  BLA::Matrix<2,1> K = (P * (~H)) / S;
  x = x + K * (z - (H * x)(0,0));
  P = (I - K * H) * P;

  return x(0,0);
}

  // Use to test how long it takes to compute
  // uint32_t t0 = micros();
  // for (int i = 0; i < 100; ++i) {
  //   kalmanUpdate(fakeMeasurement());  // your KF
  // }
  // uint32_t dt100 = micros() - t0;
  // Serial.print("Per update (us): ");
  // Serial.println(dt100 / 100.0);


  // Origional

  // const int step = 100;
  // float X[step];
  // float filteredDistance[step];
  // float predictedDistance[step];

  //   //B = {0,dt};
  // predictedDistance[:,1] = (X[:,1],0);

  // //Gatering 100 datapoints
  // for (int i = 0; i < step; i++) {
  // X[i] = analogRead(IRpin) / 1023.0 * 5.0;  // example sensor read - maybe map
  // }

  // for (int k = 1; k <= n; n++){
  // preditedDistance[:,k] = F * filteredDistance[:,k-1]; //+ B * u;
  // P_pred = F*P*F.T + Qk;

  // Y = X(k);
  // K = (P_pred*H.T)/(H*P_pred*H.T+R);
  // P = (I, K.H)*P_pred;

  // filteredDistance[:,k] = predictedDistance[:,k] + K*(Y-H*predictedDistance[:,k]);
