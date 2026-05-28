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
 for (double v1 = 16; v1 <= 30; v1 += 0.1){
        for (double k = 0.0005; k <= 0.001; k += 0.000001){
            
            double total_error = 0.0; 
            
            for(int i = 0; i < degree_values.size(); i++){
                double simulated_distance = simulate_distance(degree_values[i], v1, k);
                double current_error = abs(simulated_distance - distance_values[i]);
                
                total_error += current_error; // Add up errors for ALL points
                
                // Debug print for close matches (optional)
/*
                if (current_error < 0.4){
                    cout << "v0: " << v1 
                         << " | k: " << k 
                         << " | degree: " << degree_values[i] 
                         << " | simulated: " << simulated_distance 
                         << " | actual: " << distance_values[i] 
                         << " | error: " << current_error 
                         << endl;
                }
*/
            }
            
           
            if (total_error < min_error) {
                min_error = total_error;
                best_v0 = v1;
                best_k = k;
            }
        }
    }
    
    // FIX 3: Print out your definitive final results
    cout << "\n=====================================" << endl;
    cout << "Best Initial Velocity (v0): " << best_v0 << " ft/s" << endl;
    cout << "Best Drag Factor (k):       " << best_k << " kg/ft" << endl;
    cout << "Minimum Total Combined Error: " << min_error << " ft" << endl;
    cout << "=====================================" << endl;
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


void calcDist(double v0, double k, double x1, double y1) {
    
    double deg = 6;
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
    double distance_to_point;
    for (deg = 6; deg <= 90; deg += 0.1){
         t=0;
         x = 0;
         y = 5 * sin(deg * pi / 180.0);
         vx = v0 * cos(deg * pi / 180.0);
         vy = v0 * sin(deg * pi / 180.0);
        double min_distance = 1e9; // Initialize min distance to a large number
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
        distance_to_point = sqrt(pow(x - x1, 2) + pow(y - y1, 2));
        if (distance_to_point < min_distance) {
            min_distance = distance_to_point;
        }

    }
    if (min_distance < 0.5) {
        cout << "Close to point at degree: " << deg << " with min distance: " << min_distance << endl;
    }    
}
}




int main() {
    double k = 0.000712;
    double v0 = 22.8;
    
    //run_calc();
    //cout <<simulate_distance(11, v0, k);
    //get_plot(11, v0, k);
    calcDist(v0, k, 50, 5);
    return 0;
}