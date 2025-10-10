import <BasicLinearAlgebra.h> using namespace BLA;

BLA::Matrix<2,2> F,P,Qk, I;
BLA::Matrix<2,1> B, K,
BLA::Matrix<1,2> H;
float R = 0.5f;
float u = 0.5f;
float dt = 0.01f;

const int step = 100;
float u = 0.5f;
float dt = 0.001;

int X = [step];

int filteredDistance = [step];
int predictedDistance = [step];

void kalmanFilter(){

F = {1,dt,0,1};
H = {1,0};
//B = {0,dt};


x[:,1] = (X[1],0);
//Gatering 100 datapoints
for (int i = 0; i < step; i++) {
X[i] = analogRead(A0) / 1023.0 * 5.0;  // example sensor read - maybe map
}

for (int k = 1; k <= n; n++){
preditedDistance[:,k] = F * filteredDistance[:,k-1]; //+ B * u;
P_pred = F*P*F.T + Qk;

Y = X(k);
K = (P_pred*H.T)/(H*P_pred*H.T+R);

P = (eye(2), K.H)*P_pred;
filteredDistance = predictedDistance[:,k] + K*(Y-H*predictedDistance[:,k]);

}

// Use to test how long it takes to compute
// uint32_t t0 = micros();
// for (int i = 0; i < 100; ++i) {
//   kalmanUpdate(fakeMeasurement());  // your KF
// }
// uint32_t dt100 = micros() - t0;
// Serial.print("Per update (us): ");
// Serial.println(dt100 / 100.0);
