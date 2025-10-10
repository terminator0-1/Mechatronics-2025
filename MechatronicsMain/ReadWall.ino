1. V = analogRead(IRpin);

2. d_cm = voltage_linear_regression(V); ----> get values from MATLAB fit . Many datapoints of voltage at certain distances. 

3. d_filt = kalmanfilter(d_cm); 


4. To make a even better filter, we can recursively update R and Q based on the the recent varience between points. 

var(X) = sum(xi - sample_avg)^2 / N_samples - 1


We can also combine the moving average with the Kalman filter to ensure that spikes are covered and don't affect the Kalman filter.

structure:


int N = 10;
float sum = 0;
R = 0.5;
Q = 0.01;
float varsum = 0;
bool sensingWall = true;
float averageVoltage = 0;
while (sensingWall){
averageVoltage = 0;

float voltageReadings[N];
// Gather readings
  for(int i; i<N;i++){
	float V = analogRead(IRpin) * (5.0 / 1023.0);
	sum += V; // Gathering sum.
    } 
    averageVoltage = sum/N;
	
  for(int i; i<N;i++){
	varsum += pow(voltageReadings[i] - avgVoltage,2);
  }
  samp_var = varsum / N-1;This is R! Q can stay const. 

   // Update R adaptively
   R = 0.9 * R + 0.1 * samp_var;
    distance_reg = matlab_regression(averageVoltage);
    distance_filt = kalanFilter(distance_reg, R); // Hopefully this achieves an error no less than 1%.
    if (rms(desired dist & distance_filt)) >= error) {
	//Do something
	stop motors.
	sensingWall = false;
}

5. After all is said and done. We need to compare the filtering results. We will compare the filtered_cm to the actual_cm, based on that line we will see what the maximum error is for our filtering and exactly where that occurs.
