#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>
#include <cmath>
using namespace std;

double simulate_distance(double deg, double v0, double k){
    double x = 0;
    const double pi =  3.14159265358979323846;
    const double m = 0.057;
    const double g = 3.2808399;//gravity in ft/s^2
    const double dt = 0.0001;
    double y = 5 * sin(deg * pi / 180.0);
    double vx = v0 * cos(deg * pi / 180.0);
    double vy = v0 * sin(deg * pi / 180.0);
    double v;
    double ax, ay;

    while (y >= 0.0){
        //calculate velocity magnitude
        v = sqrt(vx*vx + vy*vy);
        //calculate acceleration due to drag and gravity 
        ax = (-k * v * vx) / m;
        ay = (-k * v * vy) / m - g;
        //update velocity and position using Euler's method
        vx += ax * dt;
        vy += ay * dt;
        x += vx * dt;
        y += vy * dt; 
    }
    return x;
}

void run_calc() {
    vector<double> degree_values;
    vector<double> distance_values;

    //open csv file and initialize read variable
    ifstream file("input.csv", ios::in);
    string line;

    getline(file, line); // Skip the header line

    while(getline(file, line)) {
        stringstream ss(line);
        double d,f;
        char comma;

        ss >> d >> comma >> f; // Read degree and distance values
        degree_values.push_back(d);
        distance_values.push_back(f);
    }
    file.close();

    double total_error = 0.0;
    double simulated_distance;
    double best_v0 = 0.0;
    double best_k = 0.0;
    double min_error = 1e9;
    
    //the file outputs have been read and stored in the vectors, now we can use them
    for (double v1 = 35; v1 <= 38; v1 += 0.1){
        for (double k = 0.002; k <= 0.004; k += 0.00005){
            
            for(int i = 0; i < degree_values.size(); i++){
                
                simulated_distance = simulate_distance(degree_values[i], v1, k);
                total_error += abs(simulated_distance - distance_values[i]);
                
               if (abs(simulated_distance - distance_values[i]) < 0.4){
                cout << "v0: " << v1 
                     << " | k: " << k 
                     << " | degree: " << degree_values[i] 
                     << " | simulated: " << simulated_distance 
                     << " | actual: " << distance_values[i] 
                     << " | error: " << abs(simulated_distance - distance_values[i]) 
                     << endl;
               }
                if (abs(simulated_distance - distance_values[i]) < min_error) {
                    min_error = abs(simulated_distance - distance_values[i]);
                    best_v0 = v1;
                    best_k = k;
                }
            }
            
            
        }
    }

    // FIXED: Corrected the mismatched variables here so it labels the output properly
            cout << "--> Total error for v0 = " << best_v0 << " and k = " << best_k << " error: " << min_error 
                 << endl;   

    
}

void get_plot(double deg, double v0, double k){
    double t=0;
    double x = 0;
    const double pi =  3.14159265358979323846;
    const double m = 0.057;
    const double g = 3.2808399;//gravity in ft/s^2
    const double dt = 0.00001;
    double y = 5 * sin(deg * pi / 180.0);
    double vx = v0 * cos(deg * pi / 180.0);
    double vy = v0 * sin(deg * pi / 180.0);
    double v;
    double ax, ay;

    ofstream plot_file("plot.csv");
    if (!plot_file) {
        cerr << "Unable to open plot.csv for writing." << endl;
        return;
    }
    plot_file << "t,x,y\n";
    int counter = 0;

    while (y >= 0.0){
        //calculate velocity magnitude
        v = sqrt(vx*vx + vy*vy);
        //calculate acceleration due to drag and gravity 
        ax = (-k * v * vx) / m;
        ay = (-k * v * vy) / m - g;
        //update velocity and position using Euler's method
        vx += ax * dt;
        vy += ay * dt;
        x += vx * dt;
        y += vy * dt;
        t += dt;
        if (counter % 1000 == 0) {
            plot_file << t << "," << x << "," << y << "\n";
        }
        counter++;
    }
    cout << "done!";
}


int main() {
    double k = 0.0029;
    double v0 = 38;
    
    // run_calc();
    //cout <<simulate_distance(45, v0, k);
    get_plot(45, v0, k);



    return 0;
}